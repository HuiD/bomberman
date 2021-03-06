/*
 * Copyright (c) 2013 Ahmed Samy  <f.fallen45@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#include "scheduler.h"

#include <iostream>
#include <algorithm>

Scheduler g_sched;

Scheduler::Scheduler()
{
	m_thread = std::thread(std::bind(&Scheduler::schedulerThread, this));
	m_stopped = false;
}

Scheduler::~Scheduler()
{

}

void Scheduler::stop()
{
	std::lock_guard<std::mutex> guard(m_mutex);
	m_stopped = true;
	m_condition.notify_one();
}

uint32_t Scheduler::scheduleEvent(const EventFunc& fun, int64_t delay, bool repeated)
{
	std::lock_guard<std::mutex> guard(m_mutex);
	if (m_stopped)
		return 0;

	EventPtr event(new Event(fun, delay, repeated));
	event->setID(++m_lastId);
	m_eventList.push_back(event);
	m_condition.notify_one();
	return event->getID();
}

void Scheduler::stopEvent(uint32_t eventId)
{
	// avoid race conditions and just remove in the thread
	std::lock_guard<std::mutex> guard(m_mutex);
	auto it = std::find(m_eventIds.begin(), m_eventIds.end(), eventId);
	if (it != m_eventIds.end())
		m_eventIds.erase(it);
}

void Scheduler::schedulerThread()
{
	std::unique_lock<std::mutex> uniqueLock(m_mutex, std::defer_lock);

	while (!m_stopped) {	
		uniqueLock.lock();
		while (m_eventList.empty())
			m_condition.wait(uniqueLock);

		if (m_stopped) {
			uniqueLock.unlock();
			break;
		}

		uniqueLock.unlock();
		for (auto it = m_eventList.begin(); it != m_eventList.end(); ++it) {
			uniqueLock.lock();
			const EventPtr& ev = *it;
			uniqueLock.unlock();

			auto iter = std::find(m_eventIds.begin(), m_eventIds.end(), ev->getID());
			if (iter != m_eventIds.end()) {
				(*ev) ();

				if (!ev->isRepeated()) {
					uniqueLock.lock();
					m_eventList.erase(it++);
					m_eventIds.erase(iter);
					uniqueLock.unlock();
				} else
					ev->setExpiration(ev->getDelay());
			} else {
				uniqueLock.lock();
				m_eventList.erase(it);
				uniqueLock.unlock();
			}
		}
	}
}


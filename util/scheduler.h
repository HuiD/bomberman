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
#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <thread>
#include <functional>
#include <condition_variable>
#include <list>
#include <chrono>

typedef std::function<void ()> EventFunc;

struct Event
{
	Event(const EventFunc& f, int64_t delay, bool repeat)
	{
		m_repeat = repeat;
		m_f = f;
		m_waitTime = std::chrono::system_clock::now() + std::chrono::milliseconds(delay);
	}

	void setID(uint32_t i) { m_id = i; }
	uint32_t getID() const { return m_id; }

	bool isRepeated() const { return m_repeat; }
	bool expired() const { return std::chrono::system_clock::now() >= m_waitTime; } 
	void operator()() { m_f(); }

private:
	uint32_t m_id;
	bool m_repeat;

	EventFunc m_f;
	std::chrono::time_point<std::chrono::system_clock> m_waitTime;
};
typedef std::shared_ptr<Event> EventPtr;

class Scheduler
{
public:
	Scheduler();
	~Scheduler();

	uint32_t scheduleEvent(const EventFunc& fun, int64_t delay, bool repeated = false);
	void stopEvent(uint32_t eventId);
	void stop();

protected:
	void schedulerThread();

private:
	bool m_stopped;
	uint32_t m_lastId;

	std::list<EventPtr> m_eventList;
	std::vector<uint32_t> m_eventIds;

	std::thread m_thread;
	std::mutex m_mutex;
	std::condition_variable m_condition;
};

extern Scheduler g_sched;

#endif


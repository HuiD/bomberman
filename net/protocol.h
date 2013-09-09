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
#ifndef __PROTOCOL_H
#define __PROTOCOL_H

#include "decl.h"

#include "inputmessage.h"
#include "outputmessage.h"

#include "connection.h"

class Protocol
{
public:
	Protocol();
	virtual ~Protocol();

	void connect(const std::string& host, const std::string& port);
	void disconnect();

	ConnectionPtr getConnection() const { return m_conn; }
	void setConnection(const ConnectionPtr& c)
	{
		m_conn = c;
		if (c)
			onConnect();
	}

	virtual void send(const OutputMessage& out);
	virtual void recv() =0;

	void readBytes(size_t size, const std::function<void(uint8_t, InputMessage)>& cb);

protected:
	virtual void onConnect() = 0;
	virtual void onRead(uint8_t byte, InputMessage in);

private:
	ConnectionPtr m_conn;
};

#endif


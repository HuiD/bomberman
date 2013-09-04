#ifndef __CONNECTION_H
#define __CONNECTION_H

#include "decl.h"

#include <list>

class Connection
	: public std::enable_shared_from_this<Connection>
{
	typedef std::function<void(uint8_t *, uint16_t)> ReadCallback;
public:
	Connection();
	~Connection();

	void connect(const std::string& host, const std::string& port,
			const std::function<void()>& cb);
	void close();
	bool isConnected() const { return m_socket.is_open(); }

	void write(uint8_t *data, uint16_t bytes);
	void read(uint16_t bytes, const ReadCallback& rc);

	std::string getIP();

protected:
	void internalWrite(const boost::system::error_code& e);
	void handleConnect(const boost::system::error_code& e);
	void handleResolve(const boost::system::error_code& e,
				asio::ip::basic_resolver<asio::ip::tcp>::iterator endpointIterator);
	void handleWrite(const boost::system::error_code& e, size_t bytes,
			 std::shared_ptr<asio::streambuf> m_outputStream);
	void handleRead(const boost::system::error_code& e, size_t readSize);
	void handleError(const boost::system::error_code& e);
private:
	std::function<void()> m_connectCallback;
	ReadCallback m_readCallback;

	asio::deadline_timer m_delayedWriteTimer;
	asio::ip::tcp::socket m_socket;
	asio::ip::tcp::resolver m_resolver;

	static std::list<std::shared_ptr<asio::streambuf>> m_outputStreams;
	std::shared_ptr<asio::streambuf> m_outputStream;
	asio::streambuf m_inputStream;

	friend class Listener;
};

#endif


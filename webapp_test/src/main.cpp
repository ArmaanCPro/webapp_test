#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <iostream>

using boost::asio::ip::tcp;

class Session
{
public:
    Session(boost::asio::io_service& io_service)
        :
        socket_(io_service)
    {}

    tcp::socket& socket() { return socket_; }

    void start()
    {
        socket_.async_read_some(boost::asio::buffer(data_, max_length),
            boost::bind(&Session::handle_read, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred)
        );
    }
private:
    void handle_read(const boost::system::error_code& error, size_t bytes_transferred)
    {
        if (!error)
        {
            // for debug, write the data to stdout
            std::cout.write(data_, bytes_transferred);
            std::cout.flush();

            // echo back
            boost::asio::async_write(socket_, boost::asio::buffer(data_, bytes_transferred),
                boost::bind(&Session::handle_write, this, boost::asio::placeholders::error));
        }
        else
            delete this;
    }

    void handle_write(const boost::system::error_code& error)
    {
        if (!error)
        {
            socket_.async_read_some(boost::asio::buffer(data_, max_length),
                boost::bind(&Session::handle_read, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
        }
        else
            delete this;
    }


    tcp::socket socket_;
    enum { max_length = 1024 };
    char data_[1024];
};

class Server
{
public:
    Server(boost::asio::io_service& io_service, short port)
        :
        io_service_(io_service),
        acceptor_(io_service, tcp::endpoint(tcp::v4(), port))
    {
        start_accept();
    }

private:
    void start_accept()
    {
        Session* new_session = new Session(io_service_);
        acceptor_.async_accept(new_session->socket(),
            boost::bind(&Server::handle_accept, this, new_session, boost::asio::placeholders::error));
    }

    void handle_accept(Session* new_session, const boost::system::error_code& error)
    {
        if (!error)
            new_session->start();
        else
            delete new_session;

        start_accept();
    }

    boost::asio::io_service& io_service_;
    tcp::acceptor acceptor_;
};

int main(int argc, char* argv[])
{
    try
    {
        if (argc != 2)
        {
            std::cerr << "Usage: async_tcp_echo_server <port>\n";
            return 1;
        }

        boost::asio::io_service io_service;

        using namespace std;
        Server s(io_service, atoi(argv[1]));

        io_service.run();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
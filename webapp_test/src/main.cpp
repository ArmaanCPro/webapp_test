#include <boost/asio.hpp>
#include <iostream>

using boost::asio::ip::tcp;

std::string make_http_response(const std::string& content)
{
    return "HTTP/1.1 200 OK\r\n"
           "Content-Length: " + std::to_string(content.length()) + "\r\n"
           "Content-Type: text/html\r\n"
           "Access-Control-Allow-Origin: *\r\n"
           "\r\n" +
           content;
}

void handle_request(tcp::socket& socket)
{
    boost::system::error_code ec;
    boost::asio::streambuf buffer;

    boost::asio::read_until(socket, buffer, "\r\n\r\n", ec);
    if (!ec) {
        std::istream request_stream(&buffer);
        std::string request_line;
        std::getline(request_stream, request_line);

        std::string response_content = "<html><body><p>Hello, mom!</p></body></html>";
        std::string response = make_http_response(response_content);

        boost::asio::write(socket, boost::asio::buffer(response), ec);
        socket.shutdown(tcp::socket::shutdown_both, ec);
        socket.close(ec);
    }
}

int main()
{
    try
    {
        boost::asio::io_context io_context;
        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 8080));

        const std::string address = "http://localhost:8080/";
        std::cout << "Server is running on " << address << std::endl;
        std::cout << "Note, going to the web address (" << address << ") will only display the web server's output" << std::endl;
        std::cout << "Try opening the html file in your browser while the c++ app is running!";

        while (true) {
            tcp::socket socket(io_context);
            acceptor.accept(socket);
            handle_request(socket);
        }
    }
    catch (std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
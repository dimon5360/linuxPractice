/* user libs  ------------------------------------------------------ */
#include "main.h"
#include <iostream>

#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/format.hpp>
#include <boost/chrono.hpp>

using namespace boost::asio;

typedef boost::shared_ptr<ip::tcp::socket> socket_ptr;

/* Print application information */
static void PrintAppInfo(void);
/* Handler for client session */
static void client_session(socket_ptr sock);

int main() {

    PrintAppInfo();
    
    io_service service;
    ip::tcp::endpoint ep(ip::address::from_string("127.0.0.1"), 2001);

    ip::tcp::acceptor acc(service, ep);

    // wait a client
    while(true) {
        // create new socket obj and put in reference
        socket_ptr sock(new ip::tcp::socket(service));
        // accept a connection for new client
        acc.accept(*sock);
        // create single thread for new client connection
        boost::thread(boost::bind(client_session, sock));
        std::cout << "Client accepted\n";
    }
    return 0;
}

static void client_session(socket_ptr sock) {
    int timeout = 5;
    while(true) {
        char data[512];
        size_t len = sock->read_some(buffer(data));
        if (len > 0) {
            write(*sock, buffer("ok", 2));
        }
        boost::this_thread::sleep_for(boost::chrono::seconds(timeout));
    }
}

static void PrintAppInfo(void) {
    std::cout << "Application version " << 
    boost::format("%u.%u.%u") % MAJOR % MINOR % BUILD << std::endl;
}
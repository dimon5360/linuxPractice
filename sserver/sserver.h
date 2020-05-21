/* std libs */
#include <unistd.h>
#include <stdint.h>
#include <string>
#include <stdlib.h> 
#include <ostream>
#include "stdio.h"
/* tcp socket lib */
#include <sys/socket.h>
/* net lib */
#include <netinet/in.h> 

/* max threads number */
#define THREADS_NUMBER 10
#define CLIENTS_NUMBER THREADS_NUMBER

/* TCP socket server class */
class STcpServer {

private:
    uint32_t tcp_port;
    std::string ip;

public:
    /* server class constructor */
    STcpServer(std::string ip_address, uint16_t ip_port);
    /* server class destructor */
    ~STcpServer();

private:
    /* function creates socket server */
    void CreateSocketServer(void);
    /* main function for handle of connection */
    // void *handle(void* id);
};
#include <sserver.h>

#include <iostream>
/* smart pointers */
#include <memory>
/* multythread */
#include <pthread.h>

static void *handle(void* id);

STcpServer::STcpServer(std::string ip_address, uint16_t ip_port) {
    this->tcp_port = ip_port;
    this->ip = ip_address;
    CreateSocketServer();
}

STcpServer::~STcpServer() {
}

void STcpServer::CreateSocketServer(void) {
    int server_fd, valread; 
    struct sockaddr_in address; 
    int opt = 1; 
    int addrlen = sizeof(address); 
    char buffer[1024] = {0}; 
    char *hello = (char*)"Hello from server"; 
       
    // Creating socket file descriptor 
    if ((server_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_IP)) == -1) { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } else {
        perror("scoket created\n");
    }

    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( tcp_port ); 
       
    // Forcefully attaching socket to the port tcp_port 
    if (bind(server_fd, (struct sockaddr *)&address,  
                                 sizeof(address))<0) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 

    if (listen(server_fd, 3) < 0) 
    { 
        perror("listen"); 
        exit(EXIT_FAILURE); 
    } 

    pthread_t threads[THREADS_NUMBER];
    int32_t sock_clients[CLIENTS_NUMBER], clientIndex = 0, threadId = 0;

    while(1) {

        if ((sock_clients[clientIndex] = accept(server_fd, (struct sockaddr *)&address,  
                        (socklen_t*)&addrlen))<0) 
        { 
            perror("accept"); 
            exit(EXIT_FAILURE); 
        } 

        valread = read(sock_clients[clientIndex] , buffer, 1024); 
        printf("%s\n",buffer ); 

        if(send(sock_clients[clientIndex] , hello , sizeof(hello) , 0) < 0) {
            printf("Hello message has not sent to client\n");
            exit(EXIT_FAILURE); 
        } else {
            printf("Hello message sent\n"); 
            int rc = pthread_create(&threads[threadId], NULL, handle, (void*)threadId);
            if(rc != 0) {
                printf("Thread nahs not created");
                exit(-1);
            } else {
                threadId++;
                clientIndex++;
            }
        }
    }
    pthread_exit(NULL);
}

static void *handle(void* threadId) {

    // printf("Thread id %d", threadId);
    // while(1) {

    // }
}

/* code template */
static void CreateThreads(void) {

    // pthread_t threads[THREADS_NUMBER];
    // int id;

    // for( id = 0; id < THREADS_NUMBER; id++) {
    //     int rc = pthread_create(&threads[id], NULL, CreateTcpServer, (void*)id);
    //     if(rc != 0) {
    //         cout << "unable to create thread/n";
    //         exit(-1);
    //     }
    // }
    // pthread_exit(NULL);
}
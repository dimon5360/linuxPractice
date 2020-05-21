/* user libs  ------------------------------------------------------ */
#include "sserver.h"
#include "main.h"

/* useful libs  ---------------------------------------------------- */
/* standard data types */
#include <stdint.h>
/* io lib */
#include <iostream>
/* smart pointers */
#include <memory>
/* multythread */
#include <pthread.h>

#define THREADS_NUMBER 10

using namespace std;

void *CreateTcpServer(void* threadid);
void CreateThreads(void);

int main() {

    STcpServer server = STcpServer("192.168.1.69", 4059);
    // CreateThreads();

    return 0;
}

void *CreateTcpServer(void* threadid) {

    // shared_ptr<STcpServer> serv = 
    //     make_shared<STcpServer>("192.168.1.69", 4059);
    cout << "Welcome\n";
}

void CreateThreads(void) {

    pthread_t threads[THREADS_NUMBER];
    int id;

    for( id = 0; id < THREADS_NUMBER; id++) {
        int rc = pthread_create(&threads[id], NULL, CreateTcpServer, (void*)id);
        if(rc != 0) {
            cout << "unable to create thread/n";
            exit(-1);
        }
    }
    pthread_exit(NULL);
}
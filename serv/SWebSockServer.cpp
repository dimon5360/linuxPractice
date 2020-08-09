/**
 *  @file SWebSockServer.cpp
 *  @brief  Definitions of Web socket server Class
 *
 *  @author Kalmykov Dmitry
 *
 *  @version 0.1
 *  @date 09.08.2020
 */

/* local headers */
#include "main.h"
#include "config.h"
#include "SWebSockServer.hpp"

/**
 * @brief SWebSockServer class constructor
 */
SWebSockServer::SWebSockServer() {
    std::cout << "Object of SWebSockServer class created." << std::endl;
        
}

/**
 * @brief SWebSockServer class destructor
 */
SWebSockServer::~SWebSockServer() {
    std::cout << "Object of SWebSockServer class removed." << std::endl;
    
}


/***
 *  @brief  Push the output data to queue
 */
void SWebSockServer::pushOutQueue(const std::string & resp) {
    /* lock mutex for pushing data */
    try {
        boost::lock_guard<boost::mutex> lock(_mtx);
    } catch(std::exception ex) {
        std::cout << ex.what() << std::endl;
    }
    outQueueResponse.push(resp);
}

/***
 *  @brief  Push the input data to queue
 */
void SWebSockServer::pushInQueue(const std::string & req) {    
    /* lock mutex for pushing data */
    try {
        boost::lock_guard<boost::mutex> lock(_mtx);
    } catch(std::exception ex) {
        std::cout << ex.what() << std::endl;
    }
    inQueueRequest.push(req);
}

/***
 *  @brief  Get output data from queue
 */
std::string SWebSockServer::pullOutQueue(void) {

    /* lock mutex for pushing data */
    try {
        boost::lock_guard<boost::mutex> lock(_mtx);
    } catch(std::exception ex) {
        std::cout << ex.what() << std::endl;
    }
    std::string resp;

    if(!isOutQueueEmpty()) {
        resp = outQueueResponse.front();
        outQueueResponse.pop();
    }
    return resp;
}

/***
 *  @brief  Get input data from queue
 */
std::string SWebSockServer::pullInQueue(void) {

    /* lock mutex for pushing data */
    try {
        boost::lock_guard<boost::mutex> lock(_mtx);
    } catch(std::exception ex) {
        std::cout << ex.what() << std::endl;
    }

    std::string req;

    if(!isInQueueEmpty()) {
        req = inQueueRequest.front();
        inQueueRequest.pop();
    }
    return req;
}

/*** 
 *  @brief  Check that input data queue is empty 
 */
bool SWebSockServer::isInQueueEmpty(void) {
    return inQueueRequest.empty();
}

/*** 
 *  @brief  Check that output data queue is empty 
 */
bool SWebSockServer::isOutQueueEmpty(void) {
    return outQueueResponse.empty();
}

/*********************
 * @file DDataprocessor.hpp
 * @brief Derived from SService class for data processing.
 *
 *  @author Kalmykov Dmitry
 *
 *  @version 0.1
 *  @date 30.05.2020
 */

/* local headers */
#include "main.h"
#include "config.h"
#include "DDataProcessor.hpp"

/* boost c++ lib heades */
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>

/**
 * @brief SServer class constructor
 */
DDataProcessor::DDataProcessor() {
#if DATA_PROC_CALLED_FUNCTION
    std::cout << __func__ << "()" << std::endl;
#endif /* DATA_PROC_CALLED_FUNCTION */

    boost::thread(boost::bind(&DDataProcessor::handle, this));
    // std::thread t(&DDataProcessor::handle, this);
    // t.detach();
}

/**
 * @brief SServer class destructor
 */
DDataProcessor::~DDataProcessor() {
#if DATA_PROC_CALLED_FUNCTION
    std::cout << __func__ << "()" << std::endl;
#endif /* DATA_PROC_CALLED_FUNCTION */
    
}

/* Push the output data to queue */
void DDataProcessor::pushOutQueue(const std::string & resp) {
#if DATA_PROC_CALLED_FUNCTION
    std::cout << __func__ << "()" << std::endl;
#endif /* DATA_PROC_CALLED_FUNCTION */

#if DATA_PROC_DEBUG_INFO
    std::cout << "Response to queue: " << resp << std::endl;  
#endif /* DATA_PROC_DEBUG_INFO */

    /* lock mutex for pushing data */
    try {
        boost::lock_guard<boost::mutex> lock(_mtx);
    } catch(std::exception ex) {
        std::cout << ex.what() << std::endl;
    }
    outQueueResponse.push(resp);
}

/* Push the input data to queue */
void DDataProcessor::pushInQueue(const std::string & req) {
#if DATA_PROC_CALLED_FUNCTION
    std::cout << __func__ << "()" << std::endl;
#endif /* DATA_PROC_CALLED_FUNCTION */

#if DATA_PROC_DEBUG_INFO
    std::cout << "Request to queue: " << req << std::endl;  
#endif /* DATA_PROC_DEBUG_INFO */
    
    /* lock mutex for pushing data */
    try {
        boost::lock_guard<boost::mutex> lock(_mtx);
    } catch(std::exception ex) {
        std::cout << ex.what() << std::endl;
    }
    inQueueRequest.push(req);
}

/* Get output data from queue */
std::string DDataProcessor::pullOutQueue(void) {
#if DATA_PROC_CALLED_FUNCTION
    std::cout << __func__ << "()" << std::endl;
#endif /* DATA_PROC_CALLED_FUNCTION */

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

#if DATA_PROC_DEBUG_INFO
        std::cout << "Response from queue: " << resp << std::endl; 
#endif /* DATA_PROC_DEBUG_INFO */
    }
    return resp;
}

/* Get input data from queue */
std::string DDataProcessor::pullInQueue(void) {
#if DATA_PROC_CALLED_FUNCTION
    std::cout << __func__ << "()" << std::endl;
#endif /* DATA_PROC_CALLED_FUNCTION */

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

#if DATA_PROC_DEBUG_INFO
        std::cout << "Request from queue: " << req << std::endl; 
#endif /* DATA_PROC_DEBUG_INFO */
    }
    return req;
}

/* Check that input data queue is empty */
bool DDataProcessor::isInQueueEmpty(void) {
#if DATA_PROC_CALLED_FUNCTION
    std::cout << __func__ << "()" << std::endl;
#endif /* DATA_PROC_CALLED_FUNCTION */

    return inQueueRequest.empty();
}

/* Check that output data queue is empty */
bool DDataProcessor::isOutQueueEmpty(void) {
#if DATA_PROC_CALLED_FUNCTION
    std::cout << __func__ << "()" << std::endl;
#endif /* DATA_PROC_CALLED_FUNCTION */

    return outQueueResponse.empty();
}

void DDataProcessor::handle() {
#if DATA_PROC_CALLED_FUNCTION
    std::cout << __func__ << "()" << std::endl;
#endif /* DATA_PROC_CALLED_FUNCTION */

    while(true) {
        if(!isInQueueEmpty()) {

#if DATA_PROC_DEBUG_INFO
            std::cout << "Queue has a request." << std::endl;
#endif /* DATA_PROC_DEBUG_INFO */

            std::string req = pullInQueue();   
            RevString(req);         
            pushOutQueue(req);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(THREAD_TIMEOUT));
    }
}

void DDataProcessor::RevString(std::string &origString) {
#if !DATA_PROC_CALLED_FUNCTION
    std::cout << __func__ << "()" << std::endl;
#endif /* DATA_PROC_CALLED_FUNCTION */
    std::string revString;

    size_t size_ = origString.length()-1;
    for(int i = size_; i >= 0; --i) {
        revString += origString[i-1];
    }
    origString = revString;    
}
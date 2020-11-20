/*********************
 * @file DDataprocessor.hpp
 * @brief Derived from SService class for data processing.
 *
 *  @author Kalmykov Dmitry
 *
 *  @version 0.1
 *  @date 20.11.2020
 */

/* local headers */
#include "main.h"
#include "config.h"
#include "DDataProcessor.hpp"

/* boost c++ lib heades */
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>

/* Static private funtions declarations ------------------------------------ */

/* Reverse string for test output of data */
static void RevString(std::string &&origString);


/* Class methods implementaions -------------------------------------------- */

/******************************************************************************
 * @brief SServer class constructor
 */
DDataProcessor::DDataProcessor() {
    /* start DataProcessor handler */
    std::thread(std::bind(&DDataProcessor::handle, this)).detach();
}

/******************************************************************************
 * @brief SServer class destructor
 */
DDataProcessor::~DDataProcessor() {
}

/******************************************************************************
 *  @brief  Main data processor class handler
 */
void DDataProcessor::handle() {
    while(true) {

        if(std::string req = pullInQueue(); !req.empty()) { 

#if DATA_PROCESSOR_HANDLER_LOG
            std::cout << "Input request for Data Processor: " << req << std::endl;
#endif /* DATA_PROCESSOR_HANDLER_LOG */

            // TODO: replace this function to HTTP request handler
            RevString(std::move(req));         
            pushOutQueue(std::move(req));
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(THREAD_TIMEOUT));
    }
}

/******************************************************************************
 *  @brief  Push the output data to OUT queue for connection handler <CClient>
 *  @param[in] Reference to string with output HTTP response
 */
void DDataProcessor::pushOutQueue(const std::string && resp) {
    
    /* lock mutex for pushing data */
    try {
        boost::lock_guard<boost::mutex> lock(_mtx);

#if DATA_PROCESSOR_HANDLER_LOG
            std::cout << "Out response for Data Processor: " << resp << std::endl;
#endif /* DATA_PROCESSOR_HANDLER_LOG */

        outQueueResponse.push(std::move(resp));
    } catch(std::exception ex) {
        std::cout << ex.what() << std::endl;
    }
}

/******************************************************************************
 *  @brief  Push the input data to IN queue for HTTP handler
 *  @param[in] Reference to string with input HTTP request
 */
void DDataProcessor::pushInQueue(const std::string && req) {

    /* lock mutex for pushing data */
    try {
        boost::lock_guard<boost::mutex> lock(_mtx);
        inQueueRequest.push(std::move(req));
    } catch(std::exception ex) {
        std::cout << ex.what() << std::endl;
    }
}

/******************************************************************************
 *  @brief  Pull the output data from OUT queue for connection handler
 *  @param  None
 *  @return If no exception - String with HTTP handler response
 */
std::string DDataProcessor::pullOutQueue(void) {

    std::string resp;
    /* lock mutex for pushing data */
    try {
        boost::lock_guard<boost::mutex> lock(_mtx);

    if(!isOutQueueEmpty()) {
        resp = outQueueResponse.front();
        outQueueResponse.pop();
    }
    } catch(std::exception ex) {
        std::cout << ex.what() << std::endl;
    }
    return resp;
}


/******************************************************************************
 *  @brief  Pull the input data from IN queue for HTTP handler
 *  @param  None
 *  @return If no exception - String with HTTP handler request
 */
std::string DDataProcessor::pullInQueue(void) {

    std::string req;
    /* lock mutex for pushing data */
    try {
        boost::lock_guard<boost::mutex> lock(_mtx);

        if(!isInQueueEmpty()) {
            req = inQueueRequest.front();
            inQueueRequest.pop();
        }
    } catch(std::exception ex) {
        std::cout << ex.what() << std::endl;
    }

    return req;
}

/*** 
 *  @brief  Check that input data queue is empty 
 */
bool DDataProcessor::isInQueueEmpty(void) {
    return inQueueRequest.empty();
}

/*** 
 *  @brief  Check that output data queue is empty 
 */
bool DDataProcessor::isOutQueueEmpty(void) {
    return outQueueResponse.empty();
}

/* Static private functions implementations -------------------------------- */

/*** 
 *  @brief  Reverse string for test output of data
 */
static void RevString(std::string &&origString) {
    std::reverse(origString.begin(), origString.end());
}
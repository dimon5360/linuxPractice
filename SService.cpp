/**
 *  @file SService.cpp
 *  @brief Parent class for service (SServer, DataProcess etc.) realization
 *
 *  @author Kalmykov Dmitry
 *
 *  @version 0.1
 *  @date 30.05.2020
 */

/* local headers */
#include "config.h"
#include "SService.hpp"
#include "main.h"


/* interfaces for work with queue ------------------------------------------ */
/***
 * @brief Push the output data to queue 
 */
void SService::pushOutQueue(std::string response) {
    outServiceQueue.push(response);
}

/***
 * @brief Push the input data to queue 
 */
void SService::pushInQueue(std::string request) {
    inServiceQueue.push(request);
}

/***
 * @brief Get output data from queue 
 */
std::string SService::pullOutQueue(void) {
    std::string response;
    response = outServiceQueue.front();
    outServiceQueue.pop();
    return response;
}

/***
 * @brief Get input data from queue 
 */
std::string SService::pullInQueue(void) {
    std::string request;
    request = inServiceQueue.front();
    inServiceQueue.pop();
    return request;
}

/***
 * @brief Check that input data queue is empty
 */
bool SService::isInQueueEmpty(void) {
    return inServiceQueue.empty();
}
/***
 * @brief Check that output data queue is empty
 */
bool SService::isOutQueueEmpty(void) {
    return outServiceQueue.empty();
}



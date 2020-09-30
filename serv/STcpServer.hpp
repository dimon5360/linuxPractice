/*********************
 * @file STcpServer.hpp
 * @brief Parent class header for other classes based on it.
 * 
 * @author kalmykov Dmitry
 * 
 * @version 0.0.1 
 * @date 01.06.2020
 */

#include "SService.hpp"

class STcpServer {


public:
    STcpServer();
    ~STcpServer();

    /* interfaces for work with queue -------------------------------------- */
    /* Push the output data to queue */
    void pushOutQueue(std::string);
    /* Push the input data to queue */
    void pushInQueue(std::string);
    /* Get output data from queue */
    std::string pullOutQueue(void);
    /* Get input data from queue */
    std::string pullInQueue(void);
    /* Check that input data queue is empty */
    bool isInQueueEmpty(void);
    /* Check that output data queue is empty */
    bool isOutQueueEmpty(void);
};
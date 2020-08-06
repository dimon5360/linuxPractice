/******************************************************************************
 * @file    PgConnection.hpp
 * @brief   Separate class declarations to process postgres connection.
 * 
 * @author  kalmykov Dmitry
 * 
 * @version 0.0.1 
 * @date    05.08.2020
 *****************************************************************************/

#pragma once

/* C++ std lib headers */
#include <string> 

class PgConnection {
private:

    bool connectionStatus = false;

public:

    PgConnection();
    ~PgConnection();

    /* postgrees connection process interfaces ----------------------------- */
    void PgSetConnection(std::string, 
                         std::string,
                         std::string,
                         std::string,
                         std::string);
    void PgResetConnection();
    bool GetConnectionStatus();
};
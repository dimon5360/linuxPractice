/******************************************************************************
 * @file    PgRequest.cpp
 * @brief   Separate class definitions to prepare postgres requests.
 * 
 * @author  kalmykov Dmitry
 * 
 * @version 0.0.1 
 * @date    06.08.2020
 *****************************************************************************/

/* local headers */
#include "PgRequest.hpp"

/* C++ std lib headers */
#include <iostream>

/***
 *  @brief  PgRequest class constructor
 */
PgRequest::PgRequest() {
}

/***
 *  @brief  PgRequest class destructor
 */
PgRequest::~PgRequest() {
    /* ... */
}

/***
 *  @brief  Print PgRequest object fields
 */
void PgRequest::PgPrintReqInfo() {
    using namespace std;
    cout << "Request data:";
    cout << "\n\tSELECT params\n";
    for(auto &v : select_params) {
        cout << v << " ";
    }
    cout << "\n\FROM params\n";
    for(auto &v : from_params) {
        cout << v << " ";
    }
    cout << "\n\WHERE params\n";
    for(auto &v : where_params) {
        cout << v << " ";
    }
}
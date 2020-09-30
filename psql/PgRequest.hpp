/******************************************************************************
 * @file    PgRequest.hpp
 * @brief   Separate class declarations to prepare postgres requests.
 * 
 * @author  kalmykov Dmitry
 * 
 * @version 0.0.1 
 * @date    06.08.2020
 *****************************************************************************/

#pragma once

/* C++ std lib headers */
#include <string_view>
#include <string>
#include <vector>
#include <utility>


class PgRequest {
private:
    std::vector<std::string> select_params;
    std::vector<std::string> from_params;
    std::vector<std::string> where_params;

public:
    /* PgRequest class constructor */
    PgRequest();
    /* copy constructor */
    PgRequest(const PgRequest & req) :
         select_params(req.select_params),
         from_params(req.from_params),
         where_params(req.where_params) 
    {   };
    /* move constructor */
    PgRequest(PgRequest && req) :
         select_params(std::move(req.select_params)),
         from_params(std::move(req.from_params)),
         where_params(std::move(req.where_params)) 
    {   };

    /* PgRequest class destructor */
    ~PgRequest();
    /* Print PgRequest object fields */
    void PgPrintReqInfo() noexcept;
};

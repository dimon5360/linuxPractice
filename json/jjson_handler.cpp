/*********************
 * @file jjson_parser.cpp
 * @brief Class JSON parser definition
 * 
 * @author kalmykov Dmitry
 * 
 * @version 0.0.1 
 * @date 18.11.2020
 */

/* user classes headers */
#include "jjson_handler.hpp"
#include "DDataProcessor.hpp"

/* C++ boost lib headers */
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

using cliReq = struct ClientRequest  {
    std::string request_type;
    std::string request_data; 
};


/****************************************************
 *  @brief  Json handler class constructor
 */
JJsonHandler::JJsonHandler() {
    std::cout << "JJsonHandler class created." << std::endl;
    
    std::string_view auth_json_data 
        { "{ \"email\" : \"test@test.com\", \"password\" : \"admin1234\" }" };

    std::stringstream json_req;
    json_req << "POST https://api.test.org/api/auth/login\r\n"
             << "Content-Length: " << auth_json_data.length() << "\r\n"
             << "Content-Type: application/json\r\n"
             << "\r\n"
             << auth_json_data;
    
    PrintJson(auth_json_data);
}

#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/stream.hpp>

#include <string_view>
/****************************************************
 *  @brief  Util to print Json strings
 */
void JJsonHandler::PrintJson(const std::string_view ss) {
    namespace pt = boost::property_tree;

    try {

        pt::ptree tree;

        boost::iostreams::array_source as(ss.data(), ss.size());
        boost::iostreams::stream<boost::iostreams::array_source> is(as);

        pt::read_json(is, tree);
        std::cout << "email : \"" << tree.get<std::string>("email") << "\"\n";
        std::cout << "password : \"" << tree.get<std::string>("password") << "\"\n";
        
        std::cout << tree.data() << std::endl;
    }
    catch(std::exception const &e) {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }    
}
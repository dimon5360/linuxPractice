/*********************
 * @file CClient.cpp
 * @brief Class CClient methods implementations
 * 
 * @author kalmykov Dmitry
 * 
 * @version 0.0.1 
 * @date 12.06.2020
 */

#include "CClient.hpp"


#include "iostream"

/* C++ boost lib headers */



using tcp = boost::asio::ip::tcp; 

/******************************************************
 *  @brief      Client class constructor
 * 
 *  @param[in]  clientId Reference to got ID from connection handler
 *  @param[in]  ws Client websocket reference (through std::move) 
 */
CClient::CClient(const uint32_t &clientId, tcp::socket&&ws):
    id(clientId),
    ws(std::move(ws)) 
{

    WaitConnection();    
}

/*************************************************************
 *  @brief      Processor for input JSON request from client
 * 
 *  @param[in]  req Input JSON request in string
 *  @return     Client request structure (alias cliReq)
 */
static const std::string &PrepareResponse() noexcept  {

    
}

/*************************************************************
 *  @brief      Processor for input JSON request from client
 * 
 *  @param[in]  req Input JSON request in string
 *  @return     Client request structure (alias cliReq)
 */
static const std::string &ProcessRequest(std::string && req) noexcept  {

    
}

void CClient::WaitConnection() {

    try
    {
        // Accept the websocket handshake
        ws.accept();
        std::cout << "New Client with ID #" << this->id << " accepted\n";

        // This buffer will hold the incoming message
        boost::beast::multi_buffer buffer;

        for(;;)
        {
            // Read a message
            ws.read(buffer);

            if(ws.got_text()) {
                
                // Echo the message back
                ws.text(ws.got_text());
                std::string str = buffers_to_string(buffer.data()); 
                std::cout << "Client msg: \"" << str << "\"\n";

                // TODO: prepare the response to client with its ID
                std::transform(str.begin(), str.end(), str.begin(), ::tolower);    





                ws.write(boost::asio::buffer(str));
            }
        }
    }
    catch(boost::system::system_error const& se)
    {
        // This indicates that the session was closed
        if(se.code() != websocket::error::closed) {
            std::cerr << "Error 1: " << se.code().message() << std::endl;
            this->~CClient();
        }
    }
    catch(std::exception const& e)
    {
        std::cerr << "Error 2: " << e.what() << std::endl;
    }
}

/******************************************************************************
 * @file    PgConnection.hpp
 * @brief   Separate class definitions to process postgres connection.
 * 
 * @author  kalmykov Dmitry
 * 
 * @version 0.0.1 
 * @date    05.08.2020
 *****************************************************************************/

/* local headers */
#include "PgConnection.hpp"

/* external lib for postgres database */
#include <postgresql/libpq-fe.h>

/* C++ std lib headers */
#include <sstream> 
#include <iostream>

static PGconn * conn;

PgConnection::PgConnection() {
    PgSetConnection("users_db", 
                    "localhost",
                    "5432",
                    "admin",
                    "admin1234");
}

PgConnection::~PgConnection() {
    PgResetConnection();
}

/***
 *  @brief  Set connection to user postgres db
 */
void PgConnection::PgSetConnection(std::string db_name, 
                                   std::string host,
                                   std::string port,
                                   std::string username,
                                   std::string pass) 
{
    if(!connectionStatus)  {
        using namespace std;
        stringstream req;
        req << "dbname=" << db_name << " host=" << host <<
            " port=" << port << " user=" << username << " password=" << pass;

        conn = PQconnectdb(req.str().c_str()); 

        if(PQstatus(conn) == CONNECTION_OK) {
            connectionStatus = true; 
            cout << "Connection had been set." << endl;
        }
        else {
            cout << "Connection status is " << 
            string(PQerrorMessage(conn)) << endl;
        }
    }
}

/***
 *  @brief  Reset connection to user postgres db
 */
void PgConnection::PgResetConnection() {
        using namespace std;
    if(connectionStatus) {
        PQfinish(conn);
        cout << "Connection had been reset." << endl;
    }
}

/***
 *  @brief  Reset connection to user postgres db
 */
bool PgConnection::GetConnectionStatus() {
    return connectionStatus;
}
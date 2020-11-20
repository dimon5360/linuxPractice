/**
 * @file config.h
 * @brief Preprocessor settings
 *
 * @author Kalmykov Dmitry
 *
 * @version 0.1
 * @date 08.04.2020
 */

#pragma once


/* unit testing ------------------------------------------------------------ */
#define UNIT_TESTS_ENABLE               1

#if UNIT_TESTS_ENABLE
#define UNIT_TEST_DEBUG_INFO            1
#define UNIT_TEST_CALLED_FUNCTION       1

/* unit tests */
#define UNIT_TEST_DATA_PROCESSOR_QUEUE  0
#define UNIT_TEST_DATA_BASE_QUEUE       0
#define UNIT_TEST_DATA_BASE_CONNECTION  0
#define UNIT_TEST_WEBSOCKET_SERVER      1
#define UNIT_TEST_JSON_HANDLER          1


#endif /* UNIT_TESTS_ENABLE */

/* logger items ------------------------------------------------------------ */
#define TCP_SERVER_CALLED_FUNCTION      0
#define WEB_SOCK_SERVER_CALLED_FUNCTION 0
#define DATA_BASE_CALLED_FUNCTION       0
#define DATA_PROC_CALLED_FUNCTION       0

/* debug data processor logger --------------------------------------------- */
#define DATA_PROC_DEBUG_INFO            1
#define DATA_PROCESSOR_HANDLER_LOG      1

/* debug data base processor logger ---------------------------------------- */
#define DATA_BASE_DEBUG_INFO            1

/* config server service --------------------------------------------------- */
/* server implementation (TCP or Web socket) */
#define USE_WEB_SOCKET_SERVER           1
#if USE_WEB_SOCKET_SERVER
#define USE_TCP_SOCKET_SERVER           0
#else 
#define USE_TCP_SOCKET_SERVER           1

#endif /* USE_WEB_SOCKET_SERVER */
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

#endif /* UNIT_TESTS_ENABLE */

/* logger items ------------------------------------------------------------ */
#define TCP_SERVER_CALLED_FUNCTION      0
#define DATA_BASE_CALLED_FUNCTION       0
#define DATA_PROC_CALLED_FUNCTION       0

/* debug data processor logger --------------------------------------------- */
#define DATA_PROC_DEBUG_INFO            1

/* debug data base processor logger ---------------------------------------- */
#define DATA_BASE_DEBUG_INFO            1
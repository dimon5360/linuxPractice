
#ifndef MAIN_H
#define MAIN_H

/* C++ boost lib headers */ 
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/format.hpp>
#include <boost/chrono.hpp>
#include <boost/format.hpp>
// #include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/bind/bind.hpp>

/* application version v.0.0.8 from 08.07.2020 */
#define MAJOR           0
#define MINOR           0
#define BUILD           8

/* deafult thread timeout */
#define THREAD_TIMEOUT  5        // 1000 ms

#endif /* MAIN_H */
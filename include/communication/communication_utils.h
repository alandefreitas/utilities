//
// Created by Alan de Freitas on 27/09/16.
//

#ifndef WPP_COMMUNICATION_UTILS_H
#define WPP_COMMUNICATION_UTILS_H

// External
#include <boost/asio/io_service.hpp>
#include <boost/asio/steady_timer.hpp>

#include <boost/asio/write.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/ip/tcp.hpp>

#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/containers/string.hpp>
#include <boost/interprocess/sync/named_mutex.hpp>
#include <boost/interprocess/sync/named_condition.hpp>
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/interprocess_condition.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>

#include "server_http.hpp"
#include "client_http.hpp"

#ifdef HAVE_OPENSSL
#include "crypto.hpp"
#endif

// Internal

namespace utl {
    namespace asio = boost::asio;
    using namespace boost::asio::ip;
    namespace interprocess = boost::interprocess;
    typedef SimpleWeb::Server<SimpleWeb::HTTP> http_server;
    typedef SimpleWeb::Client<SimpleWeb::HTTP> http_client;

}

#endif //WPP_COMMUNICATION_UTILS_H

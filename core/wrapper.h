// -*- mode: c++ -*-

#ifndef _WRAPPER_H_
#define _WRAPPER_H_

#include "pipeline.h"

namespace pipeserv {

class Wrapper
{
protected:
    Connection* conn_;
    Pipeline&   pipeline_;
public:
    Wrapper(Connection* conn);
    virtual ~Wrapper() {}
protected:
    void disable_poll() { pipeline_.disable_poll(conn_); }
    void enable_poll() { pipeline_.enable_poll(conn_); }
};

class Request : public Wrapper
{
public:
    Request(Connection* conn);
    virtual ~Request();

    ssize_t read_data(byte* ptr, size_t sz);
};

class Response : public Wrapper
{
    size_t      buffer_size_;
    bool        inactive_;
public:
    Response(Connection* conn, size_t buffer_size = 4096);
    virtual ~Response();

    ssize_t write_data(const byte* ptr, size_t sz);
    ssize_t flush_data();
    bool    active() { return !inactive_; }
    void    close();
};

}

#endif /* _WRAPPER_H_ */

// -*- mode: c++ -*-

#ifndef _HTTP_STAGES_H_
#define _HTTP_STAGES_H_

#include "core/stages.h"
#include "http/interface.h"

namespace tube {

class HttpConnectionFactory : public ConnectionFactory
{
public:
    static int kDefaultTimeout;
    virtual Connection* create_connection(int fd);
    virtual void        destroy_connection(Connection* conn);
};

class HttpParserStage : public ParserStage
{
    Stage* handler_stage_;
public:
    HttpParserStage();
    virtual ~HttpParserStage();

    virtual void initialize();
protected:
    int process_task(Connection* conn);
};

class HttpHandlerStage : public Stage
{
public:
    static const int kMaxContinuesRequestNumber;

    HttpHandlerStage();
    virtual ~HttpHandlerStage();
protected:
    int process_task(Connection* conn);
};

}

#endif /* _HTTP_STAGES_H_ */

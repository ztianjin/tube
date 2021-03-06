// -*- mode: c++ -*-

#ifndef _HTTP_WRAPPER_H_
#define _HTTP_WRAPPER_H_

#include <string>

#include "http/connection.h"
#include "core/wrapper.h"

namespace tube {

class HttpRequest : public Request
{
protected:
    HttpRequestData request_;
public:
    HttpRequest(Connection* conn, const HttpRequestData& request);

    static std::string url_decode(std::string url);

    std::string path() const { return request_.path; }
    std::string uri() const { return request_.uri; }
    std::string query_string() const { return request_.query_string; }
    std::string fragment() const { return request_.fragment; }
    Buffer      chunk_buffer() const { return request_.chunk_buffer; }
    short       method() const { return request_.method; }
    std::string method_string() const;
    u64         content_length() const { return request_.content_length; }
    short       transfer_encoding() const { return request_.transfer_encoding; }
    short       version_major() const { return request_.version_major; }
    short       version_minor() const { return request_.version_minor; }
    bool        keep_alive() const { return request_.keep_alive; }

    void set_uri(std::string uri) { request_.uri = uri; }

    const HttpHeaderEnumerate& headers() const { return request_.headers; }
    HttpHeaderEnumerate& headers() { return request_.headers; }

    bool has_header(std::string key) const;
    std::vector<std::string> find_header_values(std::string key) const;
    std::string find_header_value(std::string key) const;
    const UrlRuleItem* url_rule_item() const { return request_.url_rule; }

    // used for C wrapper only
    const HttpRequestData& request_data_ref() const { return request_; }
};

struct HttpResponseStatus
{
    int         status_code;
    std::string reason;

    HttpResponseStatus(int code, const std::string& reason);

    static const HttpResponseStatus kHttpResponseContinue;
    static const HttpResponseStatus kHttpResponseSwitchingProtocols;
    static const HttpResponseStatus kHttpResponseOK;
    static const HttpResponseStatus kHttpResponseCreated;
    static const HttpResponseStatus kHttpResponseAccepted;
    static const HttpResponseStatus kHttpResponseNonAuthoritativeInformation;
    static const HttpResponseStatus kHttpResponseNoContent;
    static const HttpResponseStatus kHttpResponseResetContent;
    static const HttpResponseStatus kHttpResponsePartialContent;
    static const HttpResponseStatus kHttpResponseMultipleChoices;
    static const HttpResponseStatus kHttpResponseMovedPermanently;
    static const HttpResponseStatus kHttpResponseFound;
    static const HttpResponseStatus kHttpResponseSeeOther;
    static const HttpResponseStatus kHttpResponseNotModified;
    static const HttpResponseStatus kHttpResponseUseProxy;
    static const HttpResponseStatus kHttpResponseTemporaryRedirect;
    static const HttpResponseStatus kHttpResponseBadRequest;
    static const HttpResponseStatus kHttpResponseUnauthorized;
    static const HttpResponseStatus kHttpResponsePaymentRequired;
    static const HttpResponseStatus kHttpResponseForbidden;
    static const HttpResponseStatus kHttpResponseNotFound;
    static const HttpResponseStatus kHttpResponseMethodNotAllowed;
    static const HttpResponseStatus kHttpResponseNotAcceptable;
    static const HttpResponseStatus kHttpResponseProxyAuthenticationRequired;
    static const HttpResponseStatus kHttpResponseRequestTimeout;
    static const HttpResponseStatus kHttpResponseConflict;
    static const HttpResponseStatus kHttpResponseGone;
    static const HttpResponseStatus kHttpResponseLengthRequired;
    static const HttpResponseStatus kHttpResponsePreconditionFailed;
    static const HttpResponseStatus kHttpResponseRequestEntityTooLarge;
    static const HttpResponseStatus kHttpResponseRequestUriTooLarge;
    static const HttpResponseStatus kHttpResponseUnsupportedMediaType;
    static const HttpResponseStatus kHttpResponseRequestedRangeNotSatisfiable;
    static const HttpResponseStatus kHttpResponseExpectationFailed;
    static const HttpResponseStatus kHttpResponseInternalServerError;
    static const HttpResponseStatus kHttpResponseNotImplemented;
    static const HttpResponseStatus kHttpResponseBadGateway;
    static const HttpResponseStatus kHttpResponseServiceUnavailable;
    static const HttpResponseStatus kHttpResponseGatewayTimeout;
    static const HttpResponseStatus kHttpResponseHttpVersionNotSupported;
};

class HttpResponse : public Response
{
protected:
    HttpHeaderEnumerate headers_;
    int64               content_length_;
    Buffer              prepare_buffer_;
    bool                use_prepare_buffer_;
    bool                has_content_length_;
    bool                is_responded_;

public:
    static const char* kHttpVersion;
    static const char* kHttpNewLine;

    HttpResponse(Connection* conn);

    void add_header(const std::string& key, const std::string& value);

    void set_has_content_length(bool enabled) { has_content_length_ = enabled; }
    void set_content_length(int64 content_length) {
        content_length_ = content_length;
    }
    void disable_prepare_buffer() { use_prepare_buffer_ = false; }

    bool has_content_length() const { return has_content_length_; }
    int64 content_length() const { return content_length_; }
    bool is_responded() const { return is_responded_; }

    // write it into the prepared buffer
    virtual ssize_t write_data(const byte* ptr, size_t size);
    virtual void respond(const HttpResponseStatus& status);
    virtual void reset();
};

}

#endif /* _HTTP_WRAPPER_H_ */

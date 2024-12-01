#ifndef ALIAS_H
#define ALIAS_H

namespace wfrest
{
class HttpReq;
class HttpResp;
class HttpServer;
class HttpCookie;
} // namespace wfrest

namespace App
{
using HTTPRequest  = wfrest::HttpReq;
using HTTPResponse = wfrest::HttpResp;
using HTTPServer   = wfrest::HttpServer;
using HTTPCookie   = wfrest::HttpCookie;
} // namespace App

#endif

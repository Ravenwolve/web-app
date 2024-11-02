#ifndef FUNCTIONAL_H
#define FUNCTIONAL_H

#include "alias.h"
#include <functional>
#include <wfrest/HttpServer.h>

namespace App
{
template<typename TController>
auto bind(void (TController::*handler)(const HTTPRequest *, HTTPResponse *), TController *controller) -> wfrest::Handler
{
    using std::placeholders::_1, std::placeholders::_2;
    return static_cast<wfrest::Handler>(std::bind(handler, controller, _1, _2));
}

template<typename TController>
auto bind(void handler(const HTTPRequest *, HTTPResponse *), TController *controller) -> wfrest::Handler
{
    using std::placeholders::_1, std::placeholders::_2;
    return static_cast<wfrest::Handler>(std::bind(handler, controller, _1, _2));
}

template<typename TRequestDTO>
auto extract(const HTTPRequest *request) -> std::optional<TRequestDTO>;
} // namespace App

#endif

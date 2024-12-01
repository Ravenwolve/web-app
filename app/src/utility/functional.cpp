#include "functional.h"
#include "dto/refreshrequestdto.h"
#include "dto/signinrequestdto.h"
#include "dto/signuprequestdto.h"
#include <QDebug>

namespace App
{
template<>
auto extract(const HTTPRequest *request) -> std::optional<SignUpRequestDTO>
{
    const auto &query_list = request->json();

    if (query_list.size() != 2 || !query_list.has("usr") || !query_list.has("pwd"))
    {
        return std::nullopt;
    }

    SignUpRequestDTO dto{QString::fromStdString(query_list["usr"]), QString::fromStdString(query_list["pwd"])};

    return dto;
}

template<>
auto extract(const HTTPRequest *request) -> std::optional<SignInRequestDTO>
{
    const auto &query_list = request->json();

    if (query_list.size() != 2 || !query_list.has("usr") || !query_list.has("pwd"))
    {
        return std::nullopt;
    }

    SignInRequestDTO dto{QString::fromStdString(query_list["usr"]), QString::fromStdString(query_list["pwd"])};

    return dto;
}

template<>
auto extract(const HTTPRequest *request) -> std::optional<RefreshRequestDTO>
{
    const auto &cookies = request->cookies();

    if (!cookies.contains("Refresh-Token"))
    {
        return std::nullopt;
    }

    return RefreshRequestDTO{QString::fromStdString(cookies.at("Refresh-Token")).split(";")[0]};
}
} // namespace App

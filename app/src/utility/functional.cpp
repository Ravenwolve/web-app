#include "functional.h"
#include "dto/authrequestdto.h"
#include "dto/userrequestdto.h"
#include <QDebug>

namespace App
{
template<>
auto extract(const HTTPRequest *request) -> std::optional<UserRequestDTO>
{
    const auto &query_list = request->json();

    if (query_list.size() != 2 || !query_list.has("usr") || !query_list.has("pwd"))
    {
        return std::nullopt;
    }

    UserRequestDTO dto{QString::fromStdString(query_list["usr"]), QString::fromStdString(query_list["pwd"])};

    return dto;
}
} // namespace App

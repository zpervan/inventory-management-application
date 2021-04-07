#include "database_query.h"

#include <fmt/core.h>

void DatabaseQuery::Connect()
{
    database_connection_ = std::make_unique<PGconn*>(PQconnectdb(CreateConnectionLoginString().c_str()));

    if (PQstatus(*database_connection_) != ConnStatusType::CONNECTION_OK)
    {
        fmt::print("Cannot connect to database. Error: {}", PQerrorMessage(*database_connection_));
        PQfinish(*database_connection_);
    }
    else
    {
        fmt::print("Connection to database established.");
    }
}

std::string DatabaseQuery::Fetch()
{
    std::unique_ptr<PGresult*> result = std::make_unique<PGresult*>(PQexec(*database_connection_, "SELECT * FROM pc"));
    fmt::print("\nPQntuples: {}", PQntuples(*result));
    fmt::print("\nPQnfields: {}", PQnfields(*result));

    for (std::size_t i = 0; i < PQnfields(*result); i++)
    {
        fmt::print("\nPQfnames: {}", PQfname(*result, i));
    }

    for (int i = 0; i < PQntuples(*result); i++)
    {
        fmt::print("\n");
        for (int j = 0; j < PQnfields(*result); j++)
        {
            fmt::print(" {} ", PQgetvalue(*result, i, j));
        }
    }
    return {};
}

ConnStatusType DatabaseQuery::GetConnectionStatus() const
{
    return PQstatus(*database_connection_);
}

std::string DatabaseQuery::CreateConnectionLoginString() const
{
    return fmt::format("{}{}&{}&{}&{}", url, port, dbname, user, password);
}

#include "database_query.h"

#include <fmt/core.h>

int DatabaseQuery::Connect()
{
    database_connection_ = std::make_unique<PGconn*>(PQconnectdb(CreateConnectionLoginString().c_str()));

    if (PQstatus(*database_connection_) != ConnStatusType::CONNECTION_OK)
    {
        fmt::print("Cannot connect to database. Error: {}", PQerrorMessage(*database_connection_));
        PQfinish(*database_connection_);
        return ConnStatusType::CONNECTION_BAD;
    }
    else
    {
        fmt::print("Connection to database established.");
        return ConnStatusType::CONNECTION_OK;
    }
}

void DatabaseQuery::Fetch() {}

std::string DatabaseQuery::CreateConnectionLoginString() const
{
    return fmt::format("{}{}&{}&{}&{}", url, port, dbname, user, password);
}

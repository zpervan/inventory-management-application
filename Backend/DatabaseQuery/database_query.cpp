#include "database_query.h"

#include <fmt/format.h>

/// @TODO: Add error handling for failed database connection
void DatabaseQuery::Connect()
{
    database_connection_ = PQconnectdb(CreateConnectionLoginString().c_str());

    if (PQstatus(database_connection_) != ConnStatusType::CONNECTION_OK)
    {
        fmt::print("Cannot connect to database. Error: {}", PQerrorMessage(database_connection_));
        PQfinish(database_connection_);
    }
    else
    {
        fmt::print("Connection to database established.");
    }
}

DatabaseResponse DatabaseQuery::FetchFromDatabase(const std::string& name)
{
    query_result_ = PQexec(database_connection_, fmt::format("SELECT * FROM {}", name).c_str());
    column_count_ = PQnfields(query_result_);
    row_count_ = PQntuples(query_result_);

    return {FetchDatabaseHeader(), FetchDatabaseValues()};
}

void DatabaseQuery::PrintQueryResult()
{
    for (const auto& column_name : FetchDatabaseHeader())
    {
        fmt::print("\nPQfnames: {}", column_name);
    }

    for (const auto& value_pair : FetchDatabaseValues())
    {
        fmt::print("\n");
        for (const auto& value : value_pair.second)
        {
            fmt::print(" {} ", value);
        }
    }
}

ConnStatusType DatabaseQuery::GetConnectionStatus() const
{
    return PQstatus(database_connection_);
}

std::string DatabaseQuery::CreateConnectionLoginString() const
{
    return fmt::format("{}{}&{}&{}&{}", url, port, dbname, user, password);
}

DatabaseHeader DatabaseQuery::FetchDatabaseHeader()
{
    DatabaseHeader column_names{};
    column_names.reserve(column_count_);

    for (int i = 0; i < column_count_; i++)
    {
        column_names.emplace_back(PQfname(query_result_, i));
    }

    return column_names;
}

DatabaseValues DatabaseQuery::FetchDatabaseValues()
{
    DatabaseValues database_values{};

    for (int i = 0; i < row_count_; i++)
    {
        std::vector<std::string> values{};
        values.reserve(column_count_);

        for (int j = 1; j < column_count_; j++)
        {
            values.emplace_back(PQgetvalue(query_result_, i, j));
        }
        database_values[i] = values;
    }

    return database_values;
}

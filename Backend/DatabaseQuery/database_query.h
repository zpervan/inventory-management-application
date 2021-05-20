#ifndef INVENTORYMANAGEMENTAPPLICATION_DATABASE_QUERY_H
#define INVENTORYMANAGEMENTAPPLICATION_DATABASE_QUERY_H

#include <map>
#include <memory>
#include <string>
#include <vector>

#include <libpq-fe.h>

using DatabaseHeader = std::vector<std::string_view>;
using DatabaseValues = std::map<std::size_t, std::vector<std::string>>;

struct DatabaseResponse
{
    DatabaseHeader database_header;
    DatabaseValues database_values;
};

class DatabaseQuery
{
  public:
    /// @brief Establish a connection to the PostgreSQL database
    /// @TODO: Change signature to accept login data
    void Connect();

    /// @brief FetchFromDatabase all the content from the given table
    [[nodiscard]] DatabaseResponse FetchFromDatabase(const std::string& name);

    ConnStatusType GetConnectionStatus() const;

    /// @brief Prints the database response from the query result.
    /// @attention Only for debug purposes
    void PrintQueryResult();

  private:
    std::string CreateConnectionLoginString() const;
    DatabaseHeader FetchDatabaseHeader();
    DatabaseValues FetchDatabaseValues();

    /// @TODO: The database information should be removed once a login and connection form is established
    const std::string url{"postgresql://postgres@localhost?"};
    const std::string port{"port=5432"};
    const std::string dbname{"dbname=postgres"};
    const std::string user{"user=postgres"};
    const std::string password{"password=root"};
    int column_count_{0};
    int row_count_{0};

    PGconn* database_connection_{nullptr};
    PGresult* query_result_{nullptr};
};

#endif  // INVENTORYMANAGEMENTAPPLICATION_DATABASE_QUERY_H

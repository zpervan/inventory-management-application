#ifndef INVENTORYMANAGEMENTAPPLICATION_DATABASE_QUERY_H
#define INVENTORYMANAGEMENTAPPLICATION_DATABASE_QUERY_H

#include <memory>
#include <string>

#include <libpq-fe.h>

class DatabaseQuery
{
  public:
    /// @brief Establish a connection to the PostgreSQL database
    /// @TODO: Change signature to accept login data
    int Connect();

    /// @brief Fetch all the content from the given table
    void Fetch();

  private:
    std::string CreateConnectionLoginString() const;

    /// @TODO: The database information should be removed once a login and connection form is established
    const std::string url{"postgresql://postgres@localhost?"};
    const std::string port{"port=5432"};
    const std::string dbname{"dbname=postgres"};
    const std::string user{"user=postgres"};
    const std::string password{"password=root"};

    std::unique_ptr<PGconn*> database_connection_;
};

#endif  // INVENTORYMANAGEMENTAPPLICATION_DATABASE_QUERY_H

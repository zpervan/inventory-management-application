#ifndef INVENTORYMANAGEMENTAPPLICATION_DATABASE_QUERY_H
#define INVENTORYMANAGEMENTAPPLICATION_DATABASE_QUERY_H

#include <string>

class DatabaseQuery
{
  public:
    int Connect();

  private:
    const std::string url_{"postgresql://postgres@localhost?"};
    const std::string port_{"port=5432"};
    const std::string dbname_{"port=postgres"};
    const std::string user_{"user=postgres"};
    const std::string password_{"password=root"};
};

#endif  // INVENTORYMANAGEMENTAPPLICATION_DATABASE_QUERY_H

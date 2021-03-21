#include "database_query.h"

#include <iostream>

#include <libpq-fe.h>

int DatabaseQuery::Connect()
{
    const char conninfo[] = "postgresql://postgres@localhost?port=5432&dbname=postgres&user=postgres&password=root";

    PGconn* conn = PQconnectdb(conninfo);

    if (PQstatus(conn) != CONNECTION_OK)
    {
        std::cout << "Connection to database failed: " << PQerrorMessage(conn) << std::endl;
        PQfinish(conn);
        return 1;
    }
    else
    {
        std::cout << "Connection to database succeed." << std::endl;
        return 0;
    }
}

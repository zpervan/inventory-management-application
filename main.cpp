#include "Backend/DatabaseQuery/database_query.h"
int main()
{
    DatabaseQuery dbq;

    dbq.Connect();
    dbq.Fetch();

    return 0;
}
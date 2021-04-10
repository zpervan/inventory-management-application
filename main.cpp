#include <memory>

#include "Backend/DatabaseQuery/database_query.h"
#include "GUI/gui_runner.h"

int main()
{
    DatabaseQuery dbq;
    dbq.Connect();
    dbq.Fetch();

    std::unique_ptr<Runner> runner{new Runner};
    runner->Run();

    return 0;
}
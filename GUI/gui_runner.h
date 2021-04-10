#ifndef INVENTORYMANAGEMENTAPPLICATION_GUI_GUI_RUNNER_H_
#define INVENTORYMANAGEMENTAPPLICATION_GUI_GUI_RUNNER_H_

#include <d3d10.h>
#include <string>

class Runner {
public:
    void Run();

private:
    int Initialize();

    const std::string application_title{"Inventory Management Application DEMO"};
    HWND window_{};
};

#endif  // INVENTORYMANAGEMENTAPPLICATION_GUI_GUI_RUNNER_H_

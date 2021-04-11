#ifndef INVENTORYMANAGEMENTAPPLICATION_GUI_GUI_RUNNER_H_
#define INVENTORYMANAGEMENTAPPLICATION_GUI_GUI_RUNNER_H_

#include <string>

class Runner {
  public:
    /// @brief
    void Run();

  private:
    void InitializeImguiContext();

    void CheckForEvents();

    void StartDearImguiFrame();

    void Render();

    void Destroy();

    const std::string application_title{"Inventory Management Application DEMO"};
    bool done_{false};
};

#endif  // INVENTORYMANAGEMENTAPPLICATION_GUI_GUI_RUNNER_H_

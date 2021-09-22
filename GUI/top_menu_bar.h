#ifndef INVENTORYMANAGEMENTAPPLICATION_GUI_TOP_MENU_BAR_H_
#define INVENTORYMANAGEMENTAPPLICATION_GUI_TOP_MENU_BAR_H_

#include "../ThirdParty/Imgui/imgui.h"

namespace menu_bar {

inline void Create() {
  ImGui::BeginMainMenuBar();
  {
    if (ImGui::BeginMenu("Aplikacija")) {
      if (ImGui::MenuItem("Izlaz")) {}
      ImGui::EndMenu();
    }
    if (ImGui::MenuItem("Postavke")) {};
    if (ImGui::MenuItem("Pomoc")) {};
  }
  ImGui::EndMainMenuBar();
}
}

#endif //INVENTORYMANAGEMENTAPPLICATION_GUI_TOP_MENU_BAR_H_

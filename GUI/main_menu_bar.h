#ifndef INVENTORYMANAGEMENTAPPLICATION_GUI_MAIN_MENU_BAR_H_
#define INVENTORYMANAGEMENTAPPLICATION_GUI_MAIN_MENU_BAR_H_

#include "application_settings.h"
#include "directx_window.h"
#include <iostream>

namespace main_menu {

void Create() {
  ImGui::SetNextWindowSize(main_menu::kGSize);
  ImGui::SetNextWindowPos(main_menu::kGPosition);
  ImGui::Begin("Hello, world!", nullptr, properties::kGWindowFlags);
  ImGui::End();
}

}

#endif //INVENTORYMANAGEMENTAPPLICATION_GUI_MAIN_MENU_BAR_H_

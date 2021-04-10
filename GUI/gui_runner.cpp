#include "gui_runner.h"

#include <iostream>

#include <d3d10.h>
#include <d3d10_1.h>
#include <tchar.h>

/// @TODO: Avoid relative paths
#include "../ThirdParty/DearImgui/imgui.h"
#include "../ThirdParty/DearImgui/imgui_impl_dx10.h"
#include "../ThirdParty/DearImgui/imgui_impl_win32.h"

void Runner::Run()
{
    std::cout << "\nHello from runner" << std::endl;
}

void Runner::Initialize() {}

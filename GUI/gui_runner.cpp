#include "gui_runner.h"

#include <iostream>

#include <d3d10.h>
#include <d3d10_1.h>
#include <imgui.h>
#include <tchar.h>

#include "imgui_impl_dx10.h"
#include "imgui_impl_win32.h"

void Runner::Run()
{
    std::cout << "\nHello from runner" << std::endl;
}

void Runner::Initialize() {}

#include "runner.h"
#include "window_bootstrap.h"
#include "main_menu_bar.h"
#include "main_window.h"
#include "top_menu_bar.h"

void Runner::run() {
    CreateDirectXWindow("Inventory Management");
    InitializeImguiContext();
    main_menu::Initialize();
    main_window::Initialize();

    while (!window::done)
    {
        CheckForEvents();

        if (window::done)
        {
            break;
        }

        StartDearImguiFrame();

        /** GUI Components START **/
        menu_bar::Create();
        main_menu::Create();
        main_window::Create();
        /** GUI Components END **/

        Render();
    }

    Destroy();
}

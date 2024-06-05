#pragma once

#include "../ui/IGuiApp.hpp"

namespace program
{
    namespace loader {
        namespace container {
            extern std::unique_ptr<IGuiApp> guiApp;

            void init(int argc, char** argv);
        }
    }
}


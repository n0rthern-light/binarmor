#ifndef LOADER_APPLICATION_CONTAINER_HPP_
#define LOADER_APPLICATION_CONTAINER_HPP_

#include "../ui/IGuiApp.hpp"

namespace program
{
    namespace loader {
        namespace container {
            extern IGuiApp* guiApp;

            void init(int argc, char** argv);
            void exit();
        }
    }
}

#endif // LOADER_APPLICATION_CONTAINER_HPP_

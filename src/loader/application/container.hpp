#ifndef SRC_LOADER_APPLICATION_CONTAINER_HPP_
#define SRC_LOADER_APPLICATION_CONTAINER_HPP_





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




#endif // SRC_LOADER_APPLICATION_CONTAINER_HPP_

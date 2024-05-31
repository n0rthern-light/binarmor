#pragma once

#include "../message/IMessageBus.hpp"

namespace program
{
    namespace shared
    {
        namespace container
        {
            extern std::shared_ptr<IMessageBus> eventBus;

            void init(int argc, char** argv);
        }
    }
}


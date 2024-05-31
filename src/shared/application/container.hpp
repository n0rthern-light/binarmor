#pragma once

#include "../message/IMessageBus.hpp"

namespace program
{
    namespace shared
    {
        namespace container
        {
            extern std::shared_ptr<IMessageBus> eventBus;
            extern std::shared_ptr<IMessageBus> commandBus;

            void init(int argc, char** argv);
        }
    }
}


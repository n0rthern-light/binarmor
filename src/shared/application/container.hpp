#pragma once

#include "../message/IMessageBus.hpp"
#include "../crypto/IHasher.hpp"

namespace program
{
    namespace shared
    {
        namespace container
        {
            extern std::unique_ptr<IMessageBus> eventBus;
            extern std::unique_ptr<IHasher> hasher;

            void init(int argc, char** argv);
        }
    }
}


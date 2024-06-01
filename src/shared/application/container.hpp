#pragma once

#include "../message/IMessageBus.hpp"
#include "../crypto/IHasher.hpp"

namespace program
{
    namespace shared
    {
        namespace container
        {
            extern std::shared_ptr<IMessageBus> eventBus;
            extern std::shared_ptr<IHasher> hasher;

            void init(int argc, char** argv);
        }
    }
}


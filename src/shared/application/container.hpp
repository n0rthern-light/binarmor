#ifndef SHARED_APPLICATION_CONTAINER_HPP_
#define SHARED_APPLICATION_CONTAINER_HPP_

#include "../message/IMessageBus.hpp"
#include "../crypto/IHasher.hpp"
#include "../crypto/ICrypter.hpp"

namespace program
{
    namespace shared
    {
        namespace container
        {
            extern std::unique_ptr<program::shared::message::IMessageBus> eventBus;
            extern std::unique_ptr<program::shared::message::IMessageBus> commandBus;
            extern std::unique_ptr<program::shared::crypto::IHasher> hasher;
            extern std::unique_ptr<program::shared::crypto::ICrypter> crypter;

            void init(int argc, char** argv);
            void exit();
        }
    }
}

#endif // SHARED_APPLICATION_CONTAINER_HPP_

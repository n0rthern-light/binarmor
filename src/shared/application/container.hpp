#ifndef SRC_SHARED_APPLICATION_CONTAINER_HPP_
#define SRC_SHARED_APPLICATION_CONTAINER_HPP_



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




#endif // SRC_SHARED_APPLICATION_CONTAINER_HPP_

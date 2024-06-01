#include "container.hpp"
#include "../message/simple/SimpleMessageBus.hpp"
#include "../crypto/openssl/OpenSslHasher.hpp"

std::shared_ptr<IMessageBus> program::shared::container::eventBus = nullptr;
std::shared_ptr<IHasher> program::shared::container::hasher = nullptr;

void program::shared::container::init(int argc, char** argv)
{
    program::shared::container::eventBus = std::make_shared<CSimpleMessageBus>(false);
    program::shared::container::hasher = std::make_shared<COpenSslHasher>();
}


#include "container.hpp"
#include "../message/simple/SimpleMessageBus.hpp"
#include "../crypto/openssl/OpenSslHasher.hpp"

std::unique_ptr<IMessageBus> program::shared::container::eventBus = nullptr;
std::unique_ptr<IMessageBus> program::shared::container::commandBus = nullptr;
std::unique_ptr<IHasher> program::shared::container::hasher = nullptr;

void program::shared::container::init(int argc, char** argv)
{
    program::shared::container::eventBus = std::make_unique<CSimpleMessageBus>();
    program::shared::container::commandBus = std::make_unique<CSimpleMessageBus>(true);
    program::shared::container::hasher = std::make_unique<COpenSslHasher>();
}

void program::shared::container::exit()
{
    program::shared::container::hasher = nullptr;
    program::shared::container::eventBus = nullptr;
}


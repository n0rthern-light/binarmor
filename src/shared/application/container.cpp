#include "container.hpp"
#include "../message/simple/SimpleMessageBus.hpp"
#include "../crypto/openssl/OpenSslHasher.hpp"
#include "../crypto/openssl/OpenSslCrypter.hpp"

std::unique_ptr<program::shared::message::IMessageBus> program::shared::container::eventBus = nullptr;
std::unique_ptr<program::shared::message::IMessageBus> program::shared::container::commandBus = nullptr;
std::unique_ptr<program::shared::crypto::IHasher> program::shared::container::hasher = nullptr;
std::unique_ptr<program::shared::crypto::ICrypter> program::shared::container::crypter = nullptr;

void program::shared::container::init(int argc, char** argv)
{
    program::shared::container::eventBus = std::make_unique<program::shared::message::simple::CSimpleMessageBus>();
    program::shared::container::commandBus = std::make_unique<program::shared::message::simple::CSimpleMessageBus>(true);
    program::shared::container::hasher = std::make_unique<program::shared::crypto::openssl::COpenSslHasher>();
    program::shared::container::crypter = std::make_unique<program::shared::crypto::openssl::COpenSslCrypter>();
}

void program::shared::container::exit()
{
    program::shared::container::crypter = nullptr;
    program::shared::container::hasher = nullptr;
    program::shared::container::eventBus = nullptr;
    program::shared::container::commandBus = nullptr;
}


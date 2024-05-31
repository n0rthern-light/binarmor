#include "container.hpp"
#include "../message/simple/SimpleMessageBus.hpp"

std::shared_ptr<IMessageBus> program::shared::container::eventBus = nullptr;
std::shared_ptr<IMessageBus> program::shared::container::commandBus = nullptr;

void program::shared::container::init(int argc, char** argv)
{
    program::shared::container::eventBus = std::make_shared<CSimpleMessageBus>(false);
    program::shared::container::commandBus = std::make_shared<CSimpleMessageBus>(true);
}


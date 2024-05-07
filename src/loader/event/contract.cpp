#include "contract.hpp"
#include "simple/SimpleEventBus.hpp"

std::shared_ptr<IEventBus> event::bus = nullptr;

void event::init()
{
	event::bus = std::make_shared<CSimpleEventBus>();
}

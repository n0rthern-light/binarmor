#include "behave.hpp"
#include "container.hpp"
#include <shared/application/container.hpp>
#include "events/NewFileSelectedEvent.hpp"

void program::core::application::behave(int argc, char** argv)
{
    program::shared::container::eventBus->subscribe(typeid(CNewFileSelectedEvent), [&](IMessage* event) {
		auto newFileSelectedEvent = dynamic_cast<CNewFileSelectedEvent*>(event);
        program::core::container::file::binaryFileStateManager->load(newFileSelectedEvent->path());
	});
}


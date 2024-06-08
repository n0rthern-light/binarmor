#include "behave.hpp"
#include "container.hpp"
#include <shared/application/container.hpp>
#include "events/NewFileSelectedEvent.hpp"

void program::core::application::behave(int argc, char** argv)
{
    program::shared::container::eventBus->subscribe(typeid(CNewFileSelectedEvent), [&](message_ptr event) {
		auto newFileSelectedEvent = dynamic_cast<CNewFileSelectedEvent*>(event.get());
        program::core::container::file::binaryFileStateManager->load(newFileSelectedEvent->path());
	});
}


#pragma once

#include "headers.hpp"
#include "ui/IGuiApp.hpp"
#include <shared/event/IEventBus.hpp>
#include <core/file/IFileReader.hpp>
#include <core/file/BinaryFileStateManager.hpp>
#include <core/file/analysis/AnalysisRunner.hpp>

namespace container {
	extern std::shared_ptr<IEventBus> eventBus;
	extern std::shared_ptr<IGuiApp> guiApp;

	namespace core {
		namespace file {
			extern std::shared_ptr<IFileReader> fileReader;
			extern std::shared_ptr<CBinaryFileStateManager> binaryFileStateManager;

			namespace analysis {
				extern std::shared_ptr<CAnalysisRunner> runner;
			}
		}
	}

	void init(int argc, char** argv);
}

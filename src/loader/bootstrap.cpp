#include "bootstrap.hpp"
#include <shared/application/container.hpp>
#include <core/application/container.hpp>
#include <core/application/behave.hpp>
#include "application/container.hpp"
#include "application/behave.hpp"

void program::bootstrap::init(int argc, char** argv)
{
    program::shared::container::init(argc, argv);
    program::core::container::init(argc, argv);
    program::loader::container::init(argc, argv);

    program::loader::application::behave(argc, argv);
    program::core::application::behave(argc, argv);
}


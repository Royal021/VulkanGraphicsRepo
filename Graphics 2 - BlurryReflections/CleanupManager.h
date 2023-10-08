#pragma once

#include <functional>

namespace CleanupManager{
    
/// Register a function to be called when CleanupManager::cleanupEverything() is called.
/// @param func The function to call.
void registerCleanupFunction( std::function<void()> func);

/// Call all registered cleanup functions.
void cleanupEverything();

};

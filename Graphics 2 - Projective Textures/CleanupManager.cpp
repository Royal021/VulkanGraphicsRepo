#include "CleanupManager.h"
#include <vector>
#include <functional>

static std::vector<std::function<void()> > cleanupFunctions;

void CleanupManager::registerCleanupFunction( std::function<void()> func)
{
    cleanupFunctions.push_back(func);
}

void CleanupManager::cleanupEverything(){
    for(auto& f : cleanupFunctions ){
        f();
    }
}


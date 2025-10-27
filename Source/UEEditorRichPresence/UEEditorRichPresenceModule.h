#pragma once
#include "Modules/ModuleManager.h"

class FUEEditorRichPresenceModule : public IModuleInterface
{
public:
    virtual void StartupModule() override {}
    virtual void ShutdownModule() override {}
};

#pragma once

#include <string>
#include <vector>

namespace DCURSES {
    struct ExternalEvent {
        std::string id;
        std::string displayName;
        double weight = 0;
        std::string owner = "unknown"; // Plugin file of the form that sent the register event.
        bool takeKeys = false;         // "~takekeys" flag: roll Key Loss Chance before the event runs.
    };

    // Weight <= 0 removes the id. Same id registers again and replaces the weight.
    // Ids are case-insensitive. Optional display name: "mycurse~My Curse".
    // Optional flags after a second '~': "mycurse~My Curse~takekeys" makes the event roll the
    // Key Loss Chance setting and remove DD keys like the standard event. Default: keys are kept.
    // Registering the same id again also replaces the flag.
    // The sender only names the owner for the duplicate id warning; the native call has none.
    bool RegisterExternalEvent(std::string spec, double weight, RE::TESForm* sender = nullptr);
    bool UnregisterExternalEvent(std::string spec);
    double GetExternalEventWeight(std::string spec);
    int GetExternalEventCount();
    ExternalEvent GetExternalEventAt(int index);
    std::vector<ExternalEvent> GetExternalEvents();
    void ClearExternalEvents();

    // If takeKeys, rolls Key Loss Chance and removes DD keys from the actor. Then fires the
    // targeted DCurses_RunExternalEvent_<id> (only that mod's listener runs), then the normal
    // DCurses_EventTriggered notice.
    void RunExternalEvent(std::string id, std::string displayName, bool takeKeys, bool isBoss, std::string contName, RE::Actor* actor);
}

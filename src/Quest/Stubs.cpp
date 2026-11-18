#include "Quest/QuestEvents.h"
#include "Quest/QuestSettings.h"
#include "Quest/Serialized.h"

using namespace SKSE;

namespace DCURSES::Quest {
    // The GitLab tree does not include the quest cpp files. These keep the DLL linkable.
    // Quest-plugin behavior from the official DLL is not in this source drop.

    bool CheckObjectActivation(RE::TESObjectREFR*) { return false; }
    void CheckQuestStageChanged(RE::FormID, uint16_t) {}
    void OnLocationChanged() {}
    void OnGameLoaded() {}
    void OnSettingsChanged() {}

    void PlayerMessage(Translator, bool) {}
    void ResetMCMSettings() {}
    void SaveMCMSettings() {}
    bool LoadSettingsFile() { return false; }
    void PushSettingsToMCM() {}
    bool PapyrusFunctionsSettigns(RE::BSScript::IVirtualMachine*) { return true; }

    // Keep the QDAT cosave record round-tripping unchanged, so quest data from the official DLL
    // survives a save made with this build. (Based on crajjjj's Devious-Curses-NG patch build.)
    QuestData* QuestData::GetSingleton() {
        static QuestData instance;
        return &instance;
    }

    void QuestData::revert() {
        std::memset(static_cast<void*>(this), 0, sizeof(QuestData));
    }

    void SerdeOnGameSaved(SKSE::SerializationInterface* serde) {
        if (!serde->OpenRecord(QuestDataRecord, 0)) {
            log::error("Unable to open record to write quest cosave data.");
            return;
        }
        serde->WriteRecordData(QuestData::GetSingleton(), sizeof(QuestData));
    }

    void SerdeOnRecordLoaded(SKSE::SerializationInterface* serde, std::uint32_t type, std::uint32_t size, std::uint32_t) {
        if (type != QuestDataRecord) {
            return;
        }
        if (size == sizeof(QuestData)) {
            serde->ReadRecordData(QuestData::GetSingleton(), sizeof(QuestData));
        }
        else {
            log::warn("Error reading quest data, quest state reset.");
        }
    }

    void SerdeOnRevert(SKSE::SerializationInterface*) {
        QuestData::GetSingleton()->revert();
    }
}

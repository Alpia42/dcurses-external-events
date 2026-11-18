# DCurses External Events

A fork of [Devious Curses NG](https://www.loverslab.com/files/file/41083-devious-curses-ng/) by CyberCheese. Other mods can add their own weighted events to the chest, door and body roll. Devious Curses still decides whether anything fires, and a registered event only competes with the built-in weights. This fork also adds support for SLO Aroused NG and fixes several bugs from 0.9.0.

Version 0.11.0, based on Devious Curses NG 0.9.0.

See [docs/ExternalEvents.md](docs/ExternalEvents.md) for the register and run events, the id rules, the optional `~takekeys` flag, and a Papyrus example.

## Features

- **External events API.** Mods register a weighted bucket with `DCurses_RegisterEvent`. When it is picked, only that mod receives `DCurses_RunExternalEvent_<id>`. The MCM has an External Events page that lists what is registered.
- **Optional key loss.** An event registered with `~takekeys` rolls the MCM Key Loss Chance and removes DD keys before it runs, like the built-in bondage event. Without the flag, keys are kept.
- **SLO Aroused NG support** (3.3.0 or newer, through its native API). Arousal is read live for every actor. The arousal this mod adds is its own effect that halves over time (MCM: Arousal Half-Life). A Frigid Wash lowers arousal by 100 and wears off over a set time (MCM: Frigid Wash Duration). OSL Aroused and other SLA-compatible mods work as before.

## Install

This is a DLL. Replace `DeviousCurses.dll` in the installed Devious Curses NG 0.9.0 mod and keep the original plugin. Use the `DCurses_MCM.pex` built from `SourceScripts/DCurses_MCM.psc`. It sends `DCurses_RequestEvents` on reload and adds the External Events page and the new settings.

## Building

Visual Studio with the C++ and CMake workloads, using the vcpkg bundled with Visual Studio. `ports/commonlibsse-ng` pins the CommonLibSSE-NG version. Set `OUTPUT_FOLDER` to a mod folder to have the DLL copied there after a build.

The source of the Quests add-on is not public. `src/Quest/Stubs.cpp` keeps the DLL linkable and carries the add-on's save record through unchanged.

After changing the MCM block in `include/Settings.h`, run `python CODEGEN.py`. It regenerates `SourceScripts/DCurses_MCM.psc`, the English MCM strings in `translationData/`, and the generated parts of `src/Settings.cpp`. Then compile `DCurses_MCM.psc` against the SkyUI SDK, SexLab P+, PapyrusUtil and Devious Devices NG sources.

## Credits

- **CyberCheese**: Devious Curses NG, the original mod and source ([GitLab](https://gitlab.com/cybercheese/devious-curses)).
- **crajjjj**: SLO Aroused NG support, and the fixes for the stuck contraption faction, the Nocturnal piercing spectators, the settings migration and the quest save record, from [Devious-Curses-NG](https://github.com/crajjjj/Devious-Curses-NG).

## License

MIT, see [LICENSE](LICENSE). The original copyright notice is kept.

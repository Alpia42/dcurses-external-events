#pragma once

namespace DCURSES {
	bool CanFastTravelMap(RE::Actor*, bool);

	bool CanFastTravelDevices();

	// The CanFastTravelMap call hook (AE ID 53095 + 0x328) is used from 1.6.640 on. On Skyrim 1.7.99 / 1.7.104
	// the address library still has ID 53095, and the function and its neighbours sit at the same relative
	// offsets as on 1.6.1170, so the hook is installed there too. Set this to false to skip it on 1.7.x and
	// use the Papyrus fallback (SetFastTravelStatePapyrus) instead.
	inline constexpr bool kFastTravelHookOn1_7 = true;

	// Returns false, and leaves the game untouched, when the hook site is not a 5-byte call.
	bool InstallFastTravelHooks();

	void SetFastTravelStatePapyrus(bool can_install_fast_travel_hook);
}
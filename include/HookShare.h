#pragma once

#include <vector>  // vector

namespace RE
{
	class InputEvent;
	class PlayerInputHandler;
}


#define HOOK_SHARE_API_VERSION_MAJOR	1


namespace HookShare
{
	enum ReturnType : UInt32
	{
		kReturnType_False,
		kReturnType_True,
		kReturnType_Continue
	};


	enum Hook : UInt32
	{
		kHook_FirstPersonState,
		kHook_ThirdPersonState,
		kHook_Favorites,
		kHook_Movement,
		kHook_Look,
		kHook_Sprint,
		kHook_ReadyWeapon,
		kHook_AutoMove,
		kHook_ToggleRun,
		kHook_Activate,
		kHook_Jump,
		kHook_Shout,
		kHook_AttackBlock,
		kHook_Run,
		kHook_Sneak
	};


	typedef ReturnType _PlayerInputHandler_CanProcess_t(RE::PlayerInputHandler* a_this, RE::InputEvent* a_event);
	extern std::vector<_PlayerInputHandler_CanProcess_t*> firstPersonStateRegs;
	extern std::vector<_PlayerInputHandler_CanProcess_t*> thirdPersonStateRegs;
	extern std::vector<_PlayerInputHandler_CanProcess_t*> favoritesRegs;
	extern std::vector<_PlayerInputHandler_CanProcess_t*> movementRegs;
	extern std::vector<_PlayerInputHandler_CanProcess_t*> lookRegs;
	extern std::vector<_PlayerInputHandler_CanProcess_t*> sprintRegs;
	extern std::vector<_PlayerInputHandler_CanProcess_t*> readyWeaponRegs;
	extern std::vector<_PlayerInputHandler_CanProcess_t*> autoMoveRegs;
	extern std::vector<_PlayerInputHandler_CanProcess_t*> toggleRunRegs;
	extern std::vector<_PlayerInputHandler_CanProcess_t*> activateRegs;
	extern std::vector<_PlayerInputHandler_CanProcess_t*> jumpRegs;
	extern std::vector<_PlayerInputHandler_CanProcess_t*> shoutRegs;
	extern std::vector<_PlayerInputHandler_CanProcess_t*> attackBlockRegs;
	extern std::vector<_PlayerInputHandler_CanProcess_t*> runRegs;
	extern std::vector<_PlayerInputHandler_CanProcess_t*> sneakRegs;


	typedef void _RegisterHook_t(_PlayerInputHandler_CanProcess_t* a_func, Hook a_hookType);
	void RegisterHook(_PlayerInputHandler_CanProcess_t* a_func, Hook a_hookType);
}

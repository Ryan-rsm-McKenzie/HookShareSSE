#pragma once

#include <vector>  // vector
#include "RE/BShkbAnimationGraph.h"  // BShkbAnimationGraphPtr

namespace RE
{
	class InputEvent;
	class PlayerInputHandler;
	class TESObjectREFR;
}


#define HOOK_SHARE_API_VERSION_MAJOR	3


namespace HookShare
{
	enum class ReturnType : UInt32
	{
		kFalse = 0,
		kTrue = 1,
		kContinue = 2
	};


	enum class Hook : UInt32
	{
		kFirstPersonState = 0,
		kThirdPersonState = 1,
		kFavorites = 2,
		kMovement = 3,
		kLook = 4,
		kSprint = 5,
		kReadyWeapon = 6,
		kAutoMove = 7,
		kToggleRun = 8,
		kActivate = 9,
		kJump = 10,
		kShout = 11,
		kAttackBlock = 12,
		kRun = 13,
		kSneak = 14
	};


	enum Type : UInt32
	{
		kType_CanProcess = 0
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

	/* REGS BEGIN */

	typedef void _RegisterForCanProcess_t(_PlayerInputHandler_CanProcess_t* a_func, Hook a_hookType);
	void RegisterForCanProcess(_PlayerInputHandler_CanProcess_t* a_func, Hook a_hookType);

	/* REGS END */
}

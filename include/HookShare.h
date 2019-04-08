#pragma once

#include <vector>  // vector
#include "RE/BShkbAnimationGraph.h"  // BShkbAnimationGraphPtr

namespace RE
{
	class InputEvent;
	class PlayerInputHandler;
	class TESObjectREFR;
}


namespace HookShare
{
	enum { kAPIVersionMajor = 4 };


	enum class result_type : UInt32
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


	using PlayerInputHandler_CanProcess_t = result_type(RE::PlayerInputHandler* a_this, RE::InputEvent* a_event);
	using PlayerInputHandler_CanProcess_regs = std::vector<PlayerInputHandler_CanProcess_t*>;
	extern PlayerInputHandler_CanProcess_regs firstPersonStateRegs;
	extern PlayerInputHandler_CanProcess_regs thirdPersonStateRegs;
	extern PlayerInputHandler_CanProcess_regs favoritesRegs;
	extern PlayerInputHandler_CanProcess_regs movementRegs;
	extern PlayerInputHandler_CanProcess_regs lookRegs;
	extern PlayerInputHandler_CanProcess_regs sprintRegs;
	extern PlayerInputHandler_CanProcess_regs readyWeaponRegs;
	extern PlayerInputHandler_CanProcess_regs autoMoveRegs;
	extern PlayerInputHandler_CanProcess_regs toggleRunRegs;
	extern PlayerInputHandler_CanProcess_regs activateRegs;
	extern PlayerInputHandler_CanProcess_regs jumpRegs;
	extern PlayerInputHandler_CanProcess_regs shoutRegs;
	extern PlayerInputHandler_CanProcess_regs attackBlockRegs;
	extern PlayerInputHandler_CanProcess_regs runRegs;
	extern PlayerInputHandler_CanProcess_regs sneakRegs;

	/* REGS BEGIN */

	using RegisterForCanProcess_t = void(Hook a_hookType, PlayerInputHandler_CanProcess_t* a_func);
	void RegisterForCanProcess(Hook a_hookType, PlayerInputHandler_CanProcess_t* a_func);

	/* REGS END */
}

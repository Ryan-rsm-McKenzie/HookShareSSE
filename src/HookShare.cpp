#include "HookShare.h"

#include <vector>  // vector


namespace HookShare
{
	std::vector<_PlayerInputHandler_CanProcess_t*> firstPersonStateRegs;
	std::vector<_PlayerInputHandler_CanProcess_t*> thirdPersonStateRegs;
	std::vector<_PlayerInputHandler_CanProcess_t*> favoritesRegs;
	std::vector<_PlayerInputHandler_CanProcess_t*> movementRegs;
	std::vector<_PlayerInputHandler_CanProcess_t*> lookRegs;
	std::vector<_PlayerInputHandler_CanProcess_t*> sprintRegs;
	std::vector<_PlayerInputHandler_CanProcess_t*> readyWeaponRegs;
	std::vector<_PlayerInputHandler_CanProcess_t*> autoMoveRegs;
	std::vector<_PlayerInputHandler_CanProcess_t*> toggleRunRegs;
	std::vector<_PlayerInputHandler_CanProcess_t*> activateRegs;
	std::vector<_PlayerInputHandler_CanProcess_t*> jumpRegs;
	std::vector<_PlayerInputHandler_CanProcess_t*> shoutRegs;
	std::vector<_PlayerInputHandler_CanProcess_t*> attackBlockRegs;
	std::vector<_PlayerInputHandler_CanProcess_t*> runRegs;
	std::vector<_PlayerInputHandler_CanProcess_t*> sneakRegs;

	std::vector<_IAnimationGraphManager_ConstructBShkbAnimationGraph_t*> animationGraphEventRegs;


	void RegisterFunc(void* a_func, Hook a_hookType)
	{
		switch (a_hookType) {
		case Hook::kFirstPersonState:
		{
			_PlayerInputHandler_CanProcess_t* func = (_PlayerInputHandler_CanProcess_t*)(a_func);
			firstPersonStateRegs.push_back(func);
			break;
		}
		case Hook::kThirdPersonState:
		{
			_PlayerInputHandler_CanProcess_t* func = (_PlayerInputHandler_CanProcess_t*)(a_func);
			thirdPersonStateRegs.push_back(func);
			break;
		}
		case Hook::kFavorites:
		{
			_PlayerInputHandler_CanProcess_t* func = (_PlayerInputHandler_CanProcess_t*)(a_func);
			favoritesRegs.push_back(func);
			break;
		}
		case Hook::kMovement:
		{
			_PlayerInputHandler_CanProcess_t* func = (_PlayerInputHandler_CanProcess_t*)(a_func);
			movementRegs.push_back(func);
			break;
		}
		case Hook::kLook:
		{
			_PlayerInputHandler_CanProcess_t* func = (_PlayerInputHandler_CanProcess_t*)(a_func);
			lookRegs.push_back(func);
			break;
		}
		case Hook::kSprint:
		{
			_PlayerInputHandler_CanProcess_t* func = (_PlayerInputHandler_CanProcess_t*)(a_func);
			sprintRegs.push_back(func);
			break;
		}
		case Hook::kReadyWeapon:
		{
			_PlayerInputHandler_CanProcess_t* func = (_PlayerInputHandler_CanProcess_t*)(a_func);
			readyWeaponRegs.push_back(func);
			break;
		}
		case Hook::kAutoMove:
		{
			_PlayerInputHandler_CanProcess_t* func = (_PlayerInputHandler_CanProcess_t*)(a_func);
			autoMoveRegs.push_back(func);
			break;
		}
		case Hook::kToggleRun:
		{
			_PlayerInputHandler_CanProcess_t* func = (_PlayerInputHandler_CanProcess_t*)(a_func);
			toggleRunRegs.push_back(func);
			break;
		}
		case Hook::kActivate:
		{
			_PlayerInputHandler_CanProcess_t* func = (_PlayerInputHandler_CanProcess_t*)(a_func);
			activateRegs.push_back(func);
			break;
		}
		case Hook::kJump:
		{
			_PlayerInputHandler_CanProcess_t* func = (_PlayerInputHandler_CanProcess_t*)(a_func);
			jumpRegs.push_back(func);
			break;
		}
		case Hook::kShout:
		{
			_PlayerInputHandler_CanProcess_t* func = (_PlayerInputHandler_CanProcess_t*)(a_func);
			shoutRegs.push_back(func);
			break;
		}
		case Hook::kAttackBlock:
		{
			_PlayerInputHandler_CanProcess_t* func = (_PlayerInputHandler_CanProcess_t*)(a_func);
			attackBlockRegs.push_back(func);
			break;
		}
		case Hook::kRun:
		{
			_PlayerInputHandler_CanProcess_t* func = (_PlayerInputHandler_CanProcess_t*)(a_func);
			runRegs.push_back(func);
			break;
		}
		case Hook::kSneak:
		{
			_PlayerInputHandler_CanProcess_t* func = (_PlayerInputHandler_CanProcess_t*)(a_func);
			sneakRegs.push_back(func);
			break;
		}
		case Hook::kPlayerAnimationGraphEvent:
		{
			_IAnimationGraphManager_ConstructBShkbAnimationGraph_t* func = (_IAnimationGraphManager_ConstructBShkbAnimationGraph_t*)(a_func);
			animationGraphEventRegs.push_back(func);
			break;
		}
		}
	}


	void RegisterForCanProcess(_PlayerInputHandler_CanProcess_t* a_func, Hook a_hookType)
	{
		RegisterFunc(a_func, a_hookType);
	}


	void RegisterForAnimationGraphEvent(_IAnimationGraphManager_ConstructBShkbAnimationGraph_t* a_func, Hook a_type)
	{
		RegisterFunc(a_func, a_type);
	}
}

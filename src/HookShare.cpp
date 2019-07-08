#include "HookShare.h"

#include <vector>  // vector


namespace HookShare
{
	decltype(firstPersonStateRegs) firstPersonStateRegs;
	decltype(thirdPersonStateRegs) thirdPersonStateRegs;
	decltype(favoritesRegs) favoritesRegs;
	decltype(movementRegs) movementRegs;
	decltype(lookRegs) lookRegs;
	decltype(sprintRegs) sprintRegs;
	decltype(readyWeaponRegs) readyWeaponRegs;
	decltype(autoMoveRegs) autoMoveRegs;
	decltype(toggleRunRegs) toggleRunRegs;
	decltype(activateRegs) activateRegs;
	decltype(jumpRegs) jumpRegs;
	decltype(shoutRegs) shoutRegs;
	decltype(attackBlockRegs) attackBlockRegs;
	decltype(runRegs) runRegs;
	decltype(sneakRegs) sneakRegs;


	void RegisterFunc(Hook a_hookType, void* a_func)
	{
		switch (a_hookType) {
		case Hook::kFirstPersonState:
			{
				PlayerInputHandler_CanProcess_t* func = reinterpret_cast<PlayerInputHandler_CanProcess_t*>(a_func);
				firstPersonStateRegs.push_back(func);
			}
			break;
		case Hook::kThirdPersonState:
			{
				PlayerInputHandler_CanProcess_t* func = reinterpret_cast<PlayerInputHandler_CanProcess_t*>(a_func);
				thirdPersonStateRegs.push_back(func);
			}
			break;
		case Hook::kFavorites:
			{
				PlayerInputHandler_CanProcess_t* func = reinterpret_cast<PlayerInputHandler_CanProcess_t*>(a_func);
				favoritesRegs.push_back(func);
			}
			break;
		case Hook::kMovement:
			{
				PlayerInputHandler_CanProcess_t* func = reinterpret_cast<PlayerInputHandler_CanProcess_t*>(a_func);
				movementRegs.push_back(func);
			}
			break;
		case Hook::kLook:
			{
				PlayerInputHandler_CanProcess_t* func = reinterpret_cast<PlayerInputHandler_CanProcess_t*>(a_func);
				lookRegs.push_back(func);
			}
			break;
		case Hook::kSprint:
			{
				PlayerInputHandler_CanProcess_t* func = reinterpret_cast<PlayerInputHandler_CanProcess_t*>(a_func);
				sprintRegs.push_back(func);
			}
			break;
		case Hook::kReadyWeapon:
			{
				PlayerInputHandler_CanProcess_t* func = reinterpret_cast<PlayerInputHandler_CanProcess_t*>(a_func);
				readyWeaponRegs.push_back(func);
			}
			break;
		case Hook::kAutoMove:
			{
				PlayerInputHandler_CanProcess_t* func = reinterpret_cast<PlayerInputHandler_CanProcess_t*>(a_func);
				autoMoveRegs.push_back(func);
			}
			break;
		case Hook::kToggleRun:
			{
				PlayerInputHandler_CanProcess_t* func = reinterpret_cast<PlayerInputHandler_CanProcess_t*>(a_func);
				toggleRunRegs.push_back(func);
			}
			break;
		case Hook::kActivate:
			{
				PlayerInputHandler_CanProcess_t* func = reinterpret_cast<PlayerInputHandler_CanProcess_t*>(a_func);
				activateRegs.push_back(func);
			}
			break;
		case Hook::kJump:
			{
				PlayerInputHandler_CanProcess_t* func = reinterpret_cast<PlayerInputHandler_CanProcess_t*>(a_func);
				jumpRegs.push_back(func);
			}
			break;
		case Hook::kShout:
			{
				PlayerInputHandler_CanProcess_t* func = reinterpret_cast<PlayerInputHandler_CanProcess_t*>(a_func);
				shoutRegs.push_back(func);
			}
			break;
		case Hook::kAttackBlock:
			{
				PlayerInputHandler_CanProcess_t* func = reinterpret_cast<PlayerInputHandler_CanProcess_t*>(a_func);
				attackBlockRegs.push_back(func);
			}
			break;
		case Hook::kRun:
			{
				PlayerInputHandler_CanProcess_t* func = reinterpret_cast<PlayerInputHandler_CanProcess_t*>(a_func);
				runRegs.push_back(func);
			}
			break;
		case Hook::kSneak:
			{
				PlayerInputHandler_CanProcess_t* func = reinterpret_cast<PlayerInputHandler_CanProcess_t*>(a_func);
				sneakRegs.push_back(func);
			}
			break;
		}
	}


	void RegisterForCanProcess(Hook a_hookType, PlayerInputHandler_CanProcess_t* a_func)
	{
		switch (a_hookType) {
		case Hook::kFirstPersonState:
		case Hook::kThirdPersonState:
		case Hook::kFavorites:
		case Hook::kMovement:
		case Hook::kLook:
		case Hook::kSprint:
		case Hook::kReadyWeapon:
		case Hook::kAutoMove:
		case Hook::kToggleRun:
		case Hook::kActivate:
		case Hook::kJump:
		case Hook::kShout:
		case Hook::kAttackBlock:
		case Hook::kRun:
		case Hook::kSneak:
			RegisterFunc(a_hookType, a_func);
			break;
		default:
			_ERROR("Hook type was not valid for CanProcess (%i)!\n", a_hookType);
			break;
		}
	}
}

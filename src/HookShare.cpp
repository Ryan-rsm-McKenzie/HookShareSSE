#include "HookShare.h"


namespace HookShare
{
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
	std::vector<_PlayerInputHandler_CanProcess_t*> togglePOVRegs;


	void RegisterHook(_PlayerInputHandler_CanProcess_t* a_func, Hook a_hookType)
	{
		switch (a_hookType) {
		case kHook_Favorites:
			favoritesRegs.push_back(a_func);
			break;
		case kHook_Movement:
			movementRegs.push_back(a_func);
			break;
		case kHook_Look:
			lookRegs.push_back(a_func);
			break;
		case kHook_Sprint:
			sprintRegs.push_back(a_func);
			break;
		case kHook_ReadyWeapon:
			readyWeaponRegs.push_back(a_func);
			break;
		case kHook_AutoMove:
			autoMoveRegs.push_back(a_func);
			break;
		case kHook_ToggleRun:
			toggleRunRegs.push_back(a_func);
			break;
		case kHook_Activate:
			activateRegs.push_back(a_func);
			break;
		case kHook_Jump:
			jumpRegs.push_back(a_func);
			break;
		case kHook_Shout:
			shoutRegs.push_back(a_func);
			break;
		case kHook_AttackBlock:
			attackBlockRegs.push_back(a_func);
			break;
		case kHook_Run:
			runRegs.push_back(a_func);
			break;
		case kHook_Sneak:
			sneakRegs.push_back(a_func);
			break;
		case kHook_TogglePOV:
			togglePOVRegs.push_back(a_func);
			break;
		}
	}
}

#include "Hooks.h"

#include "skse64_common/SafeWrite.h"  // SafeWrite64

#include <vector>  // vector

#include "HookShare.h"

#include "RE/Offsets.h"
#include "RE/PlayerInputHandler.h"  // PlayerInputHandler


namespace Hooks
{
	template <uintptr_t offset, std::vector<HookShare::_PlayerInputHandler_CanProcess_t*>& regs>
	class PlayerInputHandler : public RE::PlayerInputHandler
	{
	public:
		typedef bool(PlayerInputHandler::*_CanProcess_t)(RE::InputEvent* a_event);
		static _CanProcess_t orig_CanProcess;


		bool hook_CanProcess(RE::InputEvent* a_event)
		{
			using HookShare::ReturnType;

			bool result = (this->*orig_CanProcess)(a_event);

			if (a_event && !regs.empty()) {
				UInt32 retFalse = 0;
				UInt32 retTrue = 0;
				for (auto& reg : regs) {
					ReturnType ret = reg(this, a_event);
					switch (ret) {
					case ReturnType::kReturnType_False:
						++retFalse;
						break;
					case ReturnType::kReturnType_True:
						++retTrue;
						break;
					case ReturnType::kReturnType_Continue:
					default:
						break;
					}
				}

				if (retFalse) {
					return false;
				} else if (retTrue) {
					return true;
				} else {
					return result;
				}
			}

			return result;
		}


		static void installHook()
		{
			RelocPtr<_CanProcess_t> vtbl_CanProcess(offset);
			orig_CanProcess = *vtbl_CanProcess;
			SafeWrite64(vtbl_CanProcess.GetUIntPtr(), GetFnAddr(&hook_CanProcess));
		}
	};


	template <uintptr_t offset, std::vector<HookShare::_PlayerInputHandler_CanProcess_t*>& regs> typename PlayerInputHandler<offset, regs>::_CanProcess_t PlayerInputHandler<offset, regs>::orig_CanProcess;
	typedef PlayerInputHandler<RE::FIRST_PERSON_STATE_VTBL + (0x8 * 0x8) + 0x10 + (0x1 * 0x8), HookShare::firstPersonStateRegs>	FirstPersonStateHandlerEx;
	typedef PlayerInputHandler<RE::THIRD_PERSON_STATE_VTBL + (0xF * 0x8) + 0x10 + (0x1 * 0x8), HookShare::thirdPersonStateRegs>	ThirdPersonStateHandlerEx;
	typedef PlayerInputHandler<RE::FAVORITES_HANDLER_VTBL + (0x1 * 0x8), HookShare::favoritesRegs>								FavoritesHandlerEx;
	typedef PlayerInputHandler<RE::MOVEMENT_HANDLER_VTBL + (0x1 * 0x8), HookShare::movementRegs>								MovementHandlerEx;
	typedef PlayerInputHandler<RE::LOOK_HANDLER_VTBL + (0x1 * 0x8), HookShare::lookRegs>										LookHandlerEx;
	typedef PlayerInputHandler<RE::SPRINT_HANDLER_VTBL + (0x1 * 0x8), HookShare::sprintRegs>									SprintHandlerEx;
	typedef PlayerInputHandler<RE::READY_WEAPON_HANDLER_VTBL + (0x1 * 0x8), HookShare::readyWeaponRegs>							ReadyWeaponHandlerEx;
	typedef PlayerInputHandler<RE::AUTO_MOVE_HANDLER_VTBL + (0x1 * 0x8), HookShare::autoMoveRegs>								AutoMoveHandlerEx;
	typedef PlayerInputHandler<RE::TOGGLE_RUN_HANDLER_VTBL + (0x1 * 0x8), HookShare::toggleRunRegs>								ToggleRunHandlerEx;
	typedef PlayerInputHandler<RE::ACTIVATE_HANDLER_VTBL + (0x1 * 0x8), HookShare::activateRegs>								ActivateHandlerEx;
	typedef PlayerInputHandler<RE::JUMP_HANDLER_VTBL + (0x1 * 0x8), HookShare::jumpRegs>										JumpHandlerEx;
	typedef PlayerInputHandler<RE::SHOUT_HANDLER_VTBL + (0x1 * 0x8), HookShare::shoutRegs>										ShoutHandlerEx;
	typedef PlayerInputHandler<RE::ATTACK_BLOCK_HANDLER_VTBL + (0x1 * 0x8), HookShare::attackBlockRegs>							AttackBlockHandlerEx;
	typedef PlayerInputHandler<RE::RUN_HANDLER_VTBL + (0x1 * 0x8), HookShare::runRegs>											RunHandlerEx;
	typedef PlayerInputHandler<RE::SNEAK_HANDLER_VTBL + (0x1 * 0x8), HookShare::sneakRegs>										SneakHandlerEx;


	void InstallHooks()
	{
		FirstPersonStateHandlerEx::installHook();
		ThirdPersonStateHandlerEx::installHook();
		FavoritesHandlerEx::installHook();
		MovementHandlerEx::installHook();
		LookHandlerEx::installHook();
		SprintHandlerEx::installHook();
		ReadyWeaponHandlerEx::installHook();
		AutoMoveHandlerEx::installHook();
		ToggleRunHandlerEx::installHook();
		ActivateHandlerEx::installHook();
		JumpHandlerEx::installHook();
		ShoutHandlerEx::installHook();
		AttackBlockHandlerEx::installHook();
		RunHandlerEx::installHook();
		SneakHandlerEx::installHook();
	}
}

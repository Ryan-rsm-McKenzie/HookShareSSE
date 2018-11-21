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
		typedef bool(PlayerInputHandler::*_CanProcess_t)(InputEvent* a_event);
		static _CanProcess_t orig_CanProcess;


		bool hook_CanProcess(InputEvent* a_event)
		{
			using HookShare::ReturnType;

			if (a_event) {
				UInt32 retFalse = 0;
				UInt32 retTrue = 0;
				UInt32 retContinue = 0;
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
						++retContinue;
						break;
					}
				}

				if (retFalse) {
					return false;
				} else if (retTrue) {
					return true;
				} else {
					return (this->*orig_CanProcess)(a_event);
				}
			}
			return (this->*orig_CanProcess)(a_event);
		}


		static void installHook()
		{
			RelocPtr<_CanProcess_t> vtbl_CanProcess(offset);
			orig_CanProcess = *vtbl_CanProcess;
			SafeWrite64(vtbl_CanProcess.GetUIntPtr(), GetFnAddr(&hook_CanProcess));
		}
	};


	template <uintptr_t offset, std::vector<HookShare::_PlayerInputHandler_CanProcess_t*>& regs> typename PlayerInputHandler<offset, regs>::_CanProcess_t PlayerInputHandler<offset, regs>::orig_CanProcess;
	typedef PlayerInputHandler<FAVORITES_HANDLER_VTBL_META + 0x10, HookShare::favoritesRegs>		FavoritesHandlerEx;
	typedef PlayerInputHandler<MOVEMENT_HANDLER_VTBL_META + 0x10, HookShare::movementRegs>			MovementHandlerEx;
	typedef PlayerInputHandler<LOOK_HANDLER_VTBL_META + 0x10, HookShare::lookRegs>					LookHandlerEx;
	typedef PlayerInputHandler<SPRINT_HANDLER_VTBL_META + 0x10, HookShare::sprintRegs>				SprintHandlerEx;
	typedef PlayerInputHandler<READY_WEAPON_HANDLER_VTBL_META + 0x10, HookShare::readyWeaponRegs>	ReadyWeaponHandlerEx;
	typedef PlayerInputHandler<AUTO_MOVE_HANDLER_VTBL_META + 0x10, HookShare::autoMoveRegs>			AutoMoveHandlerEx;
	typedef PlayerInputHandler<TOGGLE_RUN_HANDLER_VTBL_META + 0x10, HookShare::toggleRunRegs>		ToggleRunHandlerEx;
	typedef PlayerInputHandler<ACTIVATE_HANDLER_VTBL_META + 0x10, HookShare::activateRegs>			ActivateHandlerEx;
	typedef PlayerInputHandler<JUMP_HANDLER_VTBL_META + 0x10, HookShare::jumpRegs>					JumpHandlerEx;
	typedef PlayerInputHandler<SHOUT_HANDLER_VTBL_META + 0x10, HookShare::shoutRegs>				ShoutHandlerEx;
	typedef PlayerInputHandler<ATTACK_BLOCK_HANDLER_VTBL_META + 0x10, HookShare::attackBlockRegs>	AttackBlockHandlerEx;
	typedef PlayerInputHandler<RUN_HANDLER_VTBL_META + 0x10, HookShare::runRegs>					RunHandlerEx;
	typedef PlayerInputHandler<SNEAK_HANDLER_VTBL_META + 0x10, HookShare::sneakRegs>				SneakHandlerEx;
	typedef PlayerInputHandler<TOGGLE_POV_HANDLER_VTBL_META + 0x10, HookShare::togglePOVRegs>		TogglePOVHandlerEx;


	void InstallHooks()
	{
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
		TogglePOVHandlerEx::installHook();
	}
}

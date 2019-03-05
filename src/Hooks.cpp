#include "Hooks.h"

#include "skse64_common/BranchTrampoline.h"  // g_localTrampoline
#include "skse64_common/Relocation.h"  // RelocAddr
#include "skse64_common/SafeWrite.h"  // SafeWrite8
#include "xbyak/xbyak.h"

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
					case ReturnType::kFalse:
						++retFalse;
						break;
					case ReturnType::kTrue:
						++retTrue;
						break;
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
	using FirstPersonStateHandlerEx = PlayerInputHandler<RE::FIRST_PERSON_STATE_VTBL + (0x8 * 0x8) + 0x10 + (0x1 * 0x8), HookShare::firstPersonStateRegs>;
	using ThirdPersonStateHandlerEx = PlayerInputHandler<RE::THIRD_PERSON_STATE_VTBL + (0xF * 0x8) + 0x10 + (0x1 * 0x8), HookShare::thirdPersonStateRegs>;
	using FavoritesHandlerEx = PlayerInputHandler<RE::FAVORITES_HANDLER_VTBL + (0x1 * 0x8), HookShare::favoritesRegs>;
	using MovementHandlerEx = PlayerInputHandler<RE::MOVEMENT_HANDLER_VTBL + (0x1 * 0x8), HookShare::movementRegs>;
	using LookHandlerEx = PlayerInputHandler<RE::LOOK_HANDLER_VTBL + (0x1 * 0x8), HookShare::lookRegs>;
	using SprintHandlerEx = PlayerInputHandler<RE::SPRINT_HANDLER_VTBL + (0x1 * 0x8), HookShare::sprintRegs>;
	using ReadyWeaponHandlerEx = PlayerInputHandler<RE::READY_WEAPON_HANDLER_VTBL + (0x1 * 0x8), HookShare::readyWeaponRegs>;
	using AutoMoveHandlerEx = PlayerInputHandler<RE::AUTO_MOVE_HANDLER_VTBL + (0x1 * 0x8), HookShare::autoMoveRegs>;
	using ToggleRunHandlerEx = PlayerInputHandler<RE::TOGGLE_RUN_HANDLER_VTBL + (0x1 * 0x8), HookShare::toggleRunRegs>;
	using ActivateHandlerEx = PlayerInputHandler<RE::ACTIVATE_HANDLER_VTBL + (0x1 * 0x8), HookShare::activateRegs>;
	using JumpHandlerEx = PlayerInputHandler<RE::JUMP_HANDLER_VTBL + (0x1 * 0x8), HookShare::jumpRegs>;
	using ShoutHandlerEx = PlayerInputHandler<RE::SHOUT_HANDLER_VTBL + (0x1 * 0x8), HookShare::shoutRegs>;
	using AttackBlockHandlerEx = PlayerInputHandler<RE::ATTACK_BLOCK_HANDLER_VTBL + (0x1 * 0x8), HookShare::attackBlockRegs>;
	using RunHandlerEx = PlayerInputHandler<RE::RUN_HANDLER_VTBL + (0x1 * 0x8), HookShare::runRegs>;
	using SneakHandlerEx = PlayerInputHandler<RE::SNEAK_HANDLER_VTBL + (0x1 * 0x8), HookShare::sneakRegs>;


	void PatchMiscStatHandlers()
	{
		constexpr uintptr_t TARGET_FUNC = 0x001F7BF0;
		RelocAddr<uintptr_t> target(TARGET_FUNC + 0x14);
		struct Patch : Xbyak::CodeGenerator
		{
			Patch(void* a_buf) : Xbyak::CodeGenerator(1024, a_buf)
			{
				or (r11d, 0x0F);
			}
		};
		void* patchBuf = g_localTrampoline.StartAlloc();
		Patch patch(patchBuf);
		g_localTrampoline.EndAlloc(patch.getCurr());
		assert(patch.getSize() == 4);
		for (UInt32 i = 0; i < patch.getSize(); ++i) {
			SafeWrite8(target.GetUIntPtr() + i, patch.getCode()[i]);
		}
		_DMESSAGE("[DEBUG] Installed patch for misc stat event dispatchers");
	}


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

		PatchMiscStatHandlers();
	}
}

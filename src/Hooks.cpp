#include "Hooks.h"

#include "skse64_common/BranchTrampoline.h"  // g_localTrampoline
#include "skse64_common/SafeWrite.h"  // SafeWrite8
#include "xbyak/xbyak.h"

#include <cstdint>  // uintptr_t
#include <vector>  // vector

#include "HookShare.h"

#include "RE/Skyrim.h"
#include "REL/Relocation.h"


namespace Hooks
{
	template <std::uintptr_t offset, HookShare::PlayerInputHandler_CanProcess_regs& regs>
	class PlayerInputHandler : public RE::PlayerInputHandler
	{
	public:
		using func_t = function_type_t<decltype(&RE::PlayerInputHandler::CanProcess)>;
		static inline func_t* func;


		bool hook_CanProcess(RE::InputEvent* a_event)
		{
			using HookShare::result_type;

			bool result = func(this, a_event);

			if (a_event && !regs.empty()) {
				UInt32 retFalse = 0;
				UInt32 retTrue = 0;
				for (auto& reg : regs) {
					switch (reg(this, a_event)) {
					case result_type::kFalse:
						++retFalse;
						break;
					case result_type::kTrue:
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
			REL::Offset<func_t**> vFunc(offset);
			func = *vFunc;
			SafeWrite64(vFunc.GetAddress(), GetFnAddr(&hook_CanProcess));
		}
	};


	using FirstPersonStateHandlerEx = PlayerInputHandler<RE::Offset::FirstPersonState::Vtbl + (0x8 * 0x8) + 0x10 + (0x1 * 0x8), HookShare::firstPersonStateRegs>;
	using ThirdPersonStateHandlerEx = PlayerInputHandler<RE::Offset::ThirdPersonState::Vtbl + (0xF * 0x8) + 0x10 + (0x1 * 0x8), HookShare::thirdPersonStateRegs>;
	using FavoritesHandlerEx = PlayerInputHandler<RE::Offset::FavoritesHandler::Vtbl + (0x1 * 0x8), HookShare::favoritesRegs>;
	using MovementHandlerEx = PlayerInputHandler<RE::Offset::MovementHandler::Vtbl + (0x1 * 0x8), HookShare::movementRegs>;
	using LookHandlerEx = PlayerInputHandler<RE::Offset::LookHandler::Vtbl + (0x1 * 0x8), HookShare::lookRegs>;
	using SprintHandlerEx = PlayerInputHandler<RE::Offset::SprintHandler::Vtbl + (0x1 * 0x8), HookShare::sprintRegs>;
	using ReadyWeaponHandlerEx = PlayerInputHandler<RE::Offset::ReadyWeaponHandler::Vtbl + (0x1 * 0x8), HookShare::readyWeaponRegs>;
	using AutoMoveHandlerEx = PlayerInputHandler<RE::Offset::AutoMoveHandler::Vtbl + (0x1 * 0x8), HookShare::autoMoveRegs>;
	using ToggleRunHandlerEx = PlayerInputHandler<RE::Offset::ToggleRunHandler::Vtbl + (0x1 * 0x8), HookShare::toggleRunRegs>;
	using ActivateHandlerEx = PlayerInputHandler<RE::Offset::ActivateHandler::Vtbl + (0x1 * 0x8), HookShare::activateRegs>;
	using JumpHandlerEx = PlayerInputHandler<RE::Offset::JumpHandler::Vtbl + (0x1 * 0x8), HookShare::jumpRegs>;
	using ShoutHandlerEx = PlayerInputHandler<RE::Offset::ShoutHandler::Vtbl + (0x1 * 0x8), HookShare::shoutRegs>;
	using AttackBlockHandlerEx = PlayerInputHandler<RE::Offset::AttackBlockHandler::Vtbl + (0x1 * 0x8), HookShare::attackBlockRegs>;
	using RunHandlerEx = PlayerInputHandler<RE::Offset::RunHandler::Vtbl + (0x1 * 0x8), HookShare::runRegs>;
	using SneakHandlerEx = PlayerInputHandler<RE::Offset::SneakHandler::Vtbl + (0x1 * 0x8), HookShare::sneakRegs>;


	void PatchMiscStatHandlers()
	{
		// E8 ? ? ? ? 80 7B 0A 00
		constexpr std::uintptr_t TARGET_FUNC = 0x001F7BF0;	// 1_5_62
		REL::Offset<std::uintptr_t> target(TARGET_FUNC + 0x14);
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
			SafeWrite8(target.GetAddress() + i, patch.getCode()[i]);
		}
		_DMESSAGE("Installed patch for misc stat event dispatchers");
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

		//PatchMiscStatHandlers();
	}
}

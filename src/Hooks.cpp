#include "Hooks.h"

#include "skse64_common/BranchTrampoline.h"  // g_localTrampoline
#include "skse64_common/SafeWrite.h"  // SafeWrite8
#include "xbyak/xbyak.h"

#include <cstdint>  // uintptr_t
#include <vector>  // vector

#include "HookShare.h"

#include "RE/Skyrim.h"
#include "REL/Relocation.h"

namespace RE {
	class InputEvent;
}

// from skse64_common/Utilities
template <typename T>
uintptr_t GetFnAddr(T src)
{
	union
	{
		uintptr_t	u;
		T			t;
	} data;

	data.t = src;

	return data.u;
}

namespace Hooks
{
	template <HookShare::PlayerInputHandler_CanProcess_regs& regs>
	class PlayerInputHandler : public RE::PlayerInputHandler
	{
	public:
		//using func_t = function_type_t<decltype(&RE::PlayerInputHandler::CanProcess)>;
		typedef bool (RE::PlayerInputHandler::*func_t)(RE::InputEvent * a_event);
		static inline func_t func;


		bool hook_CanProcess(RE::InputEvent* a_event)
		{
			using HookShare::result_type;

			bool result = (this->*func)(a_event);

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

		static void installHook(const uintptr_t offset)
		{
			REL::Offset<func_t*> vFunc(offset);
			func = *vFunc;
			SafeWrite64(vFunc.GetAddress(), GetFnAddr(&hook_CanProcess));
		}
	};


	using FirstPersonStateHandlerEx = PlayerInputHandler<HookShare::firstPersonStateRegs>;
	using ThirdPersonStateHandlerEx = PlayerInputHandler<HookShare::thirdPersonStateRegs>;
	using FavoritesHandlerEx = PlayerInputHandler<HookShare::favoritesRegs>;
	using MovementHandlerEx = PlayerInputHandler<HookShare::movementRegs>;
	using LookHandlerEx = PlayerInputHandler<HookShare::lookRegs>;
	using SprintHandlerEx = PlayerInputHandler<HookShare::sprintRegs>;
	using ReadyWeaponHandlerEx = PlayerInputHandler<HookShare::readyWeaponRegs>;
	using AutoMoveHandlerEx = PlayerInputHandler<HookShare::autoMoveRegs>;
	using ToggleRunHandlerEx = PlayerInputHandler<HookShare::toggleRunRegs>;
	using ActivateHandlerEx = PlayerInputHandler<HookShare::activateRegs>;
	using JumpHandlerEx = PlayerInputHandler<HookShare::jumpRegs>;
	using ShoutHandlerEx = PlayerInputHandler<HookShare::shoutRegs>;
	using AttackBlockHandlerEx = PlayerInputHandler<HookShare::attackBlockRegs>;
	using RunHandlerEx = PlayerInputHandler<HookShare::runRegs>;
	using SneakHandlerEx = PlayerInputHandler<HookShare::sneakRegs>;


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
		FirstPersonStateHandlerEx::installHook(RE::Offset::FirstPersonState::Vtbl.GetOffset() + (0x8 * 0x8) + 0x10 + (0x1 * 0x8));
		ThirdPersonStateHandlerEx::installHook(RE::Offset::ThirdPersonState::Vtbl.GetOffset() + (0xF * 0x8) + 0x10 + (0x1 * 0x8));
		FavoritesHandlerEx::installHook(RE::Offset::FavoritesHandler::Vtbl.GetOffset() + (0x1 * 0x8));
		MovementHandlerEx::installHook(RE::Offset::MovementHandler::Vtbl.GetOffset() + (0x1 * 0x8));
		LookHandlerEx::installHook(RE::Offset::LookHandler::Vtbl.GetOffset() + (0x1 * 0x8));
		SprintHandlerEx::installHook(RE::Offset::SprintHandler::Vtbl.GetOffset() + (0x1 * 0x8));
		ReadyWeaponHandlerEx::installHook(RE::Offset::ReadyWeaponHandler::Vtbl.GetOffset() + (0x1 * 0x8));
		AutoMoveHandlerEx::installHook(RE::Offset::AutoMoveHandler::Vtbl.GetOffset() + (0x1 * 0x8));
		ToggleRunHandlerEx::installHook(RE::Offset::ToggleRunHandler::Vtbl.GetOffset() + (0x1 * 0x8));
		ActivateHandlerEx::installHook(RE::Offset::ActivateHandler::Vtbl.GetOffset() + (0x1 * 0x8));
		JumpHandlerEx::installHook(RE::Offset::JumpHandler::Vtbl.GetOffset() + (0x1 * 0x8));
		ShoutHandlerEx::installHook(RE::Offset::ShoutHandler::Vtbl.GetOffset() + (0x1 * 0x8));
		AttackBlockHandlerEx::installHook(RE::Offset::AttackBlockHandler::Vtbl.GetOffset() + (0x1 * 0x8));
		RunHandlerEx::installHook(RE::Offset::RunHandler::Vtbl.GetOffset() + (0x1 * 0x8));
		SneakHandlerEx::installHook(RE::Offset::SneakHandler::Vtbl.GetOffset() + (0x1 * 0x8));

		//PatchMiscStatHandlers();
	}
}

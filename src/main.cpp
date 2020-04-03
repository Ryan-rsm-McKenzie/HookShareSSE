#include "skse64_common/BranchTrampoline.h"  // g_localTrampoline
#include "skse64_common/skse_version.h"  // RUNTIME_VERSION

#include "Hooks.h"  // InstallHooks
#include "HookShare.h"  // RegisterHook
#include "version.h"  // VERSION_VERSTRING

#include "SKSE/API.h"


void MessageHandler(SKSE::MessagingInterface::Message* a_msg)
{
	switch (a_msg->type) {
	case SKSE::MessagingInterface::kDataLoaded:
		{
			auto messaging = SKSE::GetMessagingInterface();
			messaging->Dispatch(HookShare::kType_CanProcess, HookShare::RegisterForCanProcess, HookShare::kAPIVersionMajor, 0);
		}
		break;
	}
}


extern "C" {
	bool SKSEPlugin_Query(const SKSE::QueryInterface* a_skse, SKSE::PluginInfo* a_info)
	{
		SKSE::Logger::OpenRelative(FOLDERID_Documents, L"\\My Games\\Skyrim Special Edition\\SKSE\\HookShareSSE.log");
		SKSE::Logger::SetPrintLevel(SKSE::Logger::Level::kDebugMessage);
		SKSE::Logger::SetFlushLevel(SKSE::Logger::Level::kDebugMessage);
		SKSE::Logger::UseLogStamp(true);

		_MESSAGE("HookShareSSE v%s", HSHR_VERSION_VERSTRING);

		a_info->infoVersion = SKSE::PluginInfo::kVersion;
		a_info->name = "HookShareSSE";
		a_info->version = HookShare::kAPIVersionMajor;

		if (a_skse->IsEditor()) {
			_FATALERROR("Loaded in editor, marking as incompatible!\n");
			return false;
		}
		
#if 0
		// 
		if (!a_skse->RuntimeVersion().Compare(SKSE::RUNTIME_1_5_73))
		if (!a_skse->RuntimeVersion().Compare(SKSE::RUNTIME_1_5_80))
		if (!a_skse->RuntimeVersion().Compare(SKSE::RUNTIME_1_5_97))
		{
			_FATALERROR("Unsupported runtime version %08X!\n", a_skse->RuntimeVersion());
			return false;
		}
#endif
		

		return true;
	}


	bool SKSEPlugin_Load(const SKSE::LoadInterface* a_skse)
	{
		_MESSAGE("HookShareSSE loaded");

		if (!SKSE::Init(a_skse)) {
			return false;
		}

		if (g_localTrampoline.Create(1024 * 8)) {
			_MESSAGE("Local trampoline creation successfull");
		} else {
			_MESSAGE("Local trampoline creation failed!\n");
			return false;
		}

		auto messaging = SKSE::GetMessagingInterface();
		if (messaging->RegisterListener("SKSE", MessageHandler)) {
			_MESSAGE("Messaging interface registration successful");
		} else {
			_FATALERROR("Messaging interface registration failed!\n");
			return false;
		}

		Hooks::InstallHooks();
		_MESSAGE("Hooks installed");

		return true;
	}
};

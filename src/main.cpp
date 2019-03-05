#include "common/IDebugLog.h"  // IDebugLog
#include "skse64_common/BranchTrampoline.h"  // g_localTrampoline
#include "skse64_common/skse_version.h"  // RUNTIME_VERSION
#include "skse64/PluginAPI.h"  // PluginHandle, SKSEMessagingInterface, SKSEInterface, PluginInfo

#include <ShlObj.h>  // CSIDL_MYDOCUMENTS

#include "Hooks.h"  // InstallHooks
#include "HookShare.h"  // RegisterHook
#include "version.h"  // HOOKSHARESSE_VERSION_VERSTRING


static PluginHandle	g_pluginHandle = kPluginHandle_Invalid;
static SKSEMessagingInterface* g_messaging = 0;


void MessageHandler(SKSEMessagingInterface::Message* a_msg)
{
	switch (a_msg->type) {
	case SKSEMessagingInterface::kMessage_DataLoaded:
		g_messaging->Dispatch(g_pluginHandle, HookShare::kType_CanProcess, HookShare::RegisterForCanProcess, HOOK_SHARE_API_VERSION_MAJOR, 0);
		break;
	}
}


extern "C" {
	bool SKSEPlugin_Query(const SKSEInterface* a_skse, PluginInfo* a_info)
	{
		gLog.OpenRelative(CSIDL_MYDOCUMENTS, "\\My Games\\Skyrim Special Edition\\SKSE\\HookShareSSE.log");
		gLog.SetPrintLevel(IDebugLog::kLevel_DebugMessage);
		gLog.SetLogLevel(IDebugLog::kLevel_DebugMessage);

		_MESSAGE("HookShareSSE v%s", HOOKSHARESSE_VERSION_VERSTRING);

		a_info->infoVersion = PluginInfo::kInfoVersion;
		a_info->name = "HookShareSSE";
		a_info->version = HOOK_SHARE_API_VERSION_MAJOR;

		g_pluginHandle = a_skse->GetPluginHandle();

		if (a_skse->isEditor) {
			_FATALERROR("[FATAL ERROR] Loaded in editor, marking as incompatible!\n");
			return false;
		}

		if (a_skse->runtimeVersion != RUNTIME_VERSION_1_5_62) {
			_FATALERROR("[FATAL ERROR] Unsupported runtime version %08X!\n", a_skse->runtimeVersion);
			return false;
		}

		return true;
	}


	bool SKSEPlugin_Load(const SKSEInterface* a_skse)
	{
		_MESSAGE("[MESSAGE] HookShareSSE loaded");

		if (g_localTrampoline.Create(1024 * 8)) {
			_MESSAGE("[MESSAGE] Local trampoline creation successfull");
		} else {
			_MESSAGE("[FATAL ERROR] Local trampoline creation failed!\n");
			return false;
		}

		g_messaging = (SKSEMessagingInterface*)a_skse->QueryInterface(kInterface_Messaging);
		if (g_messaging->RegisterListener(g_pluginHandle, "SKSE", MessageHandler)) {
			_MESSAGE("[MESSAGE] Messaging interface registration successful");
		} else {
			_FATALERROR("[FATAL ERROR] Messaging interface registration failed!\n");
			return false;
		}

		Hooks::InstallHooks();
		_MESSAGE("[MESSAGE] Hooks installed");

		return true;
	}
};

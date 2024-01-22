#include "main.hpp"
#include "bitbuf.h"
#include "../minhook-master/include/MinHook.h"
#include "ivdebugoverlay.h"
#include "drawing.h"
CVSPlugin g_VSPlugin;
EXPOSE_SINGLE_INTERFACE_GLOBALVAR(CVSPlugin, IServerPluginCallbacks, INTERFACEVERSION_ISERVERPLUGINCALLBACKS, g_VSPlugin)

#define REGISTERMESSAGE(fn) CUserMsg_Register(usermessages, #fn, 1); CUserMsg_HookMessage(usermessages, #fn, fn);

IVDebugOverlay* debugoverlay;

void* usermessages = (void*)0x24277D50;

typedef void(__cdecl* umsghook_t)(bf_read&);

//CUserMessages::Register
typedef void(__thiscall* CUserMsg_Register_t)(void* this_, const char* name, int size);
CUserMsg_Register_t CUserMsg_Register = (CUserMsg_Register_t)0x241213C0;
// sub_24121140
typedef void(__thiscall* CUserMsg_HookMessage_t)(void* this_, const char* name, umsghook_t function);
CUserMsg_HookMessage_t CUserMsg_HookMessage = (CUserMsg_HookMessage_t)0x24121140;
// sub_241211C0 dispatchmessage

typedef bool(__thiscall* DispatchUserMessage_t)(void* this_, int msg_type, bf_read& msg_data);
DispatchUserMessage_t CUserMsg_DispatchMessage = (DispatchUserMessage_t)0x241211C0;


CVSPlugin::CVSPlugin() : m_iClientCommandIndex(0)
{
}

CVSPlugin::~CVSPlugin()
{
}


bool CVSPlugin::Load(CreateInterfaceFn interfaceFactory, CreateInterfaceFn gameServerFactory)
{
	debugoverlay = (IVDebugOverlay*)interfaceFactory(VDEBUG_OVERLAY_INTERFACE_VERSION, NULL);
	REGISTERMESSAGE(AddEntityTextOverlay);
	REGISTERMESSAGE(AddBoxOverlay);
	REGISTERMESSAGE(AddTriangleOverlay);
	REGISTERMESSAGE(AddLineOverlay);
	REGISTERMESSAGE(AddTextOverlay);
	REGISTERMESSAGE(AddScreenTextOverlay);
	REGISTERMESSAGE(AddSweptBoxOverlay);
	REGISTERMESSAGE(ClearDeadOverlays);
	REGISTERMESSAGE(ClearAllOverlays);
	REGISTERMESSAGE(AddTextOverlayRGB);
	return true;
}

void CVSPlugin::Unload(void)
{
}


void CVSPlugin::Pause(void)
{
}

void CVSPlugin::UnPause(void)
{
}

const char* CVSPlugin::GetPluginDescription(void)
{
	return "";
}

void CVSPlugin::LevelInit(char const* pMapName)
{
}

void CVSPlugin::ServerActivate(edict_t* pEdictList, int edictCount, int clientMax)
{
}

void CVSPlugin::GameFrame(bool simulating)
{
}

void CVSPlugin::LevelShutdown(void)
{
}

void CVSPlugin::ClientActive(edict_t* pEntity)
{
}

void CVSPlugin::ClientDisconnect(edict_t* pEntity)
{
}

void CVSPlugin::ClientPutInServer(edict_t* pEntity, char const* playername)
{
}

void CVSPlugin::SetCommandClient(int index)
{
}

void CVSPlugin::ClientSettingsChanged(edict_t* pEdict)
{
}

PLUGIN_RESULT CVSPlugin::ClientConnect(bool* bAllowConnect, edict_t* pEntity, const char* pszName, const char* pszAddress, char* reject, int maxrejectlen)
{
	return PLUGIN_CONTINUE;
}

PLUGIN_RESULT CVSPlugin::ClientCommand(edict_t* pEntity)
{
	return PLUGIN_CONTINUE;
}

PLUGIN_RESULT CVSPlugin::NetworkIDValidated(const char* pszUserName, const char* pszNetworkID)
{
	return PLUGIN_CONTINUE;
}
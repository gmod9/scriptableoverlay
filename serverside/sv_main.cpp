#include "main.hpp"
#include "../minhook-master/include/MinHook.h"
#include "iface.hpp"
CVSPlugin g_VSPlugin;
EXPOSE_SINGLE_INTERFACE_GLOBALVAR(CVSPlugin, IServerPluginCallbacks, INTERFACEVERSION_ISERVERPLUGINCALLBACKS, g_VSPlugin)

int first = 0;
IVEngineServer* engine = NULL;
void* usermessages = (void*)0x225CB498;
CUserMsg_Register_t CUserMsg_Register = (CUserMsg_Register_t)0x222A5290;

CVSPlugin::CVSPlugin() : m_iClientCommandIndex(0)
{
}

CVSPlugin::~CVSPlugin()
{
}

bool CVSPlugin::Load(CreateInterfaceFn interfaceFactory, CreateInterfaceFn gameServerFactory)
{
	engine = (IVEngineServer*)interfaceFactory(INTERFACEVERSION_VENGINESERVER, NULL);
	if (!engine) {
		return false;
	}
	first = *(int*)((char*)usermessages + 20);
	MH_Initialize();
	InitLua();
	return true;
}

void CVSPlugin::Unload(void)
{
	MH_Uninitialize();
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
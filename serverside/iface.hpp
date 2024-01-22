
typedef void(__thiscall* CUserMsg_Register_t)(void* this_, const char* name, int size);
#define REGISTERMESSAGE(x) CUserMsg_Register(usermessages, #x, -1);
extern IVEngineServer* engine;
extern int first;
extern void* usermessages;
extern CUserMsg_Register_t CUserMsg_Register;
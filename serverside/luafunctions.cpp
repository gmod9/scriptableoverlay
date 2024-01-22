#include "main.hpp"
#include "../minhook-master/include/Minhook.h"
#include "filter.hpp"
#include "bitbuf.h"
#ifdef __cplusplus 
extern "C" {
#endif
#include "../lua/lua.h"
#include "../lua/lualib.h"
#include "../lua/lauxlib.h"
#ifdef __cplusplus 
}
#endif
void* stringlib = (void*)0x22426650; // hooking point

typedef int(__cdecl *openstring_t)(lua_State* L);
openstring_t jumpback = NULL;

double* l_vecget(lua_State* L, int nArg)
{
	if (!luaL_checkudata(L, nArg, "vector3"))
		luaL_typerror(L, nArg, "vector3");
	return (double*)lua_touserdata(L, nArg);
}

Vector l_vecget2(lua_State* L, int nArg)
{
	if (!luaL_checkudata(L, nArg, "vector3"))
		luaL_typerror(L, nArg, "vector3");
	double* dvec = (double*)lua_touserdata(L, nArg);
	return Vector(dvec[0], dvec[1], dvec[2]);
}

static int AddEntityTextOverlay(lua_State* L) {
	int targetclient = luaL_checknumber(L, 1);
	int entity = luaL_checknumber(L, 2);
	int line = luaL_checknumber(L, 3);
	float duration = luaL_checknumber(L, 4);
	int r = luaL_checknumber(L, 5);
	int g = luaL_checknumber(L, 6);
	int b = luaL_checknumber(L, 7);
	int a = luaL_checknumber(L, 8);
	const char* text = luaL_checkstring(L, 9);
	CRecipientFilter filter(targetclient);
	bf_write* m = engine->UserMessageBegin(&filter, first);
	m->WriteShort(entity);
	m->WriteShort(line);
	m->WriteFloat(duration);
	m->WriteByte(r);
	m->WriteByte(g);
	m->WriteByte(b);
	m->WriteByte(a);
	m->WriteString(text);
	engine->MessageEnd();
	return 0;
}

static int AddBoxOverlay(lua_State* L) {
	int targetclient = luaL_checknumber(L, 1);
	Vector origin = l_vecget2(L, 2);
	Vector min = l_vecget2(L, 3);
	Vector max = l_vecget2(L, 4);
	Vector orientation = l_vecget2(L, 5);
	int r = luaL_checknumber(L, 6);
	int g = luaL_checknumber(L, 7);
	int b = luaL_checknumber(L, 8);
	int a = luaL_checknumber(L, 9);
	float duration = luaL_checknumber(L, 10);
	CRecipientFilter filter(targetclient);
	bf_write* m = engine->UserMessageBegin(&filter, first+1);
	m->WriteBitVec3Coord(origin);
	m->WriteBitVec3Coord(min);
	m->WriteBitVec3Coord(max);
	m->WriteBitVec3Coord(orientation);
	m->WriteByte(r);
	m->WriteByte(g);
	m->WriteByte(b);
	m->WriteByte(a);
	m->WriteFloat(duration);
	engine->MessageEnd();
	return 0;
}

static int AddTriangleOverlay(lua_State* L) {
	int targetclient = luaL_checknumber(L, 1);
	Vector p1 = l_vecget2(L, 2);
	Vector p2 = l_vecget2(L, 3);
	Vector p3 = l_vecget2(L, 4);
	int r = luaL_checknumber(L, 5);
	int g = luaL_checknumber(L, 6);
	int b = luaL_checknumber(L, 7);
	int a = luaL_checknumber(L, 8);
	if (lua_type(L, 9) != LUA_TBOOLEAN) {
		luaL_typerror(L, 9, "boolean");
		return 0;
	}
	bool depth = lua_toboolean(L, 9);
	float duration = luaL_checknumber(L, 10);
	CRecipientFilter filter(targetclient);
	bf_write* m = engine->UserMessageBegin(&filter, first + 2);
	m->WriteBitVec3Coord(p1);
	m->WriteBitVec3Coord(p2);
	m->WriteBitVec3Coord(p3);
	m->WriteByte(r);
	m->WriteByte(g);
	m->WriteByte(b);
	m->WriteByte(a);
	m->WriteByte(depth);
	m->WriteFloat(duration);
	engine->MessageEnd();
	return 0;
}

static int AddLineOverlay(lua_State* L) {
	int targetclient = luaL_checknumber(L, 1);
	Vector p1 = l_vecget2(L, 2);
	Vector p2 = l_vecget2(L, 3);
	int r = luaL_checknumber(L, 4);
	int g = luaL_checknumber(L, 5);
	int b = luaL_checknumber(L, 6);
	if (lua_type(L, 7) != LUA_TBOOLEAN) {
		luaL_typerror(L, 7, "boolean");
		return 0;
	}
	bool depth = lua_toboolean(L, 7);
	float duration = luaL_checknumber(L, 8);
	CRecipientFilter filter(targetclient);
	bf_write* m = engine->UserMessageBegin(&filter, first + 3);
	m->WriteBitVec3Coord(p1);
	m->WriteBitVec3Coord(p2);
	m->WriteByte(r);
	m->WriteByte(g);
	m->WriteByte(b);
	m->WriteByte(depth);
	m->WriteFloat(duration);
	engine->MessageEnd();
	return 0;
}

static int AddTextOverlay(lua_State* L) {
	int targetclient = luaL_checknumber(L, 1);
	Vector p1 = l_vecget2(L, 2);
	int lineoffset = luaL_checknumber(L, 3);
	float dur = luaL_checknumber(L, 4);
	const char* text = luaL_checkstring(L, 5);
	//Msg("%i %f %f %f %i %f %s", targetclient, p1.x, p1.y, p1.z, lineoffset, dur, text);
	CRecipientFilter filter(targetclient);
	bf_write* m = engine->UserMessageBegin(&filter, first + 4);
	m->WriteBitVec3Coord(p1);
	m->WriteShort(lineoffset);
	m->WriteFloat(dur);
	m->WriteString(text);
	engine->MessageEnd();
	return 0;
}

static int AddScreenTextOverlay(lua_State* L) {
	int targetclient = luaL_checknumber(L, 1);
	float x = luaL_checknumber(L, 2);
	float y = luaL_checknumber(L, 3);
	float dur = luaL_checknumber(L, 4);
	int r = luaL_checknumber(L, 5);
	int g = luaL_checknumber(L, 6);
	int b = luaL_checknumber(L, 7);
	int a = luaL_checknumber(L, 8);
	const char* text = luaL_checkstring(L, 9);
	CRecipientFilter filter(targetclient);
	bf_write* m = engine->UserMessageBegin(&filter, first + 5);
	m->WriteFloat(x);
	m->WriteFloat(y);
	m->WriteFloat(dur);
	m->WriteByte(r);
	m->WriteByte(g);
	m->WriteByte(b);
	m->WriteByte(a);
	m->WriteString(text);
	engine->MessageEnd();
	return 0;
}

static int AddSweptBoxOverlay(lua_State* L) {
	int targetclient = luaL_checknumber(L, 1);
	Vector p1 = l_vecget2(L, 2);
	Vector p2 = l_vecget2(L, 3);
	Vector p3 = l_vecget2(L, 4);
	Vector p4 = l_vecget2(L, 5);
	Vector p5 = l_vecget2(L, 6);
	int r = luaL_checknumber(L, 7);
	int g = luaL_checknumber(L, 8);
	int b = luaL_checknumber(L, 9);
	int a = luaL_checknumber(L, 10);
	float dur = luaL_checknumber(L, 11);
	CRecipientFilter filter(targetclient);
	bf_write* m = engine->UserMessageBegin(&filter, first + 6);
	m->WriteBitVec3Coord(p1);
	m->WriteBitVec3Coord(p2);
	m->WriteBitVec3Coord(p3);
	m->WriteBitVec3Coord(p4);
	m->WriteBitVec3Coord(p5);
	m->WriteByte(r);
	m->WriteByte(g);
	m->WriteByte(b);
	m->WriteByte(a);
	m->WriteFloat(dur);
	engine->MessageEnd();
	return 0;
}

static int ClearDeadOverlays(lua_State* L) {
	int targetclient = luaL_checknumber(L, 1);
	CRecipientFilter filter(targetclient);
	bf_write* m = engine->UserMessageBegin(&filter, first + 7);
	engine->MessageEnd();
	return 0;
}

static int ClearAllOverlays(lua_State* L) {
	int targetclient = luaL_checknumber(L, 1);
	CRecipientFilter filter(targetclient);
	bf_write* m = engine->UserMessageBegin(&filter, first + 8);
	engine->MessageEnd();
	return 0;
}

static int AddTextOverlayRGB(lua_State* L) {
	int targetclient = luaL_checknumber(L, 1);
	Vector p1 = l_vecget2(L, 2);
	int lineoffset = luaL_checknumber(L, 3);
	float dur = luaL_checknumber(L, 4);
	int r = luaL_checknumber(L, 5);
	int g = luaL_checknumber(L, 6);
	int b = luaL_checknumber(L, 7);
	int a = luaL_checknumber(L, 8);
	const char* text = luaL_checkstring(L, 9);
	CRecipientFilter filter(targetclient);
	bf_write* m = engine->UserMessageBegin(&filter, first + 9);
	m->WriteBitVec3Coord(p1);
	m->WriteShort(lineoffset);
	m->WriteFloat(dur);
	m->WriteByte(r);
	m->WriteByte(g);
	m->WriteByte(b);
	m->WriteByte(a);
	m->WriteString(text);
	engine->MessageEnd();
	return 0;
}

static const struct luaL_reg reg_overlay[] = {
	{"AddEntityTextOverlay", AddEntityTextOverlay},
	{"AddBoxOverlay", AddBoxOverlay},
	{"AddTriangleOverlay", AddTriangleOverlay},
	{"AddLineOverlay", AddLineOverlay},
	{"AddTextOverlay", AddTextOverlay},
	{"AddScreenTextOverlay", AddScreenTextOverlay},
	{"AddSweptBoxOverlay", AddSweptBoxOverlay},
	{"ClearDeadOverlays", ClearDeadOverlays},
	{"ClearAllOverlays", ClearAllOverlays},
	{"AddTextOverlayRGB", AddTextOverlayRGB},
	{NULL,NULL}
};

static int __cdecl hookstring(lua_State* L) {
	luaL_openlib(L, "overlay", reg_overlay, 0);
	return jumpback(L);
}

void InitLua() {
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
	MH_CreateHook(stringlib, &hookstring, (void**)&jumpback);
	MH_EnableHook(NULL);
}
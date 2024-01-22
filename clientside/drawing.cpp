#include "drawing.h"
#include "bitbuf.h"
#include "vector.h"
void __cdecl AddEntityTextOverlay(bf_read& msg) {
	Msg("message recv\n");
	char ass[255];
	int entity = msg.ReadShort();
	int line = msg.ReadShort();
	float duration = msg.ReadFloat();
	int r = msg.ReadByte();
	int g = msg.ReadByte();
	int b = msg.ReadByte();
	int a = msg.ReadByte();
	msg.ReadString(ass, sizeof(ass),false);
	debugoverlay->AddEntityTextOverlay(entity, line, duration, r, g, b, a, ass);
}

void __cdecl AddBoxOverlay(bf_read& msg) {
	Vector t[4] = {};
	int c[4];
	float d;
	msg.ReadBitVec3Coord(t[0]);
	msg.ReadBitVec3Coord(t[1]);
	msg.ReadBitVec3Coord(t[2]);
	msg.ReadBitVec3Coord(t[3]);
	c[0] = msg.ReadByte();
	c[1] = msg.ReadByte();
	c[2] = msg.ReadByte();
	c[3] = msg.ReadByte();
	d = msg.ReadFloat();
	//Msg("%f %f %f %f %f %f %f %f %f %f %f %f %i %i %i %i %f\n", t[0].x, t[0].y, t[0].z, t[1].x, t[1].y, t[1].z, t[2].x, t[2].y, t[2].z, t[3].x, t[3].y, t[3].z, c[0], c[1], c[2], c[3], d);
	void* vp = &t[3];
	QAngle* ang = (QAngle*)vp; // #hack
	debugoverlay->AddBoxOverlay(t[0], t[1], t[2], *ang, c[0], c[1], c[2], c[3], d);
}

void __cdecl AddTriangleOverlay(bf_read& msg) {
	Vector p[3];
	int c[4];
	bool depth;
	float dur;
	msg.ReadBitVec3Coord(p[0]);
	msg.ReadBitVec3Coord(p[1]);
	msg.ReadBitVec3Coord(p[2]);
	c[0] = msg.ReadByte();
	c[1] = msg.ReadByte();
	c[2] = msg.ReadByte();
	c[3] = msg.ReadByte();
	depth = msg.ReadByte();
	dur = msg.ReadFloat();
	debugoverlay->AddTriangleOverlay(p[0], p[1], p[2], c[0], c[1], c[2], c[3], depth, dur);
}

void __cdecl AddLineOverlay(bf_read& msg) {
	Vector p[2];
	int c[3];
	bool depth;
	float dur;
	msg.ReadBitVec3Coord(p[0]);
	msg.ReadBitVec3Coord(p[1]);
	c[0] = msg.ReadByte();
	c[1] = msg.ReadByte();
	c[2] = msg.ReadByte();
	depth = msg.ReadByte();
	dur = msg.ReadFloat();
	debugoverlay->AddLineOverlay(p[0], p[1], c[0], c[1], c[2], depth, dur);
}

void __cdecl AddTextOverlay(bf_read& msg) {
	Vector p;
	int off;
	float dur;
	char text[128];
	msg.ReadBitVec3Coord(p);
	off = msg.ReadShort();
	dur = msg.ReadFloat();
	msg.ReadString(text,sizeof(text), false);
	debugoverlay->AddTextOverlay(p, off, dur, text);
}

void __cdecl AddScreenTextOverlay(bf_read& msg) {
	float a[3];
	int b[4];
	char text[128];
	a[0] = msg.ReadFloat();
	a[1] = msg.ReadFloat();
	a[2] = msg.ReadFloat();
	b[0] = msg.ReadByte();
	b[1] = msg.ReadByte();
	b[2] = msg.ReadByte();
	b[3] = msg.ReadByte();
	msg.ReadString(text, sizeof(text));
	debugoverlay->AddScreenTextOverlay(a[0], a[1], a[2], b[0], b[1], b[2], b[3], text);
}

void __cdecl AddSweptBoxOverlay(bf_read& msg) {
	Vector p[5];
	float d;
	int c[4];
	msg.ReadBitVec3Coord(p[0]);
	msg.ReadBitVec3Coord(p[1]);
	msg.ReadBitVec3Coord(p[2]);
	msg.ReadBitVec3Coord(p[3]);
	msg.ReadBitVec3Coord(p[4]);
	c[0] = msg.ReadByte();
	c[1] = msg.ReadByte();
	c[2] = msg.ReadByte();
	c[3] = msg.ReadByte();
	d = msg.ReadFloat();
	void* vp = &p[4];
	QAngle* ang = (QAngle*)vp;
	debugoverlay->AddSweptBoxOverlay(p[0], p[1], p[2], p[3], *ang, c[0], c[1], c[2], c[3], d);
}

void __cdecl ClearDeadOverlays(bf_read& msg) {
	debugoverlay->ClearDeadOverlays();
}

void __cdecl ClearAllOverlays(bf_read& msg) {
	debugoverlay->ClearAllOverlays();
}

void __cdecl AddTextOverlayRGB(bf_read& msg) {
	Vector p;
	int off;
	float dur;
	int c[4];
	char text[128];
	msg.ReadBitVec3Coord(p);
	off = msg.ReadShort();
	dur = msg.ReadFloat();
	c[0] = msg.ReadByte();
	c[1] = msg.ReadByte();
	c[2] = msg.ReadByte();
	c[3] = msg.ReadByte();
	msg.ReadString(text, sizeof(text), false);
	debugoverlay->AddTextOverlayRGB(p, off, dur, c[0], c[1], c[2], c[3], text);
}

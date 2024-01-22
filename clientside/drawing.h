#pragma once
#include "bitbuf.h"
#include "ivdebugoverlay.h"
extern IVDebugOverlay* debugoverlay;
void __cdecl AddEntityTextOverlay(bf_read& msg);
void __cdecl AddBoxOverlay(bf_read& msg);
void __cdecl AddTriangleOverlay(bf_read& msg);
void __cdecl AddLineOverlay(bf_read& msg);
void __cdecl AddTextOverlay(bf_read& msg);
void __cdecl AddScreenTextOverlay(bf_read& msg);
void __cdecl AddSweptBoxOverlay(bf_read& msg);
void __cdecl ClearDeadOverlays(bf_read& msg);
void __cdecl ClearAllOverlays(bf_read& msg);
void __cdecl AddTextOverlayRGB(bf_read& msg);
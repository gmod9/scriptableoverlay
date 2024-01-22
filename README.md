# Scriptable Overlay
Scriptable client overlay from serverside lua!

## What is this for lol
The primary reason why i made it is easier geometry visualization (Boxes and triangles). Only way to draw a box in gmod9 is by calculating every vertex and drawing every line separately. 
This library aims to make it easier by exposing IVDebugOverlay and having it be controllable from the server' lua instance.

## Building

1. Grab a copy of the Source SDK from here https://github.com/alliedmodders/hl2sdk (branch: episode1).
2. Set the HL2SDK environment variable to the path of the sdk.
3. Load up the solution in VS2022.
4. In both clientside and serverside projects, delete or change the post build event commandline.
5. Build in Release mode for x86.

## Usage

- overlay.AddEntityTextOverlay(number client, number entity, number line, number duration, number r, number g, number b, number a, string text)
- overlay.AddBoxOverlay(number client, vector3 origin, vector3 mins, vector3 maxs, vector3 angles, number r, number g, number b, number a, number duration)
- overlay.AddTriangleOverlay(number client, vector3 p1, vector3 p2, vector3 p3, number r, number g, number b, number a, bool depth, number duration)
- overlay.AddLineOverlay(number client, vector3 p1, vector3 p2, number r, number g, number b, bool depth, number duration)
- overlay.AddTextOverlay(number client, vector3 pos,number line,number duration,string text)
- overlay.AddScreenTextOverlay(number client, number x, number y, number duration, number r, number g, number b, number a, string text)
- overlay.AddSweptBoxOverlay(vector3 start, vector3 end, vector3 mins, vector3 maxs, vector3 angles, number g, number b, number a, number duration)
- overlay.ClearAllOverlays(number client)
- overlay.ClearDeadOverlays(number client)
- overlay.AddTextOverlayRGB(number client, vector3 origin, number line, number duration, number r, number g, number b, number a, string text)

### Credits
- https://www.lua.org/ (lua/)
- https://github.com/TsudaKageyu/minhook (minhook-master/)
- @dakrk (memoverride patch)

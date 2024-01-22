Patches to `memoverride.cpp` and related headers to allow building on Visual Studio 2022 (and some older), adapted from https://github.com/ozxybox/source-mp13-vs2022 for SDK 2006.

We need to use Valve's allocators as due to how `CLua::Startup` is hooked, Lua using the C runtime's `malloc` directly instead of Valve's stuff causes a crash.

This isn't a good way to go about applying such a patch, but it works fine (for now).
#if _MSC_VER >= 1900
#pragma message ("warning: Fixed memoverride.cpp for newer compilers being included.")
#include "_new-msvc-fix/memoverride.cpp"
#else
#include "tier0/memoverride.cpp"
#endif
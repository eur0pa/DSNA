#include "stdafx.h"
#include "DSNA.h"
#include "Matchmaking.h"

AddRequestLobbyListDistanceFilter oAddRequestLobbyListDistanceFilter = nullptr;

extern ERegionFilterMode eRegionFilterMode;

__declspec(naked) void __stdcall tAddRequestLobbyListDistanceFilter(ELobbyDistanceFilter eLobbyDistanceFilter)
{
    void* This;

    _asm
    {
        push ebp
            mov ebp, esp
            sub esp, __LOCAL_SIZE
            mov This, ecx
                push eRegionFilterMode
                call oAddRequestLobbyListDistanceFilter
            mov ecx, This
            mov esp, ebp
        pop ebp
        retn 4
    }
}

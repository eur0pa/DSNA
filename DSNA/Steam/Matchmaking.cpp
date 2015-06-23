#include "stdafx.h"
#include "DSNA.h"
#include "Matchmaking.h"

AddRequestLobbyListDistanceFilter oAddRequestLobbyListDistanceFilter = nullptr;

extern ERegionFilterMode eRegionFilterMode;

void __fastcall tAddRequestLobbyListDistanceFilter(void* __this, void* /* edx */, ELobbyDistanceFilter eLobbyDistanceFilter)
{
    if (eRegionFilterMode != k_ERegionFilterModeWorldwide)
    {
        debug("AddRequestLobbyListDistanceFilter(%d) [rerouted to %d]", eLobbyDistanceFilter, eRegionFilterMode);
        eLobbyDistanceFilter = (ELobbyDistanceFilter)eRegionFilterMode;
    }
    else
    {
        debug("AddRequestLobbyListDistanceFilter(%d)", eLobbyDistanceFilter);
    }
    return oAddRequestLobbyListDistanceFilter(__this, eLobbyDistanceFilter);
}
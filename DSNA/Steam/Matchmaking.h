#pragma once
#include "stdafx.h"
#include "Libs\steam\steam_api.h"

typedef void(__stdcall *AddRequestLobbyListDistanceFilter)(ELobbyDistanceFilter);   // vft[9]
extern AddRequestLobbyListDistanceFilter oAddRequestLobbyListDistanceFilter;
extern void __stdcall tAddRequestLobbyListDistanceFilter(ELobbyDistanceFilter);

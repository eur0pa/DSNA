#pragma once
#include "stdafx.h"
#include "Libs\steam\steam_api.h"


typedef void(__thiscall* AddRequestLobbyListDistanceFilter)(void*, ELobbyDistanceFilter);   // vft[9]
extern AddRequestLobbyListDistanceFilter oAddRequestLobbyListDistanceFilter;
extern void __fastcall tAddRequestLobbyListDistanceFilter(void*, void*, ELobbyDistanceFilter);
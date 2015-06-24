#pragma once
#include "stdafx.h"
#include "Libs\steam\steam_api.h"

//typedef void(__thiscall* AddRequestLobbyListDistanceFilter)(void*, ELobbyDistanceFilter);   // vft[9]
typedef void(__stdcall *AddRequestLobbyListDistanceFilter)(ELobbyDistanceFilter);
extern AddRequestLobbyListDistanceFilter oAddRequestLobbyListDistanceFilter;
extern void __stdcall tAddRequestLobbyListDistanceFilter(ELobbyDistanceFilter);
//extern void __fastcall tAddRequestLobbyListDistanceFilter(void*, void*, ELobbyDistanceFilter);

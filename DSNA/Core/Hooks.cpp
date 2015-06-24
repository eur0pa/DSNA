#include "stdafx.h"
#include "Hooks.h"

#include "Steam\Networking.h"
#include "Steam\Matchmaking.h"

HMODULE hSteam = nullptr;
ISteamFriends* sFriends = nullptr;
ISteamMatchmaking* sMatchmaking = nullptr;
ISteamNetworking* sNetwork = nullptr;

BOOL SteamHooks()
{
    // <Steam>
    //  get the handle for the Steam module and initialize Detours
    while (hSteam == nullptr)
    {
        hSteam = GetModuleHandle(TEXT("steam_api.dll"));
        Sleep(500);
    }
    debug(".steamclient.dll @ 0x%p", hSteam);

    if (DetourTransactionBegin() != NO_ERROR || DetourUpdateThread(GetCurrentThread()) != NO_ERROR)
    {
        log_err("failed to initialize Detours");
        return false;
    }
    // </Steam>


    // <SteamMatchmaking>
    //  handles: region filtering
    while (sMatchmaking == nullptr)
    {
        sMatchmaking = ((ISteamMatchmaking*(*)(void))GetProcAddress(hSteam, "SteamMatchmaking"))();
        Sleep(500);
    }
    debug("::SteamMatchmaking @ 0x%p", sMatchmaking);

    oAddRequestLobbyListDistanceFilter = (AddRequestLobbyListDistanceFilter)(*(uint32**)sMatchmaking)[9];

    if (DetourAttach(&(PVOID&)oAddRequestLobbyListDistanceFilter, (PVOID)tAddRequestLobbyListDistanceFilter) != NO_ERROR)
    {
        log_err("failed to create hooks for SteamMatchmaking");
        return false;
    }
    debug("SteamMatchmaking->AddRequestLobbyDistanceFilter @ 0x%p t-> 0x%p", oAddRequestLobbyListDistanceFilter, tAddRequestLobbyListDistanceFilter);
    // </SteamMatchmaking>


    // <SteamFriends>
    //  handles: selective player blocking based on relationship status
    while (sFriends == nullptr)
    {
        sFriends = ((ISteamFriends*(*)(void))GetProcAddress(hSteam, "SteamFriends"))();
        Sleep(500);
    }
    debug("::SteamFriends @ 0x%p", sFriends);
    // </SteamFriends>


    // <SteamNetworking>
    //  handles: accepting or dropping packets from players based on their relationship
    //      get the location for members SendP2PPacket() and ReadP2PPacket()
    //      from the ISteamNetworking VFT and enable their hooks
    while (sNetwork == nullptr)
    {
        sNetwork = ((ISteamNetworking*(*)(void))GetProcAddress(hSteam, "SteamNetworking"))();
        Sleep(500);
    }
    debug("::SteamNetworking @ 0x%p", sNetwork);

    oSendP2PPacket = (SendP2PPacket)(*(uint32**)sNetwork)[0];
    oReadP2PPacket = (ReadP2PPacket)(*(uint32**)sNetwork)[2];

    if (DetourAttach(&(PVOID&)oSendP2PPacket, (PVOID)tSendP2PPacket) != NO_ERROR ||
        DetourAttach(&(PVOID&)oReadP2PPacket, (PVOID)tReadP2PPacket) != NO_ERROR)
    {
        log_err("failed to create hooks for SteamNetworking");
        return false;
    }

    if (DetourTransactionCommit() != NO_ERROR)
    {
        log_err("failed to enable hooks for SteamNetworking");
        return false;
    }
    debug("SteamNetworking->SendP2PPacket() @ 0x%p t-> 0x%p", oSendP2PPacket, tSendP2PPacket);
    debug("SteamNetworking->ReadP2PPacket() @ 0x%p t-> 0x%p", oReadP2PPacket, tReadP2PPacket);
    // </SteamNetworking>

    return true;
}

BOOL RemoveSteamHooks()
{
    if (DetourTransactionBegin() != NO_ERROR)
    {
        log_err("failed to uninitialize Detours");
        return false;
    }

    if (DetourDetach(&(PVOID&)oAddRequestLobbyListDistanceFilter, (PVOID)tAddRequestLobbyListDistanceFilter) != NO_ERROR ||
        DetourDetach(&(PVOID&)oSendP2PPacket, (PVOID)tSendP2PPacket) != NO_ERROR ||
        DetourDetach(&(PVOID&)oReadP2PPacket, (PVOID)tReadP2PPacket) != NO_ERROR)
    {
        return false;
    }

    if (DetourTransactionCommit() != NO_ERROR)
    {
        log_err("failed to disable hooks for SteamNetworking");
        return false;
    }

    return true;
}
#include "stdafx.h"
#include "DSNA.h"
#include "Networking.h"

SendP2PPacket oSendP2PPacket = nullptr;
ReadP2PPacket oReadP2PPacket = nullptr;

extern ISteamFriends* sFriends;
extern EMatchmakingMode eMatchmakingMode;

bool __fastcall tSendP2PPacket(void* __this, void* /* edx */, CSteamID steamIDRemote, const void* pubData, uint32 cubData, EP2PSend eP2PSendType, int nChannel)
{
    EPersonaState kPersonaState = sFriends->GetPersonaState();

    // if not set on everyone, or custom + online...
    if (eMatchmakingMode != k_EMatchmakingModeEveryone ||
       (eMatchmakingMode != k_EMatchmakingModeCustom && kPersonaState != k_EPersonaStateOnline))
    {
        EFriendRelationship kFriend = sFriends->GetFriendRelationship(steamIDRemote);

        // if set to friends only, or custom + offline...
        if (eMatchmakingMode == k_EMatchmakingModeFriendsOnly ||
           (eMatchmakingMode == k_EMatchmakingModeCustom && kPersonaState == k_EPersonaStateOffline))
        {
            if (kFriend != k_EFriendRelationshipFriend)
            {
                debug("SendP2PPacket(-> %I64d) (kFR = %d) [discarded: friends only]", steamIDRemote.ConvertToUint64(), kFriend);
                return false;
            }
        }
        // if set to blocklist, or custom + away...
        else if (eMatchmakingMode == k_EMatchmakingModeBlocklist ||
                (eMatchmakingMode == k_EMatchmakingModeCustom && kPersonaState == k_EPersonaStateAway))
        {
            if (kFriend == k_EFriendRelationshipBlocked ||
                kFriend == k_EFriendRelationshipIgnored ||
                kFriend == k_EFriendRelationshipIgnoredFriend)
            {
                debug("SendP2PPacket(-> %I64d) (kFR = %d) [discarded: blocklist]", steamIDRemote.ConvertToUint64(), kFriend);
                return false;
            }
        }
    }

    return oSendP2PPacket(__this, steamIDRemote, pubData, cubData, eP2PSendType, nChannel);
}

bool __fastcall tReadP2PPacket(void* __this, void* /* edx */, void* pubDest, uint32 cubDest, uint32* pcubMsgSize, CSteamID* psteamIDRemote, int nChannel)
{
    EPersonaState kPersonaState = sFriends->GetPersonaState();
    bool bReadRes = oReadP2PPacket(__this, pubDest, cubDest, pcubMsgSize, psteamIDRemote, nChannel);

    // if not set on everyone, or custom + online...
    if (eMatchmakingMode != k_EMatchmakingModeEveryone ||
       (eMatchmakingMode != k_EMatchmakingModeCustom && kPersonaState != k_EPersonaStateOnline))
    {
        EFriendRelationship kFriend = sFriends->GetFriendRelationship(*psteamIDRemote);

        // if set to friends only, or custom + offline...
        if (eMatchmakingMode == k_EMatchmakingModeFriendsOnly ||
            (eMatchmakingMode == k_EMatchmakingModeCustom && kPersonaState == k_EPersonaStateOffline))
        {
            if (kFriend != k_EFriendRelationshipFriend)
            {
                debug("ReadP2PPacket(<- %I64d) (kFR = %d) [discarded: friends only]", psteamIDRemote->ConvertToUint64(), kFriend);
                return false;
            }
        }
        // if set to blocklist, or custom + away...
        else if (eMatchmakingMode == k_EMatchmakingModeBlocklist ||
                (eMatchmakingMode == k_EMatchmakingModeCustom && kPersonaState == k_EPersonaStateAway))
        {
            if (kFriend == k_EFriendRelationshipBlocked ||
                kFriend == k_EFriendRelationshipIgnored ||
                kFriend == k_EFriendRelationshipIgnoredFriend)
            {
                debug("ReadP2PPacket(<- %I64d) (kFR = %d) [discarded: blocklist]", psteamIDRemote->ConvertToUint64(), kFriend);
                return false;
            }
        }
    }

    return bReadRes;
}
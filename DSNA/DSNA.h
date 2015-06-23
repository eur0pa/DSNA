#pragma once
#include "stdafx.h"

enum ERegionFilterMode
{
    k_ERegionFilterModeClose,
    k_ERegionFilterModeRegional,
    k_ERegionFilterModeFar,
    k_ERegionFilterModeWorldwide,
};

enum EMatchmakingMode
{
    k_EMatchmakingModeEveryone,
    k_EMatchmakingModeBlocklist,
    k_EMatchmakingModeFriendsOnly,
    k_EMatchmakingModeCustom,
};

extern ERegionFilterMode eRegionFilterMode;
extern EMatchmakingMode eMatchmakingMode;

extern BOOL GetSettings();
extern BOOL Begin();
extern BOOL End();
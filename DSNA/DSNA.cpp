#include "stdafx.h"
#include "DSNA.h"

#include "Core\Hooks.h"
#include "Core\Settings.h"

ERegionFilterMode eRegionFilterMode;
EMatchmakingMode eMatchmakingMode;

BOOL GetSettings()
{
    eRegionFilterMode = k_ERegionFilterModeWorldwide;
    eMatchmakingMode = k_EMatchmakingModeEveryone;

    Settings::get().load();

    if (!Settings::get().getRegionFilter().empty())
    {
        if (Settings::get().getRegionFilter().compare("close") == 0)
        {
            eRegionFilterMode = k_ERegionFilterModeClose;
        }
        else if (Settings::get().getRegionFilter().compare("regional") == 0)
        {
            eRegionFilterMode = k_ERegionFilterModeRegional;
        }
        else if (Settings::get().getRegionFilter().compare("far") == 0)
        {
            eRegionFilterMode = k_ERegionFilterModeFar;
        }
        else
        {
            eRegionFilterMode = k_ERegionFilterModeWorldwide;
        }
    }

    if (!Settings::get().getMatchmakingMode().empty())
    {
        if (Settings::get().getMatchmakingMode().compare("friendsonly") == 0)
        {
            eMatchmakingMode = k_EMatchmakingModeFriendsOnly;
        }
        else if (Settings::get().getMatchmakingMode().compare("blocklist") == 0)
        {
            eMatchmakingMode = k_EMatchmakingModeBlocklist;
        }
        else if (Settings::get().getMatchmakingMode().compare("custom") == 0)
        {
            eMatchmakingMode = k_EMatchmakingModeCustom;
        }
        else
        {
            eMatchmakingMode = k_EMatchmakingModeEveryone;
        }
    }

    return true;
}

BOOL Begin()
{
    MessageBox(NULL, "ALT", "ALT", MB_OK);

    // Get user settings
    if (GetSettings() == false)
    {
        log_err("Failed to load user settings");
        return false;
    }
    log_info("RegionFilter is set to %d", eRegionFilterMode);
    log_info("Matchmaking is set to %d", eMatchmakingMode);

    // Enable hooks for Steam
    if (SteamHooks() == false)
    {
        log_err("Failed to apply Steam hooks");
        return false;
    }

    return true;
}

BOOL End()
{
    if (RemoveSteamHooks() == false)
    {
        log_err("Failed to remove Steam hooks");
        return false;
    }

    return true;
}



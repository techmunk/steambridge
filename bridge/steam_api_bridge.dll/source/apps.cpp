// apps.cpp - Implements various functions related to the ISteamApps class
// Copyright (c) 2014 Bryan DeGrendel
//
// See COPYING and license/LICENSE.steambridge for license information

#include <cstdio>

#include <steam_api.h>

#define NOMINMAX
#include <wine/debug.h>

#include "api.h"
#include "logging.h"
#include "state.h"

WINE_DEFAULT_DEBUG_CHANNEL(steambridge);

extern "C"
{

STEAM_API_BRIDGE_API bool steam_bridge_SteamApps_BIsSubscribedApp(
    class ISteamApps *steamApps, AppId_t appId)
{
  WINE_TRACE("(%p,%u)\n", steamApps, appId);

  if (!steamApps) __ABORT("NULL steamApps pointer!");

  return steamApps->BIsSubscribedApp(appId);
}

STEAM_API_BRIDGE_API const char *steam_bridge_SteamApps_GetCurrentGameLanguage(
    class ISteamApps *steamApps)
{
  WINE_TRACE("(%p)\n", steamApps);

  if (!steamApps) __ABORT("NULL steamApps pointer!");

  return steamApps->GetCurrentGameLanguage();
}

STEAM_API_BRIDGE_API class ISteamApps *steam_bridge_SteamApps()
{
  WINE_TRACE("\n");

  if (!state)
  {
    WINE_ERR("NULL internal state (init not called?)\n");
    return NULL;
  }

  return state->getSteamApps();
}

} // extern "C"


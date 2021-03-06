// core.cpp - Implements code related to various core API calls
// Copyright (c) 2014 Bryan DeGrendel
//
// See COPYING and license/LICENSE.steambridge for license information

#include <cstdio>

#include <dlfcn.h>

#include <steam_api.h>

#define NOMINMAX
#include <wine/debug.h>

#include "api.h"
#include "logging.h"
#include "state.h"

typedef bool (*steam_api_InitSafe_t)(void);
typedef void (*steam_api_Shutdown_t)(void);

WINE_DEFAULT_DEBUG_CHANNEL(steambridge);

extern "C"
{

// TODO: Would we want/need a wrapper for the straight Init() function?
//       Maybe one that creates a state that uses the default ISteam*
//       classes?
bool SteamAPI_InitSafe_()
{
  WINE_TRACE("\n");

  if (!state)
  {
    if (!(state = new State()))
      __ABORT("Unable to allocate the internal state!!");

    __DLSYM_GET(steam_api_InitSafe_t, api, "SteamAPI_InitSafe");
    if (!(*api)())
    {
      WINE_WARN("SteamAPI_InitSafe failed! - look for Steam messages\n");
      return false;
    }

    state->initialize();

    WINE_TRACE("Created internal state (%p)\n", state);
  }
  else
    WINE_WARN("Init called twice (perhaps internally the first time)\n");
  return true;
}

void SteamAPI_Shutdown_()
{
  WINE_TRACE("\n");
  if (state == NULL)
    WINE_WARN("Shutdown called when not initialized!\n");
  else
  {
    __DLSYM_GET(steam_api_Shutdown_t, api, "SteamAPI_Shutdown");
    (*api)();
    delete state;
    state = NULL;
    WINE_TRACE("SteamAPI Shutdown\n");
  }
}

} // extern "C"

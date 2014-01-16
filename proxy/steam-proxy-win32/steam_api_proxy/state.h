// state.h - Records the state of the app, specifically stuff that's
//           internal and can't be cleanly tossed back to the app via 
//           the existing (and expected) classes/interfaces.

#pragma once

class AppState
{
  public:
    AppState();
    ~AppState();

    void setSafeMode(bool safe);
    bool getSafeMode();

  private:
    bool safeMode;
};

extern AppState state;

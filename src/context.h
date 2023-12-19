#ifndef CONTEXT_H
#define CONTEXT_H

#include "config.h"
#include "Joystick.h"
#include "Button.h"
#include "StatusDisplay.h"
#include "GameDisplay.h"
#include "AppStateManager.h"
#include "MenuManager.h"
#include "InputManager.h"
#include "LeaderboardManager.h"
#include "SoundManager.h"
#include "Game.h"

// - Input components
extern Joystick joystick;
extern Button triggerBtn;

// - Output components
extern StatusDisplay statusDisp;
extern GameDisplay gameDisp;

// - App state components
extern AppStateManager appStateManager;
extern MenuManager menuManager;
extern InputManager inputManager;
extern LeaderboardManager leaderboardManager;
extern SoundManager soundManager;
extern Game game;

#endif // CONTEXT_H

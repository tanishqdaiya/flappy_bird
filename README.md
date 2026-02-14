FLAPPY BIRD -- Overview
=======================
This project was built as an exercise in disciplined system design. A simple
game was selected to allow for directed attention on the structure. The system
is divided into clear replaceable modules, directly inspired from The DOOM C
Source. A formal state machine was also implemented to govern flow, with a fixed
logical resolution to maintain consistent experience across different displays.

Third-Party Libraries
---------------------
This project uses external libraries. All third-party libraries are the property
of their respective copyright holders and are distributed under their own
licenses.

No ownership is claimed over these libraries. Refer to the lib/ directory.

Module Spec
-----------
The system is divided into modules.

G_ "Game Control" :: Handles state
P_ "Physics" :: No UI. No Raylib calls.
R_ "Rendering" :: Render Pipeline
UI_ "User Interface" :: Menus, Score Display, Pause Screen, etc.
S_ "Sound System" :: Sound effects and Music.
M_ "Memory" :: Memory Management (IF SOMEDAY)
I_ "Interface/System" :: OS Boundary; File IO; Time;
U_ "Utility" :: Math; Small helpers

State Machine
-------------
The game will follow a state machine pattern. Here is a map of all the
possible transitions:

PLAYING <-> PAUSED
PLAYING <-> GAME_OVER
MENU -> PLAYING
PAUSED -> MENU

Rendering Model
---------------
Logical resolution is fixed.
scale = min(screenw/designw, screenh/designh)

UI Configuration
----------------
The UI will be data-driven. I aim to load it from the config file at startup,
while monitoring the file for changes. We will reload the configuration state on
change.

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

Current State
-------------

The current state of the project is simple: It has done what it first aimed to
achieve. It is a proper game engine with config file hot-reloading. It uses
Raylib only as an abstraction layer to handle rendering. The code is modular and
easily maintainable.

Then what is left?
1) A _Good_ UX: I'm quite unsatisfied with what we current have. I can obviously
do better than default Raylib fonts and a better theme for the UI elements. Not
to mention, the game lacks soul because it lacks music. It is a small addition
but can do wonders. Also I would quite like to fix the constants to make the
physics appealing.
2) Highscore (auto)saving system: The feature is quite simple to implement and
there are blanks left for that. However, I am not much interested in handling
files (again) to implement a feature that doesn't teach me much.
3) Optimzations and Memory: I haven't quite extensively reviewed the code. There
are a lot of optimizations that can be done but were not because of time
limitations. A lot of extensive testing was simply not the goal for the project.
4) An AI: This might be a cute little side venture where you have an AI play the
game. Helps in testing and optimizing constants for a good play experience.
5) Distributable Binary: I do need to work on this immediately. A config
directory directory for the program isn't that hard to create.
6) Cross-Platform: Currently this works only for Windows. Although its
modularity (and raylib's portability) does allow for easy porting to other
platforms.

A lot can be done to refine it. However, now that I have gained everything that
was to gain from this project, I think it would not be wise to spend any time
further on simple applications unless I have the freedom of time on my hands to
do so.

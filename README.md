This is a very basic AI for some Tetris-like game.

The basic logic of the game (only a subset is implemented) needed by the AI is in Block and Board.
The AI is of course in AI.  Some common defines (colours and size of board) are in common.h.

There are currently two programs (discounting the test):

* `ai\_demo` just simulates some tetris game, using the AI to place 2000 random blocks
* `play` attempts to play Cultris II (training / versus against bots)

Most of the code is just ordinary C99 with no interesting dependencies.  `play` currently uses some
X11 extensions, so it is not portable at all (and most of the file should be in some separate API).
Furthermore, `play` needs to know (currently hard-coded) where to look on-screen for the current and
next block (it looks at the X11 window and sends key events just like a human).

Features such as slow / quick-falling, handling lines being sent (lines coming up from below in
Cultris) and several other details are currently not handled at all.  The AI and the `play` file
simply drops pieces.

This project is not very complete, but it may be of interest if you feel like writing something
similar.  It has managed in my tests to beat a medium-hard Cultris II bot.

Cultris is developed by [GEWALTIG entertainment](www.gewaltig.net)

Tetris® is a registered trademark of the Tetris Holding.  Neither I nor GEWALTIG (to my knowledge)
are in any way affiliated with Tetris Holding.

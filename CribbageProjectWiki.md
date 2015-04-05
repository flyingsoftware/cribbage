What is the Cribbge project?

# Introduction #

After some deep thinking I came to the conclusion that the game of cribbage can be a closed science.  This project is an attempt to use game theory to create a cribbage program that will always make optimal plays.


# Details #

To start you'll need a C++ compiler.  I chose to use the Borland C++ compiler because it's free for commercial use where as Visual Studio has a free download but it's only allowed for academic work.

Once you get a C++ compiler you can use the Makefile to build the project.  Make also comes with Borland C++.  Make sure you put the Borland executables in your path.  Once in your path you can either edit the Makefile to modify BORLAND\_HOME or run "make BORLAND\_HOME=some\_path".

Assuming everyting compiles for you the main executable is main.exe.

As of the first drop the computer will play a 'dummy' player.  This can be changed to a human player by modifying the Game::run method to use a HumanPlayer instead of a Player (which is a dummy player that randomly plays cards).

In this first drop the computer player will go through a decision tree during card play to determine which card play will result in more points for the computer with respect to its opponent.  If there is more than one card play with an optimal point return it simply uses the first play it examined.  It also doesn't smartly use a deck of cards during decision tree play evaluation so it does erroneously evaluate situations where there might be more than 4 of a kind.

That's all I have for now.  Enjoy!
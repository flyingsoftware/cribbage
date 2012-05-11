// =============================================================================
// Copyright 2012.
// Scott Alexander Holm.
// All Rights Reserved.
// =============================================================================

#ifndef GAME_H
#define GAME_H

#include "deck.h"
#include "player.h"
#include "humanplayer.h"
#include "computerplayer.h"
#include "hand.h"
#include "cribhand.h"
#include "constants.h"




// Two player cribbage
class Game {

private:
    // private data

    // Deck with 52 cards
    Deck d;

    // two players
    //Player p[NUMBER_OF_PLAYERS];
    //HumanPlayer hp;
    //Player cp;
    
    // The cib
    CribHand crib;
    // The cut card
    Card starter;
    // The player to start the deal with
    short int dealer;
    // set to true when the game is over
    bool gameover;
    // private methods

    // Determine who the dealer is.
    short int decideDealer (Player *p[]);

    // Deal to players
    void deal (Player *p[]);
    // discard to crib
    void discardCrib (Player *p[]);
    // flip the cut card.  Return true if gameover
    bool cut (Player *p[]);
    // play the hands.  Return true if gameover
    bool play (Player *p[]);
    // count the hands return true if gameover
    bool count (Player *p[]);
    // check for win and display totals.  return true if gameover
    bool scorecard (Player *p[]);

public:
    // public methods
    Game (void);
    void run (void);

};

#endif

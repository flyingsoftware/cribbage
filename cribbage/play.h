// =============================================================================
// Copyright 2012.
// Scott Alexander Holm.
// All Rights Reserved.
// =============================================================================

#ifndef PLAY_H
#define PLAY_H

#include "player.h"
#include "card.h"
#include "constants.h"



// Crib play
class Play {

protected:
    // array of cards thus played.
    Card played[8];
    // index into play array
    short int played_index;

    // a players go
    bool go[2];

    // whos turn it is
    bool turn;

    // players of the game
    Player *p[2];

    // the running count
    short unsigned int count;

    // the state of points after the last card was played
    bool fifteen;
    bool thirtyone;
    bool quadruple;
    bool triple;
    bool pair;
    short unsigned int run;
    bool last;

    // points earned from last play
    short unsigned int earned;


public:
    //Play (void);
    Play (void);
    Play (Player *contestant[], bool dealer);
    Play (Player *contestant[],  short unsigned int new_count,
    Card *new_played, short int new_played_index);

    // reset the gos and count and played card array
    void resetPlay(void);

    // nuke the scored states
    void resetScored(void);

    // return any points earned by discard
    virtual short unsigned int playCard (Card discard);

    // the state of points after the last card was played
    bool fifteenScored(void); 
    bool thirtyoneScored(void); 
    bool quadrupleScored(void); 
    bool tripleScored(void); 
    bool pairScored(void); 
    short unsigned int runScored(void); 
    bool lastScored(void);

    // the points earned from the last play
    short unsigned int pointsEarned (void);

    // get the running count
    short unsigned int getCount (void);

    // set the running count
    void setCount (short unsigned int new_count);

    // get the last discarded
    Card getDiscard();

    // deal with the go
    bool isGo();
    void setGo(short unsigned int turn);

    // true when both players have said 'go'
    bool countReached(void);

    // true when one player has said go and the other hasn't but doesn't have
    // any cards that can be played
    bool isLast(void);

    // set the 'last' variable to true
    bool setLast(void);

    // return play when both players are out of cards
    bool playOver(void);

    // announce any points gained during play
    virtual void announcePlay(void);

    // make it the next players turn
    void endTurn(void);

    // get who's turn it is
    bool getTurn(void);

    // play up to 31 or we run out of cards
    bool playSet(void);
    // play as many times as we can up to 31 or we run out of cards
    virtual bool playAllSets(void);

    // The main routine
    //bool play(Player *p[]);

    // get the seed value from the current players points values
    virtual short unsigned int getCurrentPlayerPointsSeed(void);
    virtual short unsigned int getOpponentPlayerPointsSeed(void);
};

#endif

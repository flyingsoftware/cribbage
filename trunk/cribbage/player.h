// =============================================================================
// Copyright 2012.
// Scott Alexander Holm.
// All Rights Reserved.
// =============================================================================

#ifndef PLAYER_H
#define PLAYER_H

#include "hand.h"
#include "deck.h"
#include "constants.h"
//#include "play.h"

short unsigned int const INPUT_LENGTH=20;


// Cribbage Player
class Player {

protected:
    // the players hand
    Hand h;
    // cards the player discards during play
    Hand played;

    // how many points a player has
    short unsigned int points;
    // who you think you are
    char name[INPUT_LENGTH];
    // the go
    //bool go;


public:
    Player (void);
    Player(char *new_name);
    void addCard (Card c);
    Card addDiscard (Card c);
    void addHand (const Hand& newh);
    void setHand (Hand newh);
    void restoreDiscards(void);
    Hand getHand(void) const;

    virtual Hand discardCrib(bool is_dealer, Player *opponent);

    // Have player 'dealer' deal 'cards' cards to 'players' players in array p
    // from deck d 
    void deal (short int dealer, short int cards, short int players,
        Player *p[], Deck& d);
    Card dealCut (short int order, const Deck& d) const;
    Card cut(Deck& d, short int top_offset, short int bottom_offset);
    short unsigned int peg(short unsigned int p);
    short unsigned int getPoints(void);
    short unsigned int setPoints(short unsigned int p);

    virtual bool hasPlayRankOrLess( short unsigned int bound);
    virtual short int getNumCards () const;

    bool isWinner(void);

    // throw some card
    Card removeRandomCard (void);

    // throw a specific card
    Card removeCard (Card c);

    // discard a random card with play rank less than rank bound
    Card removeRandomCardWithPlayRankOrLess( short unsigned int bound);

    // play a card in crib play
    virtual Card playCard(short unsigned int count, Card *played,
        short int played_index, Player *opponent, bool opponents_go,
        short int current_player_points_seed,
        short int opponent_player_points_seed);

    // add points from hand to current points
    short unsigned int countHand(Card starter);

    // Discard the entire hand
    Hand discardHand (void);

    // return the players name
    const char *getName(void) const;

    // announce any points gained during play
    //void announcePlay(Play p);

    // return true if the player can play a card
    bool canPlay(short unsigned int count);

    // check if player is a 'go'
    //bool isGo(void);
    // set the go
    //void setGo(bool g);

    //Card discardPegging (short int unsigned total);
    friend ostream& operator <<(ostream& o, const Player& p);


};

#endif

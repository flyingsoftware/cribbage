// =============================================================================
// Copyright 2012.
// Scott Alexander Holm.
// All Rights Reserved.
// =============================================================================

#ifndef HAND_H
#define HAND_H

#include <iostream.h>

#include "card.h"
#include "deck.h"

short unsigned int const HAND_MAX_SIZE = DECK_SIZE;

// cribbage hand
class Hand {

protected:
    // dynamic array of cards in hand
    Card hand[HAND_MAX_SIZE];

    // Hash table where keys are possible cards and value is location into
    // hand array
    //short int cardHash[DECK_SIZE];

    // index to last card in hand
    short int last;

    // set to true if the hand is a crib hand

public:
    Hand (void);
    const Card *getHand(void) const;
    Card addCard (Card c);
    short int getNumCards () const;
    Card removeRandomCard ();
    Card removeRandomCardWithPlayRankOrLess (short unsigned int bound);
    Card removeCard (Card c);

    // count the points in the hand
    short unsigned int countHand(Card starter);
    //short unsigned int countCribHand(Card starter);

    // get rid of the hand
    Hand discardHand (void);

    bool hasPlayRankOrLess(short unsigned int rank);

    // counting methods
    short unsigned int countFifteens(void);
    short unsigned int countPairs(void);
    short unsigned int countRuns(void);
    virtual short unsigned int countFlush(Card starter);
    short unsigned int countNobs(Card starter);

    void addHand(const Hand& h);

    //void sort(void);
    friend ostream& operator <<(ostream& o, const Hand& h);
    friend Hand operator +(const Hand& h1, const Hand& h2);

    //const Hand& operator =(const Hand& right_side);
};

#endif

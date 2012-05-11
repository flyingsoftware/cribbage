// =============================================================================
// Copyright 2012.
// Scott Alexander Holm.
// All Rights Reserved.
// =============================================================================

#ifndef DECK_H
#define DECK_H

#include "card.h"

short unsigned int const DECK_SIZE=52;

enum Rank { ACE=1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE,
        TEN, JACK, QUEEN, KING};

enum Suit { DIAMONDS, CLUBS, HEARTS, SPADES};

class Deck {

private:
    Card c[DECK_SIZE];
    // index to top of deck
    short int top;

public:
    Deck (void);
    void setCards (short int c);
    void shuffle (void);
    // do a cribbage cut by looking at the bottom of the card on the upper
    // part of the deck cut in the range passed.
    Card dealCut(short int lower, short int upper) const;
    Card cut(short int top_offset, short int bottom_offset);
    Card draw (void);

};

#endif

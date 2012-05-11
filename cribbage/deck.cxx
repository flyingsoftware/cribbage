// =============================================================================
// Copyright 2012.
// Scott Alexander Holm.
// All Rights Reserved.
// =============================================================================

#include "deck.h"
#include "card.h"

#include <iostream.h>

// Constructors
Deck::Deck (void) {
    // set the top of the deck at 0
    top = 0;

    // seed
    //int seed;

    for (int i = 0; i < DECK_SIZE; i++) {
        c[i].setFace(i);
    }

    // seed random number generator for future operations
    srand (time(NULL));

    //cout << "RAND SEED=" << seed << "\n";

    // Caller should always assume the deck needs to be shuffled like in 
    // real life.
    //shuffle ();
}

// Methods
void Deck::shuffle (void) {
    // swap space
    Card swap;

    // random index
    short int r;

    // Pick a number between 0 and i.  Pull that card out of the deck and swap
    // it with card i + 1.  When i is 0 we don't need to pick a random card
    // since we can assume the last card standing is shuffled since there is
    // no unshuffled card to swap it with.
    for (int i = DECK_SIZE - 1; i >0; i--) {
        r = random (i+1);
        swap = c[i];
        c[i] = c[r];
        c[r] = swap;
    }

    // after we shuffle put the top index to 0
    top = 0;
}

// do a cribbage cut by looking at the bottom of the card on the upper
// part of the deck cut in the range passed.
Card Deck::dealCut(short int lower, short int upper) const {
    // assume the random number generator was seeded by the constructor
    return c[random(upper-lower) + lower];
}

Card Deck::cut (short int top_offset, short int bottom_offset) {
    // get a random number in a valid range and return the card there.  Note
    // card returned is -1 below the card selected since that is the card
    // to flip over after a cut has been made
    return c[random((DECK_SIZE - top - top_offset - bottom_offset))
        + top + top_offset - 1];
}

// return the top card and increment the top of the deck pointer
Card Deck::draw (void) {
    //cout << "top = " << top << "\n";
    //cout << c[top] << "\n";
    return c[top++];
}



// =============================================================================
// Copyright 2012.
// Scott Alexander Holm.
// All Rights Reserved.
// =============================================================================

#include "cribhand.h"


// override the method to figure out a flush
short unsigned int CribHand::countFlush(Card starter) {
    short unsigned int count = 0;

    // remove the starter card from the hand to see if we have a regular flush
    removeCard(starter);

    // check for a flush in the hand
    if ((hand[0].getSuit() == hand[1].getSuit()) &&
        (hand[1].getSuit() == hand[2].getSuit()) &&
        (hand[2].getSuit() == hand[3].getSuit()) &&
        (hand[3].getSuit() == starter.getSuit())) {
        count = 5;
    }

    // put the card back in the hand in case if the player still needs it there
    addCard (starter);

    cout << "    FLUSH for " << count << "\n";

    return count;
}



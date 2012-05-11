// =============================================================================
// Copyright 2012.
// Scott Alexander Holm.
// All Rights Reserved.
// =============================================================================


#include "hand.h"
#include "deck.h"

// Constructors
Hand::Hand (void) {
    // With no cards make sure the last card is below 0
    last = -1;
}


// Accessors
const Card *Hand::getHand(void) const {
    return hand;
}

// Mutators
Card Hand::addCard (Card c) {

    // set to true if we've added the card somewhere in the middle of the hand
    bool added = false;

    // Update the location of the last card
    last++;

    // keep hand sorted when adding a new card
    for (int i=0; i < last; i++) {
        // If the new card rank is lower than the current card then move all
        // the cards over and insert the current card here.
        if (c.getRank() < hand[i].getRank()) {
            for (int j = last; j > i; j--) {
                hand [j] = hand[j-1];
            }
            hand[i] = c;
            added = true;
            break;
        }
    }

    // If we went throug all the cards and didn't have to add the new card into
    // the middle of the card then add it on the end.
    if (!added) {
        hand[last] = c;
    }

    return c;
}

// Methods
short int Hand::getNumCards () const {
    return last + 1;
}

// Remove a random card (for 'dumb' player testing)
Card Hand::removeRandomCard() {

    // Choose a random card in the hand and
    // remove card from the hand
    return removeCard(hand[random(last +1)]);
}

Card Hand::removeCard (Card c) {
    // set to true if card removed
    bool removed = false;

    // iterate through the hand, except for the last card since it will always
    // go away
    for (int i=0; i < last; i++) {
        // Check if the card to remove matches the card in the hand or if
        // card was already removed
        if (c == hand[i] || removed) {
            hand[i] = hand[i+1];
            removed = true;
        }
    } 

    // Decrement the last card index
    last--; 

    // Return the card removed
    return c;
}

bool Hand::hasPlayRankOrLess(short unsigned int bound) {
    // return 1 as soon as we find a card equal or less to bound
    for (int i=0; i < last+1; i++) {
        if (hand[i].getPlayRank() <= bound) {
            return true;
        }
    }
    // if we made it here then we don't have a card less than or equal to rank
    // so return false
    return false;
}

Card Hand::removeRandomCardWithPlayRankOrLess (short unsigned int bound)
    {
    // an array of cards copied from hand
    Card rand_card[HAND_MAX_SIZE];
    // index to last card in r
    //short unsigned int rand_card_index = last;
    // space to move cards around
    Card swap;
    short unsigned int rand_num;

    // copy hand into rand_card
    for (int i=0; i < last+1; i++) {
        rand_card[i] = hand[i];
    }

    // pick random card from rand_card between i and 0 until we find one
    // <= bound
    for (int i=last; i > -1; i--) {
        // pick random card that hadn't already been tried
        rand_num = random(i + 1);

        // if the random card is less than or = to bound then return it
        if (rand_card[rand_num].getPlayRank() <= bound) {

            return removeCard(rand_card[rand_num]);
        }
        // otherwise swap the randomly selected card with the card at the end
        // of the list so it is not selected in the next random selection
        swap = rand_card[i];
        rand_card[i] = rand_card[rand_num];
        rand_card[rand_num] = swap;
    }

    // if we reach this point then an error had occured becuase we don't have
    // a card that is less than or equal to bound
    cout << "FATAL ERROR: No card with rank less than " << bound << "\n";
    exit (1);
    // this should never run
    return rand_card[rand_num];
}

Hand Hand::discardHand (void) {
    Hand discard = *this;
    last = -1;
    return discard;
}

// count the hand
short unsigned int Hand::countHand(Card starter) {
    short unsigned int count = 0;

    cout << "    hand: " << *this << "\n";
    cout << "    starter: " << starter << "\n";
    //cout << "face values " << hand[0].getFace() << " " <<
    //    hand[1].getFace() << " "
    //    << hand[2].getFace() << " " << hand[3].getFace() << " " <<
    //    hand[4].getFace() << "\n";

    // Add the starter card to the hand
    addCard (starter);

    count = count +
        countFifteens() +
        countPairs() +
        countRuns() +
        countFlush(starter) +
        countNobs(starter);

    // remove the starter card from the hand
    removeCard (starter);

    return count;
}

short unsigned int Hand::countFifteens(void) {
    short unsigned int count = 0;

    // check for pairs totaling 15s
    for (int i=0; i < last; i++) {
        for (int j=i+1; j < last+1; j++) {
            // check for 15 total and add 2 to count if so
            if (hand[i].getPlayRank() + hand[j].getPlayRank() == 15) {
                count = count + 2;
            }
        }
    }
    // check for triples totaling 15s
    for (int i=0; i < last-1; i++) {
        for (int j=i+1; j < last; j++) {
            for (int k=j+1; k < last+1; k++) {
                // check for 15 total and add 2 to count if so
                if (hand[i].getPlayRank() + hand[j].getPlayRank() +
                    hand[k].getPlayRank() == 15) {
                    count = count + 2;
                }
            }
        }
    }
    // check for quadruples totaling 15s
    for (int i=0; i < last-2; i++) {
        for (int j=i+1; j < last-1; j++) {
            for (int k=j+1; k < last; k++) {
                for (int l=k+1; l < last+1; l++) {
                    // check for 15 total and add 2 to count if so
                    if (hand[i].getPlayRank() + hand[j].getPlayRank() +
                        hand[k].getPlayRank() + hand[l].getPlayRank()  == 15) {
                        count = count + 2;
                    }
                }
            }
        }
    }
    // check quintuple for 15s.
    if (hand[0].getPlayRank() + hand[1].getPlayRank() +
        hand[2].getPlayRank() + hand[3].getPlayRank() +
        hand[4].getPlayRank() == 15) {
        count = count + 2;
    }

    cout << "    FIFTEENS for " << count << "\n";

    return count;
}

short unsigned int Hand::countPairs(void) {
    short unsigned int count = 0;
    short unsigned int pair_count = 0;
  
    for (int i=1; i < last+1; i++) {
        // check if the current card matches the prior card and if so update
        // the pair count
        if (hand[i].getRank() == hand[i-1].getRank()) {
            pair_count = pair_count++;
        }
        else {
            // set the pair_count count back to zero
            pair_count = 0;
        }

        // add 2, then 4, then 6 as pairs are found
        count = count + (pair_count * 2);
    }

    cout << "    PAIRS for " << count << "\n";

    return count;
}

short unsigned int Hand::countRuns(void) {
    short unsigned int count = 0;
    short unsigned int run_count = 1;
    // bools for extra multipliers
    bool pair = false;
    bool triple = false;
    bool double_pair = false;

    for (int i=1; i < last+1; i++) {
        // check if either the current card  matches the prior card or the
        // current card is a run from the prior card and if so update
        // the multiplier or the run_count
        if (hand[i].getRank() == hand[i-1].getRank() || 
            hand[i].getRank() == (hand[i-1].getRank() + 1)) {

            // check if we continue the run
            if (hand[i].getRank() == (hand[i-1].getRank() + 1)) {
                run_count++;
            }
            // check if the next card pairs
            if (hand[i].getRank() == hand[i-1].getRank()) {
                // check if the card is a triple
                if (pair && hand[i].getRank() == hand[i-2].getRank()) {
                    triple = true;
                    pair = false;
                }
                // if it's not a triple but the last card was a pair then
                // this is a double pair
                else if
                    (pair && hand[i].getRank() != hand[i-2].getRank()) {
                    double_pair = true;
                    pair = false;
                }
                // otherwise we just have a double run so far
                else {
                    pair = true;
                }
            }
        }
        // if we don't pair and we don't run and our run is less than 3 then
        // reset our counters, otherwise break with the info we have so far.
        else {
            if (run_count > 2) {
                break;
            }
            run_count = 1;
            pair = false;
            triple = false;
            double_pair = false;
        }
    }
    // check if we have a run and what we should multiply our run_count by
    // some number depending on the type of pairs/triples in the run
    if (run_count > 2) {
        if (pair) { // double run
            count = run_count * 2;
            cout << "    DOUBLE RUN for " << count << "\n";
        }
        else if (triple) { // triple run
            count = run_count * 3;
            cout << "    TRIPLE RUN for " << count << "\n";
        }
        else if (double_pair) { // double double run
            count = run_count * 4;
            cout << "    DOUBLE DOUBLE RUN for " << count << "\n";
        }
        else { // just a run
            count = run_count;
            cout << "    SINGLE RUN for " << count << "\n";
        }
    }
    else {
        cout << "    RUN for " << count << "\n";
    }

    return count;
}


short unsigned int Hand::countFlush(Card starter) {
    short unsigned int count = 0;

    // remove the starter card from the hand to see if we have a regular flush
    removeCard(starter);

    // check for a flush in the hand
    if ((hand[0].getSuit() == hand[1].getSuit()) &&
        (hand[1].getSuit() == hand[2].getSuit()) &&
        (hand[2].getSuit() == hand[3].getSuit())) {
        count = 4;
        // check if the starter card is part of the flush
        if (hand[0].getSuit() == starter.getSuit()) {
            count++;
        }
    }

    // put the card back in the hand in case if the player still needs it there
    addCard (starter);

    cout << "    FLUSH for " << count << "\n";

    return count;
}

short unsigned int Hand::countNobs(Card starter) {
    short unsigned int count = 0;

    // remove the starter card from the hand to see if we have a regular flush
    removeCard(starter);

    for (int i=0; i < last+1; i++) {
        if (hand[i].getRank() == JACK &&
            hand[i].getSuit() == starter.getSuit()) {
            count = 1;
        }
    }

    cout << "    NOBS for " << count << "\n";

    // put the card back in the hand in case if the player still needs it there
    addCard (starter);
    return count;
}

// Like + operator but it inherits without trouble
void Hand::addHand(const Hand& h) {
    const Card *c = h.getHand();

    for (int i=0; i < h.getNumCards(); i++) {
        addCard(c[i]);
    }
}

ostream& operator << (ostream& o, const Hand& h) {
    const Card *c = h.getHand();

    for (int i=0; i < h.getNumCards(); i++) {
        o << c[i];
        if (i < h.getNumCards()) {
            cout << " ";
        }
    }

    return o;
}

Hand operator +(const Hand& h1, const Hand& h2) {
    Hand h;

    const Card *c1 = h1.getHand();
    const Card *c2 = h2.getHand();

    // Add cards from hand 1 to h
    for (int i=0; i < h1.getNumCards(); i++) {
        h.addCard (c1[i]);
    }

    // Add cards from hand 2 to h
    for (int i=0; i < h2.getNumCards(); i++) {
        h.addCard (c2[i]);
    }

    return h;
}



// =============================================================================
// Copyright 2012.
// Scott Alexander Holm.
// All Rights Reserved.
// =============================================================================

#include "card.h"

// Constructors
Card::Card (short int f) {
    face = f;
}

Card::Card (void) {
    face = -1;
}

// Mutators
void Card::setFace (short int f) {
    face = f;
}

// Accessors
short int Card::getFace (void) const {
    return face;
}

// Methods
short int Card::getSuit (void) const {
    return face / 13;
}

//  Rank is 1-13 not 0-12
short int Card::getRank (void) const {
    return ((face % 13) + 1);
}

//  Rank is 1-10.  10 and all face cards are 10
short int Card::getPlayRank (void) const {
    if (getRank() > 9) {
        return 10;
    }
    else {
        return getRank();
    }
}


ostream& operator << (ostream& o, const Card& c) {

    switch (c.getRank()) {
        case 1:
            o << "A";
            break;
        default:
            o << c.getRank();
            break;
        case 11:
            o << "J";
            break;
        case 12:
            o << "Q";
            break;
        case 13:
            o << "K";
            break;
    }

    switch (c.getSuit()) {
        case 0:
            o << "\4";
            break;
        case 1:
            o << "\5";
            break;
        case 2:
            o << "\3";
            break;
        case 3:
            o << "\6";
            break;
    }
    //o << "rank=" << c.getRank() << "\n" << "suit=" << c.getSuit() << "\n";
    return o;
}

//void Card::operator =(const Card& c) {
//    face = c.getFace();
//}

bool operator ==(const Card& c1, const Card& c2) {
    return c1.getFace() == c2.getFace();
}

int operator +(const int& count, const Card& c) {
    return (count + c.getRank());
}

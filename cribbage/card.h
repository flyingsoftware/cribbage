#ifndef CARD_H
#define CARD_H

// =============================================================================
// Copyright 2012.
// Scott Alexander Holm.
// All Rights Reserved.
// =============================================================================

#include <stdlib.h>
#include <iostream.h>

class Card {
private:
    short int face;
public:
    Card (short int f);
    Card (void);
    short int getSuit (void) const;
    short int getRank (void) const;
    short int getPlayRank (void) const;
    void setFace (short int f);
    short int getFace (void) const;
    friend ostream& operator <<(ostream& o, const Card& c);
    friend bool operator ==(const Card& c1, const Card& c2);
    friend int operator +(const int& count, const Card& c);
//    void operator =(const Card& c);
};


#endif

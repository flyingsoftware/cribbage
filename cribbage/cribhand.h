// =============================================================================
// Copyright 2012.
// Scott Alexander Holm.
// All Rights Reserved.
// =============================================================================

#ifndef CRIBHAND_H
#define CRIBHAND_H

#include <iostream.h>

#include "hand.h"
#include "card.h"
#include "deck.h"

// cribbage hand
class CribHand : public Hand {

private:
    virtual short unsigned int countFlush(Card starter);

public:

};

#endif


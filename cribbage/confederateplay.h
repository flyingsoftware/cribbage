// =============================================================================
// Copyright 2012.
// Scott Alexander Holm.
// All Rights Reserved.
// =============================================================================

#ifndef CONFEDERATEPLAY_H
#define CONFEDERATEPLAY_H

#include "play.h"

// Play without display
class ConfederatePlay : public Play {

private:
    short unsigned int seed[2];

public:
    ConfederatePlay (Player *contestant[],  short unsigned int new_count,
        Card *new_played, short int new_played_index, bool opponents_go,
        short unsigned int seed0, short unsigned int seed1);
    ConfederatePlay (Player *contestant[],
        short unsigned int seed0, short unsigned int seed1);

    // announce any points gained during play
    virtual void announcePlay(void);

    // play the confederate discard and move on
    virtual short unsigned int playCard(Card discard);
    short unsigned int playCard(void);


    // get the seed value from the current players points values
    virtual short unsigned int getCurrentPlayerPointsSeed(void);
    virtual short unsigned int getOpponentPlayerPointsSeed(void);

};

#endif

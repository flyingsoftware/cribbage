// =============================================================================
// Copyright 2012.
// Scott Alexander Holm.
// All Rights Reserved.
// =============================================================================

#ifndef CONFEDERATEPLAYER_H
#define CONFEDERATEPLAYER_H

#include "player.h"

// Cribbage Player
class ConfederatePlayer : public Player {

private:
    short unsigned int num_cards;

public:
    ConfederatePlayer (Player *p);
    ConfederatePlayer (short unsigned int new_points, short unsigned int cards);

    virtual Card playCard(short unsigned int count, Card *played,
        short int played_index, Player *opponent, bool opponents_go,
        short int current_player_points_seed,
        short int opponent_player_points_seed);

    virtual bool hasPlayRankOrLess( short unsigned int bound);
    virtual short int getNumCards () const;

};

#endif

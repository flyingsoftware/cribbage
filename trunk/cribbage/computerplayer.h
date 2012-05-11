// =============================================================================
// Copyright 2012.
// Scott Alexander Holm.
// All Rights Reserved.
// =============================================================================

#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H

#include "player.h"
//#include "play.h"
#include "confederateplay.h"

// Computer Cribbage Player
class ComputerPlayer : public Player {

private:


public:
    ComputerPlayer(void);


    // play a card in crib play
    virtual Card playCard(short unsigned int count, Card *played,
        short int played_index, Player *opponent, bool opponents_go,
        short int current_player_points_seed,
        short int opponent_player_points_seed);

    virtual Hand discardCrib(bool is_dealer, Player *opponent);

};

#endif

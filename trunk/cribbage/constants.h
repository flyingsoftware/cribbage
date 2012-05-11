// =============================================================================
// Copyright 2012.
// Scott Alexander Holm.
// All Rights Reserved.
// =============================================================================

// cribbage constants

#ifndef CONSTANTS_H
#define CONSTANTS_H

short unsigned int const NUMBER_OF_PLAYERS=2;
short unsigned int const CARDS_PER_PLAYER = 6;
short unsigned int const CARDS_TO_THROW_PER_PLAYER = 2;

short unsigned int const GAME_HOLE = 121;

short unsigned int const MAX_PLAY_COUNT = 31;

enum PlayScoring {
    NOBS=1,
    NIBS=2,
    PAIR=2,
    TRIPLE=6,
    QUADRUPLE=12,
    FIFTEEN=2,
    THIRTYONE=2,
    LASTCARD=1
    };


#endif

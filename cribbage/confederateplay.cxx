// =============================================================================
// Copyright 2012.
// Scott Alexander Holm.
// All Rights Reserved.
// =============================================================================

#include "confederateplay.h"

ConfederatePlay::ConfederatePlay (Player *contestant[],
        short unsigned int seed0, short unsigned int seed1) {

    Card *c;


    // since this is an unadalterated play we can make assumptions to make
    // it easier on the caller
    ConfederatePlay::ConfederatePlay (contestant, 0, c, -1, false, seed0, seed1);
}


ConfederatePlay::ConfederatePlay (Player *contestant[],
    short unsigned int new_count,
    Card *new_played, short int new_played_index, bool opponents_go,
    short unsigned int seed0, short  unsigned int seed1) {

    p[0] = contestant[0];
    p[1] = contestant[1];

    resetScored();
    resetPlay();

    // assume it's the first players turn
    turn = 0;

    // set a new played_index
    played_index = new_played_index;

    // copy the cards played so fard into the played array
    for (int i=0; i <= played_index; i++) {
        played[i] = new_played[i];
    }

    // set the count
    count = new_count;

    // set the opponents go
    go[!turn] = opponents_go;

    // set the seed point values
    seed[0] = seed0;
    seed[1] = seed1;


}

short unsigned int ConfederatePlay::getCurrentPlayerPointsSeed(void) {
    return seed[turn];
}

short unsigned int ConfederatePlay::getOpponentPlayerPointsSeed(void) {
    return seed[!turn];
}

short unsigned int ConfederatePlay::playCard(Card discard) {
    // preserve some values after set play
    //short unsigned int current_points;
    //short unsigned int opponent_points;

    // get the current players points
    //current_points = p[0]->getPoints();
    //opponent_points = p[1]->getPoints();


    Play::playCard (discard);

    announcePlay();

    endTurn();

    playAllSets();

    //if ( (p[0]->getPoints() - seed[0]) < 0 ) {
    //    cout << "Hypothetical play set ";
    //    for (int i=0; i <= played_index; i++) {
    //        cout << played[i] << " ";
    //    }
    //    cout << "\n";
    //    cout << *p[0] << " score: " << p[0]->getPoints() - seed[0] << "\n";
    //    cout << *p[1] << " score: " << p[1]->getPoints() - seed[1] << "\n";
    //}


    // return the number of points earned over the opponent
    return (p[0]->getPoints() - seed[0]) -
        (p[1]->getPoints() - seed[1]);

}


short unsigned int ConfederatePlay::playCard(void) {

//cout << "more stuff " << *p[1] << "\n";
    // play through it all
    playAllSets();

    // return the number of points earned over the opponent
    return (p[0]->getPoints() - seed[0]) -
        (p[1]->getPoints() - seed[1]);

}


// methods
void ConfederatePlay::announcePlay (void) {
    // do nothing
}

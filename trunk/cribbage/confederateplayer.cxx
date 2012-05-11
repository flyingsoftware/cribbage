// =============================================================================
// Copyright 2012.
// Scott Alexander Holm.
// All Rights Reserved.
// =============================================================================

#include "confederateplayer.h"
#include "computerplayer.h"

ConfederatePlayer::ConfederatePlayer (Player *p) {
    strcpy(name, "CONFEDERATE PLAYER");
    num_cards = p->getNumCards();
    points = p->getPoints();
}
ConfederatePlayer::ConfederatePlayer (short unsigned int new_points,
        short unsigned int cards) {
    strcpy(name, "CRIB TEST PLAYER");
    num_cards = cards;
    points = new_points;
}

bool ConfederatePlayer::hasPlayRankOrLess( short unsigned int bound) {
    // get rid of compiler warning
    bound;

    // if we have at least one card then we'll have a confederate card
    // to play less than bound
    return (num_cards > 0);
}

short int ConfederatePlayer::getNumCards () const {
    return num_cards;
}


// methods
Card ConfederatePlayer::playCard (short unsigned int count, Card *played,
        short int played_index, Player *opponent, bool opponents_go,
        short int current_player_points_seed,
        short int opponent_player_points_seed) {
    // trivial use of unused parameters
    //played[0];
    //played_index;
    //*opponent;

    // reduce the number of cards we can have since we'll play a card in
    // this method
    num_cards--;

    // create new array to pass to new play object
    Player *p[2];

    // new card to play
    Card test_c;

    // card to return
    Card c;

    // keep higest point value returned.  start with -infinity
    short int highest_return = -GAME_HOLE;

    // the return from the last card played
    short int current_return;

    // iterate through 0-12 card values (A-K of diamonds)
    for (int i=0; i < 13; i++) {

        // set the face of card
        test_c.setFace(i);

        // if the play rank of the card exceeds the bound then stop iterating
        // through possible cards
        if (test_c.getPlayRank() + count > MAX_PLAY_COUNT) {
            // bring the face down to the last card in bound
            test_c.setFace(i-1);
            break;
        }

        // new players
        p[0] = new ConfederatePlayer(this);
        p[1] = new ComputerPlayer();
        //*p[0] = *this;
        *p[1] = *opponent;

//cout << *p[1] << " HAND: " << p[1]->getHand() << "\n";

        ConfederatePlay confederateplay(p, count, played, played_index,
            opponents_go,
            current_player_points_seed,
            opponent_player_points_seed);

        // play a card
        current_return =
            confederateplay.playCard(
            test_c);

        // check for highest return
        if (current_return > highest_return) {
            c = test_c;
            highest_return = current_return;
        }

        // delete this line
        //confederateplay.announcePlay();

        // flip the turn
        //confederateplay.endTurn();

        // iterate through the rest of play
        //confederateplay.playSet();
        
        //cout << "card number " << i << "\n";
        //cout << "Card to Play " << choices[i] << "\n";
 
        //cout << "Card earns " << confederateplay.playCard(choices[i]) << "\n";

    // ponts_earned_over_oppenent = Game(players card)
    // if point_earned_over_opponent > highest_so_far_points_earned_over_opp
    //    then c = players card

        // clean up the temp workspace
        delete p[0];
        delete p[1];
    }

    //return addDiscard(removeRandomCardWithPlayRankOrLess(MAX_PLAY_COUNT-count));

        //for (int i = 0; i <= played_index; i++) {
        //    cout << "Played " << played[i] << "\n";
        //}
        //cout << "COUNT = " << count << "\n";
        //cout << " --------------------------- \n";

    if (c.getFace() < 0) {
        //c = test_c;
        cout << "FATAL ERROR!!!!   ABORT!!!!  NEGATIVE FACE VALUE!!!!\n";
        cout << "AHHHHHHHHHHHHHHHHHHHHHHHHHHH!!!!\n";
        cout << "COUNT = " << count << "\n";
        for (int i = 0; i <= played_index; i++) {
            cout << "Played " << played[i] << "\n";
        }
        cout << "CARD TO PLAY = " << c << "\n";
        cout << "CURRENT RETURN = " << current_return << "\n";
        cout << "HIGHEST RETURN = " << highest_return << "\n";
        
    }
    return c;

}

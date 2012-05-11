// =============================================================================
// Copyright 2012.
// Scott Alexander Holm.
// All Rights Reserved.
// =============================================================================

#include "computerplayer.h"
#include "confederateplayer.h"
#include "play.h"

// constructor
ComputerPlayer::ComputerPlayer(void) {
    strcpy(name, "DEUS EX MACHINA");
}


// Play a card during cribbage play
Card ComputerPlayer::playCard(short unsigned int count, Card *played,
        short int played_index, Player *opponent, bool opponents_go,
        short int current_player_points_seed,
        short int opponent_player_points_seed) {

        //for (int i = 0; i <= played_index; i++) {
        //    cout << "Played " << played[i] << "\n";
        //}
        //cout << "COUNT = " << count << "\n";
        //cout << "PLAYED INDEX = " << played_index << "\n";
        //cout << " --------------------------- \n";

    // card to return
    Card c;

    // keep higest point value returned.  start with -infinity
    short int highest_return = -GAME_HOLE;

    // the return from the last card played
    short int current_return;

    // array of cards in hand
    const Card *choices = h.getHand();

    // create new array to pass to new play object
    Player *p[2];

    for (int i=0; i < h.getNumCards() &&
        choices[i].getPlayRank() <= (MAX_PLAY_COUNT-count)
        ; i++) {

        p[0] = new ComputerPlayer();
        p[1] = new ConfederatePlayer(opponent);
        *p[0] = *this;

//if (getNumCards() == 4) {
//    cout << "choice = " << choices[i] << "\n";
//}

        ConfederatePlay confederateplay(p, count, played, played_index,
            opponents_go,
            current_player_points_seed,
            opponent_player_points_seed);

        // play a card
        current_return = confederateplay.playCard(p[0]->removeCard(choices[i]));

        // check for highest return
        if (current_return > highest_return) {
            c = choices[i];
            highest_return = current_return;
        }

        // clean up the temp workspace
        delete p[0];
        delete p[1];
    }

    return addDiscard(removeCard(c));
}

// Discard a 2-card hand to the crib
Hand ComputerPlayer::discardCrib (bool is_dealer, Player *opponent) {
    // the cards to throw
    Hand discard;

    // array of cards in players hand
    const Card *c = h.getHand();

    // cards we want to discard
    Card d1;
    Card d2;

    // hand to test
    Hand test_hand = getHand();

    // array of pointer to players to use
    Player *p[2];



    // set to the highest so far returned
    short int highest_return = -GAME_HOLE;
    // the last returned score count
    short int current_return;

    for (int i = 0; i < 5; i++) {
        for (int j = i+1; j < 6; j++) {

            // remove the cards from the test_hand
            test_hand.removeCard(c[i]);
            test_hand.removeCard(c[j]);

            p[is_dealer] = new ComputerPlayer;
            p[!is_dealer] = new ConfederatePlayer(opponent->getPoints(), 4);
            *p[is_dealer] = *this;
            p[is_dealer]->setHand(test_hand);

            Card *empty_c;
            ConfederatePlay confederateplay(p, 0, empty_c, -1, false,
                p[0]->getPoints(),
                p[1]->getPoints());

            current_return = (is_dealer) ?
                -confederateplay.playCard() :
                confederateplay.playCard();

cout << "CARD 1 = " << c[i] << "\n";
cout << "CARD 2 = " << c[j] << "\n";
cout << "REMAINING HAND " << test_hand << "\n";
cout << "RETURN VALUE = " << current_return << "\n";

            // test the point value of the hand
            if (current_return > highest_return) {
                d1 = c[i];
                d2 = c[j];
                highest_return = current_return;
            }

            // restore the test_hand
            test_hand.addCard (c[i]);
            test_hand.addCard (c[j]);

            // remove the used players
            delete p[0];
            delete p[1];
        } 


    }


    // Throw a couple of random cards to discard
    discard.addCard(h.removeCard(d1));
    discard.addCard(h.removeCard(d2));

    return discard;
}


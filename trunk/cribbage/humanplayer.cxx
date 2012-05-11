// =============================================================================
// Copyright 2012.
// Scott Alexander Holm.
// All Rights Reserved.
// =============================================================================

#include "humanplayer.h"
#include <iostream.h>


HumanPlayer::HumanPlayer (void) {
    strcpy (name, "MEAT");
}

// Play a card during cribbage play.
// IMPORTANT: this method assumes the user has a card that can be played.
Card HumanPlayer::playCard(short unsigned int count, Card *played,
        short int played_index, Player *opponent, bool opponents_go,
        short int current_player_points_seed,
        short int opponent_player_points_seed) {
    // get an array of cards
    const Card *c = h.getHand();
    // string input
    char input[INPUT_LENGTH];
    // persistent index
    unsigned short int index;
    // the choice meat makes
    int meat_choice;

    // trivial use of unused parameters
    //played[0];
    //played_index;
    *opponent;
    opponents_go;
    current_player_points_seed;
    opponent_player_points_seed;

    // show state of play
    cout << "Opponent holds " << opponent->getNumCards() << " cards\n";
    if (opponents_go) {
        cout << *opponent << " has GO\n";
    }
    cout << "Plaued cards: ";
    for (int i = 0; i <= played_index; i++) {
        cout << played[i] << " ";
    }
    cout << "\n";

    do {
        // show MEAT options
        cout << *this << " choices:\n";
        // display cards until we run out or the value is higher than bound
        for (index=0; index < h.getNumCards() &&
            c[index].getPlayRank() <= (MAX_PLAY_COUNT-count);
            index++) {
            cout << index << ": " << c[index] << "\n";
        }

        // if index is 1 then we only have one choice, the first card
        // if index is 0 then the first card is less than bound
        if (index == 1 || !index) {
            meat_choice = 0;
            break;
        }

        cout << "Enter card reference (0-" << index - 1 << "): ";
        cin.getline(input, INPUT_LENGTH + 1);

        // make sure MEAT makes good choice
        if (isdigit (input[0])) {
            meat_choice = atoi(input);
        }
        else {
            meat_choice = -1;
            cout << *this << " chooses invalid option\n";
        }
        //cout << "\n";
    // continue until MEAT figures it out
    } while (meat_choice < 0 || meat_choice >= index);

    //cout << *this << " plays " << c[meat_choice] << "\n";

    return addDiscard(h.removeCard(c[meat_choice]));
}

Hand HumanPlayer::discardCrib(bool is_dealer, Player *opponent) {
    // The cards to throw to the crib
    Hand crib_discard;
    // get an array of cards
    const Card *c = h.getHand();
    // string input to convert to int
    char input[INPUT_LENGTH];
    // the choice MEAT makes
    int meat_choice;

    // useless use of variables to prevent compiler warnings
    is_dealer;
    opponent;

    cout << *this << " hand: " << this->getHand() << "\n";

    // Tell MEAT what to do
    cout << "Discard to crib...\n";

    // do while 2 cards are pulled from hand h
    for (int j=0; j < 2; j++) {
        // get one card
        do {
            // show MEAT options
            cout << *this << " choices:\n";
            // display cards until we run out
            for (int i=0; i < h.getNumCards(); i++) {
                cout << i << ": " << c[i] << "\n";
            }

            cout << "Enter card reference (0-" << h.getNumCards() - 1 << "): ";
            cin.getline (input, INPUT_LENGTH + 1);
            // make sure MEAT makes good choice
            if (isdigit (input[0])) {
                meat_choice = atoi(input);
            }
            else {
                meat_choice = -1;
                cout << *this << " chooses invalid option\n";
            }
            //cout << "\n";
        // continue until MEAT figures it out
        } while (meat_choice < 0 || meat_choice >= h.getNumCards());

        // remove the card from players hand while adding it to crib discard
        crib_discard.addCard(h.removeCard(c[meat_choice]));
    }

    cout << *this << " discards " << crib_discard << "\n";
    cout << "\n";

    return crib_discard;
}

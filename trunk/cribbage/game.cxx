// =============================================================================
// Copyright 2012.
// Scott Alexander Holm.
// All Rights Reserved.
// =============================================================================

#include "game.h"
#include "play.h"
#include "confederateplay.h"

#include <iostream.h>

// Constructors

Game::Game (void) {

    // game on
    gameover = false;

}

// Methods


// Run the game
void Game::run (void) {

    // We need players
    Player *p[NUMBER_OF_PLAYERS];
    //p[0] = new HumanPlayer();
    p[0] = new Player("DMMMY PLAYER");
    //p[0] = new ComputerPlayer();
    p[1] = new ComputerPlayer();

    cout << *p[0] << " vs " << *p[1] << "\n\n";

    // What player is the dealer.
    dealer = decideDealer(p);
    cout << "The dealer is " << *p[dealer] << "\n";
    cout << "\n";

    // vacuious scorecard display
    scorecard (p);

    short int starting_dealer = dealer;

    int p0_wins = 0;
    int p1_wins = 0;

    for (int i=0; i < 1; i++) {





    // play until someone wins
    while (!gameover) {
        // make sure no players are holding any cards
        p[!dealer]->discardHand();
        p[dealer]->discardHand();
        crib.discardHand();

        deal(p);
        discardCrib(p);

//cout << *p[1] << ": " << p[1]->getHand() << "\n";
        cut(p);
        if (gameover) {
            break;
        }
        play(p);
        if (gameover) {
            break;
        }
        count(p);
        if (gameover) {
            break;
        }


        // switch the dealer
        dealer = !dealer;
        cout << "The dealer is now " << *p[dealer] << "\n";
        cout << "\n";
    }






    // announce the winner
    cout << "The winner is ";
    if (p[0]->getPoints() == GAME_HOLE) {
        p0_wins++;
        cout << *p[0] << "\n\n";
    } else {
        p1_wins++;
        cout << *p[1] << "\n\n";
    }

    // print some stats
    cout << *p[0] << " wins: " << p0_wins << "\n";
    cout << *p[1] << " wins: " << p1_wins << "\n";
   
    // switch the dealer
    dealer = !starting_dealer;
    starting_dealer = dealer;

    // announce the dealer switch
    cout << "\n\nThe dealer is now " << *p[dealer] << "\n";

    // reset the game to zero
    p[0]->setPoints(0);
    p[1]->setPoints(0);
    gameover = false;
    }

}

// Cut for deal.  Assume only two players can cut for now.
short int Game::decideDealer(Player *p[]) {

    // I have no idea why I did it this way
    short unsigned int first = 0;

    Card cut[NUMBER_OF_PLAYERS];

    // get a cut card for each player
    for (int i=0; i < NUMBER_OF_PLAYERS; i++) {
        cut[(first + i) % NUMBER_OF_PLAYERS] =
            p[(first + i) % NUMBER_OF_PLAYERS]->dealCut(i, d);
        cout << "Cut card for player " <<
            *p[((first + i) % NUMBER_OF_PLAYERS)]
            << ": " << cut[(first + i) % NUMBER_OF_PLAYERS] << "\n"; 
    }

    if (cut[first].getRank() == cut[(first+1) % NUMBER_OF_PLAYERS].getRank()) { 
        return decideDealer(p);
    }
    else if
        (cut[first].getRank() < cut[(first+1) % NUMBER_OF_PLAYERS].getRank()) {
        return first;
    }
    // the second player cuts
    else {
        return (first + 1) % NUMBER_OF_PLAYERS;
    }
   
}

void Game::deal (Player *p[]) {

    // Semantics but dealer need to deal the deck.
    // player 'dealer' deal 'CARDS_PER_PLAYER' to 'NUMBER_OF_PLAYERS' in
    // players p[]
    p[dealer]->deal (dealer, CARDS_PER_PLAYER, NUMBER_OF_PLAYERS, p, d);

    //cout << *p[dealer] << " hand " << p[dealer]->getHand() << "\n";
    //cout << *p[!dealer] << " hand   " << p[!dealer]->getHand() << "\n";

}

// have players discard cars to the crib
void Game::discardCrib (Player *p[]) {
    Hand discard;

    for (int i=0; i < NUMBER_OF_PLAYERS; i++) {
        discard = p[i]->discardCrib( (dealer == i), p[!i] );
        crib.addHand(discard);
        //cout << *p[i] << " discard " << discard << "\n";
    }

    //cout << *p[dealer] << " hand " << p[dealer]->getHand() << "\n";
    //cout << *p[!dealer] << " hand   " << p[!dealer]->getHand() << "\n";
    //cout << "Crib hand   " << crib << "\n";
}

bool Game::scorecard (Player *p[]) {

    cout << "\n";
    cout <<
        "BOARD:";
    cout << "\n";
    cout << "    " << *p[0] << " " << p[0]->getPoints() << "\n";
    cout << "    " << *p[1] << " " << p[1]->getPoints() << "\n";
    cout << "\n";
    if (p[0]->getPoints() == GAME_HOLE || p[1]->getPoints() == GAME_HOLE) {
        gameover = true;
        return true;
    }
    return false;
}

// Get the person to the left of the dealer to cut the starter card
bool Game::cut (Player *p[]) {
    // The game of cribbage requires at a cut at least 4 cards deep
    // and not at least 4 cards off the bottom
    starter = p[(dealer + 1) % NUMBER_OF_PLAYERS]->cut(d, 4, 4);

    cout << "Starter card: " << starter << "\n";

    // check for 'his heels'
    if (starter.getRank() == JACK) {
        p[dealer]->peg(NIBS);
        cout << *p[dealer] << " announce NIBS\n";
    }


    return scorecard(p);
}


bool Game::play (Player *p[]) {
    // The players turn
    //bool turn = !dealer;

    // the play object
    Play *play = new Play(p, dealer);

    gameover = play->playAllSets();

    // Make each player pick up their hand
    for (int i=0; i < NUMBER_OF_PLAYERS; i++) {
        p[i]->restoreDiscards();
        //p[i]->addHand(h[i]);
    }

    if (gameover) {
        scorecard(p);
    }

    return gameover;
}

// count the hands
bool Game::count (Player *p[]) {
    // holder for card count
    short int count;

    // quick recap of points
    scorecard(p);

    // count the person who didn't deal
    //p[!dealer]->addCard(starter);
    cout << *p[!dealer] << " counts..." << "\n";
    count = p[!dealer]->countHand(starter);
    cout << *p[!dealer] << " pegs     " << count << "\n";
    p[!dealer]->peg(count);
    if (scorecard(p)) {
        return gameover;
    }

    // count the dealer
    //p[dealer]->addCard(starter);
    cout << *p[dealer] << " counts..." << "\n";
    count = p[dealer]->countHand(starter);
    cout << *p[dealer] << " pegs   " << count << "\n";
    p[dealer]->peg(count);
    if (scorecard(p)) {
        return gameover;
    }

    // count the crib
    //crib.addCard(starter);
    cout << *p[dealer] << " counts crib..." << "\n";
    count = crib.countHand(starter);
    cout << *p[dealer] << "'s crib " << count << "\n";
    p[dealer]->peg(count);
    if (scorecard(p)) {
        return gameover;
    }

    return gameover;
}

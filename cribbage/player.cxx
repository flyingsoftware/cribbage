// =============================================================================
// Copyright 2012.
// Scott Alexander Holm.
// All Rights Reserved.
// =============================================================================

#include "player.h"
#include "game.h"
#include <string.h>

// Constructors
Player::Player (void) {
    // start with 0 points
    points = 0;    

    // set go to false
    //go = false;

    strcpy(name, "DUMMY PLAYER");

}

Player::Player(char *new_name) {
    Player::Player();
    strcpy(name, new_name);
}


// Methods
void Player::addCard (Card c) {
    h.addCard(c);
}

Card Player::addDiscard (Card c) {
    return played.addCard(c);
}

void Player::restoreDiscards (void) {
    h = played;
    played.discardHand();
}

void Player::addHand (const Hand& newh) {
    h.addHand(newh);
}

void Player::setHand (Hand newh) {
    h = newh;
}

Hand Player::getHand (void) const {
    return h;
}



// Assume there are only two people cutting so only {0,1} in order
Card Player::dealCut (short int order, const Deck& d) const {
    
    // if the order is 0 then cut from the top half of the deck, excluding
    // the first 4 cards.
    if (! order) {
        return d.dealCut ((DECK_SIZE / 2) + 1, DECK_SIZE - 4);
    }
    // else cut from the bottom half excluding the , exluding the 4 last cards
    else {
        return d.dealCut (4, (DECK_SIZE / 2));
    }
}

// Have the player deal
void Player::deal (short int dealer, short int cards, short int players,
    Player *p[], Deck& d) {

    // shuffle before you deal.  For the highly pendandic semantic on shuffling
    // rules see the ACC rule sheet.
    d.shuffle ();

    // Deal 'cards' cards
    for (int i=0; i < cards; i++) {
        // Deal to 'players' players
        for (int j=0; j < players; j++) 	{
            // start deal to next player in rotation
            p[(dealer + j) % players]->addCard(d.draw());
        }
    }
}

// Discard a 2-card hand to the crib
Hand Player::discardCrib (bool is_dealer, Player *opponent) {
    Hand discard;

    // unused but needed to prevent warning
    is_dealer;
    opponent;

    // Throw a couple of random cards to discard
    discard.addCard(h.removeRandomCard());
    discard.addCard(h.removeRandomCard());

    return discard;
}

Card Player::removeRandomCard(void) {
    return h.removeRandomCard ();
}

Card Player::removeCard(Card c) {
    return h.removeCard(c);
}

Card Player::cut (Deck& d, short int top_offset, short int bottom_offset) {
    return d.cut(top_offset, bottom_offset);
}

short unsigned int Player::peg (short unsigned int p) {
    points = points + p;
    // we can't exceed GAME_HOLE points
    if (points > GAME_HOLE) {
        points = GAME_HOLE;
    }
    return points;
}

bool Player::isWinner(void) {
    return (points == GAME_HOLE);
}

short unsigned int Player::setPoints (short unsigned int p) {
    points = p;
    return points;
}

short unsigned int Player::getPoints(void) {
    return points;
}

// Dummy method to access Hand method
short int Player::getNumCards () const {
    return h.getNumCards ();
}

// Is someone telling you "'rank' or less drunkey..."
bool Player::hasPlayRankOrLess (short unsigned int bound) {
    return h.hasPlayRankOrLess(bound);
}

Card Player::removeRandomCardWithPlayRankOrLess (short unsigned int bound) {
    return h.removeRandomCardWithPlayRankOrLess(bound);
}

// Play a card during cribbage play
Card Player::playCard(short unsigned int count, Card *played,
        short int played_index, Player *opponent, bool opponents_go,
        short int current_player_points_seed,
        short int opponent_player_points_seed) {

    // trivial use of unused parameters
    played[0];
    played_index;
    *opponent;
    opponents_go;
    current_player_points_seed;
    opponent_player_points_seed;

    return addDiscard(removeRandomCardWithPlayRankOrLess(MAX_PLAY_COUNT-count));
}


Hand Player::discardHand (void) {
    return h.discardHand();
}

short unsigned int Player::countHand(Card starter) {
    return h.countHand(starter);
}

const char *Player::getName (void) const {
    return name;
}

// shout out what state you put play in.
//void Player::announcePlay (Play p) {
//    cout << name << " discards " << p.getDiscard() << "\n";
//    cout << name << " announces count is " << p.getCount() << "\n";
//    if (p.fifteenScored()) {
//        cout << name << " announces FIFTEEN\n";
//    }
//    if (p.thirtyoneScored()) {
//        cout << name << " announces THIRTYONE\n";
//    }
//    if (p.quadrupleScored()) {
//        cout << name << " announces QUADRUPLE\n";
//    }
//    if (p.tripleScored()) {
//        cout << name << " announces TRIPLE\n";
//    }
//    if (p.pairScored()) {
//        cout << name << " announces PAIR\n";
//    }
//    if (p.runScored()) {
//        cout << name << " announces RUN of " << p.runScored() << "\n";
//    }
//
//    if (p.pointsEarned()) {
//        cout << name << " pegs " << p.pointsEarned() << "\n";
//        cout << name << " moves to peg " << points << "\n";
//    }
//
//
//}

//bool Player::isGo(void) {
//    return go;
//}

//void Player::setGo(bool g) {
//    go = g;
//}

bool Player::canPlay(short unsigned int count) {
    return (getNumCards() && hasPlayRankOrLess(MAX_PLAY_COUNT-count));
}


ostream& operator << (ostream& o, const Player& p) {
    o << p.getName();
    return o;
}

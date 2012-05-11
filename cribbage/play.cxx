// =============================================================================
// Copyright 2012.
// Scott Alexander Holm.
// All Rights Reserved.
// =============================================================================

#include "play.h"
#include "game.h"

// constructor
//Play::Play (void) {
//cout << "BASE CONSTRUCTOR RUNS!!!\n";
//}

Play::Play (void) {
    resetScored();
    resetPlay();
}


Play::Play (Player *contestant[], bool dealer) {
    p[0] = contestant[0];
    p[1] = contestant[1];
    turn = !dealer;

    resetScored();
    resetPlay();
}



void Play::resetPlay (void) {
    // index into cards played
    played_index = -1;

    // the running count
    count = 0;

    // reset the gos
    go[0] = false;
    go[1] = false;
}

void Play::resetScored (void) {

    // reset the point makers
    fifteen = false;
    thirtyone = false;
    quadruple = false;
    triple = false;
    pair = false;
    run = 0;
    // point marker for no points
    last = false;

    // reset the points earned from the last play
    earned = 0;

}



// accessor
bool Play::fifteenScored(void) {
    return fifteen;
}
bool Play::thirtyoneScored(void) {
    return thirtyone;
}
bool Play::quadrupleScored(void) {
    return quadruple;
}
bool Play::tripleScored(void) {
    return triple;
}
bool Play::pairScored(void) {
    return pair;
}
short unsigned int Play::runScored(void) {
    return run;
}
bool Play::lastScored(void) {
    return last;
}

short unsigned int Play::pointsEarned(void) {
    return earned;
}

bool Play::isGo() {
    return go[turn];
}

void Play::setGo(short unsigned int turn) {
    go[turn] = true;
}

// methods

// return true when both players are a go or the count is MAX_PLAY_COUNT
bool Play::countReached(void) {
    return ((go[0] && go[1]) || count == MAX_PLAY_COUNT);
}

bool Play::isLast(void) {
    return (go[!turn] && !go[turn]);
}

bool Play::setLast(void) {

    // if we set the last for the current move then we also set the go
    go[turn] = true;

    // we earn a point for last
    earned = 1;

    // give the play their due points
    p[turn]->peg(earned);

    return (last = true);
}


bool Play::playOver(void) {
    return (!p[0]->getNumCards() && !p[1]->getNumCards());
}


// get the running count
short unsigned int Play::getCount (void) {
    return count;
}


// set the count
void Play::setCount (short unsigned int new_count) {
    count = new_count;
}


// return the last card discarded
Card Play::getDiscard(void) {
    return played[played_index];
}

// play the discard
short unsigned int Play::playCard(Card discard) {

    // up the count of play
    count = count + discard.getPlayRank();

    // nuke the scored states
    //resetScored();

    // the points earned by the play
    //short unsigned int earned = 0;

    // bucket to find non-sequential runs
    bool rank_bucket[13];
    // counts for non-sequential runs
    short unsigned int run_count;
    short unsigned int max_run_count;

    // add the new card into the play sequence
    played[++played_index] = discard;

    // if count is 15 give the player whos turn it is 2
    if (count == 15) {
        earned = earned + FIFTEEN;
        fifteen = true;
    }
    // if count is MAX_PLAY_COUNT give the player whos turn it is 2
    if (count == MAX_PLAY_COUNT) {
        earned = earned + THIRTYONE;
        thirtyone = true;

    }
    // check for quadruple
    if (played_index > 2 &&
        played[played_index].getRank()== played[played_index-1].getRank() &&
        played[played_index-1].getRank()== played[played_index-2].getRank() &&
        played[played_index-2].getRank()== played[played_index-3].getRank())
    {
        earned = earned + QUADRUPLE;
        quadruple = true;
    }
    // check for triple
    else if (played_index > 1 &&
        played[played_index].getRank()== played[played_index-1].getRank() &&
        played[played_index-1].getRank()== played[played_index-2].getRank())
    {
        earned = earned + TRIPLE;
        triple = true;
    }
    // check for pair
    else if (played_index > 0 &&
        played[played_index].getRank()== played[played_index-1].getRank())
    {
        earned = earned + PAIR;
        pair = true;
    }

    // check for runs

    // start using a bucket sort to make a new run for each card
    // played starting with the last card played.  If the run
    // created contains as many cards as thus attempted to make
    // a run of then we have a run of at least that many points.

    if (played_index > 1) {
        // max run count found
        max_run_count = 1;

        // dump the rank buckets
        for (int i=0; i < 13; i++) {
            rank_bucket[i] = false;
        }

        for (int i=played_index; i > -1; i--) {
            // toss rank into bucket
            rank_bucket[played[i].getRank()-1] = true;
            run_count = 1;

            // search for run in rank_bucket
            for (int j=1; j < 13; j++) {
                // if the current bucket if full and the previous
                // bucket is full then we have the start of a run
                if (rank_bucket[j] && rank_bucket[j-1]) {
                    run_count++;
                }
            }
            // if the run_count is the same as the number
            // of cards that have been checked so far then
            // we have the biggest run so far
            if (run_count == (played_index - i + 1)) {
                max_run_count = run_count;
            }
        }


        // if the run_count is more than two then peg it
        if (max_run_count > 2) {
            earned = earned + max_run_count;
            run = max_run_count;
        }
    }

    // give the play their due points
    p[turn]->peg(earned);

    // this may not be required but could be nice for computer analysis
    return earned;
}



// shout out what state you put play in.
void Play::announcePlay (void) {

    if (lastScored()) {
        cout << *p[turn] << " announces LAST\n";
    }
    else {
        if (!isGo()) {
            cout << *p[turn] << " discards " << getDiscard() << "\n";
        }
        if (fifteenScored()) {
            cout << *p[turn] << " announces FIFTEEN\n";
        }
        if (thirtyoneScored()) {
            cout << *p[turn] << " announces THIRTYONE\n";
        }
        if (quadrupleScored()) {
            cout << *p[turn] << " announces QUADRUPLE\n";
        }
        if (tripleScored()) {
            cout << *p[turn] << " announces TRIPLE\n";
        }
        if (pairScored()) {
            cout << *p[turn] << " announces PAIR\n";
        }
        if (runScored()) {
            cout << *p[turn] << " announces RUN of "
                << runScored() << "\n";
        }
    }
  

    if (pointsEarned()) {
        cout << *p[turn] << " pegs " << pointsEarned() << "\n";
        cout << *p[turn] << " moves to peg " << p[turn]->getPoints()
            << "\n";
    }

    
    // always annuonce the count if it went up but not if the play is over
    // if the count is MAX_PLAY_COUNT then announce the count is 0 otherwise
    // announce the running count
    if (!lastScored() && !playOver() && !isGo() && !thirtyoneScored()) {
        cout << *p[turn] << " announces count is " << getCount() << "\n";
    }
    else if (isGo() && !playOver() && !lastScored()) {
        cout << *p[turn] << " announces GO\n";
    }

    if ((thirtyoneScored() || lastScored()) && !playOver()) {
        cout << *p[turn] << " announces count is 0\n";
    }

}



void Play::endTurn(void) {
    turn = !turn;
}

bool Play::getTurn(void) {
    return turn;
}

short unsigned int Play::getCurrentPlayerPointsSeed(void) {
    return p[turn]->getPoints();
}

short unsigned int Play::getOpponentPlayerPointsSeed(void) {
    return p[!turn]->getPoints();
}

// return true if winner created
bool Play::playSet(void) {

    // play until both players have said 'go'
    while (!countReached()) {

        resetScored();

        // if we have 1 or more cards in hand and we have at least one
        // card that does not have a play rank exceeding MAX_PLAY_COUNT
        if (p[turn]->canPlay(getCount())) {
            playCard(p[turn]->playCard(getCount(), played, played_index,
                p[!turn], go[!turn],
                getCurrentPlayerPointsSeed(), getOpponentPlayerPointsSeed()));

        }
        else  {
            // if the current player hasn't said go, can't play a card
            // and the oponent has already said go then we get a point for
            // last card.  (points for MAX_PLAY_COUNT should have already been
            // taken
            // before we got here)
            if (isLast()) {
                // set 'last' in play class
                setLast();
            }
            // we don't have a card to throw and the pone already had a go
            else {
                // set go
                setGo(turn);
            }
        }

        // player announces states of play that earns points
        announcePlay();

        if (p[turn]->isWinner()) {
            return 1;
        }

        // make it the next players turn
        endTurn();

    }
    return 0;
}

bool Play::playAllSets(void) {

    bool gameover = false;

    // play until there are no cards in the players hands
    while (!playOver()) {
        
        gameover = playSet();

        if(gameover) {
            break;
        }
        resetPlay();
    }

    return gameover;
}




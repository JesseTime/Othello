#ifndef Opponent_h
#define Opponent_h

#include "GlobalAndIncludes.h"

class Player{
private:
    int color;
    
public:
    Player(int c = BLACK) { color = c; }
    virtual ~Player() { };
    int getColor() { return color; }
    void setColor(int c) { color = c; }
    ///////// This needs to be changed back
    virtual void move(int[8][8], pair<int,int>&) = 0;
};

// end testing code

class Move {
public:
    pair<int, int> position;
    int score;
    bool operator<(const Move &other) const {
        return (this->score < other.score);
    }

    Move(pair<int, int> p, int s) {
        position = p;
        score = s;
    }

    Move(Move const &other) {
        position = other.position;
        score = other.score;
    }
};

class Opponent: public Player
{
public:
	Opponent(int c = BLACK):Player(c) {;}
    //**************************************************************************
    // name: move                                                              *
    // description: finds a location to place a piece for the current move of  *
    //              Othello given the board.                                   *
    // return type: void                                                       *
    // pre: the board information is valid and reflects the current state of   *
    //      the game.                                                          *
    // post: the move reference passed is changed to the decided piece         *
    //       placement                                                         *
    // returns: nothing                                                        *
    //**************************************************************************
    void move(int[8][8], pair<int,int>&);
	set<Move> findMoves(int, vector<pair<int, int> > const &, int[8][8]);
};



#endif
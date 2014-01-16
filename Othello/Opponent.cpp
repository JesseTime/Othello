#include "Opponent.h"

//*****************************************************************************
// name: findMoves                                                            *
// description: finds all on the moves for a particular color and returns it  *
//     as a set                                                               *
// return type: set<Move>                                                     *
// pre: the color integer is a valid value, the board is valid, and the       *
//     pieces/oppPiece vectors contain valid places on the board of           *
//     the proper color for each player.                                      *
// post: the pieces/oppPiece vectors and board is unchanged                   *
// returns: a set containing the possible moves for a player                  *
//*****************************************************************************
set<Move> Opponent::findMoves(int color, 
                    vector<pair<int, int> > const &oppPiece, int b[8][8]) {
    set<Move> moves;
    int opponent;
    if (color == WHITE) {
        opponent = BLACK;
    } else {
        opponent = WHITE;
    }
    // for all opponents pieces
    for (unsigned int piece = 0; piece < oppPiece.size(); piece++) {
        // for all directions
        for(int dir1 = 0; dir1 < 8; dir1++) {
            // make a move for each direction in adjMovs
            pair<int,int> move = make_pair(oppPiece[piece].first +
                                           adjMovs[dir1].first,
                                           oppPiece[piece].second +
                                           adjMovs[dir1].second);
            // if that move is on the board and is BLANK
            if (move.first >= 0 && move.first < 8 &&
                move.second >= 0 && move.second < 8 &&
                b[move.first][move.second] == BLANK) {
                // keep track of score
                int score = 0;
                // for all directions
                for (int dir2 = 0; dir2 < 8; dir2++) {
                    // keep track of score for each direction
                    int dirScore = 0;
                    pair<int, int> nextDir;
                    nextDir.first = move.first + adjMovs[dir2].first;
                    nextDir.second = move.second + adjMovs[dir2].second;

                    while (nextDir.first >= 0 && nextDir.first < 8 &&
                           nextDir.second >= 0 && nextDir.second < 8 &&
                           b[nextDir.first][nextDir.second] == opponent) {
                        dirScore++;
                        nextDir = make_pair(nextDir.first + adjMovs[dir2].first,
                                            nextDir.second + adjMovs[dir2].second);
                    }
                    if (nextDir.first >= 0 &&
                        nextDir.first < 8 &&
                        nextDir.second >= 0 &&
                        nextDir.second < 8 &&
                        b[nextDir.first][nextDir.second] == color) {
                        score += dirScore;
                    }
                }
                // if the move is a valid move (it took an opponents piece)
                if (score > 0) {
                    int cols = 8;
                    int rows = 8;
                    // if the move is a corner spot, set to highest priority
                    if ((move.first == 0 && move.second == 0) ||
                        (move.first == 0 && move.second == cols - 1) ||
                        (move.first == rows - 1 && move.second == 0) ||
                        (move.first == rows - 1 && move.second == cols - 1)) {
                        score = -(cols * rows);
                    }
                    // if the move is the piece diagonal to the corner piece,
                    // set to lowest priority
                    else if ((move.first == 1 && move.second == 1) ||
                             (move.first == 1 && move.second == cols - 2) ||
                             (move.first == rows - 2 && move.second == 1) ||
                             (move.first == rows - 2 && move.second == cols - 2)) {
                        score = (cols * rows);
                    }

                    // if the move is adjacent to a corner spot and the corner
                    // spot has a piece in it, prioritize the move as high
                    // if the corner spot is BLANK, prioritize to low
                    else if (move.first == 0 && move.second == 1) {
                        if (b[0][0] == BLANK) score = 3*rows;
                        else score = 0;
                    }
                    else if (move.first == 0 && move.second == cols - 2) {
                        if (b[0][cols-1] == BLANK) score = 3*rows;
                        else score = 0;
                    }
                    else if (move.first == rows - 1 && move.second == 1) {
                        if (b[rows-1][0] == BLANK) score = 3*rows;
                        else score = 0;
                    }
                    else if (move.first == rows - 1 && move.second == cols - 2){
                        if (b[rows-1][cols-1] == BLANK) score = 3*rows;
                        else score = 0;
                    }

                    else if (move.first == 1 && move.second == 0) {
                        if (b[0][0] == BLANK) score = 3*rows;
                        else score = 0;
                    }
                    else if (move.first == 1 && move.second == cols - 1) {
                        if (b[0][cols-1] == BLANK) score = 3*rows;
                        else score = 0;
                    }
                    else if (move.first == rows - 2 && move.second == 0) {
                        if (b[rows-1][0] == BLANK) score = 3*rows;
                        else score = 0;
                    }
                    else if (move.first == rows - 2 && move.second == cols - 1){
                        if (b[rows-1][cols-1] == BLANK) score = 3*rows;
                        else score = 0;
                    }

                    // if the move is an edge move, prioritize it to high
                    else if (move.first == 0 || move.first == rows - 1 ||
                             move.second == 0 || move.second == cols - 1) {
                        score = 0;
                    }

                    moves.insert(Move(move, score));
                }
            }
        }
    }
    return moves;
}

//*****************************************************************************
// name: move                                                                 *
// description: finds a location to place a piece for the current move of     *
//     Othello given the board.                                               *
// return type: void                                                          *
// pre: the board information is valid and reflects the current state of the  *
//     game.                                                                  *
// post: the move reference passed is changed to the decided piece placement  *
// returns: nothing                                                           *
//*****************************************************************************
void Opponent::move(int b[8][8], pair<int,int> &move) {
    int color = getColor();
    int opponent;
    if (color == WHITE) {
        opponent = BLACK;
    } else {
        opponent = WHITE;
    }

    vector<pair<int, int> > oppPieces;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (b[i][j] == opponent){
                oppPieces.push_back(make_pair(i, j));
            }
        }
    }

    set<Move> moves = findMoves(color, oppPieces, b);

    if (!moves.empty()) {
        move = moves.begin()->position;
    }
}
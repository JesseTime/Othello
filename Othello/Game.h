#ifndef Game_h
#define Game_h

#include "GlobalAndIncludes.h"
#include "Opponent.h"
#include "Human.h"

class Game
{
private:
	//The surfaces
	SDL_Surface *board;
	SDL_Surface *screen;
	SDL_Surface *blackPiece;
	SDL_Surface *whitePiece;
	SDL_Surface *validDot;
	SDL_Surface *messageP;
	SDL_Surface *messageR;
	SDL_Surface *messageF;
	SDL_Surface *messageM;
	SDL_Surface *messageE;
	SDL_Surface *score;
	SDL_Surface *pscore;
	SDL_Surface *oscore;
	SDL_Surface *youwin;
	SDL_Surface *youlose;
	SDL_Surface *tie;
	SDL_Surface *logo;
	SDL_Surface *black;
	SDL_Surface *objection;
	SDL_Surface *coffee;

	//corgi stuff
	SDL_Surface *cblackPiece;
	SDL_Surface *cwhitePiece;
	SDL_Surface *cvalidDot;
	SDL_Surface *cyouwin;
	SDL_Surface *cyoulose;
	SDL_Surface *ctie;
	SDL_Surface *clogo;
	SDL_Surface *ccoffee;
	SDL_Surface *cobjection;
	Mix_Music *cbgMusic;
	Mix_Chunk *cplace;

	//event
	SDL_Event event;

	//music and sfx
	Mix_Music *bgMusic;
	Mix_Chunk *victory;
	Mix_Chunk *lose;
	Mix_Chunk *no;
	Mix_Chunk *place;
	Mix_Chunk *tieChunk;
	Mix_Chunk *obj;
	Mix_Chunk *cof;

	//font
	TTF_Font *font;

	int boardState[8][8];
	vector<int> playerScore;
	vector<int> opponentScore;
	Human human;
	Opponent computer;

	//flags
	bool playerChoice;
	bool playerTurn;
	bool windowed;
	bool endGame;
	bool soundPlayed;
	bool cMode;
public:
	Game();
	virtual ~Game();
	SDL_Surface* load_image(string filename, bool alpha);
	void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination);
	bool init();
	bool load_files();
	void play();
	void clean_up();
	void flipPieces(pair<int,int>&, int);
	bool isValid(int, int,  pair<int,int>&);
	void determineScore(vector<int>&, int);
	void determineWinner(vector<int>&, vector<int>&);
	void applyText();
	void placeValidDot();
	bool loadTheCorgis(bool&);
	void reset();
	void chooseColor(bool&);
	void cornerTaken();
	void opponentCornerTaken();
	void displayGamestate();
	void toggle_fullscreen();
};

#endif
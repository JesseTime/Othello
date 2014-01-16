#include "Game.h"

Game::Game()
{
	//surfaces
	board = NULL;
	screen = NULL;
	blackPiece = NULL;
	whitePiece = NULL;
	validDot = NULL;
	messageP = NULL;
	messageR = NULL;
	messageF = NULL;
	messageE = NULL;
	messageM = NULL;
	score = NULL;
	pscore = NULL;
	oscore = NULL;
	youwin = NULL;
	youlose = NULL;
	tie = NULL;
	logo = NULL;
	black = NULL;
	objection = NULL;

	//corgi
	cblackPiece = NULL;
	cwhitePiece = NULL;
	cvalidDot = NULL;
	cyouwin = NULL;
	cyoulose = NULL;
	ctie = NULL;
	clogo = NULL;
	cobjection = NULL;
	ccoffee = NULL;
	cbgMusic = NULL;
	cplace = NULL;

	//font
	font = NULL;

	//music and sfx
	bgMusic = NULL;
	victory = NULL;
	lose = NULL;
	no = NULL;
	place = NULL;
	tieChunk = NULL;
	obj = NULL;
	cof = NULL;

	//flags
	windowed = true;
	endGame = false;
	soundPlayed = false;
	playerTurn = true;
	playerChoice = false;
	cMode = false;

	//initial board
	for(int i = 0; i < 8; i++)
		for(int j = 0; j < 8; j++)
			boardState[i][j] = BLANK;
	boardState[3][3] = WHITE;
	boardState[4][4] = WHITE;
	boardState[4][3] = BLACK;
	boardState[3][4] = BLACK;
}

Game::~Game()
{
	
}

SDL_Surface* Game::load_image(string filename, bool alpha = false)
{
	SDL_Surface* loadedImage = NULL;

	SDL_Surface* optimizedImage = NULL;

	loadedImage = IMG_Load(filename.c_str());

	if(loadedImage != NULL)
	{
		optimizedImage = SDL_DisplayFormat(loadedImage);
		if(alpha)
			optimizedImage = SDL_DisplayFormatAlpha(loadedImage);
		SDL_FreeSurface(loadedImage);
	}
	return optimizedImage;
}

void Game::apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination)
{
	SDL_Rect offset;

	offset.x = x;
	offset.y = y;

	SDL_BlitSurface(source, NULL, destination, &offset);
}

bool Game::init()
{
	if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
		return false;
	screen = SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,SCREEN_BPP,SDL_SWSURFACE);

	if(screen == NULL)
		return false;
	if(TTF_Init() == -1)
		return false;

	int flags = IMG_INIT_JPG | IMG_INIT_PNG;
    int initted = IMG_Init(flags);
    if( (initted & flags) != flags) {
        return false;
    }

	if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
    {
        return false;    
    }

	SDL_WM_SetCaption("Othello", NULL);

	return true;
}

bool Game::load_files()
{
	//Load images
	board = load_image("Assets/background.png");
	whitePiece = load_image("Assets/white.png", true);
	blackPiece = load_image("Assets/black.png", true);
	validDot = load_image("Assets/validDot.png", true);
	youwin = load_image("Assets/youwin.png", true);
	youlose = load_image("Assets/youlose.png", true);
	tie = load_image("Assets/tie.png", true);
	logo = load_image("Assets/logo.png", true);
	black = load_image("Assets/blackbg.png");
	objection = load_image("Assets/objection.png", true);
	coffee = load_image("Assets/coffee.png", true);

	if(board == NULL || whitePiece == NULL || blackPiece == NULL || validDot == NULL || youwin == NULL || youlose == NULL || logo == NULL || tie == NULL || black == NULL || objection == NULL || coffee == NULL)
		return false;
	
	//Load font
	font = TTF_OpenFont("lazy.ttf", 28);

	if(font == NULL)
		return false;

	//Load the music
    bgMusic = Mix_LoadMUS( "Assets/bgMusic.ogg" );
	Mix_VolumeMusic(50);

	victory = Mix_LoadWAV( "Assets/victory.wav" );
    Mix_VolumeChunk(victory, 5);

	lose = Mix_LoadWAV( "Assets/lose.wav" );
    Mix_VolumeChunk(lose, 30);

	no = Mix_LoadWAV( "Assets/no.wav" );
    Mix_VolumeChunk(no, 30);

	tieChunk = Mix_LoadWAV( "Assets/tie.wav" );
    Mix_VolumeChunk(tieChunk, 50);

	place = Mix_LoadWAV( "Assets/place.wav" );
    Mix_VolumeChunk(place, 255);

	obj = Mix_LoadWAV( "Assets/objection.wav" );
    Mix_VolumeChunk(obj, 255);

	cof = Mix_LoadWAV( "Assets/coffee.wav" );
    Mix_VolumeChunk(cof, 255);

    //If there was a problem loading the music
	if( bgMusic == NULL )
        return false; 
	if(victory == NULL || lose == NULL || no == NULL || place == NULL || tieChunk == NULL || obj == NULL || cof == NULL)
		return false;


	cwhitePiece = load_image("cMode/cwhite.png", true);
	cblackPiece = load_image("cMode/cblack.png", true);
	cvalidDot = load_image("cMode/cvalidDot.png", true);
	cyouwin = load_image("cMode/cyouwin.png", true);
	cyoulose = load_image("cMode/cyoulose.png", true);
	ctie = load_image("cMode/ctie.png", true);
	clogo = load_image("cMode/clogo.png", true);
	cobjection = load_image("cMode/cobjection.png", true);
	ccoffee = load_image("cMode/ccoffee.png", true);

	if(cwhitePiece == NULL || cblackPiece == NULL || cvalidDot == NULL || cyouwin == NULL || cyoulose == NULL || clogo == NULL || ctie == NULL || cobjection == NULL || ccoffee == NULL)
		return false;

	//Load the music
	cbgMusic = Mix_LoadMUS( "cMode/cbgMusic.ogg" );
	Mix_VolumeMusic(40);

	cplace = Mix_LoadWAV( "cMode/cplace.wav" );
	Mix_VolumeChunk(place, 255);

	//If there was a problem loading the music
	if( cbgMusic == NULL )
		return false; 
	if(cplace == NULL)
		return false;

	return true;
}

void Game::clean_up()
{
	SDL_FreeSurface(board);
	SDL_FreeSurface(whitePiece);
	SDL_FreeSurface(blackPiece);
	SDL_FreeSurface(validDot);
	SDL_FreeSurface(youwin);
	SDL_FreeSurface(youlose);
	SDL_FreeSurface(tie);
	SDL_FreeSurface(logo);
	SDL_FreeSurface(black);
	SDL_FreeSurface(objection);

	SDL_FreeSurface(cblackPiece);
	SDL_FreeSurface(cwhitePiece);
	SDL_FreeSurface(cvalidDot);
	SDL_FreeSurface(cyouwin);
	SDL_FreeSurface(cyoulose);
	SDL_FreeSurface(ctie);
	SDL_FreeSurface(clogo);
	SDL_FreeSurface(cobjection);
	SDL_FreeSurface(ccoffee);
	Mix_FreeMusic(cbgMusic);
	Mix_FreeChunk(cplace);

	TTF_CloseFont(font);
	Mix_FreeMusic(bgMusic);
	Mix_FreeChunk(victory);
	Mix_FreeChunk(lose);
	Mix_FreeChunk(no);
	Mix_FreeChunk(place);
	Mix_FreeChunk(tieChunk);
	Mix_FreeChunk(obj);
	Mix_FreeChunk(cof);

	TTF_Quit();
	Mix_CloseAudio();
	SDL_Quit();
}

void Game::toggle_fullscreen()
{
    //If the screen is windowed
    if( windowed == true )
    {
        //Set the screen to fullscreen
        screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE | SDL_FULLSCREEN );
        
		apply_surface(0, 0, board, screen);

        //Set the window state flag
        windowed = false;
    }
    //If the screen is fullscreen
    else if( windowed == false )
    {
        //Window the screen
        screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);

		apply_surface(0, 0, board, screen);
       
        //Set the window state flag
        windowed = true;
    }
}

void Game::flipPieces(pair<int,int>& movePlaced, int color)
{
	for(int dir = 0; dir < 8; dir++)
	{
		int valid = isValid(color, dir, movePlaced);
		if(valid)
		{
			pair<int, int> tempMove = movePlaced;
			tempMove.first += adjMovs[dir].first;
			tempMove.second += adjMovs[dir].second;
			while(boardState[tempMove.first][tempMove.second] != color && 
				boardState[tempMove.first][tempMove.second] != BLANK &&
				boardState[tempMove.first][tempMove.second] != VALID &&
				tempMove.first < 8 && tempMove.second < 8 && tempMove.first > -1 && tempMove.second > -1)
			{
				boardState[tempMove.first][tempMove.second] = color;
				tempMove.first += adjMovs[dir].first;
				tempMove.second += adjMovs[dir].second;
			}
		}
	}
}

bool Game::isValid(int color, int dir, pair<int,int>& movePlaced)
{
	bool valid = true;
	pair<int, int> tempMove = movePlaced;
	tempMove.first += adjMovs[dir].first;
	tempMove.second += adjMovs[dir].second;

	while(boardState[tempMove.first][tempMove.second] != color && valid)
	{
		if (boardState[tempMove.first][tempMove.second] == BLANK || boardState[tempMove.first][tempMove.second] == VALID
			|| tempMove.first > 7 || tempMove.second > 7 || tempMove.first < 0 || tempMove.second < 0 || 
			tempMove == corner1 || tempMove == corner2 || tempMove == corner3 || tempMove == corner4)
		{
			valid = false;
		}
		if(valid)
		{
			tempMove.first += adjMovs[dir].first;
			tempMove.second += adjMovs[dir].second;
		}
	}
	if(tempMove.first > 7 || tempMove.second > 7 || tempMove.first < 0 || tempMove.second < 0)
		valid = false;

	return valid;
}

void Game::placeValidDot()
{
	for(int row = 0; row < 8; row++)
		for(int col = 0; col < 8; col++)
			if(boardState[row][col] == human.getColor())
			{
				pair<int, int> humanPiece;
				humanPiece.first = row;
				humanPiece.second = col;
				for(int dir = 0; dir < 8; dir++)
				{
					bool valid = true;
					pair<int, int> tempMove = humanPiece;
					tempMove.first += adjMovs[dir].first;
					tempMove.second += adjMovs[dir].second;

					while(boardState[tempMove.first][tempMove.second] != human.getColor() && valid)
					{
						if (boardState[tempMove.first][tempMove.second] == BLANK || boardState[tempMove.first][tempMove.second] == VALID)
							valid = false;
						if(valid)
						{
							tempMove.first += adjMovs[dir].first;
							tempMove.second += adjMovs[dir].second;
						}
					}
					if(!valid && !(tempMove.first > 7 || tempMove.second > 7 || tempMove.first < 0 || tempMove.second < 0)
						&& boardState[tempMove.first - adjMovs[dir].first][tempMove.second - adjMovs[dir].second] != human.getColor())
						boardState[tempMove.first][tempMove.second] = VALID;
				}
			}
}

void Game::determineScore(vector<int>& score, int color)
{
	for(int i = 0; i < 8; i++)
		for(int j = 0; j < 8; j++)
		{
			if(boardState[i][j] == color)
				score.push_back(1);
		}
}

void Game::determineWinner(vector<int>& player, vector<int>& opponent)
{
	if( Mix_PlayingMusic() )
	{
		Mix_PauseMusic();
	}
	if(player.size() > opponent.size() && !soundPlayed)
	{
		if( Mix_FadeInChannel( -1, victory, 0, 5 ) == -1 )
			{
				return;    
			}
	}

	else if(opponent.size() > player.size() && !soundPlayed)
	{
		soundPlayed = true;
		if( Mix_PlayChannel( -1, lose, 0) == -1 )
			{
				return;    
			}
		if( Mix_PlayChannel( -1, no, 0) == -1 )
			{
				return;    
			}
	}
		
	else if(opponent.size() == player.size() && !soundPlayed)
	{
		soundPlayed = true;
		if( Mix_PlayChannel( -1, tieChunk, 0) == -1 )
			{
				return;    
			}
	}
}

void Game::reset()
{
	playerScore.clear();
	opponentScore.clear();
	for(int i = 0; i < 8; i++)
		for(int j = 0; j < 8; j++)
			boardState[i][j] = BLANK;
	boardState[3][3] = WHITE;
	boardState[4][4] = WHITE;
	boardState[4][3] = BLACK;
	boardState[3][4] = BLACK;

	//If the music is paused
	if( Mix_PausedMusic() == 1 )
		Mix_ResumeMusic();

	Mix_HaltChannel(-1);

	playerChoice = false;
	playerTurn = true;
	soundPlayed = false;
	endGame = false;

}

void Game::applyText()
{
	SDL_Color textColor = { 255, 255, 255};
	stringstream humanScore;
	humanScore << "YOU: " << playerScore.size();
	stringstream compScore; 
	compScore << "COMP: " << opponentScore.size();

	apply_surface(640, 50, logo, screen);

	//Render the text
    messageP = TTF_RenderText_Solid( font, "P - Pass", textColor );
	messageR = TTF_RenderText_Solid( font, "R - Reset", textColor );
	messageM = TTF_RenderText_Solid( font, "M - Toggle Music", textColor );
	messageF = TTF_RenderText_Solid( font, "F - Toggle Fullscreen", textColor );
	messageE = TTF_RenderText_Solid( font, "ESC - Quit Game", textColor );
	score = TTF_RenderText_Solid( font, "SCORE", textColor );
	apply_surface(640,550,black,screen);
	pscore = TTF_RenderText_Solid( font, humanScore.str().c_str(), textColor );
	oscore = TTF_RenderText_Solid( font, compScore.str().c_str(), textColor );

	humanScore.clear();
	compScore.clear();

    //If there was an error in rendering the text
	if( messageP == NULL || messageR == NULL || messageM == NULL || messageF == NULL || messageE == NULL || score == NULL || pscore == NULL || oscore == NULL)
        return;    

	apply_surface( 760, 200, messageP, screen );
	apply_surface( 750, 250, messageR, screen );
	apply_surface( 730, 300, messageM, screen );
	apply_surface( 680, 350, messageF, screen );
	apply_surface( 720, 400, messageE, screen );
	apply_surface( 780, 490, score, screen );
	apply_surface( 700, 550, pscore, screen );
	apply_surface( 840, 550, oscore, screen );

	SDL_FreeSurface(messageP);
	SDL_FreeSurface(messageR);
	SDL_FreeSurface(messageF);
	SDL_FreeSurface(messageM);
	SDL_FreeSurface(messageE);
	SDL_FreeSurface(score);
	SDL_FreeSurface(pscore);
	SDL_FreeSurface(oscore);
}

void Game::chooseColor(bool& quit)
{
	while(!playerChoice && !quit)
	{
		SDL_Color textColor = { 255, 255, 255};
		if(Mix_PlayingMusic() == 0)
				if( Mix_PlayMusic( bgMusic, -1 ) == -1 )
					return;

		apply_surface(0,0,board,screen);
		for(int i = 0; i < 8; i++)
			for(int j = 0; j < 8; j++)
			{
				if(boardState[i][j] == WHITE)
				{
					apply_surface(j*80, i*80, whitePiece, screen);
				}
				if(boardState[i][j] == BLACK)
				{
					apply_surface(j*80, i*80, blackPiece, screen);
				}
				if(boardState[i][j] == VALID)
				{
					boardState[i][j] = BLANK;
				}
			}
		applyText();
		
		messageP = TTF_RenderText_Solid( font, "B - Play as BLACK (Goes First)", textColor );
		messageR = TTF_RenderText_Solid( font, "W - Play as WHITE (Goes Second)", textColor );
		apply_surface(100, 50, messageP, screen );
		apply_surface(100, 100, messageR, screen );
		SDL_FreeSurface(messageP);
		SDL_FreeSurface(messageR);
		if(SDL_PollEvent(&event))
		{
			
			if(event.type == SDL_KEYDOWN)
			{
				if(event.key.keysym.sym == SDLK_ESCAPE)
					quit = true;
				else if(event.key.keysym.sym == SDLK_b)
				{
					human.setColor(BLACK);
					computer.setColor(WHITE);
					playerTurn = true;
					playerChoice = true;
				}
				else if(event.key.keysym.sym == SDLK_w)
				{
					human.setColor(WHITE);
					computer.setColor(BLACK);
					playerTurn = false;
					playerChoice = true;
				}
				else if(event.key.keysym.sym == SDLK_f)
						toggle_fullscreen();
				else if(event.key.keysym.sym == SDLK_m)
					{
						//If the music is paused
						if( Mix_PausedMusic() == 1 )
						{
							//Resume the music
							Mix_ResumeMusic();
						}
						//If the music is playing
						else
						{
							//Pause the music
							Mix_PauseMusic();
						}
					}
			}
			else if(event.type == SDL_QUIT)
			{
				quit = true;
			}
		}

		if(SDL_Flip(screen) == -1)
			return;
	}
}

bool Game::loadTheCorgis(bool& cMode)
{
	Mix_HaltMusic();

	if(!cMode)
	{	
		swap(whitePiece, cwhitePiece);
		swap(blackPiece, cblackPiece);
		swap(validDot, cvalidDot);
		swap(youwin, cyouwin);
		swap(youlose, cyoulose);
		swap(tie, ctie);
		swap(logo, clogo);
		swap(bgMusic, cbgMusic);
		swap(place, cplace);
		swap(objection, cobjection);
		swap(coffee, ccoffee);
		cMode = !cMode;
		return true;
	}
	else
	{
		swap(whitePiece, cwhitePiece);
		swap(blackPiece, cblackPiece);
		swap(validDot, cvalidDot);
		swap(youwin, cyouwin);
		swap(youlose, cyoulose);
		swap(tie, ctie);
		swap(logo, clogo);
		swap(bgMusic, cbgMusic);
		swap(place, cplace);
		swap(objection, cobjection);
		swap(coffee, ccoffee);

		cMode = !cMode;
		return true;
	}
}

void Game::cornerTaken()
{
	int x = -640;
	while(x != 0)
	{
		displayGamestate();
		apply_surface(x, 0, objection, screen);
		x += 8;
		if(SDL_Flip(screen) == -1)
			return;
	}

	if( Mix_PlayChannel( -1, obj, 0) == -1 )
		return;

	SDL_Delay(1500);

	while(x != -640)
	{
		displayGamestate();
		apply_surface(x, 0, objection, screen);
		x -= 8;
		if(SDL_Flip(screen) == -1)
			return;
	}
}

void Game::opponentCornerTaken()
{
	int y = 640;
	while(y >= 0)
	{
		displayGamestate();
		apply_surface(0, y, coffee, screen);
		y -= 8;
		if(SDL_Flip(screen) == -1)
			return;
	}

	if( Mix_PlayChannel( -1, cof, 0) == -1 )
		return;

	SDL_Delay(4500);

	while(y != 640)
	{
		displayGamestate();
		apply_surface(0, y, coffee, screen);
		y += 8;
		if(SDL_Flip(screen) == -1)
			return;
	}
}

void Game::displayGamestate()
{
	apply_surface(0,0,board,screen);
		playerScore.clear();
		opponentScore.clear();
		for(int i = 0; i < 8; i++)
			for(int j = 0; j < 8; j++)
			{
				if(boardState[i][j] == WHITE)
				{
					apply_surface(j*80, i*80, whitePiece, screen);
				}
				if(boardState[i][j] == BLACK)
				{
					apply_surface(j*80, i*80, blackPiece, screen);
				}
				if(boardState[i][j] == VALID)
				{
					boardState[i][j] = BLANK;
				}
			}
		
		determineScore(opponentScore, computer.getColor());
		determineScore(playerScore, human.getColor());
		applyText();
}

void Game::play()
{
	bool quit = false;

	if(init() == false)
		return;
	if(load_files() == false)
		return;

	int blankCount = 0;

	while(quit == false)
	{
		chooseColor(quit);

		if(Mix_PlayingMusic() == 0)
			if( Mix_PlayMusic( bgMusic, -1 ) == -1 )
				return;

		blankCount = 0;
		
		displayGamestate();

		for(int i = 0; i < 8; i++)
			for(int j = 0; j < 8; j++)
			{
				if(boardState[i][j] == BLANK)
				{
					blankCount++;
				}
			}
		if(blankCount == 0)
			endGame = true;

		if(!playerTurn && !endGame)
		{
			pair<int,int> move;
			computer.move(boardState, move);

			if((move == corner1 || move == corner2 || move == corner3 || move == corner4)
				&& (boardState[move.first][move.second] != human.getColor()))
					opponentCornerTaken();

			boardState[move.first][move.second] = computer.getColor();
			playerTurn = !playerTurn;
			flipPieces(move,computer.getColor());
		}

		if(endGame || playerScore.empty() || opponentScore.empty())
		{
			if(opponentScore.size() > playerScore.size())
				apply_surface(0, 0, youlose, screen);
			if(opponentScore.size() < playerScore.size())
				apply_surface(0, 0, youwin, screen);
			if(opponentScore.size() == playerScore.size())
				apply_surface(0, 0, tie, screen);
			endGame = true;
			determineWinner(playerScore, opponentScore);
			if(SDL_PollEvent(&event))
			{
				if(event.type == SDL_KEYDOWN)
				{
					if(event.key.keysym.sym == SDLK_ESCAPE)
						quit = true;
					else if(event.key.keysym.sym == SDLK_r)
						reset();
					else if(event.key.keysym.sym == SDLK_f)
						toggle_fullscreen();
				}
				else if(event.type == SDL_QUIT)
				{
					quit = true;
				}
			}
		}

		placeValidDot();

		for(int i = 0; i < 8; i++)
			for(int j = 0; j < 8; j++)
			{
				if(boardState[i][j] == VALID)
				{
					apply_surface(j*80, i*80, validDot, screen);
				}
			}

		if(playerTurn && !endGame)
		{
			if(SDL_PollEvent(&event))
			{
				if(event.type == SDL_MOUSEBUTTONDOWN)
				{
					if(event.button.button == SDL_BUTTON_LEFT)
					{
						int x, y;
						SDL_GetMouseState(&x, &y);

						if(boardState[y/80][x/80] == BLANK)
							playerTurn = playerTurn;
						else if(x < 640 && y < 640 && boardState[y/80][x/80] == VALID)
						{
							pair<int, int> move;
							move.first = y/80;
							move.second = x/80;

							if( Mix_PlayChannel( -1, place, 0) == -1 )
								return;

							if(move == corner1 || move == corner2 || move == corner3 || move == corner4)
								cornerTaken();

							boardState[y/80][x/80] = human.getColor();
							flipPieces(move,human.getColor());
							playerTurn = !playerTurn;
						}
						
					}
				}
			
				else if(event.type == SDL_KEYDOWN)
				{
					if(event.key.keysym.sym == SDLK_ESCAPE)
						quit = true;
					else if(event.key.keysym.sym == SDLK_f)
						toggle_fullscreen();
					else if(event.key.keysym.sym == SDLK_p)
						playerTurn = !playerTurn;
					else if(event.key.keysym.sym == SDLK_r)
						reset();
					else if(event.key.keysym.sym == SDLK_c)
						loadTheCorgis(cMode);
					else if(event.key.keysym.sym == SDLK_m)
					{
						//If the music is paused
						if( Mix_PausedMusic() == 1 )
						{
							//Resume the music
							Mix_ResumeMusic();
						}
						//If the music is playing
						else
						{
							//Pause the music
							Mix_PauseMusic();
						}
					}

					else if(event.key.keysym.sym == SDLK_w)
						for(int i = 0; i < 8; i++)
							for(int j = 0; j < 8; j++)
									boardState[i][j] = human.getColor();

					else if(event.key.keysym.sym == SDLK_t)
						for(int i = 0; i < 8; i++)
								for(int j = 0; j < 8; j++)
								{
									if(j < 4)
										boardState[i][j] = human.getColor();
									else
										boardState[i][j] = computer.getColor();
								}

				}

				else if(event.type == SDL_QUIT)
				{
					quit = true;
				}
			}
		}
		
		if(SDL_Flip(screen) == -1)
			return;
	}

	clean_up();
}
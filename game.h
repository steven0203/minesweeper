#ifndef GAME_H
#define GAME_H
#include"ncurses.h"
#include"sect_play.h"
#include"menu.h"
#include<string>
#define MENU 1
#define SETTING 2
#define PLAY 3
#define EXIT 5
using namespace std;

class game
{
	public :
	game();
	game(int [3],int [3],int [3],string [],string [4],string,string ,int);
	~game();
	void setgame(int [3],int [3],int [3],string [],string [4],string ,string,int);
	int section(int);
	private :
	sect_play play;
	menu mainmenu;
	menu levelselect;
	int gamehieght,gamewidth,bombnum;
	int hieghts[3];
	int widths[3];
	int bombs[3];
	void set_by_player();
};

#endif

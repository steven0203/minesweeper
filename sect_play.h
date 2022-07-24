#ifndef SECT_PLAY_H
#define SECT_PLAY_H
#include"ncurses.h"
#include"mine.h"
#include"gametime.h"
class sect_play
{
	public:
	sect_play(int =9,int =9,int =10);
	void playSet(int ,int ,int ); 
	void execute();
	int getresult();
	private:
	mine game_mine;
	gametime t;
	char scr_mine[30][30];
	int play_hi,play_wi,result,bomb_num,flag_num;//result :0 play again 1 back to menu 2 reset the level 3  exit
	WINDOW *finish_win;
	int wincheck();	
	void print_help();
	void print_scrmine();
	void open_mine(int,int);
	void GetAllBomb();
    void gameover(int);
	void creatborder(int,int,int,int);
	void printtime();
};
#endif	

#include"game.h"
#include"sect_play.h"
#include"menu.h"
#include<string>

using namespace std;

game::game():gamehieght(9),gamewidth(9),bombnum(10)
{
	int hi[3]={9,16,16};
	int wi[3]={9,16,30};
	int bomb_num[3]={10,40,99};
	string gamename="MINESWEEPER";
	string menuchoise[2]={"start","exit"};
	string levels[4]={"9*9 bomb:10","16*16 bomb:40","16*30 bomb:99","setting" };
	string leveltopic="select";
	initscr();
	cbreak();
    noecho();
	nodelay(stdscr,TRUE);
	keypad(stdscr,TRUE);
	start_color();
	init_pair(1,COLOR_RED,COLOR_GREEN);
	init_pair(2,COLOR_YELLOW,COLOR_BLUE);
	init_pair(3,COLOR_BLACK,COLOR_WHITE);
    init_pair(4,COLOR_CYAN,COLOR_MAGENTA);
	init_pair(5,COLOR_RED,COLOR_BLACK);
	setgame(hi,wi,bomb_num, menuchoise,levels,gamename,leveltopic,2);
}
game::game(int hi[3],int wi[3],int bomb_num[3],string menuchoise[],string levels[4],string gamename,string leveltopic,int menu_chnum)
 :gamehieght(9),gamewidth(9),bombnum(10)           
{
	initscr();
	cbreak();
	noecho();
	nodelay(stdscr,TRUE);
	keypad(stdscr,TRUE);
	start_color();
	init_pair(1,COLOR_RED,COLOR_GREEN);
	init_pair(2,COLOR_YELLOW,COLOR_BLUE);
	init_pair(3,COLOR_BLACK,COLOR_WHITE);
	init_pair(4,COLOR_CYAN,COLOR_MAGENTA);
    init_pair(5,COLOR_RED,COLOR_BLACK);
	setgame(hi,wi,bomb_num, menuchoise,levels,gamename,leveltopic,menu_chnum);
}
game::~game()
{
	erase();
	refresh();
	endwin();
}


void game::setgame(int hi[3],int wi[3],int bomb_num[3],string menuchoise[],string levels[4],string gamename,string leveltopic,int menu_chnum)
{
	for(int i=0;i<3;i++)
	{
		hieghts[i]=hi[i];
		widths[i]=wi[i];
		bombs[i]=bomb_num[i];
	}
	mainmenu.set_menu(gamename,menuchoise,menu_chnum);
	levelselect.set_menu(leveltopic,levels,4);
}

int game::section(int select)
{
	switch(select)
	{
		case MENU:
		{
			attron(COLOR_PAIR(1));
			mvprintw(mainmenu.get_chnum()*5+3,3,"Press UP,DOWN buttom to move .Press ENTER to select.");
			attroff(COLOR_PAIR(1));
			refresh();
			mainmenu.execute();
			return mainmenu.get_choise();
		}	
		case SETTING:
		{
			int choose;
			levelselect.execute();
			choose=levelselect.get_choise();
			if(choose==3){set_by_player();}
			else
			{
				gamehieght=hieghts[choose];
				gamewidth=widths[choose];
				bombnum=bombs[choose];
			}
			return 0;
		}
		case PLAY:
		{
			play.playSet(gamehieght,gamewidth,bombnum);  
			play.execute();
			return play.getresult();//0: playagain 1:back to menu 2:reset level  3 :exit
		}
		case EXIT:
		{
			erase();
			refresh();
		}
	}
}
void game::set_by_player()                                                                                            
{
	int enter=1;
	int tmpdata;
	int maxbomb;
	char tmp[100];
	char wrongmessage[30]="You enter the wrong number .";
	echo();
	nodelay(stdscr,FALSE);
	mvprintw(4,3,"Please enter the height (max is 30,min is 9): ");
	refresh();
	while(enter==1)
	{
		mvgetstr(5,3,tmp);
		tmpdata=atoi(tmp);
		if(tmpdata>=9&&tmpdata<=30){enter=0;gamehieght=tmpdata;move(12,3);clrtoeol();refresh();}
		else
		{
			move(5,3);clrtoeol();
			attron(COLOR_PAIR(1));
			mvprintw(12,3,"%s",wrongmessage);
			attroff(COLOR_PAIR(1));
		}
		refresh();
	}
	enter=1;
	mvprintw(6,3,"Please enter the width (max is 30,min is 9): ");
	refresh();
	while(enter==1)
	{
		mvgetstr(7,3,tmp);
		tmpdata=atoi(tmp);
		if(tmpdata>=9&&tmpdata<=30){enter=0;gamewidth=tmpdata;move(12,3);clrtoeol();refresh();}
		else
		{
			move(7,3);clrtoeol();
			attron(COLOR_PAIR(1));
			mvprintw(12,3,"%s",wrongmessage);
			attroff(COLOR_PAIR(1));
		}
		refresh();
	}
	enter=1;
	maxbomb=gamehieght*gamewidth-(10+((gamehieght*gamewidth)/10));
	mvprintw(8,3,"Please enter the bomb number (max is %d,min is 10): ",maxbomb);
	refresh();
	while(enter==1)
	{                                                                                                                                                   
		mvgetstr(9,3,tmp);
		tmpdata=atoi(tmp);
		if(tmpdata>=10&&tmpdata<=maxbomb){enter=0;bombnum=tmpdata;move(12,3);clrtoeol();refresh();}
		else
		{
			move(9,3);clrtoeol();
			attron(COLOR_PAIR(1));
			mvprintw(12,3,"%s",wrongmessage);
			attroff(COLOR_PAIR(1));
		}
		refresh();
	}
	erase();
	refresh();
	noecho();
	nodelay(stdscr,TRUE);
}



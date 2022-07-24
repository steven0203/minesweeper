#include"ncurses.h"
#include"sect_play.h"
#include"mine.h"
#include"gametime.h"
#include<string>
using namespace std;

sect_play::sect_play(int minehi,int minewi,int bombnum)
{
	playSet(minehi,minewi,bombnum);
}

void sect_play::playSet(int minehi,int minewi,int bombnum)
{
	game_mine.setMine(minehi,minewi,bombnum);
	play_hi=minehi;
	play_wi=minewi;
	bomb_num=bombnum;
	flag_num=0;
	result=0;
	for(int i=0;i<play_hi;i++)
	{
		for(int j=0;j<play_wi;j++)
		{
			scr_mine[i][j]=' ';
		}              
	}
}


void sect_play::execute()
{
	creatborder(play_hi+2,play_wi+2,0,0);
	creatborder(14,60,0,play_wi+3);
	t.setTime();
	int go_on=TRUE,play_y,play_x,lose=0,exit=0,win=0,open=0,order,y=0,x=0,i=0,pause=0;
	play_x=x+1;play_y=y+1;	
	print_scrmine();
	print_help();
	while(go_on)
	{	
		open=0;
		t.time_pass();
		mvprintw(12,play_wi+5,"flag num : %3d",flag_num);
		printtime();
		move(play_y,play_x);
		refresh();
		while((order = getch()) == ERR)
		{
			t.time_pass();
			printtime();
			move(play_y,play_x);
			refresh();
		}
		switch(order)
		{
			case KEY_RIGHT:{play_x++;play_x=(play_x>play_wi)?play_x-play_wi:play_x;x=play_x-1;break;}
			case KEY_LEFT:{play_x--;play_x=(play_x<1)?play_x+play_wi:play_x;x=play_x-1;break;}
			case KEY_UP:{play_y--;play_y=(play_y<1)?play_y+play_hi:play_y;y=play_y-1;break;}
			case KEY_DOWN:{play_y++;play_y=(play_y>play_hi)?play_y-play_hi:play_y;y=play_y-1;break;}
			case 'f':
			{
				if((scr_mine[y][x]!='f')&&(scr_mine[y][x]!=' '))break;
				if(scr_mine[y][x]=='f'){scr_mine[y][x]=' ';flag_num--;}
				else {scr_mine[y][x]='f';flag_num++;}
				break;
			}		
			case 'x':{exit=1;break;}
			case 'c':{open=1;if(scr_mine[y][x]!=' '){open=0;}break;}
			case 'p':{pause=1;}
			default:break;
		}
		while(pause==1)
		{
			erase();
			attron(COLOR_PAIR(1));
			mvprintw(6,10,"PAUSE");
			mvprintw(7,10,"Press p again to continue the game .");
			attroff(COLOR_PAIR(1));
			refresh();
		    order=getch();
			if(order=='p')
			{
				erase();
				creatborder(play_hi+2,play_wi+2,0,0);
				creatborder(14,60,0,play_wi+3);
				print_help();
				refresh();
				t.time_continue(); 
				pause=0;
			}
            else{continue;}
		}
																																 
		while(exit==1)
		{
			erase();
			attron(COLOR_PAIR(1));
			mvprintw(6,10,"Do you want to exit?(y/n)");  
			attroff(COLOR_PAIR(1));
			refresh();
			order=getch();
			if(order=='y'){go_on=0;exit=0;result=3;}
			else if(order=='n')
			{
				erase();
			    creatborder(play_hi+2,play_wi+2,0,0);
				creatborder(14,60,0,play_wi+3);
				print_help();
				refresh();exit=0;t.time_continue();
			}
			else{continue;}
		}
		if(open==1)
		{	
			open_mine(y,x);
			if(scr_mine[y][x]=='b'){GetAllBomb();go_on=FALSE;lose=1;
			}                
		}
		if(lose!=1)	win=wincheck();
		if(win==1)go_on=0;
		print_scrmine();
		refresh();
	}
	if(win==1)gameover(0);
	if(lose==1)gameover(1);
	game_mine.saveMine();
	erase();
	refresh();
}

int sect_play::wincheck()
{
	int fault=0;
	int correct=0;
	int tmp;
	int flag=0;
	int i,j;
	char bomb='b';
	for(i=0;i<play_hi&&fault==0;i++)
	{
		for(j=0;j<play_wi&&fault==0;j++)
		{
			if((bomb==game_mine.openGrid(i,j))&&(scr_mine[i][j]==' ')){continue;}
			if(flag>bomb_num){fault++;break;}
			if(scr_mine[i][j]=='f'){flag++;continue;}
			if(scr_mine[i][j]!=game_mine.openGrid(i,j)){fault++;break;}
		}
	}
	if(i==play_hi&&j==play_wi)correct++;
	return correct;
}

void sect_play::print_help()
{
	mvprintw(4,play_wi+5,"Press left,up,right,and down bottom to move.");
	mvprintw(6,play_wi+5,"Press f to set a flag. Press c to open a grip.");
	mvprintw(8,play_wi+5,"Press p to pause .Press x to exit.");
	mvprintw(10,play_wi+5,"bomb num : %3d",bomb_num);
}

void sect_play::print_scrmine()
{
	int color;
	for(int i=1;i<=play_hi;i++)
	{
		for(int j=1;j<=play_wi;j++)
		{
			if(scr_mine[i-1][j-1]==' '){color=3;}
			if(scr_mine[i-1][j-1]=='b'){color=1;}
			if(scr_mine[i-1][j-1]=='f'){color=4;}
			if(scr_mine[i-1][j-1]<'9'&&scr_mine[i-1][j-1]>='0'){color=2;}
			attron(COLOR_PAIR(color));
			if(scr_mine[i-1][j-1]=='0')mvaddch(i,j,' ');
			else{mvaddch(i,j,scr_mine[i-1][j-1]);}
			if(scr_mine[i-1][j-1]==' ')mvaddch(i,j,'.');
			attroff(COLOR_PAIR(color));
		}
	}
}
 
void sect_play::open_mine(int y ,int x)
{
	if((scr_mine[y][x]!=' ')||(y==play_hi)||(y<0)||(x==play_wi)||(x<0))
	{
		return ;
	}
	scr_mine[y][x]=game_mine.openGrid(y,x);
	if(scr_mine[y][x]=='0')
	{
		open_mine(y-1,x);
		open_mine(y+1,x);
		open_mine(y,x+1);
		open_mine(y,x-1);
		open_mine(y+1,x+1);
		open_mine(y-1,x-1);
		open_mine(y+1,x-1);
		open_mine(y-1,x+1);
	}
}

void sect_play::GetAllBomb()
{
	for(int i=0;i<play_hi;i++)
	{
		for(int j=0;j<play_wi;j++)
		{
			if(game_mine.openGrid(i,j)=='b')
			scr_mine[i][j]='b';
		}
	}
}

void sect_play::gameover(int r)
{
	finish_win=newwin(12,40,play_hi+6,4);
	wborder(finish_win,'|','|','-','-','+','+','+','+');
	keypad(finish_win,TRUE);
	int order=0,ch=0,go_on=1;
	string gameresult[2]={"You win !","You lose!"};
	string choise[3]={"Play again!","Back to menu!","Reset the level!"};
	wattron(finish_win,COLOR_PAIR(5));
	mvwprintw(finish_win,2,5,"%s",gameresult[r].c_str());  
	wattroff(finish_win,COLOR_PAIR(5));
	while(go_on)
	{    
		mvwprintw(finish_win,8,6,"%s",choise[2].c_str());
		mvwprintw(finish_win,6,6,"%s",choise[1].c_str());
		mvwprintw(finish_win,4,6,"%s",choise[0].c_str());
		wattron(finish_win,A_REVERSE);
		mvwprintw(finish_win,ch*2+4,6,"%s",choise[ch].c_str());
		wattroff(finish_win,A_REVERSE);
		wrefresh(finish_win);
		order=wgetch(finish_win);
		switch(order)
		{
		case KEY_UP:{ch--;ch=(ch<0)?ch+=3:ch;break;}
		case KEY_DOWN:{ch++;ch=(ch>2)?ch-=3:ch;break;}
		case '\n':{go_on=0;result=ch;break;} 
		default :break;
		}                                                                                                              		
	}
	delwin(finish_win);
}


void sect_play::printtime()
{
	int hour,second,minute;
	hour=t.gethr();
	minute=t.getmi();
	second=t.getsc();
	attron(COLOR_PAIR(5));
	mvprintw(2,play_wi+5,"Game time : %2d:%2d:%2d",hour,minute,second);
	attroff(COLOR_PAIR(5));
}

void sect_play::creatborder(int hieght,int width,int starty,int startx)
{
	mvaddch(starty,startx,'+');
	mvaddch(starty,startx+width-1,'+');
	mvaddch(starty+hieght-1,startx,'+');
	mvaddch(starty+hieght-1,startx+width-1,'+');
	mvhline(starty,startx+1,'-',width-2);
	mvhline(starty+hieght-1,startx+1,'-',width-2);
	mvvline(starty+1,startx,'|',hieght-2);
	mvvline(starty+1,startx+width-1,'|',hieght-2);
}

int sect_play::getresult()
{
	return result;
}



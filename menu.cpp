#include"menu.h"
#include<string>
#include"ncurses.h"

using namespace std;

menu::menu():topic("You haven't set this menu ."),choise_num(2),choise(0)
{
	choises[0]="Please set this menu .";
}
menu::menu(string name,string ch[],int ch_num)
{
	set_menu(name,ch,ch_num);
}

void menu::set_menu(string name,string ch[],int ch_num)
{
	topic=name;
	choise_num=ch_num;
	choise=0;
	for(int i=0;i<ch_num;i++)
	{
		choises[i]=ch[i];
	}
}

void menu::execute()
{
	win=newwin(choise_num*5,50,0,0);
	keypad(win,TRUE);
	wborder(win,'|','|','-','-','+','+','+','+');
	wattron(win,COLOR_PAIR(5));
	mvwprintw(win,2,3,"%s",topic.c_str());
	wattroff(win,COLOR_PAIR(5));
	int ch=0,go_on=TRUE,point;
	for(int i=0;i<choise_num;i++)
	{
		mvwprintw(win,4+i*2,4,"%s",choises[i].c_str());
	}
	wrefresh(win);
	while(go_on)
	{
		for(int i=0;i<choise_num;i++)
		{
			if(i==ch)continue;
			 mvwprintw(win,4+i*2,4,"%s",choises[i].c_str());
		}
		wattron(win,A_REVERSE);
		mvwprintw(win,4+ch*2,4,"%s",choises[ch].c_str());
		wattroff(win,A_REVERSE);
		wrefresh(win);
		point=wgetch(win);
		switch (point)
		{
			case KEY_UP:
			{
				ch--;
				if(ch<0)ch+=choise_num;
				break;
			}
			case KEY_DOWN:
			{
				ch++;
				if(ch==choise_num)ch=0;
				break;
			}
			case '\n':
			{	
				go_on=FALSE;
				choise=ch;
				break;
			}
			default:break;
		}
	}
	delwin(win);
	erase();
	refresh();
}

int menu::get_choise()
{
	return choise;
}

int menu::get_chnum()
{
	return choise_num;
}


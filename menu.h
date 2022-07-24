#ifndef MENU_H
#define MENU_H
#include"ncurses.h"
#include<string>


using namespace std;
class menu
{
	public:
	menu();
	menu(string,string [],int);
	void set_menu(string ,string [],int);
	void execute();
	int get_chnum();
	int get_choise();
	private:
	string topic;
	string choises[6];
	int choise_num;
	int choise;
    WINDOW *win;
};

#endif

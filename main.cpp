#include<string>
#include"game.h"
using namespace std;


int main()
{
	int play=1,choose,result,go_menu=1,set=1;
	int hieghts[3]={9,16,16};
	int widths[3]={9,16,30};
	int bombs[3]={10,40,99};
	string gamename="MINESWEEPER";
	string menuchoise[2]={"Start","Exit"};
	string selecttopic="Please select the level.";
	string levels[4]={"1. 9*9 mine with 10 bombs ",
					  "2. 16*16 mine with 40 bombs ",
					  "3. 16*30 mine with 99 bombs ",
					  "4. set by player ",
					 };
	game minesweeper(hieghts,widths,bombs,menuchoise,levels,gamename,selecttopic,2);
	while(play)
	{	
		result=0;
		if(go_menu==1)
		{
			choose=minesweeper.section(MENU);
			if(choose==1){play=0;set=0;minesweeper.section(EXIT);break;}
		}
		if(set==1)
		{
			minesweeper.section(SETTING);
		}
		while((result=minesweeper.section(PLAY))==0);
		switch(result)
		{
			case 1:
			{go_menu=1;break;}
			case 2:
			{go_menu=0;set=1;break;}
			case 3:
			{play=0;go_menu=0;set=0;minesweeper.section(EXIT);break;}
		}
	}
	return 0;
}

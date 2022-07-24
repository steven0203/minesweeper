#ifndef MINE_H
#define MINE_H
#include<ctime>
#include<cstdlib>
#include<fstream>
class mine
{
	public:
	mine(int =9, int =9,int =10);
	void setMine(int,int,int);
	char openGrid(int,int);
	void saveMine();
	private:
	char grid[30][30];
	int mine_hi;
	int mine_wi;
	void setBomb(int);
	void setNum(int,int);
};

#endif

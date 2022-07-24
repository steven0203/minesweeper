#include<ctime>
#include<cstdlib>
#include"mine.h"
using namespace std;

mine::mine(int hieght,int width,int bomb_num)
{
	setMine(hieght,width,bomb_num); 
}


void mine::setMine(int hieght,int width,int bomb_num)
{
	int i,j;
	mine_hi=hieght;mine_wi=width;
	for(i=0;i<hieght;i++)
	{
		for(j=0;j<width;j++)
		{
			grid[i][j]='0';
		}
	}
	setBomb(bomb_num);
	for(i=0;i<hieght;i++)
	{
		for(j=0;j<width;j++)
		{
			if(grid[i][j]=='b')continue;
			setNum(i,j);

		}
	}
}

char mine::openGrid(int row,int col)
{
	return grid[row][col];
}

void mine::setBomb(int bomb_num)
{
	int row,col;
	srand(time(NULL));
	while(bomb_num!=0)
	{

		row=rand()%mine_hi;
		col=rand()%mine_wi;
		if(grid[row][col]!='b')
		{
			grid[row][col]='b';
			bomb_num--;
		}
	}
}
void mine::setNum(int row,int col)
{
	int hi_start,hi_end,wi_start,wi_end;
	hi_start=(row==0?row:row-1);
	hi_end=(row==mine_hi-1?row:row+1);
	wi_start=(col==0?col:col-1);
	wi_end=(col==mine_wi-1?col:col+1);
	for(int i=hi_start;i<=hi_end;i++)
	{
		for(int j=wi_start;j<=wi_end;j++)
		{
			if(grid[i][j]=='b')
				grid[row][col]++;
		}
	}
}
void mine::saveMine()
{
	ofstream fout("Mine.txt",ios::out);
	for(int i=0;i<mine_hi;i++)
	{
		for(int j=0;j<mine_wi;j++)
		{
			fout<<grid[i][j];
		}
		fout<<"\n";
	}
	fout.close();
}

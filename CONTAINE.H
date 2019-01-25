#ifndef CONTAINE_H
#define CONTAINE_H

#include <conio.h>
#include <math.h>
#define NULL 0x0

class ele
{
	protected:
		char type;
		int x,y,col;
	public:
		void def();
		ele();
		ele(int ntype, int ncol);
		void show(int code);
		void hide();
		int move(int nx, int ny, int code);
		void setType(int ntype);
		void setCol(int ncol);
		int getCol();
		int getType();
		int getX();
		int getY();
};

class point:public ele
{
	public:
		point();
		point(int nx, int ny, int ntype, int ncol);
		void setX(int nx);
		void setY(int ny);
};


class stkPt
{
	int front,back;
	public:
		point ary[1093];
		ele artist;
		stkPt();
		void push(point newPt);
		int pop();
		void clearStk();
		int getFront();
		int getBack();
		~stkPt();
		int draw(int nx, int ny);
		void prnStk();
};

void ele::def()
{
	x=41;
	y=11;
	type = 219;
	col = 15;
	show(0);
}

void ele::hide()
{
	gotoxy(x,y);
	cprintf(" ");
}

ele::ele()
{
	x=41;
	y=11;
	type = 219;
	col = 15;
}

ele::ele(int ntype, int ncol)
{
	x=41;y=11;
	type = ntype;
	col = ncol;
	show(0);
}

void ele::show(int code)
{
	gotoxy(x,y);
	textcolor(col);
	if(code)
		cprintf("%c",type);
	else
		cprintf("%c",(char)254);
}

void ele::setType(int ntype)
{
	type = ntype;
}

void ele::setCol(int ncol)
{
	col = ncol;
}

int ele::move(int nx, int ny, int code)
{
	if(x+nx>1&&x+nx<80)
	{
		if(y+ny>3&&y+ny<18)
		{
			if (!code)
				hide();
			x+=nx;
			y+=ny;
			show(0);
			return 1;
		}
		else
			return 0;
	}
	else
		return 0;
}

int ele::getCol()
{
	return col;
}

int ele::getType()
{
	return type;
}

int ele::getX()
{
	return x;
}

int ele::getY()
{
	return y;
}
stkPt::stkPt()
{
	front = back = -1;
}

void stkPt::push(point newPt)
{
	if (front==-1)
	{
		front = back = 0;
		ary[front] = newPt;
	}
	else
	{
		int tmp = front;
		int flag=0;
		while(tmp<=back)
		{
			if((ary[tmp].getX()==newPt.getX())&&(ary[tmp].getY()==newPt.getY()))
			{	ary[tmp] = newPt;
				flag=1;
				break;
			}
			tmp++;
		}
		if(!flag)
		{	ary[++back] = newPt;
		}
	}
}

int stkPt::pop()
{
	if (front==back==0)
		front = back = -1;
	else
	{
		if(back>0)
			back--;
		else
			return 0;
	}
	return 1;
}

void stkPt::clearStk()
{
	while(pop());
}

int stkPt::getFront()
{
	return front;
}

int stkPt::getBack()
{
	return back;
}

stkPt::~stkPt()
{
	clearStk();
}

int stkPt::draw(int nx, int ny)
{
	int X= artist.getX();
	int Y= artist.getY();
	int TYPE= artist.getType();
	int COL= artist.getCol();
	if(X+nx>1&&X+nx<80)
	{
		if(Y+ny>3&&Y+ny<18)
		{
			if(nx==0)
			{
				if (ny>0)
				{
					for (int i=Y;i<Y+ny;++i)
					{
						point tmp(X,i,TYPE,COL);
						push(tmp);
						ary[back].show(1);
					}
				}
				else
				{
					for (int i=Y;i>Y+ny;--i)
					{
						point tmp(X,i,TYPE,COL);
						push(tmp);
						ary[back].show(1);
					}
				}
				artist.move(nx,ny,1);
				return 1;
			}
			else if(ny==0)
			{
				if (nx>0)
				{
					for (int i=X;i<X+nx;++i)
					{
						point tmp(i,Y,TYPE,COL);
						push(tmp);
						ary[back].show(1);
					}
				}
				else
				{
					for (int i=X;i>X+nx;--i)
					{
						point tmp(i,Y,TYPE,COL);
						push(tmp);
						ary[back].show(1);
					}
				}
				artist.move(nx,ny,1);
				return 1;
			}
			else if(abs(ny)==abs(nx))
			{
				if (nx<0&&ny<0)
				{	for (int i=X,j=Y;i>X+nx;--i,--j)
					{
						point tmp(i,j,TYPE,COL);
						push(tmp);
						ary[back].show(1);
					}
				}
				else if(nx<0&&ny>0)
				{
					for (int i=X,j=Y;i>X+nx;--i,++j)
					{
						point tmp(i,j,TYPE,COL);
						push(tmp);
						ary[back].show(1);
					}
				}
				else if(nx>0&&ny<0)
				{
					for (int i=X,j=Y;i<X+nx;++i,--j)
					{
						point tmp(i,j,TYPE,COL);
						push(tmp);
						ary[back].show(1);
					}
				}
				else
				{
					for (int i=X,j=Y;i<X+nx;++i,++j)
					{
						point tmp(i,j,TYPE,COL);
						push(tmp);
						ary[back].show(1);
					}
				}
				artist.move(nx,ny,1);
				return 1;
			}
			return 0;
		}
		else
			return 0;
	}
	else
		return 0;
}

void stkPt::prnStk()
{
    int tmp = front;
	while(tmp>-1&&tmp<=back)
    {
		ary[tmp++].show(1);
    }
}

point::point()
{
	x=41;
	y=11;
	type = 219;
	col = 15;
};


point::point(int nx, int ny, int ntype, int ncol)
{
	x=nx;
	y=ny;
	type=ntype;
	col=ncol;
}

void point::setX(int nx)
{
	x=nx;
}

void point::setY(int ny)
{
	y=ny;
}

#endif
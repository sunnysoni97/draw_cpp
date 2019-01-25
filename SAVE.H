#ifndef SAVE_H
#define SAVE_H

#include "CONTAINE.H"
#include "DRAW.H"
#include <fstream.h>

class save
{
	public:
		void saveFile(stkPt& stk,draw& canvas,char fileName[32]);
		int openFile(stkPt& stk,draw& canvas,char fileName[32]);
};

void save::saveFile(stkPt& stk,draw& canvas,char fileName[32])
{
	ofstream of(fileName);
	of<<canvas.getCanCol() <<endl;
	int p1;
    p1 = stk.getFront();
    while(p1>-1&&p1<=stk.getBack())
    {
        of<<stk.ary[p1].getX() <<endl;
		of<<stk.ary[p1].getY() <<endl;
		of<<stk.ary[p1].getType() <<endl;
		of<<stk.ary[p1].getCol() <<endl;
        p1++;
    }
    of.close();
}

int save::openFile(stkPt& stk,draw &canvas,char fileName[32])
{
	ifstream in(fileName,ios::nocreate);
	if(in.good())
    {
		stk.clearStk();
		int i[4];
		in>>i[0];
		canvas.setCanCol(i[0]);
		while(!in.eof())
		{
			in>>i[0];
			in>>i[1];
			in>>i[2];
			in>>i[3];
			point p1(i[0],i[1],i[2],i[3]);
			stk.push(p1);
			if(in.eof())
				break;
		}
		in.close();
        return 1;
    }
    else
		in.close();
        return 0;
}

#endif
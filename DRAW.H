#ifndef DRAW_H
#define DRAW_H

#include <string.h>
#include <conio.h>
#include <iomanip.h>
#include <dos.h>

class draw
{
	char fileName[32];
	int canCol;
	public:
		draw();
		void drawBar();
		void drawFname();
		void drawCan();
		void drawConsole(int fast);
		void drawMain();
		void drawHelp();
		void drawWelcome();
		void setCanCol(int nCol);
		void setFname(char newName[32]);
		int getCanCol();
};

draw::draw()
{
	strcpy(fileName,"untitled.img");
	canCol = 0;
}

void draw::drawBar()
{
	textbackground(BLACK);
	char b = 219;
	textcolor(YELLOW);
	for (int i=1;i<=24;i+=23)
	{
		gotoxy(1,i);
		for (int j=0;j<80;++j)
		{	cprintf("%c",b);
			delay(25);
		}
	}
	for(i=2;i<24;++i)
	{       gotoxy(1,i);
		cprintf("%c",b);
		delay(25);
	}
	for (i=2;i<24;++i)
	{   gotoxy(80,i);
		cprintf("%c",b);
		delay(25);
	}
	gotoxy(2,3);
	textcolor(LIGHTRED);
	for (i=0;i<78;++i)
	{
		cprintf("%c",b);
		delay(50);
	}
	gotoxy(2,18);
	for (i=0;i<78;++i)
	{
		cprintf("%c",b);
		delay(50);
	}
	gotoxy(2,20);
	for (i=0;i<78;++i)
	{
		cprintf("%c",b);
		delay(50);
	}
	gotoxy(38,1);
	textbackground(LIGHTGRAY);
	textcolor(MAGENTA);
	cprintf("u");
	delay(50);
	cprintf("D");
	delay(50);
	cprintf("r");
	delay(50);
	cprintf("a");
	delay(50);
	cprintf("w");
	delay(50);
	cprintf("!");
	delay(50);
}

void draw::drawFname()
{
	gotoxy(2,2);
	textbackground(GREEN);
	for (int i=0;i<78;++i)
	{
		cprintf(" ");
		delay(25);
	}
	gotoxy(22,2);
	textcolor(BLUE);
	for (i=0;i<strlen(fileName);++i)
	{	cprintf("%c",fileName[i]);
		delay(50);
	}
}

void draw::drawCan()
{
	textbackground(canCol);
    for (int j=4;j<=17;++j)
    {
	for (int i=2;i<=79;++i)
	{
	    gotoxy(i,j);
	    cprintf(" ");
	}
    }
}

void draw::drawConsole(int fast)
{
	if(fast)
	{	textbackground(GREEN);
		gotoxy(2,19);
		for (int i=0;i<78;++i)
		{
			cprintf(" ");
		}
		textcolor(BLUE);
		gotoxy(2,19);
		cprintf("COMMAND : ");
		for (i=2;i<80;++i)
		{
			for (int j=21;j<24;++j)
			{
				gotoxy(i,j);
				cprintf(" ");
			}
		}
		gotoxy(2,21);
		cprintf("MESSAGE : ");
	}
	else
	{
		textbackground(GREEN);
		gotoxy(2,19);
		for (int i=0;i<78;++i)
		{
			cprintf(" ");
			delay(12);
		}
		textcolor(BLUE);
		gotoxy(2,19);
		cprintf("C");
		delay(25);
		cprintf("O");
		delay(25);
		cprintf("M");
		delay(25);
		cprintf("M");
		delay(25);
		cprintf("A");
		delay(25);
		cprintf("N");
		delay(25);
		cprintf("D");
		delay(25);
		cprintf(" : ");
		for (i=2;i<80;++i)
		{
			for (int j=21;j<24;++j)
			{
				gotoxy(i,j);
				cprintf(" ");
				delay(12);
			}
		}
		gotoxy(2,21);
		cprintf("M");
		delay(25);
		cprintf("E");
		delay(25);
		cprintf("S");
		delay(25);
		cprintf("S");
		delay(25);
		cprintf("A");
		delay(25);
		cprintf("G");
		delay(25);
		cprintf("E");
		delay(25);
		cprintf(" : ");
	}
	gotoxy(2,4);
}

void draw::drawMain()
{
	drawBar();
	drawFname();
	drawConsole(0);
	drawCan();
}

void draw::setCanCol(int nCol)
{
	canCol = nCol;
}


void draw::setFname(char newName[32])
{
	strcpy(fileName,newName);
}

int draw::getCanCol()
{
    return canCol;
}

void draw::drawHelp()
{
	int tmp = getCanCol();
	setCanCol(1);
	drawCan();
	gotoxy(2,4);
	textcolor(RED+BLINK);
	cprintf("-----Instructions for using the language - uDraw!-----");
	textcolor(RED);
	gotoxy(2,5);
	cprintf("Q1. What you Need to do ?");
	gotoxy(2,6);
	cprintf("A1. Just key in the legal commands... And watch the magic box, do as you say..");
	gotoxy(2,7);
	cprintf("Q2. What are the \'legal\' commands ?");
	gotoxy(2,8);
	cprintf("A2. Here is a list of them. Case-Sensitive and Only BkSpace, for deletion : ");
	gotoxy(2,9);
	cprintf("(Press \'w\'-move up, \'s\'-move down,\'enter\'-close help)");
	char ch = '\0';
	int no = 1;
	do
	{	
		textcolor(LIGHTMAGENTA);
		for(int i=11;i<=17;++i)
		{
			for (int j=2;j<=79;++j)
			{
				gotoxy(j,i);
				cprintf(" ");
			}	
		}
		gotoxy(2,11);
		switch(no)
		{
			case 1:
				cprintf("Changes environment variable; USAGE : set <variable> <new-value>");
				gotoxy(2,12);
				cprintf("VARIABLES : brush-type/brush-color/back-color");
				gotoxy(2,13);
				cprintf("BRUSH-TYPES : dense-dots/lighter-dots/light-dots/large-box/circle/eraser/");
				gotoxy(2,14);
				cprintf("horizontal-single/horizontal-double/vertical-single/vertical-double/");
				gotoxy(2,15);
				cprintf("COLORS : (foreground+background):blue/green/cyan/red/magenta/brown/light-grey");
				gotoxy(2,16);
				cprintf("(foreground):dark-grey/yellow/white/light-(blue to magenta)");
				gotoxy(2,17);
				cprintf("EXAMPLE : set brush-type circle ");
				break;
			case 2:
				cprintf("Draws line on canvas; USAGE : draw <direction> <value>");
				gotoxy(2,12);
				cprintf("DIRECTIONS : up/down/left/right/");
				gotoxy(2,13);
				cprintf("up-right/up-left/down-right/down-left");
				gotoxy(2,14);
				cprintf("VALUE : any positive integer (no of rows/columns)");
				gotoxy(2,15);
				cprintf("EXAMPLE : draw down-right 3 ");
				break;
			case 3:
				cprintf("Moves brush without drawing; USAGE : go <direction> <value>");
				gotoxy(2,12);
				cprintf("DIRECTIONS AND VALUE : same as in \'draw\'");
				gotoxy(2,13);
				cprintf("EXAMPLE : go up-left 4 ");
				break;
			case 4:
				cprintf("Displays info about environment variables; USAGE : get-info <variable>");
				gotoxy(2,12);
				cprintf("VARIABLE : same as in \'set\' including \'all\'");
				gotoxy(2,13);
				cprintf("EXAMPLE : get-info all ");
				break;
			case 5:
				cprintf("Saves file onto hard-disk; USAGE : save <filename>");
				gotoxy(2,12);
				cprintf("FILENAME : any string (max-length : 32 characters)");
				gotoxy(2,13);
				cprintf("EXAMPLE : save nEw1 ");
				break;
			case 6:
				cprintf("Opens file from hard-disk; USAGE : open <filename>");
				gotoxy(2,12);
				cprintf("FILENAME : name of any existing \'.img\' file in same folder");
				gotoxy(2,13);
				cprintf("EXAMPLE : open nEw1 ");
				break;
			case 7:
				cprintf("Creates a new file; USAGE : new");
				gotoxy(2,12);
				cprintf("EXAMPLE : new ");
				break;
			case 8:
				cprintf("Clears canvas; USAGE : clear");
				gotoxy(2,12);
				cprintf("EXAMPLE : clear ");
				break;
			case 9:
				cprintf("Exits the program; USAGE : exit");
				gotoxy(2,12);
				cprintf("EXAMPLE : exit ");
				break;
			case 10:
				cprintf("Displays this help window; USAGE : help");
				gotoxy(2,12);
				cprintf("EXAMPLE : help ");
				break;
		}
		ch=getch();
		switch(ch)
		{
			case 's':
			case 'S':
				if(no<10)
					no++;
				else
					no=1;
				break;
			case 'w':
			case 'W':
				if(no>1)
					no--;
				else
					no=10;
		}
	}while(ch!='\r');
	setCanCol(tmp);
}

#endif
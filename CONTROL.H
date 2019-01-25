#ifndef CONTROL_H
#define CONTROL_H

#include "CONTAINE.H"
#include "DRAW.H"
#include "SAVE.H"
#include <process.h>
#include <conio.h>
#include <string.h>

class control
{
    stkPt fStk;
    save fSave;
    draw fDraw;
    int status;
    void askInput();
    void prnMsg(int code);
    void takeAction(int nOc,char codes[3][32]);
    void colIn(char text[64]);
    int getCode1(char cmd[32]);
    int getCode2(char cmd[32]);
    int getCode3(char cmd[32]);
    int c2i(char cmd[32]);
    int code1,code2,code3;
    public:
	control();
	void drawMenu();
};

control::control()
{
    status=0;
}

void control::drawMenu()
{
    if(!status)
    {
	clrscr();
	fDraw.drawMain();
	fDraw.drawHelp();
	textbackground(fDraw.getCanCol());
	fDraw.drawCan();
	fStk.artist.show(0);
	askInput();
    }
    else
    {	askInput();
    }
}

void control::colIn(char text[64])
{
    int i=0;
    while(1)
    {
	char tmp=getch();
	if (i>0&&tmp=='\b')
	{
	    cprintf("\b \b");
	    text[i--] = '\0';
	}
	else if((i==0&&tmp=='\b')||(i==63))
	   continue;
	else if(tmp == '\r')
	{
		text[i] = '\0';
	    while(i>0)
        {
            cprintf("\b \b");
			--i;
        }
		break;
	}
	else
	{
	    text[i++] = tmp;
	    cprintf("%c",tmp);
	}
    }
}

void control::askInput()
{
    gotoxy(12,19);
    textbackground(GREEN);
    textcolor(LIGHTCYAN);
    char userIn[64];
	colIn(userIn);
    code1=code2=code3=-1;
    char cmds[3][32];
    int i=0,j=0;
    while(userIn[i]!=' '&&userIn[i]!='\0')
	{   cmds[0][j++] = userIn[i++];
		cmds[0][j] = '\0';
	}
	code1 = getCode1(cmds[0]);
    if (code1>0&&userIn[i]!='\0')
    {
	j=0;i++;
	while(userIn[i]!=' '&&userIn[i]!='\0')
    {
        cmds[1][j++] = userIn[i++];
		cmds[1][j] = '\0';
    }
	code2 = getCode2(cmds[1]);
	if (userIn[i]!='\0'&&code2>0)
	{
	    i++;
		j=0;
	    while(userIn[i]!='\0')
		{
		    cmds[2][j++] = userIn[i++];
			cmds[2][j] = '\0';
		}
	    code3 =getCode3(cmds[2]);
	    if (code3>-1)
		takeAction(3,cmds);
	    else
		{	prnMsg(0);
			askInput();
		}
	}
	else if(code2>0)
	    takeAction(2,cmds);
	else
	{	prnMsg(0);
		askInput();
	}
    }
    else if(code1>0)
        takeAction(1,cmds);
    else
    {	prnMsg(0);
		askInput();
	}
}

int control::getCode1(char cmd[32])
{
    if(!strcmp(cmd,"set"))
	return 1;
    else if(!strcmp(cmd,"draw"))
	return 2;
    else if(!strcmp(cmd,"go"))
	return 3;
    else if(!strcmp(cmd,"get-info"))
	return 4;
    else if(!strcmp(cmd,"save"))
	return 5;
    else if(!strcmp(cmd,"open"))
	return 6;
    else if(!strcmp(cmd,"new"))
	return 7;
    else if(!strcmp(cmd,"exit"))
	return 8;
    else if(!strcmp(cmd,"clear"))
	return 9;
	else if(!strcmp(cmd,"help"))
	return 10;
    else
	return 0;
}

int control::getCode2(char cmd[32])
{
    if(code1==5||code1==6)
	return 9;
    else if(!strcmp(cmd,"brush-type")||!strcmp(cmd,"right"))
	return 1;
    else if(!strcmp(cmd,"brush-color")||!strcmp(cmd,"left"))
	return 2;
    else if(!strcmp(cmd,"back-color")||!strcmp(cmd,"up"))
	return 3;
    else if(!strcmp(cmd,"all")||!strcmp(cmd,"down"))
	return 4;
    else if(!strcmp(cmd,"up-right"))
	return 5;
    else if(!strcmp(cmd,"up-left"))
	return 6;
    else if(!strcmp(cmd,"down-right"))
	return 7;
    else if(!strcmp(cmd,"down-left"))
	return 8;
    else
	return 0;
}

int control::getCode3(char cmd[32])
{
    if (!strcmp(cmd,"black"))
	return 0;
    else if(!strcmp(cmd,"dense-dots")||!strcmp(cmd,"blue"))
	return 1;
    else if(!strcmp(cmd,"lighter-dots")||!strcmp(cmd,"green"))
	return 2;
    else if(!strcmp(cmd,"light-dots")||!strcmp(cmd,"cyan"))
	return 3;
    else if(!strcmp(cmd,"large-box")||!strcmp(cmd,"red"))
	return 4;
    else if(!strcmp(cmd,"circle")||!strcmp(cmd,"magenta"))
	return 5;
    else if(!strcmp(cmd,"horizontal-single")||!strcmp(cmd,"brown"))
	return 6;
    else if(!strcmp(cmd,"horizontal-double")||!strcmp(cmd,"light-grey"))
	return 7;
    else if(!strcmp(cmd,"vertical-single")||!strcmp(cmd,"dark-grey"))
	return 8;
    else if(!strcmp(cmd,"vertical-double")||!strcmp(cmd,"light-blue"))
	return 9;
    else if(!strcmp(cmd,"eraser")||!strcmp(cmd,"light-green"))
	return 10;
    else if(!strcmp(cmd,"light-cyan"))
	return 11;
    else if(!strcmp(cmd,"light-red"))
	return 12;
    else if(!strcmp(cmd,"light-magenta"))
	return 13;
    else if(!strcmp(cmd,"yellow"))
	return 14;
    else if(!strcmp(cmd,"white"))
	return 15;
    else if(c2i(cmd)>0)
	return 16;
    else
	return -1;
}

int control::c2i(char cmd[32])
{
    int res=0,i=0;
    while(cmd[i]>='0'&&cmd[i]<='9')
    {
	res= res*10+(cmd[i]-48);
	++i;
    }
    return res;
}

void control::takeAction(int nOc,char codes[3][32])
{
    if(nOc==1)
    {
		switch(code1)
		{
			case 7:
				fDraw.setFname("untitled.img");
				fDraw.setCanCol(0);
				fDraw.drawFname();
				fDraw.drawCan();
				fStk.clearStk();
				fStk.artist.def();
				prnMsg(7);
				break;
			case 8:
				prnMsg(8);
				getch();
				exit(0);
			case 9:
				fStk.clearStk();
				fDraw.drawCan();
				fStk.artist.show(0);
				prnMsg(9);
				break;
			case 10:
				fDraw.drawHelp();
				fDraw.drawCan();
				fStk.prnStk();
				fStk.artist.show(0);
				prnMsg(10);
		}
		status=1;
		drawMenu();
    }
    else if(nOc==2)
    {
	switch(code1)
	{
	    case 4:
		switch(code2)
		{
		    case 1:
			prnMsg(41);
			break;
			
		    case 2:
			prnMsg(42);
			break;
			
		    case 3:
			prnMsg(43);
			break;
			
		    case 4:
			prnMsg(44);
		}
		status=2;
		break;
		
		
	    case 5:
		fSave.saveFile(fStk,fDraw,strcat(codes[1],".img"));
		fDraw.setFname(codes[1]);
		fDraw.drawFname();
		prnMsg(5);
		status=3;
		break;
		
		
	    case 6:
		if(fSave.openFile(fStk,fDraw,strcat(codes[1],".img")))
		{
			fDraw.setFname(codes[1]);
		    fDraw.drawFname();
			fDraw.drawCan();
			fStk.prnStk();
		    fStk.artist.def();
		    prnMsg(6);
		    status=1;
		}
		else
		{
		    prnMsg(-6);
		    status=2;
		}
	}
	drawMenu();
    }
    else
    {
	textbackground(fDraw.getCanCol());
	switch(code1)
	{
	    case 1:
		switch(code2)
		{
		    case 1:
			switch(code3)
			{
			    case 1:
				fStk.artist.setType(178);
				break;
			    case 2:
				fStk.artist.setType(177);
				break;
			    case 3:
				fStk.artist.setType(176);
				break;
			    case 4:
				fStk.artist.setType(219);
				break;
			    case 5:
				fStk.artist.setType(233);
				break;
			    case 6:
				fStk.artist.setType(196);
				break;
			    case 7:
				fStk.artist.setType(205);
				break;
			    case 8:
				fStk.artist.setType(179);
				break;
			    case 9:
				fStk.artist.setType(186);
				break;
				case 10:
				fStk.artist.setType(32);
			}
			if(code3>=1&&code3<=10)
			{	fStk.artist.show(0);
				prnMsg(11);
			}
			else
				prnMsg(-11);
			break;

		    case 2:
				fStk.artist.setCol(code3);
				fStk.artist.show(0);
				prnMsg(12);
				break;

		    case 3:
			if (code3>=0&&code3<=7)
			{
			    fDraw.setCanCol(code3);
				fDraw.drawCan();
			    fStk.prnStk();
				fStk.artist.show(0);
			    prnMsg(13);
			}
			else
			    prnMsg(-13);
		}
		break;
		
		
	    case 2:
		switch(code2)
		{
		    case 1:
			if(fStk.draw(c2i(codes[2]),0))
			    prnMsg(2);
			else
			    prnMsg(-2);
			break;

		    case 2:
			if(fStk.draw(-1*c2i(codes[2]),0))
			    prnMsg(2);
			else
			    prnMsg(-2);
			break;
		    case 3:
			if(fStk.draw(0,-1*c2i(codes[2])))
			    prnMsg(2);
			else
			    prnMsg(-2);
			break;
		    case 4:
			if(fStk.draw(0,c2i(codes[2])))
			    prnMsg(2);
			else
			    prnMsg(-2);
			break;
		    case 5:
			if(fStk.draw(c2i(codes[2]),-1*c2i(codes[2])))
			    prnMsg(2);
			else
			    prnMsg(-2);
			break;
		    case 6:
			if(fStk.draw(-1*c2i(codes[2]),-1*c2i(codes[2])))
			    prnMsg(2);
			else
			    prnMsg(-2);
			break;
		    case 7:
			if(fStk.draw(c2i(codes[2]),c2i(codes[2])))
			    prnMsg(2);
			else
			    prnMsg(-2);
			break;
		    case 8:
			if(fStk.draw(-1*c2i(codes[2]),c2i(codes[2])))
			    prnMsg(2);
			else
			    prnMsg(-2);

		}
		textbackground(fDraw.getCanCol());
		fStk.prnStk();
		fStk.artist.show(0);
		break;
		
	    case 3:
		switch(code2)
		{
		    case 1:
			if(fStk.artist.move(c2i(codes[2]),0,0))
			    prnMsg(3);
			else
			    prnMsg(-3);
			break;
			
		    case 2:
			if(fStk.artist.move(-1*c2i(codes[2]),0,0))
			    prnMsg(3);
			else
			    prnMsg(-3);
			break;
			
		    case 3:
			if(fStk.artist.move(0,-1*c2i(codes[2]),0))
			    prnMsg(3);
			else
			    prnMsg(-3);
			break;
			
		    case 4:
			if(fStk.artist.move(0,c2i(codes[2]),0))
			    prnMsg(3);
			else
			    prnMsg(-3);
			break;
			
		    case 5:
			if(fStk.artist.move(c2i(codes[2]),-1*c2i(codes[2]),0))
			    prnMsg(3);
			else
			    prnMsg(-3);
			break;
			
		    case 6:
			if(fStk.artist.move(-1*c2i(codes[2]),-1*c2i(codes[2]),0))
			    prnMsg(3);
			else
			    prnMsg(-3);
			break;
			
		    case 7:
			if(fStk.artist.move(c2i(codes[2]),c2i(codes[2]),0))
			    prnMsg(3);
			else
			    prnMsg(-3);
			break;
			
		    case 8:
			if(fStk.artist.move(-1*c2i(codes[2]),c2i(codes[2]),0))
			    prnMsg(3);
			else
			    prnMsg(-3);
		}
		textbackground(fDraw.getCanCol());
		fStk.prnStk();
		fStk.artist.show(0);
	}
	status=2;
	drawMenu();
    }
}

void control::prnMsg(int code)
{
    fDraw.drawConsole(1);
	textbackground(GREEN);
    textcolor(RED);
    gotoxy(12,21);
    switch(code)
    {
		case 0:
			cprintf("OOPS! Didnt get that...!!!");
			break;
		case 11:
			cprintf("Brush type changed successfully!!!");
            break;
		case -11:
			cprintf("Are you sure, that its a correct brush-type???");
			break;
        case 12:
            cprintf("Brush color changed successfully...!!!");
            break;
        case 13:
            cprintf("Back color changed successfully!!!");
            break;
        case -13:
            cprintf("Uh Ohhh... I am sorry, but that color is not in bg range...!!!");
            break;
        case 2:
            cprintf("Line drawn successfully...!!!");
            break;
        case -2:
            cprintf("I guess... Thats Out of Bounds!!!");
            break;
        case 3:
            cprintf("Our Artist moved successfully...!!!");
            break;
        case -3:
            cprintf("Uh Oh!!! Our Artist cant go till there!!!");
            break;
        case 41:
            cprintf("So, the brush type is : ");
            gotoxy(12,22);
            cprintf("%c - I guess you can name that yourself...!!!",(char)fStk.artist.getType());
            break;
        case 42:
            cprintf("The brush color, ummm...");
            gotoxy(12,22);
            cprintf("That is this : ");
            textcolor(fStk.artist.getCol());
            cprintf("%c",(char)219);
            break;
        case 43:
            cprintf("The background color, ummm...");
            gotoxy(12,22);
            textcolor(fDraw.getCanCol());
            cprintf("!!!THIS IS THE BACKGROUND COLOR!!!");
            break;
        case 44:
            cprintf("So, this is everything you can know...");
            gotoxy(12,22);
            textcolor(fStk.artist.getCol());
            cprintf("The brush type : %c and Color...",(char)fStk.artist.getType());
            gotoxy(12,23);
            textcolor(fDraw.getCanCol());
            cprintf("And 'tis, the background color!!!");
            break;
        case 5:
            cprintf("File saved successfully... Open it anytime you want...");
            break;
        case 6:
            cprintf("And thats your saved artwork...");
            gotoxy(12,22);
            cprintf("Yeah... Right over there ^^^");
            break;
        case -6:
            cprintf("Are you sure that it even exists?");
            gotoxy(12,22);
            cprintf("And in the same folder?");
            gotoxy(12,23);
            cprintf("Better Luck Next Time anyways!!!");
            break;
        case 7:
            cprintf("New Image Created Successfully...");
            gotoxy(12,22);
            cprintf("For you...");
            break;
        case 8:
            cprintf("Thanks for using me. Kudos to the author...");
            gotoxy(12,22);
            cprintf("Just a joke... Author's sincere appreciation for...");
			gotoxy(12,23);
			cprintf("donating your valuable time!!!");
			break;
		case 9:
			cprintf("And There you go, I have cleared the screen for you!!!");
			break;
		case 10:
			cprintf("I hope that was useful for you, mate...");
    }
}


#endif
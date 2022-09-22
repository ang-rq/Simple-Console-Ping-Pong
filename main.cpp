#include <iostream>
#include <windows.h>
#include <conio.h>
#include <iomanip>
#include <time.h>
using namespace std;

int pl1pos,pl2pos,l=7
,width=70,height=24,d=2;
int ballx=width/2,bally=height/2;
int direcx=1;
int direcy=1;
bool finish;
int okx=1,oky=1;
int dellay=50;
bool pl1win=false,pl2win=false;


void gotoxy( int column, int line )
{
    COORD coord;
    coord.X = column;
    coord.Y = line;
    SetConsoleCursorPosition(
        GetStdHandle( STD_OUTPUT_HANDLE ),
        coord
    );
}

void drawLine(char a,int x1,int y1,int x2,int y2)
{
    int d;
    bool finish=false;

    while(!finish)
    {
        if(a=='x' || a=='X')
        {
            if(x1-x2>0)
                x1--;
            if(x2-x1>0)
                x1++;
        }

        if(a=='y' || a=='Y')
        {
            if(y1-y2>0)
                y1--;
            if(y2-y1>0)
                y1++;
        }
        gotoxy(x1,y1);

        cout<<"#";

        if((a=='x' || a=='X') && x1==x2)
            finish=true;
        if((a=='y' || a=='Y') && y1==y2)
            finish=true;

        //getch();

    }

}

void drawEmptyLine(char a,int x1,int y1,int x2,int y2)
{
    int d;
    bool finish=false;

    while(!finish)
    {
        if(a=='x' || a=='X')
        {
            if(x1-x2>0)
                x1--;
            if(x2-x1>0)
                x1++;
        }

        if(a=='y' || a=='Y')
        {
            if(y1-y2>0)
                y1--;
            if(y2-y1>0)
                y1++;
        }
        gotoxy(x1,y1);

        cout<<" ";

        if((a=='x' || a=='X') && x1==x2)
            finish=true;
        if((a=='y' || a=='Y') && y1==y2)
            finish=true;

        //getch();

    }

}

void createCanvas(int width,int height)
{
    drawLine('y',0,0,0,height);
    drawLine('x',0,height,width,height);
    drawLine('y',width,height,width,0);
    drawLine('x',width,0,0,0);

}

void showBall()
{
    if(ballx<=d+1 && (bally<pl1pos && bally>pl1pos-l+1))
        okx=1;
    if(ballx>=width-d && (bally<pl2pos && bally>pl2pos-l+1))
        okx=-1;
    if(bally<=1)
        oky=1;
    if(bally>=height-1)
        oky=-1;


/*
    if(bally<pl2pos && bally>pl2pos-l+1)
    {
        gotoxy(width/2-10,height/2);
        cout<<"DA";
    }


    if(bally<pl1pos && bally>pl1pos-l+1)
    {
        gotoxy(width/2+10,height/2);
        cout<<"DA";
    }
*/







    if(okx==1)
        ballx++;
    if(okx==-1)
        ballx--;
    if(oky==1)
        bally++;
    if(oky==-1)
        bally--;

    if(ballx==1)
    {
        finish=true;
        pl2win=true;
    }

    if(ballx==width-1)
    {
        finish=true;
        pl1win=true;
    }


    if(ballx>2)
    {
        gotoxy(ballx-1,bally);
        cout<<' ';

        if(oky!=1)
        {
        gotoxy(ballx-1,bally+1);
        cout<<' ';
        }

        if(oky!=-1)
        {
        gotoxy(ballx-1,bally-1);
        cout<<' ';
        }
    }

    if(ballx<width-2)
    {
        gotoxy(ballx+1,bally);
        cout<<' ';

        if(oky!=-1)
        {
        gotoxy(ballx+1,bally-1);
        cout<<' ';
        }

        if(oky!=1)
        {
        gotoxy(ballx+1,bally+1);
        cout<<' ';
        }

    }


    if(bally>2)
    {
        gotoxy(ballx,bally-1);
        cout<<' ';

        if(okx!=-1)
        {
        gotoxy(ballx-1,bally-1);
        cout<<' ';
        }

        if(okx!=1)
        {
        gotoxy(ballx+1,bally-1);
        cout<<' ';
        }

    }

    if(bally<height-2)
    {
        gotoxy(ballx,bally+1);
        cout<<' ';

        if(okx!=-1)
        {
        gotoxy(ballx-1,bally+1);
        cout<<' ';
        }

        if(okx!=1)
        {
        gotoxy(ballx+1,bally+1);
        cout<<' ';
        }
    }



    gotoxy(ballx,bally);
    cout<<"#";
}



void showPlayer1(int pl1pos)
{
    gotoxy(d,pl1pos+1);
    cout<<' ';
    gotoxy(d,pl1pos-l-1);
    cout<<' ';
    drawLine('y',d,pl1pos,d,pl1pos-l+1);

}

void showPlayer2(int pl2pos)
{
    gotoxy(width-d,pl2pos+1);
    cout<<' ';
    gotoxy(width-d,pl2pos-l-1);
    cout<<' ';
    drawLine('y',width-d,pl2pos,width-d,pl2pos-l+1);

}

void setup()
{

    createCanvas(width,height);
    pl1pos=height/2;
    pl2pos=height/2;

}

void checkForInputPlayer1()
{

    if( GetAsyncKeyState( 'W' ) & 0x1 )
        if(pl1pos >= 7)
            pl1pos--;
    if( GetAsyncKeyState( 'S' ) & 0x1 )
        if(pl1pos <= height)
            pl1pos++;


}

void checkForInputPlayer2()
{
    if( GetAsyncKeyState( 'O' ) & 0x1  )
        if(pl2pos >= 7)
            pl2pos--;
    if( GetAsyncKeyState( 'L' ) & 0x1 )
        if(pl2pos <= height)
            pl2pos++;
}

int main()
{
    setup();
    while(!finish)
    {



        showPlayer1(pl1pos);
        showPlayer2(pl2pos);

        checkForInputPlayer1();
        checkForInputPlayer2();

        showBall();





        //gotoxy(30,5);
        //cout<<ballx;
        Sleep(dellay);

    }

    char reset;
    system("cls");
    gotoxy(width/2,height/2);
    if(pl1win)
    cout<<"Winner:  PLAYER 1";
    if(pl2win)
    cout<<"Winner:  PLAYER 2";
    Sleep(1000);
    reset=getch();
    if(reset=='r')
    {

        int pl1pos,pl2pos,l=4,width=70,height=24,d=2;
        int ballx=width/2,bally=height/2;
        int direcx=1;
        int direcy=1;
        bool finish;
        int okx=1,oky=1;
        int dellay=50;
        bool pl1win=false,pl2win=false;

    }

    return 0;
}

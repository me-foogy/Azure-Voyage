//shreekrishna.sulu@kecktm.edu.np
#include <iostream>
#include <graphics.h>
#include <conio.h>
#include <string>
#include <fstream>
#include <mmsystem.h>
#include <windows.h>


using namespace std;

//window resolution
int width =800;
int height =600;

//ellipse radius
int radiusX = 20;
int radiusY = 25;

//initial positions
int initialX = width/2;
int initialY=(height/2)+150;

//clouds
int Cloudsx = initialX;
int Cloudsy = initialY;
float C = 600, D = 200, E = 600, i = 0;


//Scoring system (karki)
int obstacle_topcoor;

//Obstacle
int random;//To save the random value for obstacle
int obstacle_size=200;
int xtopleft=400;
int ytopleft=0;
int xbottomright=xtopleft+obstacle_size;
int ybottomright=ytopleft+10;
void obstacle();

bool collision;
bool collided=false;

int padding=200;//both side border declaration
int progress=0;
float speed=0;
int speed_limit=5;

//for upperbound
int up=600;
int lb=200;

//Scoring system
int score=-2;
int scoreflag=0;
int scoreflag1=0;
int highscore;

//main menu
int centerX=width/2;
int centerY=height/2;

//for conversion of int to char for score display
char str[20];
char hstr[20];

//start game
int start=0;



int buffer;

void paddingBorder();
void sideControllsText();
void clouds();
void clouds2();
void clouds3();
void movement();
int endscreen();
void gameloop();
void restart();
int main();

bool isRectIntersect(int, int, int, int, int, int, int, int );

//FILE HANDLEING
void filehandleing_write()
{
    // Write the integer to a file
    ofstream outFile("highscore.txt");
    if (outFile.is_open())
    {
        outFile <<score;
        outFile.close();
        //cout << "Integer written to file successfully." << endl;
    }
    else
    {
        //cout << "Error opening the file." << endl;
    }
}
void filehandleing_read()
{
    ifstream inFile("highscore.txt");
    if (inFile.is_open())
    {
        inFile >> highscore;
        inFile.close();
       // cout << "Integer read from file: " << highscore << endl;
    }
    else
    {
        //cout << "Error opening the file." << endl;
        score=0;
        filehandleing_write();
        filehandleing_read();
        score=-1;
    }

}


int mainMenu()
{
    int option=1;
    while (true)
    {
        cleardevice();
        setcolor(WHITE);
        settextstyle(DEFAULT_FONT,HORIZ_DIR,4);

        outtextxy(centerX-180,centerY-100,"AZURE VOYAGE!");
        settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
        outtextxy(centerX-50,centerY,"START");
        sprintf(hstr,"%d",highscore);
        outtextxy(centerX+115,centerY+151,hstr);
        outtextxy(centerX-150,centerY+150,"HIGH SCORE:");
        outtextxy(centerX-40,centerY+50,"EXIT");
        setcolor(YELLOW);
        outtextxy(centerX-80,centerY+(option-1)*50,"*");
        delay(100);

        if(GetAsyncKeyState(VK_UP))  //Don't use getch(); for key input in graphics.h. It is a console based syntax.
        {
            if(option>1)option--;
        }
        if(GetAsyncKeyState(VK_DOWN))
        {
            if(option<2)option++;
        }
        if(GetAsyncKeyState(VK_RETURN))
        {
            if(option==1)
            {
                start = 1;
                gameloop();
            }
            else
            {
                cout<<"Exiting the game.......";
                cleardevice();
                closegraph();
                exit(0);
                break;
            }
        }
    }



}


void character()
{
    int wireColour = 1;
    int heightWire = initialY +  radiusY + 10;
    if(!collided)
    {
        movement();
    }
    if(D>1000)
    {
        C=600+(rand()%800);
        E=C;
        D=-200;
    }
    // Draw character to the off-screen buffer //
    setactivepage(buffer);
    setvisualpage(1 - buffer);
    cleardevice();
    clouds();
    clouds2();
    clouds3();
    //Baloon Part
    setcolor(wireColour);
    setfillstyle(SOLID_FILL,RED_VALUE(200)); //Fills ellipse
    fillellipse(initialX,initialY,radiusX, radiusY); //Makes ellipse
    //Horizontal Wire
    setcolor(wireColour);
    ellipse(initialX,initialY-2,1,1,radiusX-1, 7);
    setcolor(RED);
    fillellipse(initialX,initialY-2-1,radiusX-1, 7);
    //Inner ellipse(inner wires)
    setcolor(wireColour);
    ellipse(initialX,initialY,1,1,radiusX-10, radiusY);
    setcolor(wireColour);
    setfillstyle(SOLID_FILL,BLUE_VALUE(1));
    line(initialX,initialY+radiusY,initialX,heightWire);//Middle Wire
    line(initialX+5,initialY+radiusY,initialX+3,heightWire);//Right Wire
    line(initialX-5,initialY+radiusY,initialX-3,heightWire);//Left WIre
    setfillstyle(SOLID_FILL,GREEN);
    rectangle(initialX-5,initialY+radiusY+10,initialX+5,heightWire+10);
    setfillstyle(SOLID_FILL,RED_VALUE(90));
    bar(initialX-5,initialY+radiusY+10,initialX+5,heightWire+10);
    setactivepage(buffer);
    buffer = 1-buffer;
}


void background()
{
    cleardevice();
    setbkcolor(LIGHTBLUE);
}

void cloudmovement()
{
    C = E - 0.4*i;
    D = D + 0.4;
    i++;
}

void clouds()
{
    if(!collided)
    {
        cloudmovement(); // Move the clouds //
    }

    setcolor(WHITE);
    setfillstyle(SOLID_FILL, WHITE);
    fillellipse(C, D, 20, 20);
    fillellipse(C + 30, D - 15, 30, 30);
    fillellipse(C + 90, D - 10, 25, 25);
    fillellipse(C + 60, D - 15, 35, 35);
    fillellipse(C + 120, D + 5, 15, 15);
    rectangle(C, D, C + 120, D + 19);
    floodfill(C + 45, D + 18, WHITE);
    floodfill(C + 105, D + 18, WHITE);
}

void clouds2() // Cloud with a slight variation //
{
    setcolor(WHITE);
    setfillstyle(SOLID_FILL,WHITE);
    fillellipse(C+800,D-300,20,20);
    fillellipse(C+800+30,D-300-15,30,30);
    fillellipse(C+800+60,D-300-10,25,25);
    fillellipse(C+800+90,D-300-15,35,35);
    fillellipse(C+800+120,D-300+5,15,15);
    rectangle(C+800,D-300,C+800+120,D-300+19);
    floodfill(C+800+45,D-300+18,WHITE);
    floodfill(C+800+105,D-300+18,WHITE);
}
void clouds3() // Cloud with a slight variation //
{
    setcolor(WHITE);
    setfillstyle(SOLID_FILL,WHITE);
    fillellipse(C-800,D-100,20,20);
    fillellipse(C-800+30,D-100-15,30,30);
    fillellipse(C-800+60,D-100-10,25,25);
    fillellipse(C-800+90,D-100-15,35,35);
    fillellipse(C-800+120,D-100+5,15,15);
    rectangle(C-800,D-100,C-800+120,D-100+19);
    floodfill(C-800+45,D-100+18,WHITE);
    floodfill(C-800+105,D-100+18,WHITE);
}

int progress_value=1;//used to change speed value of obstacles where greater int is slower progress

void obstacle()
{
    setfillstyle(SOLID_FILL,BLACK);
    rectangle(xtopleft,ytopleft,xbottomright,ybottomright);
    floodfill(xtopleft+1,ytopleft+1,BLUE);
    if(!collided)
    {
        ytopleft+=speed+2;
        ybottomright+=speed+2;
    }
    if(ytopleft>height)
    {
        obstacle_size=150+rand()%50;
        random=(padding-50)+rand()%(width-(padding+200));
        xtopleft=random;
        xbottomright=random+obstacle_size;
        ytopleft=0;//please don't change this the scoring system depends on it;
        ybottomright=10;
        progress+=5;//Keeping track of progress
    }
    if(progress==progress_value)
    {
        if(speed<speed_limit)
        {
            speed+=0.1;
            progress=0;
        }}}

//Any thing you change in obstacle 1 needs to be changed in obstacle 2 as variables are not declared
//Obstacle
int random1;//To save the random value for obstacle
int obstacle_size1=200;
int xtopleft1=200;
int ytopleft1=-300;
int xbottomright1=xtopleft1+obstacle_size1;
int ybottomright1=ytopleft1+10;
int ytopleft1_temp;
void obstacle1();
//KARKI END
void obstacle1()
{
    setfillstyle(SOLID_FILL,RED);
    rectangle(xtopleft1,ytopleft1,xbottomright1,ybottomright1);
    floodfill(xtopleft1+1,ytopleft1+1,BLUE);


    if(!collided)
    {
        ytopleft1+=speed+2;
        ybottomright1+=speed+2;
    }


    if(ytopleft1>height)
    {
        obstacle_size1=150+rand()%50;
        random1=(padding-50)+rand()%(width-(padding+200));
        xtopleft1=random1;
        xbottomright1=random1+obstacle_size1;
        ytopleft1_temp=0;//please don't change this the scoring system depends on it;
        ytopleft1=-20+rand()%40;
        ybottomright1=ytopleft1+10;
        progress+=5;//Keeping track of progress
    }
    if(progress==progress_value)
    {
        if(speed<speed_limit)
        {
            speed+=0.1;
            progress=0;
        }
    }
}

void movement()
{
    if(collision){delay(1000);}
    //else
    {if (initialX<width-padding)
        {if(GetAsyncKeyState(VK_RIGHT))
            {initialX +=5;}}
        if (initialX>padding)
        {if(GetAsyncKeyState(VK_LEFT))
            {initialX -=5;}}
        if(GetAsyncKeyState(VK_UP))
        {initialY -=5;}
        if(GetAsyncKeyState(VK_DOWN))
        {initialY +=5;}
    }
}

void collider()
{
    int balloonLeft = initialX - radiusX;
    int balloonRight = initialX + radiusX;
    int balloonTop = initialY - radiusY;
    int balloonBottom = initialY + radiusY;
    obstacle_topcoor=balloonTop;//solely for the purpose of count
    //rectangle(balloonLeft+3,balloonTop+5,balloonRight-5,balloonBottom-5);
    collision = isRectIntersect(balloonLeft, balloonTop, radiusX * 2, radiusY * 2,
    xtopleft, ytopleft, xbottomright - xtopleft, ybottomright - ytopleft);
    if (collision)
    {
        collided = true;
        endscreen();
    }
    collision = isRectIntersect(balloonLeft, balloonTop, radiusX * 2, radiusY * 2,
    xtopleft1, ytopleft1, xbottomright1 - xtopleft1, ybottomright1 - ytopleft1);

    if (collision)
    {
        collided = true;
        endscreen();
    }
}

void score_display()
{
    if(ybottomright>obstacle_topcoor)
    {scoreflag+=1;}
    if(scoreflag==1)
    {score+=1;}
    if(ytopleft==0)scoreflag=0;
    if(ybottomright1>obstacle_topcoor)scoreflag1+=1;
    if(scoreflag1==1)score+=1;
    if(ytopleft1_temp==0)
    {
        scoreflag1=0;
        ytopleft1_temp=1;
    }
    sprintf(str,"%d",score);
    settextstyle(BOLD_FONT,HORIZ_DIR,5);
    outtextxy(width-100,100,str);
    settextstyle(BOLD_FONT,HORIZ_DIR,5);
    outtextxy(width- 150,50,"SCORE");
}

void gameloop()
{
    while(true)
    {
        score_display();
        while(start == 0)
        {
            mainMenu();
            break;
        }
        character();
        obstacle1();
        rectangle(0,0,-10,10);
        obstacle();
        collider();
        delay(5);
    }

}

bool isRectIntersect(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2)
{
    if (x1 < x2 + w2 && x1 + w1 > x2 && y1 < y2 + h2 && y1 + h1 > y2)
    {
        return true; // The rectangles intersect
    }
    return false; // The rectangles do not intersect
}
int endscreen()
{
    clouds();cloudmovement();cleardevice();
    setbkcolor(LIGHTBLUE);
    setcolor(WHITE);
    settextstyle(BOLD_FONT,HORIZ_DIR,6);
    rectangle(centerX-153, centerY-105, centerX+161, centerY-45);
    outtextxy(centerX-150,centerY-100,"GAME OVER!");
    settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
    outtextxy(centerX-150,centerY-20,"Score:");
    sprintf(str,"%d",score);
    outtextxy(centerX-5,centerY-20,str);
    if(score>highscore)
    {
        filehandleing_write();
        highscore=score;}
    outtextxy(centerX-150,centerY+19,"High Score:");
    settextstyle(DEFAULT_FONT,HORIZ_DIR,2);;
    sprintf(hstr,"%d",highscore);//Display Window
    settextstyle(3,HORIZ_DIR,5);
    settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
    outtextxy(centerX+115,centerY+20,hstr);
    settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
    outtextxy(centerX-170,centerY+200,"PRESS ENTER TO Exit.");
    if(GetAsyncKeyState(VK_RETURN))
    {exit(0);}
}

void restart()
{
    int initialX = width/2;
    int initialY=height/2;
    progress = 0;
    speed = 0;
    int xtopleft=400;
    int ytopleft=0;
    int xtopleft1=400;
    int ytopleft1=0;
    bool collided=false;
    background();
    int buffer=0;
    clouds();
    gameloop();
    collider();
}

void paddingBorder()
{
    setfillstyle(SOLID_FILL,LIGHTBLUE);
    bar(0,0,175,800);
    bar(800-175,0,800,800);
    setcolor(WHITE);
    rectangle(0,0,175,800);
    rectangle(800-175,0,800,800);

}

void sideControllsText()
{
    settextstyle(BOLD_FONT,HORIZ_DIR,2);
    outtextxy(centerX-375,centerY+125,"Controls");
    outtextxy(centerX-375,centerY+180,"left   <-");
    outtextxy(centerX-375,centerY+160,"right  ->");
    settextstyle(BOLD_FONT,HORIZ_DIR,4);
    outtextxy(centerX-375,centerY-200,"AZURE");
    outtextxy(centerX-375,centerY-170,"VOYAGE");
}

int main()
{
    initwindow(width,height,"Azure Voyage");
    /////////////////////
    PlaySound(TEXT("music.wav"), NULL, SND_FILENAME | SND_ASYNC);
    filehandleing_read();
    ////////////////////////
    background();
    int buffer=0;
    clouds();
    gameloop();
    collider();
};

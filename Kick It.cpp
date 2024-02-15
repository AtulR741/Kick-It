#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>
#include <graphics.h>
using namespace std;

double vel = 0, initvel = 0, sidevel = 0, gravity = 0.8, friction = 0.1;
int score = 0, high;
POINT pos;

class Ball{
	public:
		int x, y;
		Ball(int X, int Y)
		{
			x = X;
			y = Y;
		}
		Reset(int X, int Y)
		{
			x = X;
			y = Y;
			vel = 0;
			initvel = 0;
			sidevel = 0;
		}
		void Draww()
		{
			if(sidevel > 0)
			{
				sidevel -= friction;
				if(sidevel < 0)
					sidevel = 0;
			}
			else if(sidevel < 0)
			{
				sidevel += friction;
				if(sidevel > 0)
					sidevel = 0;
			}
			x += sidevel;
			if(x < -50 || x > 1580)
			{
				Reset(400, 790);
				score = 0;
			}
			y -= vel;
			if(y < 790)
				vel -= gravity;
			else if(y >= 791)
			{
				score = 0;
				vel = (initvel)/1.5;
				initvel = vel;
				if(vel < 1)
					vel = 0;
				y = 790;
			}
			circle(x, y, 50);
			setfillstyle(SOLID_FILL, GREEN);
			floodfill(x - 48, y, GREEN);
			floodfill(x + 48, y, GREEN);
			floodfill(x, y - 48, GREEN);
			floodfill(x, y + 48, GREEN);
		}
};
Ball b(400, 790);

int main(int argc, char** argv)
{
	initwindow(1920, 1080, "Kick It", -3, -3, true, true);
	int page = 0;
	setcolor(YELLOW);
	settextstyle(8, 0, 6);
	setvisualpage(0);
	setactivepage(0);
	outtextxy(600, 200, "Kick It!");
	settextstyle(8, 0, 3);
	outtextxy(500, 400, "Click on the ball to kick it and");
	outtextxy(500, 450, "don't let it touch the ground!");
	outtextxy(500, 550, "Press any key to continue");
	outtextxy(1300, 600, "Atul Raj");
	outtextxy(1300, 650, "21JE0195");
	outtextxy(1300, 700, "IIT (ISM)");
	outtextxy(1300, 750, "(c) Copyright");
	settextstyle(0, 0, 4);
	getch();
	setcolor(GREEN);
	
	while(1)
	{
		setactivepage(page);
		setvisualpage(1 - page);
		cleardevice();
		
		char S[20], HI[20];
		sprintf(S, "%d", score);
		sprintf(HI, "%d", high);
		outtextxy(1470, 20, S);
		outtextxy(1380, 60, "HI ");
		outtextxy(1470, 60, HI);
		setfillstyle(SOLID_FILL, WHITE);
		floodfill(1, 1, GREEN);
		b.Draww();
		if(GetAsyncKeyState(VK_LBUTTON))
		{
			GetCursorPos(&pos);
			int X = pos.x, Y = pos.y;
			if((X - b.x)*(X - b.x) + (Y - b.y)*(Y - b.y) <= 3000)
			{
				high = max(high, ++score);
				int check = abs(X - b.x);
				if(check <= 5)
					sidevel = (rand() % 21) - 10;
				else if(check <= 30)
						sidevel = (b.x - X)/3;
				else
						sidevel = (b.x - X)/5;
				vel = (Y - b.y + 50)/4;
				initvel = vel;
			}
		}
		
		page = 1 - page;
		delay(1);
	}
	
	return 0;
}

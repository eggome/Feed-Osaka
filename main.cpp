#include<graphics.h>
#include<stdio.h>
#include<windows.h>
PIMAGE osaka1,osaka2,bread;
int cntBread=0;
bool OnBread(int x,int y)
{
	if(x>169&&x<274&&y>311&&y<439)	return 1;
	return 0;
}
bool InOsaka(int x,int y)
{
	if(x>528&&x<929&&y>154&&y<630)	return 1;
	return 0;
}
inline void Paint(bool dragging,int mousex=-1,int mousey=-1)
{
	cleardevice();
	setfillcolor(EGERGB(0xff,0xff,0xff));
	setcolor(EGERGB(0xff,0xff,0xff));
	bar(158,308,292,442);
	bar(150,308,158,442);bar(158,300,292,308);bar(292,308,300,442);bar(158,442,292,450);
	fillcircle(158,308,8);fillcircle(158,442,8);fillcircle(292,308,8);fillcircle(292,442,8);
	bar(368,128,1072,632);
	bar(360,128,368,632);bar(368,120,1072,308);bar(1072,128,1080,632);bar(368,632,1072,640);
	fillcircle(368,128,8);fillcircle(368,632,8);fillcircle(1072,128,8);fillcircle(1072,632,8);
	if(!dragging||!InOsaka(mousex,mousey))	putimage(382,127,osaka1);
	else	putimage(382,127,osaka2);
	setfont(-30,0,"Segoe UI Bold");
	setcolor(EGERGB(0,0,0));
	outtextxy(434,24,"Will She Eat the Bread: The Video Game");
	xyprintf(580,70,"%d bread eaten",cntBread);
	if(!dragging)	putimage_withalpha(nullptr,bread,175,320);
	else	putimage_withalpha(nullptr,bread,mousex-50,mousey-60);
}
int main()
{
	initgraph(1280,720,INIT_RENDERMANUAL);
	setcaption("Feed Osaka");
	setbkcolor(EGERGB(255,192,203));
	osaka1=newimage(1,1);osaka2=newimage(1,1);bread=newimage(1,1);
	getimage_pngfile(osaka1,"1.png");getimage_pngfile(osaka2,"2.png");getimage_pngfile(bread,"bread.png");
	for(bool lmbon=0,dragging=0;is_run();delay_fps(60))
	{
		int mousex,mousey;
		Paint(dragging,mousex,mousey);
		if(keystate(key_mouse_l))
		{
			mousepos(&mousex,&mousey);
			if(!lmbon&&OnBread(mousex,mousey))	dragging=1;
			lmbon=1;
		}
		else
		{
			if(InOsaka(mousex,mousey)&&dragging)	++cntBread;
			dragging=lmbon=0;
		}
	}
	return 0;
}

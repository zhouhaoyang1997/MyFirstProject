#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>
#include<conio.h>

#define height 28
#define width 60
#define n 400

void GameStart();//游戏开始 
void First_snack();//初始化的蛇 
int move();//蛇头的移动和数据的更新 
void move_snack();//蛇的其他部位移动 
void static_info();//静态数据 
void food_show();//食物的出现
int judge_head();//判断是否死亡 
int GameOver();//游戏结束 
void dynamic_info();//动态数据

int node;
int music;
int speed; //用于sleep()函数的参数 
int direction;
int score;
int p;

struct SNACK
{
	int x;
	int y;
	int life;
}snack[n];
struct FOOD
{
	int x;
	int y;
}food;

void gotoxy(int x,int y)
{
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}

void Game_frame()//框架； 
{
	int i;
	for(i = 1; i <= height; i++){//为什么竖是加1而横是加2； 
		gotoxy(0,i);
		printf("■");//因为这是中文状态下的； 
		gotoxy(width,i);
		printf("■");
	}
	for(i = 0; i <= width+1; i=i+2){
		gotoxy(i,0);
		printf("■");
		gotoxy(i,height+1);
		printf("■");
	}
}

void First_snack()//蛇的初始位置； 
{
	int i, j = 0;
	Game_frame();
	for(i = 0; i < node; i++){//node =4
		snack[i].x = 28-j;//初始化蛇的位置--x
		snack[i].y = 17;//初始化蛇的位置--y
		j = j-2;//方块占两个
		gotoxy(snack[i].x,snack[i].y);
		printf("■");//定位输出方块
	}
}

//蛇头移动和数据更新 
int move()
{
	int a,b ;
	static_info();
	int key_direction=3;//第一次3 
	while(!kbhit())//没按键进入 
	{
		loop://下次 
		gotoxy(food.x,food.y);printf("※");
		
		if(key_direction==0)
		key_direction=direction;//如果和上次移动方向相反 则继续执行上次命令 
		
		switch(key_direction)//头的移动； 
		{
			case 1 : move_snack();   snack[0].y=snack[0].y-1;gotoxy(snack[0].x,snack[0].y);printf("■");  break;//向上移 后边一个是蛇头 
			case 2 : move_snack();   snack[0].y=snack[0].y+1;gotoxy(snack[0].x,snack[0].y);printf("■");  break;//向下移
			case 3 : move_snack();   snack[0].x=snack[0].x-2;gotoxy(snack[0].x,snack[0].y);printf("■");  break;//向左移
			case 4 : move_snack();   snack[0].x=snack[0].x+2;gotoxy(snack[0].x,snack[0].y);printf("■");  break;//向右移
		}
	dynamic_info();
	judge_head();
	if(p == 0){
		return 0;//此函数结束执行 
	}
	Sleep(speed);//暂停的时间来控制速度 
	}
	a=getch();//getch的返回值 //用ch=getch();会等待你按下任意键之后，把该键字符所对应的ASCII码赋给ch,再执行下面的语句。
	b=getch();//getch的接收的符号。 
	switch(a)
	{
	case 224:switch(b)//更改方向
			 {//1---下；2代表上；3代表左；4代表右； 
				case 72:key_direction=1;if(direction==2)	key_direction=0;	break;
				case 75:key_direction=3;if(direction==4)	key_direction=0;	break;
				case 80:key_direction=2;if(direction==1)	key_direction=0;	break;
				case 77:key_direction=4;if(direction==3)	key_direction=0;	break;
			 }break;
	case 0:  switch(b)//功能选项
			 {
				case 59:speed-=20;break;
				case 60:speed+=20;break;
			 	case 61:music=music==1?0:1;break;
				case 62:system("color 0C");static_info();break;//红色
				case 63:system("color 0E");static_info();break;//黄色
				case 64:system("color 0A");static_info();break;//绿色
				case 65:system("color 0D");static_info();break;//紫色
				case 66:system("color 0F");static_info();break;//亮白色
				case 67:system("color 08");static_info();break;//灰色
			 }break;
	default: goto loop;
	}
	if(key_direction)
		direction=key_direction;// 实现按反向键时暂停；  这个功能我让去掉了 我打算写个忽视其相反方向的命令 direction是用来记录上一个方向命令 
////	else
//		goto loop;  被我注释掉了 并没用 
	goto loop;//表示返回到loop位置， 
}

//蛇的其他部位移动 
void move_snack()
{
	int i ;
	gotoxy(snack[node-1].x,snack[node-1].y); //清除蛇尾 node-1就是蛇尾 
	printf(" ");
	for(i=node-1;i>=1;i--)
	{
		snack[i]=snack[i-1];
		gotoxy(snack[i].x,snack[i].y); printf("◆");//重新打印出了蛇头的节点 
	}
}

int judge_head()
{
	int i=0;
	if(snack[0].x==0 || snack[0].x==width || snack[0].y==0 || snack[0].y==height+1){
		GameOver();//首先判断是不是撞墙了
		return p = 0;
	}	
	for(i=node-1;i>=1;i--)//判断是不是咬着自己了
	{
			if(snack[0].x==snack[i].x&&snack[0].y==snack[i].y){
				GameOver();
				return p = 0;
			}
	}
	if(snack[0].x==food.x && snack[0].y==food.y)//如果吃到食物,给尾巴加上一节
	{
		if(music)
			putchar(7);//响铃
		score+=100;
		node++;
		snack[node-1]=snack[node-2];
		gotoxy(snack[node-1].x,snack[node-1].y);printf("◆");
		food_show();
	}
}

 void food_show()//食物出现； 
{
	srand(time(NULL));
	/*这是两个函数！一个是srand函数！这是在调用rand（）这个函数之前使用的！rand（）是一个产生随机数的函数！
	而srand是一个设置随机数种子的函数！通常这两个函数是一起使用的！来完成产生随机数的功能！
	而time(NULL)这个函数的返回值是作为srand函数的参数的！意思是以现在的系统时间作为随机数的种子来产生随机数！
	至于NULL这个参数。只有设置成NULL才能获得系统的时间！*/	
	do
	{
		food.x = rand()%(width-3)+2;
	}while(food.x%2!=0); 
	food.y = rand()%(height-1)+1;

}
 
void static_info()//静态信息 
{
	gotoxy(width+4,2);printf("%c %c %c %c控制",24,25,26,27);
	gotoxy(width+4,3);printf("按任意键暂停");
	gotoxy(width+4,4);printf("F1加速,F2减速");
	gotoxy(width+4,5);printf("F3开关声音");
	gotoxy(width+4,7);printf("蛇速度：");
	gotoxy(width+4,8);printf("蛇长度：");
	gotoxy(width+4,9);printf("得分:");
	gotoxy(width+4,11);printf("蛇头位置:");
	gotoxy(width+4,13);printf("食物位置:");
	gotoxy(width+4,15);printf("声音:");
	gotoxy(width+4,16);SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|FOREGROUND_INTENSITY);printf("F4:■");//红色
	gotoxy(width+4,18);SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY);printf("F5:■");//黄色
	gotoxy(width+4,20);SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_INTENSITY);printf("F6:■");//绿色
	gotoxy(width+4,22);SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_INTENSITY);printf("F7:■");//紫色
	gotoxy(width+4,24);SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_INTENSITY);printf("F8:■");//亮白色
	gotoxy(width+4,26);SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED);printf("F9:■");//灰色
} 

void dynamic_info()//动态信息 
{
	gotoxy(width+13,7);printf("%4d",500-speed);
	gotoxy(width+13,8);printf("%4d",node);
	gotoxy(width+13,9);printf("%4d",score);
	gotoxy(width+13,13);printf("%2d,%2d",food.x,food.y);
	gotoxy(width+13,11);printf("%2d,%2d",snack[0].x,snack[0].y);
	gotoxy(width+9,15);music==1?printf("开"):printf("关");
}

void GameStart()                    //首界面
{
	Game_frame();
	gotoxy(25,10);printf("贪吃蛇游戏");
	gotoxy(22,17);system("pause");//就是刚开始的请按任意键继续。。。。 
}
int GameOver()
{
	system("cls");
	Game_frame();//因为前面清屏了。 
	gotoxy(25,10);printf("Game Over");
	gotoxy(25,12);printf("得分:%d",score);
	gotoxy(20,14);printf("重复游戏请按p键\n");
	return 0;
}
int main()
{
	char a;
	loop:
	p = 1;
	system("cls");
	system("mode con: cols=80 line=31"); //是设置你批处理运行时窗口大小的
	GameStart();
	system("cls");
	node = 4;
	music = 1;
	speed=280;
	direction = 3;
	score = 0;
	First_snack();
    food_show();
	move(); 
	a = getch();
	if(a == 'p'){
		goto loop;
	}

	return 0;
}

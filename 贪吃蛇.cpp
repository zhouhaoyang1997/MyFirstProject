#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>
#include<conio.h>

#define height 28
#define width 60
#define n 400

void GameStart();//��Ϸ��ʼ 
void First_snack();//��ʼ������ 
int move();//��ͷ���ƶ������ݵĸ��� 
void move_snack();//�ߵ�������λ�ƶ� 
void static_info();//��̬���� 
void food_show();//ʳ��ĳ���
int judge_head();//�ж��Ƿ����� 
int GameOver();//��Ϸ���� 
void dynamic_info();//��̬����

int node;
int music;
int speed; //����sleep()�����Ĳ��� 
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

void Game_frame()//��ܣ� 
{
	int i;
	for(i = 1; i <= height; i++){//Ϊʲô���Ǽ�1�����Ǽ�2�� 
		gotoxy(0,i);
		printf("��");//��Ϊ��������״̬�µģ� 
		gotoxy(width,i);
		printf("��");
	}
	for(i = 0; i <= width+1; i=i+2){
		gotoxy(i,0);
		printf("��");
		gotoxy(i,height+1);
		printf("��");
	}
}

void First_snack()//�ߵĳ�ʼλ�ã� 
{
	int i, j = 0;
	Game_frame();
	for(i = 0; i < node; i++){//node =4
		snack[i].x = 28-j;//��ʼ���ߵ�λ��--x
		snack[i].y = 17;//��ʼ���ߵ�λ��--y
		j = j-2;//����ռ����
		gotoxy(snack[i].x,snack[i].y);
		printf("��");//��λ�������
	}
}

//��ͷ�ƶ������ݸ��� 
int move()
{
	int a,b ;
	static_info();
	int key_direction=3;//��һ��3 
	while(!kbhit())//û�������� 
	{
		loop://�´� 
		gotoxy(food.x,food.y);printf("��");
		
		if(key_direction==0)
		key_direction=direction;//������ϴ��ƶ������෴ �����ִ���ϴ����� 
		
		switch(key_direction)//ͷ���ƶ��� 
		{
			case 1 : move_snack();   snack[0].y=snack[0].y-1;gotoxy(snack[0].x,snack[0].y);printf("��");  break;//������ ���һ������ͷ 
			case 2 : move_snack();   snack[0].y=snack[0].y+1;gotoxy(snack[0].x,snack[0].y);printf("��");  break;//������
			case 3 : move_snack();   snack[0].x=snack[0].x-2;gotoxy(snack[0].x,snack[0].y);printf("��");  break;//������
			case 4 : move_snack();   snack[0].x=snack[0].x+2;gotoxy(snack[0].x,snack[0].y);printf("��");  break;//������
		}
	dynamic_info();
	judge_head();
	if(p == 0){
		return 0;//�˺�������ִ�� 
	}
	Sleep(speed);//��ͣ��ʱ���������ٶ� 
	}
	a=getch();//getch�ķ���ֵ //��ch=getch();��ȴ��㰴�������֮�󣬰Ѹü��ַ�����Ӧ��ASCII�븳��ch,��ִ���������䡣
	b=getch();//getch�Ľ��յķ��š� 
	switch(a)
	{
	case 224:switch(b)//���ķ���
			 {//1---�£�2�����ϣ�3������4�����ң� 
				case 72:key_direction=1;if(direction==2)	key_direction=0;	break;
				case 75:key_direction=3;if(direction==4)	key_direction=0;	break;
				case 80:key_direction=2;if(direction==1)	key_direction=0;	break;
				case 77:key_direction=4;if(direction==3)	key_direction=0;	break;
			 }break;
	case 0:  switch(b)//����ѡ��
			 {
				case 59:speed-=20;break;
				case 60:speed+=20;break;
			 	case 61:music=music==1?0:1;break;
				case 62:system("color 0C");static_info();break;//��ɫ
				case 63:system("color 0E");static_info();break;//��ɫ
				case 64:system("color 0A");static_info();break;//��ɫ
				case 65:system("color 0D");static_info();break;//��ɫ
				case 66:system("color 0F");static_info();break;//����ɫ
				case 67:system("color 08");static_info();break;//��ɫ
			 }break;
	default: goto loop;
	}
	if(key_direction)
		direction=key_direction;// ʵ�ְ������ʱ��ͣ��  �����������ȥ���� �Ҵ���д���������෴��������� direction��������¼��һ���������� 
////	else
//		goto loop;  ����ע�͵��� ��û�� 
	goto loop;//��ʾ���ص�loopλ�ã� 
}

//�ߵ�������λ�ƶ� 
void move_snack()
{
	int i ;
	gotoxy(snack[node-1].x,snack[node-1].y); //�����β node-1������β 
	printf(" ");
	for(i=node-1;i>=1;i--)
	{
		snack[i]=snack[i-1];
		gotoxy(snack[i].x,snack[i].y); printf("��");//���´�ӡ������ͷ�Ľڵ� 
	}
}

int judge_head()
{
	int i=0;
	if(snack[0].x==0 || snack[0].x==width || snack[0].y==0 || snack[0].y==height+1){
		GameOver();//�����ж��ǲ���ײǽ��
		return p = 0;
	}	
	for(i=node-1;i>=1;i--)//�ж��ǲ���ҧ���Լ���
	{
			if(snack[0].x==snack[i].x&&snack[0].y==snack[i].y){
				GameOver();
				return p = 0;
			}
	}
	if(snack[0].x==food.x && snack[0].y==food.y)//����Ե�ʳ��,��β�ͼ���һ��
	{
		if(music)
			putchar(7);//����
		score+=100;
		node++;
		snack[node-1]=snack[node-2];
		gotoxy(snack[node-1].x,snack[node-1].y);printf("��");
		food_show();
	}
}

 void food_show()//ʳ����֣� 
{
	srand(time(NULL));
	/*��������������һ����srand�����������ڵ���rand�����������֮ǰʹ�õģ�rand������һ������������ĺ�����
	��srand��һ��������������ӵĺ�����ͨ��������������һ��ʹ�õģ�����ɲ���������Ĺ��ܣ�
	��time(NULL)��������ķ���ֵ����Ϊsrand�����Ĳ����ģ���˼�������ڵ�ϵͳʱ����Ϊ������������������������
	����NULL���������ֻ�����ó�NULL���ܻ��ϵͳ��ʱ�䣡*/	
	do
	{
		food.x = rand()%(width-3)+2;
	}while(food.x%2!=0); 
	food.y = rand()%(height-1)+1;

}
 
void static_info()//��̬��Ϣ 
{
	gotoxy(width+4,2);printf("%c %c %c %c����",24,25,26,27);
	gotoxy(width+4,3);printf("���������ͣ");
	gotoxy(width+4,4);printf("F1����,F2����");
	gotoxy(width+4,5);printf("F3��������");
	gotoxy(width+4,7);printf("���ٶȣ�");
	gotoxy(width+4,8);printf("�߳��ȣ�");
	gotoxy(width+4,9);printf("�÷�:");
	gotoxy(width+4,11);printf("��ͷλ��:");
	gotoxy(width+4,13);printf("ʳ��λ��:");
	gotoxy(width+4,15);printf("����:");
	gotoxy(width+4,16);SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|FOREGROUND_INTENSITY);printf("F4:��");//��ɫ
	gotoxy(width+4,18);SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY);printf("F5:��");//��ɫ
	gotoxy(width+4,20);SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_INTENSITY);printf("F6:��");//��ɫ
	gotoxy(width+4,22);SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_INTENSITY);printf("F7:��");//��ɫ
	gotoxy(width+4,24);SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_INTENSITY);printf("F8:��");//����ɫ
	gotoxy(width+4,26);SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED);printf("F9:��");//��ɫ
} 

void dynamic_info()//��̬��Ϣ 
{
	gotoxy(width+13,7);printf("%4d",500-speed);
	gotoxy(width+13,8);printf("%4d",node);
	gotoxy(width+13,9);printf("%4d",score);
	gotoxy(width+13,13);printf("%2d,%2d",food.x,food.y);
	gotoxy(width+13,11);printf("%2d,%2d",snack[0].x,snack[0].y);
	gotoxy(width+9,15);music==1?printf("��"):printf("��");
}

void GameStart()                    //�׽���
{
	Game_frame();
	gotoxy(25,10);printf("̰������Ϸ");
	gotoxy(22,17);system("pause");//���Ǹտ�ʼ���밴����������������� 
}
int GameOver()
{
	system("cls");
	Game_frame();//��Ϊǰ�������ˡ� 
	gotoxy(25,10);printf("Game Over");
	gotoxy(25,12);printf("�÷�:%d",score);
	gotoxy(20,14);printf("�ظ���Ϸ�밴p��\n");
	return 0;
}
int main()
{
	char a;
	loop:
	p = 1;
	system("cls");
	system("mode con: cols=80 line=31"); //������������������ʱ���ڴ�С��
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

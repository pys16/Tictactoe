//井字棋(tictactoe)我决定只让AI先手吧……
#include<iostream>
#include <windows.h>
#define DEPTH 5
void arraycopy33(int(*source)[3], int(*destiniation)[3])
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			destiniation[i][j] = source[i][j];
}
void gotoxy(int x, int y) {
	COORD cursorPosition;
	cursorPosition.X = x;
	cursorPosition.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}//光标定位
using namespace std;
int chessboard[3][3] = { 0 };//棋盘 0为空，1为玩家1，1为玩家2
int AItmpboard[3][3] = { 0 };
const char ch[12][4] = { "┌","┬","┐","├","┼","┤","└","┴","┘","○","×","●" };  //可供选用的字符，输出棋盘或者棋子用 ch[n]调用第n个字符
int place = 0;//AI下子的位置
int main()
{
	void draw();
	int IfEnd(int(*ChessBoard)[3]);
	int AIPlay(int(*PresentSituation)[3]);
	int huihe = 0;
	int x = 0, y = 0;
	while (IfEnd(chessboard)==0)
	{
		system("cls");
		draw();
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				AItmpboard[i][j] = chessboard[i][j];
		if (huihe % 2 == 0)AIPlay(AItmpboard);
		else
		{
			cout << "请落子，xy坐标,屏幕横向为x，纵向为y" << endl;
			cin >> x >> y;
			chessboard[y-1][x-1] = 2;
		}
		huihe++;
	}
	system("cls");
	draw();
	if (IfEnd(chessboard) == 1)cout << "AI赢了" << endl;
	if (IfEnd(chessboard) == 2)cout << "你赢了" << endl;
	if (IfEnd(chessboard) == 3)cout << "平局了" << endl;

	return 0;
}
//绘制当前棋局的函数
void draw()
{
	//画上九个黑点
	for (int i = 0; i < 3; i++)
	{
		cout << ch[11] << ch[11] << ch[11] << endl;
	}
	//在合适位置画上合适的东西
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (chessboard[i][j] == 1)
			{
				gotoxy(2*j, i);
				cout << ch[9];
			}
			if (chessboard[i][j] == 2)
			{
				gotoxy(2*j, i);
				cout << ch[10];
			}
		}
	}
	gotoxy(0, 3);
}
//判断是否结束并返回胜者的函数
int IfEnd(int(*ChessBoard)[3])
{
	for (int i = 0; i < 3; i++)
	{
		if (ChessBoard[i][0] == 1 && ChessBoard[i][1] == 1 && ChessBoard[i][2] == 1)return 1;
		if (ChessBoard[i][0] == 2 && ChessBoard[i][1] == 2 && ChessBoard[i][2] == 2)return 2;
	}
	for (int j = 0; j < 3; j++)
	{
		if (ChessBoard[0][j] == 1 && ChessBoard[1][j] == 1 && ChessBoard[2][j] == 1)return 1;
		if (ChessBoard[0][j] == 2 && ChessBoard[1][j] == 2 && ChessBoard[2][j] == 2)return 2;
	}
	if (ChessBoard[0][0] == 1 && ChessBoard[1][1] == 1 && ChessBoard[2][2] == 1)return 1;
	if (ChessBoard[0][0] == 2 && ChessBoard[1][1] == 2 && ChessBoard[2][2] == 2)return 2;
	if (ChessBoard[2][0] == 1 && ChessBoard[1][1] == 1 && ChessBoard[0][2] == 1)return 1;
	if (ChessBoard[2][0] == 2 && ChessBoard[1][1] == 2 && ChessBoard[0][2] == 2)return 2;
	bool Full = 1;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (ChessBoard[i][j] == 0)Full = 0;
	if (Full)return 3;
	return 0;
}
//对局势打分的函数
int evaluation(int (*AItmpBoard)[3])
{
	if (IfEnd(AItmpBoard) == 1)return 100000;//AI为1,这说明AI直接赢了，返回一个超大的数字
	if (IfEnd(AItmpBoard) == 2)return -100000;
	int result = 0;
	//横向成活2，+-1000分，死二不计分
	for (int i = 0; i < 3; i++)
	{
		for (int k = 0; k < 2; k++)
		{
			if (AItmpBoard[i][k] == 1 && AItmpBoard[i][k] == AItmpBoard[i][k + 1]&&AItmpBoard[i][(k+2)%3]!=2)result += 1000;
			if (AItmpBoard[i][k] == 2 && AItmpBoard[i][k] == AItmpBoard[i][k + 1]&&AItmpBoard[i][(k+2)%3]!=1)result -= 1000;
		}
	}
	//纵向成2，+-1000分
	for (int j = 0; j < 3; j++)
	{
		for (int k = 0; k < 2; k++)
		{
			if (AItmpBoard[k][j] == 1 && AItmpBoard[k][j] == AItmpBoard[k+1][j] && AItmpBoard[(k + 2) % 3][j] != 2)result += 1000;
			if (AItmpBoard[k][j] == 2 && AItmpBoard[k][j] == AItmpBoard[k+1][j] && AItmpBoard[(k + 2) % 3][j] != 1)result -= 1000;
		}
	}
	//斜向成2，+-1000分
	for (int i = 0; i < 2; i++)
	{
		if (AItmpBoard[i][i] == 1 && AItmpBoard[i][i] == AItmpBoard[i + 1][i + 1] && AItmpBoard[(i + 2) % 3][(i + 2) % 3] != 2)result += 1000;
		if (AItmpBoard[i][i] == 2 && AItmpBoard[i][i] == AItmpBoard[i + 1][i + 1] && AItmpBoard[(i + 2) % 3][(i + 2) % 3] != 1)result -= 1000;
	}
	for (int i = 0; i < 2; i++)
	{
		if (AItmpBoard[i][2 - i] == 1 && AItmpBoard[i + 1][1 - i] == AItmpBoard[i][2 - i] && AItmpBoard[(i + 2) % 3][3 - i] != 2)result += 1000;
		if (AItmpBoard[i][2 - i] == 2 && AItmpBoard[i + 1][1 - i] == AItmpBoard[i][2 - i] && AItmpBoard[(i + 2) % 3][3 - i] != 2)result -= 1000;
	}
	//每个子再给10分（我觉得这似乎没什么用）
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (AItmpBoard[i][j] == 1)result += 10;
			if (AItmpBoard[i][j] == 2)result -= 10;
		}
	}
	return result;
}
//AI主体,ABcut函数,从wiki上面扒下来的
int ABCut(int (*PresentSituation)[3],int depth,int alpha,int beta,bool IsAI,bool IsInitial)//IsInitial判断是否为本源（即需要做出选择，亦即需要改变place值）
{
	int temparray[3][3];
	arraycopy33(PresentSituation, temparray);
	if (depth == 0||IfEnd(PresentSituation)==3)
		return evaluation(PresentSituation);
	if (IsAI)
	{
		int v = alpha;
		int tmp;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (PresentSituation[i][j] == 0)//如果尚未落子
				{
					temparray[i][j] = 1;//AI就在这里落子试一下
					tmp = ABCut(temparray,depth-1,alpha,beta,FALSE,FALSE);
					if (v < tmp)
					{
						v = tmp;
						if(IsInitial)
						place = 3 * i + j;
					}
					alpha = max(alpha, v);
					if (beta <= alpha)break;//beta裁剪
					temparray[i][j] = 0;//再复原
				}
			}
		}
		return v;
	}
	else
	{
		int v = beta;
		int tmp;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (PresentSituation[i][j] == 0)//如果尚未落子
				{
					temparray[i][j] = 2;//人就在这里落子
					tmp = ABCut(temparray,depth-1,alpha,beta,TRUE,FALSE);
					if (v > tmp)
					{
						v = tmp;
						if(IsInitial)
						place = 3 * i + j;
					}
					beta = min(beta, v);
					if (beta <= alpha)break;//alpha裁剪
					temparray[i][j] = 0;//复原
				}
			}
		}
		return v;
	}
}
//下棋咯……
int AIPlay(int (*PresentSituation)[3])
{
	int tmp[3][3];
	arraycopy33(PresentSituation, tmp);
	ABCut(PresentSituation, DEPTH, -200000, 200000, TRUE,TRUE);
	chessboard[place / 3][place % 3] = 1;
	return 0;
}

/*
*程序名称：黑白棋大作业REVERSI
*制作人：张艺川 王心茹
*时间：2015-12
*/
#include<iostream>
#include<cstring>
#include<stdlib.h>//清屏操作system("cls")
#include<fstream>
#include<conio.h>
using namespace std;

int board[9][9];//存储棋盘状态:-1空，0白，1黑，2可下
bool scan[9][9];//在able_to_put函数中检查是否被检索过
int undoboard[9][9];//记录上一步，用于悔棋
char a, b, c;//全局变量，记录用户的菜单选择
int evaluation[9][9] = { 0,0,0,0,0,0,0,0,0,0, 200, -60, 10, 10, 10, 10, -60, 200 , 0, -60, -80, 5, 5, 5, 5, -80, -60 ,  0, 10, 5, 1, 1, 1, 1, 5, 10 ,  0, 10, 5, 1, 1, 1, 1, 5, 10 ,  0, 10, 5, 1, 1, 1, 1, 5, 10 ,  0, 10, 5, 1, 1, 1, 1, 5, 10 ,  0, -60, -80, 5, 5, 5, 5, -80, -60 ,0,200,-60,10,10, 10, 10, -60, 200};//估值表

void cin_board(int chess);//用户下子，并得到用户下子之后的棋盘状态
void reverse(int x, int y, int chess);//得到翻转后的棋盘状态
void print_board();//打印棋盘
void able_to_put(int x, int y, int chess);//判断哪个位置可以落子
int count(int n);//计数器，计算棋盘board中某个数字的个数
void save();//存档
void load();//读档
void startMenu();//显示菜单
void AI(int chess);
void print_help();//开始菜单中进入到游戏帮助
int calScore(int chess);//计算节点自身落子位置在估值表中的得分

void cin_board(int chess) //用户下子，并得到用户下子之后的棋盘状态
{
	int cnt2 = count(2);
	if (cnt2 == 0)    return;
	if (chess==1)    cout << "黑方落子：";
	else    cout << "白方落子：";
	int x, y;
	cin >> x >> y;
	while (board[x][y] != 2)
	{
		cout << "错啦！只有“·”处才可落子哦" << endl;
		cout << "输入你要落子的位置：";
		cin >> x >> y;
	}
	board[x][y] = chess;
	int i, j;
	for (i = 1; i <= 8; i++)
		for (j = 1; j <= 8; j++)
		{
			if (board[i][j] == 2)    board[i][j] = -1;
		}
	reverse(x, y, chess);
}

void reverse(int x, int y, int chess)//得到翻转后的棋盘状态
{
	int i, j;
	int flag = 0;//记录中间对方棋子的数量
	//向左检索
	if (y >= 2)
	{
		for (i = y - 1; i >= 1; i--)
		{
			if (board[x][i] == -1)    break;
			else if (board[x][i] == 1 - chess)    flag++;
			else if (board[x][i] == chess)
			{
				if (flag == 0)    break;
				else
				{
					for (j = i + 1; j <= y - 1; j++)    board[x][j] = chess;
					break;
				}
			}
		}
	}
	//向右检索
	flag = 0;
	if (y <= 7)
	{
		for (i = y + 1; i <= 8; i++)
		{
			if (board[x][i] == -1)    break;
			else if (board[x][i] == 1 - chess)    flag++;
			else if (board[x][i] == chess)
			{
				if (flag == 0)    break;
				else
				{
					for (j = i - 1; j >= y + 1; j--)    board[x][j] = chess;
					break;
				}
			}
		}
	}
	//向上检索
	flag = 0;
	if (x >= 2)
	{
		for (i = x - 1; i >= 1; i--)
		{
			if (board[i][y] == -1)    break;
			else if (board[i][y] == 1 - chess)    flag++;
			else if (board[i][y] == chess)
			{
				if (flag == 0)    break;
				else
				{
					for (j = i + 1; j <= x - 1; j++)    board[j][y] = chess;
					break;
				}
			}
		}
	}
	//向下检索
	flag = 0;
	if (x <= 7)
	{
		for (i = x + 1; i <= 8; i++)
		{
			if (board[i][y] == -1)    break;
			else if (board[i][y] == 1 - chess)    flag++;
			else if (board[i][y] == chess)
			{
				if (flag == 0)    break;
				else
				{
					for (j = i - 1; j >= x + 1; j--)    board[j][y] = chess;
					break;
				}
			}
		}
	}
	//向左上检索
	flag = 0;
	int diff = x - y;
	if (x >= 2 && y >= 2)
	{
		for (i = x - 1; i >= 1; i--)
		{
			if (i <= 0 || i >= 9 || i - diff <= 0 || i - diff >= 9)    break;
			if (board[i][i - diff] == -1)    break;
			else if (board[i][i - diff] == 1 - chess)    flag++;
			else if (board[i][i - diff] == chess)
			{
				if (flag == 0)    break;
				else
				{
					for (j = i + 1; j <= x - 1; j++)    board[j][j - diff] = chess;
					break;
				}
			}
		}
	}
	//向右下检索
	flag = 0;
	if (x <= 7 && y <= 7)
	{
		for (i = x + 1; i <= 8; i++)
		{
			if (i <= 0 || i >= 9 || i - diff <= 0 || i - diff >= 9)    break;
			if (board[i][i - diff] == -1)    break;
			else if (board[i][i - diff] == 1 - chess)    flag++;
			else if (board[i][i - diff] == chess)
			{
				if (flag == 0)    break;
				else
				{
					for (j = i - 1; j >= x + 1; j--)    board[j][j - diff] = chess;
					break;
				}
			}
		}
	}
	//向右上检索
	flag = 0;
	int sum = x + y;
	if (x >= 2 && y <= 7)
	{
		for (i = x - 1; i >= 1; i--)
		{
			if (i <= 0 || i >= 9 || sum - i <= 0 || sum - i >= 9)    break;
			if (board[i][sum - i] == -1)    break;
			else if (board[i][sum - i] == 1 - chess)    flag++;
			else if (board[i][sum - i] == chess)
			{
				if (flag == 0)    break;
				else
				{
					for (j = i + 1; j <= x - 1; j++)    board[j][sum - j] = chess;
					break;
				}
			}
		}
	}
	//向左下检索
	flag = 0;
	if (y >= 2 && x <= 7)
	{
		for (i = x + 1; i <= 8; i++)
		{
			if (i <= 0 || i >= 9 || sum - i <= 0 || sum - i >= 9)    break;
			if (board[i][sum - i] == -1)    break;
			else if (board[i][sum - i] == 1 - chess)    flag++;
			else if (board[i][sum - i] == chess)
			{
				if (flag == 0)    break;
				else
				{
					for (j = i - 1; j >= x + 1; j--)    board[j][sum - j] = chess;
					break;
				}
			}
		}
	}
}

void print_board()//打印棋盘
{
	system("cls");
	int i, j;
	cout << "    1   2   3   4   5   6   7   8" << endl;
	cout << " ┌─┬─┬─┬─┬─┬─┬─┬─┐" << endl;
	for (i = 1; i <= 8; i++)
	{
		cout << i << "│";
		for (j = 1; j <= 8; j++)
		{
			switch (board[i][j])
			{
			case -1:cout << "  │"; break;
			case 0:cout << "○│"; break;
			case 1:cout << "●│"; break;
			case 2:cout << "·│"; break;
			}
		}
		if (i == 1)    cout << "    ☆选项卡（请输入序号）：";
		else if (i == 2)    cout << "      2、暂停游戏";
		else if (i == 3)    cout << "      4、退出游戏";
		cout << endl;
		if (i == 8)    cout << " └─┴─┴─┴─┴─┴─┴─┴─┘" << endl;
		else if (i == 1)    cout << " ├─┼─┼─┼─┼─┼─┼─┼─┤      1、悔棋" << endl;
		else if (i == 2)    cout << " ├─┼─┼─┼─┼─┼─┼─┼─┤      3、存档" << endl;
		else    cout << " ├─┼─┼─┼─┼─┼─┼─┼─┤" << endl;
	}
	cout << endl;
	int cnt1 = count(1), cnt0 = count(0);
	cout << "            黑：白=" << cnt1 << "：" << cnt0 << endl;
	cout << "************************************" << endl;
	cout << endl;
	char ch;
	ch = _getch();
	if (ch == '1')
	{
		memcpy(board, undoboard, sizeof(board));
		print_board();
	}
	if (ch == '2')
	{
		cout << "游戏暂停，等你回来~" << endl;
		cout << endl;
		system("pause");
	}
	if (ch == '3')    save();
	if (ch == '4')    exit(1);
}

void able_to_put(int x, int y, int chess)//判断哪个位置可以落子
{
	//轮到一方下棋时，必须把棋下在与对方棋子相邻的空位上，要求所下的棋子和原有的己方棋子夹住对方的至少一个棋子（横竖斜夹均可）
	if (scan[x][y] || x <= 0 || x >= 9 || y <= 0 || y >= 9)    return;//已被查找过或越界，则退出
	int i;
	if (board[x][y] == -1)
	{
		//八个方向查找 
		if (!scan[x][y] && board[x - 1][y] == 1 - chess&&x >= 3)//上
		{
			for (i = x - 2; i >= 1; i--)
			{
				if (board[i][y] == chess)
				{
					board[x][y] = 2;
					scan[x][y] = true;
					break;
				}
				else if (board[i][y] == -1 || board[i][y] == 2)    break;
			}
		}
		if (!scan[x][y] && board[x + 1][y] == 1 - chess&&x <= 6)//下
		{
			for (i = x + 2; i <= 8; i++)
			{
				if (board[i][y] == chess)
				{
					board[x][y] = 2;
					scan[x][y] = true;
					break;
				}
				else if (board[i][y] == -1 || board[i][y] == 2)    break;
			}
		}
		if (!scan[x][y] && board[x][y - 1] == 1 - chess&&y >= 3)//左
		{
			for (i = y - 2; i >= 1; i--)
			{
				if (board[x][i] == chess)
				{
					board[x][y] = 2;
					scan[x][y] = true;
					break;
				}
				else if (board[x][i] == -1 || board[x][i] == 2)    break;
			}
		}
		if (!scan[x][y] && board[x][y + 1] == 1 - chess&&y <= 6)//右
		{
			for (i = y + 2; i <= 8; i++)
			{
				if (board[x][i] == chess)
				{
					board[x][y] = 2;
					scan[x][y] = true;
					break;
				}
				else if (board[x][i] == -1 || board[x][i] == 2)    break;
			}
		}
		int diff = x - y;
		if (!scan[x][y] && board[x - 1][y - 1] == 1 - chess&&x >= 3 && y >= 3)//左上
		{
			for (i = x - 2; i >= 1; i--)
			{
				if (i <= 0 || i >= 9 || i - diff <= 0 || i - diff >= 9)    break;
				if (board[i][i - diff] == chess)
				{
					board[x][y] = 2;
					scan[x][y] = true;
					break;
				}
				else if (board[i][i - diff] == -1 || board[i][i - diff] == 2)    break;
			}
		}
		if (!scan[x][y] && board[x + 1][y + 1] == 1 - chess&&x <= 6 && y <= 6)//右下
		{
			for (i = x + 2; i <= 8; i++)
			{
				if (i <= 0 || i >= 9 || i - diff <= 0 || i - diff >= 9)    break;
				if (board[i][i - diff] == chess)
				{
					board[x][y] = 2;
					scan[x][y] = true;
					break;
				}
				else if (board[i][i - diff] == -1 || board[i][i - diff] == 2)    break;
			}
		}
		int sum = x + y;
		if (!scan[x][y] && board[x - 1][y + 1] == 1 - chess&&x >= 3 && y <= 6)//右上
		{
			for (i = x - 2; i >= 1; i--)
			{
				if (i <= 0 || i >= 9 || sum - i <= 0 || sum - i >= 9)    break;
				if (board[i][sum - i] == chess)
				{
					board[x][y] = 2;
					scan[x][y] = true;
					break;
				}
				else if (board[i][sum - i] == -1 || board[i][sum - i] == 2)    break;
			}
		}
		if (!scan[x][y] && board[x + 1][y - 1] == 1 - chess&&y >= 3 && x <= 6)//左下
		{
			for (i = x + 2; i <= 8; i++)
			{
				if (i <= 0 || i >= 9 || sum - i <= 0 || sum - i >= 9)    break;
				if (board[i][sum - i] == chess)
				{
					board[x][y] = 2;
					scan[x][y] = true;
					break;
				}
				else if (board[i][sum - i] == -1 || board[i][sum - i] == 2)    break;
			}
		}
	}
	scan[x][y] = true;
	able_to_put(x + 1, y, chess);
	able_to_put(x, y + 1, chess);
}

int count(int n)//计数器，计算棋盘board中某个数字的个数
{
	int cnt = 0, i, j;
	for (i = 1; i <= 8; i++)
		for (j = 1; j <= 8; j++)
		{
			if (board[i][j] == n)    cnt++;
		}
	return cnt;
}

void save()//存档
{
	ofstream outfile("data.txt", ios::out);
	int i, j;
	for (i = 1; i <= 8; i++)
		for (j = 1; j <= 8; j++)    outfile << board[i][j] << " ";
	outfile << b << " " << c;
	outfile.close();
}

void load()//读档
{
	ifstream infile("data.txt", ios::in);
	int i, j;
	for (i = 1; i <= 8; i++)
		for (j = 1; j <= 8; j++)    infile >> board[i][j];
	infile >> b >> c;
	infile.close();
}

void startMenu()
{
	system("cls");
	cout << endl;
	cout << "                开始菜单" << endl;
	cout << "  ************************************" << endl;
	cout << endl;
	cout << "         请输入选项前的序号……" << endl;
	cout << endl;
	cout << "             1、新开局" << endl;
	cout << "             2、继续游戏" << endl;
	cout << "             3、帮助" << endl;
	cout << "             4、退出" << endl;
	a = _getch();
	switch (a)
	{
	case '1':
		memset(board, -1, sizeof(board));
		board[4][4] = 0, board[5][5] = 0;
		board[4][5] = 1, board[5][4] = 1;
		memset(undoboard, -1, sizeof(undoboard));
		undoboard[4][4] = 0, undoboard[5][5] = 0;
		undoboard[4][5] = 1, undoboard[5][4] = 1;
		system("cls");
		cout << "对手选择" << endl;
		cout << "1 人机对战" << endl;
		cout << "2 玩家对战" << endl;
		b = _getch();
		if (b == '1')
		{
			system("cls");
			cout << "选择您的棋子颜色" << endl;
			cout << "1 黑" << endl << "2 白" << endl;
			c = _getch();
			if (c == '1')
			{
				board[3][4] = 2, board[4][3] = 2, board[5][6] = 2, board[6][5] = 2;
				undoboard[3][4] = 2, undoboard[4][3] = 2, undoboard[5][6] = 2, undoboard[6][5] = 2;
			}
		}
		else if (b == '2')
		{
			system("cls");
			cout << "友情提示：玩家对战模式暂时无悔棋和存档功能:)" << endl;
			system("pause");
		}
		break;
	case '2':load(); break;
	case'3':print_help(); break;
	case '4':exit(1); break;
	}
}

void AI(int chess)//应用最大最小算法、α-β枝剪
{
	int tempboard1[9][9] = {}, tempboard2[9][9] = {}, tempboard3[9][9] = {};
	int score1, score2, score3, score3max = INT_MIN, score2max = INT_MIN, score1max = INT_MIN, AIputx, AIputy;
	memset(scan, false, sizeof(scan));
	able_to_put(1, 1, chess);
	int cnt2 = count(2), i, j;
	bool flag = false;
	if (cnt2 == 0)    return;//无可下的格子，pass
	for (int m = 1; m < 9; m++)
	{
		for (int n = 1; n < 9; n++)
		{
			tempboard1[m][n] = board[m][n];//储存当前棋盘状态,原棋盘用于第一步搜索
		}
	}
	for (i = 1; i <= 8; i++)
	{
		for (j = 1; j <= 8; j++)
		{
			if (board[i][j] == 2)//可以下
			{
				if ((i == 1 && j == 1) || (i == 1 && j == 8) || (i == 8 && j == 1) || (i == 8 && j == 8))
				{
					AIputx = i;
					AIputy = j;
					flag = true;
					break;
				}
				board[i][j] = chess;
				reverse(i, j, chess);
				for (int m = 1; m <= 8; m++)
				{
					for (int n = 1; n <= 8; n++)
					{
						if (board[m][n] == 2)    board[m][n] = -1;//清空合理落子点
					}
				}
				score1 = calScore(chess);
				memset(scan, false, sizeof(scan));
				able_to_put(1, 1, 1 - chess);//算玩家可下的地方
				memcpy(tempboard2, board, sizeof(tempboard2));//棋盘赋给第二个临时数组，原数组用于第二次搜索
				for (int m = 1; m <= 8; m++)
				{
					for (int n = 1; n <= 8; n++)
					{
						if (board[m][n] == 2)
						{
							board[m][n] = 1 - chess;//模拟玩家下棋
							reverse(m, n, 1 - chess);
							for (int l = 1; l < 9; l++)
							{
								for (int k = 1; k < 9; k++)
								{
									if (board[l][k] == 2) board[l][k] = -1;//清空合理落子点
								}
							}
							score2 = calScore(1 - chess);
							memset(scan, false, sizeof(scan));
							able_to_put(1, 1, chess);//判断AI可下的地方
							memcpy(tempboard3, board, sizeof(tempboard3));//棋盘赋给第三个临时数组，原数组用于第三次搜索
							for (int l = 1; l < 9; l++)
							{
								for (int k = 1; k < 9; k++)
								{
									if (board[l][k] == 2)
									{
										board[l][k] = chess;
										reverse(l, k, chess);
										for (int p = 1; p < 9; p++)
										{
											for (int q = 1; q < 9; q++)
											{
												if (board[p][q] == 2) board[p][q] = -1;//清空合理落子点
											}
										}
										score3 = calScore(chess);
										if (score3 > score3max) score3max = score3;
										memcpy(board, tempboard3, sizeof(board));//赋回
									}
								}
							}
							score2 -= score3max;
							if (score2 > score2max) score2max = score2;
							memcpy(board, tempboard2, sizeof(board));//赋回
						}
					}
				}
				score1 -= score2max;
				if (score1 > score1max)
				{
					score1max = score1;
					AIputx = i;
					AIputy = j;
				}
				memcpy(board, tempboard1, sizeof(board));
			}
		}
		if (flag)    break;
	}
	board[AIputx][AIputy] = chess;
	for (int p = 1; p < 9; p++)
	{
		for (int q = 1; q < 9; q++)
		{
			if (board[p][q] == 2) board[p][q] = -1;
		}
	}
	reverse(AIputx, AIputy, chess);
}

void print_help()
{
	system("cls");
	cout << "黑白棋，又叫反棋（Reversi）、奥赛罗棋（Othello）、苹果棋或翻转棋。" << endl;
	cout << "黑白棋在西方和日本很流行。游戏通过相互翻转对方的棋子，最后以棋盘上谁的棋子多来判断胜负。"<< endl;
	cout << "棋盘为8x8方格，共使用64个棋子，每个棋子分正反两面，分别是黑色和白色。" << endl;
	cout << "在棋局开始前，先把两个黑棋和两个白棋交叉放在棋盘中央，黑方先下，然后双方交替着子，当双方都无棋可下，或者64个方格全部占满后，棋局结束，子多的一方为胜方。" << endl;
	cout << "轮到一方下棋时，必须把棋下在与对方棋子相邻的空位上，要求所下的棋子和原有的已方棋子夹住对方的至少一个棋子(横竖斜夹均可)，然后把被夹住的子变成己方的颜色(也叫吃子)。" << endl;
	cout << "下棋过程中，任何棋子既不会从棋盘上拿走，也不会从一个格子移到另一个格子。" << endl;
	cout << "在轮到一方下棋时，如果该方无子可吃，就必须停一步，让对方继续下棋，这种情况叫pass；而当一方有子可吃时，即使像pass也不能pass。"<<endl;
	cout << endl;
	cout << "按任意键返回菜单……" << endl;
	system("pause");
	startMenu();
}

int calScore(int chess)
{
	int i, j,score0=0;
	for (i = 1; i <= 8; i++)
		for (j = 1; j <= 8; j++)
		{
			if (board[i][j] == chess)    score0 += evaluation[i][j];
			else if (board[i][j] == 1 - chess)    score0 -= evaluation[i][j];
		}
	return score0;
}

int main()
{
	startMenu();
	if (b == '1'&&c == '1')
	{
		if (count(2) != 0)//用户先下
		{
			while (1)
			{
				print_board();
				memcpy(undoboard, board, sizeof(undoboard));
				cin_board(1);
				if ((count(1) + count(0) == 64) || count(1) == 0 || count(0) == 0)    break;
				print_board();
				AI(0);
				if ((count(1) + count(0) == 64) || count(1) == 0 || count(0) == 0)    break;
				memset(scan, false, sizeof(scan));
				able_to_put(1, 1, 1);
			}
		}
		else//机器先下
		{
			while (1)
			{
				print_board();
				AI(0);
				if ((count(1) + count(0) == 64) || count(1) == 0 || count(0) == 0)    break;
				memset(scan, false, sizeof(scan));
				able_to_put(1, 1, 1);
				print_board();
				memcpy(undoboard, board, sizeof(undoboard));
				cin_board(1);
				if ((count(1) + count(0) == 64) || count(1) == 0 || count(0) == 0)    break;
			}
		}
	}
	else if (b == '1'&&c == '2')
	{
		if (count(2) == 0)//机器先下
		{
			while (1)
			{
				print_board();
				AI(1);
				if ((count(1) + count(0) == 64) || count(1) == 0 || count(0) == 0)    break;
				memset(scan, false, sizeof(scan));
				able_to_put(1, 1, 0);
				print_board();
				memcpy(undoboard, board, sizeof(undoboard));
				cin_board(0);
				if ((count(1) + count(0) == 64) || count(1) == 0 || count(0) == 0)    break;
			}
		}
		else
		{
			while (1)
			{
				print_board();
				memcpy(undoboard, board, sizeof(undoboard));
				cin_board(0);
				if ((count(1) + count(0) == 64) || count(1) == 0 || count(0) == 0)    break;
				print_board();
				AI(1);
				if ((count(1) + count(0) == 64) || count(1) == 0 || count(0) == 0)    break;
				memset(scan, false, sizeof(scan));
				able_to_put(1, 1, 0);		
			}
		}
	}
	else if (b == '2')//玩家对战
	{
		board[3][4] = 2, board[4][3] = 2, board[5][6] = 2, board[6][5] = 2;
		undoboard[3][4] = 2, undoboard[4][3] = 2, undoboard[5][6] = 2, undoboard[6][5] = 2;
		while (1)
		{
			print_board();
			memcpy(undoboard, board, sizeof(undoboard));
			cin_board(1);
			if ((count(1) + count(0) == 64) || count(1) == 0 || count(0) == 0)    break;
			memset(scan, false, sizeof(scan));
			able_to_put(1, 1, 0);
			print_board();
			memcpy(undoboard, board, sizeof(undoboard));
			cin_board(0);
			if ((count(1) + count(0) == 64) || count(1) == 0 || count(0) == 0)    break;
			memset(scan, false, sizeof(scan));
			able_to_put(1, 1, 1);
		}
	}
	print_board();
	cout << endl;
	if (count(1) == count(0))    cout << "               平局" << endl;
	else if (count(1) > count(0))    cout << "              黑方胜" << endl;
	else    cout << "              白方胜" << endl;
	cout << endl;
	system("pause");
	return 0;
}


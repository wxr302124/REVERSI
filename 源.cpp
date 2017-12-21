
/*
*�������ƣ��ڰ������ҵREVERSI
*�����ˣ����մ� ������
*ʱ�䣺2015-12
*/
#include<iostream>
#include<cstring>
#include<stdlib.h>//��������system("cls")
#include<fstream>
#include<conio.h>
using namespace std;

int board[9][9];//�洢����״̬:-1�գ�0�ף�1�ڣ�2����
bool scan[9][9];//��able_to_put�����м���Ƿ񱻼�����
int undoboard[9][9];//��¼��һ�������ڻ���
char a, b, c;//ȫ�ֱ�������¼�û��Ĳ˵�ѡ��
int evaluation[9][9] = { 0,0,0,0,0,0,0,0,0,0, 200, -60, 10, 10, 10, 10, -60, 200 , 0, -60, -80, 5, 5, 5, 5, -80, -60 ,  0, 10, 5, 1, 1, 1, 1, 5, 10 ,  0, 10, 5, 1, 1, 1, 1, 5, 10 ,  0, 10, 5, 1, 1, 1, 1, 5, 10 ,  0, 10, 5, 1, 1, 1, 1, 5, 10 ,  0, -60, -80, 5, 5, 5, 5, -80, -60 ,0,200,-60,10,10, 10, 10, -60, 200};//��ֵ��

void cin_board(int chess);//�û����ӣ����õ��û�����֮�������״̬
void reverse(int x, int y, int chess);//�õ���ת�������״̬
void print_board();//��ӡ����
void able_to_put(int x, int y, int chess);//�ж��ĸ�λ�ÿ�������
int count(int n);//����������������board��ĳ�����ֵĸ���
void save();//�浵
void load();//����
void startMenu();//��ʾ�˵�
void AI(int chess);
void print_help();//��ʼ�˵��н��뵽��Ϸ����
int calScore(int chess);//����ڵ���������λ���ڹ�ֵ���еĵ÷�

void cin_board(int chess) //�û����ӣ����õ��û�����֮�������״̬
{
	int cnt2 = count(2);
	if (cnt2 == 0)    return;
	if (chess==1)    cout << "�ڷ����ӣ�";
	else    cout << "�׷����ӣ�";
	int x, y;
	cin >> x >> y;
	while (board[x][y] != 2)
	{
		cout << "������ֻ�С��������ſ�����Ŷ" << endl;
		cout << "������Ҫ���ӵ�λ�ã�";
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

void reverse(int x, int y, int chess)//�õ���ת�������״̬
{
	int i, j;
	int flag = 0;//��¼�м�Է����ӵ�����
	//�������
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
	//���Ҽ���
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
	//���ϼ���
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
	//���¼���
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
	//�����ϼ���
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
	//�����¼���
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
	//�����ϼ���
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
	//�����¼���
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

void print_board()//��ӡ����
{
	system("cls");
	int i, j;
	cout << "    1   2   3   4   5   6   7   8" << endl;
	cout << " �����Щ��Щ��Щ��Щ��Щ��Щ��Щ���" << endl;
	for (i = 1; i <= 8; i++)
	{
		cout << i << "��";
		for (j = 1; j <= 8; j++)
		{
			switch (board[i][j])
			{
			case -1:cout << "  ��"; break;
			case 0:cout << "��"; break;
			case 1:cout << "��"; break;
			case 2:cout << "����"; break;
			}
		}
		if (i == 1)    cout << "    ��ѡ�����������ţ���";
		else if (i == 2)    cout << "      2����ͣ��Ϸ";
		else if (i == 3)    cout << "      4���˳���Ϸ";
		cout << endl;
		if (i == 8)    cout << " �����ة��ة��ة��ة��ة��ة��ة���" << endl;
		else if (i == 1)    cout << " �����੤�੤�੤�੤�੤�੤�੤��      1������" << endl;
		else if (i == 2)    cout << " �����੤�੤�੤�੤�੤�੤�੤��      3���浵" << endl;
		else    cout << " �����੤�੤�੤�੤�੤�੤�੤��" << endl;
	}
	cout << endl;
	int cnt1 = count(1), cnt0 = count(0);
	cout << "            �ڣ���=" << cnt1 << "��" << cnt0 << endl;
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
		cout << "��Ϸ��ͣ���������~" << endl;
		cout << endl;
		system("pause");
	}
	if (ch == '3')    save();
	if (ch == '4')    exit(1);
}

void able_to_put(int x, int y, int chess)//�ж��ĸ�λ�ÿ�������
{
	//�ֵ�һ������ʱ���������������Է��������ڵĿ�λ�ϣ�Ҫ�����µ����Ӻ�ԭ�еļ������Ӽ�ס�Է�������һ�����ӣ�����б�о��ɣ�
	if (scan[x][y] || x <= 0 || x >= 9 || y <= 0 || y >= 9)    return;//�ѱ����ҹ���Խ�磬���˳�
	int i;
	if (board[x][y] == -1)
	{
		//�˸�������� 
		if (!scan[x][y] && board[x - 1][y] == 1 - chess&&x >= 3)//��
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
		if (!scan[x][y] && board[x + 1][y] == 1 - chess&&x <= 6)//��
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
		if (!scan[x][y] && board[x][y - 1] == 1 - chess&&y >= 3)//��
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
		if (!scan[x][y] && board[x][y + 1] == 1 - chess&&y <= 6)//��
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
		if (!scan[x][y] && board[x - 1][y - 1] == 1 - chess&&x >= 3 && y >= 3)//����
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
		if (!scan[x][y] && board[x + 1][y + 1] == 1 - chess&&x <= 6 && y <= 6)//����
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
		if (!scan[x][y] && board[x - 1][y + 1] == 1 - chess&&x >= 3 && y <= 6)//����
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
		if (!scan[x][y] && board[x + 1][y - 1] == 1 - chess&&y >= 3 && x <= 6)//����
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

int count(int n)//����������������board��ĳ�����ֵĸ���
{
	int cnt = 0, i, j;
	for (i = 1; i <= 8; i++)
		for (j = 1; j <= 8; j++)
		{
			if (board[i][j] == n)    cnt++;
		}
	return cnt;
}

void save()//�浵
{
	ofstream outfile("data.txt", ios::out);
	int i, j;
	for (i = 1; i <= 8; i++)
		for (j = 1; j <= 8; j++)    outfile << board[i][j] << " ";
	outfile << b << " " << c;
	outfile.close();
}

void load()//����
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
	cout << "                ��ʼ�˵�" << endl;
	cout << "  ************************************" << endl;
	cout << endl;
	cout << "         ������ѡ��ǰ����š���" << endl;
	cout << endl;
	cout << "             1���¿���" << endl;
	cout << "             2��������Ϸ" << endl;
	cout << "             3������" << endl;
	cout << "             4���˳�" << endl;
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
		cout << "����ѡ��" << endl;
		cout << "1 �˻���ս" << endl;
		cout << "2 ��Ҷ�ս" << endl;
		b = _getch();
		if (b == '1')
		{
			system("cls");
			cout << "ѡ������������ɫ" << endl;
			cout << "1 ��" << endl << "2 ��" << endl;
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
			cout << "������ʾ����Ҷ�սģʽ��ʱ�޻���ʹ浵����:)" << endl;
			system("pause");
		}
		break;
	case '2':load(); break;
	case'3':print_help(); break;
	case '4':exit(1); break;
	}
}

void AI(int chess)//Ӧ�������С�㷨����-��֦��
{
	int tempboard1[9][9] = {}, tempboard2[9][9] = {}, tempboard3[9][9] = {};
	int score1, score2, score3, score3max = INT_MIN, score2max = INT_MIN, score1max = INT_MIN, AIputx, AIputy;
	memset(scan, false, sizeof(scan));
	able_to_put(1, 1, chess);
	int cnt2 = count(2), i, j;
	bool flag = false;
	if (cnt2 == 0)    return;//�޿��µĸ��ӣ�pass
	for (int m = 1; m < 9; m++)
	{
		for (int n = 1; n < 9; n++)
		{
			tempboard1[m][n] = board[m][n];//���浱ǰ����״̬,ԭ�������ڵ�һ������
		}
	}
	for (i = 1; i <= 8; i++)
	{
		for (j = 1; j <= 8; j++)
		{
			if (board[i][j] == 2)//������
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
						if (board[m][n] == 2)    board[m][n] = -1;//��պ������ӵ�
					}
				}
				score1 = calScore(chess);
				memset(scan, false, sizeof(scan));
				able_to_put(1, 1, 1 - chess);//����ҿ��µĵط�
				memcpy(tempboard2, board, sizeof(tempboard2));//���̸����ڶ�����ʱ���飬ԭ�������ڵڶ�������
				for (int m = 1; m <= 8; m++)
				{
					for (int n = 1; n <= 8; n++)
					{
						if (board[m][n] == 2)
						{
							board[m][n] = 1 - chess;//ģ���������
							reverse(m, n, 1 - chess);
							for (int l = 1; l < 9; l++)
							{
								for (int k = 1; k < 9; k++)
								{
									if (board[l][k] == 2) board[l][k] = -1;//��պ������ӵ�
								}
							}
							score2 = calScore(1 - chess);
							memset(scan, false, sizeof(scan));
							able_to_put(1, 1, chess);//�ж�AI���µĵط�
							memcpy(tempboard3, board, sizeof(tempboard3));//���̸�����������ʱ���飬ԭ�������ڵ���������
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
												if (board[p][q] == 2) board[p][q] = -1;//��պ������ӵ�
											}
										}
										score3 = calScore(chess);
										if (score3 > score3max) score3max = score3;
										memcpy(board, tempboard3, sizeof(board));//����
									}
								}
							}
							score2 -= score3max;
							if (score2 > score2max) score2max = score2;
							memcpy(board, tempboard2, sizeof(board));//����
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
	cout << "�ڰ��壬�ֽз��壨Reversi�����������壨Othello����ƻ�����ת�塣" << endl;
	cout << "�ڰ������������ձ������С���Ϸͨ���໥��ת�Է������ӣ������������˭�����Ӷ����ж�ʤ����"<< endl;
	cout << "����Ϊ8x8���񣬹�ʹ��64�����ӣ�ÿ�����ӷ��������棬�ֱ��Ǻ�ɫ�Ͱ�ɫ��" << endl;
	cout << "����ֿ�ʼǰ���Ȱ�����������������彻������������룬�ڷ����£�Ȼ��˫���������ӣ���˫����������£�����64������ȫ��ռ������ֽ������Ӷ��һ��Ϊʤ����" << endl;
	cout << "�ֵ�һ������ʱ���������������Է��������ڵĿ�λ�ϣ�Ҫ�����µ����Ӻ�ԭ�е��ѷ����Ӽ�ס�Է�������һ������(����б�о���)��Ȼ��ѱ���ס���ӱ�ɼ�������ɫ(Ҳ�г���)��" << endl;
	cout << "��������У��κ����ӼȲ�������������ߣ�Ҳ�����һ�������Ƶ���һ�����ӡ�" << endl;
	cout << "���ֵ�һ������ʱ������÷����ӿɳԣ��ͱ���ͣһ�����öԷ��������壬���������pass������һ�����ӿɳ�ʱ����ʹ��passҲ����pass��"<<endl;
	cout << endl;
	cout << "����������ز˵�����" << endl;
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
		if (count(2) != 0)//�û�����
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
		else//��������
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
		if (count(2) == 0)//��������
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
	else if (b == '2')//��Ҷ�ս
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
	if (count(1) == count(0))    cout << "               ƽ��" << endl;
	else if (count(1) > count(0))    cout << "              �ڷ�ʤ" << endl;
	else    cout << "              �׷�ʤ" << endl;
	cout << endl;
	system("pause");
	return 0;
}


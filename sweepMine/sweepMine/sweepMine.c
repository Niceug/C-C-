#include "menu.h"
#include "sweepMine.h"
int boardImg[ROWS][COLS] = { 0 };
int Count = 0;

/*
void click_Expand(int board[ROW][COL], int boardImg[ROWS][COLS], int player_x, int player_y)
{
int i = 0;
int j = 0;
int boardToGetCount[ROW][COL] = { 0 };
for (i = 1; i <= ROW; i++)
{
for (j = 1; j <= COL; j++)
{
boardToGetCount[i - 1][j - 1] =
(boardImg[i][j - 1] + boardImg[i - 1][j - 1] +
boardImg[i - 1][j] + boardImg[i - 1][j + 1] +
boardImg[i][j + 1] + boardImg[i + 1][j + 1] +
boardImg[i + 1][j] + boardImg[i + 1][j - 1]);
}
}

//����
for (i = 0; i < ROW; i++)
{
for (j = 0; j < COL; j++)
{
printf("%d ", boardToGetCount[i][j]);
}
printf("\n");
}

if (boardToGetCount[player_x + 1][player_y + 1] == 0)
{
	if (player_x - 1 + 1 < COL && player_y - 1 + 1 < ROW)
	{
		board[player_x - 1 + 1][player_y - 1 + 1] = 0;
		click_Expand(board, boardImg, player_x - 1 + 1, player_y - 1 + 1);
	}
	else
		return;

}
else
{
	if (player_x - 1 + 1< COL && player_y - 1 + 1 < ROW)
		board[player_x - 1 + 1][player_y - 1 + 1] = boardToGetCount[player_x + 1][player_y + 1];
}

if (boardToGetCount[player_x - 1][player_y - 1 + 1] == 0)
{
	if (player_x - 1 < COL && player_y - 1 + 1 < ROW)
	{
		board[player_x - 1][player_y - 1 + 1] = 0;
		click_Expand(board, boardImg, player_x - 1, player_y - 1 + 1);
	}
	else
		return;

}
else
{
	if (player_x - 1< COL && player_y - 1 + 1 < ROW)
		board[player_x - 1][player_y - 1 + 1] = boardToGetCount[player_x - 1][player_y - 1 + 1];
}

if (boardToGetCount[player_x - 1 + 1][player_y - 1] == 0)
{
	if (player_x - 1 + 1 < COL && player_y - 1 < ROW)
	{
		board[player_x - 1 + 1][player_y - 1] = 0;
		click_Expand(board, boardImg, player_x - 1 + 1, player_y - 1);
	}
	else
		return;

}
else
{
	if (player_x - 1 + 1< COL && player_y - 1< ROW)
		board[player_x - 1 + 1][player_y - 1] = boardToGetCount[player_x - 1 + 1][player_y - 1];
}

if (boardToGetCount[player_x - 1 - 1][player_y - 1 - 1] == 0)
{
	if (player_x - 1 - 1 >= 0 && player_y - 1 - 1 >= 0)
	{
		board[player_x - 1 - 1][player_y - 1 - 1] = 0;
		click_Expand(board, boardImg, player_x - 1 - 1, player_y - 1 - 1);
	}
	else
		return;

}
else
{
	if (player_x - 1 - 1 >= 0 && player_y - 1 - 1 >= 0)
		board[player_x - 1 - 1][player_y - 1 - 1] = boardToGetCount[player_x - 1 - 1][player_y - 1 - 1];
}

if (boardToGetCount[player_x - 1 - 1][player_y - 1] == 0)
{
	if (player_x - 1 - 1 >= 0 && player_y - 1 + 1 < ROW)
	{
		board[player_x - 1 - 1][player_y - 1] = 0;
		click_Expand(board, boardImg, player_x - 1 - 1, player_y - 1);
	}
	else
		return;

}
else
{
	if (player_x - 1 - 1 >= 0 && player_y - 1 + 1 < ROW)
		board[player_x - 1 - 1][player_y - 1] = boardToGetCount[player_x - 1 - 1][player_y - 1];
}

if (boardToGetCount[player_x - 1][player_y - 1 - 1] == 0)
{
	if (player_x - 1 + 1 < COL && player_y - 1 - 1 >= 0)
	{
		board[player_x - 1][player_y - 1 - 1] = 0;
		click_Expand(board, boardImg, player_x - 1, player_y - 1 - 1);
	}
	else
		return;

}
else
{
	if (player_x - 1 + 1< COL && player_y - 1 - 1 >= 0)
		board[player_x - 1][player_y - 1 - 1] = boardToGetCount[player_x - 1][player_y - 1 - 1];
}

if (boardToGetCount[player_x - 1 + 1][player_y - 1 - 1] == 0)
{
	if (player_x - 1 + 1 < COL && player_y - 1 - 1 >= 0)
	{
		board[player_x - 1 + 1][player_y - 1 - 1] = 0;
		click_Expand(board, boardImg, player_x - 1 + 1, player_y - 1 - 1);
	}
	else
		return;

}
else
{
	if (player_x - 1 + 1< COL && player_y - 1 - 1 >= 0)
		board[player_x - 1 + 1][player_y - 1 - 1] = boardToGetCount[player_x - 1 + 1][player_y - 1 - 1];
}

if (boardToGetCount[player_x - 1 - 1][player_y - 1 + 1] == 0)
{
	if (player_x - 1 - 1 >= 0 && player_y - 1 + 1 < ROW)
	{
		board[player_x - 1 - 1][player_y - 1 + 1] = 0;
		click_Expand(board, boardImg, player_x - 1 - 1, player_y - 1 + 1);
	}
	else
		return;

}
else
{
	if (player_x - 1 - 1 >= 0 && player_y - 1 + 1 < ROW)
		board[player_x - 1 - 1][player_y - 1 + 1] = boardToGetCount[player_x - 1 - 1][player_y - 1 + 1];
}
}
*/
//��չ
void click_Expand(int board[ROW][COL], int boardImg[ROWS][COLS], int player_x, int player_y)
{
	int i = 0;
	int j = 0;
	int boardToGetCount[ROW][COL] = { 0 };
	for (i = 1; i <= ROW; i++)
	{
		for (j = 1; j <= COL; j++)
		{
			boardToGetCount[i - 1][j - 1] =
				(boardImg[i][j - 1] + boardImg[i - 1][j - 1] +
					boardImg[i - 1][j] + boardImg[i - 1][j + 1] +
					boardImg[i][j + 1] + boardImg[i + 1][j + 1] +
					boardImg[i + 1][j] + boardImg[i + 1][j - 1]);
		}
	}

	/*����
	for (i = 0; i < ROW; i++)
	{
	for (j = 0; j < COL; j++)
	{
	printf("%d ", boardToGetCount[i][j]);
	}
	printf("\n");
	}*/

	if (boardToGetCount[player_x + 1][player_y + 1] == 0)
	{
		if (player_x - 1 + 1< COL && player_y - 1 + 1 < ROW)
			board[player_x - 1 + 1][player_y - 1 + 1] = 0;
	}
	else
	{
		if (player_x - 1 + 1< COL && player_y - 1 + 1 < ROW)
			board[player_x - 1 + 1][player_y - 1 + 1] = boardToGetCount[player_x + 1][player_y + 1];
	}

	if (boardToGetCount[player_x - 1][player_y - 1 + 1] == 0)
	{
		if (player_x - 1< COL && player_y - 1 + 1 < ROW)
			board[player_x - 1][player_y - 1 + 1] = 0;
	}
	else
	{
		if (player_x - 1< COL && player_y - 1 + 1 < ROW)
			board[player_x - 1][player_y - 1 + 1] = boardToGetCount[player_x - 1][player_y - 1 + 1];
	}

	if (boardToGetCount[player_x - 1 + 1][player_y - 1] == 0)
	{
		if (player_x - 1 + 1< COL && player_y - 1< ROW)
			board[player_x - 1 + 1][player_y - 1] = 0;
	}
	else
	{
		if (player_x - 1 + 1< COL && player_y - 1< ROW)
			board[player_x - 1 + 1][player_y - 1] = boardToGetCount[player_x - 1 + 1][player_y - 1];
	}

	if (boardToGetCount[player_x - 1 - 1][player_y - 1 - 1] == 0)
	{
		if (player_x - 1 - 1 >= 0 && player_y - 1 - 1 >= 0)
			board[player_x - 1 - 1][player_y - 1 - 1] = 0;
	}
	else
	{
		if (player_x - 1 - 1 >= 0 && player_y - 1 - 1 >= 0)
			board[player_x - 1 - 1][player_y - 1 - 1] = boardToGetCount[player_x - 1 - 1][player_y - 1 - 1];
	}

	if (boardToGetCount[player_x - 1 - 1][player_y - 1] == 0)
	{
		if (player_x - 1 - 1 >= 0 && player_y - 1 + 1 < ROW)
			board[player_x - 1 - 1][player_y - 1] = 0;
	}
	else
	{
		if (player_x - 1 - 1 >= 0 && player_y - 1 + 1 < ROW)
			board[player_x - 1 - 1][player_y - 1] = boardToGetCount[player_x - 1 - 1][player_y - 1];
	}

	if (boardToGetCount[player_x - 1][player_y - 1 - 1] == 0)
	{
		if (player_x - 1 + 1< COL && player_y - 1 - 1 >= 0)
			board[player_x - 1][player_y - 1 - 1] = 0;
	}
	else
	{
		if (player_x - 1 + 1< COL && player_y - 1 - 1 >= 0)
			board[player_x - 1][player_y - 1 - 1] = boardToGetCount[player_x - 1][player_y - 1 - 1];
	}

	if (boardToGetCount[player_x - 1 + 1][player_y - 1 - 1] == 0)
	{
		if (player_x - 1 + 1< COL && player_y - 1 - 1 >= 0)
			board[player_x - 1 + 1][player_y - 1 - 1] = 0;
	}
	else
	{
		if (player_x - 1 + 1< COL && player_y - 1 - 1 >= 0)
			board[player_x - 1 + 1][player_y - 1 - 1] = boardToGetCount[player_x - 1 + 1][player_y - 1 - 1];
	}

	if (boardToGetCount[player_x - 1 - 1][player_y - 1 + 1] == 0)
	{
		if (player_x - 1 - 1 >= 0 && player_y - 1 + 1 < ROW)
			board[player_x - 1 - 1][player_y - 1 + 1] = 0;
	}
	else
	{
		if (player_x - 1 - 1 >= 0 && player_y - 1 + 1 < ROW)
			board[player_x - 1 - 1][player_y - 1 + 1] = boardToGetCount[player_x - 1 - 1][player_y - 1 + 1];
	}
}
//��չ
void click_Expand1(int board[ROW][COL], int boardImg[ROWS][COLS], int player_x, int player_y)
{
	if (player_x == 0)
		return;
	if (player_y == 0)
		return;
	if (player_x == ROW)
		return;
	if (player_y == COL)
		return;
	click_Expand1(board, boardImg, player_x - 1, player_y);
	click_Expand1(board, boardImg, player_x, player_y - 1);
	click_Expand1(board, boardImg, player_x - 1, player_y - 1);
	click_Expand1(board, boardImg, player_x + 1, player_y + 1);
	click_Expand1(board, boardImg, player_x + 1, player_y);
	click_Expand1(board, boardImg, player_x, player_y + 1);
	click_Expand1(board, boardImg, player_x - 1, player_y + 1);
	click_Expand1(board, boardImg, player_x + 1, player_y - 1);

}


int main()
{
	int board[ROW][COL];
	int x;
	int y;
	int option = 1;
	int gameOverFlag = 1;
	srand((unsigned int)time(NULL));
	while (1)
	{
		option = showMenu();
		switch (option)
		{
		//�˳���Ϸ
		case 0:return 0;
		//��ʼ��Ϸ
		case 1: {
					InitBoard(board, ROW, COL);
					InitBoardImg(boardImg, ROWS, COLS);
					SetMine(boardImg, ROW, COL);
					while (1)
					{
						
						//����
						for (y = 0; y < ROWS; y++)
						{
							for (x = 0; x < COLS; x++)
							{
								printf("%d ", boardImg[y][x]);
							}
							printf("\n");
						}
						
						printf("\n");
						DisplayBoard(board, ROW, COL);
						gameOverFlag = ClearMine(board);
						if (GetMineCount() == 0)
						{
							printf("��ϲ���أ�\n");
							Count = 0;
							break;
						}

						if (gameOverFlag == 0)
						{
							DisplayBoard(board, ROW, COL);
							printf("��Ϸʧ�ܣ�\n");
							Count = 0;
							break;
						}

					}
				} break;
		default: printf("�������������ѡ��>");
		}	
	}
	return 0;
}

//��ʼ�����Ϊ-2��ʾδ���״̬
void InitBoard(int board[ROW][COL], int row, int col)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			board[i][j] = -2;
		}
	}
}

//��ʾ��Ϸ���
void DisplayBoard(int board[ROW][COL], int row, int col)
{
	int i = 0;
	int j = 0;
	printf("  ");
	for (i = 0; i < row; i++)
	{
		printf("%d ",i+1);
	}
	printf("\n");
	for (i = 0; i < row; i++)
	{
		printf("%d ", i + 1);
		for (j = 0; j < col; j++)
		{
			if(board[i][j] == -2)//��ʾ��ʼ��״̬
				printf("��");
			else if (board[i][j] == -1)//�����׵�״̬
				printf("��");
			else
				printf("%d ",board[i][j]);//��ʾ�м�����
		}
		printf("\n");
	}
}

//������
void SetMine(int boardImg[ROWS][COLS], int row, int col)
{
	int x = 0;
	int y = 0;
	int i = 0;
	int count = EASY_COUNT;//�׵�����
	while(count)
	{
		x = rand() % row;//ֻ����1��9
		++x;
		y = rand() % col;
		++y;
		if (boardImg[x][y] == 0)
		{
			boardImg[x][y] = 1;
			--count;
		}
	}
}

//�ж���Ϸʤ��
int GetMineCount()
{
	if (Count == ROW*COL - EASY_COUNT)
	{
		return 0;
	}
	else
		return 1;
}

//�����������ɨ��
int ClearMine(int board[ROW][COL])
{
	int Player_x;
	int Player_y;
	int x;
	int y;
	while (1)
	{
		printf("����������(x , y)\n");
		scanf("%d%d", &Player_x, &Player_y);
		x = Player_x - 1;
		y = Player_y - 1;
		if (board[x][y] == -2)
			break;
		printf("��������Ƿ�!\n");

	}
	if (Count == 0)
	{
		if (boardImg[Player_x][Player_y] == 1)
		{
			boardImg[Player_x][Player_y] = 0;
			Count = 1;
			board[x][y] =
				(boardImg[Player_x][Player_y - 1] + boardImg[Player_x - 1][Player_y - 1] +
					boardImg[Player_x - 1][Player_y] + boardImg[Player_x - 1][Player_y + 1] +
					boardImg[Player_x][Player_y + 1] + boardImg[Player_x + 1][Player_y + 1] +
					boardImg[Player_x + 1][Player_y] + boardImg[Player_x + 1][Player_y - 1]);
			if (board[x][y] == 0)
			{
					click_Expand(board, boardImg, Player_x, Player_y);
			}
			
			while (1)
			{
				x = rand() % ROW;//ֻ����1��9
				++x;
				y = rand() % COL;
				++y;
				if (boardImg[x][y] != 1)
				{
					boardImg[x][y] = 1;
					break;
				}
			}
		}
		else
		{
			Count = 1;
			//δ��������ʾ��Χ�׵ĸ���
			board[x][y] =
				(boardImg[Player_x][Player_y - 1] + boardImg[Player_x - 1][Player_y - 1] +
					boardImg[Player_x - 1][Player_y] + boardImg[Player_x - 1][Player_y + 1] +
					boardImg[Player_x][Player_y + 1] + boardImg[Player_x + 1][Player_y + 1] +
					boardImg[Player_x + 1][Player_y] + boardImg[Player_x + 1][Player_y - 1]);
			if (board[x][y] == 0)
			{
				click_Expand(board, boardImg, Player_x, Player_y);
			}
		}
	}
	else 
	{
		if (boardImg[Player_x][Player_y] == 1)
		{
			//��ʾ������
			board[x][y] = -1;
			//��Ϸ����
			return 0;
		}
		else
		{
			++Count;
			//δ��������ʾ��Χ�׵ĸ���
			board[x][y] =
					(boardImg[Player_x][Player_y - 1] + boardImg[Player_x - 1][Player_y - 1] +
					boardImg[Player_x - 1][Player_y] + boardImg[Player_x - 1][Player_y + 1] +
					boardImg[Player_x][Player_y + 1] + boardImg[Player_x + 1][Player_y + 1] +
					boardImg[Player_x + 1][Player_y] + boardImg[Player_x + 1][Player_y - 1]);
			if (board[x][y] == 0)
			{
				click_Expand(board, boardImg, Player_x, Player_y);
			}
		}
	}
	return 1;
}

void InitBoardImg(int boardImg[ROWS][COLS], int rows, int cols)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			boardImg[i][j] = 0;
		}
	}
}

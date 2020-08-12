/*Viking's Swing
���� ����: �׳׸� Ÿ�� �������� ��� ���� �Ʒ�, ���� ������ �ı��϶�.*/
#define _CRT_SECURE_NO_WARNINGS
#pragma warning (disable : 4996)
#include <stdio.h>
#include<conio.h>
#include<time.h>
#include<stdlib.h>
#include<Windows.h>

/* ĳ���� Figure
	players: ��(player1)
			 �¢�(player2)
			 ����	//����ŷ �׳׸� Ÿ�� �ִ� �÷��̾�1, 2
	boss: ��
		  ��
		  ��		//ȭ�� ���ִ� ����
	������ ���� : * (BALL)

	�Ʊ� ĳ����: ��
	���� ĳ����: ��
*/
int k = 0; int l = 0;

typedef struct _Char {

	int HP;				//ü��
	int nMoveX, nMoveY;	//�̵� ��ǥ
	int nDist;			//�̵� �Ÿ�
	clock_t MoveTime;	//�̵� �ð� ����
	clock_t OldTime;	//���� �̵� �ð�
}Char;

typedef struct _Soldier {
	
	int HP;				//ü��
	int nMoveX;			//�̵� ��ǥ
	int nDist;			//�̵� �Ÿ�
	clock_t MoveTime;	//�̵� �ð� ����
	clock_t OldTime;	//���� �̵� �ð�
}Soldier;

typedef struct _BALL {
	int createBall;
	int nX, nY;
	clock_t MoveTime;
	clock_t OldTime;
}BALL;

Char boss;				//boss
Soldier g_sEnemy[30];	//���� ĳ����
Soldier g_sFriend[15];	//�Ʊ� ĳ����
Char player1;			//player1
Char player2;			//player2	
int g_nenemyCount = 0;	//���� ��
int g_nfriendCount = 0;	//�Ʊ� �� 
int enemyHP = 15;		//���� ü�� vs (�Ʊ� ü���� player2�� ����)
BALL ball;

void Init() {

	//boss �ʱ⼳��
	boss.HP = 13;
	boss.nMoveX = 89;
	boss.nMoveY = 12;
	boss.nDist = 1;
	boss.MoveTime = 30;
	boss.OldTime = clock();

	//players �ʱ⼳��
	player1.HP = 13;
	player1.nMoveX = 20;
	player1.nMoveY = 12;
	player1.nDist = 1;
	player1.MoveTime = 30;
	player1.OldTime = clock();

	player2.HP = 15;
	player2.nMoveX = player1.nMoveX;
	player2.nMoveY = 12;
	player2.nDist = 1;
	player2.MoveTime = 30;			//player2�� ground�� �����ִ� ���� �ð��� ����
	player2.OldTime = clock();

	//boss�� ����
	ball.MoveTime = 30;
	ball.nY = 4;
	ball.OldTime = clock();
}

void Update(){

	clock_t CurTime = clock();

	//boss �¿� �
	if ((CurTime - boss.OldTime) > boss.MoveTime) {
		boss.OldTime = CurTime;
		if (boss.nMoveX + boss.nDist >= 20 && (boss.nMoveX + boss.nDist) <= 89) {
			boss.nMoveX += boss.nDist;
		}
		else {
			boss.nDist *= -1;	//-1�� ������ �ٲپ���.
			ball.createBall = rand() % 4;	// 2/4 Ȯ���� �������� ����
			switch (ball.createBall) {
			case 1:
				ball.nX = 30;
				break;
			case 2:
				ball.nX = 70;
				break;
			default:
				break;
			}
		}
	}
	//players �¿� �
	if ((CurTime - player1.OldTime) > player1.MoveTime) {
		player1.OldTime = CurTime;
		if (player1.nMoveX + player1.nDist >= 20 && (player1.nMoveX + player1.nDist) <= 89) {
			player1.nMoveX += player1.nDist;
		}
		else {
			player1.nDist *= -1;	//-1�� ������ �ٲپ���.

			int randomB = rand() % 2;	//boss //ĳ���͵��� Y ��ġ ���� �缳��
			int randomP = rand() % 2;	//player1, 2

			if (randomB == 0) {		//0: �׳��� line ��
				boss.nMoveY = 9;
			}
			else if (randomB == 1) {//1: �׳��� line �Ʒ�
				boss.nMoveY = 12;
			}
			if (randomP == 0) {		//0: �׳��� line ��
				player1.nMoveY = 9;
				ball.nY = 4;
			}
			else if (randomP == 1) {//1: �׳��� line �Ʒ�
				player1.nMoveY = 12;
				ball.nY = 7;
			}
		}
	}
	//player1�� boss�� �浹 ��
	if (boss.nMoveX == player1.nMoveX &&boss.nMoveY == player1.nMoveY) {
		if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
			boss.HP--;		//player1 ���� ����, boss ü�� -1
		}
		else {
			player1.HP--;	//���� ����, player1 ü�� -1
		}
	}

	//g_sFriend ĳ���� ��ȯ
	if (GetAsyncKeyState(VK_F12) & 0x8000) {
		if (g_nfriendCount < 15) {
			g_sFriend[g_nfriendCount].HP = 1;
			g_sFriend[g_nfriendCount].nDist = 1;
			g_sFriend[g_nfriendCount].nMoveX = 1;
			g_sFriend[g_nfriendCount].OldTime = CurTime;
			g_sFriend[g_nfriendCount].MoveTime = 1000;
			g_nfriendCount += 1;
		}
	}
	//g_sFriend ����
	for (int i = 0; i < g_nfriendCount; i++) {
		if (g_sFriend[i].HP == 1) {
			if (CurTime - g_sFriend[i].OldTime > g_sFriend[i].MoveTime) {
				g_sFriend[i].OldTime = CurTime;
				if (g_sFriend[i].nMoveX >= 60) {
					g_sFriend[i].HP = 0;	//��� ���� �� �����
					enemyHP -= 1;
					k++;
				}
				g_sFriend[i].nMoveX += g_sFriend[i].nDist;
			}
		}
	}
	//g_sEnemy ���
	if (g_nenemyCount < 30) {
		int create = rand() % 200;	//1/200 Ȯ���� ���� ��ȯ��
		if (create == 0) {
			g_sEnemy[g_nenemyCount].HP = 1;
			g_sEnemy[g_nenemyCount].nDist = 1;
			g_sEnemy[g_nenemyCount].nMoveX = 1;
			g_sEnemy[g_nenemyCount].OldTime = CurTime;
			g_sEnemy[g_nenemyCount].MoveTime = rand() % 1000 + 1000;
			g_nenemyCount++;
		}
	}
	//g_sEnemy ����
	for (int i = 0; i < g_nenemyCount; i++) {
		if (g_sEnemy[i].HP == 1) {
			if (CurTime - g_sEnemy[i].OldTime > g_sEnemy[i].MoveTime) {
				g_sEnemy[i].OldTime = CurTime;
				if (g_sEnemy[i].nMoveX >= 60) {
					player2.HP--;
					g_sEnemy[i].HP = 0;	//��� ���� �� �����
					l++;
				}
				g_sEnemy[i].nMoveX += g_sEnemy[i].nDist;
			}
		}
	}
	//���� vs �Ʊ� �浹 ó��
	if (g_sFriend[k].HP == 1 && g_sEnemy[l].HP == 1) {
		if ((84 - g_sEnemy[l].nMoveX) == (24 + g_sFriend[k].nMoveX)) {
			g_sEnemy[l].HP = 0;
			g_sFriend[k].HP = 0;			//�Ʊ� ĳ������ ü���� 0�� ����Ǵµ� ��� ���� �߻�
			g_sFriend[k].HP = 0;
			if (g_sFriend[k].HP != 0) {		
				while (1) {
					g_sFriend[k].HP = 0;
					if (g_sFriend[k].HP == 0)
						break;
				}
			}
			k++; l++;
		}
	}

	//player2�� ���ݰ� ����
	if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
		player2.nMoveY = 19;
		player2.nMoveX = player1.nMoveX;
		player2.OldTime = CurTime;
		for (int i = 0; i < g_nenemyCount; i++) {
			if (player2.nMoveX == g_sEnemy[i].nMoveX) {
				if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
					g_sEnemy[i].HP = 0;
					l++;
				}
				else
					player2.HP--;
			}
		}
	}
	if (player1.nMoveX == player2.nMoveX) {
		if (GetAsyncKeyState(VK_UP) & 0x8000) {
			player2.nMoveY = player1.nMoveY;
		}
	}
	if (player2.nMoveY == 19) {					//player2�� ground�� �����ִ� ���� �ð�	 
		if (((CurTime - player2.OldTime) / 1000) > 8) {
			player2.HP--;
			player2.nMoveY = player1.nMoveY;	//���� ����
		}
	}
	//���� vs player2 �浹 ó��
	for (int i = 0; i < g_nenemyCount; i++) {
		if (player2.nMoveY == 19) {
			if (g_sEnemy[i].HP == 1) {
				if(84 - g_sEnemy[i].nMoveX )
				if (84 - g_sEnemy[i].nMoveX == player2.nMoveX) {
					if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
						g_sEnemy[i].HP = 0;
						enemyHP--;
						l++;
					}
					else
						player2.HP--;
				}
			}
		}
	}
	
	//boss�� ����
	if (boss.HP > 0) {
		if (ball.createBall == 1 || ball.createBall == 2) {
			if (abs(player1.nMoveX - ball.nX) <= 10) {
				if (CurTime - ball.OldTime > ball.MoveTime) {
					ball.OldTime = CurTime;
					if (ball.nY + 1 > 15)
						ball.createBall = 0;
					else
						ball.nY++;
				}
			}
		}
	}
	if (ball.nY == player1.nMoveY) {
		if (GetAsyncKeyState(VK_TAB) & 0x8000)
			player1.HP;
		else
			player1.HP--;
	}
	if (player1.HP < 0)
		player1.HP == 0;
	if (player2.HP < 0)
		player2.HP == 0;
	if (boss.HP < 0)
		boss.HP == 0;
	if (enemyHP < 0)
		enemyHP == 0;

	fflush(stdin);
}

void GameScreen() {

	ScreenPrint(46, 2, "��VIKING's SWING��");

	//�÷��� ȭ��
	for (int i = 0; i <= 69; i++) {
		ScreenPrint(20 + i, 1, "-");
		ScreenPrint(20 + i, 3, "-");
	}
	for (int j = 1; j <= 16; j++) {
		ScreenPrint(19, j, "��");
		ScreenPrint(89, j, "��");
	}
	for (int k = 0; k <= 69; k++) {
		ScreenPrint(20 + k, 19, "_");
	}

	//���
	ScreenPrint(20, 16, "�١�");	//player
	ScreenPrint(20, 17, "++++");
	ScreenPrint(20, 18, "���");
	ScreenPrint(20, 19, "���");

	ScreenPrint(86, 16, "���");	//boss
	ScreenPrint(86, 17, "++++");
	ScreenPrint(86, 18, "���");
	ScreenPrint(86, 19, "���");
	
	//ü��
	for (int j = player1.HP; j > 0; j--) {	//player1
		ScreenPrint(18, 17 - j, "��");
	}
	for (int j = boss.HP; j > 0; j--) {		//boss
		ScreenPrint(90, 17 - j, "��");
	}
	for (int j = player2.HP; j > 0; j--) {	//player2(player ����� ü�°� ����)
		ScreenPrint(23 + j*2, 0, "��");
	
	}
	for (int j = 0; j < enemyHP; j++) {		//boss�� ���
		ScreenPrint(83 - j * 2, 0, "��");
	}
}

void Render() {
	
	ScreenClear();
	
	//Note: ������ ����
	GameScreen();

	//�׳��� line ǥ��
	for (int i = 0; i < 69; i++) {
		ScreenPrint(20 + i, 11, "_");
	}
	
	ScreenPrint(boss.nMoveX, boss.nMoveY, "��");				//boss
	ScreenPrint(boss.nMoveX, boss.nMoveY + 1, "��");
	ScreenPrint(boss.nMoveX, boss.nMoveY + 2, "��");
	

	ScreenPrint(player1.nMoveX, player1.nMoveY, "��");			//player1
	ScreenPrint(player1.nMoveX, player1.nMoveY + 1, "��");
	ScreenPrint(player1.nMoveX, player1.nMoveY + 2, "��");
	
	
	if (player2.nMoveY != 19) {
		if (player1.nDist == 1) {								//player2
			ScreenPrint(player1.nMoveX + 1, player1.nMoveY + 1, "��");
			ScreenPrint(player1.nMoveX + 2, player1.nMoveY + 2, "��");
		}
		else if (player1.nDist == -1) {
			ScreenPrint(player1.nMoveX - 2, player1.nMoveY + 1, "��");
			ScreenPrint(player1.nMoveX - 2, player1.nMoveY + 2, "��");
		}
	}
	else if (player2.nMoveY == 19) {							//player2�� �ٴڿ� ������ �ο� �� ĳ���� ����1�� ��
		ScreenPrint(player2.nMoveX, player2.nMoveY, "��");
	}
	
	for (int i = 0; i < g_nenemyCount; i++) {
		if (g_sEnemy[i].HP) {
			ScreenPrint(84 - g_sEnemy[i].nMoveX , 19, "��");
			if (g_sEnemy[i].nMoveX >= 60) {
				ScreenPrint(22, 19, "��");	//������ �ް� ũ���� ���� ����
			}
		}
	}
	for (int i = 0; i < g_nfriendCount; i++) {
		if (g_sFriend[i].HP != 0) {
			ScreenPrint(24 + g_sFriend[i].nMoveX, 19, "��");
			if (g_sFriend[i].nMoveX >= 60) {
				ScreenPrint(86, 19, "��");	//������ �ް� ũ���� ���� ����
			}
		}
	}
	//boss ball ����
	
	if (ball.createBall == 1 || ball.createBall == 2) {
		ScreenPrint(ball.nX, ball.nY, "*");
	}
	
	ScreenFlipping();
}

int main(){

	ScreenInit();
	Init();		

	srand((unsigned int)time(NULL));
	
	while (1) {
		
		Update();
	
		Render();

		if ((player1.HP <= 0 && player2.HP <= 0) || (boss.HP <= 0 && enemyHP <= 0))
			break;
	}

	ScreenRelease();
	
	printf("Game Over!\n");

	if (boss.HP <= 0 && enemyHP <= 0) {
		printf("�¸�!");
	}
	else if (player1.HP <= 0 && player2.HP <= 0) {
		printf("Game Over! �絵�� �Ͻðڽ��ϱ�?");
	}
	else if ((player1.HP <= 0 && player2.HP <= 0) && (boss.HP <= 0 && enemyHP <= 0)) {
		printf("���º�");
	}

	return 0;
}

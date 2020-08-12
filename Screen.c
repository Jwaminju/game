/*Viking's Swing
//게임 설명: 그네를 타고 펼쳐지는 대결 구도 아래, 적의 기지를 파괴하라.
Screen.c 소스는 게임 인터페이스를 다운받아 사용함
출처: C를 이용한 게임 프로그래밍(출판사: 나우커뮤니케이션/ 지은이: 이태성 지음)*/
#include <windows.h>

static int g_nScreenIndex;
static HANDLE g_hScreen[2];

void ScreenInit() {
	CONSOLE_CURSOR_INFO cci;

	//화면에 2개의 버퍼를 만듬
	g_hScreen[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	g_hScreen[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

	// 커서 숨기기
	cci.dwSize = 1;
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(g_hScreen[0], &cci);
	SetConsoleCursorInfo(g_hScreen[1], &cci);
}

void ScreenFlipping() {
	Sleep(10);
	SetConsoleActiveScreenBuffer(g_hScreen[g_nScreenIndex]);
	g_nScreenIndex = !g_nScreenIndex;
}

void ScreenClear() {
	COORD Coor = { 0,0 };
	DWORD dw;
	FillConsoleOutputCharacter(g_hScreen[g_nScreenIndex], ' ', 80 * 25, Coor, &dw);
}

void ScreenRelease() {
	CloseHandle(g_hScreen[0]);
	CloseHandle(g_hScreen[1]);
}
void ScreenPrint(int x, int y, char *string) {
	DWORD dw;
	COORD CursorPosition = { x,y };
	SetConsoleCursorPosition(g_hScreen[g_nScreenIndex], CursorPosition);
	WriteFile(g_hScreen[g_nScreenIndex], string, strlen(string), &dw, NULL);
}
//1~15 개의 색상 설정 가능
void SetColor(unsigned short color) {
	SetConsoleTextAttribute(g_hScreen[g_nScreenIndex], color);
}


#include "Renderer.h"

void gotoxy(int x, int y) {
    COORD pos = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void SetColor(int color) {
	static HANDLE std_output_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(std_output_handle, color);
}

void Renderer::show_logo()
{
	gotoxy(13, 3);
	printf("旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬");
	Sleep(100);
	gotoxy(13, 4);
	printf("早 ﹣﹣﹣  ﹣﹣﹣  ﹣﹣﹣   ﹣﹣     ﹣   ﹣﹣﹣ 早");
	Sleep(100);
	gotoxy(13, 5);
	printf("早   ﹣    ﹣        ﹣     ﹣ ﹣    ﹣   ﹣     早");
	Sleep(100);
	gotoxy(13, 6);
	printf("早   ﹣    ﹣﹣﹣    ﹣     ﹣﹣     ﹣     ﹣   早");
	Sleep(100);
	gotoxy(13, 7);
	printf("早   ﹣    ﹣        ﹣     ﹣ ﹣    ﹣       ﹣ 早");
	Sleep(100);
	gotoxy(13, 8);
	printf("早   ﹣    ﹣﹣﹣    ﹣     ﹣  ﹣   ﹣   ﹣﹣﹣ 早");
	Sleep(100);
	gotoxy(13, 9);
	printf("曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭");

	gotoxy(28, 20);
	printf("Please Press Any Key~!");
}

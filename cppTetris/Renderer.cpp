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
	printf("��������������������������������������������������������������������������������������������������");
	Sleep(100);
	gotoxy(13, 4);
	printf("�� �ߡߡ�  �ߡߡ�  �ߡߡ�   �ߡ�     ��   �ߡߡ� ��");
	Sleep(100);
	gotoxy(13, 5);
	printf("��   ��    ��        ��     �� ��    ��   ��     ��");
	Sleep(100);
	gotoxy(13, 6);
	printf("��   ��    �ߡߡ�    ��     �ߡ�     ��     ��   ��");
	Sleep(100);
	gotoxy(13, 7);
	printf("��   ��    ��        ��     �� ��    ��       �� ��");
	Sleep(100);
	gotoxy(13, 8);
	printf("��   ��    �ߡߡ�    ��     ��  ��   ��   �ߡߡ� ��");
	Sleep(100);
	gotoxy(13, 9);
	printf("��������������������������������������������������������������������������������������������������");

	gotoxy(28, 20);
	printf("Please Press Any Key~!");
}

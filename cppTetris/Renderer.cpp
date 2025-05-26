#include <conio.h>
#include <ctime>
#include <cstdlib>
#include "Renderer.h"

using namespace std;
void gotoxy(int x, int y) {
    COORD pos = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void SetColor(Color color) {
	static HANDLE std_output_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(std_output_handle, static_cast<int>(color));
}

void Renderer::show_logo()
{
	srand(static_cast<unsigned int>(time(NULL))); // ���� �ʱ�ȭ

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

	int i;
	for (i = 0; i >= 0; i++) {
		if (i % 40 == 0)
		{
			for (int j = 0; j < 5; j++) {
				gotoxy(12, 14 + j);
				printf("                                                          ");
			}

			// ������ ��� 4�� ���� �� ȭ�鿡 ���
			show_cur_block(rand() % 7, 6, 14);
			show_cur_block(rand() % 7, 12, 14);
			show_cur_block(rand() % 7, 18, 14);
			show_cur_block(rand() % 7, 24, 14);
		}

		if (_kbhit()) break;
		Sleep(30);
	}

	_getch();
	system("cls");
}

int Renderer::show_cur_block(int shapeIndex, int x, int y)
{
	// Tetromino enum���� ��ȯ
	Tetromino t = static_cast<Tetromino>(shapeIndex);

	Block tempBlock(t);
	tempBlock.move(x - tempBlock.getX(), y - tempBlock.getY()); // ��ġ ����

	setBlockColor(t);
	shapeVec shape = tempBlock.getShape();
	short px = tempBlock.getX();
	short py = tempBlock.getY();

	for (size_t i = 0; i < shape.size(); i++) {
		for (size_t j = 0; j < shape[0].size(); j++) {
			if (shape[i][j] == 1) {
				gotoxy((px + j) * 2, py + i);
				printf("��");
			}
		}
	}

	SetColor(Color::BLACK);
	gotoxy(77, 23);
	return 0;
}


int Renderer::input_data()
{
	int i = 0;
	SetColor(Color::GRAY);
	gotoxy(10, 7);
	printf("��������������������<GAME KEY>��������������������");
	Sleep(10);
	gotoxy(10, 8);
	printf("�� UP   : Rotate Block        ��");
	Sleep(10);
	gotoxy(10, 9);
	printf("�� DOWN : Move One-Step Down  ��");
	Sleep(10);
	gotoxy(10, 10);
	printf("�� SPACE: Move Bottom Down    ��");
	Sleep(10);
	gotoxy(10, 11);
	printf("�� LEFT : Move Left           ��");
	Sleep(10);
	gotoxy(10, 12);
	printf("�� RIGHT: Move Right          ��");
	Sleep(10);
	gotoxy(10, 13);
	printf("������������������������������������������������������������");


	//while (i < 1 || i>8)																	//���� �����ϴ� ��
	//{
	//	gotoxy(10, 3);
	//	printf("Select Start level[1-8]:       \b\b\b\b\b\b\b");
	//	scanf_s("%d", &i);
	//}


	//level = i - 1;

	gotoxy(10, 3);
	cout << "Press any key" << endl;
	_getch();
	system("cls");
	return 0;
}

// �ణ�� ������ �ʿ��ҵ�
void Renderer::drawBlock(Block block)
{
	setBlockColor(block.getType());
	SetColor(color);
	short x = block.getX();
	short y = block.getY();
	gotoxy(x, y);
	shapeVec shape = block.getShape();

	for (size_t i = 0; i < shape.size(); i++) {
		for (size_t j = 0; j < shape[0].size(); j++) {
			if (shape[i][j] == 1) {
				gotoxy(x + j*2, y + i);
				cout << "��";
			}

		}
	}

	SetColor(Color::BLACK);
	gotoxy(77, 23);
}

void Renderer::eraseBlock(Block block)
{
	short x = block.getX();
	short y = block.getY();
	shapeVec shape = block.getShape();
	for (size_t i = 0; i < shape.size(); i++) {
		for (size_t j = 0; j < shape[0].size(); j++) {
			if (shape[i][j] == 1) {
				gotoxy(x + j * 2, y + i);
				cout << "   ";
			}

		}
	}
}


void Renderer::setBlockColor(Tetromino t)
{
	switch (t)
	{
	case Tetromino::I:
		color = Color::SKY_BLUE;
		break;
	case Tetromino::O:
		color = Color::YELLOW;
		break;
	case Tetromino::T:
		color = Color::VOILET;
		break;
	case Tetromino::J:
		color = Color::BLUE;
		break;
	case Tetromino::L:
		color = Color::DARK_YELLOW;
		break;
	case Tetromino::S:
		color = Color::GREEN;
		break;
	case Tetromino::Z:
		color = Color::RED;
		break;
	}
	SetColor(color);

}

void Renderer::drawBoard(Board board)
{
	SetColor(Color::DARK_GRAY);
	for (size_t i = 0; i < Board::height; i++) {
		for (size_t j = 0; j < Board::width; j++) {
			if(board.board[i][j] == 1)
				cout << ((i < 3) ? "��" : "��");
			else
				cout << "  ";
		}
		cout << endl;
	}

	SetColor(Color::BLACK);
	gotoxy(77, 23);
}

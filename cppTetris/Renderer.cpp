#include "Renderer.h"
#include <conio.h>
#include <ctime>
#include <cstdlib>

using namespace std;


void gotoxy(int x, int y) {
    COORD pos = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void SetColor(Color color) {
	static HANDLE std_output_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(std_output_handle, static_cast<int>(color));
}

Renderer::Renderer()
{
	menu_string = { "Start", "Setting", "Exit" };
	system("Tetris");
	system("mode con:cols=100 lines=30");
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = false;
	ConsoleCursor.dwSize = 1;
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(consoleHandle, &ConsoleCursor);
}

void Renderer::show_logo()
{
	srand(static_cast<unsigned int>(time(NULL))); // 랜덤 초기화

	SetColor(Color::DARK_SKY_BLUE);


	// 추후 수정!
	const vector<string> logoLines = {
		"┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓",
		"┃ ◆◆◆  ◆◆◆  ◆◆◆   ◆◆     ◆   ◆◆◆ ┃",
		"┃   ◆    ◆        ◆     ◆ ◆    ◆   ◆     ┃",
		"┃   ◆    ◆◆◆    ◆     ◆◆     ◆     ◆   ┃",
		"┃   ◆    ◆        ◆     ◆ ◆    ◆       ◆ ┃",
		"┃   ◆    ◆◆◆    ◆     ◆  ◆   ◆   ◆◆◆ ┃",
		"┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛"
	};
	for (size_t i = 0; i < logoLines.size(); ++i) {
		gotoxy(13, 3 + static_cast<int>(i));
		cout << logoLines[i];
		Sleep(100);
	}

	gotoxy(28, 20);
	SetColor(Color::WHITE);
	cout << "Please Press Any Key~!";

	int i = 0;
	while(true) {
		
		if (i % 40 == 0)
		{
			for (int j = 0; j < 5; j++) {
				gotoxy(6, 14 + j);
				printf("                                                                ");
			}

			// 무작위 겹치지 않는 블럭 4개 생성 후 화면에 출력
			Block block;
			for (int k = 0; k < 4; k++) {
				block.setBlock(static_cast<Tetromino>((i + k) % 7));
				block.move(1 + 6*k, 14);
				if (rand() % 2 == 0) 
					block.rotate();
				
				drawBlock(block);
			}
		}

		if (_kbhit()) break;
		Sleep(30);
		i++;
	}

	_getch();
	system("cls");
}

void Renderer::show_menu(short menu)
{
	cout << endl;
	for (size_t i = 0; i < 3; i++) {
		gotoxy(42, 20 + i);
		if (menu == i) 
			SetColor(Color::YELLOW);
		else
			SetColor(Color::WHITE);
		cout << "▶" << menu_string[i] << endl;
	}

	SetColor(Color::WHITE);
	gotoxy(77, 23);
}

// 약간의 개선이 필요할듯
void Renderer::drawBlock(Block& block)
{
	cout << endl;
	setBlockColor(block.getType());
	SetColor(color);
	short x = block.getX();
	short y = block.getY();
	gotoxy(x, y);
	shapeVec shape = block.getShape();

	for (int i = 0; i < shape.size(); i++) {
		for (int j = 0; j < shape[0].size(); j++) {
			if (shape[i][j] == 1) {
				gotoxy((x + j)*2 + ab_x, y + i + ab_y);
				cout << "■";
			}

		}
	}

	SetColor(Color::BLACK);
	gotoxy(77, 23);
}

void Renderer::eraseBlock(Block& block)
{
	cout << endl;
	short x = block.getX();
	short y = block.getY();
	shapeVec shape = block.getShape();
	for (int i = 0; i < shape.size(); i++) {
		for (int j = 0; j < shape[0].size(); j++) {
			if (shape[i][j] == 1) {
				gotoxy((x + j) * 2 + ab_x, y + i + ab_y);
				cout << "  ";
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

void Renderer::drawBoard(Board& board)
{
	cout << endl;
	SetColor(Color::DARK_GRAY);
	for (size_t i = 0; i < Board::height; i++) {
		for (size_t j = 0; j < Board::width; j++) {

			gotoxy((j * 2) + ab_x, i + ab_y);

			if(board.board[i][j] == 1)
				cout << ((i < 3) ? "□" : "■");
			else
				cout << "   ";
		}
	}

	SetColor(Color::BLACK);
	gotoxy(77, 23);
}

void Renderer::eraseLine(size_t i)
{
	cout << endl;
	SetColor(Color::BLUE);
	gotoxy(1 * 2 + 5, i + 1);
	for (size_t j = 1; j < Board::width - 1; j++)
	{
		cout << "□";
		Sleep(10);
	}
	gotoxy(1 * 2, i);
	for (size_t j = 1; j < 13; j++)
	{
		cout << "  ";
		Sleep(10);
	}
}


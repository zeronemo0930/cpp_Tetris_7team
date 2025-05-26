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
	gotoxy(13, 3);
	printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
	Sleep(100);
	gotoxy(13, 4);
	printf("┃ ◆◆◆  ◆◆◆  ◆◆◆   ◆◆     ◆   ◆◆◆ ┃");
	Sleep(100);
	gotoxy(13, 5);
	printf("┃   ◆    ◆        ◆     ◆ ◆    ◆   ◆     ┃");
	Sleep(100);
	gotoxy(13, 6);
	printf("┃   ◆    ◆◆◆    ◆     ◆◆     ◆     ◆   ┃");
	Sleep(100);
	gotoxy(13, 7);
	printf("┃   ◆    ◆        ◆     ◆ ◆    ◆       ◆ ┃");
	Sleep(100);
	gotoxy(13, 8);
	printf("┃   ◆    ◆◆◆    ◆     ◆  ◆   ◆   ◆◆◆ ┃");
	Sleep(100);
	gotoxy(13, 9);
	printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");

	gotoxy(28, 20);
	printf("Please Press Any Key~!");
}


// 약간의 개선이 필요할듯
void Renderer::drawBlock(Block& block)
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
				cout << "■";
			}

		}
	}

	SetColor(Color::BLACK);
	gotoxy(77, 23);
}

void Renderer::eraseBlock(Block& block)
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

void Renderer::drawBoard(Board& board)
{
	SetColor(Color::DARK_GRAY);
	for (size_t i = 0; i < Board::height; i++) {
		for (size_t j = 0; j < Board::width; j++) {
			if(board.board[i][j] == 1)
				cout << ((i < 3) ? "□" : "■");
			else
				cout << "  ";
		}
		cout << endl;
	}

	SetColor(Color::BLACK);
	gotoxy(77, 23);
}

void Renderer::eraseLine(Board& board)
{
	SetColor(Color::BLUE);
	gotoxy(1 * 2, i);
	for (j = 1; j < width - 1; j++)
	{
		cout << "□";
		Sleep(10);
	}
	gotoxy(1 * 2, i);
	for (j = 1; j < 13; j++)
	{
		cout << "  ";
		Sleep(10);
	}
}

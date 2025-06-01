#include "Renderer.h"
#include <conio.h>
#include <ctime>
#include <cstdlib>

using namespace std;


enum {
	BLACK = 0,
	BLUE = 1,
	GREEN = 2,
	SKY_BLUE = 3,
	RED = 4,
	VOILET = 5,
	YELLOW = 6,
	WHITE = 7,
	GRAY = 8,
	DARK_YELLOW = 14
};


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

int Renderer::input_data()
{
	int i = 0;
	SetColor(Color::GRAY);
	gotoxy(10, 7);
	cout << ("┏━━━━━━━━━<GAME KEY>━━━━━━━━━┓");
	Sleep(10);
	gotoxy(10, 8);
	cout << ("┃ UP   : Rotate Block        ┃");
	Sleep(10);
	gotoxy(10, 9);
	cout << ("┃ DOWN : Move One-Step Down  ┃");
	Sleep(10);
	gotoxy(10, 10);
	cout << ("┃ SPACE: Move Bottom Down    ┃");
	Sleep(10);
	gotoxy(10, 11);
	cout << ("┃ LEFT : Move Left           ┃");
	Sleep(10);
	gotoxy(10, 12);
	cout << ("┃ RIGHT: Move Right          ┃");
	Sleep(10);
	gotoxy(10, 13);
	cout << ("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");


	//while (i < 1 || i>8)																	//레벨 변경하는 거
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

// 약간의 개선이 필요할듯
void Renderer::drawBlock(Block& block)
{
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

void SetColor(int color)															// color 설정하는거 못찾아서 새로추가...
{
	static HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}

void Renderer::show_next_block(Block& nextBlock)
{
	const shapeVec& shape = nextBlock.getShape();
	Tetromino type = nextBlock.getType();

	// 색 설정 (기존 enum 값 사용)
	switch (type)
	{
	case Tetromino::I: SetColor(SKY_BLUE); break;
	case Tetromino::O: SetColor(YELLOW); break;
	case Tetromino::T: SetColor(VOILET); break;
	case Tetromino::J: SetColor(BLUE); break;
	case Tetromino::L: SetColor(DARK_YELLOW); break;
	case Tetromino::S: SetColor(GREEN); break;
	case Tetromino::Z: SetColor(RED); break;
	}

	// 테두리 박스 출력 (위치 고정)
	for (int i = 0; i < 6; i++)
	{
		gotoxy(33, i + 1);
		for (int j = 0; j < 6; j++)
		{
			if (i == 0 || i == 5 || j == 0 || j == 5)
				printf("■");
			else
				printf("  ");
		}
	}

	// 블록 도형 출력 (위치: x=35, y=2 기준)
	for (int i = 0; i < shape.size(); ++i)
	{
		for (int j = 0; j < shape[i].size(); ++j)
		{
			if (shape[i][j] == 1)
			{
				gotoxy(35 + j * 2, 2 + i);
				printf("■");
			}
		}
	}

	SetColor(BLACK);     // 색상 초기화
	gotoxy(77, 23);      // 커서 숨김용
}


void Renderer::show_game_stat(int score)
{
	static bool printed_text = false;
	SetColor(Color::GRAY);

	// "SCORE" 텍스트는 한 번만 출력
	if (!printed_text)
	{
		gotoxy(35, 9);
		std::cout << "SCORE";
		printed_text = true;
	}

	// 점수는 계속 업데이트됨
	gotoxy(35, 10);
	printf("%10d", score);
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
			gotoxy((j * 2) + ab_x, i + ab_y);
			if(board.board[i][j] == 1)
				cout << ((i < 3) ? "□" : "■");
			else
				cout << "  ";
		}
	}

	SetColor(Color::BLACK);
	gotoxy(77, 23);
}

void Renderer::eraseLine(size_t i)
{
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

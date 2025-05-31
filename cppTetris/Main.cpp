#include <iostream>
#include "GameManager.h"
using namespace std;

int main() {
	GameManager GM = GameManager();
	/*Block block;
	Renderer renderer;
	block.rotate();
	renderer.drawBlock(block);*/

	GM.start();
	return 0;
}
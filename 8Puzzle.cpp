//============================================================================
// Name        : 8Puzzle.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;
#include "State.h"
#include "Game.h"

int main() {
	srand(time(0));
	clock_t begin = clock();
	double elapsed_secs = 0;
	cout << "\nGame\n";
	Game firstGame;
	firstGame.play();
	clock_t end = clock();
	elapsed_secs = double(end - begin) / 1000000;
	cout << "\nTOTAL TIME: " << elapsed_secs;
	return 0;
}

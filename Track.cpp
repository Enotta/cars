#include "Track.h"

Track::Track(int length) {
	if (length > 2 || length < 0) length = 0;

	srand(time(0));

	grid = new char* [20];
	for (int i = 0; i < 20; ++i) {
		grid[i] = new char[20];
		for (int j = 0; j < 20; ++j) {
			grid[i][j] = '0';
		}
	}

	// Определение первой опорной точки
	corner1 = new int[2];
	while (true) {
		int x = rand() / ((RAND_MAX + 1u) / 10);
		int y = rand() / ((RAND_MAX + 1u) / 10);

		if ((x >= length*2 && x < 2+length*2 && y <= 8 && y >= 2*length) || (x <= 8 && x >= length*2 && y >= length*2 && y < 2+length*2)) {
			corner1[0] = x;
			corner1[1] = y;
			grid[y][x] = 'a';
			break;
		}
	}

	// Определение второй опорной точки
	corner2 = new int[2];
	while (true) {
		int x = rand() / ((RAND_MAX + 1u) / 10) + 10;
		int y = rand() / ((RAND_MAX + 1u) / 10);

		if ((x >= 11 && x <= 19-length*2 && y >= length*2 && y < 2+length*2) || (x <= 19-length*2 && x > 17-length*2 && y <= 8 && y >= length*2)) {
			corner2[0] = x;
			corner2[1] = y;
			grid[y][x] = 'b';
			break;
		}
	}

	// Определение третьей опорной точки
	corner3 = new int[2];
	while (true) {
		int x = rand() / ((RAND_MAX + 1u) / 10) + 10;
		int y = rand() / ((RAND_MAX + 1u) / 10) + 10;

		if ((x <= 19-length*2 && x > 17-length*2 && y >= 11 && y <= 19-length*2) || (x >= 11 && x <= 19-length*2 && y <= 19-length*2 && y > 17-length*2)) {
			corner3[0] = x;
			corner3[1] = y;
			grid[y][x] = 'c';
			break;
		}
	}

	// Определение четвёртой опорной точки
	corner4 = new int[2];
	while (true) {
		int x = rand() / ((RAND_MAX + 1u) / 10);
		int y = rand() / ((RAND_MAX + 1u) / 10) + 10;

		if ((x <= 8 && x >= length*2 && y <= 19-length*2 && y > 17-length*2) || (x >= length*2 && x < 2+length*2 && y >= 11 && y <= 19-length*2)) {
			corner4[0] = x;
			corner4[1] = y;
			grid[y][x] = 'd';
			break;
		}
	}

	createPath(corner1, corner2);
	createPath(corner2, corner3);
	createPath(corner3, corner4);
	createPath(corner4, corner1);
}

void Track::createPath(int* p1, int* p2) {
	srand(time(0));

	// Создание копии карты с которой работаем
	char** gridCopy = new char* [20];
	for (int i = 0; i < 20; ++i) {
		gridCopy[i] = new char[20];
	}

	for (int i = 0; i < 20; ++i) {
		for (int j = 0; j < 20; ++j) {
			gridCopy[i][j] = grid[i][j];
		}
	}

	char startChar = gridCopy[p1[1]][p1[0]];
	char endChar = gridCopy[p2[1]][p2[0]];

	// Прокладка шаблона маршрута
	int* startPos = new int [2] {p1[0]+forward.at(startChar)[0], p1[1]+forward.at(startChar)[1]};
	int* endPos = new int [2] {p2[0]+backward.at(endChar)[0], p2[1]+backward.at(endChar)[1]};

	random_device dev;
	mt19937 rng(dev());
	uniform_int_distribution<mt19937::result_type> dist10(1, 10);
	while (startPos[0] != endPos[0] || startPos[1] != endPos[1]) {
		gridCopy[startPos[1]][startPos[0]] = 'z';

		int xMul = 0;
		if (startPos[0] - endPos[0] != 0) {
			xMul = (endPos[0] - startPos[0]) / abs(endPos[0] - startPos[0]);
		}

		int yMul = 0;
		if (startPos[1] - endPos[1] != 0) {
			yMul = (endPos[1] - startPos[1]) / abs(endPos[1] - startPos[1]);
		}

		int s = dist10(rng);
		if (s <= 5) {
			if (gridCopy[startPos[1]][startPos[0]+xMul] == '0') {
				startPos[0] += xMul;
			}
		}
		else {
			if (gridCopy[startPos[1]+yMul][startPos[0]] == '0') {
				startPos[1] += yMul;
			}
		}
	}
	gridCopy[startPos[1]][startPos[0]] = 'z';

	// Прокладка маршрута
	startPos[0] = p1[0];
	startPos[1] = p1[1];

	int* priority1 = new int[2] {0, 0};
	int* priority2 = new int[2] {0, 0};
	int* priority3 = new int[2] {0, 0};

	switch (gridCopy[startPos[1]][startPos[0]])
	{
	case 'a':
		priority1[1] = -1;
		priority2[0] = 1;
		priority3[1] = 1;
		break;
	case 'b':
		priority1[0] = 1;
		priority2[1] = 1;
		priority3[0] = -1;
		break;
	case 'c':
		priority1[1] = -1;
		priority2[0] = 1;
		priority3[1] = 1;
		break;
	case 'd':
		priority1[1] = -1;
		priority2[0] = 1;
		priority3[1] = 1;
		break;
	}

	// Переносим значения из копии на карту
	for (int i = 0; i < 20; ++i) {
		for (int j = 0; j < 20; ++j) {
			if (gridCopy[i][j] != '0') grid[i][j] = gridCopy[i][j];
		}
	}

	delete[] gridCopy;
	delete[] startPos;
	delete[] endPos;
}

void Track::print() {
	for (int i = 0; i < 20; ++i) {
		for (int j = 0; j < 20; ++j) {
			if (grid[i][j] != '0') cout << grid[i][j] << " ";
			else cout << "  ";
		}
		cout << endl;
	}
}

bool Track::isOnTrack(double x, double y) {

	return true;
}
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

	// First corner set up
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

	// Second corner set up
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

	// Third corner set up
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

	// Fourth corner set up
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

	// Create map copy to work with
	char** gridCopy = new char* [20];
	for (int i = 0; i < 20; ++i) {
		gridCopy[i] = new char[20];
	}

	for (int i = 0; i < 20; ++i) {
		for (int j = 0; j < 20; ++j) {
			gridCopy[i][j] = grid[i][j];
		}
	}

	char currentChar = gridCopy[p1[1]][p1[0]];
	char endChar = gridCopy[p2[1]][p2[0]];

	// Track maket
	int* current = new int [2] {p1[0]+forward.at(currentChar)[0], p1[1]+forward.at(currentChar)[1]};
	int* endPos = new int [2] {p2[0]+backward.at(endChar)[0], p2[1]+backward.at(endChar)[1]};

	random_device dev;
	mt19937 rng(dev());
	uniform_int_distribution<mt19937::result_type> dist10(1, 10);
	while (current[0] != endPos[0] || current[1] != endPos[1]) {
		gridCopy[current[1]][current[0]] = 'z';

		int xMul = 0;
		if (current[0] - endPos[0] != 0) {
			xMul = (endPos[0] - current[0]) / abs(endPos[0] - current[0]);
		}

		int yMul = 0;
		if (current[1] - endPos[1] != 0) {
			yMul = (endPos[1] - current[1]) / abs(endPos[1] - current[1]);
		}

		int s = dist10(rng);
		if (s <= 5) {
			if (gridCopy[current[1]][current[0]+xMul] == '0') {
				current[0] += xMul;
			}
		}
		else {
			if (gridCopy[current[1]+yMul][current[0]] == '0') {
				current[1] += yMul;
			}
		}
	}
	gridCopy[current[1]][current[0]] = 'z';

	// Set pointers for track filling
	int* previous = new int[2] {p1[0], p1[1]};
	current[0] = p1[0] + forward.at(currentChar)[0];
	current[1] = p1[1] + forward.at(currentChar)[1];
	int* next = new int[2] {0, 0};

	// Set up priority for each direction
	int* priority1 = new int[2] {0, 0};
	int* priority2 = new int[2] {0, 0};
	int* priority3 = new int[2] {0, 0};

	switch (gridCopy[previous[1]][previous[0]])
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
		priority1[1] = 1;
		priority2[0] = -1;
		priority3[1] = -1;
		break;
	case 'd':
		priority1[0] = -1;
		priority2[1] = -1;
		priority3[0] = 1;
		break;
	}

	// Track filling
	while (true) {
		int priority1x = current[0] + priority1[0];
		int priority1y = current[1] + priority1[1];
		int priority2x = current[0] + priority2[0];
		int priority2y = current[1] + priority2[1];		
		int priority3x = current[0] + priority3[0];
		int priority3y = current[1] + priority3[1];

		// Find top priority cell available
		if (priority1x >= 0 && priority1x <= 19 && priority1y >= 0 && priority1y <= 19 && (gridCopy[priority1y][priority1x] == 'z' || (priority1x == p2[0] && priority1y == p2[1]))) {
			next[0] = priority1x;
			next[1] = priority1y;
		}
		else if (priority2x >= 0 && priority2x <= 19 && priority2y >= 0 && priority2y <= 19 && (gridCopy[priority2y][priority2x] == 'z' || (priority2x == p2[0] && priority2y == p2[1]))) {
			next[0] = priority2x;
			next[1] = priority2y;
		}
		else if (priority3x >= 0 && priority3x <= 19 && priority3y >= 0 && priority3y <= 19 && (gridCopy[priority3y][priority3x] == 'z' || (priority3x == p2[0] && priority3y == p2[1]))) {
			next[0] = priority3x;
			next[1] = priority3y;
		}

		// Find cells that has appropriate back and forwars biases
		vector<char> variants;
		for (const auto& [c, bias] : backward) {
			if (bias[0] == previous[0] - current[0] && bias[1] == previous[1] - current[1]) {
				if (forward.at(c)[0] == next[0] - current[0] && forward.at(c)[1] == next[1] - current[1]) {
					variants.push_back(c);
				}
			}
		}

		// Choosing random variant
		auto it = variants.cbegin();
		int random = rand() % variants.size();
		gridCopy[current[1]][current[0]] = *(it + random);

		// Moving pointers
		previous[0] = current[0];
		previous[1] = current[1];
		current[0] = next[0];
		current[1] = next[1];

		// Run until the end
		if (current[0] == p2[0] && current[1] == p2[1]) {
			break;
		}
	}

	// Swap to original
	for (int i = 0; i < 20; ++i) {
		for (int j = 0; j < 20; ++j) {
			if (gridCopy[i][j] != '0') grid[i][j] = gridCopy[i][j];
		}
	}

	delete[] gridCopy;
	delete[] priority1;
	delete[] priority2;
	delete[] priority3;
	delete[] previous;
	delete[] current;
	delete[] next;
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
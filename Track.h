#include <algorithm>
#include <functional>
#include <random>
#include <vector>
#include <map>
#include <time.h>
#include <iostream>

using namespace std;

#pragma once
class Track
{
private:
	char** grid;

	int* corner1;
	int* corner2;
	int* corner3;
	int* corner4;

	const map<char, vector<char>> fit{ { 'a', vector<char> {'b', 'i', 'm'}},
								{ 'b', vector<char> {'c', 'j', 'n'}},
								{ 'c', vector<char> {'d', 's', 'k'}},
								{ 'd', vector<char> {'a', 'l', 't'}},
								{ 'e', vector<char> {'i', 'f', 'q'}},
								{ 'f', vector<char> {'g', 'j', 'r'}},
								{ 'g', vector<char> {'h', 's', 'o'}},
								{ 'h', vector<char> {'e', 't', 'p'}},
								{ 'i', vector<char> {'b', 'f', 'm', 'q', 'i'}},
								{ 'j', vector<char> {'c', 'g', 'n', 'r', 'j'}},
								{ 'k', vector<char> {'n', 'j', 'c'}},
								{ 'l', vector<char> {'d', 's', 'k'}},
								{ 'm', vector<char> {'a', 'l', 't'}},
								{ 'n', vector<char> {'b', 'i', 'm'}},
								{ 'o', vector<char> {'g', 'j', 'r'}},
								{ 'p', vector<char> {'h', 's', 'o'}},
								{ 'q', vector<char> {'e', 't', 'p'}},
								{ 'r', vector<char> {'i', 'f', 'q'}},
								{ 's', vector<char> {'d', 'h', 'o', 'k', 's'}},
								{ 't', vector<char> {'a', 'e', 'l', 'p', 't'}} };

	const map<char, int*> forward{ { 'a', new int [2] {1, 0}},
								{ 'b', new int [2] {0, 1} },
								{ 'c', new int [2] {-1, 0} },
								{ 'd', new int [2] {0, -1} },
								{ 'e', new int [2] {1, 0} },
								{ 'f', new int [2] {0, 1} },
								{ 'g', new int [2] {-1, 0} },
								{ 'h', new int [2] {0, -1} },
								{ 'i', new int [2] {1, 0} },
								{ 'j', new int [2] {0, 1} },
								{ 'k', new int [2] {0, 1} },
								{ 'l', new int [2] {-1, 0} },
								{ 'm', new int [2] {0, -1} },
								{ 'n', new int [2] {1, 0} },
								{ 'o', new int [2] {0, 1} },
								{ 'p', new int [2] {-1, 0} },
								{ 'q', new int [2] {0, -1} },
								{ 'r', new int [2] {1, 0} },
								{ 's', new int [2] {-1, 0} },
								{ 't', new int [2] {0, -1} } };

	const map<char, int*> backward{ { 'a', new int [2] {0, 1}},
								{ 'b', new int [2] {-1, 0} },
								{ 'c', new int [2] {0, -1} },
								{ 'd', new int [2] {1, 0} },
								{ 'e', new int [2] {0, 1} },
								{ 'f', new int [2] {-1, 1} },
								{ 'g', new int [2] {0, -1} },
								{ 'h', new int [2] {1, 0} },
								{ 'i', new int [2] {-1, 0} },
								{ 'j', new int [2] {0, -1} },
								{ 'k', new int [2] {1, 0} },
								{ 'l', new int [2] {0, 1} },
								{ 'm', new int [2] {-1, 0} },
								{ 'n', new int [2] {0, -1} },
								{ 'o', new int [2] {1, 0} },
								{ 'p', new int [2] {0, 1} },
								{ 'q', new int [2] {-1, 0} },
								{ 'r', new int [2] {-1, 0} },
								{ 's', new int [2] {1, 0} },
								{ 't', new int [2] {0, 1} } };

	void createPath(int* point1, int* point2);

public:
	Track(int length);

	bool isOnTrack(double x, double y);
	bool whereOut(double x1, double y1, double x2, double y2, double& xOut, double& yOut);

	void print();
};


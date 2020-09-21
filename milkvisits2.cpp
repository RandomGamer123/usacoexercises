/*
ID: your_id_here
TASK: test
LANG: C++
*/
/* LANG can be C++11 or C++14 for those more recent releases */
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int N, M;
bool cowtypes[100000]; /* false = G, true = H */
int paths[99999][2];
int currentfindval = 0;
bool checkfound = false;

bool comparecheck(int numtoadd) {
	if (numtoadd == currentfindval) {
		checkfound = true;
		return true;
	}
	return false;
}

void iterategroup(int curstart, bool targetcowtype, int previousnumber) { 
	if (checkfound) {
		return;
	}
	for (int i = 0; i < (N - 1); i++) {
		bool pathvalid = false;
		int pathnotmatchnum = 0;
		if (paths[i][0] == curstart) {
			if (paths[i][1] == previousnumber) {
				continue;
			}
			if (cowtypes[paths[i][1] - 1] == targetcowtype) {
				if (comparecheck(paths[i][1])) {
					return;
				}
			}
			else {
				continue;
			}
			pathvalid = true;
			pathnotmatchnum = 1;
		}
		else if (paths[i][1] == curstart) {
			if (paths[i][0] == previousnumber) {
				continue;
			}
			if (cowtypes[paths[i][0] - 1] == targetcowtype) {
				if (comparecheck(paths[i][0])) {
					return;
				}
			}
			else {
				continue;
			}
			pathvalid = true;
		}
		if (pathvalid == false) {
			continue;
		}
		iterategroup(paths[i][pathnotmatchnum], targetcowtype, curstart);
		if (checkfound) {
			return;
		}
	}
}

bool happy(int endpointa, int endpointb, bool cowtype) {
	bool cowtypea, cowtypeb;
	cowtypea = cowtypes[endpointa - 1];
	cowtypeb = cowtypes[endpointb - 1];
	currentfindval = endpointb;
	checkfound = false;
	if (cowtypea == cowtype) {
		return true;
	}
	if (cowtypeb == cowtype) {
		return true;
	}
	if (endpointa == endpointb) {
		return false;
	}
	iterategroup(endpointa, cowtypea, -1);
	if (checkfound) {
		return false;
	}
	return true;
}

bool parsechar(char cowtype) {
	if (cowtype == 'G') {
		return false;
	}
	else {
		return true;
	}
}

int main() {
	ofstream fout("milkvisits.out");
	ifstream fin("milkvisits.in");
	fin >> N >> M;
	char placeholder;
	string output;
	for (int i = 0; i < N; i++) {
		fin >> placeholder;
		cowtypes[i] = parsechar(placeholder);
	}
	for (int i = 0; i < (N - 1); i++) {
		fin >> paths[i][0] >> paths[i][1];
	}
	int endpointa, endpointb;
	for (int i = 0; i < M; i++) {
		fin >> endpointa >> endpointb;
		fin >> placeholder;
		if (happy(endpointa, endpointb, parsechar(placeholder))) {
			output += "1";
		}
		else {
			output += "0";
		}
	}
	fout << output << endl;
	cout << "Done";
	int stall;
	cin >> stall;
	return 0;
}
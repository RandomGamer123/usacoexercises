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

int iteratepath(int curstart, int targetend, int previousnumber) { /* Return codes: 0 -> failure, 1 -> success, only G found ; 2 -> success, only H found; 3 -> success, only G and H found*/
	for (int i = 0; i < (N - 1); i++) {
		bool pathvalid = false;
		int pathnotmatchnum = 0; 
		if (paths[i][0] == curstart) {
			if (paths[i][1] == previousnumber) {
				continue;
			}
			if (paths[i][1] == targetend) {
				if (cowtypes[targetend-1]) {
					return 2; /* found successful path, cow type is H*/
				}
				else {
					return 1; /* found successful path, cow type is G*/
				}
			}
			pathvalid = true;
			pathnotmatchnum = 1;
		}
		else if (paths[i][1] == curstart) {
			if (paths[i][0] == previousnumber) {
				continue;
			}
			if (paths[i][0] == targetend) {
				if (cowtypes[targetend-1]) {
					return 2; /* found successful path, cow type is H*/
				}
				else {
					return 1; /* found successful path, cow type is G*/
				}
			}
			pathvalid = true;
		}
		if (pathvalid == false) {
			continue;
		}
		int returnstatus = iteratepath(paths[i][pathnotmatchnum], targetend, curstart);
		if (returnstatus == 0) {
			continue;
		}
		else if (returnstatus == 3) {
			return 3;
		}
		else if (returnstatus == 1) { /*Successful path found with only type G cows*/
			if (cowtypes[curstart-1]) { /* This cow is type H */
				return 3;
			}
			else {
				return 1;
			}
		}
		else { /*Successful path found with only type H cows*/
			if (cowtypes[curstart-1]) { /* This cow is type H */
				return 2;
			}
			else {
				return 3;
			}
		}
	} /* If loop finishes, no successful path was found */
	return 0;
}

bool happy(int endpointa, int endpointb, bool cowtype) {
	bool cowtypea, cowtypeb;
	cowtypea = cowtypes[endpointa-1];
	cowtypeb = cowtypes[endpointb-1];
	if (cowtypea == cowtype) {
		return true;
	}
	if (cowtypeb == cowtype) {
		return true;
	}
	if (endpointa == endpointb) {
		return false;
	}
	int pathresult = iteratepath(endpointa, endpointb, -1);
	if (pathresult == 3) {
		return true;
	}
	if (pathresult == 2 && cowtype == true) {
		return true;
	}
	if (pathresult == 1 && cowtype == false) {
		return true;
	}
	if (pathresult == 0) {
		cout << "Logic error!";
	}
	return false;
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
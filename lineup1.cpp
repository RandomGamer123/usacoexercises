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

int N;
int restrictionsnum[7][2];
bool success = false;
string correctstring = "";
const int cowcount = 8;
string cows[8] = {"Beatrice","Belinda","Bella","Bessie","Betsy","Blue","Buttercup","Sue"};

void testrestrictions(string currenttest) { 
	for (int i = 0; i < N; i++) {
		int compareposa = 0;
		int compareposb = 0;
		for (int j = 0; j < cowcount; j++) {
			if ((currenttest.at(j)- '0') == restrictionsnum[i][0]) {
				compareposa = j;
			} else if ((currenttest.at(j) - '0') == restrictionsnum[i][1]) {
				compareposb = j;
			}
		}
		if (((compareposa - 1) != compareposb) && ((compareposa +1) != compareposb)) {
			return;
		}
	}
	success = true;
	correctstring = currenttest;
	return;
}

void iteratecows(int step, string unusednumbers, string coworder) {
	if (success == true) {
		return;
	}
	if (step == 0) {
		testrestrictions(coworder);
		return;
	}
	for (int i = 0; i < step; i++) {
		iteratecows(step-1,unusednumbers.substr(0,i-0)+unusednumbers.substr(i+1,step-i-1),coworder + unusednumbers.at(i));
	}
	return;
}

int cownametonum(string cow) {
	for (int i = 0; i < cowcount; i++) {
		if (cows[i] == cow) {
			return i;
		}
	}
	return -1;
}

int main() {
	ofstream fout("lineup.out");
	ifstream fin("lineup.in");
	fin >> N;
	string restrictions[7][2];
	for (int i = 0; i < N; i++) {
		string dummy;
		fin >> restrictions[i][0] >> dummy >> dummy >> dummy >> dummy >> restrictions[i][1];
		restrictionsnum[i][0] = cownametonum(restrictions[i][0]);
		restrictionsnum[i][1] = cownametonum(restrictions[i][1]);
	}
	iteratecows(8, "01234567", "");
	for (int i = 0; i < cowcount; i++) {
		fout << cows[correctstring.at(i) - '0'] << endl;
	}
	int hold;
	cin >> hold;
	return 0;
}
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

int main() {
	ofstream fout("moobuzz.out");
	ifstream fin("moobuzz.in");
	fin >> N;
#if 0 /* This method will timeout on larger numbers of N*/
	int i = 1, counter = 0;
	while (true) {
		if ((i % 3 != 0) && (i % 5 != 0)) {
			counter++;
		}
		if (counter == N) {
			break;
		}
		i++;
	}
	fout << i << endl;
#endif
#if 1
	int mainpart = N / 8;
	mainpart *= 15;
	int remainder = N % 8;
	if (remainder == 0) {
		remainder = 8;
		mainpart -= 15;
	}
	int lclcounter = 0;
	for (int i = 1; i <= 15; i++) {
		if ((i % 3 != 0) && (i % 5 != 0)) {
			lclcounter++;
		}
		if (lclcounter == remainder) {
			mainpart += i;
			break;
		}
	}
	fout << mainpart << endl;
#endif
	int stall;
	cin >> stall;
	return 0;
}
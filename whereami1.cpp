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
string colors;

int main() {
	ofstream fout("whereami.out");
	ifstream fin("whereami.in");
	fin >> N;
	fin >> colors;
	string test_substrings[100];
	for (int test_k = 1; test_k <= N; test_k++) {
		bool conflict = false;
		for (int current_test_start = 0; current_test_start <= N - test_k; current_test_start++) {
			string compared_substr = colors.substr(current_test_start, test_k);
			cout << compared_substr << endl;
			for (int compare_test = 0; compare_test < current_test_start; compare_test++) {
				cout << compared_substr << " " << test_substrings[compare_test] << endl;
				if (compared_substr == test_substrings[compare_test]) {
					cout << "conflict" << endl;
					conflict = true;
					break;
				}
			}
			if (conflict == true) {
				break;
			}
			cout << current_test_start << endl;
			test_substrings[current_test_start] = compared_substr;
		}
		if (conflict == false) {
			fout << test_k << endl;
			return 0;
		}
	}
	int hold;
	cin >> hold;
	return 0;
}
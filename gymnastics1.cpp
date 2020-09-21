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

int K, N;

int data1[10][20];

bool isconsistent(int cowa, int cowb) {
	cout << cowa << " " << cowb << endl;
	int status = 0;
	for (int session = 0; session < K; session++) {
		for (int cowloop = 0; cowloop < N; cowloop++) {
			if (data1[session][cowloop] == cowa) {
				if (status == 0) {
					status = 1;
					break;
				}
				else if (status == 2) {
					return false;
				}
				else {
					break;
				}
			}
			if (data1[session][cowloop] == cowb) {
				if (status == 0) {
					status = 2;
					break;
				}
				else if (status == 1) {
					return false;
				}
				else {
					break;
				}
			}
		}
	}
	cout << "true" << endl;
	return true;
}

int main() {
	ofstream fout("gymnastics.out");
	ifstream fin("gymnastics.in");
	fin >> K >> N;
	int count = 0;
	cout << K << endl << N << endl;
	for (int session = 0; session < K; session++) {
		for (int cow = 0; cow < N; cow++) {
			fin >> data1[session][cow];
			cout << data1[session][cow];
		}
		cout << endl;
	}
	for (int cowa = 1; cowa <= N; cowa++) {
		for (int cowb = cowa + 1; cowb <= N; cowb++) {
			if (isconsistent(cowa, cowb)) {
				count++;
			}
		}
	}
	fout << count << endl;
	return 0;
}
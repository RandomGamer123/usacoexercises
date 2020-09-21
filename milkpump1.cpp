/*
ID: your_id_here
TASK: test
LANG: C++
*/
/* LANG can be C++11 or C++14 for those more recent releases */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int N, M;
bool visited[1001] = { false }; /* false = unvisited, true = visited */
vector<int> tentvals[2001] = { vector<int>(1,-1) }; /* int[n*2-1] = total cost of item n, int[n*2] = flow rate of item n*/
vector<short> pipes[3001]; /* short[n*3-2] = dest, short[n*3-1] = cost, short[n*3] = flowrate */

short extractmin() {
	short curmin;
	float foc = -1;
	for (short i = 1; i <= 1000; i++) {
		if (visited[i]) {
			continue;
		}
		if (tentvals[i * 2].size() == 0) {
			continue;
		}
		float comparefoc = (float)tentvals[i * 2][0] / (float)tentvals[i * 2 - 1][0];
		if (comparefoc > foc) {
			foc = comparefoc;
			curmin = i;
		}
	}
	return(curmin);
}

void djikstra(short currentnode) {
	if (visited[N] == true) {
		return;
	}
	for (size_t i = 0; i != pipes[currentnode * 3 - 2].size(); i++) {
		short dest = pipes[currentnode * 3 - 2][i];
		if (visited[dest]) {
			continue;
		}
		vector<int> reptvalues[2]; /* ccost = reptvalues[0], crate = reptvalues[1] */
		vector<bool> push_c;
		size_t push_c_targetsize = tentvals[currentnode * 2 - 1].size();
		push_c.reserve(push_c_targetsize);
		vector<bool> push_d;
		size_t push_d_targetsize = tentvals[dest * 2 - 1].size();
		push_d.reserve(push_d_targetsize);
		for (size_t i = 0; i < push_c_targetsize; i++) {
			push_c.push_back(false);
		}
		for (size_t i = 0; i < push_d_targetsize; i++) {
			push_d.push_back(false);
		}
		for (size_t j = 0; j != tentvals[currentnode*2-1].size(); j++) {
			int ccost = tentvals[currentnode * 2 - 1][j];
			int crate = tentvals[currentnode * 2][j];
			ccost += pipes[currentnode * 3 - 1][i];
			crate = min(crate, (int)pipes[currentnode * 3][i]);
			if (tentvals[dest * 2 - 1].size() == 0) {
				if (push_c[j]) {
					continue;
				}
				push_c[j] = true;
				reptvalues[0].push_back(ccost);
				reptvalues[1].push_back(crate);
				continue;
			}
			for (size_t k = 0; k != tentvals[dest * 2 - 1].size(); k++) {
				int dcost = tentvals[dest * 2 - 1][k];
				int drate = tentvals[dest * 2][k];
				if (dcost == -1) {
					if (push_c[j]) {
						continue;
					}
					push_c[j] = true;
					reptvalues[0].push_back(ccost);
					reptvalues[1].push_back(crate);
					continue;
				}
				if (ccost <= dcost && crate >= drate) {
					if (push_c[j]) {
						continue;
					}
					push_c[j] = true;
					reptvalues[0].push_back(ccost);
					reptvalues[1].push_back(crate);
					continue;
				}
				if (dcost <= ccost && drate >= crate) {
					if (push_d[k]) {
						continue;
					}
					push_d[k] = true;
					reptvalues[0].push_back(dcost);
					reptvalues[1].push_back(drate);
					continue;
				}
				if (!push_c[j]) {
					reptvalues[0].push_back(ccost);
					reptvalues[1].push_back(crate);
					push_c[j] = true;
				}
				if (!push_d[k]) {
					reptvalues[0].push_back(dcost);
					reptvalues[1].push_back(drate);
					push_d[k] = true;
				}
			}
		}
		tentvals[dest * 2 - 1] = reptvalues[0];
		tentvals[dest * 2] = reptvalues[1];
	}
	visited[currentnode] = true;
	if (visited[N] == true) {
		return;
	}
	djikstra(extractmin());
}

int main() {
	ofstream fout("pump.out");
	ifstream fin("pump.in");
	fin >> N >> M;
	short placeholder_origin, placeholder_dest, placeholder_cost, placeholder_flowrate;
	for (int i = 1; i <= M; i++) {
		fin >> placeholder_origin >> placeholder_dest >> placeholder_cost >> placeholder_flowrate;
		pipes[placeholder_origin * 3 - 2].push_back(placeholder_dest);
		pipes[placeholder_origin * 3 - 1].push_back(placeholder_cost);
		pipes[placeholder_origin * 3].push_back(placeholder_flowrate);
		pipes[placeholder_dest * 3 - 2].push_back(placeholder_origin);
		pipes[placeholder_dest * 3 - 1].push_back(placeholder_cost);
		pipes[placeholder_dest * 3].push_back(placeholder_flowrate);
	}
	tentvals[1] = vector<int>(1, 0);
	tentvals[2] = vector<int>(1, 0x7FFFFFFF);
	djikstra(1);
	float curfoc = 0;
	float comparefoc = 0;
	for (size_t i = 0; i != tentvals[N * 2].size(); i++) {
		comparefoc = (float)tentvals[N * 2][i] / (float)tentvals[N * 2 - 1][i];
		if (comparefoc > curfoc) {
			curfoc = comparefoc;
		}
	}
	curfoc *= 1000000;
	fout << (int)curfoc << endl;
	cout << "Done";
	int stall;
	cin >> stall;
	return 0;
}
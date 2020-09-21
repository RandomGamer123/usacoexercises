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
bool cowtypes[100001]; /* false = G, true = H */
//int paths[99999][2];
vector<int> paths[100001];
bool discovered[100001] = { false };
vector<int> changes;
int groupnumber;
//vector<int> pathsgroup[100001];

#if 0
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
	for (vector<int>::iterator it = paths[curstart].begin(); it != paths[curstart].end(); it++) {
		if (*it == previousnumber) {
			continue;
		}
		if (cowtypes[*it] == targetcowtype) {
			if (comparecheck(*it)) {
				return;
			}
		}
		else {
			continue;
		}
		iterategroup(*it, targetcowtype, curstart);
		if (checkfound) {
			return;
		}
	}
	/*
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
	*/
}
#endif

#if 0
void iterateadd(int endpointa, int endpointb, int previousnumber) {
	for (vector<int>::iterator it = pathsgroup[endpointa].begin(); it != pathsgroup[endpointa].end(); it++) {
		if (*it == previousnumber) {
			continue;
		}
		iterateadd(*it, endpointb, endpointa);
		pathsgroup[*it].push_back(endpointb);
	}
	pathsgroup[endpointa].push_back(endpointb);
}
#endif

#if 0
void iterateaddgroup(int addterm, int loopthrough, int previousnumber) {
	for (vector<int>::iterator it = paths[loopthrough].begin(); it != paths[loopthrough].end(); it++) {
		if (previousnumber == *it) {
			continue;
		}
		if (cowtypes[addterm] != cowtypes[*it]) {
			continue;
		}
		pathsgroup[addterm].push_back(*it);
		iterateaddgroup(addterm, *it, loopthrough);
	}
	return;
}
#endif

#if 0
void iterateaddgroup2(int addterm, int loopthrough, int previousnumber, bool useorig) {
	if (useorig) {
		for (vector<int>::iterator it = originalcopy.begin(); it != originalcopy.end(); it++) {
			if (previousnumber == *it) {
				continue;
			}
			if (cowtypes[addterm] != cowtypes[*it]) {
				continue;
			}
			iterateaddgroup2(addterm, *it, loopthrough, false);
		}
	}
	else {
		for (vector<int>::iterator it = paths[loopthrough].begin(); it != paths[loopthrough].end(); it++) {
			if (previousnumber == *it) {
				continue;
			}
			if (cowtypes[addterm] != cowtypes[*it]) {
				continue;
			}
			if (find(paths[addterm].begin(), paths[addterm].end(), *it) == paths[addterm].end()) {
				paths[addterm].push_back(*it);
				iterateaddgroup2(addterm, *it, loopthrough, false);
			}
		}
	}
	return;
}
#endif

void iterateaddgroup3(int start, bool targetcowtype) {
	discovered[start] = true;
	changes.push_back(start);
	for (vector<int>::iterator it = paths[start].begin(); it != paths[start].end(); it++) {
		if (cowtypes[*it] != targetcowtype) {
			continue;
		}
		if (!(discovered[*it])) {
			iterateaddgroup3(*it, targetcowtype);
		}
	}
	return;
}

void changepaths() {
	vector<int> groupnum (1,groupnumber);
	for (vector<int>::iterator it = changes.begin(); it != changes.end(); it++) {
		paths[*it] = groupnum;
	}
	changes.clear();
	return;
}

bool happy(int endpointa, int endpointb, bool cowtype) {
	bool cowtypea, cowtypeb;
	cowtypea = cowtypes[endpointa];
	cowtypeb = cowtypes[endpointb];
	/*
	currentfindval = endpointb;
	checkfound = false;
	*/
	if (cowtypea == cowtype) {
		return true;
	}
	if (cowtypeb == cowtype) {
		return true;
	}
	if (endpointa == endpointb) {
		return false;
	}
	if (paths[endpointa] == paths[endpointb]) {
		return false;
	}
	/*
	iterategroup(endpointa, cowtypea, -1);
	if (checkfound) {
		return false;
	}
	*/
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
	for (int i = 1; i <= N; i++) {
		fin >> placeholder;
		cowtypes[i] = parsechar(placeholder);
	}
	int endpointa, endpointb;
	for (int i = 0; i < (N - 1); i++) {
		//fin >> paths[i][0] >> paths[i][1];
		fin >> endpointa >> endpointb;
		if (cowtypes[endpointa] == cowtypes[endpointb]) {
			paths[endpointa].push_back(endpointb);
			paths[endpointb].push_back(endpointa);
			/*
			iterateadd(endpointa, endpointb, -1);
			iterateadd(endpointb, endpointa, -1);
			for (vector<int>::iterator it = pathsgroup[endpointa].begin(); it != pathsgroup[endpointa].end(); it++) {
				pathsgroup[*it].push_back(endpointb);
			}
			for (vector<int>::iterator it = pathsgroup[endpointb].begin(); it != pathsgroup[endpointb].end(); it++) {
				pathsgroup[*it].push_back(endpointa);
			}
			pathsgroup[endpointa].push_back(endpointb);
			pathsgroup[endpointb].push_back(endpointa);
			*/
		}
	}
	for (int i = 1; i <= N; i++) {
		if (discovered[i] == true) {
			continue;
		}
		groupnumber++;
		iterateaddgroup3(i,cowtypes[i]);
		changepaths();
	}
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
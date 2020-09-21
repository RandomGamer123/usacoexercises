#if 0

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
#include <cstring>

using namespace std;

int N, M;
int cowtypes[100001]; 
//int paths[99999][2];
vector<int> paths[100001];
int groups[100001];
bool discovered[100001] = { false };
vector<int> changes;
vector<int> pathsumchanges;
int groupnumber;
bool dfslocated = false;
bool cowtypefound = false;
bool changemode = false; //false = only update groups; true = only update paths
bool added[100001];
vector<int> grouppaths[100001];
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

void dfsgrouped(int endpointa, int groupendpointb, int cowtype, bool cowtypelocated) {
	if (dfslocated) {
		return;
	}
	discovered[groups[endpointa]] = true;
	for (vector<int>::iterator it = grouppaths[groups[endpointa]].begin(); it != grouppaths[groups[endpointa]].end(); it++) {
		if (groups[*it] == groupendpointb) {
			cowtypefound = cowtypelocated;
			dfslocated = true;
			return;
		}
		if (!(discovered[groups[*it]])) {
			if (cowtypes[*it] == cowtype) {
				dfsgrouped(*it, groupendpointb, cowtype, true);
			}
			else {
				dfsgrouped(*it, groupendpointb, cowtype, cowtypelocated);
			}
		}
	}
	return;
}

void iterateaddgroup3(int start, int targetcowtype) {
	discovered[start] = true;
	changes.push_back(start);
	for (vector<int>::iterator it = paths[start].begin(); it != paths[start].end(); it++) {
		if (cowtypes[*it] != targetcowtype) {
			if (changemode) {
				if (!(added[groups[*it]])) {
					pathsumchanges.push_back(*it);
					added[groups[*it]] = true;
					continue;
				}
			}
			continue;
		}
		if (!(discovered[*it])) {
			iterateaddgroup3(*it, targetcowtype);
		}
	}
	return;
}

void changepaths() {
	for (vector<int>::iterator it = changes.begin(); it != changes.end(); it++) {
		if (changemode) {
			grouppaths[groups[*it]] = pathsumchanges;
			break;
		}
		else {
			groups[*it] = groupnumber;
		}
	}
	changes.clear();
	pathsumchanges.clear();
	return;
}

bool happy(int endpointa, int endpointb, int cowtype) {
	int cowtypea, cowtypeb;
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
	if (groups[endpointa] == groups[endpointb]) {
		return false;
	}
	memset(discovered, false, 100001);
	dfslocated = false;
	cowtypefound = false;
	dfsgrouped(endpointa, groups[endpointb], cowtype, false);
	if (cowtypefound) {
		return true;
	}
	else {
		return false;
	}
	/*
	iterategroup(endpointa, cowtypea, -1);
	if (checkfound) {
		return false;
	}
	return true;
	*/
}

int main() {
	ofstream fout("milkvisits.out");
	ifstream fin("milkvisits.in");
	fin >> N >> M;
	int placeholder;
	string output;
	for (int i = 1; i <= N; i++) {
		fin >> placeholder;
		cowtypes[i] = placeholder;
	}
	int endpointa, endpointb;
	for (int i = 0; i < (N - 1); i++) {
		//fin >> paths[i][0] >> paths[i][1];
		fin >> endpointa >> endpointb;
		paths[endpointa].push_back(endpointb);
		paths[endpointb].push_back(endpointa);
	}
	for (int i = 1; i <= N; i++) {
		if (discovered[i] == true) {
			continue;
		}
		groupnumber++;
		iterateaddgroup3(i, cowtypes[i]);
		changepaths();
	}
	changemode = true;
	memset(discovered, false, 100001);
	groupnumber = 0;
	for (int i = 1; i <= N; i++) {
		if (discovered[i] == true) {
			continue;
		}
		groupnumber++;
		iterateaddgroup3(i, cowtypes[i]);
		changepaths();
		memset(added, false, 100001);
	}
	for (int i = 0; i < M; i++) {
		fin >> endpointa >> endpointb;
		fin >> placeholder;
		if (happy(endpointa, endpointb, placeholder)) {
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


#endif

#if 0
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cassert>
#include <array>
//#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pi;
typedef vector<int> vi;
typedef vector<pi> vpi;

#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define F0R(i, a) for (int i = 0; i < (a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= (a); i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
#define trav(a, x) for (auto& a : x)

#define mp make_pair
#define pb push_back
#define f first
#define s second

#define sz(x) (int)x.size()
#define all(x) begin(x), end(x)
#define rsz resize

const int MX = 100005;


#if 0
void setIO(string name) {
	ios_base::sync_with_stdio(0); cin.tie(0);
	freopen((name + ".in").c_str(), "r", stdin);
	freopen((name + ".out").c_str(), "w", stdout);
}
#endif

int N, M, T[MX], C[MX];
bool ok[MX];
vi adj[MX];
array<int, 2> dat[MX];
vi todo[MX];
pi range[MX];

int co = 0;
void dfs(int x, int y) {
	range[x].f = co++;
	trav(t, adj[x]) if (t != y) dfs(t, x);
	range[x].s = co - 1;
}

vpi stor[MX];
vi ord;

bool anc(int a, int b) {
	return range[a].f <= range[b].f && range[b].s <= range[a].s;
}

void dfs2(int x, int y) {
	stor[T[x]].pb({ x,sz(ord) }); ord.pb(x);
	trav(t, todo[x]) if (sz(stor[C[t]])) {
		pi y = stor[C[t]].back();
		if (y.f == x) ok[t] = 1;
		else {
			int Y = ord[y.s + 1];
			// x is one of endpoints for query t
			assert(dat[t][0] == x || dat[t][1] == x);
			if (!anc(Y, dat[t][0] + dat[t][1] - x)) ok[t] = 1;
		}
	}
	trav(t, adj[x]) if (t != y) dfs2(t, x);
	stor[T[x]].pop_back(); ord.pop_back();
}

int main() {
	ofstream fout("milkvisits.out");
	ifstream fin("milkvisits.in");
	fin >> N >> M;
	FOR(i, 1, N + 1) fin >> T[i];
	F0R(i, N - 1) {
		int A, B; fin >> A >> B;
		adj[A].pb(B), adj[B].pb(A);
	}
	dfs(1, 0);
	F0R(i, M) {
		fin >> dat[i][0] >> dat[i][1] >> C[i];
		F0R(j, 2) todo[dat[i][j]].pb(i);
	}
	dfs2(1, 0);
	F0R(i, M) {
		if (ok[i]) fout << 1;
		else fout << 0;
	}
	fout << "\n";
}
#endif
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
#include <tuple>
#include <cstring>

using namespace std;

int N, M;
int cowtypes[100001];
int order = 0;
int getorder[100001];
int dfstraversed[100001];
vector<tuple<int, int, int>> listqueries[100001];
//int paths[99999][2];
vector<int> paths[100001];
bool discovered[100001] = { false };
//int groupnumber;
int depth = 0;
string output(100000, '0');
vector<pair<int, int>> passedmatch[100001];
vector<int> ancestors;
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

void dfsaddorder(int start) {
	depth++;
	discovered[start] = true;
	getorder[start] = order;
	dfstraversed[order] = (depth);
	order++;
	for (vector<int>::iterator it = paths[start].begin(); it != paths[start].end(); it++) {
		if (!(discovered[*it])) {
			dfsaddorder(*it);
		}
	}
	depth--;
	return;
}

#if 0
void changepaths() {
	vector<int> groupnum(1, groupnumber);
	for (vector<int>::iterator it = changes.begin(); it != changes.end(); it++) {
		paths[*it] = groupnum;
	}
	changes.clear();
	return;
}
#endif

#if 0
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
#endif

#if 0
bool parsechar(char cowtype) {
	if (cowtype == 'G') {
		return false;
	}
	else {
		return true;
	}
}
#endif

bool isancestor(int basecheck, int ancestor) {
	int curorder = getorder[basecheck];
	int targetorder = getorder[ancestor];
	if (targetorder > curorder) {
		return false;
	}
	int curdepth = dfstraversed[curorder];
	int targetdepth = dfstraversed[targetorder];
	if (targetdepth >= curdepth) {
		return false;
	}
	while (curdepth > targetdepth) {
		curorder--;
		curdepth = dfstraversed[curorder];
	}
	if (curorder == targetorder) {
		return true;
	} 
	return false;
}

void dfslogic(int start) {
	depth++;
	discovered[start] = true;
	ancestors.push_back(start);
	passedmatch[cowtypes[start]].push_back(make_pair(start, depth));
	for (vector<tuple<int, int, int>>::iterator it = listqueries[start].begin(); it != listqueries[start].end(); it++) {
		if (output[get<2>(*it)] == '1') {
			continue;
		}
		if (cowtypes[start] == get<1>(*it)) {
			output[get<2>(*it)] = '1';
			continue;
		}
		if (start == get<0>(*it)) {
			continue;
		}
		if (passedmatch[get<1>(*it)].size() == 0) {
			continue;
		}
		if (isancestor(get<0>(*it), get<0>(passedmatch[get<1>(*it)].back()))) {
			if (isancestor(get<0>(*it), ancestors[get<1>(passedmatch[get<1>(*it)].back())])) {
				continue;
			}
			else {
				output[get<2>(*it)] = '1';
				continue;
			}
		}
		else {
			output[get<2>(*it)] = '1';
			continue;
		}
	}
	for (vector<int>::iterator it = paths[start].begin(); it != paths[start].end(); it++) {
		if (!(discovered[*it])) {
			dfslogic(*it);
		}
	}
	passedmatch[cowtypes[start]].pop_back();
	ancestors.pop_back();
	depth--;
	return;
}

int main() {
	ofstream fout("milkvisits.out");
	ifstream fin("milkvisits.in");
	fin >> N >> M;
	output.resize(M);
	int placeholder;
	tuple<int, int, int> placeholder2;
	for (int i = 1; i <= N; i++) {
		fin >> placeholder;
		cowtypes[i] = placeholder;
	}
	int endpointa, endpointb;
	for (int i = 0; i < (N - 1); i++) {
		//fin >> paths[i][0] >> paths[i][1];
		fin >> endpointa >> endpointb;
		paths[endpointa].push_back(endpointb);
		paths[endpointb].push_back(endpointa);
	}
	dfsaddorder(1);
	for (int i = 0; i < M; i++) {
		fin >> endpointa >> endpointb;
		fin >> placeholder;
		listqueries[endpointa].push_back(make_tuple(endpointb, placeholder, i));
		listqueries[endpointb].push_back(make_tuple(endpointa, placeholder, i));
		/*
		if (happy(endpointa, endpointb, parsechar(placeholder))) {
			output += "1";
		}
		else {
			output += "0";
		}
		*/
	}
	memset(discovered, false, 100001);
	depth = 0;
	dfslogic(1);
	fout << output << endl;
	cout << "Done";
	int stall;
	cin >> stall;
	return 0;
}
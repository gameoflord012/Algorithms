#include <bits/stdc++.h>

using namespace std;

#define Cerr cerr << "\nTest: "
#define endl "\n"
#define mp make_pair
#define fi first
#define se second
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define fastio { ios_base::sync_with_stdio(false), cin.tie(NULL); }
#define forn(i, n) for(int i = 0; i < (int)(n); i++)
#define for1(i, n) for(int i = 1; i <= (int)(n); i++)
#define fore(i, a, b) for (int i = (int)(a); i <= (int)(b); i++)
#define ford(i, n) for (int i = (int)(n) - 1; i >= 0; --i)

#ifdef RICARDO
	#define bug(x) cerr << #x << " = " << (x) << endl;
	#define block if(1)
#else
	#define bug(x) "IDINGO"
	#define block if(0)
#endif


template<class T> bool mini(T &a, T b) { return a > b ? (a = b, true) : false; }
template<class T> bool maxi(T &a, T b) { return a < b ? (a = b, true) : false; }

typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<pii> vpi;
typedef vector<vi> vvi;
typedef long long i64;
typedef vector<i64> vi64;
typedef vector<vi64> vvi64;
typedef pair<i64, i64> pi64;
typedef double ld;

//=================================================CODE=================================================//
//https://codeforces.com/group/FLVn1Sc504/contest/274823/problem/Z
signed main(int argc, char* argv[])
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.precision(10);
	cout << fixed;
#ifdef RICARDO		
	freopen("i", "r", stdin);
#endif
	int n, m, s, t;
	cin >> n >> m >> s >> t;
	s--; t--;
			
	vvi G(n);
	vpi edges;
	vi C, F;

	forn(i, m) {
		int u, v, c; cin >> u >> v >> c;
		u--, v--;
		G[u].pb(i * 2);
		G[v].pb(i * 2 + 1);
		edges.pb({u, v});
		edges.pb({v, u});
		C.pb(c);
		C.pb(c);
		F.pb(0);
		F.pb(c);
	}

	auto bfs = [&](int s, int t) {
		vector<bool> was(n, 0);
		vi st;
		st.pb(s);
		was[s] = 1;
		vi flowCost(n, 0);
		flowCost[s] = INT_MAX;
		vi p(n, -1);

		bool ok = 0;
		forn(cur, st.size()) {
			int u = st[cur];
			for(int i : G[u]) {
				int v = edges[i].se;
				if(was[v] or C[i] - F[i] == 0) continue;
				p[v] = i;
				flowCost[v] = min(flowCost[u], C[i] - F[i]);
				was[v] = 1;
				st.pb(v);
			}
		}

		int cur = t;
		while(p[cur] >= 0) {
			int ed = p[cur];
			F[ed] += flowCost[t];
			F[ed ^ 1] -= flowCost[t];
			cur = edges[ed].first;
		}

		return flowCost[t];
	};

	int ans = 0;
	do {
		int add = bfs(s, t);
		if(add == 0) break;
		ans += add;		
	} while(1);
	

	cout << ans << endl;
#ifdef RICARDO
	cerr << "\nTime elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
#endif
}
#include <algorithm>
#include <bit>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <deque>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <ranges>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

using ll = int64_t;
using vl = vector<ll>;
using vs = vector<string>;
using vvl = vector<vl>;
using Pos = pair<ll, ll>;

constexpr auto kInf = numeric_limits<ll>::max() / 2;

ll C, R;
vs Map;
vvl dist;

vl dr{-1, 1, 0, 0};
vl dc{0, 0, -1, 1};

ll ans = kInf;
void solve() {
  queue<Pos> Q{};
  Q.push({0, 0});

  while (!Q.empty()) {
    auto [fr, fc] = Q.front();
    Q.pop();

    if (fr == R - 1 && fc == C - 1) {
      ans = min(ans, dist[fr][fc]);
    }

    const auto& dist_now = dist[fr][fc];
    for (auto d = 0; d < 4; ++d) {
      const auto& nr = fr + dr[d];
      const auto& nc = fc + dc[d];

      if (nr < 0 || R <= nr || nc < 0 || C <= nc) continue;

      if (Map[nr][nc] == '0') {
        if (dist_now < dist[nr][nc]) {
          dist[nr][nc] = dist_now;
          Q.push({nr, nc});
        }
      } else {
        if (dist_now + 1 < dist[nr][nc]) {
          dist[nr][nc] = dist_now + 1;
          Q.push({nr, nc});
        }
      }
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  cin >> C >> R;
  Map = vs(R);
  for (auto&& row : Map) cin >> row;

  dist = vvl(R, vl(C, kInf));
  dist[0][0] = 0;

  solve();
  cout << ans;

  return 0;
}
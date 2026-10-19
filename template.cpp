#include <bits/stdc++.h>
#include <atcoder/segtree>
using namespace std;
using namespace atcoder;
using ll = long long;
using pll = pair<ll, ll>;
using vl = vector<ll>;
using vvl = vector<vl>;
using vs = vector<string>;
using vp = vector<pll>;
using vb = vector<bool>;
using vvb = vector<vb>;

// 速さのため endl は "\n" にしている
// インタラクティブ問題では、出力のたびに cout << flush を足すこと
#define endl "\n"
#define rep(i, n) for (ll i = 0; i < (ll)(n); i++)
#define rep2(i, a, b) for (ll i = (a); i < (ll)(b); i++)
#define drep(i, n) for (ll i = (ll)(n) - 1; i >= 0; i--)
#define drep2(i, a, b) for (ll i = (ll)(b) - 1; i >= (ll)(a); i--)
#define nall(v) (v).begin(), (v).end()
#define rall(v) (v).rbegin(), (v).rend()
#define Yes cout << "Yes" << endl
#define No cout << "No" << endl

// -----------------------------------------------
// マクロ名: All_search(v)
// 機　能: v の並べ替えを全通り試す（v は中で並べ替えられる）
// 引　数: v = 並べ替える配列
// 使い方: vl p(n); iota(nall(p), 0LL); All_search(p) { ... }
// 注　意: n! 通りなので n は 8 程度まで
// -----------------------------------------------
#define All_search(v) for (bool _c = (sort(nall(v)), true); _c; _c = next_permutation(nall(v)))

// -----------------------------------------------
// マクロ名: dbg(x)
// 機　能: 変数名と値を cerr に出す（デバッグ用）
// 使い方: dbg(n); dbg(dp[i][j]);
// 注　意: -DLOCAL を付けてコンパイルしたときだけ動く
//         AtCoder では何もしないので、消し忘れても提出に影響しない
//         vector や pair はそのまま出せない。要素ごとに使う
// -----------------------------------------------
#ifdef LOCAL
#define dbg(x) cerr << #x << " = " << (x) << "\n"
#else
#define dbg(x)
#endif

// -----------------------------------------------
// 関数名: chmin / chmax
// 機　能: a を「a と b の小さい方 / 大きい方」に書き換える
// 引　数: a = 書き換える変数, b = 比べる値（a と型が違ってよい）
// 戻り値: 書き換えたら true
// 使い方: chmin(dp[i], dp[i - 1] + c);   chmax(ans, x);
// 注　意: DP の更新や、最大・最小の記録で毎回使う形
// -----------------------------------------------
template <class T, class U>
inline bool chmin(T &a, const U &b)
{
    if (b < a)
    {
        a = b;
        return true;
    }
    return false;
}

template <class T, class U>
inline bool chmax(T &a, const U &b)
{
    if (a < b)
    {
        a = b;
        return true;
    }
    return false;
}

// -----------------------------------------------
// 定数名: INF
// 機　能: 「とても大きい値」。最小値を求めるときの初期値などに使う
// 注　意: 1LL << 60 ≒ 1.15 × 10^18。INF 同士を何回か足しても溢れない
//         （4e18 だと INF + INF で上限ギリギリ、もう1回足すと溢れる）
// -----------------------------------------------
const ll INF = 1LL << 60;

// -----------------------------------------------
// 定数名: dx4 / dy4, dx8 / dy8
// 機　能: グリッド上の隣接マスへの移動量
//         dx4/dy4 = 上下左右の4方向, dx8/dy8 = 斜めを含む8方向
// 使い方: rep(k, 4) { ll ni = i + dx4[k], nj = j + dy4[k]; ... }
// 注　意: 範囲外チェックは呼ぶ側で行う
// -----------------------------------------------
const ll dx4[4] = {1, -1, 0, 0};
const ll dy4[4] = {0, 0, 1, -1};
const ll dx8[8] = {1, 1, 1, 0, 0, -1, -1, -1};
const ll dy8[8] = {1, 0, -1, 1, -1, 1, 0, -1};

// ============ MOD 計算（余りを取る問題で使う） ============

// -----------------------------------------------
// 変数名: MOD
// 機　能: 余りを取る法。問題文を見て毎回書き換える
// 注　意: mod_inv / div_MOD は MOD が素数のときだけ正しい
//         よく出るのは 998244353 と 1000000007（どちらも素数）
//         余りを取ると大小比較と % は意味を失う。使えるのは + - × ÷ 累乗 だけ
// -----------------------------------------------
ll MOD = 998244353;

// -----------------------------------------------
// 関数名: mod_pow
// 機　能: b の e 乗を mod で割った余りを求める（繰り返し二乗法）
// 引　数: b = 底, e = 指数（e ≥ 0）, mod = 法
// 戻り値: b^e % mod
// 計算量: O(log e)
// 注　意: 素直に e 回掛けると間に合わない場面で使う
// -----------------------------------------------
inline ll mod_pow(ll b, ll e, ll mod)
{
    ll r = 1 % mod;
    b %= mod;
    if (b < 0)
        b += mod;
    while (e > 0)
    {
        if (e & 1)
            r = r * b % mod;
        b = b * b % mod;
        e >>= 1;
    }
    return r;
}

// -----------------------------------------------
// 関数名: mod_inv
// 機　能: mod での a の逆数（a で割ることに相当する数）を求める
// 引　数: a = 対象, mod = 法（素数であること）
// 戻り値: a の逆元
// 注　意: mod が素数のときだけ正しい。998244353 も 1000000007 も素数
// -----------------------------------------------
inline ll mod_inv(ll a, ll mod)
{
    return mod_pow(a, mod - 2, mod);
}

// -----------------------------------------------
// 関数名: norm_MOD
// 機　能: a を 0 以上 MOD 未満に直す
// 引　数: a = 対象の数（負でも MOD 以上でもよい）
// 戻り値: 0 以上 MOD 未満の値
// 注　意: すでに 0 以上 MOD 未満なら % を使わずにそのまま返す（速い）
//         % は足し算の数十倍重いので、整っていないときだけ使う
// -----------------------------------------------
inline ll norm_MOD(ll a)
{
    if (a < 0 || a >= MOD)
        a = (a % MOD + MOD) % MOD;
    return a;
}

// -----------------------------------------------
// 関数名: add_MOD
// 機　能: a + b を MOD で割った余りを求める
// 引　数: a, b = 足す 2 つの数（負でも MOD 以上でもよい）
// 戻り値: 0 以上 MOD 未満の値
// 注　意: ふつう（0〜MOD-1 同士）は % を使わないので速い
// -----------------------------------------------
inline ll add_MOD(ll a, ll b) { return norm_MOD(norm_MOD(a) + norm_MOD(b)); }

// -----------------------------------------------
// 関数名: sub_MOD
// 機　能: a - b を MOD で割った余りを求める
// 引　数: a, b = 引く 2 つの数（負でもよい）
// 戻り値: 0 以上 MOD 未満の値
// 注　意: 生の (a - b) % MOD は負になり得る。必ずこちらを使う
//         ふつう（0〜MOD-1 同士）は % を使わないので速い
// -----------------------------------------------
inline ll sub_MOD(ll a, ll b) { return norm_MOD(norm_MOD(a) - norm_MOD(b)); }

// -----------------------------------------------
// 関数名: mul_MOD
// 機　能: a × b を MOD で割った余りを求める
// 引　数: a, b = 掛ける 2 つの数（負でも MOD 以上でもよい）
// 戻り値: 0 以上 MOD 未満の値
// 注　意: ふつう（0〜MOD-1 同士）は % を1回しか使わないので速い
// -----------------------------------------------
inline ll mul_MOD(ll a, ll b) { return norm_MOD(a) * norm_MOD(b) % MOD; }

// -----------------------------------------------
// 関数名: div_MOD
// 機　能: a ÷ b を MOD で割った余りを求める（逆元を掛ける）
// 引　数: a, b = 割られる数と割る数（b は MOD の倍数でないこと）
// 戻り値: 0 以上 MOD 未満の値
// 注　意: MOD が素数のときだけ正しい。/ は使えないのでこれを使う
// -----------------------------------------------
inline ll div_MOD(ll a, ll b) { return mul_MOD(a, mod_inv(norm_MOD(b), MOD)); }

// -----------------------------------------------
// 関数名: pow_MOD
// 機　能: a の e 乗を MOD で割った余りを求める
// 引　数: a = 底, e = 指数（e ≥ 0）
// 戻り値: 0 以上 MOD 未満の値
// 注　意: C++ の ^ は XOR であって累乗ではない。累乗はこちらを使う
// -----------------------------------------------
inline ll pow_MOD(ll a, ll e) { return mod_pow(a, e, MOD); }

// -----------------------------------------------
// 関数名: make_fact
// 機　能: 0! から n! までを mod で割った余りの表を作る
// 引　数: n = 上限, mod = 法
// 戻り値: 長さ n+1 の配列。f[i] = i! % mod
// 計算量: O(n)
// -----------------------------------------------
inline vl make_fact(ll n, ll mod)
{
    vl f(n + 1);
    f[0] = 1 % mod;
    rep2(i, 1, n + 1)
        f[i] = f[i - 1] * i % mod;
    return f;
}

// -----------------------------------------------
// 関数名: nCr
// 機　能: n 個から r 個を選ぶ組み合わせの数を mod で求める
// 引　数: n, r = 選ぶ元と個数, fact = make_fact で作った表, mod = 法（素数）
// 戻り値: nCr % mod（r が範囲外なら 0）
// 計算量: 1 回あたり O(log mod)
// 注　意: fact は n 以上の大きさで作っておくこと
// -----------------------------------------------
inline ll nCr(ll n, ll r, const vl &fact, ll mod)
{
    if (r < 0 || r > n)
        return 0;
    return fact[n] * mod_inv(fact[r] * fact[n - r] % mod, mod) % mod;
}

// ============ 入力 ============

// -----------------------------------------------
// 関数名: input
// 機　能: vector の全要素を cin から読み込む
// 引　数: v = 読み込み先（サイズは先に確保しておくこと）
// 戻り値: なし
// -----------------------------------------------
template <class T>
inline void input(vector<T> &v)
{
    for (auto &x : v)
        cin >> x;
}

// -----------------------------------------------
// 関数名: input（添字指定版）
// 機　能: vector の st 番目以降を cin から読み込む
// 引　数: v = 読み込み先, st = 読み始める添字
// 戻り値: なし
// 使い方: 1 始まりで持ちたいとき input(v, 1)
// -----------------------------------------------
template <class T>
inline void input(vector<T> &v, ll st)
{
    for (ll i = st; i < (ll)v.size(); i++)
        cin >> v[i];
}

// -----------------------------------------------
// 関数名: read_all
// 機　能: 標準入力を、空白・改行も含めて丸ごと読む
// 引　数: なし
// 戻り値: 入力全体をつなげた文字列
// -----------------------------------------------
inline string read_all()
{
    string s(istreambuf_iterator<char>(cin), {});
    return s;
}

// -----------------------------------------------
// 関数名: read_words
// 機　能: 標準入力を単語ごとに読み、空白・改行を除いて連結する
// 引　数: なし
// 戻り値: 連結した文字列
// -----------------------------------------------
inline string read_words()
{
    string s, t;
    while (cin >> t)
        s += t;
    return s;
}

// ============ 文字列 ============

// -----------------------------------------------
// 関数名: digit_sum
// 機　能: 数字だけの文字列について、各桁の和を求める
// 引　数: n = 数字のみからなる文字列
// 戻り値: 各桁の和
// 注　意: 数字以外が混ざると正しくない値になる
// -----------------------------------------------
inline int digit_sum(string n)
{
    int sum = 0;
    for (auto it = n.begin(); it < n.end(); it++)
    {
        sum += *it - '0';
    }
    return sum;
}

// -----------------------------------------------
// 関数名: scan_n
// 機　能: 数字の並びを n 進数として読み取り、10 進の値を返す
// 引　数: s = 数字のみの文字列, n = 基数（n ≥ 2）
// 戻り値: 読み取った値。n 以上の数字が含まれ読み取れない場合は -1
// 使い方: scan_n("237", 8) == 159
// -----------------------------------------------
inline ll scan_n(const string &s, ll n)
{
    ll v = 0;
    for (char c : s)
    {
        ll d = c - '0';
        if (d >= n)
        {
            return -1;
        }
        v = v * n + d;
    }
    return v;
}

// -----------------------------------------------
// 関数名: prefix_function
// 機　能: KMP 法の前処理表を作る
//         pi[i] = t[0..i] の「先頭と末尾が一致する最長の長さ」
//         （t[0..i] 全体は除く）
// 引　数: t = 対象の文字列
// 戻り値: 長さ |t| の配列 pi
// 計算量: O(|t|)
// -----------------------------------------------
inline vl prefix_function(const string &t)
{
    ll m = t.size();
    vl pi(m, 0);
    for (ll i = 1; i < m; i++)
    {
        ll j = pi[i - 1];
        while (j > 0 && t[i] != t[j])
            j = pi[j - 1];
        if (t[i] == t[j])
            j++;
        pi[i] = j;
    }
    return pi;
}

// -----------------------------------------------
// 関数名: kmp_count
// 機　能: s の中に t が何個現れるかを数える
// 引　数: s = 探される側, t = 探す側,
//         overlap = true なら重なりも数える
// 戻り値: 出現回数
// 計算量: O(|s| + |t|)
// -----------------------------------------------
inline ll kmp_count(const string &s, const string &t, bool overlap)
{
    if (t.empty())
        return 0;
    vl pi = prefix_function(t);
    ll m = t.size(), j = 0, cnt = 0;
    for (char c : s)
    {
        // j = 今 t の先頭から何文字一致しているか
        while (j > 0 && c != t[j])
            j = pi[j - 1];
        if (c == t[j])
            j++;
        if (j == m)
        {
            cnt++;
            // 重なりあり: 見つかった t の末尾を次の t の先頭として再利用する
            // 重なりなし: 使った文字は捨てて 0 からやり直す
            j = overlap ? pi[m - 1] : 0;
        }
    }
    return cnt;
}

// -----------------------------------------------
// 関数名: count_overlap
// 機　能: s の中の t の個数を、重なりも数えて求める
// 引　数: s = 探される側, t = 探す側
// 戻り値: 出現回数（aaaa の中の aa は 3）
// -----------------------------------------------
inline ll count_overlap(const string &s, const string &t)
{
    return kmp_count(s, t, true);
}

// -----------------------------------------------
// 関数名: count_nonoverlap
// 機　能: s の中の t の個数を、重ならないように数える
// 引　数: s = 探される側, t = 探す側
// 戻り値: 出現回数（aaaa の中の aa は 2）
// -----------------------------------------------
inline ll count_nonoverlap(const string &s, const string &t)
{
    return kmp_count(s, t, false);
}

// -----------------------------------------------
// 関数名: rle
// 機　能: ランレングス圧縮。同じ文字が何個続くかに分解する
// 引　数: s = 対象の文字列
// 戻り値: (文字, 連続する個数) を先頭から並べた配列
// 使い方: rle("aaabbc") -> (a,3) (b,2) (c,1)
// 計算量: O(|s|)
// -----------------------------------------------
inline vector<pair<char, ll>> rle(const string &s)
{
    vector<pair<char, ll>> res;
    for (char c : s)
    {
        if (!res.empty() && res.back().first == c)
            res.back().second++;
        else
            res.push_back(make_pair(c, 1LL));
    }
    return res;
}

// -----------------------------------------------
// 関数名: to_upper
// 機　能: 文字列をすべて大文字にする（その場で書き換え）
// 引　数: s = 書き換える文字列
// 戻り値: 書き換えた s 自身への参照
// 使い方: to_upper(s) == w のようにそのまま比較にも使える
// -----------------------------------------------
inline string &to_upper(string &s)
{
    for (char &c : s)
        c = toupper(c);
    return s;
}

// -----------------------------------------------
// 関数名: to_lower
// 機　能: 文字列をすべて小文字にする（その場で書き換え）
// 引　数: s = 書き換える文字列
// 戻り値: 書き換えた s 自身への参照
// -----------------------------------------------
inline string &to_lower(string &s)
{
    for (char &c : s)
        c = tolower(c);
    return s;
}

// -----------------------------------------------
// 関数名: swap_case
// 機　能: 大文字と小文字を入れ替える（その場で書き換え）
//         アルファベット以外はそのまま
// 引　数: s = 書き換える文字列
// 戻り値: 書き換えた s 自身への参照
// -----------------------------------------------
inline string &swap_case(string &s)
{
    for (char &c : s)
        c = isupper(c) ? tolower(c) : toupper(c);
    return s;
}

// -----------------------------------------------
// 関数名: substr_ab
// 機　能: s の a 文字目から b 文字目まで（両端を含む）を取り出す
// 引　数: s = 対象, a = 開始位置, b = 終了位置（どちらも 0 始まり）
// 戻り値: 取り出した部分文字列
// -----------------------------------------------
inline string substr_ab(const string &s, ll a, ll b)
{
    return s.substr(a, b - a + 1);
}

// -----------------------------------------------
// 関数名: reverse_ab
// 機　能: s の a〜b 文字目（両端を含む）を反転する（その場で書き換え）
// 引　数: s = 書き換える文字列, a = 開始位置, b = 終了位置（0 始まり）
// 戻り値: なし
// -----------------------------------------------
inline void reverse_ab(string &s, ll a, ll b)
{
    reverse(s.begin() + a, s.begin() + b + 1);
}

// -----------------------------------------------
// 関数名: replace_ab
// 機　能: s の a〜b 文字目（両端を含む）を p に置き換える
// 引　数: s = 書き換える文字列, a = 開始位置, b = 終了位置（0 始まり）,
//         p = 置き換える文字列（長さは違ってよい）
// 戻り値: なし
// -----------------------------------------------
inline void replace_ab(string &s, ll a, ll b, const string &p)
{
    s.replace(a, b - a + 1, p);
}

// ============ 距離 ============

// -----------------------------------------------
// 関数名: minkowski
// 機　能: 2 点間のミンコフスキー距離を求める
// 引　数: x, y = 同じ長さの座標, p = 次数
//         （p=1 でマンハッタン距離, p=2 でユークリッド距離）
// 戻り値: 距離
// -----------------------------------------------
inline double minkowski(const vl &x, const vl &y, double p)
{
    double sum = 0;
    rep(i, x.size())
        sum += pow(abs(x[i] - y[i]), p);
    return pow(sum, 1.0 / p);
}

// -----------------------------------------------
// 関数名: chebyshev
// 機　能: チェビシェフ距離（p = ∞ のミンコフスキー距離）を求める
//         各成分の差の絶対値のうち最大のもの
// 引　数: x, y = 同じ長さの座標
// 戻り値: 距離
// -----------------------------------------------
inline double chebyshev(const vl &x, const vl &y)
{
    ll mx = 0;
    rep(i, x.size())
        mx = max(mx, abs(x[i] - y[i]));
    return mx;
}

// ============ 累積和 ============

// -----------------------------------------------
// 関数名: build_cumsum
// 機　能: 累積和の表を作る。cs[i] = a[0] + ... + a[i-1]
// 引　数: a = 元の配列
// 戻り値: 長さ (a のサイズ + 1) の配列。先頭は 0
// 使い方: vl cs = build_cumsum(a); を先に1回だけ呼ぶ
// 計算量: O(n)
// -----------------------------------------------
inline vl build_cumsum(const vl &a)
{
    vl cs(a.size() + 1, 0);
    rep(i, a.size())
        cs[i + 1] = cs[i] + a[i];
    return cs;
}

// -----------------------------------------------
// 関数名: range_sum
// 機　能: a[l] から a[r] まで（両端を含む）の合計を求める
// 引　数: cs = build_cumsum で作った表, l = 左端, r = 右端（0 始まり）
// 戻り値: 区間の合計
// 計算量: O(1)
// 注　意: l > r のときは呼ばないこと
// -----------------------------------------------
inline ll range_sum(const vl &cs, ll l, ll r)
{
    return cs[r + 1] - cs[l];
}

// -----------------------------------------------
// 関数名: build_cumsum2
// 機　能: 2 次元の累積和の表を作る
// 引　数: a = 元の 2 次元配列（各行の長さは同じであること）
// 戻り値: (縦+1) × (横+1) の表。先頭の行と列は 0
// 計算量: O(縦 × 横)
// -----------------------------------------------
inline vvl build_cumsum2(const vvl &a)
{
    ll h = a.size(), w = h ? a[0].size() : 0;
    vvl cs(h + 1, vl(w + 1, 0));
    rep(i, h)
        rep(j, w)
            cs[i + 1][j + 1] = cs[i][j + 1] + cs[i + 1][j] - cs[i][j] + a[i][j];
    return cs;
}

// -----------------------------------------------
// 関数名: range_sum2
// 機　能: 長方形 (i1,j1) から (i2,j2) まで（両端を含む）の合計を求める
// 引　数: cs = build_cumsum2 で作った表,
//         i1,j1 = 左上, i2,j2 = 右下（どちらも 0 始まり）
// 戻り値: 長方形の中の合計
// 計算量: O(1)
// -----------------------------------------------
inline ll range_sum2(const vvl &cs, ll i1, ll j1, ll i2, ll j2)
{
    return cs[i2 + 1][j2 + 1] - cs[i1][j2 + 1] - cs[i2 + 1][j1] + cs[i1][j1];
}

// -----------------------------------------------
// 関数名: sum_all
// 機　能: 配列の全要素の合計を求める
// 引　数: v = 対象の配列
// 戻り値: 合計
// 計算量: O(n)
// 注　意: 中身は accumulate。0LL を渡さないと int で溢れるので注意
// -----------------------------------------------
inline ll sum_all(const vl &v) { return accumulate(nall(v), 0LL); }

// -----------------------------------------------
// 関数名: sum_range
// 機　能: a から b までの整数をすべて足した合計を求める
// 引　数: a = 下端, b = 上端（どちらも含む。負でもよい）
// 戻り値: 合計（a > b なら 0）
// 計算量: O(1)
// 使い方: sum_range(1, 10) == 55
// 注　意: ループ不要。b が 10^16 でも一瞬で出る
// -----------------------------------------------
inline ll sum_range(ll a, ll b)
{
    if (a > b)
        return 0;
    ll n = b - a + 1, s = a + b;
    if (n % 2 == 0) // 先に半分にして溢れにくくする
        n /= 2;
    else
        s /= 2;
    return n * s;
}

// -----------------------------------------------
// 関数名: sum_arith
// 機　能: 等差数列の合計を求める
// 引　数: a = 初項, d = 公差, n = 項数
// 戻り値: 合計（n ≤ 0 なら 0）
// 計算量: O(1)
// 使い方: sum_arith(2, 3, 5) == 40   （2+5+8+11+14）
// -----------------------------------------------
inline ll sum_arith(ll a, ll d, ll n)
{
    if (n <= 0)
        return 0;
    ll s = 2 * a + (n - 1) * d;
    if (n % 2 == 0)
        return (n / 2) * s;
    return n * (s / 2);
}

// ============ 数論 ============

// -----------------------------------------------
// 関数名: kiriage
// 機　能: a ÷ b の切り上げ（a / b 以上で最小の整数）を求める
// 引　数: a = 割られる数, b = 割る数（b > 0）
// 戻り値: 切り上げた商
// 使い方: kiriage(9, 4) == 3,  kiriage(8, 4) == 2
// 注　意: a が負でも正しく動く。b は正にすること
// -----------------------------------------------
inline ll kiriage(ll a, ll b)
{
    if (a >= 0)
        return (a + b - 1) / b;
    return a / b; // 負の数の割り算は 0 の方向に切り捨てなので、これで切り上げになる
}

// -----------------------------------------------
// 関数名: divisors
// 機　能: n の約数をすべて列挙する（試し割り）
// 引　数: n = 対象の整数（n ≥ 1）
// 戻り値: 約数を昇順に並べた配列
// 計算量: O(√n)
// -----------------------------------------------
inline vl divisors(ll n)
{
    vl res, big; // res: √n 以下の約数（昇順）, big: √n より大きい約数（降順）
    for (ll i = 1; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            res.push_back(i);
            if (i != n / i) // n が平方数のとき √n を2回入れない
                big.push_back(n / i);
        }
    }
    res.insert(res.end(), rall(big)); // big を逆順につなげると全体が昇順になる
    return res;
}

// -----------------------------------------------
// 関数名: is_prime
// 機　能: n が素数かどうかを判定する
// 引　数: n = 対象の整数
// 戻り値: 素数なら true（0 と 1 と負の数は false）
// 計算量: O(√n)
// -----------------------------------------------
inline bool is_prime(ll n)
{
    if (n < 2)
        return false;
    for (ll i = 2; i * i <= n; i++)
        if (n % i == 0)
            return false;
    return true;
}

// -----------------------------------------------
// 関数名: sieve
// 機　能: エラトステネスの篩。0〜n の素数表を一度に作る
// 引　数: n = 上限（n ≥ 0）
// 戻り値: 長さ n+1 の配列。p[i] = i が素数なら true
// 計算量: O(n log log n)
// 使い方: 何度も素数判定するなら is_prime より断然速い
// -----------------------------------------------
inline vb sieve(ll n)
{
    vb p(n + 1, true);
    if (n >= 0)
        p[0] = false;
    if (n >= 1)
        p[1] = false;
    for (ll i = 2; i * i <= n; i++)
        if (p[i])
            for (ll j = i * i; j <= n; j += i)
                p[j] = false;
    return p;
}

// -----------------------------------------------
// 関数名: factorize
// 機　能: n を素因数分解する
// 引　数: n = 対象の整数（n ≥ 1）
// 戻り値: (素数, その個数) を素数の昇順で並べた配列
// 使い方: factorize(12) -> (2,2) (3,1)   つまり 2^2 × 3
// 計算量: O(√n)
// -----------------------------------------------
inline vp factorize(ll n)
{
    vp res;
    for (ll i = 2; i * i <= n; i++)
    {
        if (n % i)
            continue;
        ll c = 0;
        while (n % i == 0)
        {
            n /= i;
            c++;
        }
        res.push_back(pll(i, c));
    }
    if (n > 1) // 最後に残った n は素数
        res.push_back(pll(n, 1));
    return res;
}

// -----------------------------------------------
// 関数名: gcd_ll
// 機　能: a と b の最大公約数を求める
// 引　数: a, b = 対象の整数（a, b ≥ 0）
// 戻り値: 最大公約数（両方 0 なら 0）
// 注　意: std::gcd は C++17 以降。古い規格でも動くよう自前で持つ
// -----------------------------------------------
inline ll gcd_ll(ll a, ll b)
{
    while (b)
    {
        ll t = a % b;
        a = b;
        b = t;
    }
    return a;
}

// -----------------------------------------------
// 関数名: lcm_ll
// 機　能: a と b の最小公倍数を求める
// 引　数: a, b = 対象の整数（a, b ≥ 1）
// 戻り値: 最小公倍数
// 注　意: 先に割ってから掛ける（a * b / gcd だと途中があふれやすい）
// -----------------------------------------------
inline ll lcm_ll(ll a, ll b)
{
    return a / gcd_ll(a, b) * b;
}

// -----------------------------------------------
// 関数名: common_divisors
// 機　能: a と b の公約数をすべて列挙する
//         公約数 = 最大公約数 g の約数なので、g の約数を列挙するだけ
// 引　数: a, b = 対象の整数（a, b ≥ 1）
// 戻り値: 公約数を昇順に並べた配列
// 計算量: O(√gcd(a, b))
// -----------------------------------------------
inline vl common_divisors(ll a, ll b)
{
    return divisors(gcd_ll(a, b));
}

// ============ その他 ============

// -----------------------------------------------
// 関数名: zahyo_asshuku
// 機　能: 座標圧縮。各値を「小さい方から何番目か」に置き換える
// 引　数: values = 元の値の並び
// 戻り値: 同じ長さの配列。各要素が 0 始まりの順位
// 注　意: 同じ値には同じ順位が入る
// 計算量: O(n log n)
// -----------------------------------------------
inline vl zahyo_asshuku(vl values)
{
    vl sorted_values = values; // コピーしてソート用に使う
    sort(sorted_values.begin(), sorted_values.end());
    sorted_values.erase(unique(sorted_values.begin(), sorted_values.end()), sorted_values.end());
    // ↑ 重複を削除(座圧では、ユニークな値だけを対象にするのが一般的)

    vl ranks(values.size());
    rep(i, values.size())
    {
        ranks[i] = lower_bound(sorted_values.begin(), sorted_values.end(), values[i]) - sorted_values.begin();
    }
    return ranks;
}

// -----------------------------------------------
// 関数名: napDP
// 機　能: ナップサックDP（数え上げ）。渡された dp に品物を足していく
//         dp[s] = 合計がちょうど s になる選び方の数
// 引　数: dp = 今の状態。使う前に dp[0] = 1 にしておく
//         ws = 追加する品物の重さ
//         mod = 余りを取る法（0 を渡すと余りを取らない）
//         unlimited = false なら各品1回まで / true なら何個でも
// 戻り値: 更新後の dp（サイズは渡した dp と同じ）
// 計算量: O(品数 × dp のサイズ)
// 注　意: dp のサイズが上限を決める。合計 M までしか要らないなら
//         dp を M+1 で作れば、そこで勝手に打ち切られる
// -----------------------------------------------
inline vl napDP(vl dp, const vl &ws, ll mod, bool unlimited)
{
    ll S = (ll)dp.size() - 1;
    for (ll b : ws)
    {
        if (b <= 0 || b > S)
            continue;
        if (unlimited)
            for (ll s = b; s <= S; s++) // 昇順: 何個でも使える
            {
                dp[s] += dp[s - b];
                if (mod && dp[s] >= mod) // 超えたときだけ引く（% より速い）
                    dp[s] -= mod;
            }
        else
            for (ll s = S; s >= b; s--) // 降順: 各品1回まで
            {
                dp[s] += dp[s - b];
                if (mod && dp[s] >= mod) // 超えたときだけ引く（% より速い）
                    dp[s] -= mod;
            }
    }
    return dp;
}

// -----------------------------------------------
// 関数名: napDP_max
// 機　能: ナップサックDP（価値最大化）
//         dp[w] = 重さ w 以下で得られる価値の最大
// 引　数: dp = 今の状態（ふつうは全部 0 で初期化）
//         items = (重さ, 価値) の配列
//         unlimited = false なら各品1回まで / true なら何個でも
// 戻り値: 更新後の dp（サイズは渡した dp と同じ）
// 計算量: O(品数 × dp のサイズ)
// 注　意: 数え上げ版と初期化が違う。こちらは dp[0] = 1 にしない
// -----------------------------------------------
inline vl napDP_max(vl dp, const vp &items, bool unlimited)
{
    ll W = (ll)dp.size() - 1;
    for (size_t i = 0; i < items.size(); i++)
    {
        ll w = items[i].first, v = items[i].second;
        if (w <= 0 || w > W)
            continue;
        if (unlimited)
            for (ll s = w; s <= W; s++)
                dp[s] = max(dp[s], dp[s - w] + v);
        else
            for (ll s = W; s >= w; s--)
                dp[s] = max(dp[s], dp[s - w] + v);
    }
    return dp;
}

// -----------------------------------------------
// 構造体名: UnionFind
// 機　能: 要素をグループにまとめ、同じグループかを高速に判定する
// 作り方: UnionFind uf(n);   要素は 0 〜 n-1
// 使い方: uf.unite(x, y) … x と y を同じグループにする（既に同じなら false）
//         uf.same(x, y)  … 同じグループか
//         uf.size(x)     … x が属するグループの要素数
// 計算量: 1 回あたりほぼ O(1)
// -----------------------------------------------
struct UnionFind
{
    vl par, siz;
    UnionFind(ll n) : par(n), siz(n, 1)
    {
        rep(i, n) par[i] = i;
    }
    ll find(ll x)
    {
        return par[x] == x ? x : par[x] = find(par[x]);
    }
    bool unite(ll x, ll y)
    {
        x = find(x);
        y = find(y);
        if (x == y)
            return false;
        if (siz[x] < siz[y])
            swap(x, y);
        par[y] = x;
        siz[x] += siz[y];
        return true;
    }
    bool same(ll x, ll y) { return find(x) == find(y); }
    ll size(ll x) { return siz[find(x)]; }
};

// -----------------------------------------------
// 関数名: grid_bfs
// 機　能: グリッド上の最短距離を、開始マスから全マスぶん求める（幅優先探索）
// 引　数: g = 盤面（各行の長さは同じ）, si,sj = 開始マス,
//         wall = 通れないマスを表す文字
// 戻り値: 縦 × 横 の距離表。届かないマスは -1
// 計算量: O(縦 × 横)
// 注　意: 移動は上下左右の4方向。斜めも許すなら dx8/dy8 に差し替える
// -----------------------------------------------
inline vvl grid_bfs(const vs &g, ll si, ll sj, char wall)
{
    ll h = g.size(), w = h ? g[0].size() : 0;
    vvl d(h, vl(w, -1));
    if (g[si][sj] == wall)
        return d;
    queue<pll> q;
    d[si][sj] = 0;
    q.push(pll(si, sj));
    while (!q.empty())
    {
        pll c = q.front();
        q.pop();
        rep(k, 4)
        {
            ll ni = c.first + dx4[k], nj = c.second + dy4[k];
            if (ni < 0 || nj < 0 || ni >= h || nj >= w)
                continue;
            if (g[ni][nj] == wall || d[ni][nj] != -1)
                continue;
            d[ni][nj] = d[c.first][c.second] + 1;
            q.push(pll(ni, nj));
        }
    }
    return d;
}

// - - - - - - - まずはこの４つの問いに答える - - - - - - - - - - - - - - - - - -
// 1. 何ごとの話にすると見やすい？ 何だけ持てばいい？
//
// 2. それについて、何が分かれば答えになる？
//
// 3. 何を捨ててよく、なぜそれで足りる？ 何が効く / 何が禁止？
//
// 4. その情報をどう更新 / 判定 / 集計すれば実装できる？
//
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

/* 考察するとこ
 *
 *
 *
 *
 */

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    return 0;
}

/* 反省・感想
 * 気づくきっかけ：
 * 原因→対策：
 *
 */

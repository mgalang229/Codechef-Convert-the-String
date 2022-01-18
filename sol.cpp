#include <bits/stdc++.h>

using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int tt;
	cin >> tt;
	while (tt--) {
		int n;
		cin >> n;
		string a;
		cin >> a;
		string b;
		cin >> b;
		// it is impossible to change a to b if:
		// - the letter(s) from a is greater than the letter(s) from b (lexicographic order)
		// - the letter(s) from b cannot be found in a
		bool checker = true;
		for (int i = 0; i < n; i++) {
			checker &= ((a[i] - 'a') >= (b[i] - 'a'));
			checker &= (a.find(b[i]) != string::npos);
		}
		if (!checker) {
			cout << -1 << '\n';
			continue;
		}
		// otherwise, store the frequency of the letters that are not equal in a and b
		vector<int> counter(26, 0);
		for (int i = 0; i < n; i++) {
			if (a[i] != b[i]) {
				counter[b[i] - 'a']++;
			}
		}
		// count the unmatched letters
		int cnt = 0;
		for (int i = (int) counter.size() - 1; i >= 0; i--) {
			if (counter[i] > 0) {
				cnt++;
			}
		}
		cout << cnt << '\n';
		// the trick is to change the letters which have the same letter-to-be in order to get the minimum
		// note: start from the end of the alphabet because if we start at random order we might override
		// a letter that we might possibly need again
		for (int i = (int) counter.size() - 1; i >= 0; i--) {
			if (counter[i] > 0) {
				// output the needed letters to be changed plus 1 (this 1 is the letter that will be copied)
				cout << counter[i] + 1 << " ";
				bool visited[n];
				memset(visited, false, sizeof(visited));
				bool checker = false;
				// change the letters that are needed to be changed
				for (int j = 0; j < n; j++) {
					if (a[j] != b[j] && b[j] == (char) (i + 'a')) {
						cout << j << " ";
						checker |= (a[j] == (char) (i + 'a'));
						a[j] = b[j];
						visited[j] = true;
					}
				}
				// find the index of the letter to be copied
				if (!checker) {
					for (int j = 0; j < n; j++) {
						if (a[j] == (char) (i + 'a') && !visited[j]) {
							cout << j << " ";
							break;
						}
					}
				}
				cout << '\n';
			}
		}
	}
	return 0;
}

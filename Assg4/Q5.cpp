#include <iostream>
#include <vector>
#include <string>

using namespace std;

string least_rotation(const string& S)
{
    string T = S + S;  // Concatenate the string with itself
    int n = T.size();
    vector<int> f(n, -1);  // Failure function
    int k = 0;  // Least rotation of string found so far

    for (int j = 1; j < n; ++j) {
        char sj = T[j];
        int i = f[j - k - 1];
        while (i != -1 && sj != T[k + i + 1]) {
            if (sj < T[k + i + 1]) {
                k = j - i - 1;
            }
            i = f[i];
        }
        if (sj != T[k + i + 1]) {  // mismatch after i matches
            if (sj < T[k]) {  // Found a smaller rotation
                k = j;
            }
            f[j - k] = -1;
        } else {
            f[j - k] = i + 1;
        }
    }
    return T.substr(k, S.size());
}

int main()
{
    string S = "sresac";
    string smallest_rotation = least_rotation(S);
    cout << "The lexicographically smallest rotation is: " << smallest_rotation << endl;
    return 0;
}

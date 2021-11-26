#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

#define ALPHABET_LEN 128

void ComputeLastOccurrenceFunction(vector<char> P, int m, int stop[ALPHABET_LEN]) {
    
    for (int i = 0; i < ALPHABET_LEN; i++)
        stop[i] = -1;
    for (int j = 0; j < m - 1; j++) {
        stop[int(P[j])] = j;
    }
}

void ComputeGoodSuffixFunction(vector<char> P, int m, vector<int>& suff) {

    vector<int> z(m, 0);
    int maxZpos = 0, maxZ = 0;
    for (int j = 1; j < m; ++j) {
        if (j <= maxZ) 
            z[j] = min(maxZ - j + 1, z[j - maxZpos]);
        while (j + z[j] < m && P[m - 1 - z[j]] == P[m - 1 - (j + z[j])]) 
            z[j]++;
        if (j + z[j] - 1 > maxZ) 
        {
            maxZpos = j;
            maxZ = j + z[j] - 1;
        }
    }
    for (int j = m - 1; j > 0; j--) 
        suff[m - z[j]] = j;
    int r = 0;
    for (int j = 1; j <= m - 1; j++)
        if (j + z[j] == m)
            for (; r <= j; r++)
                if (suff[r] == m) suff[r] = j;
    
}

void BMalgorithm(vector<char> str, vector<char> pat, int n, int m)
{   
    unsigned int start_time = clock();

    int stop[ALPHABET_LEN];
    ComputeLastOccurrenceFunction(pat, m, stop);

    vector<int> suff(m + 1, m);
    ComputeGoodSuffixFunction(pat, m, suff);

    int s = 0;
    while (s <= n - m) {
        int j = m - 1;
        while (j > -1 && pat[j] == str[s + j])
            j -= 1;
        if (j == -1)
        {
            cout << "Output:" << s <<endl;
            s += suff[0];
        }
        else
        {
            s += max(suff[j+1], j - stop[int(str[s + j])]);
        }
    };

    unsigned int end_time = clock();

    cout<<"Time:" << end_time - start_time << " mls" << endl;
}

void Generate(int n, int m)
{
    vector<char> str(n);
    vector<char> pat(m);

    for (int i = 0; i < m; i++)
        pat[i] = rand() % ALPHABET_LEN;

    int start_copy = 0;
    if (n != m) start_copy = rand() % (n - m);

    for (int i = 0; i < n; i++)
        if (i < start_copy || i >= start_copy + m)
            str[i] = rand() % ALPHABET_LEN;
        else str[i] = pat[i-start_copy];
    BMalgorithm(str, pat, n, m);

}

int main() 
{

    int n, m;
    cout << "Input string size:";
    cin >> n;
    cout << "Input pattern size:";
    cin >> m;
    if (n > m && n > 0 && m > 0) Generate(n, m);
    else cout << "Wrong input";
	return 0;
}
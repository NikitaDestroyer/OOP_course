#include <iostream>
#include <vector>
#include <math.h>
#include <conio.h>

using namespace std;
int main()
{
    int n, m, quant, minim_dist, maxim=0, t;
    cin >> n >> m;
    cin >> quant;
    vector<int> x(n);
    vector<int> y(m);
    for (int i = 0; i < quant; ++i) {
        cin >> x[i] >> y[i];
    }
    

    for (int i = 1; i < n + 1; ++i) {
        for (int j = 1; j < m + 1; ++j)
        {
            minim_dist = n + m;
            for (int u = 0; u < quant; ++u){
                t = (abs(i - x[u]) + abs(j - y[u]));
                if (t < minim_dist) {
                    minim_dist = t;
                }
            }
            if (minim_dist > maxim) {
                maxim = minim_dist;
            }
        }
    }
    cout << maxim << endl;
}







#include <bits/stdc++.h>
#include <unordered_map>
#include <chrono>
#include <random>

#define mp make_pair
#define pb push_back
#define ll long long
#define ll_MAX 1e18

ll MOD = 1e9 + 7;

using namespace std;

double total = -1;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

vector<string> questsCompleted(int time, int team, int parallel, int sack, bool is1) {
    int overall = time * parallel;
    double used = 0;
    int i = 1;

    vector<string> counter;

    vector<int> hardness;
    for (int i = 0; i < 400; i++) {
        int random = uniform_int_distribution<int>(10, 20)(rng);
        hardness.push_back(random);
    }

    if (is1) {
        while (counter.size() < 100) {
            used += 15 * sqrt(i * team);
            counter.push_back("1");
            i++;
        }
        total = used/4;
        return counter;
    }

    while (used + hardness[i] * sqrt(i * team) <= overall) {
        used += hardness[i] * sqrt(i * team);
        counter.push_back("1");
        i++;
    }

    int tries = 0;
    double prevTime = used;
    double hold = used;
    double holdi = i;
    double holdprev = prevTime;
    vector<string> holdCounter = counter;
    
    vector<string> oldCounter;

    int max1 = 0;

    while (tries <= (total-time)/sack) {
        int sacs = (total - time) / sack - tries;
        int onecounter = 0;

        for (int x = 1; x <= sacs; x++) {
            counter.push_back("S");
            parallel++;
            while (used+ hardness[i] * sqrt(i * team) <= prevTime+sack * (parallel + x)) {
                used += hardness[i] * sqrt(i * team);
                counter.push_back("1");
                i++;
                onecounter++;
            }
            prevTime += sack * (parallel + x);
        }
        while (used + hardness[i] * sqrt(i * team) <=total) {
            used += hardness[i] * sqrt(i * team);
            counter.push_back("1");
            i++;
            onecounter++;
        }
        if (onecounter>=max1) {
            oldCounter = counter;
            max1 = onecounter;
        }
       
        
        tries++;
        i = holdi;
        used = hold;
        counter = holdCounter;
        parallel = 4;
        prevTime = holdprev;
    }

    counter = oldCounter;

    while (counter.size()<100) {
        counter.push_back("0");
    }

    return counter;
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(NULL);
    ofstream fout;
    fout.open("output.txt");

    /*
    Sack represents how long teams have between consecutive simulations.
    Until represents how long teams must initially wait before being able to sacrifice
    Repeat represents the number of times we repeat our simulation.
    */

    int sack = 200;
    int until = 500;
    int repeat = 1000;




    vector<vector<string>> doneb4;
    doneb4.resize(51);

    vector<int> attempted;
    attempted.resize(100);

    
    int skips = 0;

    for (int qq = 0; qq < repeat; qq++) {
        for (int a = 1; a <= 50; a++) {
            if (a == 1)
                doneb4[a] = questsCompleted(until, a, 4, sack, true);
            else {
                doneb4[a] = questsCompleted(until, a, 4, sack, false);
            }

            for (int i = 0; i < 100; i++) {
                if (doneb4[a][i] == "1") {
                    attempted[i]++;
                }
                else if (doneb4[a][i] == "S") {
                    skips++;
                }
            }
        }

        
        for (int i = 1; i < doneb4.size(); i++) {
            fout << i << ": ";
            if (i<10) {
                fout << " ";
            }

            for (int y = 0; y < 100; y++) {
                fout << doneb4[i][y];

                if (y%5==4) {
                    fout << " ";
                }
            }

            fout << endl;
        }
        
        
    }
    for (int i = 0; i < 100; i++) {
        cout << (i + 1) << ": " << (double)attempted[i] / repeat << endl;
    }

    cout << "Average Skips: " << skips / (50.0*repeat) << endl;

    /*
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 5; j++) {
            fout << "$Q" << 10 * j + i + 1 << "\\rightarrow " << (double)attempted[10 * j + i] / repeat << "$";
            if (j != 4) {
                fout << "&";
            }
            else {
                fout << "\\\\";
            }
        }
        fout << endl;
    }
    for (int i = 0; i < 10; i++) {
        for (int j = 5; j < 10; j++) {
            fout << "$Q" << 10 * j + i + 1 << "\\rightarrow " << (double)attempted[10 * j + i] / repeat << "$";
            if (j != 9) {
                fout << "&";
            }
            else {
                fout << "\\\\";
            }
        }

        fout << endl;
    }
    */
    return 0;
}

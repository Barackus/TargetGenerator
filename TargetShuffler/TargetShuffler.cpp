// TargetShuffler.cpp this program will take the input generated for one of the aiming methods, and creates new ones by shuffling the order of the targets.

#include "TargetShuffler.h";

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string>

#include<corecrt_math_defines.h> //for pi
#include<random>
#include<cmath>
#include<chrono>

using namespace std;

int main()
{
    const int nrOfTargetsPerSession = 42;
    const int nrOfSessions = 3; //per aiming method
    const int totalTargets = nrOfTargetsPerSession * nrOfSessions;
    const int thirdOfTotalTargets = totalTargets / 3;
    const int sixthOfTotalTargets = totalTargets / 6;
    const int practiceTargets = 18;
    const int nrOfPracticeSessions = 1;
    const int totalPracticeTargets = practiceTargets * nrOfPracticeSessions;
    const int thirdOfPracticeTargets = practiceTargets / 3;
    const int sixthOfPracticeTargets = practiceTargets / 6;

    int normalSessionIndexes[nrOfTargetsPerSession];
    for (int i = 0; i < nrOfTargetsPerSession; i++) {
        normalSessionIndexes[i] = i; //while reading the 42 lines, put them in a random position instead of sequentially.
    }
    shuffle_array(normalSessionIndexes, nrOfTargetsPerSession);
    //cout << normalSessionIndexes[0];
    int practiceSessionIndexes[practiceTargets];
    for (int i = 0; i < practiceTargets; i++) {
        practiceSessionIndexes[i] = i; //while reading the 18 lines, put them in a random position instead of sequentially.
    }
    shuffle_array(practiceSessionIndexes, practiceTargets);
    string normalSessionLines[nrOfTargetsPerSession]; //containers for the next 42 lines to shuffle them, then store them in the big array of those lines.
    string practiceSessionLines[practiceTargets]; //containers for the next 18 lines to shuffle them, then store them in the big array of those lines.

    string allNormalSessionLines[totalTargets]; //these arrays will contain all the lines, now shuffled, to be printed to the output file.
    string allPracticeSessionLines[totalPracticeTargets];

    //general idea, read the input, shuffle the order of input, write it to a new file. keep the regular and practice targets separate.
    string line;
    int readIndex = 0;
    vector <string> v;
    int normalSessionNr = 0;
    int practiceSessionNr = 0;
    bool skipNextIf = false;

    ifstream fin;
    fin.open("D:\\Master Thesis\\TargetGenerator\\TargetGenerator\\Input.txt"); //the hard path where the file is generated from TargetGenerator.
    if (fin.is_open()) {
        while (!fin.eof()) {
            getline(fin, line);
            cout << readIndex << " " << line << "\n";
            readIndex++;
            
            if ((line.find("@") == 0) && normalSessionNr < nrOfSessions) {//if this line contains an @ symbol, shuffle the next 42 targets (or whatever nroftargetsPerSession is)
                for (int i = 0; i < nrOfTargetsPerSession; i++) {
                    int letterIndex = line.find("@");
                    cout << letterIndex << endl;
                    getline(fin, line);
                    cout << readIndex << " in @ " << line << "\n";
                    readIndex++;
                    //if (line.find('@')) getline(fin, line);
                    normalSessionLines[normalSessionIndexes[i]] = line;
                }
                for (int i = 0; i < nrOfTargetsPerSession; i++) {
                    int ansIndex = i + (normalSessionNr * nrOfTargetsPerSession);
                    allNormalSessionLines[ansIndex] = normalSessionLines[i];
                }
                normalSessionNr++; //after we have fininished shuffling the 42 targets, putting them in the big list, add one to this number so the next 42 targets get put on the next 42 spots, instead of overwriting the first 42 spots.
            }
            else if ((line.find("$") == 0) && practiceSessionNr < nrOfPracticeSessions) {//if this line contains a $ symbol, shuffle the next 18 (or whatever practiceTargets is)
                for (int i = 0; i < practiceTargets; i++) {
                    getline(fin, line);
                    cout << readIndex << " in $ " << line << "\n";
                    readIndex++;
                    //if (line.find('$', 2)) getline(fin, line); //if this line contains a $, skip it.

                    practiceSessionLines[practiceSessionIndexes[i]] = line;
                }
                for (int i = 0; i < practiceTargets; i++) {
                    int apsIndex = i + (practiceSessionNr * practiceTargets);
                    allPracticeSessionLines[apsIndex] = practiceSessionLines[i];
                }
                practiceSessionNr++;               
            }
        }
    }
    fin.close();
    
    ofstream file;
    file.open("Input.txt");
    file << "pp01abc \n";
    file << "Head,Mouse,Gun\n";
    file << nrOfSessions << "\n";
    file << nrOfTargetsPerSession << "\n";
    file << practiceTargets << "\n";
    file << "@ \n";

    for (int i = 0; i < nrOfSessions; i++) {
        for (int j = 0; j < nrOfTargetsPerSession; j++) {
            int index = i * nrOfTargetsPerSession + j;
            file << allNormalSessionLines[index] << "\n";
        }
        file << "@ \n";
    }
    file << "$ \n";
    for (int i = 0; i < nrOfPracticeSessions; i++) {
        for (int j = 0; j < practiceTargets; j++) {
            int index = i * nrOfPracticeSessions + j;
            file << allPracticeSessionLines[index] << "\n";
        }
        file << "$ \n";
    }   
    file.close();
}

void shuffle_array(int arr[], int n)
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count(); //0;
    shuffle(arr, arr + n, default_random_engine(seed));
}

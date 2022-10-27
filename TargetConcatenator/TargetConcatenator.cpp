// TargetConcatenator.cpp : This program takes three different sets of generated targets and combines them in the right order to make complete lists for use in the tests.

#include <iostream>
#include <fstream>
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
    const int nrOfSessions = 9;
    const int nrOfSessionsPerMethod = 3;
    const int totalTargets = nrOfTargetsPerSession * nrOfSessions;
    const int targetsPerMethod = totalTargets / 3;
    const int targetsPlusSymbolsPerMethod = targetsPerMethod + 4;
    
    const int practiceTargets = 18;
    const int nrOfPracticeSessions = 3;
    const int totalPracticeTargets = practiceTargets * nrOfPracticeSessions;
    const int practiceTargetsPerMethod = totalPracticeTargets / 3;
    const int practiceTargetsPlusSymbolsPerMethod = practiceTargetsPerMethod + 2;

    string gunHeadMouse = "Gun, Head, Mouse";
    string headMouseGun = "Head, Mouse, Gun";
    string mouseGunHead = "Mouse, Gun, Head";

    const int nrOfParticipants = 36;

    string baseOutputPath = "D:\\Master Thesis\\TargetGenerator\\TargetConcatenator\\Output\\TestPerson";
    int testPersonNr = 1;

    string gunTargets[targetsPlusSymbolsPerMethod];
    string headTargets[targetsPlusSymbolsPerMethod];
    string mouseTargets[targetsPlusSymbolsPerMethod];

    string practiceGunTargets[practiceTargetsPlusSymbolsPerMethod];
    string practiceHeadTargets[practiceTargetsPlusSymbolsPerMethod];
    string practiceMouseTargets[practiceTargetsPlusSymbolsPerMethod];

    int readIndex = 0;
    int normalSessionNr = 0;
    int practiceSessionNr = 0;

    //read in the targets Designated for the Gun aiming method, the input file is in the corresponding folder.
    string line;
    ifstream gunTargetsIn;
    gunTargetsIn.open("D:\\Master Thesis\\TargetGenerator\\TargetConcatenator\\GunTargets\\Input.txt"); //the hard path where the file is generated from TargetGenerator or TargetShuffler.
    if (gunTargetsIn.is_open()) {
        while (!gunTargetsIn.eof()) {
            getline(gunTargetsIn, line);
            cout << readIndex << " " << line << "\n";
            readIndex++;

            if (line.find("@") == 0) {
                gunTargets[0] = line;
                for (int i = 1; i < targetsPlusSymbolsPerMethod; i++) {
                    getline(gunTargetsIn, line);
                    cout << readIndex << " in @ " << line << "\n";
                    readIndex++;
                    gunTargets[i] = line;
                }
            }
            else if (line.find("$") == 0) {
                practiceGunTargets[0] = line;
                for (int i = 1; i < practiceTargetsPlusSymbolsPerMethod; i++) {
                    getline(gunTargetsIn, line);
                    cout << readIndex << " in $ " << line << "\n";
                    readIndex++;
                    practiceGunTargets[i] = line;
                }
            }
        }
    }
    gunTargetsIn.close();

    //read in the targets Designated for the Head aiming method, the input file is in the corresponding folder.
    
    ifstream headTargetsIn;
    headTargetsIn.open("D:\\Master Thesis\\TargetGenerator\\TargetConcatenator\\HeadTargets\\Input.txt"); //the hard path where the file is generated from TargetGenerator or TargetShuffler.
    if (headTargetsIn.is_open()) {
        while (!headTargetsIn.eof()) {
            getline(headTargetsIn, line);
            cout << readIndex << " " << line << "\n";
            readIndex++;

            if (line.find("@") == 0) {
                headTargets[0] = line;
                for (int i = 1; i < targetsPlusSymbolsPerMethod; i++) {
                    getline(headTargetsIn, line);
                    cout << readIndex << " in @ " << line << "\n";
                    readIndex++;
                    headTargets[i] = line;
                }
            }
            else if (line.find("$") == 0) {
                practiceHeadTargets[0] = line;
                for (int i = 1; i < practiceTargetsPlusSymbolsPerMethod; i++) {
                    getline(headTargetsIn, line);
                    cout << readIndex << " in $ " << line << "\n";
                    readIndex++;
                    practiceHeadTargets[i] = line;
                }
            }
        }
    }
    headTargetsIn.close();


    //read in the targets Designated for the Mouse aiming method, the input file is in the corresponding folder.
    ifstream mouseTargetsIn;
    mouseTargetsIn.open("D:\\Master Thesis\\TargetGenerator\\TargetConcatenator\\MouseTargets\\Input.txt"); //the hard path where the file is generated from TargetGenerator or TargetShuffler.
    if (mouseTargetsIn.is_open()) {
        while (!mouseTargetsIn.eof()) {
            getline(mouseTargetsIn, line);
            cout << readIndex << " " << line << "\n";
            readIndex++;

            if (line.find("@") == 0) {
                mouseTargets[0] = line;
                for (int i = 1; i < targetsPlusSymbolsPerMethod; i++) {
                    getline(mouseTargetsIn, line);
                    cout << readIndex << " in @ " << line << "\n";
                    readIndex++;
                    mouseTargets[i] = line;
                }
            }
            else if (line.find("$") == 0) {
                practiceMouseTargets[0] = line;
                for (int i = 1; i < practiceTargetsPlusSymbolsPerMethod; i++) {
                    getline(mouseTargetsIn, line);
                    cout << readIndex << " in $ " << line << "\n";
                    readIndex++;
                    practiceMouseTargets[i] = line;
                }
            }
        }
    }
    mouseTargetsIn.close();

    for (int i = 1; i < nrOfParticipants; i= i + 3) { //for each testperson
        testPersonNr = i;
        ofstream file;
        //string order;
        
        string path = baseOutputPath + to_string(testPersonNr) + "\\Input.txt";
        string name = "TestPerson" + to_string(testPersonNr);
        
     
        
        file.open(path);
        file << name << "\n";
        file << gunHeadMouse << "\n";
        file << nrOfSessions << "\n";
        file << nrOfTargetsPerSession << "\n";
        file << practiceTargets << "\n";

        for (int j = 0; j < targetsPlusSymbolsPerMethod-1; j++) {
            file << gunTargets[j] << "\n";
        }
        for (int j = 0; j < targetsPlusSymbolsPerMethod-1; j++) {
            file << headTargets[j] << "\n";
        }
        for (int j = 0; j < targetsPlusSymbolsPerMethod; j++) {
            file << mouseTargets[j] << "\n";
        }
        for (int j = 0; j < practiceTargetsPlusSymbolsPerMethod-1; j++) {
            file << practiceGunTargets[j] << "\n";
        }
        for (int j = 0; j < practiceTargetsPlusSymbolsPerMethod-1; j++) {
            file << practiceHeadTargets[j] << "\n";
        }
        for (int j = 0; j < practiceTargetsPlusSymbolsPerMethod; j++) {
            file << practiceMouseTargets[j] << "\n";
        }
        file.close();


        testPersonNr++;
        path = baseOutputPath + to_string(testPersonNr) + "\\Input.txt";
        name = "TestPerson" + to_string(testPersonNr);

        file.open(path);
        file << name << "\n";
        file << headMouseGun << "\n";
        file << nrOfSessions << "\n";
        file << nrOfTargetsPerSession << "\n";
        file << practiceTargets << "\n";

        for (int j = 0; j < targetsPlusSymbolsPerMethod-1; j++) {
            file << headTargets[j] << "\n";
        }
        for (int j = 0; j < targetsPlusSymbolsPerMethod-1; j++) {
            file << mouseTargets[j] << "\n";
        }
        for (int j = 0; j < targetsPlusSymbolsPerMethod; j++) {
            file << gunTargets[j] << "\n";
        }
        for (int j = 0; j < practiceTargetsPlusSymbolsPerMethod-1; j++) {
            file << practiceHeadTargets[j] << "\n";
        }
        for (int j = 0; j < practiceTargetsPlusSymbolsPerMethod-1; j++) {
            file << practiceMouseTargets[j] << "\n";
        }
        for (int j = 0; j < practiceTargetsPlusSymbolsPerMethod; j++) {
            file << practiceGunTargets[j] << "\n";
        }
        file.close();

        testPersonNr++;
        path = baseOutputPath + to_string(testPersonNr) + "\\Input.txt";
        name = "TestPerson" + to_string(testPersonNr);

        file.open(path);
        file << name << "\n";
        file << mouseGunHead << "\n";
        file << nrOfSessions << "\n";
        file << nrOfTargetsPerSession << "\n";
        file << practiceTargets << "\n";

        for (int j = 0; j < targetsPlusSymbolsPerMethod-1; j++) {
            file << mouseTargets[j] << "\n";
        }
        for (int j = 0; j < targetsPlusSymbolsPerMethod-1; j++) {
            file << gunTargets[j] << "\n";
        }
        for (int j = 0; j < targetsPlusSymbolsPerMethod; j++) {
            file << headTargets[j] << "\n";
        }
        for (int j = 0; j < practiceTargetsPlusSymbolsPerMethod-1; j++) {
            file << practiceMouseTargets[j] << "\n";
        }
        for (int j = 0; j < practiceTargetsPlusSymbolsPerMethod-1; j++) {
            file << practiceGunTargets[j] << "\n";
        }
        for (int j = 0; j < practiceTargetsPlusSymbolsPerMethod; j++) {
            file << practiceHeadTargets[j] << "\n";
        }
        file.close();
    }
}

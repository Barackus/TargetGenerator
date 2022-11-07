// TargetGenerator.cpp : this program will generate Targets and practice targets for a single aiming method. TargetShuffle will shuffle the targets to make new sets with comparable difficulty.
//
#include "TargetGenerator.h"
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
    //The shooting gallery starts at the positive x axis, positive Z is above you, positive y is 90 degrees to the right.
    const int nrOfTargetsPerSession = 42;
    const int nrOfSessions = 3; //We only generate targets for a single aiming method, then shuffle the order generate the other two.
    const int totalTargets = nrOfTargetsPerSession * nrOfSessions;
    const int thirdOfTotalTargets = totalTargets / 3;
    const int sixthOfTotalTargets = totalTargets / 6;
    const int practiceTargets = 18;
    const int thirdOfPracticeTargets = practiceTargets / 3;
    const int sixthOfPracticeTargets = practiceTargets / 6;
    //limits where on the sphere the points are generated. 
    const float upperLimitDegrees = 45;
    const float lowerLimitDegrees = 0;
    const float leftLimitDegrees = 85;
    const float rightLimitDegrees = 85;
    const float leftLimitNumber = 0.5 - ((leftLimitDegrees / 90) / 2); //90 degrees == 0, 0 degrees == 0.5
    const float rightLimitNumber = 0.5 + ((rightLimitDegrees / 90) / 2);  //0 degrees = 0.5, 90 degrees = 1.0  
    const double verticalOffset = 100; //distance from the floor, add this to every z coordinate so that every z coordinate is at least 100 or higher.
    vector<float> center;
    center.assign(3, 0);
    float closeRadius = 300;
    float mediumRadius = 600;
    float farRadius = 900;
   
    string distanceLabelList[totalTargets]; //these arrays should be as big as totalTargets
    string movementLabelList[totalTargets];
    vector<double> targetLocationList[totalTargets];
    for (int i = 0; i < totalTargets; i++) { targetLocationList[i].assign(3, 0.0); }

    string practiceDistanceLabelList[practiceTargets];
    string practiceMovementLabelList[practiceTargets];
    vector<double> practiceTargetLocationList[practiceTargets];
    for (int i = 0; i < practiceTargets; i++) { practiceTargetLocationList[i].assign(3, 0.0); }


    // Set up random number generators
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 generator(seed);
    std::uniform_real_distribution<double> uniform01(leftLimitNumber, rightLimitNumber);
    std::uniform_real_distribution<double> uniform02(((90-upperLimitDegrees)/180), 0.5); // from 0 to 70 degrees means being at least 20 degrees away from the z axis, so a minimum of 20/180 = 0.11111111

    //set up random index arrays
    int proximityIndexes[totalTargets];
    for (int i = 0; i < totalTargets; i++) {
        proximityIndexes[i] = i;
    }
    shuffle_array(proximityIndexes,totalTargets);

    /*####################### CLOSE ########################*/
    int closeIndexes[thirdOfTotalTargets];
    for (int i = 0; i < thirdOfTotalTargets; i++) {
        closeIndexes[i] = proximityIndexes[i];
        distanceLabelList[closeIndexes[i]] = "close"; //add the label "close" to the target randomly selected as a close target.
    }
    shuffle_array(closeIndexes, thirdOfTotalTargets);
    int closeStaticIndexes[sixthOfTotalTargets];
    int closeDynamicIndexes[sixthOfTotalTargets];
    for (int i = 0; i < sixthOfTotalTargets; i++) { //pick the first random half of the close targets as static, put it in the lists.
        closeStaticIndexes[i] = closeIndexes[i];
        movementLabelList[closeStaticIndexes[i]] = "static";
    }
    for (int i = 0; i < sixthOfTotalTargets; i++) {
        int index = sixthOfTotalTargets + i;
        closeDynamicIndexes[i] = closeIndexes[index];//pick the second random half of the close targets as dynamic, put it in the lists.
        movementLabelList[closeDynamicIndexes[i]] = "dynamic";
    }

    /*####################### MEDIUM ########################*/
    int mediumIndexes[thirdOfTotalTargets];
    for (int i = 0; i < thirdOfTotalTargets; i++) {
        int index = thirdOfTotalTargets + i; //grab the indexes between 1 third and 2 thirds
        mediumIndexes[i] = proximityIndexes[index];
        distanceLabelList[mediumIndexes[i]] = "medium"; //add the label "medium" to the target randomly selected as a medium target.
    }
    shuffle_array(mediumIndexes, thirdOfTotalTargets);
    int mediumStaticIndexes[sixthOfTotalTargets];
    int mediumDynamicIndexes[sixthOfTotalTargets];
    for (int i = 0; i < sixthOfTotalTargets; i++) { //pick the first random half of the medium targets as static, put it in the lists.
        mediumStaticIndexes[i] = mediumIndexes[i];
        movementLabelList[mediumStaticIndexes[i]] = "static";
    }
    for (int i = 0; i < sixthOfTotalTargets; i++) {
        int index = sixthOfTotalTargets + i;
        mediumDynamicIndexes[i] = mediumIndexes[index];//pick the second random half of the medium targets as dynamic, put it in the lists.
        movementLabelList[mediumDynamicIndexes[i]] = "dynamic";
    }

    /*####################### FAR ########################*/
    int farIndexes[thirdOfTotalTargets];
    for (int i = 0; i < thirdOfTotalTargets; i++) {
        int index = (2 * thirdOfTotalTargets) + i; //grab the indexes from 2 thirds until the end.
        farIndexes[i] = proximityIndexes[index];
        distanceLabelList[farIndexes[i]] = "far"; //add the label "far" to the target randomly selected as a far target.
    }
    shuffle_array(farIndexes, thirdOfTotalTargets);
    int farStaticIndexes[sixthOfTotalTargets];
    int farDynamicIndexes[sixthOfTotalTargets];
    for (int i = 0; i < sixthOfTotalTargets; i++) { //pick the first random half of the far targets as static, put it in the lists.
        farStaticIndexes[i] = farIndexes[i];
        movementLabelList[farStaticIndexes[i]] = "static";
    }
    for (int i = 0; i < sixthOfTotalTargets; i++) {
        int index = sixthOfTotalTargets + i;
        farDynamicIndexes[i] = farIndexes[index];//pick the second random half of the far targets as dynamic, put it in the lists.
        movementLabelList[farDynamicIndexes[i]] = "dynamic";
    }

    // repeat the same process, but for the practice targets.
    //set up random index arrays
    int PracticeProximityIndexes[practiceTargets];
    for (int i = 0; i < practiceTargets; i++) {
        PracticeProximityIndexes[i] = i;
    }
    shuffle_array(PracticeProximityIndexes, practiceTargets);


    /*####################### Practice CLOSE ########################*/
    int practiceCloseIndexes[thirdOfPracticeTargets];
    for (int i = 0; i < thirdOfPracticeTargets; i++) {
        practiceCloseIndexes[i] = PracticeProximityIndexes[i];
        practiceDistanceLabelList[practiceCloseIndexes[i]] = "close"; //add the label "close" to the target randomly selected as a close target.
    }
    shuffle_array(practiceCloseIndexes, thirdOfPracticeTargets);
    int practiceCloseStaticIndexes[sixthOfPracticeTargets];
    int practiceCloseDynamicIndexes[sixthOfPracticeTargets];
    for (int i = 0; i < sixthOfPracticeTargets; i++) { //pick the first random half of the close targets as static, put it in the lists.
        practiceCloseStaticIndexes[i] = practiceCloseIndexes[i];
        practiceMovementLabelList[practiceCloseStaticIndexes[i]] = "static";
    }
    for (int i = 0; i < sixthOfPracticeTargets; i++) {
        int index = sixthOfPracticeTargets + i;
        practiceCloseDynamicIndexes[i] = practiceCloseIndexes[index];//pick the second random half of the close targets as dynamic, put it in the lists.
        practiceMovementLabelList[practiceCloseDynamicIndexes[i]] = "dynamic";
    }

    /*####################### Practice MEDIUM ########################*/
    int practiceMediumIndexes[thirdOfPracticeTargets];
    for (int i = 0; i < thirdOfPracticeTargets; i++) {
        int index = thirdOfPracticeTargets + i; //grab the indexes between 1 third and 2 thirds
        practiceMediumIndexes[i] = PracticeProximityIndexes[index];
        practiceDistanceLabelList[practiceMediumIndexes[i]] = "medium"; //add the label "medium" to the target randomly selected as a medium target.
    }
    shuffle_array(practiceMediumIndexes, thirdOfPracticeTargets);
    int practiceMediumStaticIndexes[sixthOfPracticeTargets];
    int practiceMediumDynamicIndexes[sixthOfPracticeTargets];
    for (int i = 0; i < sixthOfPracticeTargets; i++) { //pick the first random half of the medium targets as static, put it in the lists.
        practiceMediumStaticIndexes[i] = practiceMediumIndexes[i];
        practiceMovementLabelList[practiceMediumStaticIndexes[i]] = "static";
    }
    for (int i = 0; i < sixthOfPracticeTargets; i++) {
        int index = sixthOfPracticeTargets + i;
        practiceMediumDynamicIndexes[i] = practiceMediumIndexes[index];//pick the second random half of the medium targets as dynamic, put it in the lists.
        practiceMovementLabelList[practiceMediumDynamicIndexes[i]] = "dynamic";
    }

    /*####################### Practice FAR ########################*/
    int practiceFarIndexes[thirdOfPracticeTargets];
    for (int i = 0; i < thirdOfPracticeTargets; i++) {
        int index = (2 * thirdOfPracticeTargets) + i; //grab the indexes from 2 thirds until the end.
        practiceFarIndexes[i] = PracticeProximityIndexes[index];
        practiceDistanceLabelList[practiceFarIndexes[i]] = "far"; //add the label "far" to the target randomly selected as a far target.
    }
    shuffle_array(practiceFarIndexes, thirdOfPracticeTargets);
    int practiceFarStaticIndexes[sixthOfPracticeTargets];
    int practiceFarDynamicIndexes[sixthOfPracticeTargets];
    for (int i = 0; i < sixthOfPracticeTargets; i++) { //pick the first random half of the far targets as static, put it in the lists.
        practiceFarStaticIndexes[i] = practiceFarIndexes[i];
        practiceMovementLabelList[practiceFarStaticIndexes[i]] = "static";
    }
    for (int i = 0; i < sixthOfPracticeTargets; i++) {
        int index = sixthOfPracticeTargets + i;
        practiceFarDynamicIndexes[i] = practiceFarIndexes[index];//pick the second random half of the far targets as dynamic, put it in the lists.
        practiceMovementLabelList[practiceFarDynamicIndexes[i]] = "dynamic";
    }


    // generate N random numbers
    int N = totalTargets;

    for (int i = 0; i < N; i++) {
        double theta = M_PI * uniform01(generator); //theta is the azimuthal angle, starting from the X axis, giving an angle on the x,y plane range is 360 degrees or from 0 to 2 pi. To change this to the correct range, just remove the 2 *  
        double phi = acos(1 - 2 * uniform02(generator)); //phi is the polar angle, starting from the z axis, giving and angle on the z and the custom plane defined by the azimuthal angle. range is from 0 to 180 degrees or from 0 to pi.
        double x = sin(phi) * cos(theta); //assuming a radius of 1
        double y = sin(phi) * sin(theta);
        double z = cos(phi);
        //make a third of the points close, another medium, the rest far.
        //for every one of those groups, make a random half selection dynamic instead of static.
        //multiply the vectors by the corresponding radius, store those points.
        //put the coordinates in the list.
        int scalar = 0;
        if (distanceLabelList[i] == "close") scalar = closeRadius;
        else if (distanceLabelList[i] == "medium") scalar = mediumRadius;
        else scalar = farRadius;

        targetLocationList[i][0] = scalar * x;
        targetLocationList[i][1] = scalar * y;
        targetLocationList[i][2] = (scalar * z) + verticalOffset; //vertical offset ensures the target spawns above the ground, and does not clip it.
    }

    // fill the practice targets with random points
    for (int i = 0; i < practiceTargets; i++) {
        double theta = M_PI * uniform01(generator); //theta is the azimuthal angle, starting from the X axis, giving an angle on the x,y plane range is 360 degrees or from 0 to 2 pi. To change this to the correct range, just remove the 2 *  
        double phi = acos(1 - 2 * uniform02(generator)); //phi is the polar angle, starting from the z axis, giving and angle on the z and the custom plane defined by the azimuthal angle. range is from 0 to 180 degrees or from 0 to pi.
        double x = sin(phi) * cos(theta); //assuming a radius of 1
        double y = sin(phi) * sin(theta);
        double z = cos(phi);
        //make a third of the points close, another medium, the rest far.
        //for every one of those group, make a random half selection dynamic instead of static.
        //multiply their vectors by the corresponding radius, store those points.
        //put the coordinates in the list.
        int scalar = 0;
        if (practiceDistanceLabelList[i] == "close") scalar = closeRadius;
        else if (practiceDistanceLabelList[i] == "medium") scalar = mediumRadius;
        else scalar = farRadius;

        practiceTargetLocationList[i][0] = scalar * x;
        practiceTargetLocationList[i][1] = scalar * y;
        practiceTargetLocationList[i][2] = (scalar * z) + verticalOffset;


    }
    //writes the file, with the data stored in the three data arrays.
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
            file << distanceLabelList[index] + ", " + movementLabelList[index] + ", ";
            file << targetLocationList[index][0] << ", " << targetLocationList[index][1] << ", " << targetLocationList[index][2] << "\n";
        }
        file << "@ \n";

    }
    file << "$ \n";
    for (int i = 0; i < practiceTargets; i++) {
        file << practiceDistanceLabelList[i] << ", " << practiceMovementLabelList[i] << ", ";
        file << practiceTargetLocationList[i][0] << ", " << practiceTargetLocationList[i][1] << ", " << practiceTargetLocationList[i][2] << "\n";

    }
    file << "$ \n";

    file.close();
    return 0;
}

void shuffle_array(int arr[], int n)
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(arr, arr + n, default_random_engine(seed));
}


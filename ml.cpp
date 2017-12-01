#include <unordered_map>
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>
#include <sstream>
#include <ctime>
#include <cmath>
#include <climits>
using namespace std;

// Prototypes
string welcome();
void readFile(string);
void pickAlgorithm();
void normalizeData(); 
void forwardFeatureSearch();
void backwardEliminationSearch();
void printDataInfo();
void shuffleData();
void seedTime();
void printSet(const vector< double> &);
double leaveOneOutCrossValidation(const vector< vector<double> > &); 
double getDistance (const vector<double> &, const vector<double> &); 

// Global Variables
vector< vector<double> > rawData;
vector< vector<double> > features;
vector<double> classifications;
vector<double> masterFeatureIDS;

// Beginning
int main() {
    seedTime();
    string filename = welcome();
    readFile(filename);
    pickAlgorithm();
    return 0;
}

// Welcome prompt that returns filename string.
string welcome() {
    srand((unsigned)time(0));
    cout << "Welcome to Luis Lopez's Feature Selection Algorithm." << endl;
    cout << "Type in the name of the file to test: ";
    string filename;
    getline(cin, filename);
    return filename;
}

// https://stackoverflow.com/questions/1894886/
// parsing-a-comma-delimited-stdstring
//
// Reads text from user input filename and populates global vector's.
void readFile(string filename) {
    vector<double> data;
    double d;
    string line;
    ifstream file;
    file.open(filename);

    if (!file.is_open()) {
        cout << "Error opening file. Closing program!" << endl;
        exit(1);
    }

    while (getline(file, line)) {
        stringstream ss(line);
        while (ss >> d) {
            data.push_back(d);
        }
        rawData.push_back(data);
        data.clear();
    }
    file.close();

    // Populating feature vector vector
    for (unsigned i = 1; i < rawData.at(0).size(); i++) { 
        vector<double> featureColumn;
        for (unsigned j = 0; j < rawData.size(); j++) {
            featureColumn.push_back(rawData.at(j).at(i));
        }
        features.push_back(featureColumn);
        featureColumn.clear();
    }

    // Populating master feature IDs. Initially gives each feature ID in
    // ascending order from 0 to n-1. This is useful because eventually I will
    // shuffle the data around but need to keep track of the features. 
    for (unsigned i = 0; i < features.size(); i++) {
        masterFeatureIDS.push_back(i);
    }

    // Populating parallel classificationss vector
    for (unsigned i = 0; i < rawData.size(); i++) {
        classifications.push_back(rawData.at(i).at(0));
    }
}

void pickAlgorithm() {
    char algorithm;
    cout << "\nType the number of the algorithm you want to run.\n\n";
    cout << "\t1) Forward Selection\n";
    cout << "\t2) Backward Elimination\n";
    cout << "\t3) Luis's Special Algorithm\n\n\t\t\t\t";
    cin >> algorithm;
    cin.ignore();
    switch(algorithm) {
        case '1':
            printDataInfo();
            shuffleData();
            forwardFeatureSearch();
            break;
        case '2':
            printDataInfo();
            backwardEliminationSearch();
            break;
        case '3':
            printDataInfo();
            cout << "Hello: " << rand() % features.size() << endl;
            break;
        default:
            cout << "\nInvalid Choice. Please try again.\n";
            pickAlgorithm();
            break;
    }
}

// http://www.techcrashcourse.com/2017/01/
// cpp-program-to-calculate-standard-deviation.html
void normalizeData() {
    double sum;
    double deviation;
    double mean;
    unsigned size = features.size();
    unsigned instanceSize = features.at(0).size();

    for (unsigned i = 0; i < size; i++ ) {
        sum = 0;
        deviation = 0;

        for (unsigned j = 0; j < instanceSize; j++) {
            sum += features.at(i).at(j);
        }

        mean = sum / instanceSize;

        for (unsigned j = 0; j < instanceSize; j++) {
            deviation += pow(features.at(i).at(j) - mean, 2.0);
        }

        deviation = sqrt(deviation/size);

        for (unsigned j = 0; j < instanceSize; j++) {
            double temp = features.at(i).at(j);
            features.at(i).at(j) = (temp - mean) / deviation;
        }
    }
}

double leaveOneOutCrossValidation(const vector< vector<double> > &currentSet) {
    double distance;
    double percentage;
    int nearestNeighbor;
    int correctClassification = 0;
    unsigned instanceSize = currentSet.at(0).size();
    unsigned totalFeatures = currentSet.size();

    for (unsigned i = 0; i < instanceSize; i++ ) {
        double minDistance = UINT_MAX;
        vector<double> testPoint;

        // Creating a test point
        for (unsigned j = 0; j < totalFeatures; j++) {
            testPoint.push_back(currentSet.at(j).at(i));
        }

        // Creating new points from current set. Will use these points to get
        // Euclidian Distance from the created testPoint.
        for (unsigned j = 0; j < instanceSize; j++) {
            if (j != i) {
                vector<double> point; 
                for (unsigned k = 0; k < totalFeatures; k++) {
                    point.push_back(currentSet.at(k).at(j));
                }

                distance = getDistance(testPoint, point);
                if (distance < minDistance) {
                    minDistance = distance;
                    nearestNeighbor = j;
                }
            }
        }

        // If test point's closest neighbor is of the same class, increment
        // number of correct classifications.
        if (classifications.at(i) == classifications.at(nearestNeighbor)) {
            correctClassification++;
        }
        testPoint.clear();
    }

    percentage = correctClassification / static_cast<double>(instanceSize);
    return percentage * 100.00;
}

double getDistance (const vector<double> &test, const vector<double> &training) {
    double total = 0;
    for (unsigned i = 0; i < test.size(); i++) {
        double temp = test.at(i) - training.at(i);
        temp = pow(temp, 2.0);
        total += temp;
    }
    total = sqrt(total);
    return total;
}

void forwardFeatureSearch() { 
    vector< vector<double> > currentFeatureSet; // Initializing empty set
    unordered_map<int, bool> addedFeatures;     // To keep track of added features
    vector<double> currentFeatureSetIDS;        // Keeps track of each feature index
    vector<double> bestFeatures;
    double bestTotalAccuracy = 0;

    cout << "Beginning search" << endl << endl;
    for (unsigned i = 0; i < features.size(); i++) {
        int featureID = 0;
        double bestNewAccuracy = 0;
        
        for (unsigned j = 0; j < features.size(); j++) {
            if (!addedFeatures[masterFeatureIDS[j]]) {
                currentFeatureSet.push_back(features.at(j));
                currentFeatureSetIDS.push_back(masterFeatureIDS[j]);
                double accuracy = leaveOneOutCrossValidation(currentFeatureSet);

                cout << "\tUsing features(s) ";
                printSet(currentFeatureSetIDS);
                cout << "accuracy is " << accuracy << "%" << endl;

                if (accuracy > bestNewAccuracy || 
                  (accuracy == bestNewAccuracy && 
                  currentFeatureSetIDS.size() < bestFeatures.size())) {

                    bestNewAccuracy = accuracy;
                    featureID = masterFeatureIDS[j];
                }
                currentFeatureSet.pop_back();
                currentFeatureSetIDS.pop_back();
            }
        }
        addedFeatures[featureID] = true;
        currentFeatureSetIDS.push_back(featureID);
        currentFeatureSet.push_back(features.at(currentFeatureSetIDS.back()));

        if (bestNewAccuracy > bestTotalAccuracy) {
            bestTotalAccuracy = bestNewAccuracy;
            bestFeatures = currentFeatureSetIDS;
        }
        else {
            cout << endl << "(Warning, Accuracy has decreased! Continuing search ";
            cout << "in case of local maxima)";
        }

        cout << endl << "Feature set ";
        printSet(currentFeatureSetIDS);
        cout << "was best, accuracy is " << bestNewAccuracy << "%" << endl << endl;
    }
    cout << "Finished search! The best feature subset is ";
    printSet(bestFeatures);
    cout << "which has an accuracy of " << bestTotalAccuracy << "%" << endl;
}

void backwardEliminationSearch() {
    vector< vector<double> > currentFeatureSet; // Initializing empty feature set
    unordered_map<int, bool> removedFeatures;   // Keeps track of removed features
    vector<double> currentFeatureSetIDS;        // Keeps track of each feature index
    vector<double> bestFeatures;
    vector<double> bestNewFeatures;
    double bestTotalAccuracy = 0;
    double bestNewAccuracy = 0;
    double accuracy = 0;            // The result of k-fold cross validation 

    cout << "\nBeginning search " << endl << endl;

    // Filling currentFeatureSetIDS with every feature's index and filling the
    // currentFeatureSet with every feature. 
    for (unsigned i = 0; i < features.size(); i++) {
        currentFeatureSet.push_back(features.at(i));
        currentFeatureSetIDS.push_back(i);
    }

    accuracy = leaveOneOutCrossValidation(currentFeatureSet);

    cout << "\tUsing features(s) ";
    printSet(currentFeatureSetIDS);
    cout << "accuracy is " << accuracy << "%" << endl;

    if (accuracy > bestTotalAccuracy) {
        bestTotalAccuracy = accuracy;
        bestFeatures = currentFeatureSetIDS;
    }
    cout << endl << "Feature set ";
    printSet(currentFeatureSetIDS);
    cout << "was best, accuracy is " << bestTotalAccuracy << "%" << endl << endl;

    currentFeatureSet.clear();
    currentFeatureSetIDS.clear();

    // Beginning to remove elements one at at time now.
    for (unsigned i = 0; i < features.size()-1; i++) {
        int featureID = 0;
        bestNewAccuracy = 0;

        for (unsigned j = 0; j < features.size(); j++) {
            if (!removedFeatures[masterFeatureIDS[j]]) {

                // If feature j is not among the removed features and not the current 
                // feature to be removed, rebuild current set, then run k-fold on 
                // the current set
                for (unsigned k = 0; k < features.size(); k++) {
                    if (!removedFeatures[k] && k != j) {
                        currentFeatureSet.push_back(features.at(masterFeatureIDS[k]));
                        currentFeatureSetIDS.push_back(masterFeatureIDS[k]);
                    }
                }

                accuracy = leaveOneOutCrossValidation(currentFeatureSet);

                cout << "\tUsing features(s) ";
                printSet(currentFeatureSetIDS);
                cout << "accuracy is " << accuracy << "%" << endl;

                if (accuracy > bestNewAccuracy || 
                  (accuracy == bestNewAccuracy && 
                  currentFeatureSetIDS.size() < bestNewFeatures.size())) {

                    bestNewAccuracy = accuracy;
                    bestNewFeatures.assign(currentFeatureSetIDS.begin(), 
                                           currentFeatureSetIDS.end());
                    featureID = masterFeatureIDS[j];
                }
            }
            currentFeatureSet.clear();
            currentFeatureSetIDS.clear();
        }

        // After internal loop tries removing elements.
        removedFeatures[featureID] = true;
        if (bestNewAccuracy > bestTotalAccuracy) {
            bestTotalAccuracy = bestNewAccuracy;
            bestFeatures.assign(bestNewFeatures.begin(),
                                bestNewFeatures.end());
        }
        else {
            cout << endl << "(Warning, Accuracy has decreased! Continuing search ";
            cout << "in case of local maxima)";
        }

        cout << endl << "Feature set ";
        printSet(bestNewFeatures);
        cout << "was best, accuracy is " << bestNewAccuracy << "%" << endl << endl;
    }
    cout << "Finished search! The best feature subset is ";
    printSet(bestFeatures);
    cout << "Which has an accuracy of " << bestTotalAccuracy << "%" << endl;
}

void shuffleData() {
    unordered_map<int, bool> table;
    vector< vector<double > > vecVecTemp;
    vecVecTemp.push_back(features.at(0));
    vecVecTemp.push_back(features.at(1));
    vecVecTemp.push_back(features.at(2));
    for (unsigned i = 3; i < features.size(); i++) {
        vecVecTemp.push_back(features.at(i));
    }
    features.swap(vecVecTemp);

    vector<double> idTemp;
    idTemp.push_back(masterFeatureIDS.at(0));
    idTemp.push_back(masterFeatureIDS.at(1));
    idTemp.push_back(masterFeatureIDS.at(2));
    for (unsigned i = 3; i < masterFeatureIDS.size(); i++) {
        idTemp.push_back(masterFeatureIDS.at(i));
    }
    masterFeatureIDS.swap(idTemp);
}

void seedTime() {
    srand(time(0));
}

void printSet(const vector< double> &currentFeatureSetIDS) {
    cout << "{";
    for (unsigned j = 0; j < currentFeatureSetIDS.size(); j++) {
        if (j != currentFeatureSetIDS.size() -1)
            cout << currentFeatureSetIDS.at(j)+1 << ",";
        else 
            cout << currentFeatureSetIDS.at(j)+1;
    }
    cout << "} ";
}

void printDataInfo() {
    cout << "This dataset has " << features.size() << " features (not including ";
    cout << "the class attribute), with " << features.at(0).size() << " instances.\n\n";
    cout << "Please wait while I normalize the data... ";
    normalizeData(); 
    cout << "Done!\n\n";
}



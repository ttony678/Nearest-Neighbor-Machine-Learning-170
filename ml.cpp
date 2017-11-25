#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>
#include <sstream>
#include <ctime>
#include <unordered_map>
using namespace std;

// Prototypes
string welcome();
void readFile(string);
double leaveOneOutCrossValidation(); 
void forwardFeatureSearch();
void backwardEliminationSearch();
void printSet(const vector< double> &);
void printVecVector(vector< vector<double> >);
void printVector(vector<double>);

// Global Variables
vector< vector<double> > rawData;
vector< vector<double> > features;
vector<double> classifications;

// Beginning
int main() {
    string filename = welcome();
    readFile(filename);

    // forwardFeatureSearch();
    backwardEliminationSearch();

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

    // Populating feature vector vector
    for (unsigned i = 1; i < rawData.at(0).size(); i++) { 
        vector<double> featureColumn;
        for (unsigned j = 0; j < rawData.size(); j++) {
            featureColumn.push_back(rawData.at(j).at(i));
        }
        features.push_back(featureColumn);
        featureColumn.clear();
    }

    // Populating parallel classificationss vector
    for (unsigned i = 0; i < rawData.size(); i++) {
        classifications.push_back(rawData.at(i).at(0));
    }

    file.close();
}

double leaveOneOutCrossValidation() {
    double accuracy;
    accuracy = rand()%101+1;
    return accuracy;
}

void forwardFeatureSearch() { 
    vector< vector<double> > currentFeatureSet; // Initializing empty set
    unordered_map<int, bool> addedFeatures;     // To keep track of added features
    vector<double> currentFeatureSetIDS;        // Keeps track of each feature index
    vector<double> bestFeatures;
    double bestTotalAccuracy = 0;

    cout << endl << "Beginning search" << endl << endl;
    for (unsigned i = 0; i < features.size(); i++) {
        int featureID = 0;
        double bestNewAccuracy = 0;
        
        for (unsigned j = 0; j < features.size(); j++) {
            if (!addedFeatures[j]) {
                currentFeatureSet.push_back(features.at(j));
                currentFeatureSetIDS.push_back(j);
                double accuracy = leaveOneOutCrossValidation();

                cout << "\tUsing features(s) ";
                printSet(currentFeatureSetIDS);
                cout << "accuracy is " << accuracy << " %" << endl;

                if (accuracy > bestNewAccuracy) {
                    bestNewAccuracy = accuracy;
                    featureID = j;
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

    accuracy = leaveOneOutCrossValidation();

    cout << "\tUsing features(s) ";
    printSet(currentFeatureSetIDS);
    cout << "accuracy is " << accuracy << " %" << endl;

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
            if (!removedFeatures[j]) {

                // If feature j is not among the removed features and not the current 
                // feature to be removed, rebuild current set, then run k-fold on 
                // the current set
                for (unsigned k = 0; k < features.size(); k++) {
                    if (!removedFeatures[k] && k != j) {
                        currentFeatureSet.push_back(features.at(k));
                        currentFeatureSetIDS.push_back(k);
                    }
                }
                double accuracy = leaveOneOutCrossValidation();

                cout << "\tUsing features(s) ";
                printSet(currentFeatureSetIDS);
                cout << "accuracy is " << accuracy << " %" << endl;

                if (accuracy > bestNewAccuracy) {
                    bestNewAccuracy = accuracy;
                    bestNewFeatures.assign(currentFeatureSetIDS.begin(), 
                                           currentFeatureSetIDS.end());
                    featureID = j;
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

void printVecVector(vector< vector<double> > vec) {
    for (unsigned i = 0; i < vec.size(); i++) {
        for (unsigned j = 0; j < vec.at(i).size(); j++) {
            cout << vec.at(i).at(j) << " ";
        }
        cout << endl;
    }
}

void printVector(vector<double> vec) {
    for (unsigned i = 0; i < vec.size(); i++) {
        cout << vec.at(i) << " ";
    }
    cout << endl;
}




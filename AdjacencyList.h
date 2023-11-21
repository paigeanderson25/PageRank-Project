#include <map>
#include <bits/stdc++.h>
#include <vector>
using namespace std;

class AdjacencyList {

private:
    int numEntries; // num lines entered
    int powIter; // num power iterations


    // maps
    map<string, vector<string>> toKeyMap; // map matching string to its out strings
    map<string, vector<string>> fromKeyMap; // map matching out strings to to strings
    map<string, double> outdegreeMap; // map matching string to outdegree (use string map size)
    map<string, vector<pair<string, double>>> adjList; // map matching string to pairs of outdegrees
    map<string, double> rankMap; // rankMap initialized to 1/V
    map<string, double> rankMap2; // stores updated rank map

public:
    //constructor
    AdjacencyList(int n, int p);

    // functions
    void CreateInitialMaps(string fromPage, string toPage);
    void CreateAdjList(); // creates stringVecMap, outdegreeMap and adjList to create graph
    void AdjustRankMap();
    void PageRank(); // print final rankMap in alphabetical order

};

// constructor
AdjacencyList::AdjacencyList(int n, int p) {
    // integers
    numEntries = n;
    powIter = p;
}

// create initial string map
void AdjacencyList::CreateInitialMaps(string toPage, string fromPage) {
    // if map does not include the fromPage, add as key and push back toPage; else just push back toPage
    if (toKeyMap.count(toPage) < 1) {
        toKeyMap[toPage];
        toKeyMap[toPage].push_back(fromPage);
        outdegreeMap.insert({toPage, 0});
    }
    else {
        toKeyMap[toPage].push_back(fromPage);
        outdegreeMap.insert({toPage, 0});
    }

    if(fromKeyMap.count(fromPage) < 1) {
        fromKeyMap[fromPage];
        fromKeyMap[fromPage].push_back(toPage);
        outdegreeMap.insert({fromPage, 0});
    }
    else {
        fromKeyMap[fromPage].push_back(toPage);
        outdegreeMap.insert({fromPage, 0});
    }
}

// create graph
void AdjacencyList::CreateAdjList() {
    // use stringVecMap to create outdegreeMap: iterate through stringVecMap; add to map string and 1/vector.size()
    map<string, vector<string>>:: iterator it;
    double currSize = 0;
    double outDegree = 0;
    string currString = "";

    for (it = fromKeyMap.begin(); it != fromKeyMap.end(); it++) {
        currSize = it->second.size();
        outDegree = 1.0/currSize;
        currString = it->first;

        outdegreeMap[currString] = outDegree;
    }

    // use outDegreeMap to create adjList --> key = string; value = vector of string, outdegree pairs
    // iterate through string vector; add string as key; iterate through vector adding pair for each string
    for (it = toKeyMap.begin(); it != toKeyMap.end(); it++) {
        currString = it->first;
        currSize = it -> second.size();
        adjList[currString];
        string stringOutdegree = "";
        for (int i = 0; i < currSize; i++) {
            stringOutdegree = it->second.at(i); // set string outdegree = to i value of string vector
            adjList[currString].push_back({stringOutdegree, outdegreeMap[stringOutdegree]});
        }
    }

    // create initial rank map by creating vector of unique strings
    double initialRank = 1.0/(outdegreeMap.size());
    map<string, double>::iterator it2;
    for (it2 = outdegreeMap.begin(); it2 != outdegreeMap.end(); it2++) {
        rankMap.insert({it2->first, (initialRank)});
    }
}

// create adjusted rank map
void AdjacencyList::AdjustRankMap() {
    map<string, vector<pair<string, double>>>:: iterator it;
    map<string, double>::iterator it2;

    string currString = "";
    int vecSize = 0;
    double currRank = 0;
    double newValue = 0;
    //rankMap2 = rankMap;
    for (it2 = outdegreeMap.begin(); it2 != outdegreeMap.end(); it2++) {
        rankMap2.insert({it2->first, 0.0});
    }


    // iterate through adjacency list; multiply string R by each string M and add
    for (it = adjList.begin(); it != adjList.end(); it++) {
        // find the vector size then iterate for vector size; multiplying, adding, changing rankMap
        currString = it->first;
        vecSize = it->second.size();
        vector<pair<string,double>> currVector = it->second;
        newValue = 0;

        for (int i = 0; i < vecSize; i++) {
            currRank = rankMap[currVector.at(i).first];
            newValue = newValue + (currRank*(currVector.at(i).second));
        }

        rankMap2[currString] = newValue;
    }
    rankMap = rankMap2;
}

// multiply graph and rank map, then print final rank map in alphabetical order
void AdjacencyList::PageRank() {
    CreateAdjList(); // create graph

    map<string, double>:: iterator it;

    // perform power iterations
    if (powIter == 2) {
        // perform singular power iteration
        AdjustRankMap();
    }
    else if (powIter > 2) {
        // perform p power iterations
        for (int i = 1; i < powIter; i++) {
            AdjustRankMap();
        }
    }


    for (it = rankMap.begin(); it != rankMap.end(); it++) {
        cout << it->first << " " << fixed << setprecision(2) << (it->second) << endl;
    }
}







#include <iostream>
#include "AdjacencyList.h"
using namespace std;

int main() {
    // create variables
    int n = 0;
    int p = 0;
    string fromPage = "";
    string toPage = "";

    // read in first line
    cin >> n;
    cin >> p;

    // create graph object
    AdjacencyList graph = AdjacencyList(n, p);

    // read in strings
    for (int i = 0; i < n; i++) {
        cin >> fromPage;
        cin >> toPage;
        graph.CreateInitialMaps(toPage, fromPage);
    }
    // call page rank
    graph.PageRank();

    return 0;
}

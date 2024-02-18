#include <bits/stdc++.h>

using namespace std;

struct Item {
    int weight;
    int value;
};

int knapsack(vector<Item>& items, int capacity, int index, vector<int>& solution) {
    if (index < 0 || capacity == 0) {
        return 0;
    }

    if (items[index].weight > capacity) {
        return knapsack(items, capacity, index - 1, solution);
    }

    vector<int> includeSolution(solution);
    includeSolution[index] = 1;
    int include = items[index].value + knapsack(items, capacity - items[index].weight, index - 1, includeSolution);

    vector<int> excludeSolution(solution);
    excludeSolution[index] = 0;
    int exclude = knapsack(items, capacity, index - 1, excludeSolution);

    if (include > exclude) {
        solution = includeSolution;
        return include;
    } else {
        solution = excludeSolution;
        return exclude;
    }
}

int main() {
    string inputFilename, outputFilename;

    cout << "Enter the path of input file: ";
    cin >> inputFilename;

    ifstream inputFile(inputFilename);
    if (!inputFile) {
        cerr << "Error: Unable to open the input file." << endl;
        return 1;
    }

    int numItems, capacity;
    inputFile >> numItems >> capacity;

    vector<Item> items(numItems);
    for (int i = 0; i < numItems; i++) {
        inputFile >> items[i].weight >> items[i].value;
    }

    vector<int> solution(numItems, 0);
    int maxValue = knapsack(items, capacity, numItems - 1, solution);

    cout << "Enter the output filename: ";
    cin >> outputFilename;

    ofstream outputFile(outputFilename);
    if (!outputFile) {
        cerr << "Error: Unable to open the output file." << endl;
        return 1;
    }

    // Write the maximum value to the output file
    outputFile << "max profit:" << maxValue << endl;

    // Write the selected items to the output file
    outputFile << "solution:";
    for (int i = 0; i < numItems; i++) {
        outputFile << solution[i];
    }

    cout << "Results have been written to " << outputFilename << endl;

    return 0;
}

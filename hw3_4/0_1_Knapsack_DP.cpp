#include <bits/stdc++.h>

using namespace std;

struct Item {
    int weight;
    int value;
};

int main() 
{
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

    // Create a 2D vector for dynamic programming
    vector<vector<int>> dp(numItems + 1, vector<int>(capacity + 1, 0));

    for (int i = 1; i <= numItems; i++) {
        for (int w = 1; w <= capacity; w++) {
            if (items[i-1].weight <= w) {
                dp[i][w] = max(dp[i-1][w], dp[i-1][w - items[i-1].weight] + items[i-1].value);
            } else {
                dp[i][w] = dp[i-1][w];
            }
        }
    }

    int maxValue = dp[numItems][capacity];

    // Backtrack to find which items are selected
    vector<int> selectedItems(numItems, 0);
    int w = capacity;
    for (int i = numItems; i > 0; i--) {
        if (dp[i][w] != dp[i-1][w]) {
            selectedItems[i-1] = 1;
            w -= items[i-1].weight;
        }
    }

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
        outputFile << selectedItems[i];
    }

    cout << "Results have been written to " << outputFilename << endl;

    return 0;
}

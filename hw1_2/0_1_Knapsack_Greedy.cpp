#include <bits/stdc++.h>

using namespace std;

struct Item {
    int weight;
    int value;
    double valueToWeightRatio;
    int index; // To keep track of the original index of the item
};

// Function to compare items based on their value-to-weight ratios
bool compareItems(const Item& item1, const Item& item2) {
    return item1.valueToWeightRatio > item2.valueToWeightRatio;
}

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
        items[i].valueToWeightRatio = static_cast<double>(items[i].value) / items[i].weight;
        items[i].index = i;
    }

    // Sort the items based on their value-to-weight ratios in descending order
    sort(items.begin(), items.end(), compareItems);

    int currentWeight = 0;
    int maxValue = 0;
    vector<int> selectedItems(numItems, 0);

    for (int i = 0; i < numItems; i++) {
        if (currentWeight + items[i].weight <= capacity) {
            currentWeight += items[i].weight;
            maxValue += items[i].value;
            selectedItems[items[i].index] = 1;
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

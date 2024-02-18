#include<bits/stdc++.h>

using namespace std;

struct Item {
    int weight;
    int value;
};

const int POPULATION_SIZE = 100;
const double CROSSOVER_RATE = 0.85;
const double MUTATION_RATE = 0.55;
const int TOURNAMENT_SIZE = 15;

// Random number generator
int randRange(int min, int max) {
    return min + rand() % (max - min + 1);
}

// Function to calculate fitness
int evaluate(const vector<int>& solution, const vector<Item>& items, int capacity) {
    int totalValue = 0, totalWeight = 0;
    for (size_t i = 0; i < solution.size(); i++) {
        if (solution[i]) {
            totalValue += items[i].value;
            totalWeight += items[i].weight;
            if (totalWeight > capacity) return 0;
        }
    }
    return totalValue;
}

// Tournament Selection
vector<int> tournamentSelection(const vector<vector<int>>& population, const vector<Item>& items, int capacity) {
    vector<int> best;
    int bestFitness = -1;
    for (int i = 0; i < TOURNAMENT_SIZE; ++i) {
        int idx = randRange(0, population.size() - 1);
        int fitness = evaluate(population[idx], items, capacity);
        if (fitness > bestFitness) {
            bestFitness = fitness;
            best = population[idx];
        }
    }
    return best;
}

// One-Point Crossover
void onePointCrossover(vector<int>& parent1, vector<int>& parent2) {
    int crossoverPoint = randRange(1, parent1.size() - 2);
    for (int i = crossoverPoint; i < parent1.size(); ++i) {
        swap(parent1[i], parent2[i]);
    }
}

// Two-Point Crossover
void twoPointCrossover(vector<int>& parent1, vector<int>& parent2) {
    int point1 = randRange(1, parent1.size() - 2);
    int point2 = randRange(point1, parent1.size() - 1);
    for (int i = point1; i <= point2; ++i) {
        swap(parent1[i], parent2[i]);
    }
}

// Uniform Crossover
void uniformCrossover(vector<int>& parent1, vector<int>& parent2) {
    for (size_t i = 0; i < parent1.size(); ++i) {
        if (rand() % 2) {
            swap(parent1[i], parent2[i]);
        }
    }
}

// Mutation
void mutate(vector<int>& individual) {
    for (int& gene : individual) {
        if ((rand() / (double)RAND_MAX) < MUTATION_RATE) {
            gene = 1 - gene; // Flip the bit
        }
    }
}

// Main Genetic Algorithm Function
vector<int> geneticAlgorithm(const vector<Item>& items, int capacity, int evaluationMax) {
    vector<vector<int>> population(POPULATION_SIZE, vector<int>(items.size()));
    for (auto& individual : population) {
        for (int& gene : individual) {
            gene = randRange(0, 1);
        }
    }

    vector<int> bestSolution;
    int bestFitness = -1;

    for (int evaluation = 0; evaluation < evaluationMax; ++evaluation) {
        vector<vector<int>> newPopulation;

        while (newPopulation.size() < population.size()) {
            vector<int> parent1 = tournamentSelection(population, items, capacity);
            vector<int> parent2 = tournamentSelection(population, items, capacity);

            if ((rand() / (double)RAND_MAX) < CROSSOVER_RATE) {
                int crossoverMethod = randRange(1, 3);
                if (crossoverMethod == 1) {
                    onePointCrossover(parent1, parent2);
                } else if (crossoverMethod == 2) {
                    twoPointCrossover(parent1, parent2);
                } else {
                    uniformCrossover(parent1, parent2);
                }
            }

            mutate(parent1);
            mutate(parent2);

            newPopulation.push_back(parent1);
            if (newPopulation.size() < population.size()) {
                newPopulation.push_back(parent2);
            }
        }

        population = newPopulation;

        // Parallel fitness evaluation
        vector<thread> threads;
        vector<int> fitnesses(population.size(), 0);

        for (size_t i = 0; i < population.size(); ++i) {
            threads.emplace_back([&fitnesses, &population, &items, capacity, i]() {
                fitnesses[i] = evaluate(population[i], items, capacity);
            });
        }

        for (auto& t : threads) {
            if (t.joinable()) {
                t.join();
            }
        }

        for (size_t i = 0; i < population.size(); ++i) {
            if (fitnesses[i] > bestFitness) {
                bestFitness = fitnesses[i];
                bestSolution = population[i];
            }
        }
    }

    return bestSolution;
}

int main() {
    srand(time(nullptr));

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

    int evaluationMax;
    cout << "Enter the maximum number of evaluations: ";
    cin >> evaluationMax;

    cout << "Enter the output filename: ";
    cin >> outputFilename;

    ofstream outputFile(outputFilename);
    if (!outputFile) {
        cerr << "Error: Unable to open the output file." << endl;
        return 1;
    }

    vector<int> bestSolutions(30, 0);
    vector<double> executionTimes(30, 0.0);

    for (int run = 0; run < 30; run++) {
        auto startTime = chrono::high_resolution_clock::now();

        vector<int> solution = geneticAlgorithm(items, capacity, evaluationMax);
        int solutionValue = evaluate(solution, items, capacity);
        bestSolutions[run] = solutionValue;

        auto endTime = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();
        executionTimes[run] = duration / 1000.0;

        outputFile << "Run " << (run + 1) << ": Max profit:" << solutionValue << endl;
        outputFile << "Solution:";
        for (int gene : solution) {
            outputFile << gene;
        }
        outputFile << endl;

        cout << "Run " << (run + 1) << ": Execution time = " << executionTimes[run] << " seconds" << endl;
    }

    int sumBest = accumulate(bestSolutions.begin(), bestSolutions.end(), 0);
    double averageBest = static_cast<double>(sumBest) / 30;
    
    printf("Average Best Solution: %f\n", averageBest);

    cout << "Results have been written to " << outputFilename << endl;

    return 0;
}

# NSYSU CSE Algorithms Course Homework

This repository hosts homework assignments for the Algorithms course offered by the Department of Computer Science and Engineering at National Sun Yat-sen University (NSYSU). The assignments focus on solving algorithmic problems, with a particular emphasis on the knapsack problem and genetic algorithms.

## Directory Structure

- `hw1_2/` - Contains solutions for the classic and fractional knapsack problems.
- `hw3_4/` - Features implementations for dynamic programming solutions to the knapsack problem and a genetic algorithm approach.

## Assignment Descriptions

### HW1_2: Knapsack Problem Solutions

This folder contains C++ implementations for solving the knapsack problem:

- **Classic Knapsack Problem**: Determines the maximum value that can be obtained from a set of items without exceeding the capacity of the knapsack. Utilizes a recursive approach to explore all possible combinations of items.
- **Fractional Knapsack Problem**: Similar to the classic problem but allows for items to be broken into smaller pieces. The solution sorts items by their value-to-weight ratio and fills the knapsack to maximize total value.

### HW3_4: Advanced Knapsack Solutions and Genetic Algorithm

This directory includes advanced solutions to the knapsack problem and an implementation of a genetic algorithm:

- **Dynamic Programming Solution**: Uses dynamic programming to efficiently solve the knapsack problem by avoiding the recalculation of subproblems.
- **Genetic Algorithm for Knapsack Problem**: Applies a genetic algorithm to find an approximate solution to the knapsack problem. This approach simulates the process of natural selection where the fittest individuals are selected for reproduction to produce offspring for the next generation.

## Running the Code

To compile and run the solutions, use a C++ compiler that supports C++11 or later. For example, you can use g++ as follows:

```bash
g++ -std=c++11 -o solution hw1_2/knapsack.cpp
./solution
```
Replace hw1_2/knapsack.cpp with the path to the specific solution file you want to compile and run.

## Input and Output
Each program reads input from a file specified by the user at runtime. The input file should contain the number of items, the capacity of the knapsack, and the weight and value of each item. The programs output the maximum value that can be achieved and the solution to the knapsack problem to a user-specified output file.

## Output Example

After running the provided solution for the given input dataset, the program outputs the maximum profit and the solution vector indicating which items were selected for the optimal solution. Here's an example of what the output might look like:

- **Maximum Profit**: `309`
- **Solution Vector**: `1111010000`

In this example, the maximum profit that can be achieved is 309. The solution vector `1111010000` indicates the selection of items for achieving this profit, where `1` represents an item that is included in the knapsack, and `0` represents an item that is not included. According to the solution vector, the first five items are selected, and the last five are not.

## Contributing
Contributions to improve the solutions or documentation are welcome. Please adhere to the academic integrity policies of the NSYSU CSE department when contributing to this repository.

## Acknowledgments
Thanks to the instructors and TAs of the NSYSU CSE Algorithms course for their guidance and support.

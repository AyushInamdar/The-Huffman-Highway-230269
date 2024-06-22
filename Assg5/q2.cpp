#include <iostream>
#include <vector>
#include <queue>

int optimalMergePattern(std::vector<int>& file_sizes)
{
    //create min heap
    std::priority_queue<int, std::vector<int>, std::greater<int>> min_heap;

    //push files into min heap
    for (int size : file_sizes)
        min_heap.push(size);

    int total_cost = 0;

    //keep merging till one file remains
    while (min_heap.size() > 1) {
        //extracting two smallest files
        int first = min_heap.top();
        min_heap.pop();
        int second = min_heap.top();
        min_heap.pop();

        //compute cost of merging
        int current_cost = first + second;

        total_cost += current_cost;

        min_heap.push(current_cost);
    }

    return total_cost;
}

int main()
{
    std::vector<int> file_sizes = {4, 3, 2, 6};

    int min_cost = optimalMergePattern(file_sizes);

    std::cout << "Minimum Cost = " << min_cost << std::endl;

    return 0;
}

#include <iostream>

int main() {
    int scores[10];
    int sum = 0;
    int highest = 0;
    int lowest = 100;  // Assuming scores are out of 100
    int aboveAverageCount = 0;
    int belowAverageCount = 0;

    // Input 10 exam scores
    std::cout << "Enter 10 exam scores: ";
    for(int i = 0; i < 10; ++i) {
        std::cin >> scores[i];
        sum += scores[i];
        if(scores[i] > highest) highest = scores[i];
        if(scores[i] < lowest) lowest = scores[i];
    }

    // Calculate the average score
    double average = static_cast<double>(sum) / 10;

    // Count scores above and below average
    for(int i = 0; i < 10; ++i) {
        if(scores[i] > average) ++aboveAverageCount;
        else if(scores[i] < average) ++belowAverageCount;
    }

    // Display results
    std::cout << "Average exam score: " << average << std::endl;
    std::cout << "Highest exam score: " << highest << std::endl;
    std::cout << "Lowest exam score: " << lowest << std::endl;
    std::cout << "Number of exam scores above the average: " << aboveAverageCount << std::endl;
    std::cout << "Number of exam scores below the average: " << belowAverageCount << std::endl;

    return 0;
}


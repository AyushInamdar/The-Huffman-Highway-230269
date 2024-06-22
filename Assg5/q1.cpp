#include <iostream>
#include <vector>
#include <algorithm>

int minimumPlatforms(std::vector<int>& arrival, std::vector<int>& departure)
{
    //sorting the vectors for arrival and departures
    std::sort(arrival.begin(), arrival.end());
    std::sort(departure.begin(), departure.end());

    int n = arrival.size();
    int platforms = 1;
    int result = 1;
    int i = 1;//because a train will by default first arrive only.
    int j = 0;

    while (i < n && j < n)
    {
        if (arrival[i] <= departure[j]) {
            platforms++;
            i++;
        }

        else if (arrival[i] > departure[j]) {
            platforms--;
            j++;
        }
        //checking if train is arriving or leaving first.
        //we have two pointers traversing both vectors at the same time, whichever time point comes first,
        //is taken into account

        if (platforms > result)     //if current need exceeds past maximum need
            result = platforms;
    }

    return result;
}

int main() {
    //creating vectors for arrival and departure times
    std::vector<int> arrival = {900, 940, 950, 1100, 1500, 1800};
    std::vector<int> departure = {910, 1200, 1120, 1130, 1900, 2000};

    std::cout << "Minimum Platforms = " << minimumPlatforms(arrival, departure) << std::endl;

    return 0;
}

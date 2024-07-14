#include <bits/stdc++.h>
using namespace std;

int maxProjectValue(int N, vector<int>& values, vector<vector<string>>& required_languages, set<string>& known_languages) {
    // Create a bitmask to represent the projects we can complete
    int max_value = 0;
    int num_projects = values.size();

    // Iterate through all possible combinations of projects
    for (int mask = 0; mask < (1 << num_projects); mask++) {
        int current_value = 0;
        bool valid_combination = true;

        // Check each project in the current combination
        for (int i = 0; i < num_projects; i++) {
            if (mask & (1 << i)) {  // If this project is selected in the current combination
                // Check if we know all required languages for this project
                for (const string& lang : required_languages[i]) {
                    if (known_languages.find(lang) == known_languages.end()) {
                        valid_combination = false;
                        break;
                    }
                }

                if (!valid_combination) break;
                current_value += values[i];
            }
        }

        // Update max_value if this is a valid combination with higher value
        if (valid_combination) {
            max_value = max(max_value, current_value);
        }
    }

    return max_value;
}

int main() {
    int N = 10;
    vector<int> values = {50, 30, 70, 20, 90, 10, 60, 40, 80, 100};
    vector<vector<string>> required_languages = {
        {"Python", "C++"}, {"Java", "Python"}, {"C++", "Java", "Python"},
        {"Python"}, {"Java", "Go"}, {"C++"}, {"Python", "Go"},
        {"C++", "Python"}, {"Java", "Python", "Go"}, {"C++", "Java", "Go"}
    };
    set<string> known_languages = {"Python", "C++", "Java"};

    int result = maxProjectValue(N, values, required_languages, known_languages);
    cout << "Maximum Project Value: " << result << endl;

    return 0;
}

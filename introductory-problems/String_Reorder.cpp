/*
PROBLEM:
    Given a string, reorder its characters so that no two adjacent characters are the same.
    If there are multiple solutions, output the lexicographically smallest one.
    If it's impossible to do so, output -1.

CONSTRAINTS:
    • 1 <= n <= 10^6 (length of the string)
    • Characters are uppercase English letters ('A'-'Z')

KEY CONCEPTS:
    1. Greedy Algorithm

ALGORITHM:
    
    Step 1: Frequency Calculation and Possibility Check
    ---------------------------------------------------
    Store the frequency of each character appearing in the string in a `charCounts` array.
    If any character appears more than (n + 1) / 2 times, it's trivially impossible to 
    reorder without having two identical adjacent characters.

    Step 2: Greedily Build the String
    ---------------------------------
    To get the lexicographically smallest valid string, we start filling the result string in 
    a greedy manner from left to right. For each position, we try placing the minimum possible 
    character ('A' to 'Z') that satisfies the following conditions:
      • The character must be available (charCounts > 0).
      • The character must not be the same as the last placed character.
      • Placing the character must satisfy the modal condition for the remaining positions.

    The Modal Condition
    -------------------
    While placing the i-th character in the result string, we have (n - i - 1) positions left 
    to fill. After placing a character, we need to ensure that no remaining character has a 
    frequency greater than (remainingPositions + 1) / 2.

FUNCTION PARAMETERS:
    • canPlaceCharacter(int charIndex, vector<int>& charCounts, int remainingPositions):
        - charIndex: The 0-25 index representing the character we want to test.
        - charCounts: The current available frequencies of all characters.
        - remainingPositions: The number of empty slots left in the string.
        Returns true if placing this character leaves a valid state for the rest of the string.

    • getBestNextChar(vector<int>& charCounts, char lastPlaced, int remainingPositions):
        - charCounts: The current available frequencies of all characters.
        - lastPlaced: The character placed in the immediate previous position (to avoid adjacent duplicates).
        - remainingPositions: The number of empty slots left to be filled *after* this one.
        Returns the lexicographically smallest valid character, or '\0' if none are valid.

TIME COMPLEXITY:
    • Preprocessing: O(n) to count character frequencies.
    • String Building: O(26 * 26 * n) = O(n) since we check at most 26 characters for each 
      of the n positions, and finding the maximum frequency takes O(26) steps.
    • Total: O(n)

SPACE COMPLEXITY: O(n) to store the result string + O(1) for the frequency array of size 26.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

bool canPlaceCharacter(const int charIndex, vector<int>& charCounts, const int remainingPositions) {
    // Temporarily decrement the character to simulate placing it
    --charCounts[charIndex];
    int maxFreq = *max_element(charCounts.begin(), charCounts.end());
    // Backtrack the decrement
    ++charCounts[charIndex];
    
    return maxFreq <= (remainingPositions + 1) / 2;
}

char getBestNextChar(vector<int>& charCounts, const char lastPlaced, const int remainingPositions) {
    for (int k = 0; k < 26; ++k) {
        // Skip if the character is exhausted
        if (charCounts[k] == 0) continue;
        
        // Skip if it matches the immediately preceding character
        if (lastPlaced - 'A' == k) continue;
        
        // Skip if placing this character makes the rest of the string impossible to build
        if (!canPlaceCharacter(k, charCounts, remainingPositions)) continue;
        
        // Valid character found: decrement its availability and return it
        --charCounts[k];
        return k + 'A';
    }
    
    return '\0'; // Should only be reached if no valid character exists
}

string rearrangeString(const string& s) {
    int n = s.length();
    vector<int> charCounts(26, 0);
    
    // Step 1: Count frequencies and check for trivial impossibility
    for (char c : s) {
        if (++charCounts[c - 'A'] > (n + 1) / 2) {
            return "-1";
        }
    }

    // Step 2: Greedily construct the lexicographically smallest result
    string result;
    result.resize(n);
    char lastPlaced = '\0';
    
    for (int i = 0; i < n; ++i) {
        int remainingPositions = n - i - 1;
        result[i] = getBestNextChar(charCounts, lastPlaced, remainingPositions);
        lastPlaced = result[i];
    }

    return result;
}

int main() {
    // Optimize standard I/O operations for competitive programming
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    if (cin >> s) {
        cout << rearrangeString(s) << '\n';
    }

    return 0;
}
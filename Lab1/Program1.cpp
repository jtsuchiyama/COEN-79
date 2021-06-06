#include <iostream>
#include <string>

using namespace std;

int main() {
	int i;
	int alpha_counter = 0;
	int non_counter= 0;

	string input;
	cout << "Please input something\n";
	getline(cin, input); // Stores input line into str input
	
	for(i=0;i<input.length();i++) {
	// Parse the entire input string
		if (input[i] != ' ') {
		// If the current character is not a space, continue. Otherwise, ignore it
			if (isalnum(input[i]))
			// Increment the alphanumeric counter
				alpha_counter++;
			else
			// Increment the non-alphanumeric counter
				non_counter++;
		}
	}
	cout << "Number of alphanumeric characters: " << alpha_counter << "\n";
	cout << "Number of non-alphanumeric characters: " << non_counter << "\n";

	return 0;
}

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main(int argc, char *argv[]) {
	int i;
	string word;

	string line;
	ifstream infile(argv[1]); // Open the file given by the first argument

	while(infile >> word) {
	// Read the opened file, word by word
		for(i=0;i<word.length();i++) {
		// Iterates through the word
			if(isalnum(word[i]))
			// If the char is alphanumeric, uppercase it
				word[i] = toupper(word[i]);

			else
			// If the char is non-alphanumeric, erase it
				word.erase(i--,1);
		}
		if (word.length() >= 10)
		// If the word is of length 10 or greater, print it
			cout << word << "\n";
	}	

	infile.close();
	return 0;
}

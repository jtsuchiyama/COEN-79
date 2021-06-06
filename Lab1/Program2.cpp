#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

int main() {
	int i;
	int j;
	int flag=0;

	string input;
	cout << "Input a string with exactly 10 digits (No spaces)\n";
	cin >> input;

	if(input.length() != 10) {
	// If the input is not of length 10, then it errors and returns out
		cout << "Error. Input a string with EXACTLY 10 digits (No spaces)\n";
		return 1;
	}

	for(i=0;i<10;i++) {
	// If the string does not contain all digits, then it indicates such through the flag
		if (not isdigit(input[i])) {
			flag = 1;
			break;	
		}
	}
	if (flag == 1) {
	// If the flag indicates error, then it errors and returns out
		cout << "Error. Input a string with exactly 10 DIGITS (No spaces)\n";
		return 1;
	}
	
	cout << "\n";
	for(i=0;i<4;i++) {
	// Iterates the loop 4 times to print 4 lines
		cout << setw(i*2+12) << input << setw(12); // Prints the 2 offset spacings and the input string
		for(j=input.length() - 1;j>=0;j--)
		// Prints the input string in reverse 
			cout << input[j];
		cout << "\n";
	}
	return 0;	
}

#include <iostream>
#include <ctime>
#include <vector>
#include <stdint.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <chrono>


using namespace std;

void radixSort(uint16_t * A, uint16_t digit, int len);

int main() {
	int arrSize[11] = {100, 500, 1000, 5000, 10000, 50000, 100000, 500000, 1000000, 5000000, 10000000};
	printf("Radix Sort\n");
	for(int i = 0; i < 11; ++i) {
		// Create the Array to be sorted with random data
		srand(clock());
		uint16_t * A = new uint16_t[arrSize[i]];
		for(int j = 0; j < arrSize[i]; ++j) {
			A[j] = rand();
		}
		// Get the start time
		auto init = chrono::high_resolution_clock::now();
		// Run the algorithm
		radixSort(A, 16, arrSize[i]);
		// Get the end time
		auto end = chrono::high_resolution_clock::now();
		// Calculate the elepsed time
		auto duration = end - init;
		int sec = chrono::duration_cast<chrono::seconds>(duration).count();
		int nano = chrono::duration_cast<chrono::nanoseconds>(duration).count() % 1000000000;

		printf("%i, %i.%09i\n", arrSize[i], sec, nano);
		// Make sure the output was sorted
		for (int j = 1; j < arrSize[i]; j++) {
			if (A[j] < A[j - 1]) {
				cout << "WRONG " << j;
			}
		}
		delete[] A;
	}
	// Wait for user input.
	string tmp;
	getline(cin, tmp);
}

void radixSort(uint16_t * A, uint16_t digit, int len) {
	if (len > 1 && digit > 0) {
		int zeroTop = 0;
		int oneTop = 1;
		for (int i = 0; i < len; ++i) {
			// Check if the digit bit is zero
			if (!(A[i] & (1 << digit - 1))) {
				// Put the item into the zero "Bin"
				swap(A[zeroTop], A[i]);
				zeroTop++;
				oneTop++;
			}
			else {
				// Put the item into the one "Bin"
				swap(A[zeroTop], A[i]);
				oneTop++;
			}

		}

		// Sort the next digit for items in the zero "Bin" and the one "Bin"
		radixSort(A, digit - 1, zeroTop);
		radixSort(A + zeroTop, digit - 1, len - zeroTop);
	}
}

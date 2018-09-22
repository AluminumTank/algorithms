#include <iostream>
#include <ctime>
#include <vector>
#include <stdint.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <chrono>


using namespace std;

void insertionSort(vector<uint16_t> &A);

int main() {
	int arrSize[11] = {100, 500, 1000, 5000, 10000, 50000, 100000, 500000, 1000000, 5000000, 10000000};
	string tmp;
	getline(cin, tmp);
	printf("Insertion Sort\n");
	for(int i = 0; i < 11; ++i) {
		// Create the Array to be sorted with random data
		srand(clock());
		vector<uint16_t> A(arrSize[i]);
		for(int j = 0; j < arrSize[i]; ++j) {
			A[j] = rand();
		}
		// Get the start time
		auto init = chrono::high_resolution_clock::now();
		// Run the algorithm
		insertionSort(A);
		// Get the end time
		auto end = chrono::high_resolution_clock::now();
		// Calculate the elepsed time
		auto duration2 = end - init;
		int sec2 = chrono::duration_cast<chrono::seconds>(duration2).count();
		int nano2 = chrono::duration_cast<chrono::nanoseconds>(duration2).count() % 1000000000;

		printf("%i, %i.%09i\n", arrSize[i], sec2, nano2);
		// Make sure the output was sorted
		for (int j = 1; j < A.size(); j++) {
			if (A[j] < A[j - 1]) {
				cout << "WRONG " << j;
			}
		}
	}
	// Wait for user input.
	//string tmp;
	getline(cin, tmp);
}

// Based on sudo-code on slide
void insertionSort(vector<uint16_t> &A) {
	for(int i = 1; i < A.size(); ++i) {
		int key = A[i];
		int j = i -1;
		while(j >= 0 and A[j] > key) {
			A[j + 1] = A[j];
			j--;
		}
		A[j + 1] = key;
	}
}

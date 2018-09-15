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

/*int main() {
	int runningTimes[11] = {100, 500, 1000, 5000, 10000, 50000, 100000, 500000, 1000000, 5000000, 10000000};
	printf("Radix Sort\n");
	for(int i = 0; i < 11; ++i) {
		srand(clock());
		uint16_t * A = new uint16_t[runningTimes[i]];
		uint16_t * B = new uint16_t[runningTimes[i]];
		for(int j = 0; j < runningTimes[i]; ++j) {
			A[j] = rand();
			B[j] = A[j];
		}
		auto init = chrono::high_resolution_clock::now();
		radixSort(A, 16, runningTimes[i]);
		auto end = chrono::high_resolution_clock::now();
		auto duration1 = end - init;
		int sec1 = chrono::duration_cast<chrono::seconds>(duration1).count();
		int nano1 = chrono::duration_cast<chrono::nanoseconds>(duration1).count() % 1000000000;

		printf("%i, %i.%09i\n", runningTimes[i], sec1, nano1);
		for (int j = 1; j < runningTimes[i]; j++) {
			//cout << A[j] << ", ";
			if (A[j] < A[j - 1]) {
				cout << "WRONGA " << j;
			}
		}
		for (int j = 1; j < runningTimes[i]; j++) {
			//cout << A[j] << ", ";
			if (B[j] < B[j - 1]) {
				cout << "WRONGB " << j;
			}
		}
		delete[] A;
		delete[] B;
	}
	string tmp;
	getline(cin, tmp);
}*/

void radixSort(uint16_t * A, uint16_t digit, int len) {
	if (len > 1 && digit > 0) {
		int zeroTop = 0;
		int oneTop = 1;
		for (int i = 0; i < len; ++i) {
			// Check if the digit bit is zero
			if (!(A[i] & (1 << digit - 1))) {
				swap(A[zeroTop], A[i]);
				zeroTop++;
				oneTop++;
			}
			else {
				swap(A[zeroTop], A[i]);
				oneTop++;
			}

		}

		// sort the next for the zero set and the ones set
		radixSort(A, digit - 1, zeroTop);
		radixSort(A + zeroTop, digit - 1, len - zeroTop);
	}
}

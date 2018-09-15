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
	int runningTimes[11] = {100, 500, 1000, 5000, 10000, 50000, 100000, 500000, 1000000, 5000000, 10000000};
	printf("Radix Sort\n");
	for(int i = 0; i < 11; ++i) {
		srand(clock());
		uint16_t * A = new uint16_t[runningTimes[i]];
		for(int j = 0; j < runningTimes[i]; ++j) {
			A[j] = rand();
		}
		int init = clock();
		radixSort(A, 16, runningTimes[i]);
		float runtime = static_cast<float>(clock() - init) / static_cast<float>(CLOCKS_PER_SEC);
		printf("%i,%f\n", runningTimes[i], runtime);
		for (int j = 1; j < runningTimes[i]; j++) {
			//cout << A[j] << ", ";
			if (A[j] < A[j - 1]) {
				cout << "WRONG " << j;
			}
		}
		delete[] A;
	}
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

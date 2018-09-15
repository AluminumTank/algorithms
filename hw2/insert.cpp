#include <iostream>
#include <ctime>
#include <vector>
#include <stdint.h>
#include <stdio.h>
#include <iostream>
#include <string>


using namespace std;

void insertionSort(vector<uint16_t> &A);

/*int main() {
	int runningTimes[11] = {100, 500, 1000, 5000, 10000, 50000, 100000, 500000, 1000000, 5000000, 10000000};
	printf("Insertion Sort\n");
	for(int i = 0; i < 11; ++i) {
		srand(clock());
		vector<uint16_t> A(runningTimes[i]);
		for(int j = 0; j < runningTimes[i]; ++j) {
			A[j] = rand();
		}
		int init = clock();
		insertionSort(A);
		float runtime = static_cast<float>(clock() - init) / static_cast<float>(CLOCKS_PER_SEC);
		printf("%i,%f\n", runningTimes[i], runtime);
		for (int j = 1; j < A.size(); j++) {
			//cout << A[j] << ", ";
			if (A[j] < A[j - 1]) {
				cout << "WRONG " << j;
			}
		}
	}
	string tmp;
	getline(cin, tmp);
}*/

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

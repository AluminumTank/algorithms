#include <iostream>
#include <unistd.h>
#include <ctime>
#include <vector>

using namespace std;

void insertionSort(vector<u_int16_t>);

int main() {
	int runningTimes[11] = {100, 500, 1000, 5000, 10000, 50000, 100000, 10, 10, 10, 10};
	printf("Insertion Sort\n");
	for(int i = 0; i < 11; ++i) {

		vector<u_int16_t> A(runningTimes[i]);
		for(int j = 0; j <=runningTimes[i]; ++j) {
			srand(clock());
			A.push_back(rand());
		}

		int init = clock();
		insertionSort(A);
		float runtime = static_cast<float>(clock() - init) / static_cast<float>(CLOCKS_PER_SEC);
		printf("%i,%f\n", runningTimes[i], runtime);
	}
	string tmp;
	getline(cin, tmp);
}

void insertionSort(vector<u_int16_t> A) {
	for(int i = 1; i <= A.size(); ++i) {
		int key = A[i];
		int j = i -1;
		while(j >= 0 and A[j] > key) {
			A[j + 1] = A[j];
			j--;
		}
		A[j + 1] = key;
	}

	for(int i = 0; i <= A.size(); ++i) {
		if(A[i] < A[i-1]) {
			cout << "WRONG\n";
		}
	}
}

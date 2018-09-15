#include <iostream>
#include <climits>
#include <ctime>
#include <vector>
#include <string>

using namespace std;

void mergeSort(int * A, int p, int q, int r);

int main() {
	int arrSize[11] = {100, 500, 1000, 5000, 10000, 50000, 100000, 500000, 1000000, 5000000, 10000000};
	printf("Merge Sort\n");
	for(int i = 0; i < 11; ++i) {

		srand(clock());
		int * A = new int[arrSize[i]];
		int * check = new int[10000];
		for(int j = 0; j < 10000; ++j) {
			check[j] = 0;
		}
		for(int j = 0; j < arrSize[i]; ++j) {
			A[j] = rand() % 10000;
			check[A[j]]++;
		}
		clock_t start = clock();
		mergeSort(A, 0, (arrSize[i] - 1) / 2, arrSize[i] - 1);
		clock_t end = clock();
		for(int j = 0; j < arrSize[i]; ++j) {
			check[A[j]]--;
			if(j != arrSize[i] - 1 && A[j] > A[j + 1]) {
				printf("WRONG: %i: %i: %i", j, A[j], A[j + 1]);
			}
			//printf("%i,%i\n", j, A[j]);
		}
		for(int j = 0; j < 10000; ++j) {
			if(check[j] != 0) {
				printf("WRONG\n");
			}
		}
		string tmp;
		getline(cin, tmp);
		double runtime = double(end - start) / CLOCKS_PER_SEC;
		printf("%i,%f\n", arrSize[i], runtime);
		delete[] A;
	}
	string tmp;
	getline(cin, tmp);
}

void mergeSort(int * A, int p, int q, int r) {
	if(p < r) {
		mergeSort(A, p, (p + q) / 2, q);
		mergeSort(A, q + 1, (q + 1 + r) / 2, r);

		// this portion will be the actual merging of the arrays
		int * L = new int[q - p + 1];
		for(int i = 0; i < q - p + 1; ++i) {
			L[i] = A[p + i];
		}

		int * R = new int[r - q];
		for(int i = 0; i < r - q; ++i) {
			R[i] = A[q + 1 + i];
		}

		int i = 0;
		int j = 0;
		for(int k = p; k <= r; ++k) {
			// instead of using sentinel "infinite" values, we check to see if i and j
			// are in range
			if(( L[i] <= R[j] && i != (q - p + 1) ) || j == r - q) {
				A[k] = L[i];
				++i;
			} else {
				A[k] = R[j];
				++j;
			}
		}
		delete[] L;
		delete[] R;
	}
}

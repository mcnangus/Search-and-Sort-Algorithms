#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <time.h>
#include <stdlib.h>
using namespace std;

void swap(vector<unsigned long long>& v, unsigned long long x, unsigned long long y) {
    unsigned long long temp = v[x];
    v[x] = v[y];
    v[y] = temp;
}

unsigned long long partition(vector<unsigned long long>& v, unsigned long long left, unsigned long long right, unsigned long long pivotIndex) {
	unsigned long long pivot = v[pivotIndex];

	swap(v, pivotIndex, right);

	unsigned long long pIndex = left;
	unsigned long long i;

	for (i = left; i < right; i++) {
		if (v[i] <= pivot) {
			swap(v, i, pIndex);
			pIndex++;
		}
	}

	swap(v, pIndex, right);
	
	return pIndex;
}

unsigned long long quickselect(vector<unsigned long long>& vec, unsigned long long left, unsigned long long right, unsigned long long k) {
	if (left == right)
		return vec[left];

	unsigned long long pivotIndex = left + rand() % (right - left + 1);

	pivotIndex = partition(vec, left, right, pivotIndex);

	if (k == pivotIndex)
		return vec[k];
	else if (k < pivotIndex)
		return quickselect(vec, left, pivotIndex - 1, k);
	else
		return quickselect(vec, pivotIndex + 1, right, k);
}

int main(int argc, char *argv[]) {
		
	// make sure we have exactly 1 parameter
	if (argc != 2) {
		cout << "Invalid format, please use read_file [filename]\n";
		return -1;
	}
	
	// load in our file
	string filename = argv[1];  // argument 0 is the executable, 1 is the 
						 		// first parameter.
		    
	ifstream infile(filename);
	
	unsigned long long L;
	unsigned long long W;
	unsigned long long N;
	infile >> L >> W >> N;
    
    unsigned long long num;
	std::vector<unsigned long long> vec;
	unsigned long long count = 0;
	
	if (infile.is_open()) {
		while (not infile.eof()) {
			infile >> num;
			if (count % 2 == 1)
				vec.push_back(num);
			count++;
		}
	}

    // Code
    srand(time(NULL));
    cout << quickselect(vec, 0, vec.size()-1, vec.size() / 2);
}
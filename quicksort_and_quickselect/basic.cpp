#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

void swap(vector<unsigned long long>& v, unsigned long long x, unsigned long long y) {
    unsigned long long temp = v[x];
    v[x] = v[y];
    v[y] = temp;
}

void quicksort(vector<unsigned long long>& vec, unsigned long long L, unsigned long long R) {
    unsigned long long i, j, mid, piv;
    i = L;
    j = R;
    mid = L + (R - L) / 2;
    piv = vec[mid];

    while (i<R || j>L) {
        while (vec[i] < piv)
            i++;
        while (vec[j] > piv)
            j--;

        if (i <= j) {
            swap(vec, i, j);
            i++;
            j--;
        }
        else {
            if (i < R)
                quicksort(vec, i, R);
            if (j > L)
                quicksort(vec, L, j);
            return;
        }
    }
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
	quicksort(vec, 0, vec.size()-1);     //(n-1) for last index
	unsigned long long med = vec[vec.size() / 2];
    cout << med;
}

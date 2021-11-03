#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

int maxSum = 0;
std::vector<int> maxIndicesArr;

void permute(int M, vector<vector<int>> data, int typeIndex, int prevSum, vector<int> indicesArr) {
    for (int i = 0; i < data[typeIndex].size(); i++) {
        indicesArr.push_back(i + 1);
        int sum = prevSum + data[typeIndex][i];
        if (typeIndex < data.size() - 1) {
            permute(M, data, typeIndex + 1, sum, indicesArr);
        } else if (sum <= M & sum > maxSum) {
            maxSum = sum;
            maxIndicesArr = indicesArr;
            //int n = sizeof(indicesArr) / sizeof(indicesArr[0]);
            // maxIndicesArr(indicesArr, indicesArr+n);
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
	
	int M;
	int T;
	infile >> M >> T;
    
    int num;
	
    std::vector<vector<int>> array;
    string line;
	
	if (infile.is_open()) {
		while (not infile.eof()) {
            std::vector<int> vec;
            std::getline(infile, line);
			std::stringstream iss(line);
            iss >> num;
            while (iss >> num)
                vec.push_back(num);
            array.push_back(vec);
		}   
	}
	
	// Code
    vector<int> indicesArr;
    permute(M, array, 0, 0, indicesArr);

    cout << maxSum;
    for (int i = 0; i < maxIndicesArr.size(); i++) {
        cout << " " << maxIndicesArr[i];
    }
}

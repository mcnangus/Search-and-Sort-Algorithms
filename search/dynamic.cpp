#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iterator>
using namespace std;

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
	
    std::vector<vector<int>> data;
    string line;
	
	if (infile.is_open()) {
		while (not infile.eof()) {
            std::vector<int> vec;
            std::getline(infile, line);
			std::stringstream iss(line);
            iss >> num;
            while (iss >> num)
                vec.push_back(num);
            data.push_back(vec);
		}   
	}
	
	// Code
    
    vector<bool> prevBoolArr(M, false);
    vector<int> arr[M] = {};
    int sum;
    for (int i = 0; i < data.size(); i++) {
        vector<bool> boolArr(M, false);
        if (i==0) {
            for (int j=0; j < data[i].size(); j++) {
                if (!boolArr[data[i][j]]) {
                    boolArr[data[i][j]] = true;
                    arr[data[i][j]].push_back(j+1);
                }
            }
        } else {
            for (int j=0; j < M; j++) {
                if (prevBoolArr[j] & !boolArr[j]) {
                    for (int k=0; k < data[i].size(); k++) {
                        sum = j + data[i][k];
                        if (sum < M & !boolArr[sum]) {
                            boolArr[sum] = true;
                            arr[sum].push_back(k+1);
                        }
                    }
                }
            }
        }
        prevBoolArr = boolArr;
    }
    int maxSum = 0;
    vector<int> indicesArr;
    for (int i=0; i < M; i++) {
        if (arr[i].size()==data.size()) {
            maxSum = i;
            indicesArr = arr[i];
        }
    }
    cout << maxSum;
    for (int i=0; i < indicesArr.size(); i++) {
        cout << " " << indicesArr[i];
    }
}

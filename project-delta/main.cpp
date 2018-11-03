#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using std::string;

string line;
std::vector<string> allLines;

std::vector<string> readFromCSV(string filename){
    std::ifstream fileIn(filename);
    std::ofstream fileOut("credits.txt");

    while(!fileIn.eof()){
        getline(fileIn,line,'\n');
        allLines.push_back(line);
    }
    //now we have all lines in a vec and we will get
    // each line that starts with title and put all the strings in those lines
    // into another vec then write them to the output file
}
int main() {
    readFromCSV("data.csv");
}
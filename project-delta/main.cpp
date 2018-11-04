#include <vector>
#include <unordered_map>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using std::string;
using std::vector;
using std::unordered_map;
using std::cin;
using std::cout;

string line;
string theseLines;
vector<string> allLines;
vector<int> klLocation;
vector<string> klData;
unordered_map<int,vector<string>> klSplitted;

void readFromCSV(string filename){
    std::ifstream fileIn(filename);

    if (!fileIn.is_open()) {
            cout << "ERROR: Cannot Locate or Cannot Open File" << std::endl;
    }

    while(fileIn.peek() != EOF){
        getline(fileIn,line,'\n');
        allLines.push_back(line);
    }
}

vector<string> divideStr (string divideThis, char delimiter){
    vector<int> whereFirstAre;
    vector<string> subStr;
    int pos=0;

    whereFirstAre.push_back(pos);
    for (pos=0; pos<divideThis.length(); ++pos){
        if(divideThis[pos]==delimiter){
            whereFirstAre.push_back(pos+1);
        }
    }

    cout << "==" << std::endl;
    for(int i=0; i<whereFirstAre.size(); ++i){
        if (i+1 != whereFirstAre.size()) {
            string s = divideThis.substr(whereFirstAre.at(i), whereFirstAre.at(i + 1) - whereFirstAre.at(i) - 1);
            subStr.push_back(s);
        }
        else {
            subStr.push_back(divideThis.substr(whereFirstAre.at(i)));
        }
    }
    for(int i = 0; i<subStr.size(); ++i){
        cout<< subStr.at(i) << std::endl;
    }
    return subStr;
}


void readLines(string lineNum){
    vector<string> allSubs = divideStr(lineNum, ',');
    for(string s : allSubs) {
        vector<string> subOfS;
        if(s.find('-') == string::npos){
            klLocation.push_back(stoi(s));
        }
        else {
            subOfS = divideStr(s,'-');
            int start=std::stoi(subOfS.at(0));
            int last=std::stoi(subOfS.at(1));
            for(int i=start;i<=last;++i){
                klLocation.push_back(i);
            }
        }
    }
    for (int i=0; i<klLocation.size(); ++i){
        klData.push_back((allLines.at(klLocation.at(i))));
        cout << klLocation.at(i) << std::endl;
    }
}

void toMap(){
    vector<string> temp;
    for (int i=0; i<klData.size(); i++){
        temp = divideStr(klData.at(i), ',');
        klSplitted[i] = temp;
    }

}

void writeFromCSV(){
    std::ofstream fileOut("credits.txt");
    toMap();
    for (int i = 0; i<klLocation.size(); ++i){
//        klData.push_back((allLines.at(klLocation.at(i))));
        fileOut << allLines.at(klLocation.at(i));
    }
}


void remove(string content){
}


int main() {
    readFromCSV("../data.csv");
    cin >> theseLines;
    readLines(theseLines);
    writeFromCSV();
}
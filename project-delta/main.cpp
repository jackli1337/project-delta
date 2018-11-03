#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using std::string;
using std::vector;
using std::cin;

string line;
string theseLine;
vector<string> allLines;

vector<string> readFromCSV(string filename){
    std::ifstream fileIn(filename);
    std::ofstream fileOut("credits.txt");

    while(!fileIn.eof()){
        getline(fileIn,line,'\n');
        allLines.push_back(line);
    }
}

vector<string> divideStr (string divideThis, char delimiter){
        vector<int> whereCommasAre;
        vector<string> subStr;
        int pos=0;

        string::iterator it=divideThis.begin();
        while(it!=divideThis.end()){
            pos++;
            if(*it==delimiter){
                whereCommasAre.push_back(pos);
            }
        }

        it=divideThis.begin();
        bool firstsub=true;
        int lastComma;
        while(it!=divideThis.end()){
            string s;
            if(firstsub){
                s = divideThis.substr(divideThis.front(),whereCommasAre.front());
                firstsub=false;
            }
            else{
                s= divideThis.substr(lastComma,whereCommasAre.front());
            }
            lastComma=whereCommasAre.front();
            whereCommasAre.erase(whereCommasAre.begin());
            subStr.push_back(s);
        }
        return subStr;
}


vector<int> readLines(string lineNum){
    vector<int> retVal;
    vector<string> allSubs = divideStr(lineNum, ',');
    for(string s : allSubs) {
        vector<string> subOfS;
        if(s.find('-') != string::npos){
            subOfS = divideStr(s,'-');
            int start=std::stoi(subOfS.at(0));
            int last=std::stoi(subOfS.at(1));
            for(int i=start;i<=last;++i){
                retVal.push_back(i);
            }
        }
        else {
            retVal.push_back(stoi(s));
        }
    }
    return retVal;
}

int main() {
    readFromCSV("data.csv");
    cin >> theseLine;
    readLines(theseLine);
}
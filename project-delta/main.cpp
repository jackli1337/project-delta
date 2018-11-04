#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using std::string;
using std::vector;
using std::cin;
using std::cout;

string line;
string theseLines;
vector<string> allLines;
/**
 *
 * @param filename
 * a filename that we want to read data from to transfer to a document
 *
 * this method takes in a filename and will write each line of the file to a global vector
 */
void readFromCSV(string filename){
    std::ifstream fileIn(filename);
    std::ofstream fileOut("credits.txt");

    if (!fileIn.is_open()) {
            cout << "ERROR: Cannot Locate or Cannot Open File" << std::endl;
    }

    while(fileIn.peek() != EOF){
        getline(fileIn,line,'\n');
        allLines.push_back(line);
    }
}
/**
 *
 * @param divideThis
 * a string that we want to get substrings of to either get numbers
 * in between commas or numbers on either side of a dash
 *
 * @param delimiter
 * character that you want to use to divide the string into substrings
 * should only be a comma or dash but could be any character
 *
 * @return
 * a vector of the substrings of the string that we want
 * (either a vector of numbers that were in a comma separated list,
 * or numbers that were on either side of a dash)
 */
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

/**
 *
 * @param lineNum
 * the line numbers that someone want to transfer to the document
 * @return
 * the line numbers in a vector converted to ints
 */
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
    readFromCSV("../data.csv");
    cin >> theseLines;
    readLines(theseLines);
}
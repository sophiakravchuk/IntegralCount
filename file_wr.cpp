#include <fstream>
#include <sstream>
//#include "parsing_error.cpp"

std::vector<std::string> reading_from_file(const std::string& file_name){
    std::string line;
    std::ifstream myFile;
    myFile.open(file_name);

    std::vector<std::string> vecOfLines;
    std::string currLine;
    if (myFile.is_open()) {
        while (std::getline(myFile, currLine)) {
            // Line contains string of length > 0 then save it in vector
            if (currLine.size() > 0)
                vecOfLines.push_back(currLine);
        }
//        auto ss = std::ostringstream{};
//        ss << myFile.rdbuf();
//        std::string s = ss.str();
        myFile.close();
        return vecOfLines;
    }
    else {
        throw MyParsingError("No such file was found");
    }
}

void writing_to_file(const std::string& file_name, const std::string& text){
    std::string line;
    std::ofstream myFile;
    myFile.open(file_name);
    if (myFile.is_open()) {
        myFile << text;
        myFile.close();
    }
    else {
        throw MyParsingError("No such file was found");
    }
}
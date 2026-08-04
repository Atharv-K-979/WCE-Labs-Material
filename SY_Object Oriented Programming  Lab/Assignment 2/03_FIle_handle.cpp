#include <iostream>
#include <cstdio>   // for FILE, fopen, fprintf, fclose
using namespace std;

class FileHandler {
private:
    FILE* file;        // file pointer
    const char* name;  // file name

public:
    // Constructor -> open file
    FileHandler(const char* fileName) {
        name = fileName;
        file = fopen(name, "a");   // open in append mode
        if (file != NULL) {
            cout << "File '" << name << "' opened successfully." << endl;
        } else {
            cout << "Error opening file." << endl;
        }
    }

    // Function to write a line
    void writeLine(const char* text) {
        if (file != NULL) {
            fprintf(file, "%s\n", text);
            cout << "Written to file: " << text << endl;
        }
    }

    // Destructor -> close file
    ~FileHandler() {
        if (file != NULL) {
            fclose(file);
            cout << "File '" << name << "' closed in destructor." << endl;
        }
    }
};

int main() {
    FileHandler file1("myfile.txt");
    file1.writeLine("This is the first line.");
    file1.writeLine("This is the second line.");
    file1.writeLine("C++ program using FILE operations.");
    return 0;
}

#include "source.h"

string fileContent = "";

void menu(){
    cout << "1. Add new text to the end of the file\n2. Display the content of the file\n3. Empty the file\n";
    cout << "4. Encrypt the file content\n5. Decrypt the file content\n6. Merge another file\n";
    cout << "7. Count the number of words in the file.\n8. Count the number of characters in the file\n9. Count the number of lines in the file\n";
    cout << "10. Search for a word in the file\n11. Count the number of times a word exists in the file\n12. Turn the file content to upper case.\n";
    cout << "13. Turn the file content to lower case.\n14. Turn file content to 1st caps (1st char of each word is capital)\n15. Save\n16. Exit\n";
}

void loadFileContent(string filename) {
    fstream dataSource;

    dataSource.open(filename, ios::in);
    while (!dataSource.eof()) {
        char chr = dataSource.get();
        if (chr != EOF) { // to avoid having multiple eof characters
            fileContent += chr;
        }
    }

    dataSource.close();
}

void saveFileContent(string filename) { // This is Mahmoud's job so will leave it as it is
    fstream dataTarget;                 // it needs to ask for new filename, or same file
    dataTarget.open(filename + ".txt", ios::out); 

    dataTarget << fileContent;

    dataTarget.close();
}

void addTxt(){
    //needs to work on something other than the external console and to delete the ctrl+z symbol
    string txt;
    cout << "Enter the text you want to add to the file or ctrl + z + enter to exit: " << endl;
    getline(cin >> ws, txt, '\0');
    fileContent += txt + '\n';
}

void displayContent(){
    cout << fileContent;
}

void emptyFile(char file[151]){
    char ans;
    cout << "\nDo you want to delete the file itself? (y/n)\n";
    cin >> ans; ans = tolower(ans);
    if (ans == 'y'){
        int status = remove(file);
        if(status==0)
            cout<<"\nFile Deleted Successfully!\n";
        else
            cout<<"\nError Occurred!";
    }
    else
        cout << "\nThe file is empty now but not deleted!\n";
    cout<<endl;
}

void encrypt(){
    for (char & i : fileContent) {
        if (i == 'z')
            i = 'a';
        else if (i == 'Z')
            i = 'A';
        else
            i += 1;
    }
    cout << "\nFile contents have been encrypted!\n";
}
void decrypt(){
    for (char & i : fileContent) {
        if (i == 'a')
            i = 'z';
        else if (i == 'A')
            i = 'Z';
        else
            i -= 1;
    }
    cout << "\nFile contents have been decrypted!\n";
}

void mergeAnotherFile() {
    string filename;
    cout << "Enter name of the file: ";
    cin >> filename;
    loadFileContent(filename);
}

void countWords() { // 100% accuracy
    int nWords = 0;

    for (int i = 0; i < fileContent.length(); i++) {
        if (fileContent[i] != ' ' && fileContent[i] != '\n' && (
                fileContent[i+1] == ' ' || fileContent[i+1] == '\n' || fileContent[i+1] == '\0')
                ) {
            nWords++;
        }
    }

    // for (char chr : fileContent) { // not that accurate...
    //     if (chr == ' ' || chr == '\n') {
    //         nWords++;
    //     }
    // }
    cout << nWords;
}



void countChars() {
    int nChars;
    for (char chr : fileContent) {
        nChars++;
    }
    cout << nChars;
}


void countLines() {
    int nLines = 0;
    for (int i = 0; i <= fileContent.length(); i++) {
        if (fileContent[i] == '\n' || fileContent[i] == '\0') {
            nLines++;
        }
    }
    cout << nLines;
}


void searchWord() { // sstream WAS NOT #includED!
   istringstream contentStream(fileContent);
   string wantedWord, word;
   bool isFound = false;

   cout << "Enter a word to search for: ";
   cin >> wantedWord;
   tolower(wantedWord); // overloaded to work with string

   while (!contentStream.fail()) {
       contentStream >> word;
       tolower(word);
       if (wantedWord == word) {
           isFound = true;
           break;
       }
   }

   if (isFound) {
       cout << "Word was found.\n";
   }
   else {
       cout << "Word was not found.\n";
   }
}

void tolower(string& str) {
    for (char& chr : str) {
        chr = towlower(chr);
    }
}
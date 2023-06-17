// CSE211 - TERM PROJECT
// ZEYNEP DUKKANCIOGLU -20200702076
//THIS PROJECT IS FOR MANAGING THE DIRECTORY COMPONENTS

#include <iostream>
#include <vector>
#include <dirent.h>
#include <sys/stat.h>

using namespace::std;

class Node { //WE CREATE A NODE CLASS AS ALWAYS TO PUT INFORMATION
public:
    string name;
    string extension;
    long long int size; //SIZE CAN BE IN MANY VARIES SO WE USE LONG LONG INT
    //WHEN WE ARE DEALING WITH BYTE VALUES I THINK THIS CAN BE THE BEST VARIABLE

    Node* nextName = NULL;
    Node* nextExtension = NULL;
    Node* nextSize = NULL;

};

void printNode(Node* node) { //WE ARE PRINTING NODES INFORMATION
    cout << node->name << "\t\t\t" << node->extension << "\t" << node->size << " bytes" << endl;
}

void InsertNode(Node* node, Node** nameHead, Node** sizeHead, Node** extHead) { //INSERT NODE FUNCTION IS FOR 3 DIFFRENT THINGS. NAME, SIZE AND EXTENSION. SO WE USE SAME METHOD BUT
    //DIFFERENT VARIABLES FOR EACH OF THEM. WE USE THİS İN READ FROM DİRECTORY.

    Node* temp = *nameHead; //THIS IS FOR FILES NAME PART
    if (*nameHead == NULL || (*nameHead)->name >= node->name) {
        node->nextName = *nameHead;
        *nameHead = node;
    }
    else {
        while (temp->nextName != NULL && temp->nextName->name < node->name) {
            temp = temp->nextName;
        }
        node->nextName = temp->nextName;
        temp->nextName = node;
    }

    temp = *sizeHead; //THIS IS FOR FILES SIZE PART
    if (*sizeHead == NULL || (*sizeHead)->size >= node->size) {
        node->nextSize = *sizeHead;
        *sizeHead = node;
    }
    else {
        while (temp->nextSize != NULL && temp->nextSize->size < node->size) {
            temp = temp->nextSize;
        }
        node->nextSize = temp->nextSize;
        temp->nextSize = node;
    }

    temp = *extHead; //THIS IS FOR FILES EXTENSION PART
    if (*extHead == NULL || (*extHead)->extension >= node->extension) {
        node->nextExtension = *extHead;
        *extHead = node;
    }
    else {
        while (temp->nextExtension != NULL && temp->nextExtension->extension < node->extension) {
            temp = temp->nextExtension;
        }
        node->nextExtension = temp->nextExtension;
        temp->nextExtension = node;
    }
}

void TraverseBy(Node* head, int mode, string filter, int ifilter) { //mode is for extension part, filter is for name part, ifilter is for size part.
    cout << "File Name\t\tExtension\tSize" << endl;
    int print = 1; //nodeu sırayla print etmek icin bir print degiskeni tanımladık
    Node* temp = head;

    while (temp != NULL) { //WHEN NOT EMPTY
        if (filter != "") { //isim kısmı boş değilse
            if (mode == 0) { //extension kısmına ihtiyac yoksa
                if (temp->name != filter) { //eğer nodeun namei filtera eşit değilse
                    print = 0;
                }
                else
                {
                    print = 1;
                }
            }
            else if (mode == 1) { //eger extension kısmına ihtiyac varsa ama asıl amacımız sizeı aramaksa
                if (temp->size < ifilter) print = 0;
                else print = 1;
            }
            else if (mode == 2) { //mode yani extension kısmı 2 olunca amacımız extensionu aramak ve sıralamak
                if (temp->extension != filter)  {
                        print = 0;
                }
                else {
                    print = 1;
                }
            }
        }
        else {
            print = 1;
        }
        if (print == 1) {
            printNode(temp);
        }
        if (mode == 0) {
            temp = temp->nextName;// bir sonraki nodea geçiş
        }
        else if (mode == 1) {
            temp = temp->nextSize;
        }
        else if (mode == 2) {
            temp = temp->nextExtension;
        }
    }
    cout << endl;
}

void readFromDirectory(string dirname, Node** nameHead, Node** sizeHead, Node** extHead) { //TO WRTIE THIS FUNCTION STACKOWERFLOW HELPED ME A LOT
    DIR* dir; struct dirent* diread;
    struct stat file_stats;
    if ((dir = opendir(dirname.c_str())) != nullptr) { //c_str is for converting directorys name
        while ((diread = readdir(dir)) != nullptr) { //readdir is for reading the directory
            Node* nn = new Node();
            string name = diread->d_name;
            int pos = name.rfind(".");
            if (pos == string::npos) {
                nn->name = name;
            }
            else {
                nn->name = name.substr(0, pos); //returns at a specified character position
                nn->extension = name.substr(pos, name.length() - pos);
            }
            if (!stat(diread->d_name, &file_stats))
            {
                nn->size = (long long int)file_stats.st_size;
            }
            InsertNode(nn, nameHead, sizeHead, extHead);
        }
        closedir(dir);
    }
}


void removeNode(Node** head, Node* node, int mode) {
    Node* temp = *head;
    Node* prev = NULL;
    if (temp != NULL && temp == node)
    {
        if (mode == 1) {
            *head = temp->nextSize;
        }
        else if (mode == 2) {
            *head = temp->nextExtension;
        }
        return;
    }
    else
    {
        while (temp != NULL && temp != node)
        {
            prev = temp;
            if (mode == 1) {
                temp = temp->nextSize;
            }
            else if (mode == 2) {
                temp = temp->nextExtension;
            }
        }
        if (mode == 1) {
            prev->nextSize = temp->nextSize;
        }
        else if (mode == 2) {
            prev->nextExtension = temp->nextExtension;
        }
    }
}
Node* removeByFileName(Node** head, string filename) {
    Node* temp = *head;
    Node* prev = NULL;
    if (temp != NULL && temp->name == filename) //WHEN ITS EQUAL TO FILENAME
    {
        *head = temp->nextName;
        return temp;
    }
    else
    {
        while (temp != NULL && temp->name != filename) //WHEN ITS NOT EQUAL TO FILENAME
        {
            prev = temp;
            temp = temp->nextName; //sonraki nodea geçiyoruz
        }
        if (temp == NULL)
        {
            cout << "File not found with name " << filename << endl;
            return NULL;
        }
        prev->nextName = temp->nextName;
        return temp;
    }
    return NULL;
}

int main() {
    Node* nameHead = NULL;
    Node* sizeHead = NULL;
    Node* extHead = NULL;
    string directory;
    cout << "\t\t\t" << "\t\t\t211 TERM PROJECT" <<endl;
    cout << "\t\t\t" << "\t\t\tZEYNEP DUKKANCIOGLU " <<  endl;
    cout << "\t\t\t" << "\t\t\t20200702076" <<  endl;
    cout << "\t\t\t" << "If you want to list files in directory please type . "<< endl;

    cout << endl<<endl<<"Enter directory location:";
    cin >> directory;
    readFromDirectory(directory, &nameHead, &sizeHead, &extHead);
    string filter; //for file name

    while (1) {
        cout << "1-Search by Filename" << endl;
        cout << "2-Search by Extension" << endl;
        cout << "3-Search by File Size" << endl;
        cout << "4-Remove by File Name" << endl;
        cout << "5-Update The List" << endl;
        cout << "6-Traverse List by Name" << endl;
        cout << "7-Traverse List by Extension" << endl;
        cout << "8-Traverse List by Size" << endl;
        cout << "9-Exit" << endl;


        int choice;
        cout << "Choice:";
        cin >> choice;
        if (choice == 1) {
            cout << "Enter file name to search:";
            cin >> filter; //filter is for filename
            TraverseBy(nameHead, 0, filter, 0); //we put 0 because we dont need them.
        }
        else if (choice == 2) {
            cout << "Enter file extension to search:"; //we put 0 because we dont need size for now
            cin >> filter;
            TraverseBy(extHead, 2, filter, 0);
        }
        else if (choice == 3) {
            cout << "Enter file size to search:";  //we dont need filename to search by size so its empty string
            int filteri;
            cin >> filteri;
            TraverseBy(sizeHead, 1, "", filteri);
        }
        else if (choice == 4) {
            cout << "Enter file name to remove:";
            cin >> filter;

            Node* deleted = removeByFileName(&nameHead, filter); //we delete name not node
            if (deleted != NULL) { //we delete node here
                removeNode(&sizeHead, deleted, 1);
                removeNode(&extHead, deleted, 2);
            }
        }
        else if (choice == 5) {
            cout << "\t\tList is updating\n ";
            nameHead = NULL;
            sizeHead = NULL;
            extHead = NULL;
            readFromDirectory(directory, &nameHead, &sizeHead, &extHead);
            cout << "Done" << endl;
        }
        else if (choice == 6) {
            TraverseBy(nameHead, 0, "", 0); //(head, mode, filter, ifilter) this is the line of functionn to make it clear to understand
        }
        else if (choice == 7) {
            TraverseBy(extHead, 2, "", 0);
        }
        else if (choice == 8) {
            TraverseBy(sizeHead, 1, "", 0);
        }
        else if (choice == 9) {
            break;
        }
    }

    return 0;
}

#ifndef FILEDIRECTORYTREE_H
#define FILEDIRECTORYTREE_H
#include <iostream>
#include <string>
#include <fstream>
#include "Queue.h"
#include "Stack.h"
#include <cmath>

using namespace std;

void clearTheFile(string filename)
{
    ofstream outfile(filename, ios::trunc); // Open the file in trunc mode

    if (outfile.is_open())
    {
        outfile.close();
        cout << "File cleared successfully." << endl;
    }
    else
    {
        cout << "Error opening the file." << endl;
    }
}

bool FileIsEmpty(string filename)
{
    std::ifstream infile(filename);
    bool status;

    if (infile.is_open())
    {
        infile.seekg(0, ios::end);       // Move the file pointer to the end
        streampos size = infile.tellg(); // Get the current position, which is the size of the file

        if (size == 0)
        {
            status = true;
        }
        else
        {
            status = false;
        }

        infile.close();
        return status;
    }
    else
    {
        cout << "Error opening the file." << endl;
    }

    return false;
}

class FileDirectoryTree
{
    struct Node
    {
        string name;
        string path;
        char type; // d for directory, f for file
        Node *right;
        Node *left;

        Node(string name_, string path_, char type_) : name(name_), path(path_), type(type_), left(nullptr), right(nullptr)
        {
        }
    };

    Node *root;

    void destroySubTree(Node *current)
    {
        if (current)
        {
            destroySubTree(current->left);
            destroySubTree(current->right);
            delete current;
        }
    }

public:
    FileDirectoryTree()
    {
        root = new Node("", "", '\0');

        root->left = new Node("PatientsData", "/PatientsData", 'd');
        root->left->left = new Node("PatientsHome", "/PatientsData PatientsHome", 'd');
        root->left->right = new Node("PatientList.txt", "/PatientsData PatientList.txt", 'f');

        root->right = new Node("Logs", "/Logs", 'd');
        root->right->left = new Node("LogsHome", "/Logs LogsHome", 'd');
        root->right->right = new Node("LogReport.pdf", "/Logs LogReport.pdf", 'f');
    }

    ~FileDirectoryTree()
    {
        destroySubTree(root);
        root = nullptr;
    }
    void DisplayInTreeView()
    {
        if (!root)
        {
            cout << "The Tree is empty!" << endl;
            return;
        }

        Node *current = root;

        Queue<Node *> traversal;
        traversal.enqueue(current);

        while (!traversal.isEmpty())
        {
            int lvl_size = traversal.getNumItems();
            // cout<<lvl_size<<endl;

            for (int i = 0; i < lvl_size; i++)
            {
                current = traversal.showFront();
                traversal.dequeue();

                cout << current->name << "  ";

                if (current->left)
                    traversal.enqueue(current->left);
                if (current->right)
                    traversal.enqueue(current->right);
            }

            cout << endl;
        }
        cout << endl;
    }

    void Display()
    {
        if (!root)
        {
            cout << "The Tree is empty!" << endl;
            return;
        }
        Node *current = root;
        Queue<Node *> q;
        q.enqueue(current);
        int size;

        Node *temp;

        while (!q.isEmpty())
        {
            size = q.getNumItems();
            for (int i = 0; i < size; i++)
            {
                temp = q.showFront();
                q.dequeue();
                cout << temp->path << endl;

                if (temp->left)
                    q.enqueue(temp->left);
                if (temp->right)
                    q.enqueue(temp->right);
            }
            cout << endl;
        }
    }

private:
    Node *insertDirectoryAtLast(Node *current, string name)
    {
        while (current->left)
        {
            current = current->left;
        }

        Node *newNode = new Node(name, current->path + " " + name, 'd');
        current->left = newNode; // Add the new node as the left child

        return current->left;
    }

public:
    void insertDirectory(string path, string name)
    {
        Node *current = root;
        bool insertAtLast = false;
        // if (path == "/PatientsData PatientsHome")
        // {
        //     insertAtLast = true;
        // }
        // else if (path == "/Logs LogsHome")
        // {
        //     insertAtLast = true;
        // }
        if (path == "/PatientsData")
        {
            cout << "Cannot insert in this directory!" << endl;
            return;
        }
        else if (path == "/Logs")
        {
            cout << "Cannot insert in this directory!" << endl;
            return;
        }

        while (current)
        {
            if (current->left && current->left->path == path)
            {
                if (current->left->type == 'f')
                {
                    cout << "Cannot insert directory into this file!" << endl;
                    return;
                }
                if (!current->left->left)
                {
                    Node *newNode = new Node(name, path + " " + name, 'd');
                    current->left->left = newNode; // Add the new node as the left child
                    cout<<"Directory inserted successfully!" << endl;
                }
                else
                {
                    if (insertAtLast)
                    {
                        insertDirectoryAtLast(current->left, name);
                        cout<<"Directory inserted successfully!" << endl;
                        return;
                    }
                    Node *newNode = new Node(name, path + " " + name, 'd');
                    newNode->left = current->left->left;
                    current->left->left = newNode;
                    cout<<"Directory inserted successfully!" << endl;
                    Node *temp_current = current->left->left->left;
                    int path_last_index = path.length();
                    while (temp_current)
                    {
                        temp_current->path.insert(path_last_index, " " + name);
                        if (temp_current->right)
                        {
                            temp_current->right->path.insert(path_last_index, " " + name);
                        }
                        temp_current = temp_current->left;
                    }
                }
                return; // Exit the function after insertion
            }
            else if (current->left && path.find(current->left->path) != string::npos)
            {
                current = current->left;
            }
            else if (current->right && path.find(current->right->path) != string::npos)
            {
                current = current->right;
            }
            else
            {
                cout << "Invalid input of path to insert directory!" << endl;
                return;
            }
        }
    }

    void insertFile(string path, string name, string type)
    {
        Node *current = root;
        bool insertAtLast = false;
        if (path == "/PatientsData PatientsHome")
        {
            insertAtLast = true;
        }
        else if (path == "/Logs LogsHome")
        {
            insertAtLast = true;
        }
        else if (path == "/PatientsData")
        {
            cout << "Cannot insert in this directory!" << endl;
            return;
        }
        else if (path == "/Logs")
        {
            cout << "Cannot insert in this directory!" << endl;
            return;
        }

        while (current)
        {
            if (current->left && current->left->path == path)
            {
                if (current->left->type == 'f')
                {
                    cout << "Cannot insert file into the file!" << endl;
                    return;
                }

                if (insertAtLast)
                {
                    current = insertDirectoryAtLast(current->left, "FolderOf" + name);
                    Node *newNode = new Node(name + type, current->path + " " + name + type, 'f');
                    current->right = newNode; // Add the new node as the left child
                    cout<<"File inserted successfully!" << endl;
                    return;
                }

                if (!current->left->right)
                {
                    if (current->left->name == "PatientsHome" || current->left->name == "LogsHome")
                    {
                        cout << "Cannot add file to the folder PatientsHome or LogsHome" << endl;
                        return;
                    }

                    Node *newNode = new Node(name + type, path + " " + name + type, 'f');
                    current->left->right = newNode; // Add the new node as the left child
                    cout<<"File inserted successfully!" << endl;
                }
                else
                {
                    char choice;
                input_choice:
                    cout << "Do you want to rewrite the existing file(y/n): " << endl;
                    cin >> choice;

                    if (choice == 'n')
                    {
                        return;
                    }
                    else if (choice == 'y')
                    {
                        Node *temp = current->left->right;
                        Node *newNode = new Node(name + type, path + " " + name + type, 'f');
                        current->left->right = newNode; // Add the new node as the left child
                        cout<<"File inserted successfully!" << endl;
                        delete temp;
                    }
                    else
                    {
                        cout << "Invalid input!" << endl;
                        goto input_choice;
                    }
                }
                return; // Exit the function after insertion
            }
            else if (current->left && path.find(current->left->path) != string::npos)
            {
                current = current->left;
            }
            else if (current->right && path.find(current->right->path) != string::npos)
            {
                current = current->right;
            }
            else
            {
                cout << "Invalid input of path to insert directory!" << endl;
                return;
            }
        }
    }

private:
    Node *findNodeByName(Node *current, const string name)
    {
        if (!current)
            return nullptr;

        if (current->name == name)
            return current; // returns the target node otherwise nullptr is returned

        // Search in the left subtree
        Node *leftResult = findNodeByName(current->left, name);
        if (leftResult)
            return leftResult;

        // If not found in the left subtree, search in the right subtree
        return findNodeByName(current->right, name);
    }

public:
    void copy(string fileName, string destinationDirectory)
    {
        Node *source = root, *destination = root;

        source = findNodeByName(source, fileName);
        destination = findNodeByName(destination, destinationDirectory);
        if (!source)
        {
            cout << "Source file " << fileName << " not found! " << endl;
            return;
        }
        else
        {
            if (source->type != 'f')
            {
                cout << "fileName is incorrect! Cannot add directory name inplace of file Name" << endl;
                return;
            }
        }
        if (!destination)
        {
            cout << "Destination directory " << destinationDirectory << " not found! " << endl;
            return;
        }
        else
        {
            if (destination->type != 'd')
            {
                cout << "Directory Name is incorrect! Cannot add file Name inplace of directory Name" << endl;
                return;
            }
        }

        if (!destination->right)
        {
            destination->right = new Node(fileName, destination->path + " " + fileName, 'f');
            cout<<"File copied successfully!" << endl;
        }
        else
        {
            char choice;
        take_choice_for_copy:
            cout << "The destination directory is not empty! Do you want to overwrite the file of this directory?(y/n) or cancle copy proccess(c)" << endl;
            cin >> choice;

            if (choice == 'n')
            {
                cout << "file is not copied!" << endl;
            }
            else if (choice == 'y')
            {
                destination->right->name = fileName;
                destination->right->path = destination->path + " " + fileName;
                cout<<"File copied successfully!" << endl;
            }
            else if (choice == 'c')
            {
                cout << "Copy Proccess canceled!" << endl;
                cout << "file is not copied!" << endl;
            }
            else
            {
                cout << "Invalid input!" << endl;
                goto take_choice_for_copy;
            }
        }
    }

    void move(string fileName, string destinationDirectory)
    {
        Node *source = root, *destination = root;

        source = findNodeByName(source, fileName);
        destination = findNodeByName(destination, destinationDirectory);

        string SourceFolderName;

        if (!source)
        {
            cout << "Source file " << fileName << " not found! " << endl;
            return;
        }
        else
        {
            if (source->type != 'f')
            {
                cout << "fileName is incorrect! Cannot add directory name inplace of file Name" << endl;
                return;
            }

            string temp = source->path;
            string temp2 = " " + fileName;
            int i = temp.find(temp2);
            temp.erase(i, temp2.length());
            int j;
            for (j = temp.length() - 1; temp[j - 1] != ' '; j--)
            {
            }
            temp.erase(0, j);
            SourceFolderName = temp;
        }

        if (!destination)
        {
            cout << "Destination directory " << destinationDirectory << " not found! " << endl;
            return;
        }
        else
        {
            if (destination->type != 'd')
            {
                cout << "Directory Name is incorrect! Cannot add file Name inplace of directory Name" << endl;
                return;
            }
        }

        if (!destination->right)
        {
            deleteNode(fileName);
            destination->right = new Node(fileName, destination->path + " " + fileName, 'f');
            cout<<"File moved successfully!" << endl;

            source = nullptr;
            source = findNodeByName(root, SourceFolderName);
            if (!source->left && !source->right)
            {
                char choice;
            ch_1:
                cout << "Folder of source file becomes empty!" << endl;
                cout << "Do you want to delete it(y/n)?" << endl;
                cin >> choice;

                if (choice == 'y')
                    deleteNode(SourceFolderName);
                else if (choice == 'n')
                {
                    cout << "Folder not deleted!" << endl;
                    return;
                }
                else
                {
                    cout << "Invalid choice! Enter again" << endl;
                    goto ch_1;
                }
            }
        }
        else
        {
            char choice;
        take_choice_for_copy:
            cout << "The destination directory is not empty! Do you want to overwrite the file of this directory?(y/n) or cancle move proccess(c)" << endl;
            cin >> choice;

            if (choice == 'n')
            {
                cout << "file is not moved!" << endl;
            }
            else if (choice == 'y')
            {
                deleteNode(fileName);
                destination->right->name = fileName;
                destination->right->path = destination->path + " " + fileName;
                cout<<"File moved successfully!" << endl;

                source = nullptr;
                source = findNodeByName(root, SourceFolderName);
                if (!source->left && !source->right)
                {
                    char choice2;
                ch_2:
                    cout << "Folder of source file becomes empty!" << endl;
                    cout << "Do you want to delete it(y/n)?" << endl;
                    cin >> choice2;

                    if (choice == 'y')
                        deleteNode(SourceFolderName);
                    else if (choice == 'n')
                    {
                        cout << "Folder not deleted!" << endl;
                    }
                    else
                    {
                        cout << "Invalid choice! Enter again" << endl;
                        goto ch_2;
                    }
                }
            }
            else if (choice == 'c')
            {
                cout << "Move Proccess canceled!" << endl;
                cout << "file is not copied!" << endl;
            }
            else
            {
                cout << "Invalid input!" << endl;
                goto take_choice_for_copy;
            }
        }
    }

    void mergeDirectories(string sourceName, string destinationName)
    {
        Node *source = root, *destination = root;

        source = findNodeByName(source, sourceName);
        destination = findNodeByName(destination, destinationName);

        if (!source)
        {
            cout << "Source directroy " << sourceName << " not found! " << endl;
            return;
        }
        if (!destination)
        {
            cout << "Destination directory " << destinationName << " not found! " << endl;
            return;
        }

        if (source->type == 'f' || destination->type == 'f')
        {
            cout << "Files cannot be merged! only directories can be merged" << endl;
            return;
        }

        if (source->right)
        {
            move(source->right->name, destination->name);
            source = findNodeByName(source, sourceName);
            if (source)
                deleteNode(sourceName);

            char choice;

        renaming_choice:
            cout << "Do you want to rename destination folder?(y/n)" << endl;
            cin >> choice;
            if (choice == 'y')
                renameNode(destinationName);
            else if (choice == 'n')
                return;
            else
            {
                cout << "Invalid input! " << endl;
                goto renaming_choice;
            }
        }
        else
        {
            deleteNode(sourceName);
            goto renaming_choice;
        }
        cout<<"Directories merged successfully!" << endl;
    }

private:
    void performingDeletion(Node *&current, const string name, bool &isDeleted)
    {
        if (current->type == 'f')
        {
            delete current;
            current = nullptr; // not working
            isDeleted = true;
        }
        else
        {
            if (!current->left && !current->right)
            {
                delete current;
                current = nullptr;
                isDeleted = true;
            }
            else if (!current->left)
            {
                char choice;
            take_choice_for_deletion2:
                cout << "This directory is not empty! Do you want to merge this directory with another? or continue deletion" << endl;
                cout << "Enter your choice to merge the direcotory(y/n) or cancle deletion(c)" << endl;
                cin >> choice;

                if (choice == 'n')
                {
                    isDeleted = true;
                    delete current->right;
                    delete current;
                    current = nullptr;
                }
                else if (choice == 'y')
                {
                    string destination;
                    cout << "Enter the name of the destination directory: ";
                    cin >> destination;

                    mergeDirectories(current->name, destination);
                    cout << "Directories merged then the source file is deleted" << endl;
                    isDeleted = true;
                }
                else if (choice == 'c')
                {
                    cout << "Deletion Proccess canceled!" << endl;
                }
                else
                {
                    cout << "Invalid input!" << endl;
                    goto take_choice_for_deletion2;
                }
            }
            else if (!current->right)
            {
                isDeleted = true;
                Node *temp = current;
                string deletedName = " " + temp->name;
                current = temp->left;
                delete temp;

                temp = nullptr;
                temp = current;
                int i = temp->path.find(deletedName);
                while (temp)
                {
                    temp->path.erase(i, deletedName.length());
                    if (temp->right)
                    {
                        temp->right->path.erase(i, deletedName.length());
                    }
                    temp = temp->left;
                }
            }
            else
            {
                char choice;
            take_choice_for_deletion:
                cout << "This directory is not empty! Do you want to merge this directory with another? or continue deletion" << endl;
                cout << "Enter your choice to merge the direcotory(y/n) or cancle deletion(c)" << endl;
                cin >> choice;

                if (choice == 'n')
                {
                    isDeleted = true;
                    Node *temp = current;
                    string deletedName = " " + temp->name;
                    current = temp->left;
                    delete temp->right;
                    delete temp;

                    temp = nullptr;
                    temp = current;
                    int i = temp->path.find(deletedName);
                    while (temp)
                    {
                        temp->path.erase(i, deletedName.length());
                        if (temp->right)
                        {
                            temp->right->path.erase(i, deletedName.length());
                        }
                        temp = temp->left;
                    }
                }
                else if (choice == 'y')
                {
                    string destination;
                    cout << "Enter the name of the destination directory: ";
                    cin >> destination;

                    mergeDirectories(current->name, destination);
                    cout << "Directories merged then the source file is deleted" << endl;
                    isDeleted = true;
                }
                else if (choice == 'c')
                {
                    cout << "Deletion Proccess canceled!" << endl;
                }
                else
                {
                    cout << "Invalid input!" << endl;
                    goto take_choice_for_deletion;
                }
            }
        }
    }
    void makeDeletion(Node *&current, const string name, bool &isDeleted)
    {
        if (!current)
            return;

        if (current->name == name)
        {
            performingDeletion(current, name, isDeleted);
            return;
        }

        makeDeletion(current->left, name, isDeleted);
        makeDeletion(current->right, name, isDeleted);
    }

public:
    bool deleteNode(string name)
    {
        bool isDeleted = false;
        makeDeletion(root, name, isDeleted);

        return isDeleted;
    }

    void renameNode(string name) // pass the name of the node you want to rename
    {
        Node *target = root;
        target = findNodeByName(target, name);

        if (!target)
        {
            cout << "Invalid input! (Target file/directory not found for renaming)" << endl;
        }
        else
        {
            string name;
            string type;
            cout << "Enter the new name of the directory or file(with out type): ";
            cin >> name;
            if (target->type == 'f')
            {
                cout << "Enter the extension type(.txt or .pdf) of the file: ";
                cin >> type;
                name = name + type;

                string prevName = target->name;
                target->name = name;
                int i = target->path.find(prevName);
                target->path.replace(i, prevName.length(), name);
                cout << "File renamed successfully!" << endl;
            }
            else
            {
                string prevName = target->name;
                target->name = name;
                int i = target->path.find(prevName);
                target->path.replace(i, prevName.length(), name);

                if (target->right)
                {
                    target->right->path.replace(i, prevName.length(), name);
                }

                if (target->left)
                {
                    Node *current = target->left;
                    while (current)
                    {
                        current->path.replace(i, prevName.length(), name);

                        if (current->right)
                        {
                            current->right->path.replace(i, prevName.length(), name);
                        }

                        current = current->left;
                    }
                }
                cout << "Directory Renamed successfully!" << endl;
            }
        }
    }

    void searchNode(string name)
    {
        Node *target = findNodeByName(root, name);

        if (!target)
        {
            cout << "The target directory or file does not exist!" << endl;
            return;
        }

        if (target->type == 'f')
            cout << "The Path of the file is: " << target->path << endl;
        else
        {
            cout << "The directory exists! " << endl;
        }
    }

private:
    void serialize(Node *current, ofstream &outfile)
    {
        if (!current)
        {
            outfile << "#" << endl; // Using '#' to represent null nodes
            return;
        }

        outfile << "name:" << current->name << " path:" << current->path << " type:" << current->type << endl;

        serialize(current->left, outfile);
        serialize(current->right, outfile);
    }

public:
    void writeFromTreeToFile(string filename)
    {
        if (!root)
        {
            cout << "The Tree is empty!" << endl;
            return;
        }
        if (!FileIsEmpty(filename))
        {
            cout << "The file already contains data of a tree!" << endl;
            char choice;
            cout << "Do you want clear the file!(y/n)" << endl;
            cin >> choice;

            if (choice == 'y')
            {
                clearTheFile(filename);
            }
            else if (choice == 'n')
            {
                cout << "The file is not cleared and the data of the tree is not written!" << endl;
                return;
            }
            else
            {
                cout << "The file is not cleared and the data of the tree is not written!" << endl;
                return;
            }
        }
        ofstream outfile(filename);
        serialize(root, outfile);
        outfile.close();

        cout<<"Tree is exported successfully!"<<endl;
    }

private:
    // Deserialization
    Node *deserialize(ifstream &infile)
    {
        string value;
        string name, path;
        char type;
        getline(infile, value);

        if (value == "#")
            return nullptr;

        size_t i = value.find("name:");
        size_t j = value.find("path:");
        size_t k = value.find("type:");

        name = value.substr(i + 5, j - (i + 5));
        path = value.substr(j + 6, k - (j + 6));
        type = value[k + 5];

        Node *current = new Node(name, path, type);

        current->left = deserialize(infile);
        current->right = deserialize(infile);

        return current;
    }

public:
    void readFromFileToTree(string filename)
    {
        if (FileIsEmpty(filename))
        {
            cout << "File is empty!" << endl;
            return;
        }
        if (root)
        {
            cout << "The Tree already exists!" << endl;
            return;
        }
        ifstream infile(filename);
        root = deserialize(infile);
        infile.close();
        cout<<"The Tree is imported successfully!" << endl;
    }
};

#endif // FILEDIRECTORYTREE_H
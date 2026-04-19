// Muhammad Yousaf
// i228797
// SE-F
#include <iostream>
#include "string"
#include "FileDirectoryTree.h"
using namespace std;

void Menu()
{
	FileDirectoryTree fileTree;
	int choice;
	bool DoDisplay = false;
	while (true)
	{
		system("cls");

		cout << "1. Add Directory" << endl
			 << "2. Add File" << endl
			 << "3. List of Directoty in Tree view" << endl
			 << "4. Merge Directory" << endl
			 << "5. Delete file/directory" << endl
			 << "6. Rename file/directory" << endl
			 << "7. Search file/directory" << endl
			 << "8. Copy file" << endl
			 << "9. Move file" << endl
			 << "10.import form file to tree" << endl
			 << "11.export to file from tree" << endl
			 << "12.Simple Display" << endl
			 << "13.Delete Tree" << endl
			 << "14.Clear File" << endl
			 << "15.exit" << endl
			 << endl;

		if (DoDisplay)
		{
			cout << "Diplaying Data________________" << endl;
			fileTree.Display();
			cout << "______________________________________________________";
			cout << endl;
			DoDisplay = false;
		}

		cout << "Enter your choice from the given Menu: ";
		while (true)
		{
			if (cin >> choice)
			{
				break;
			}
			else
			{
				// Clear the error state
				cin.clear();
				// Discard invalid input in the buffer
				cin.ignore(numeric_limits<streamsize>::max(), '\n');

				cout << "Invalid input. Please enter an integer:" << std::endl;
			}
		}

		string path, name, type; // variables required in switch cases
		switch (choice)
		{
		case 1:
		{
			cin.clear();
			cin.ignore();
			cout << "Enter the path for the directory: ";
			getline(cin, path);

			cout << "Enter the name of the directory: ";
			cin >> name;

			fileTree.insertDirectory(path, name);
		}
		break;
		case 2:
		{
			cin.clear();
			cin.ignore();
			cout << "Enter the path of the directory in which you want to insert file: ";
			getline(cin, path);
			cout << "Enter the name of the file without type: ";
			cin >> name;
			cout << "Enter the extension type(.txt or .pdf) of the file: ";
			cin >> type;

			fileTree.insertFile(path, name, type);
		}
		break;
		case 3:
			fileTree.DisplayInTreeView();
			break;
		case 4:
		{
			string sourceName, destinationName;
			cout << "Enter the source directory name: ";
			cin >> sourceName;
			cout << "Enter the destination directory name: ";
			cin >> destinationName;

			fileTree.mergeDirectories(sourceName, destinationName);
		}
		break;
		case 5:
		{
			// deletion
			cout << "Enter the full name of the directory or file with its type(.pdf or .txt) as postfix: ";
			cin >> name;
			if (fileTree.deleteNode(name))
			{
				cout << "File/Directory Deleted successfully!" << endl;
			}
			else
			{
				cout << "File/Directory not found!" << endl;
			}
		}
		break;
		case 6:
		{
			// renaming
			cout << "Enter the full name of the directory or file with its type(.pdf or .txt) as postfix: ";
			cin >> name;

			fileTree.renameNode(name);
		}
		break;
		case 7:
		{
			cout << "Enter the full name of the directory or file with its type(.pdf or .txt) as postfix: ";
			cin >> name;

			fileTree.searchNode(name); // not confirm if we take path or name for the directory
		}
		break;
		case 8:
		{
			string fileName, destinationDirectoryName;
			cout << "Enter the file name with its type(.pdf or .txt) as postfix: ";
			cin >> fileName;
			cout << "Enter the destination directory name :";
			cin >> destinationDirectoryName;
			fileTree.copy(fileName, destinationDirectoryName);
		}
		break;
		case 9:
		{
			string fileName, destinationDirectoryName;
			cout << "Enter the file name with its type(.pdf or .txt) as postfix: ";
			cin >> fileName;
			cout << "Enter the destination directory name :";
			cin >> destinationDirectoryName;
			fileTree.move(fileName, destinationDirectoryName);
		}
		break;
		case 10:
			fileTree.readFromFileToTree("TreeFile.txt");
			break;
		case 11:
			fileTree.writeFromTreeToFile("TreeFile.txt");
			break;
		case 12:
			DoDisplay = true;
			break;
		case 13:
			fileTree.~FileDirectoryTree();
			break;
		case 14:
			clearTheFile("TreeFile.txt");
			break;
		case 15:
			exit(0);
			break;

		default:
			cout << "Invalid input!" << endl;
			break;
		}

		if (!DoDisplay)
			system("pause");
	}
}

int main()
{
	// FileDirectoryTree t;
	// t.Display();
	// t.insertDirectory("/PatientsData PatientsHome", "a");
	// t.Display();
	// t.insertFile("/PatientsData PatientsHome a", "report", ".pdf");
	// t.Display();
	// t.insertFile("/PatientsData PatientsHome a", "report2", ".pdf");
	// t.Display();

	Menu();
}

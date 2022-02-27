
#include <iostream>
using namespace std;

#include "BST.h"

BST<char> charBST; //creating empty bst

int main()
{
    while (1) {     //while loop for menu
        int userChoice;
        cout << "-------------------- MENU ----------------------" << endl;
        cout << "\t\t1. Insert node(s)" << endl;
        cout << "\t\t2. Traverse Preorder" << endl;
        cout << "\t\t3. Search BST" << endl;
        cout << "\t\t4. Delete node" << endl;
        cout << "\t\t5. Leaf Count" << endl;
        cout << "\t\t6. Sibling of a node" << endl;
        cout << "\t\t7. Quit" << endl;
        cout << "\n\nEnter your choice: ";
        cin >> userChoice;

        switch (userChoice) { //switch for each user menu option
        case 1:
            cout << "\nNow insert a bunch of letters into the BST."
                "\nTry items not in the BST and some that are in it:\n";
            char letter;
            for (;;)
            {
                cout << "Item to insert ('=' to stop): ";
                cin >> letter;
                if (letter == '=') break; //taking user input until they exit
                cout << letter << " inserted" << endl;
                charBST.insert(letter); //sending letter to insert function
            }

            cout << endl;
            continue; //to set back to menu
            break;

        case 2:
            cout << "Preorder Traversal of BST: \n";
            charBST.preorder(cout); //displaying traverse
            continue;
            break;

        case 3:
            cout << "\n\nNow testing the search() operation."
                "\nTry both items in the BST and some not in it:\n";
            for (;;)
            {
                cout << "Item to find ('=' to stop): ";
                cin >> letter;
                if (letter == '=') break;
                cout << (charBST.search(letter) ? "Found" : "Not found") << endl; //checking bst to see if letter found
            }
            continue;
            break;

        case 4:
            cout << "\nNow testing the remove() operation."
                "\nTry both items in the BST and some not in it:\n";
            for (;;)
            {
                cout << "Item to remove ('=' to stop): ";
                cin >> letter;
                if (letter == '=') break;
                charBST.remove(letter); //sending letter to be removed to remove function
                cout << letter << " removed.\n";
            }
            cout << "\nPreorder Traversal of BST: \n";
            charBST.preorder(cout);
            cout << endl;
            continue;
            break;

        case 5:
            cout << "\n Now testing the leaf count.\n" << endl;
            charBST.leafcount(); //calling leaf function
            continue;
            break;

        case 6:
            cout << "\nNow testing the nodesibling() operation." << endl;
            for (;;)
            {
                cout << "Item to find sibling of ('=' to stop): ";
                cin >> letter;
                if (letter == '=') break;
                charBST.nodesibling(letter);  //checking if user letter has sibling
            }
            continue;
            break;

        case 7:
            break; //quit command
        }
        break;
    }
}

#include "menu.h"

#include <iostream>
using std::cout;
using std::cin;
using std::endl;
using std::stringstream;

int main() {
    int selected;

    Menu menu1(2);
    menu1.SetTitle("A Menu");
    menu1.SetInputType(INT);
    menu1.SetErrorMessage("Your input was not recognized, perhaps input a string where a number is expected");
    menu1.SetInvalidOption("Your input is not one of the given choices");
    menu1.AddMenuOption(0, "1", "first");
    menu1.AddMenuOption(1, "2", "second");
    while ((selected = menu1.Run()) != EXIT){
        switch (selected) {
            case INVALID_INPUT:

                break;
            case INPUT_ERROR:
                break;
            case 0:
                cout << "User Selected the first choice... do something" << endl;
                break;
            case 1:
                cout << "User Selected the second choice... second plate, so sad" << endl;
                break;
        }
    }
    cout << "----------------------------" << endl;
    cout << "The end of Menu 1" << endl << endl << endl;

    Menu menu2(3);
    menu2.SetTitle("A Second Menu");
    menu2.SetInputType(STRING);
    menu2.SetErrorMessage("Your input was not recognized");
    menu2.SetInvalidOption("Your input is not one of the given choices");
    menu2.AddMenuOption(0, "Alpha", "This is the Alpha Option");
    menu2.AddMenuOption(2, "Sigma", "This is the Sigma Option");

    while ((selected = menu2.Run()) != EXIT){
        switch (selected) {
            case INVALID_INPUT:
                break;
            case INPUT_ERROR:
                break;
            case 0:
                cout << "Alpha Centauri is near" << endl;
                break;
            case 1:
                cout << "This should not happen" << endl;
                break;
            case 2:
                cout << "Sigma is the name of the summation" << endl;
                break;
        }
    }
    cout << "----------------------------" << endl;
    cout << "The end of Menu 2" << endl << endl << endl;

    Menu menu3(3);
    menu3.SetTitle("A Third Menu");
    menu3.SetInputType(CHAR);
    menu3.SetErrorMessage("Your input was not recognized --");
    menu3.SetInvalidOption("Your input is not one of the given choices --");
    menu3.AddMenuOption(0, "a", "A for Apple");
    menu3.AddMenuOption(1, "b", "B for Book");
    menu3.AddMenuOption(2, "c", "C for... cube?");

    while ((selected = menu3.Run()) != EXIT){
        switch (selected) {
            case INVALID_INPUT:
                break;
            case INPUT_ERROR:
                break;
            case 0: // The case numbers correspond to the optionNumbers when adding the menu options
                cout << "Apple is a brand" << endl;
                break;
            case 1:
                cout << "Book is an object" << endl;
                break;
            case 2:
                cout << "Cube is a solid" << endl;
                break;
        }
    }
    cout << "----------------------------" << endl;
    cout << "The end of Menu 3" << endl << endl << endl;

    Menu menu4(5);
    menu4.SetTitle("Bookstore Menu");
    menu4.SetInputType(INT);
    menu4.SetErrorMessage("- - > Unrecognized Input < - -");
    menu4.SetInvalidOption("- - > Please Input One of the Given Choices < - -");
    menu4.AddMenuOption(0, "1", "Add book");
    menu4.AddMenuOption(1, "2", "List Books");
    menu4.AddSeparator(2);
    menu4.AddMenuOption(3, "3", "Update Book");
    menu4.AddMenuOption(4, "4", "Remove Book");

    while ((selected = menu4.Run()) != EXIT){
        switch (selected) {
            case INVALID_INPUT:
                break;
            case INPUT_ERROR:
                break;
            case 0: // The case numbers correspond to the optionNumbers when adding the menu options
                cout << "Add a new Book" << endl;
                cout << "Input the name: " << endl;
                cout << " ... " << endl;
                break;
            case 1:
                cout << "Listing all books" << endl;
                cout << "1. a book" << endl;
                cout << "2. another book" << endl;
                cout << "3. cooking book" << endl;
                cout << endl << endl;
                break;
            case 2:
                cout << "Should not happen!" << endl;
                break;
            case 3:
                cout << "Update a book" << endl;
                cout << "1. a book" << endl;
                cout << "2. another book" << endl;
                cout << "3. cooking book" << endl;
                cout << endl << endl;
                cout << "What book you want to modify: " << endl;
                cout << " ... " << endl;
                break;
            case 4:
                cout << "Remove a book" << endl;
                cout << "1. a book" << endl;
                cout << "2. another book" << endl;
                cout << "3. cooking book" << endl;
                cout << endl << endl;
                cout << "What book you want to remove: " << endl;
                cout << " ... " << endl;
                break;
        }
    }
    cout << "The end of Menu 4" << endl << endl << endl << endl;


    return 0;
}

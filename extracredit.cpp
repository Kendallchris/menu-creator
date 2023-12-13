/**
 * Title:   Lab 3 - Working With Arrays Extra Credit: extracredit.cpp
 *
 * Purpose: Work with menu class to work dynamically with Arrays
 * Class:   CSC 2330 Fall 2022
 * Author:  Chris Kendall
 */

#include <iostream>
#include <iomanip>
#include "menu.h"
#include <cctype>

using std::cout;
using std::cin;
using std::endl;
using std::setw;
using std::fixed;
using std::setprecision;
using std::stringstream;

int IsInteger(const string& str);
void RemoveNum(size_t& numElements, double* arrayPointer, const size_t& toRemove);
double GetAverage(const size_t& numElements, double* arrayPointer);
void ListElements(const double* arrayPointer, const size_t& numElements);

int main(){
    int selected;
    int size;
    string selection;
    bool arrayCreated = false;
    double toAdd;
    size_t toRemove;
    size_t numElements = 0;
    double* arrayPointer = nullptr;

    // creating Menu
    Menu menu(7);
    menu.SetErrorMessage("- - > Please Input One of the Given Choices < - -");
    menu.SetInvalidOption("- - > Unrecognized Input < - -");
    menu.SetInputType(INT);
    menu.SetTitle("Working with Arrays");
    menu.AddMenuOption(0, "1", "Set Size of the Array");
    menu.AddSeparator(1);
    menu.AddMenuOption(2, "2", "Add Number to the Array");
    menu.AddMenuOption(3, "3", "List the Numbers");
    menu.AddMenuOption(4, "4", "Remove a Number");
    menu.AddSeparator(5);
    menu.AddMenuOption(6, "5", "Calculate Average");


    while ((selected = menu.Run()) != EXIT){
        switch (selected) {
            case INVALID_INPUT:
                break;
            case INPUT_ERROR:
                break;
            case 0: // Creating Array
                cout << "Please input the maximum capacity of the array: ";
                cin >> selection;

                // checking to see if input is an int
                if ((size = IsInteger(selection)) > 0) {
                    arrayPointer = new double[size];
                    cout << "Array Created Successfully" << endl;
                    arrayCreated = true;
                }
                break;
            case 2: //Adding number to array
                // making sure the array is created and that it is not already full
                if (!arrayCreated) {
                    cout << "Need to create array first!" << endl;
                    break;
                } else if (numElements == size) {
                    cout << "The array is already full, remove a number first." << endl;
                    break;
                }

                cout << "Please input the number you want to add: ";
                cin >> toAdd;
                arrayPointer[numElements] = toAdd;
                cout << "Number " << setprecision(6) << fixed << toAdd << " Added to Position " << numElements << " Successfully" << endl;
                numElements++;

                break;
            case 3: // Listing array
                // making sure the array is created
                if (!arrayCreated) {
                    cout << "Need to create array first!" << endl;
                    break;
                }

                cout << "Listing Numbers" << endl;
                ListElements(arrayPointer, numElements);

                break;
            case 4: // Removing number from array
                // making sure the array is created
                if (!arrayCreated) {
                    cout << "Need to create array first!" << endl;
                    break;
                }

                cout << "Remove a Number" << endl;
                ListElements(arrayPointer, numElements);
                cout << "What is the position where you want to remove a number: ";
                cin >> toRemove;

                // making sure input is a valid position
                if (toRemove > numElements) {
                    cout << "Invalid Position" << endl;
                    break;
                }

                RemoveNum(numElements, arrayPointer, toRemove);
                cout << "Number in Position " << toRemove << " Removed Successfully" << endl;

                break;
            case 6: // Calculating average of array
                // making sure the array is created
                if (!arrayCreated) {
                    cout << "Need to create array first!" << endl;
                    break;
                }
                cout << "The average is: " << GetAverage(numElements, arrayPointer) << endl;
                break;
        }
    }

    delete[] arrayPointer;
    cout << "Finished the Program... Goodbye" << endl << endl;
    return 0;
}

/**
 * Creates a c-string copy of the passed string and makes sure that all values are digits.
 * @param str
 * @return the input as an int or -1 if it is not a valid input
 */
int IsInteger(const string& str) {
    size_t length = str.length();
    char cSelection[length];
    strcpy(cSelection, str.c_str());

    for (size_t i = 0; i < length; i++) {
        if (!isdigit(cSelection[i])) {
            cout << "Please input an integer only" << endl;
            return -1;
        }
    }
    int optionInt = stoi(str);
    return optionInt;
}

/**
 * Removes the designated index "toRemove" from the array and shifts the remaining indexes to fill its spot.
 * @param numElements
 * @param arrayPointer
 * @param toRemove
 */
void RemoveNum(size_t& numElements, double* arrayPointer, const size_t& toRemove) {
    double temp[numElements];
    size_t counter = 0;
    for (size_t i = 0; i <= numElements; i++) {
        if (i != toRemove) {
            temp[counter] = arrayPointer[i];
            counter++;
        }
    }
    for (size_t i = 0; i < numElements; i++) {
        arrayPointer[i] = temp[i];
    }
    numElements--;
}

/**
 * Calculates the average of all of the values stored in the array, returning it as a double.
 * @param numElements
 * @param arrayPointer
 * @return the average of all of the values contained in the array
 */
double GetAverage(const size_t& numElements, double* arrayPointer) {
    double average = 0.0;
    for (size_t i = 0; i <= numElements; i++) {
        average += arrayPointer[i];
    }
    return (average / (double)numElements);
}

/**
 * Simply lists the values contained in the array in a user-friendly format.
 * @param arrayPointer
 * @param numElements
 */
void ListElements(const double* arrayPointer, const size_t& numElements){
    for (size_t i = 0; i < numElements; i++) {
        cout << "   " << i << " " << arrayPointer[i] << endl;
    }
}



// EXTRA CREDIT IDEA
/**
 * Create a menu with the following options
 * 1. Set Size of the Array
 *  =========================
 * 2. Add Number to the Array
 * 3. List the Numbers
 * 4. Remove a Number
 *  ========================
 * 5. Calculate Average
 * 99. Exit
 *
 * AND the program that goes with it!  <------------ <------------- <--------------
 * What happens on each option:
 * 1. Creates a dynamic array of the size that the user inputs (frees the array if it was already created!)
 * >> None of the options below work if there is no array created!
 * 2. Reads a number from the user and adds it to the end of the array... if it fits, if it doesn't signals the error
 * 3. Shows all the numbers very nicely formatted in the screen
 * 4. Given the position of the number it removes it from the array, it pushes the numbers if it is not the last
 * 5. Calculates the average of the numbers in the array
 */
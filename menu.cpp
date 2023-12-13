/**
 * Title:   Lab 3 - Menu class Implementation: menu.cpp
 *
 * Purpose: Implements the class Menu
 * Class:   CSC 2330 Fall 2022
 * Author:  Chris Kendall
 */


#include "menu.h"
#include <iostream>
#include <string>
#include <cctype>
#include <cstring>

using std::endl;
using std::stringstream;
using std::string;


/**
 * The Menu constructor. Notice there is no default constructor. Notice that three streams can be sent to this
 * constructor, they will set _output, _input and _errorStream respectively. When you want to output something to
 * the screen you will use _output. For example:
 * _output << _menuTitle << endl;
 * That statement would send the title of the menu to whatever output stream has be set, by default cout.
 * @param numberOfOptions the number of options the menu will have, remember to include the separators
 * @param output the stream that will be used to send the normal output, by default cout
 * @param input the stream that will be used to receive the normal input, by default cin
 * @param errorStream the stream that will be used to send error output, by default cerr
 */
Menu::Menu(int numberOfOptions, ostream &output, istream &input, ostream &errorStream):
    _numberOfOptions(numberOfOptions),
    _output(output),
    _input(input),
    _errorStream(errorStream){
    _menuElements = new MenuElement[numberOfOptions];
}
/**
 * Class destructor, in charge of cleaning the memory
 */
Menu::~Menu() {
    delete[] _menuElements;
}
/**
 * Finds the maximum length of all menu options, the purpose is to be able to find how many
 * characters are needed for the separators
 * @return the length of the largest menu option (includes option and text)
 */
size_t Menu::MaxMenuLength() const {
    size_t count = 0;
    for (size_t i = 0; i < _numberOfOptions; i++) {
        if (_menuElements[i].MenuElementWidth() > count) {
            count = _menuElements[i].MenuElementWidth();
        }
    }
    return count;
}

/**
 * Sets the error message
 * @param errorMessage The error message when the user inputs a string when a number is expected
 */
void Menu::SetErrorMessage(const string &errorMessage) {
    _errorMessage = errorMessage;
}

/**
 * Sets the invalid option error message
 * @param invalidMessage The error message when the user inputs an option that is not in the menu
 */
void Menu::SetInvalidOption(const string &invalidMessage) {
    _invalidMessage = invalidMessage;
}

/**
 * Sets the input type of the Menu
 * @param type What kind of input the Menu will have, see line 33 to see the available options
 */
void Menu::SetInputType(InputType type) {
    _inputType = type;
}

/**
 * Sets the title of the Menu
 * @param title menu title
 */
void Menu::SetTitle(const string &title) {
    _menuTitle = title;
}

/**
 * Gets the Error Message
 * @return The error message when the user inputs a string when a number is expected
 */
string Menu::GetErrorMessage() const {
    return _errorMessage;
}

/**
 * Gets the Invalid Option error Message
 * @return The error message when the user inputs an option that is not in the menu
 */
string Menu::GetInvalidOption() const {
    return _invalidMessage;
}

/**
 * Gets the input type
 * @return What kind of input the Menu will have, see line 33 to see the available options
 */
InputType Menu::GetInputType() const {
    return _inputType;
}

/**
 * Gets the title
 * @return menu title
 */
string Menu::GetTitle() const {
    return _menuTitle;
}

/**
 * This method is to add options to the menu. If the user sends an invalid optionNumber the method will return INVALID_MENU_INDEX. Users of this method
 * should never use as displayOption 99 or E, since they are reserved values for exiting.
 * @param optionNumber the slot where the menu is to be added. This represents the position in the array, the method needs to validate that it is a valid position 0<=optionNumber<_numberOfOptions
 * @param displayOption what the user needs to input to select a given menu option
 * @param menuOption the actual text that will be display as a menu option
 * @return INVALID_MENU_INDEX if optionNumber is greater than or equal than numberOfOptions, OVERWROTE_OPTION if there was something already in that array position, the optionNumber otherwise
 */
int Menu::AddMenuOption(unsigned int optionNumber, const string &displayOption, const string &menuOption) {
    if (optionNumber > _numberOfOptions - 1) {
        _errorStream << INVALID_MENU_INDEX;
        return -6;
    }
    if (_menuElements[optionNumber].GetMenuText().empty() && !_menuElements[optionNumber].IsSeparator()) {
        _menuElements[optionNumber] = MenuElement(displayOption, menuOption);
        return optionNumber;
    }
    _menuElements[optionNumber] = MenuElement(displayOption, menuOption);
    return -5;
}

/**
 * This method adds a separator to the menu. The method will need to call MaxMenuLength to see how big the separator needs to be and set the separator character to '-'.
 * If the user sends an invalid separatorPosition the method will return INVALID_MENU_INDEX
 * @param separatorPosition the slot position where the separator is going to be stored. The method needs to validate that it is a valid position 0<=separatorPosition<numberOfOptions
 * @return INVALID_MENU_INDEX if separatorPosition >= _numberOfOptions, OVERWROTE_OPTION if the slot had something already in that position, separatorPosition otherwise
 */
int Menu::AddSeparator(unsigned int separatorPosition) {
    size_t temp = MaxMenuLength();
    if (separatorPosition > _numberOfOptions - 1) {
        _menuElements[separatorPosition].SetSeparator(temp, '-');
        _errorStream << INVALID_MENU_INDEX;
        return -6;
    }
    _menuElements[separatorPosition].SetSeparator(temp, '-');
    return separatorPosition;
}

/**
 * This is the main driver of the class! This method will do the following operations:
 * 1. Output the Title
 * 2. Show all the menu options and separators
 * 3. Wait for the user to input the selection
 * 4. Return the user selection, or error appropriately
 * Remember you are outputting to _output, you are reading from _input and you are sending errors to _errorStream!
 * Furthermore, you will need to check what type of input the menu has, depending on that you will read numbers, a character or string.
 *      If your _inputType is INT and the user inputs a letter (or something that is not a number) then Run will return INPUT_ERROR
 *      If your _inputType is INT and the user inputs a number that is not an available option then run will return INVALID_INPUT
 *      If your _inputType is CHAR and the user inputs a string of more than one letter then Run will return INPUT_ERROR
 *      If your _inputType is CHAR and the user inputs a letter that is not an available option then run will return INVALID_INPUT
 *      If your _inputType is STRING and the user inputs a string that is not an available option then run will return INVALID_INPUT
 * @return the slot where the option has been stored (see optionNumber in AddMenuOption), if there is an error it will return the error value as noted above.
 */
int Menu::Run() const {
    _output << _menuTitle << endl;
    for (size_t i = 0; i < _numberOfOptions; i++) {
        _output << _menuElements[i].ToString() << endl;
    }
    if (_inputType == INT) {
        _output << "99 Exit\n";
    } else {
        _output << "Type E to Exit\n";
    }

    // local variables
    string selection;
    _input >> selection;
    size_t length = selection.length();
    char cSelection[length];

    // store the user's input into a c-string for easy manipulation
    strcpy(cSelection, selection.c_str());
    // calls Evaluate methode to determine if input is valid or not and to determine what is wrong with it if so
    int selectionPlace = Evaluate(cSelection, length);

    return selectionPlace;
}

/**
 * This is the primary logic method of this class. It checks the user's input (passes as a parameter "selection") as a c-string
 * and based on whether the expected input type is an INT, STRING, or CHAR it will check the validity of the input. If the
 * expected input is neither INT, STRING, or CHAR it returns -4, invalid input.
 *
 * If it is INT, it makes sure all the indexes
 * contain digits, changes the c-string to an int, checks for exit parameter (99), checks to see if the input is available
 * within the menu, and returns the value's index as an int.
 *
 * If it is a STRING, it checks for exit parameter ("E"), checks if the option value is within the menu, and returns the index
 * of the selection as an int.
 *
 * If it is a CHAR, it makes sure the c-string is only 1 index, checks for exit parameter ('E'), checks if the option is available
 * in the menu, and returns the index of the selection as an int.
 * @param selection
 * @param length
 * @return the selection index as an int or, if exit parameter, -1, or, if an invalid input, -2, or, if input is not available
 * in the menu, -3. Also, if expected input is neither INT, STRING, or CHAR, returns -4.
 */
int Menu::Evaluate(char* selection, const size_t &length) const {
    size_t optionPlace;
    bool isFound = false;

    // ***** INT *****
    if (_inputType == INT) {

        // check to see if all chars are digits
        for (size_t i = 0; i < length; i++) {
            if (!isdigit(selection[i])) {
                _errorStream << _errorMessage << endl;
                return -2;
            }
        }

        // change selection char to int
        int optionInt = atoi(selection);

        // check for exit parameter
        if (optionInt == 99) {
            return -1;
        }

        // check to see if option is available in the menu
        for (optionPlace = 0; optionPlace < _numberOfOptions; optionPlace++) {
            if (_menuElements[optionPlace].IsSeparator()) {
                continue;
            }
            int temp = stoi(_menuElements[optionPlace].GetSelectionOption());
            if (optionInt == temp) {
                isFound = true;
                break;
            }
        }
        if (!isFound) {
            _errorStream << _invalidMessage << endl;
            return -3;
        }
        return optionPlace;


    // ***** STRING *****
    } else if (_inputType == STRING) {
        string StrSelection = selection;

        // check for exit parameter
        if (StrSelection == "E") {
            return -1;
        }

        // check to see if option is available in the menu
        for (optionPlace = 0; optionPlace < _numberOfOptions; optionPlace++) {
            if (_menuElements[optionPlace].IsSeparator()) {
                continue;
            }
            string temp = _menuElements[optionPlace].GetSelectionOption();
            if (StrSelection == temp) {
                isFound = true;
                break;
            }
        }
        if (!isFound) {
            _errorStream << _invalidMessage << endl;
            return -3;
        }
        return optionPlace;


    // ***** CHAR *****
    } else if (_inputType == CHAR) {

        // check if option is more than one char
        if (length > 1) {
            _errorStream << _errorMessage << endl;
            return -3;
        }

        // check for exit parameter
        if (selection[0] == 'E') {
            return -1;
        }

        // check to see if option is available in the menu
        for (optionPlace = 0; optionPlace < _numberOfOptions; optionPlace++) {
            if (_menuElements[optionPlace].IsSeparator()) {
                continue;
            }
            char temp = _menuElements[optionPlace].GetSelectionOption()[0];
            if (selection[0] == temp) {
                isFound = true;
                break;
            }
        }
        if (!isFound) {
            _errorStream << _invalidMessage << endl;
            return -3;
        }
        return optionPlace;


    // ERROR: Expected input is neither INT, STRING, nor CHAR
    } else {
        _errorStream << "Error: InputType is neither Char, Int, or String";
        return -4;
    }
}

//
// Created by Carlos R. Arias on 1/25/22.
//


#include "menu.h"
#include "menu_element.h"

#include <sstream>
#include <string>
#include <iostream>
#include <iomanip>

using std::cout;
using std::cerr;
using std::endl;
using std::stringstream;
using std::string;
using std::setw;
using std::left;

void Test(bool condition, const char* message, unsigned int& passedTests);

int main(int argc, char* argv[]){
    unsigned int passedTests = 0;

// *********************************************************************************************************************
// Testing MenuElement class  ******************************************************************************************

    // Testing MenuElement class
    MenuElement* element = nullptr;

//  Testing Default Constructor
    element = new MenuElement();
    Test(element->IsSeparator() == false, "Menu Element Separator", passedTests);
    Test(element->GetSelectionOption() == "", "Menu Selection Option Empty", passedTests);
    Test(element->GetMenuText() == "", "Menu Text Empty", passedTests);
    Test(element->ToString() == " ", "Menu Element ToString", passedTests);
    Test(element->MenuElementWidth() == 1, "Menu Element Width", passedTests);
    delete element;

//  Testing MenuElement(size_t length, char separator);
    element = new MenuElement(10, '*');
    Test(element->IsSeparator() == true, "Menu Element Separator", passedTests);
    Test(element->GetSelectionOption() == "", "Menu Selection Option Empty", passedTests);
    Test(element->GetMenuText() == string(10, '*'), "Menu Text **********", passedTests);
    Test(element->ToString() == " **********", "Menu Element ToString", passedTests);
    Test(element->MenuElementWidth() == 11, "Menu Element Width", passedTests);
    delete element;

//  Testing MenuElement(const string& selectionOption, const string& menuText);
    element = new MenuElement("A", "The Alpha Choice");
    Test(element->IsSeparator() == false, "Menu Element Separator", passedTests);
    Test(element->GetSelectionOption() == "A", "Menu Selection Option \'A\'", passedTests);
    Test(element->GetMenuText() == "The Alpha Choice", "Menu Text The Alpha Choice", passedTests);
    Test(element->ToString() == "A The Alpha Choice", "Menu Element ToString", passedTests);
    Test(element->MenuElementWidth() == 18, "Menu Element Width", passedTests);
    delete element;

// Testing SetMenuElement and SetSeparator
    element = new MenuElement();
    element->SetSeparator(10, '-');
    Test(element->IsSeparator() == true, "Menu Element Separator", passedTests);
    element->SetMenuElement("1", "Number 1");
    Test(element->IsSeparator() == false, "SetMenuElement unsets IsSeparator", passedTests);
    Test(element->ToString() == "1 Number 1", "SetMenuElement successful", passedTests);
    delete element;

// *********************************************************************************************************************

// *********************************************************************************************************************
// Testing Menu class   ************************************************************************************************

    Menu* menu = nullptr;
    stringstream stdOutput, stdInput, stdError;
    int returnValue;
    string fullMenuText;

    // Testing with INT options
    menu = new Menu(4, stdOutput, stdInput, stdError);

    menu->SetErrorMessage("An Error Message");
    menu->SetInvalidOption("An Invalid Option Error Message");
    menu->SetInputType(INT);
    menu->SetTitle("Menu Title");
    Test(menu->GetErrorMessage() == "An Error Message", "Error Message Set", passedTests);
    Test(menu->GetInvalidOption() == "An Invalid Option Error Message", "Invalid Option Set", passedTests);
    Test(menu->GetInputType() == INT, "Input Type Set", passedTests);
    Test(menu->GetTitle() == "Menu Title", "Menu Title Set", passedTests);

    // Adding menu options
    returnValue = menu->AddMenuOption(0, "1", "Burger");
    Test(returnValue == 0, "Added Menu option to menu slot 0", passedTests);
    returnValue = menu->AddMenuOption(1, "2", "Sandwich");
    Test(returnValue == 1, "Added Menu option to menu slot 1", passedTests);
    returnValue = menu->AddMenuOption(1, "2", "Bacon Sandwich");
    Test(returnValue == OVERWROTE_OPTION, "Overwrote Menu option in menu slot 1", passedTests);
    returnValue = menu->AddMenuOption(2, "3", "Soda");
    Test(returnValue == 2, "Added Menu option to menu slot 2", passedTests);
    returnValue = menu->AddSeparator(3);
    Test(returnValue == 3, "Added Separator to menu slot 3", passedTests);

    fullMenuText = "Menu Title\n"
                   "1 Burger\n"
                   "2 Bacon Sandwich\n"
                   "3 Soda\n"
                   " ----------------\n"
                   "99 Exit\n";
    stdInput << "1\nG\n2\n3\n5\n99\n";

    returnValue = menu->Run();
    Test(returnValue == 0, "Selected Option 1", passedTests);
    Test(stdOutput.str() == fullMenuText, "Full Menu Text Correct", passedTests);
    stdOutput.str("");
    returnValue = menu->Run();
    Test(returnValue == INPUT_ERROR, "Returned INPUT_ERROR correctly", passedTests);
    Test(stdError.str() == "An Error Message\n", "Error message sent to Error Stream", passedTests);
    stdError.str("") ;
    returnValue = menu->Run();
    Test(returnValue == 1, "Selected Option 2", passedTests);
    returnValue = menu->Run();
    Test(returnValue == 2, "Selected Option 3", passedTests);
    returnValue = menu->Run();
    Test(returnValue == INVALID_INPUT, "Returned INVALID_INPUT correctly", passedTests);
    Test(stdError.str() == "An Invalid Option Error Message\n", "Error message sent to Error Stream", passedTests);
    stdError.str("");
    returnValue = menu->Run();
    Test(returnValue == EXIT, "Exit Menu", passedTests);

    delete menu;
    stdError.str("");
    stdOutput.str("");
    stdInput.str("");

    // Testing with CHAR options
    menu = new Menu(6, stdOutput, stdInput, stdError);

    menu->SetErrorMessage("Another Error Message");
    menu->SetInvalidOption("Not an Option Error Message");
    menu->SetInputType(CHAR);
    menu->SetTitle("This is Another Menu");
    Test(menu->GetErrorMessage() == "Another Error Message", "Error Message Set", passedTests);
    Test(menu->GetInvalidOption() == "Not an Option Error Message", "Invalid Option Set", passedTests);
    Test(menu->GetInputType() == CHAR, "Input Type Set", passedTests);
    Test(menu->GetTitle() == "This is Another Menu", "Menu Title Set", passedTests);

    // Adding menu options
    returnValue = menu->AddMenuOption(0, "a", "Red");
    Test(returnValue == 0, "Added Menu option to menu slot 0", passedTests);
    returnValue = menu->AddMenuOption(1, "b", "Grin");
    Test(returnValue == 1, "Added Menu option to menu slot 1", passedTests);
    returnValue = menu->AddMenuOption(1, "b", "Green");
    Test(returnValue == OVERWROTE_OPTION, "Overwrote Menu option in menu slot 1", passedTests);
    returnValue = menu->AddMenuOption(2, "c", "Blue");
    Test(returnValue == 2, "Added Menu option to menu slot 2", passedTests);
    returnValue = menu->AddSeparator(3);
    Test(returnValue == 3, "Added Separator to menu slot 3", passedTests);
    returnValue = menu->AddMenuOption(4, "x", "Black");
    Test(returnValue == 4, "Added Menu option to menu slot 4", passedTests);
    returnValue = menu->AddMenuOption(5, "y", "White");
    Test(returnValue == 5, "Added Menu option to menu slot 5", passedTests);

    fullMenuText = "This is Another Menu\n"
                   "a Red\n"
                   "b Green\n"
                   "c Blue\n"
                   " -------\n"
                   "x Black\n"
                   "y White\n"
                   "Type E to Exit\n";
    stdInput << "a\nx\nt\ne\nE\n";

    returnValue = menu->Run();
    Test(returnValue == 0, "Selected Option (a)", passedTests);
    Test(stdOutput.str() == fullMenuText, "Full Menu Text Correct", passedTests);
    stdOutput.str("");
    returnValue = menu->Run();
    Test(returnValue == 4, "Selected Option (x)", passedTests);
    stdOutput.str("");
    returnValue = menu->Run();
    Test(returnValue == INVALID_INPUT, "Returned INVALID_INPUT correctly (t)", passedTests);
    Test(stdError.str() == "Not an Option Error Message\n", "Error message sent to Error Stream", passedTests);
    stdError.str("");
    returnValue = menu->Run();
    Test(returnValue == INVALID_INPUT, "Returned INVALID_INPUT correctly (e)", passedTests);
    Test(stdError.str() == "Not an Option Error Message\n", "Error message sent to Error Stream", passedTests);
    stdError.str("");
    returnValue = menu->Run();
    Test(returnValue == EXIT, "Exit Menu", passedTests);

    delete menu;
    stdError.str("");
    stdOutput.str("");
    stdInput.str("");

    // Testing with STRING options
    menu = new Menu(4, stdOutput, stdInput, stdError);

    menu->SetErrorMessage("String Error Message");
    menu->SetInvalidOption("Not a String Error Message");
    menu->SetInputType(STRING);
    menu->SetTitle("The Last Menu");
    Test(menu->GetErrorMessage() == "String Error Message", "Error Message Set", passedTests);
    Test(menu->GetInvalidOption() == "Not a String Error Message", "Invalid Option Set", passedTests);
    Test(menu->GetInputType() == STRING, "Input Type Set", passedTests);
    Test(menu->GetTitle() == "The Last Menu", "Menu Title Set", passedTests);

    // Adding menu options
    returnValue = menu->AddMenuOption(0, "Alpha", "A");
    Test(returnValue == 0, "Added Menu option to menu slot 0", passedTests);
    returnValue = menu->AddMenuOption(1, "Brav0", "B");
    Test(returnValue == 1, "Added Menu option to menu slot 1", passedTests);
    returnValue = menu->AddMenuOption(1, "Bravo", "B");
    Test(returnValue == OVERWROTE_OPTION, "Overwrote Menu option in menu slot 1", passedTests);
    returnValue = menu->AddMenuOption(2, "Charlie", "C");
    Test(returnValue == 2, "Added Menu option to menu slot 2", passedTests);
    returnValue = menu->AddMenuOption(3, "Delta", "D");
    Test(returnValue == 3, "Added Menu option to menu slot 3", passedTests);

    fullMenuText = "The Last Menu\n"
                   "Alpha A\n"
                   "Bravo B\n"
                   "Charlie C\n"
                   "Delta D\n"
                   "Type E to Exit\n";
    stdInput << "alpha\nAlpha\nCharlie\nE\n";

    returnValue = menu->Run();
    Test(stdOutput.str() == fullMenuText, "Full Menu Text Correct", passedTests);
    stdOutput.str("");
    Test(returnValue == INVALID_INPUT, "Returned INVALID_INPUT correctly (alpha)", passedTests);
    Test(stdError.str() == "Not a String Error Message\n", "Error message sent to Error Stream", passedTests);
    stdError.str("");
    returnValue = menu->Run();
    Test(returnValue == 0, "Selected Option (Alpha)", passedTests);
    returnValue = menu->Run();
    Test(returnValue == 2, "Selected Option (Charlie)", passedTests);
    stdOutput.str("");
    returnValue = menu->Run();
    Test(returnValue == EXIT, "Exit Menu", passedTests);
    delete menu;


    return 0;
}

void Test(bool condition, const char* message, unsigned int& passedTests){
    if (condition){
        cout << "TEST PASSED (" << left << setw(40) << message << ") Total Passed: " << ++passedTests << endl;
    }else{
        cout << "TEST FAILED (" << message << ")" << endl;
    }
}
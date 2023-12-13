# A Menu Class

## Introduction
There are times that software developers create libraries to help them with future projects. In this assignment you will create a `Menu` class that will serve as a library. This means that you will provide a class that another program could use. For this particular case your class will help other programmers (and yourself!) to be able to easily create menus for their programs. As you create this library notice that you don't know what menu options the user will decide to use, or even if the programmer wants their user to input numbers or letters for their menu.

## Learning Goals
The goals of the Lab are for you to practice:
* Creating classes
* Using Dynamically Allocated arrays of Objects
* Using *test scripts* with your code 

## The Target
The idea of this lab is that you create a class named `Menu`. This class will help the users create custom menus for their applications. The following code shows an example of a program using the `Menu` class:
```cpp
    Menu menu(5); // Instantiate Menu
    // Configure the Menu
    menu.SetTitle("Bookstore Menu");
    menu.SetInputType(INT);
    menu.SetErrorMessage("- - > Unrecognized Input < - -");
    menu.SetInvalidOption("- - > Please Input One of the Given Choices < - -");
    // Add the Options
    menu.AddMenuOption(0, "1", "Add book");
    menu.AddMenuOption(1, "2", "List Books");
    menu.AddSeparator(2); // This separator will be placed in #2 slot (third position)
    menu.AddMenuOption(3, "3", "Update Book");
    menu.AddMenuOption(4, "4", "Remove Book");

    while ((selected = menu.Run()) != EXIT){
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
                cout << "The Bible" << endl;
                cout << "Tom Sawyer" << endl;
                cout << "Moby Dick" << endl;
                cout << endl << endl;
                break;
            case 2: // This can't happen, since slot 2 is taken by the separator!
                cout << "Should not happen!" << endl;
                break;
            case 3:
                cout << "Update a book" << endl;
                cout << "The Bible" << endl;
                cout << "Tom Sawyer" << endl;
                cout << "Moby Dick" << endl;
                cout << endl << endl;
                cout << "What book you want to modify: " << endl;
                cout << " ... " << endl;
                break;
            case 4:
                cout << "Remove a book" << endl;
                cout << "The Bible" << endl;
                cout << "Tom Sawyer" << endl;
                cout << "Moby Dick" << endl;
                cout << endl << endl;
                cout << "What book you want to remove: " << endl;
                cout << " ... " << endl;
                break;
        }
    }

```

Your implementation of the class `Menu` will have a constructor that will need at least one parameter to indicate how many menu options the menu will have. In the example it can be seen that the create menu is going to have five menu options.
After creating the menu, you can see a sequence of operations to initially set up the menu:
1. `menu.SetTitle("Bookstore Menu");` this statement sets the title of the menu.
2. `menu.SetInputType(INT);` this statement indicates that the options of the menu are going to be integers. This is required since your menu is going to allow the user to set the options to be single characters, strings or integers. If the user wants to set the options as strings, the user will need to set the input type to `STRING`, if the user wants to use single characters, then the input type will be `CHAR`.
3. `menu.SetErrorMessage("- - > Unrecognized Input < - -");` this statement sets the **error** message when the user inputs something that is not allowed, for instance inputting a string when a number is expected.
4. `menu.SetInvalidOption("- - > Please Input One of the Given Choices < - -");` this statement sets the message that the menu will output when the user inputs an option that is not one of the available options. For example, if the menu has options 1, 2 or 3; and the user inputs 4 then `- - > Unrecognized Input < - -` is going to be sent as an **error** to the screen.

Once the menu is set up, the user will need to add the actual options of the menu. In general, it works like this:
> `menu.AddMenuOption(slot, option-text, menu-text);`
- The first parameter indicates in what *slot* you want to add the options. Think of the slots as indices in an array (they are actually the indices of the array `_menuElements`!). 
- The second parameter establishes what the user will need to input when selecting this menu item.
- The third parameter sets the text that is going to be displayed as the actual menu item.

In the example you can see `menu.AddMenuOption(0, "1", "Add book");` this adds a menu option to the slot 0, the user will need to input 1 to select that choice, and the text for that menu will be **Add Book**. The user will need to remember that this menu option was added to slot 0, since this is the value that `menu.Run()` will return when the user selects this option.

> `menu.AddSeparator(2);`

If the user wants to add a "separator" between menu options, the user can add a separator in the desired slot. In this example the separator is added to slot 2.

Once everything is set, the general menu configurations and the menu options, the user can go and use the menu. This is done by calling the method `Run`. This method will display the title of the menu, each one of the options and separators, it will add an exit option (99 Exit for input type INT, and Type E to Exit for CHAR and STRING input types). The `Run` method will return on the following:
- If the user types an option available, the method returns the slot of the selected option by the user
- If the user types an option that is not offered (i.e. types 5 when the menu has only 1,2,3,4), the method will return `INVALID_INPUT` (this constant is declared in `menu.h`).
- If the user types a string where a number is expected, or more than one character when a single character is expected, the method will return `INPUT_ERROR` (this constant is declared in `menu.h`). Look at this [page](https://stackoverflow.com/questions/10349857/how-to-handle-wrong-data-type-input) for some reference on this
- If the user types the exit option (99 for a menu that has input type INT, or E for the other input types), then the method will return `EXIT`.

Note that `while ((selected = menu.Run()) != EXIT)` basically is saying:
1. Call the method `menu.Run()`, assign the return value to `selected`
2. Repeat the loop while `selected` is not `EXIT`

Inside the `while` the user can place a `switch` block that will check which of the options the user selected. Remember that these options are the slot positions! For instance, it is not possible for the user to select the separator, that is why `case 2:` says: "Should not happen!".

## What you are given

This repository contains some starter code for you to work with. The following table describes each of the files.

|Filename | Description                                                                                                                                                                                                                                                                                                                                                                                  |
|-------- |----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| `menu.h` | This file contains the declaration of the class `Menu` you can add methods, but you cannot change the given methods.                                                                                                                                                                                                                                                                         |
| `menu.cpp` | This file contains de implementation of the methods of the `Menu` class. Inside this class you will find each of the methods commented for you to understand what each one of them do.                                                                                                                                                                                                       |
| `menu_element.h` | This file contains the declaration of the class `MenuElement`, this class represents a single item of the menu.                                                                                                                                                                                                                                                                              |
| `menu_element.cpp` | This file has the implementation of the methods of the `MenuElement` class. Some of the methods have been implemented for you, some of them you will need to implement. You may add methods but you cannot change the methods that are given.                                                                                                                                                |
|`tests.cpp` | This file contains the 'default' `main` of your project. The *test script* is located in this file. **You cannot modify this file in any way**. When your program is completed this main will test all of the functionalities of the `MenuElement` and `Menu` class. If you pass all 70 tests it means that your classes are functioning as requested.                                       |
| `main.cpp` | This file containes an additional `main`. This `main` has code for you to test your menu, some code is provided, but you can change it as you see fit. To build your program to use this main you will need to edit your `CMakeLists.txt` file, exchange the `tests.cpp` for `main.cpp` and then reload the `CMakeLists.txt`, when you run your program it will run the `main` on `main.cpp` |
|`extracredit.cpp` | This file contains an additional `main`. This `main` is empty and it contains the instructions if you want to do the extra credit. If you want to test the extra credit, you will need to change `main.cpp` or `tests.cpp` from the `CMakeLists.txt` file.                                                                                                                                   |

## A Possible Worklist
1. Implement the methods of the `MenuElement` class.
2. Run the program with `tests.cpp`, make sure that it passes all the `MenuElement` tests
3. Start working on the `Menu` class
   1. Constructor
   2. Destructor
   3. Accessors (getters) and Mutators (setters)
   4. The `Run` method.
      1. First implement the case that the user sets the input type to INT, test this
      2. Then implement the other input types

> NOTE: Remember that inside the `Run` method you will only use `_output` to write to the screen, `_input` to read from the keyboard and `stdError` to send error messages to the screen. **DO NOT** use `cout`, `cin`, or `cerr` inside this method!

## Testing your code
Your code is going to be graded based on the results of running your program using the `main` found in `tests.cpp`. You can check the tests, and work with the methods that you need to pass each of the tests. For instance:
```cpp
//  Testing Default Constructor
    element = new MenuElement();
    Test(element->IsSeparator() == false, "Menu Element Separator", passedTests);
    Test(element->GetSelectionOption() == "", "Menu Selection Option Empty", passedTests);
    Test(element->GetMenuText() == "", "Menu Text Empty", passedTests);
    Test(element->ToString() == " ", "Menu Element ToString", passedTests);
    Test(element->MenuElementWidth() == 1, "Menu Element Width", passedTests);
    delete element;

```
The very first tests check that the default constructor of class `MenuElement` is working correctly, for this you will need to correctly code:
- `MenuElement::MenuElement()`
- `bool MenuElement::IsSeparator()`
- `string MenuElement::GetSelectionOption()`
- `string MenuElement::GetMenuText()`
- `string MenuElement::ToString()`
- `string MenuElement::MenuElementWidth()`

Once you are done with those methods, you can test using `tests.cpp` and if they are correct you will pass the first 5 tests. Then you move to work on the next set, and so on. The description of each of the methods is included in the class implementation files.

## Changing the main of your project

Initially your `CMakeLists.txt` file looks like this:
```cmake
cmake_minimum_required(VERSION 3.20)
project(Menu_Assignment)

set(CMAKE_CXX_STANDARD 14)

add_executable(Menu_Assignment tests.cpp menu.cpp menu.h menu_element.cpp menu_element.h)
```

Notice that in the last line the file `tests.cpp` is included. If you want your program to run your own `main.cpp` then you would need to change `tests.cpp` for `main.cpp`. If you want your program to run your `extracredit.cpp` then you would need to change `tests.cpp` for `extracredit.cpp`. Your `add_executable` line should **always** include: `menu.cpp`, `menu.h`, `menu_element.h`, `menu_element.cpp`.

## Grading Rubric
Your lab will be graded according to the test script (`tests.cpp`). The script output when your lab is complete should look as follows:
```
TEST PASSED (Menu Element Separator                  ) Total Passed: 1
TEST PASSED (Menu Selection Option Empty             ) Total Passed: 2
TEST PASSED (Menu Text Empty                         ) Total Passed: 3
TEST PASSED (Menu Element ToString                   ) Total Passed: 4
TEST PASSED (Menu Element Width                      ) Total Passed: 5
TEST PASSED (Menu Element Separator                  ) Total Passed: 6
TEST PASSED (Menu Selection Option Empty             ) Total Passed: 7
TEST PASSED (Menu Text **********                    ) Total Passed: 8
TEST PASSED (Menu Element ToString                   ) Total Passed: 9
TEST PASSED (Menu Element Width                      ) Total Passed: 10
TEST PASSED (Menu Element Separator                  ) Total Passed: 11
TEST PASSED (Menu Selection Option 'A'               ) Total Passed: 12
TEST PASSED (Menu Text The Alpha Choice              ) Total Passed: 13
TEST PASSED (Menu Element ToString                   ) Total Passed: 14
TEST PASSED (Menu Element Width                      ) Total Passed: 15
TEST PASSED (Menu Element Separator                  ) Total Passed: 16
TEST PASSED (SetMenuElement unsets IsSeparator       ) Total Passed: 17
TEST PASSED (SetMenuElement successful               ) Total Passed: 18
TEST PASSED (Error Message Set                       ) Total Passed: 19
TEST PASSED (Invalid Option Set                      ) Total Passed: 20
TEST PASSED (Input Type Set                          ) Total Passed: 21
TEST PASSED (Menu Title Set                          ) Total Passed: 22
TEST PASSED (Added Menu option to menu slot 0        ) Total Passed: 23
TEST PASSED (Added Menu option to menu slot 1        ) Total Passed: 24
TEST PASSED (Overwrote Menu option in menu slot 1    ) Total Passed: 25
TEST PASSED (Added Menu option to menu slot 2        ) Total Passed: 26
TEST PASSED (Added Separator to menu slot 3          ) Total Passed: 27
TEST PASSED (Selected Option 1                       ) Total Passed: 28
TEST PASSED (Full Menu Text Correct                  ) Total Passed: 29
TEST PASSED (Returned INPUT_ERROR correctly          ) Total Passed: 30
TEST PASSED (Error message sent to Error Stream      ) Total Passed: 31
TEST PASSED (Selected Option 2                       ) Total Passed: 32
TEST PASSED (Selected Option 3                       ) Total Passed: 33
TEST PASSED (Returned INVALID_INPUT correctly        ) Total Passed: 34
TEST PASSED (Error message sent to Error Stream      ) Total Passed: 35
TEST PASSED (Exit Menu                               ) Total Passed: 36
TEST PASSED (Error Message Set                       ) Total Passed: 37
TEST PASSED (Invalid Option Set                      ) Total Passed: 38
TEST PASSED (Input Type Set                          ) Total Passed: 39
TEST PASSED (Menu Title Set                          ) Total Passed: 40
TEST PASSED (Added Menu option to menu slot 0        ) Total Passed: 41
TEST PASSED (Added Menu option to menu slot 1        ) Total Passed: 42
TEST PASSED (Overwrote Menu option in menu slot 1    ) Total Passed: 43
TEST PASSED (Added Menu option to menu slot 2        ) Total Passed: 44
TEST PASSED (Added Separator to menu slot 3          ) Total Passed: 45
TEST PASSED (Added Menu option to menu slot 4        ) Total Passed: 46
TEST PASSED (Added Menu option to menu slot 5        ) Total Passed: 47
TEST PASSED (Selected Option (a)                     ) Total Passed: 48
TEST PASSED (Full Menu Text Correct                  ) Total Passed: 49
TEST PASSED (Selected Option (x)                     ) Total Passed: 50
TEST PASSED (Returned INVALID_INPUT correctly (t)    ) Total Passed: 51
TEST PASSED (Error message sent to Error Stream      ) Total Passed: 52
TEST PASSED (Returned INVALID_INPUT correctly (e)    ) Total Passed: 53
TEST PASSED (Error message sent to Error Stream      ) Total Passed: 54
TEST PASSED (Exit Menu                               ) Total Passed: 55
TEST PASSED (Error Message Set                       ) Total Passed: 56
TEST PASSED (Invalid Option Set                      ) Total Passed: 57
TEST PASSED (Input Type Set                          ) Total Passed: 58
TEST PASSED (Menu Title Set                          ) Total Passed: 59
TEST PASSED (Added Menu option to menu slot 0        ) Total Passed: 60
TEST PASSED (Added Menu option to menu slot 1        ) Total Passed: 61
TEST PASSED (Overwrote Menu option in menu slot 1    ) Total Passed: 62
TEST PASSED (Added Menu option to menu slot 2        ) Total Passed: 63
TEST PASSED (Added Menu option to menu slot 3        ) Total Passed: 64
TEST PASSED (Full Menu Text Correct                  ) Total Passed: 65
TEST PASSED (Returned INVALID_INPUT correctly (alpha)) Total Passed: 66
TEST PASSED (Error message sent to Error Stream      ) Total Passed: 67
TEST PASSED (Selected Option (Alpha)                 ) Total Passed: 68
TEST PASSED (Selected Option (Charlie)               ) Total Passed: 69
TEST PASSED (Exit Menu                               ) Total Passed: 70
```

There are 70 tests that your code needs to pass. If a test is failed, then the message will appear there and that test will not be counted towards the total test passed. Your "gross" grade will be the number of tests you passed divided by 70 times 100. 

<img src="https://render.githubusercontent.com/render/math?math=grade=\frac{Tests Passed}{70}*100">

Remember that you are expected to follow the good programming practices and course coding conventions. See the [Deductions](Deductions) section for details on the issues that may reduce your gross grade.

### Deductions

* For each infraction on good programming practices there will be a deduction of 5 points
* If the program has a runtime error (the program crashes) there will be a deduction of 10 points
* If the program does not have comment headers there will be a deduction of 10 points
* If the program does not have comments on functions and appropriate additional comments there will be a deduction of 5 points
* If the program does not follow instructions, for instance if you did not implement any of the requested functions, there will be a deduction of 5 points per ignored instruction
* If the program does not compile, the grade will be zero.

### Grading yourself

It is possible, and encouraged that you grade your own assignment. The steps to grade your assignment:
1. Make sure your code compile, if it doesn't you will not receive credit for this assignment.
2. Run the program using the `tests.cpp` as main
3. Calculate your gross grade using the formula provided above
4. Check that your code follows the programming guidelines
   1. Is your code following the identifier naming conventions?
   2. Is your code appropriately indented?
   3. Does your code avoid using global variables?
   4. Does your code use a consistent style of {}?
   5. Are all your identifiers using meaningful names?
   6. Are all non-primitive type parameters passed by reference and const when needed?
   7. Is your code clean?
   8. Does your code avoid using `cout` or `cin` inside functions or methods that are not supposed to have console input or output?
   9. Does your program run smoothly? (Your code doesn't crash)
   10. Does your code have all the header comments?
   11. If your answer to all the above questions is yes, then you are unlikely to lose any points and your assignment final grade should be very close to the gross grade.



A warning: hard-coding your output will result in a zero grade!

## Academic Integrity

This programming assignment is to be done on an individual basis. At the same time, it is understood that learning from your peers is valid, and you are encouraged to talk among yourselves about programming in general and current assignments in particular. Keep in mind, however, that each individual student must do the work in order to learn.

Hence, the following guidelines are established:

* Feel free to discuss any and all programming assignments but do not allow other students to look at or copy your code. Do not give any student an electronic or printed copy of any program you write for this class.
* Gaining the ability to properly analyze common programming errors is an important experience. Do not deprive a fellow student of his/her opportunity to practice problem solving: control the urge to show them what to do by writing the code for them.
* If you’ve given the assignment a fair effort and still need help, see the instructor or a lab assistant.
* If there is any evidence that a program or other written assignment was copied from another student (or from any source), neither student will receive any credit for it. This rule will be enforced.
* Protect yourself: Handle throw-away program listings carefully.
* Remember to read the Academic Integrity guidelines provided in the class syllabus.


## Examples of Using the Menu Class

### Dummy Example #1
```cpp
    Menu menu1(2);
    menu1.SetTitle("A Menu");
    menu1.SetInputType(INT);
    menu1.SetErrorMessage("Your input was not recognized, perhaps input a string where a number is expected");
    menu1.SetInvalidOption("Your input is not one of the given choices");
    menu1.AddMenuOption(0, "1", "first");
    menu1.AddMenuOption(1, "2", "second");
    while ((selected = menu1.Run()) != EXIT){
        switch (selected) {
            case INVALID_INPUT: // You can add additional error message
                break;
            case INPUT_ERROR: // You can add additional error message
                break;
            case 0:
                cout << "User Selected the first choice... do something" << endl;
                break;
            case 1:
                cout << "User Selected the second choice... second plate, so sad" << endl;
                break;
        }
    }

```

Sample Run:
```
A Menu
1 first
2 second
99 Exit
1
User Selected the first choice... do something
A Menu
1 first
2 second
99 Exit
a
Your input was not recognized, perhaps input a string where a number is expected
A Menu
1 first
2 second
99 Exit
99
```

### Dummy Example #2
```cpp
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

```

Sample Run:
```
A Second Menu
(Alpha) This is the Alpha Option

(Sigma) This is the Sigma Option
Type E to Exit
Sigma
Sigma is the name of the summation
A Second Menu
(Alpha) This is the Alpha Option

(Sigma) This is the Sigma Option
Type E to Exit
E
```

### Dummy Example #3
```cpp
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

```

Sample Run:
```
A Third Menu
(a) A for Apple
(b) B for Book
(c) C for... cube?
Type E to Exit
b
Book is an object
A Third Menu
(a) A for Apple
(b) B for Book
(c) C for... cube?
Type E to Exit
E
```


### A Bookstore Example
```cpp
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
                cout << "The Bible" << endl;
                cout << "Tom Sawyer" << endl;
                cout << "Moby Dick" << endl;
                cout << endl << endl;
                break;
            case 2:
                cout << "Should not happen!" << endl;
                break;
            case 3:
                cout << "Update a book" << endl;
                cout << "The Bible" << endl;
                cout << "Tom Sawyer" << endl;
                cout << "Moby Dick" << endl;
                cout << endl << endl;
                cout << "What book you want to modify: " << endl;
                cout << " ... " << endl;
                break;
            case 4:
                cout << "Remove a book" << endl;
                cout << "The Bible" << endl;
                cout << "Tom Sawyer" << endl;
                cout << "Moby Dick" << endl;
                cout << endl << endl;
                cout << "What book you want to remove: " << endl;
                cout << " ... " << endl;
                break;
        }
    }

```

Sample Run:
```
Bookstore Menu
1 Add book
2 List Books
 -------------
3 Update Book
4 Remove Book
99 Exit
1
Add a new Book
Input the name:
 ...
Bookstore Menu
1 Add book
2 List Books
 -------------
3 Update Book
4 Remove Book
99 Exit
2
Listing all books
The Bible
Tom Sawyer
Moby Dick

Bookstore Menu
1 Add book
2 List Books
 -------------
3 Update Book
4 Remove Book
99 Exit
99
```


## Extra Credit

As an extra credit activity create a program inside the file `extracredit.cpp`. In this program you will use the `Menu` class that you just created. You will have a menu that will have the following options:

```
Working with Arrays
1 Set Size of the Array
 -----------------------
2 Add Number to Array
3 List the Numbers
4 Remove a Number
 -----------------------
5 Calculate Average
99 Exit

```
### Description of the Options

| Menu Option | Description |
| ----------- | ----------- |
| Set Size of Array | When the user selects this option, the user will need to input the number of elements that they want to use for the program |
| Separator | Add a separator between setting up and the list operations |
| Add Number to Array | Checks if the array is already full, if that's the case it will message that the array is full, if not it will read a number from the keyboard and add it to the end of the array. |
| List the Numbers | Outputs to screen all the numbers that have been added to the array. |
| Remove a Number | It will show the numbers with their respective position. The user will input the position of the number that they want to remove. If the position is valid, then the program will remove the number. If the number is not in the last position, remember to push the numbers to fill that empty position. |
| Separator | Add a separator between the calculation option |
| Calculate Average | Traverses the array of numbers, calculates the average and outputs the average on the screen. |

Below there is a possible output of the program, notice the following things:
* The program does not crash if the input is not a number
* Options 2, 3, 4, and 5 cannot be executed until the array has been created
* If _after_ creating the array (option 1), the user decides to select option 1 again, the previous array will be lost.
* The output is "nicely" formatted.

> IMPORTANT! You may receive extra credit ONLY if you passed the tests.

### Grading the Extra Credit

* The program doesn't allow options 2,3,4,5 unless the array is created (required)
* The program adds numbers and shows them when listed: 20
* The program removes numbers and shows them removed when listed: 20
* The program calculates the average correctly: 10
* If your program crashes you may not get any extra credit.

### Sample Expected Output:
```
Working with Arrays
1 Set Size of the Array
 -----------------------
2 Add Number to Array
3 List the Numbers
4 Remove a Number
 -----------------------
5 Calculate Average
99 Exit
2
Need to create array first!

Working with Arrays
1 Set Size of the Array
 -----------------------
2 Add Number to Array
3 List the Numbers
4 Remove a Number
 -----------------------
5 Calculate Average
99 Exit
3
Need to create array first!

Working with Arrays
1 Set Size of the Array
 -----------------------
2 Add Number to Array
3 List the Numbers
4 Remove a Number
 -----------------------
5 Calculate Average
99 Exit
4
Need to create array first!

Working with Arrays
1 Set Size of the Array
 -----------------------
2 Add Number to Array
3 List the Numbers
4 Remove a Number
 -----------------------
5 Calculate Average
99 Exit
5
Need to create array first!

Working with Arrays
1 Set Size of the Array
 -----------------------
2 Add Number to Array
3 List the Numbers
4 Remove a Number
 -----------------------
5 Calculate Average
99 Exit
a
- - > Unrecognized Input < - -
Working with Arrays
1 Set Size of the Array
 -----------------------
2 Add Number to Array
3 List the Numbers
4 Remove a Number
 -----------------------
5 Calculate Average
99 Exit
6
- - > Please Input One of the Given Choices < - -
Working with Arrays
1 Set Size of the Array
 -----------------------
2 Add Number to Array
3 List the Numbers
4 Remove a Number
 -----------------------
5 Calculate Average
99 Exit
1
Please input the maximum capacity of the array: 4
Array Created Successfully

Working with Arrays
1 Set Size of the Array
 -----------------------
2 Add Number to Array
3 List the Numbers
4 Remove a Number
 -----------------------
5 Calculate Average
99 Exit
2
Adding Number to Array
Please input the number you want to add: 1.5
Number 1.500000 Added to Position 0 Successfully

Working with Arrays
1 Set Size of the Array
 -----------------------
2 Add Number to Array
3 List the Numbers
4 Remove a Number
 -----------------------
5 Calculate Average
99 Exit
3
Listing Numbers
   0  1.500000


Working with Arrays
1 Set Size of the Array
 -----------------------
2 Add Number to Array
3 List the Numbers
4 Remove a Number
 -----------------------
5 Calculate Average
99 Exit
2
Adding Number to Array
Please input the number you want to add: 1.4142
Number 1.414200 Added to Position 1 Successfully

Working with Arrays
1 Set Size of the Array
 -----------------------
2 Add Number to Array
3 List the Numbers
4 Remove a Number
 -----------------------
5 Calculate Average
99 Exit
3
Listing Numbers
   0  1.500000
   1  1.414200


Working with Arrays
1 Set Size of the Array
 -----------------------
2 Add Number to Array
3 List the Numbers
4 Remove a Number
 -----------------------
5 Calculate Average
99 Exit
2
Adding Number to Array
Please input the number you want to add: 3.14159
Number 3.141590 Added to Position 2 Successfully

Working with Arrays
1 Set Size of the Array
 -----------------------
2 Add Number to Array
3 List the Numbers
4 Remove a Number
 -----------------------
5 Calculate Average
99 Exit
3
Listing Numbers
   0  1.500000
   1  1.414200
   2  3.141590


Working with Arrays
1 Set Size of the Array
 -----------------------
2 Add Number to Array
3 List the Numbers
4 Remove a Number
 -----------------------
5 Calculate Average
99 Exit
2
Adding Number to Array
Please input the number you want to add: 2.7172
Number 2.717200 Added to Position 3 Successfully

Working with Arrays
1 Set Size of the Array
 -----------------------
2 Add Number to Array
3 List the Numbers
4 Remove a Number
 -----------------------
5 Calculate Average
99 Exit
3
Listing Numbers
   0  1.500000
   1  1.414200
   2  3.141590
   3  2.717200


Working with Arrays
1 Set Size of the Array
 -----------------------
2 Add Number to Array
3 List the Numbers
4 Remove a Number
 -----------------------
5 Calculate Average
99 Exit
2
Adding Number to Array
The array is full
Working with Arrays
1 Set Size of the Array
 -----------------------
2 Add Number to Array
3 List the Numbers
4 Remove a Number
 -----------------------
5 Calculate Average
99 Exit
5
The average is: 2.193248

Working with Arrays
1 Set Size of the Array
 -----------------------
2 Add Number to Array
3 List the Numbers
4 Remove a Number
 -----------------------
5 Calculate Average
99 Exit
1
The created array will be lost
Please input the maximum capacity of the array: 2
Array Created Successfully

Working with Arrays
1 Set Size of the Array
 -----------------------
2 Add Number to Array
3 List the Numbers
4 Remove a Number
 -----------------------
5 Calculate Average
99 Exit
3
Listing Numbers


Working with Arrays
1 Set Size of the Array
 -----------------------
2 Add Number to Array
3 List the Numbers
4 Remove a Number
 -----------------------
5 Calculate Average
99 Exit
2
Adding Number to Array
Please input the number you want to add: 4
Number 4.000000 Added to Position 0 Successfully

Working with Arrays
1 Set Size of the Array
 -----------------------
2 Add Number to Array
3 List the Numbers
4 Remove a Number
 -----------------------
5 Calculate Average
99 Exit
2
Adding Number to Array
Please input the number you want to add: 12
Number 12.000000 Added to Position 1 Successfully

Working with Arrays
1 Set Size of the Array
 -----------------------
2 Add Number to Array
3 List the Numbers
4 Remove a Number
 -----------------------
5 Calculate Average
99 Exit
3
Listing Numbers
   0  4.000000
   1 12.000000


Working with Arrays
1 Set Size of the Array
 -----------------------
2 Add Number to Array
3 List the Numbers
4 Remove a Number
 -----------------------
5 Calculate Average
99 Exit
5
The average is: 8.000000

Working with Arrays
1 Set Size of the Array
 -----------------------
2 Add Number to Array
3 List the Numbers
4 Remove a Number
 -----------------------
5 Calculate Average
99 Exit
4
Remove a Number
   0  4.000000
   1 12.000000
What is the position where you want to remove a number: 3
Invalid Position
Working with Arrays
1 Set Size of the Array
 -----------------------
2 Add Number to Array
3 List the Numbers
4 Remove a Number
 -----------------------
5 Calculate Average
99 Exit
4
Remove a Number
   0  4.000000
   1 12.000000
What is the position where you want to remove a number: 0
Number in Position 0 Removed Successfully

Working with Arrays
1 Set Size of the Array
 -----------------------
2 Add Number to Array
3 List the Numbers
4 Remove a Number
 -----------------------
5 Calculate Average
99 Exit
3
Listing Numbers
   0 12.000000


Working with Arrays
1 Set Size of the Array
 -----------------------
2 Add Number to Array
3 List the Numbers
4 Remove a Number
 -----------------------
5 Calculate Average
99 Exit
99
Finished the Program... Goodbye


```
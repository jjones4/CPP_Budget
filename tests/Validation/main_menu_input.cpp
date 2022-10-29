/*
 * Name:       main_menu_input.cpp
 *
 * Purpose:    Contains functions for testing the different
 *             steps in validating main menu input.
 *
 *             1. Check if the input is an integer
 *             2. Check if the input is within the acceptable
 *                range for the main menu's input
 *             3. Display test results of input data coming from
 *                an infile called main_menu_input_infile
 *
 * Note:       I have included an "infile" with some test data.
 *             After compiling the test program, run the following
 *             command with the infile that is provided for
 *             testing:
 *             
 *                main_menu_input <main_menu_input_infile
 *
 * Author:     jjones4
 *
 * Copyright (c) 2022 Jerad Jones
 * This file is part of CPP_Budget.  CPP_Budget may be freely
 * distributed under the MIT license.  For all details and
 * documentation, see https://github.com/jjones4/CPP_Budget
 *
 */

#include <iostream>
#include <string>

#define MAIN_MENU_INPUT_MIN 1
#define MAIN_MENU_INPUT_MAX 5

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::stoi;

void display_results_of_test(string main_menu_input);
bool is_non_negative_integer(const string s);
bool is_within_main_menu_range(const string n);

int main()
{
   string main_menu_input;

   // If there is data to process
   if(getline(cin, main_menu_input))
   {
      display_results_of_test(main_menu_input);

      // If there is data to process, get the rest of it
      while(getline(cin, main_menu_input))
      {
         display_results_of_test(main_menu_input);
      }
   }
   else
   {
      cout << "No data to process." << endl;
      return -1;
   }

   return 0;
}

void display_results_of_test(string main_menu_input)
{
   if(!is_non_negative_integer(main_menu_input))
   {
      cout << "Not a positive integer or zero --> "
           << main_menu_input
           << endl;

      return;
   }

   if(!is_within_main_menu_range(main_menu_input))
   {
      cout << "              Not within range --> "
           << main_menu_input
           << endl;

      return;
   }
 
   if(is_non_negative_integer(main_menu_input) &&
      is_within_main_menu_range(main_menu_input))
   {
      cout << "                   Test passes --> "
           << main_menu_input
           << endl;

      return;
   }
}

// Will be shared by three different functions that validate input
// 1) is_valid_main_menu_option() - for the main menu
// 2) is_valid_edit_menu_option() - for when the user is chosing
//    which part of the budget transaction they want to edit
// 3) is_valid_date_inupt() - for validating individual parts of the date
bool is_non_negative_integer(const string s)
{
   // Empty line is integer; handle this specific case
   if(s == "")
   {
      return false;
   }

   for(unsigned int i = 0; i < s.length(); i++)
   {
      if(isdigit(s[i]) == false)
      {
         return false;
      }
   }

   return true;
}

bool is_within_main_menu_range(const string s)
{
   if(stoi(s) >= MAIN_MENU_INPUT_MIN && stoi(s) <= MAIN_MENU_INPUT_MAX)
   {
      return true;
   }
   else
   {
      return false;
   }
}

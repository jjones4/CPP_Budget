/*
 * Name:       amount_input.cpp
 *
 * Purpose:    Contains functions for making sure the amount
 *             of the transaction is a decimal number within
 *             the range of 0.00 to 999,999,999.999999999
 *
 *             1. Check if the input's characters are integers with
 *                one decimal character
 *             2. Check if the input is within the acceptable
 *                range for the allowable amount
 *             3. Display test results of input data coming from
 *                an infile called amount_input_infile
 *
 * Note:       I have included an "infile" with some test data.
 *             After compiling the test program, run the following
 *             command with the infile that is provided for
 *             testing:
 *             
 *                amount_input <amount_input_infile
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

#define INTEGER_PART_MIN_LENGTH 0
#define INTEGER_PART_MAX_LENGTH 9
#define FRACTION_PART_MIN_LENGTH 0
#define FRACTION_PART_MAX_LENGTH 5

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::stoi;
using std::strlen;

void parse_amount(string& integer_part, string& fraction_part, const string amount_input);
void display_results_of_test(string amount_input);
bool is_non_negative_integer(const string s);
bool is_integer_part_within_range(const string s);
bool is_fraction_part_within_range(const string s);

int main()
{
   string amount_input;

   // If there is data to process
   if(getline(cin, amount_input))
   {
      display_results_of_test(amount_input);

      // If there is data to process, get the rest of it
      while(getline(cin, amount_input))
      {
         display_results_of_test(amount_input);
      }
   }
   else
   {
      cout << "No data to process." << endl;
      return -1;
   }

   return 0;
}

void display_results_of_test(string amount_input)
{
   string integer_part, fraction_part;

   parse_amount(integer_part, fraction_part, amount_input);

   if(!is_non_negative_integer(integer_part))
   {
      cout << " Integer part not a positive integer or zero --> "
           << amount_input
           << endl;

      return;
   }

   if(!is_non_negative_integer(fraction_part))
   {
      cout << "Fraction part not a positive integer or zero --> "
           << amount_input
           << endl;

      return;
   }

   if(!is_integer_part_within_range(integer_part))
   {
      cout << "               Integer part not within range --> "
           << amount_input
           << endl;

      return;
   }

   if(!is_fraction_part_within_range(fraction_part))
   {
      cout << "              Fraction part not within range --> "
           << amount_input
           << endl;

      return;
   }
 
   cout << "                                 Test passes --> "
        << amount_input
        << endl;
}

// Helper function - before validating the amount, parse it into
// its integer and fractional parts
void parse_amount(string& integer_part, string& fraction_part, const string amount_input)
{
   int decimal_point_count = 0;
   bool dollar_sign_skipped = false;

   for(auto c: amount_input)
   {
      // Skip the first dollar sign
      if(dollar_sign_skipped == false && decimal_point_count == 0 && c == '$')
      {
         dollar_sign_skipped = true;
         continue;
      }
      // Before the decimal point, put the characters into
      // the integer part of the amount
      else if(decimal_point_count == 0 && c != '.')
      {
         // If our first character is not a dollar sign, we don't
         // allow any more dollar signs to be ignored
         // Additional dollar signs make the data invalid
         dollar_sign_skipped = true;
         integer_part.push_back(c);
      }
      // After the decimal point, put any characters into
      // the fractional part of the amount
      else if(decimal_point_count > 0)
      {
         fraction_part.push_back(c);
      }
      else
      {
         ++decimal_point_count;
      }
   }

   // In this case, empty parts of the data can be considered valid,
   // such as .0 or 1. but not just a single decimal point "."
   // In other cases, such as with the date or menu input
   // validation functions, empty input cannot be valid

   // For example, change .1 to 0.1 and 1. to 1.0
   if(integer_part == "" && fraction_part == "")
   {
      // If the input is completely empty such as a space or 
      // a lone decimal, we don't want to add a zero and
      // cause the input to become valid
      return;
   }
   else if(integer_part == "")
   {
      integer_part.push_back('0');
   }
   else
   {
      fraction_part.push_back('0');
   }
}

// Will be shared by four different functions that validate input
//
// 1) is_valid_date_inupt() - for validating individual parts of
//    the date
// 2) is_valid_amount_input() - for validating individual parts of the
//    amount (before the decimal and after, if applicable)
// 3) is_valid_main_menu_option() - for the main menu
// 4) is_valid_edit_menu_option() - for when the user is chosing
//    which part of the budget transaction they want to edit

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

bool is_integer_part_within_range(const string s)
{
   if(size(s) >= INTEGER_PART_MIN_LENGTH && size(s) <= INTEGER_PART_MAX_LENGTH)
   {
      return true;
   }
   else
   {
      return false;
   }
}

bool is_fraction_part_within_range(const string s)
{
   if(size(s) >= FRACTION_PART_MIN_LENGTH && size(s) <= FRACTION_PART_MAX_LENGTH)
   {
      return true;
   }
   else
   {
      return false;
   }
}

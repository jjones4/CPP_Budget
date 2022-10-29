/*
 * Name:       date_input.cpp
 *
 * Purpose:    Contains functions for testing the different
 *             steps in validating date input.
 *
 *             1. Call a parsing function to get information
 *                from before, between, and after the slashes
 *             2. Ensure our month, day, and year are integers
 *             3. Check for correct month, year, and day
 *             4. Display test results of input data coming from
 *                an infile called date_input_infile
 *
 * Note:       I have included an "infile" with some test data.
 *             After compiling the test program, run the following
 *             command with the infile that is provided for
 *             testing:
 *             
 *                date_input <date_input_infile
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

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::stoi;

#define MIN_MONTH 1
#define MAX_MONTH 12
#define MIN_DAY 1
#define MIN_YEAR 1
#define MAX_YEAR 9999

void parse_date(string& month, string& day, string& year, const string date_input);
void display_results_of_test(string date_input);
bool is_non_negative_integer(const string s);
bool is_month_within_range(const string month);
bool is_year_within_range(const string year);
bool is_day_within_range(const string month, const string day, const string year);

int main()
{
   string date_input;
   
   // If there is data to process
   if(getline(cin, date_input))
   {
      display_results_of_test(date_input);

      // If there is data to process, get the rest of it
      while(getline(cin, date_input))
      {
         display_results_of_test(date_input);
      }
   }
   else
   {
      cout << "No data to process." << endl;
      return -1;
   }

   return 0;
}

void display_results_of_test(string date_input)
{
   string month, day, year;

   parse_date(month, day, year, date_input);

   if(!is_non_negative_integer(month))
   {
      cout << "       The month was not a positive integer or zero --> "
           << date_input
           << endl;

      return;
   }

   if(!is_non_negative_integer(day))
   {
      cout << "         The day was not a positive integer or zero --> "
           << date_input
           << endl;

      return;
   }

   if(!is_non_negative_integer(year))
   {
      cout << "        The year was not a positive integer or zero --> "
           << date_input
           << endl;

      return;
   }

   if(!is_month_within_range(month))
   {
      cout << "                         The month was out of range --> "
           << date_input
           << endl;

      return;
   }

   if(!is_year_within_range(year))
   {
      cout << "                          The year was out of range --> "
           << date_input
           << endl;

      return;
   }

   if(!is_day_within_range(month, day, year))
   {
      cout << "The number of days is not valid for the given month --> "
           << date_input
           << endl;

      return;
   }

   cout << "                                        Test passes --> "
        << date_input
        << endl;
}

// Helper function - before validating the date, parse it into
// month, day, and year
void parse_date(
   string& month, string& day, string& year, const string date_input)
{
   int slashes_count = 0;

   for(auto c : date_input)
   {
      // Before the first slash, put the characters into
      // the month
      if(slashes_count == 0 && c != '/')
      {
         month.push_back(c);
      }
      // After the first slash, put the characters into
      // the day
      else if(slashes_count == 1 && c != '/')
      {
         day.push_back(c);
      }
      // After the second slash, put the characters into
      // the year (even if the characters are slashes)
      // This prevents input such as 3/4/22/2 from being
      // valid when the third slash is skipped, causing the
      // year to be 222 instead of 22/2
      else if(slashes_count >=2)
      {
         year.push_back(c);
      }
      else
      {
         ++slashes_count;
      }
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

bool is_month_within_range(const string month)
{
   if(stoi(month) < MIN_MONTH || stoi(month) > MAX_MONTH)
   {
      return false;
   }
   else
   {
      return true;
   }
}

bool is_year_within_range(const string year)
{
   if(stoi(year) < MIN_YEAR || stoi(year) > MAX_YEAR)
   {
      return false;
   }
   else
   {
      return true;
   }
}

bool is_day_within_range(string month, string day, string year)
{
   if(month == "1" || month == "3" || month == "5" ||
      month == "7" || month == "8" || month == "10" ||
      month == "12")
   {
      if(stoi(day) < MIN_DAY || stoi(day) > 31)
      {
         return false;
      }
   }
   else if(month == "4" || month == "6" || month == "9" ||
           month == "11")
   {
      if(stoi(day) < MIN_DAY || stoi(day) > 30)
      {
         return false;
      }
   }
   else
   {
      // For leap years
      if((stoi(year) % 400 == 0) ||
         (stoi(year) % 4 == 00 && stoi(year) % 100 != 0))
      {
         if(stoi(day) < MIN_DAY || stoi(day) > 29)
         {
            return false;
         }
      }
      else
      {
         if(stoi(day) < MIN_DAY || stoi(day) > 28)
         {
            return false;
         }
      }
   }

   return true;
}

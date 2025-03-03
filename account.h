#pragma once
#ifndef __ACCOUNT__
#define __ACCOUNT__


#include "base.h"

struct account
{
	string ac_name;
	string pass_word;
};



void account_menu();

bool account_state_file_check(const string& data_file_path);

void create_account();

void account_method_choice();




#endif // !__ACCOUNT__

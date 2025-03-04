#pragma once
#ifndef __ACCOUNT__
#define __ACCOUNT__


#include "base.h"

struct account
{
	string ac_name;
	string pass_word;
};

typedef struct account_state {
	bool auto_login_state = false;
	bool saving_password_state = false;
}ac_t;//账号管理配置数据



void account_menu();

void login_state_push(ac_t& ac_state,fstream & input_flie = fstream());

bool account_state_file_check(const string& data_file_path);

void create_account();

bool account_method_choice(ac_t& ac_state);

bool login(ac_t & ac_state);




#endif // !__ACCOUNT__

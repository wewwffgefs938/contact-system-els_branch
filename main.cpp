#define EXCLUDE_FILE
#ifdef EXCLUDE_FILE


#include "account.h"
#include "contact.h"

void put_data(fstream& push,vector<contac>& data);

void push_data(fstream& put, vector<contac>& data);

void ac_t_copy(ac_t& ac_state, ac_t& ac_state_copy)
{
	ac_state_copy.account_name = ac_state.account_name;
	ac_state_copy.account_password = ac_state.account_password;
	ac_state_copy.auto_login_state = ac_state.auto_login_state;
	ac_state_copy.saving_password_state = ac_state.saving_password_state;
}

ac_t ac_state;
ac_t ac_state_copy;

int main() {

	Logger error_write("log.txt");

	cout << "welcome to this system: " << setw(2) << system_name<<"-v-" << version <<"  "<< coder << endl;

	string account_state_file_path = "account_state.txt";

	fstream ac_s(account_state_file_path, ios::in | ios::out);//打开账户状态管理文件

	if (account_state_file_check(account_state_file_path))
	{
		ac_s.seekg(0, ios::beg);//重置指针pos
		ac_s >> ac_state.auto_login_state >> ac_state.saving_password_state >> ac_state.account_name >> ac_state.account_password;//载入状态
		ac_t_copy(ac_state, ac_state_copy);
		while (true)
		{
			if (ac_state.auto_login_state)//如果是自动登录
			{
				cout << "自动登录成功" << endl;
				system("pause");
				break;
			}
			else
			{
				if (account_method_choice(ac_state))
					break;
			}
			
		}
		
	}
	else
	{
		ofstream new_ac_s (account_state_file_path);
		if (!new_ac_s.is_open())
		{
			cerr << "账号管理文件无法正常生成" << endl;
		}
		else
		{
			cout << "文件生成成功" << endl;
		}
		new_ac_s.close();
		account_method_choice(ac_state);

	}

	ac_s.close();
	login_state_push(ac_state);


	bool exit = false;

	vector<contac>con_data;

	fstream file(ac_state.account_name+"contact_data.txt", ios::in | ios::out);

	if (!file.is_open()) {
		cerr << "配置文件缺失" <<"at line"<< __LINE__ << endl;
		this_thread::sleep_for(chrono::microseconds(1500));
		cout << "-------------------------" << endl;
		this_thread::sleep_for(chrono::microseconds(500));
		cout << "尝试创建文件";
		ofstream create_file (ac_state.account_name + "contact_data.txt");
		if (!create_file.is_open())
		{
			cerr << "配置文件创建错误" << endl;
			cerr << "系统异常退出" << endl;
			return 1;
		}
		else
		{
			cout << "user_contact_data配置文件创建成功" << endl;
			fstream file(ac_state.account_name + "contact_data.txt", ios::in | ios::out);
			if (!file.is_open())
			{
				cerr << "配置文件读取异常" << endl;
				cerr << "退出系统" << endl;
				return 1;
			}
		}
		create_file.close();
	}

	put_data(file,con_data);

	while (!exit) {
		
		if (contact_menu_port(con_data,file,exit,ac_state)){
			system("cls");
			continue;
		}
		else {
			file.seekg(0, ios::beg);
			push_data(file, con_data);
			if(!exit)
				system("pause");
		}
		system("cls");
	}

	login_state_push(ac_state_copy);
	file.close();
	std::cerr.flush();
	return 0;

}

void put_data(fstream& push,vector<contac>& data) {
	contac temp;
	while (1) {
		push >> temp.number >> temp.name;

		if (push.eof())
			break;
		if (push.fail()) {
			cout << "file read error" << endl;
			break;
		}
		data.push_back(temp);//save data
	}
}


void push_data(fstream& put, vector<contac>& data) {
	put.close();
	put.open(ac_state.account_name + "contact_data.txt",ios::out | ios::in | ios::trunc);
	if (data.size()) {
		for (auto it = data.begin(); it != data.end(); ++it) {
			put << it->number << it->name<<'\n';
		}
	}
	else {
		return;
	}
}

#endif



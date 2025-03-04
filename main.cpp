#define EXCLUDE_FILE
#ifdef EXCLUDE_FILE


#include "account.h"
#include "contact.h"

void put_data(fstream& push,vector<contac>& data);

void push_data(fstream& put, vector<contac>& data);

ac_t ac_state;

int main() {

	cout << "welcome to this system" << setw(2) << system_name << version << endl;

	

	string account_state_file_path = "account_state.txt";

	fstream ac_s(account_state_file_path, ios::in | ios::out);//打开账户状态管理文件

	if (account_state_file_check(account_state_file_path))
	{
		while (true)
		{
			ac_s.seekg(0, ios::beg);//重置指针pos
			ac_s >>  ac_state.auto_login_state >> ac_state.saving_password_state;//载入状态

			if (ac_state.auto_login_state)//如果是自动登录
			{
				cout << "自动登录成功" << endl;
				system("pasue");
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
		bool pd = account_method_choice(ac_state);
		login_state_push(ac_state);

	}

	ac_s.close();
	login_state_push(ac_state);


	bool exit = false;

	vector<contac>con_data;

	fstream file("contact_data.txt", ios::in | ios::out);


	if (!file.is_open()) {
		cout << "????????????????????------" << endl;
		this_thread::sleep_for(chrono::microseconds(1500));
		cout << "-------------------------" << endl;
		this_thread::sleep_for(chrono::microseconds(500));
		cout << "????-";
		if (file._Nocreate)
			cout << "???" << endl;
		else
			cout << "???" << endl;
	}

	put_data(file,con_data);

	while (!exit) {
		
		contact_menu();
		if (contact_menu_port(con_data,file,exit)){
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

	
	file.close();

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
	put.open("contact_data.txt",ios::out | ios::in | ios::trunc);
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



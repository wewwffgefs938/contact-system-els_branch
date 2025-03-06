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

	fstream ac_s(account_state_file_path, ios::in | ios::out);//���˻�״̬�����ļ�

	if (account_state_file_check(account_state_file_path))
	{
		ac_s.seekg(0, ios::beg);//����ָ��pos
		ac_s >> ac_state.auto_login_state >> ac_state.saving_password_state >> ac_state.account_name >> ac_state.account_password;//����״̬
		ac_t_copy(ac_state, ac_state_copy);
		while (true)
		{
			if (ac_state.auto_login_state)//������Զ���¼
			{
				cout << "�Զ���¼�ɹ�" << endl;
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
			cerr << "�˺Ź����ļ��޷���������" << endl;
		}
		else
		{
			cout << "�ļ����ɳɹ�" << endl;
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
		cerr << "�����ļ�ȱʧ" <<"at line"<< __LINE__ << endl;
		this_thread::sleep_for(chrono::microseconds(1500));
		cout << "-------------------------" << endl;
		this_thread::sleep_for(chrono::microseconds(500));
		cout << "���Դ����ļ�";
		ofstream create_file (ac_state.account_name + "contact_data.txt");
		if (!create_file.is_open())
		{
			cerr << "�����ļ���������" << endl;
			cerr << "ϵͳ�쳣�˳�" << endl;
			return 1;
		}
		else
		{
			cout << "user_contact_data�����ļ������ɹ�" << endl;
			fstream file(ac_state.account_name + "contact_data.txt", ios::in | ios::out);
			if (!file.is_open())
			{
				cerr << "�����ļ���ȡ�쳣" << endl;
				cerr << "�˳�ϵͳ" << endl;
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



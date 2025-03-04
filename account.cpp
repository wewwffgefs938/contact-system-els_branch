#include "account.h"

void account_menu()
{
	cout << " **************" << endl
		<< "*****" << "1.��¼" << "*****" << endl
		<< "*****" << "2.ע��" << "*****" << endl
		<< "*****" << "3.�˳�" << "*****" << endl
		<< " **************" << endl;
}

void login_state_push(ac_t& ac_state, fstream& input_file)//д���˺Ź�������
{
	if (!input_file.is_open())
	{
		fstream ac_s("account_state.txt", ios::in | ios::out);
		ac_s << ac_state.auto_login_state << " " << ac_state.saving_password_state << endl;
		ac_s.close();
	}
	else
	{
		input_file << ac_state.auto_login_state << " " << ac_state.saving_password_state << endl;
	}
}

bool account_state_file_check(const string& data_file_path)
{
	ifstream ac_state(data_file_path, ios::ate); //��״̬�ļ����ƶ�ָ�뵽�ļ�ĩβ
	if (!ac_state.is_open())
	{
		cerr << "�ļ��޷��򿪣����Դ���new file" << endl;
		return false;
	}
	streampos file_size = ac_state.tellg();

	ac_state.close();
	return 0 != file_size;
}
void login_state()
{

}

void part2(string & pass_word,size_t & pos)
{
	cout << "����Ҫ���õ�����" << endl;
	getline(cin, pass_word);
	if (pass_word.size() == 0)
	{
		cout << "���벻��Ϊ��" << endl;
		system("pause");
		part2(pass_word, pos);
		return;
	}
	pos = pass_word.find(' ');
	if (pos != string::npos)
	{
		cout << "�������벻�ó��ֿո�" << endl;
		system("pause");
		part2(pass_word,pos);
		return;
	}
}

void create_account()
{
	system("cls");
	string account_name,pass_word;
	cout << "�����˺�����" << endl;
	getline(cin, account_name);
	if (account_name.size() == 0)
	{
		cout << "�˺Ų���Ϊ��" << endl;
		system("pause");
		create_account();
		return;
	}
	size_t pos = account_name.find(' ');
	if (pos != string::npos)
	{
		cout << "�˺����벻�ó��ֿո�" << endl;
		system("pause");
		create_account();
		return;
	}
	part2(pass_word,pos);

	ofstream ac("account.txt", ios::app);
	if (!ac.is_open())
	{
		cerr << "�˺��ļ������쳣,�˳�ϵͳ��" << endl;
		return;
	}
	ac << account_name << " " << pass_word << endl;
	ac.close();
	system("cls");
}

bool account_method_choice(ac_t& ac_state)
{
	bool close_choice = false;
	while (true)
	{
		account_menu();
		switch (_getch())
		{
		case'1':
			if (login(ac_state))
				close_choice = true;
			break;
		case'2':
			create_account();
			break;
		case'3':
			return false;
			break;
		default:
			system("cls");
			cout << "��������" << endl;
			account_method_choice(ac_state);
			return false;
		}
		this_thread::sleep_for(chrono::microseconds(1000000));
		system("cls");
		if (close_choice)
			break;
	}

	return true;
}

bool check_ac_p(const vector<account> & ac_list,string & password,string ac_name)
{
	for (auto it = ac_list.begin(); it != ac_list.end(); ++it)
	{
		if (ac_name == it->ac_name && password == it->pass_word)
			return true;
	}
	return false;
}


bool login(ac_t & ac_state)
{
	ifstream ac ("account.txt");
	vector<account>account_list;
	account temp;
	char temp_input;
	while (true)
	{
		if (ac.eof())
			break;
		if (ac.fail())
			break;
		ac >> temp.ac_name >>temp.pass_word;
		account_list.push_back(temp);
	}
	string input_account_name, intput_password;
	cout << "�����˺�:" << endl;
	getline(cin, input_account_name);
	cout << "��������:" << endl;
	getline(cin, intput_password);
	cout << "�Ƿ������´��Զ���¼Y/N" << endl;
	switch (_getch())
	{
	case'Y':
		case'y':
			ac_state.auto_login_state = true;
	case'N':
		case'n':
			break;
	default:
		break;
	}
	if (!ac_state.auto_login_state)
	{
		cout << "�Ƿ�Ҫ��������" << endl;
		switch (_getch())
		{
		case'Y':
		case'y':
			ac_state.saving_password_state = true;
		case'N':
		case'n':
			break;
		default:
			break;
		}
	}
	if (check_ac_p(account_list, intput_password, input_account_name))
	{
		cout << "��¼�ɹ�" << endl;
		return true;
	}
	else
	{
		cout << "��¼ʧ��,�˺Ż��������" << endl;
		return false;
	}

}

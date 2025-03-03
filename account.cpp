#include "account.h"

void account_menu()
{
	cout << " **************" << endl
		<< "*****" << "1.��¼" << "*****" << endl
		<< "*****" << "2.ע��" << "*****" << endl
		<< "*****" << "3.�˳�" << "*****" << endl
		<< " **************" << endl;
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

void account_method_choice(bool login_state = false)
{
	
	while (true)
	{
		account_menu();
		switch (_getch())
		{
		case'1':
			break;
		case'2':
			create_account();
			break;
		case'3':
			return;
			break;
		default:
			cout << "��������" << endl;
			account_method_choice();
		}
	}
	
	

}

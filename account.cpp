#include "account.h"

void account_menu()
{
	cout << " **************" << endl
		<< "*****" << "1.登录" << "*****" << endl
		<< "*****" << "2.注册" << "*****" << endl
		<< "*****" << "3.退出" << "*****" << endl
		<< " **************" << endl;
}

bool account_state_file_check(const string& data_file_path)
{
	ifstream ac_state(data_file_path, ios::ate); //打开状态文件并移动指针到文件末尾
	if (!ac_state.is_open())
	{
		cerr << "文件无法打开，尝试创建new file" << endl;
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
	cout << "输入要设置的密码" << endl;
	getline(cin, pass_word);
	if (pass_word.size() == 0)
	{
		cout << "密码不能为空" << endl;
		system("pause");
		part2(pass_word, pos);
		return;
	}
	pos = pass_word.find(' ');
	if (pos != string::npos)
	{
		cout << "密码输入不得出现空格" << endl;
		system("pause");
		part2(pass_word,pos);
		return;
	}
}

void create_account()
{
	system("cls");
	string account_name,pass_word;
	cout << "输入账号名称" << endl;
	getline(cin, account_name);
	if (account_name.size() == 0)
	{
		cout << "账号不能为空" << endl;
		system("pause");
		create_account();
		return;
	}
	size_t pos = account_name.find(' ');
	if (pos != string::npos)
	{
		cout << "账号输入不得出现空格" << endl;
		system("pause");
		create_account();
		return;
	}
	part2(pass_word,pos);

	ofstream ac("account.txt", ios::app);
	if (!ac.is_open())
	{
		cerr << "账号文件载入异常,退出系统。" << endl;
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
			cout << "按错了喵" << endl;
			account_method_choice();
		}
	}
	
	

}

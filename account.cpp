#include "account.h"

void account_menu()
{
	cout << " **************" << endl
		<< "*****" << "1.登录" << "*****" << endl
		<< "*****" << "2.注册" << "*****" << endl
		<< "*****" << "3.退出" << "*****" << endl
		<< " **************" << endl;
}

void login_state_push(ac_t& ac_state, fstream& input_file)//写入账号管理配置
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
	ifstream ac_state(data_file_path, ios::ate); //打开状态文件并移动指针到文件末尾
	if (!ac_state.is_open())
	{
		cerr << "文件无法打开，尝试创建new file" << endl;
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
			cout << "按错了喵" << endl;
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
	cout << "输入账号:" << endl;
	getline(cin, input_account_name);
	cout << "输入密码:" << endl;
	getline(cin, intput_password);
	cout << "是否设置下次自动登录Y/N" << endl;
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
		cout << "是否要保存密码" << endl;
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
		cout << "登录成功" << endl;
		return true;
	}
	else
	{
		cout << "登录失败,账号或密码错误" << endl;
		return false;
	}

}

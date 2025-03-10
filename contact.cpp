#include "contact.h"
#include "account.h"


void fun1_add_contacts(vector<contac>& condata);
void fun2_show_contacts(vector<contac>& condata);
void fun3_delete_contacts(vector<contac>& condata);
void fun4_find_contacts(vector<contac>& condata);
void fun5_revise_contacts(vector<contac>& condata);
void fun6_empty_all_contacts(vector<contac>& condata);
void fun7_login_sitting(ac_t& account_state);
void fun0_go_down_system(bool &exit);

void back_menu(bool & back);


bool switch_yes_or_no()
{
	switch (_getch())
	{
	case 'Y':
	case'y':
		return true;
	default:
		break;
	}
	return false;
}

const string account_satate_on_off_print(ac_t& account_state,int method = 0)//1 to auto_login_state, 2 to saving password state
{
	if (1 == method)
	{
		if (account_state.auto_login_state)
			return "(开启)";
		else
			return "(关闭)";
	}
	else if (2 == method)
	{
		if (account_state.saving_password_state)
			return"(开启)";
		else
			return"(关闭)";
	}
}

void contact_menu() {
	cout << " ********************" << endl
		<< "*****" << "1.添加联系人" << "*****" << endl
		<< "*****" << "2.显示联系人" << "*****" << endl
		<< "*****" << "3.删除联系人" << "*****" << endl
		<< "*****" << "4.查找联系人" << "*****" << endl
		<< "*****" << "5.修改联系人" << "*****" << endl
		<< "*****" << "6.清空通讯录" << "*****" << endl
		<< "*****" << " 7.登录设置 " << "*****" << endl
		<< "*****" << " 0.退出系统 " << "*****" << endl
		<< " ********************" << endl;
}


void login_setting_menu(ac_t & account_state)
{
	cout << "当前账号：" << setw(2) << account_state.account_name << endl;
	cout << "密码:" << setw(2);
	for (int i = 0; i < account_state.account_password.size(); i++) cout << '*';
	cout << endl;
	cout << "************************" << endl
		<< "****" << "1.自动登录" << account_satate_on_off_print(account_state, 1) << "****" << endl
		<< "****" << "2.保留密码" << account_satate_on_off_print(account_state, 2) << "****" << endl
		<< "****" << "  3.显示密码  " << "****" << endl
		<< "****" << "  4.退出设置  " << "****" << endl
		<< "************************" << endl;

}

bool contact_menu_port(vector<contac>& condata,fstream& file,bool& exit,ac_t & account_state) {
	bool back = false;
	bool menu_break = false;
	while (true)
	{
		system("cls");
		contact_menu();
		back = false;
		file.seekg(0, ios::beg);//相对于文件开头将文件指针移动到0的位置
		bool commit = false;
		cout << "请按下你的选择" << endl;
		switch (_getch())
		{
		case '1':
			back_menu(back);
			if (back) {
				break;
			}

			fun1_add_contacts(condata);
			break;
		case '2':
			back_menu(back);
			if (back) {
				break;
			}

			fun2_show_contacts(condata);
			break;
		case '3':
			back_menu(back);
			if (back) {
				break;
			}
			if (!condata.size())
				cout << "你个社恐一个联系人都没有，你删牛魔呢" << endl;
			else
				fun3_delete_contacts(condata);
			break;
		case '4':
			back_menu(back);
			if (back) {
				break;
			}
			if (!condata.size())
				cout << "你个社恐一个联系人都没有，你找牛魔呢" << endl;
			else
				fun4_find_contacts(condata);
			break;
		case '5':
			back_menu(back);
			if (back) {
				break;
			}

			fun5_revise_contacts(condata);
			break;
		case '6':
			back_menu(back);
			if (back) {
				break;
			}
			cout << "真的要清空整个通讯录吗？Y/N" << endl;
			switch (_getch())
			{
			case 'Y':
			case'y':
				commit = true;
				break;
			default:
				break;
			}
			if (commit) {
				cout << "要不要再想想呢？Y/N" << endl;
				switch (_getch())
				{
				case 'Y':
				case'y':
					commit = false;
					break;
				default:
					break;
				}
			}
			if (commit)
				fun6_empty_all_contacts(condata);
			break;
		case '7':
			fun7_login_sitting(account_state);
			break;
		case '0':
			back_menu(back);
			if (back) {
				break;
			}
			fun0_go_down_system(exit);
			menu_break = true;
			break;
		default:
			cout << "输入错误喵" << "请重新输入" << endl;
			system("pause");
			continue;
			break;
		}
		if (menu_break)
			break;
		system("pause");
	}
	return back;
}




void fun1_add_contacts(vector<contac>& condata) {
	contac tempdata;
	int size = EOF;
	cout << "选择模式：单次录入请按D，批量录入请按：B" << endl;
	switch (_getch())
	{
	case 'D':
		case 'd':
			cout << "输入电话：", cin>> tempdata.number,cout<<endl;
			getchar();
			cout << "输入姓名：", cin >> tempdata.name, cout << endl;
			condata.push_back(tempdata);
			break;
	case 'B':
		case'b':
			cout << "请输入要录入的数据个数：" << endl;
			cin >> size;
			while (size--) {
				cout << "输入电话：", cin >> tempdata.number, cout << endl;
				getchar();
				cout << "输入姓名：", cin >> tempdata.name, cout << endl;
				condata.push_back(tempdata);
			}
			break;

	default:
		cout << "按错了喵" << endl;
		break;
	}
}
void fun2_show_contacts(vector<contac>& condata) {

	int contacter_cout = 1;

	if (condata.size()) {
		cout<<left<<setw(11)<<"line_num"<<setw(15)<< "电话号码" << setw(15) << "姓名" << endl;
		for (auto it = condata.begin(); it != condata.end(); ++it) {
			cout<<left<<setw(9)<< "contacter"<<setw(2)<<contacter_cout++<< setw(15) <<it->number <<setw(15)<< it->name << endl;
		}
	}
	else
		cout << "没有联系人" << endl;
	
}
void fun3_delete_contacts(vector<contac>& condata) {
	int index = NULL;
	fun2_show_contacts(condata);
	cout << "\n" << "\n" << "\n";
	cout << "请输入你要删除的联系人的序号" << endl;
	cin >> index;
	getchar();
	index--;
	condata.erase(condata.begin() + index);
	cout << "\n" << "\n" << "\n";
	cout << "删除成功" << endl;
	fun2_show_contacts(condata);
}
void fun4_find_contacts(vector<contac>& condata) {
	bool lf = false;//left false;
	bool nm = false;//n false;
	bool iffind = false;
	auto mid = condata.begin() + condata.size() / 2;
	int ieven = condata.size() % 2;
	string temp_str = "NULL";
	long long temp_num = EOF;
	int fi = NULL;
	cout << "需要查找名字\N还是号码\M?"<<endl;
	switch (_getch())
	{
	case'N':
	case'n':
		cout << "输入要查找的名字" << endl;
		getline(cin, temp_str);
  		if (ieven) {
			while (fi <= condata.size() / 2) {
				if ((mid + fi)->name == temp_str) {
					lf = !lf;
					iffind = true;
					break;
				}
				else if ((mid - fi)->name == temp_str) {
					iffind = true;
					break;
				}
				fi++;
			}
		}
		else {
			while (fi <= condata.size() / 2) {
				if (fi < condata.size() / 2) {
					if ((mid + fi)->name == temp_str) {
						lf = !lf;
						iffind = true;
						break;
					}
				}
				else if ((mid - fi)->name == temp_str) {
					iffind = true;
					break;
				}
				fi++;
			}
		}
		
		break;
	case'M':
	case'm':
		cout << "请输入要查找的号码" << endl;
		nm = true;
		cin >> temp_num;
		cin.ignore();
		if (ieven) {
			while (fi <= condata.size() / 2) {
				if ((mid + fi)->number == temp_num) {
					iffind = true;
					lf = !lf;
					break;
				}
				else if ((mid - fi)->number == temp_num) {
					iffind = true;
					break;
				}
				fi++;
			}
		}
		else {
			while (fi <= condata.size() / 2) {
				if (fi < condata.size() / 2) {
					if ((mid + fi)->number == temp_num) {
						iffind = true;
						lf = !lf;
						break;
					}
				}
				else if ((mid - fi)->number == temp_num) {
					iffind = true;
					break;
				}
				fi++;
			}
		}
		
		break;

	default:
		cout << "输入有误" << endl;
		fun4_find_contacts(condata);
		return	;//结束多余进程
		break;
	}
	if (iffind) {
		if (lf) {
			cout << "contacter" << condata.size() / 2 + 1 + fi;
			cout << setw(8) << (condata.begin() + condata.size() / 2 + fi)->name
				<< setw(8) << (condata.begin() + condata.size() / 2 + fi)->number<<endl;
		}
		else {
			cout << "contacter" << condata.size() / 2 - fi + 1;
			cout << setw(8)<< (condata.begin() + condata.size() / 2 - fi)->name
				<< setw(8) << (condata.begin() + condata.size() / 2 - fi)->number<<endl;
		}
	}
	else {
		if (nm)
			cout << "没有找到号码" << endl;
		else
			cout << "没有找到联系人" << endl;
	}
}
void fun5_revise_contacts(vector<contac>& condata) {
	char ch = '\0';
	long long fi = NULL;
	long long number = EOF;
	bool skip = false;
	string temp_str;
	cout << "是否需要查找？ Y/N" << endl;
	ch = _getch();
	if ('y' == ch || 'Y' == ch)
		fun4_find_contacts(condata);
	cout << "请输入需要修改的联系人的序号" << endl;
	if (cin >> fi && fi <= condata.size())
		fi--;
	else {
		cout << "输入有误" << endl;
		return;
	}

	cout << "开始输入如果要跳过请按k" << endl;
	cout << "请输入修改的号码" << endl;
	ch = _getch();
	if (ch == 'k' || ch == 'K')
		skip = true;
	if (!skip) {
		cin >> number;
		(condata.begin() + fi)->number = number;
		cin.ignore();
	}
	cout << "请输入修改的名字" << endl;
	ch = _getch();
	if (ch == 'k' || ch == 'K')
		skip = true;
	else
		skip = false;
	if (!skip) {
		getline(cin, temp_str);
		(condata.begin() + fi)->name = temp_str;
	}
	cout << endl << endl;
	cout << "显示修改后数据：" << endl;
	cout << "line_num" << setw(17) << "电话号码" << setw(9) << "姓名" << endl;
	cout <<"contacter"<<fi+1<< setw(15) << (condata.begin() + fi)->number << setw(15) << (condata.begin() + fi)->name << endl;

}
void fun6_empty_all_contacts(vector<contac>& condata) {
	char ch = '\0';
	vector<contac>tempback(condata); 
	condata.clear();
	if (!condata.size())
		cout << "清除成功" << endl;
	else
		cout << "清除失败" << endl;
	cout << "是否反悔？Y\N" <<endl;
	ch = _getch();
	if ('y' == ch || 'Y' == ch)
		condata = tempback;
	else
		return;
}

void fun7_login_sitting(ac_t & account_state)
{
	bool get_down = false;
	while (true)
	{
		login_setting_menu(account_state);
		switch (_getch())
		{
		case'1':
			cout << "(开启/关闭)自动登录-(Y/N)" << endl;
			if (switch_yes_or_no())
				account_state.auto_login_state = true;
			else
				account_state.auto_login_state = false;
			break;
		case'2':
			cout << "(开启/关闭)保留密码-(Y/N)" << endl;
			if (switch_yes_or_no())
				account_state.saving_password_state = true;
			else
				account_state.saving_password_state = false;
			break;
		case'3':
			show_password(account_state);
			break;
		case'4':
			cout << "退出账号设置" << endl;
			get_down = true;
			break;
		default:
			system("cls");
			cout << "输入错误" << endl;
			continue;
			break;
		}
		if (get_down)
			break;
		system("pause");
		system("cls");
	}
}
void fun0_go_down_system(bool& exit) {
	char getmake;
	cout << "请确认退出操作，是:Y/N" << endl;
	getmake = getchar();
	if (getmake == 'Y' || getmake == 'y')
		exit = true;
	else
		return;
}

void back_menu(bool& back) {
	cout << "按V进入下一步操作，按B返回菜单" << endl;
	char temp = _getch();
	if (temp == 'V' || temp == 'v')
		return;
	else
		back = true;
}

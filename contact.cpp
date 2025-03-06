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
			return "(����)";
		else
			return "(�ر�)";
	}
	else if (2 == method)
	{
		if (account_state.saving_password_state)
			return"(����)";
		else
			return"(�ر�)";
	}
}

void contact_menu() {
	cout << " ********************" << endl
		<< "*****" << "1.�����ϵ��" << "*****" << endl
		<< "*****" << "2.��ʾ��ϵ��" << "*****" << endl
		<< "*****" << "3.ɾ����ϵ��" << "*****" << endl
		<< "*****" << "4.������ϵ��" << "*****" << endl
		<< "*****" << "5.�޸���ϵ��" << "*****" << endl
		<< "*****" << "6.���ͨѶ¼" << "*****" << endl
		<< "*****" << " 7.��¼���� " << "*****" << endl
		<< "*****" << " 0.�˳�ϵͳ " << "*****" << endl
		<< " ********************" << endl;
}


void login_setting_menu(ac_t & account_state)
{
	cout << "��ǰ�˺ţ�" << setw(2) << account_state.account_name << endl;
	cout << "����:" << setw(2);
	for (int i = 0; i < account_state.account_password.size(); i++) cout << '*';
	cout << endl;
	cout << "************************" << endl
		<< "****" << "1.�Զ���¼" << account_satate_on_off_print(account_state, 1) << "****" << endl
		<< "****" << "2.��������" << account_satate_on_off_print(account_state, 2) << "****" << endl
		<< "****" << "  3.��ʾ����  " << "****" << endl
		<< "****" << "  4.�˳�����  " << "****" << endl
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
		file.seekg(0, ios::beg);//������ļ���ͷ���ļ�ָ���ƶ���0��λ��
		bool commit = false;
		cout << "�밴�����ѡ��" << endl;
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
				cout << "������һ����ϵ�˶�û�У���ɾţħ��" << endl;
			else
				fun3_delete_contacts(condata);
			break;
		case '4':
			back_menu(back);
			if (back) {
				break;
			}
			if (!condata.size())
				cout << "������һ����ϵ�˶�û�У�����ţħ��" << endl;
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
			cout << "���Ҫ�������ͨѶ¼��Y/N" << endl;
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
				cout << "Ҫ��Ҫ�������أ�Y/N" << endl;
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
			cout << "���������" << "����������" << endl;
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
	cout << "ѡ��ģʽ������¼���밴D������¼���밴��B" << endl;
	switch (_getch())
	{
	case 'D':
		case 'd':
			cout << "����绰��", cin>> tempdata.number,cout<<endl;
			getchar();
			cout << "����������", cin >> tempdata.name, cout << endl;
			condata.push_back(tempdata);
			break;
	case 'B':
		case'b':
			cout << "������Ҫ¼������ݸ�����" << endl;
			cin >> size;
			while (size--) {
				cout << "����绰��", cin >> tempdata.number, cout << endl;
				getchar();
				cout << "����������", cin >> tempdata.name, cout << endl;
				condata.push_back(tempdata);
			}
			break;

	default:
		cout << "��������" << endl;
		break;
	}
}
void fun2_show_contacts(vector<contac>& condata) {

	int contacter_cout = 1;

	if (condata.size()) {
		cout<<left<<setw(11)<<"line_num"<<setw(15)<< "�绰����" << setw(15) << "����" << endl;
		for (auto it = condata.begin(); it != condata.end(); ++it) {
			cout<<left<<setw(9)<< "contacter"<<setw(2)<<contacter_cout++<< setw(15) <<it->number <<setw(15)<< it->name << endl;
		}
	}
	else
		cout << "û����ϵ��" << endl;
	
}
void fun3_delete_contacts(vector<contac>& condata) {
	int index = NULL;
	fun2_show_contacts(condata);
	cout << "\n" << "\n" << "\n";
	cout << "��������Ҫɾ������ϵ�˵����" << endl;
	cin >> index;
	getchar();
	index--;
	condata.erase(condata.begin() + index);
	cout << "\n" << "\n" << "\n";
	cout << "ɾ���ɹ�" << endl;
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
	cout << "��Ҫ��������\N���Ǻ���\M?"<<endl;
	switch (_getch())
	{
	case'N':
	case'n':
		cout << "����Ҫ���ҵ�����" << endl;
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
		cout << "������Ҫ���ҵĺ���" << endl;
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
		cout << "��������" << endl;
		fun4_find_contacts(condata);
		return	;//�����������
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
			cout << "û���ҵ�����" << endl;
		else
			cout << "û���ҵ���ϵ��" << endl;
	}
}
void fun5_revise_contacts(vector<contac>& condata) {
	char ch = '\0';
	long long fi = NULL;
	long long number = EOF;
	bool skip = false;
	string temp_str;
	cout << "�Ƿ���Ҫ���ң� Y/N" << endl;
	ch = _getch();
	if ('y' == ch || 'Y' == ch)
		fun4_find_contacts(condata);
	cout << "��������Ҫ�޸ĵ���ϵ�˵����" << endl;
	if (cin >> fi && fi <= condata.size())
		fi--;
	else {
		cout << "��������" << endl;
		return;
	}

	cout << "��ʼ�������Ҫ�����밴k" << endl;
	cout << "�������޸ĵĺ���" << endl;
	ch = _getch();
	if (ch == 'k' || ch == 'K')
		skip = true;
	if (!skip) {
		cin >> number;
		(condata.begin() + fi)->number = number;
		cin.ignore();
	}
	cout << "�������޸ĵ�����" << endl;
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
	cout << "��ʾ�޸ĺ����ݣ�" << endl;
	cout << "line_num" << setw(17) << "�绰����" << setw(9) << "����" << endl;
	cout <<"contacter"<<fi+1<< setw(15) << (condata.begin() + fi)->number << setw(15) << (condata.begin() + fi)->name << endl;

}
void fun6_empty_all_contacts(vector<contac>& condata) {
	char ch = '\0';
	vector<contac>tempback(condata); 
	condata.clear();
	if (!condata.size())
		cout << "����ɹ�" << endl;
	else
		cout << "���ʧ��" << endl;
	cout << "�Ƿ񷴻ڣ�Y\N" <<endl;
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
			cout << "(����/�ر�)�Զ���¼-(Y/N)" << endl;
			if (switch_yes_or_no())
				account_state.auto_login_state = true;
			else
				account_state.auto_login_state = false;
			break;
		case'2':
			cout << "(����/�ر�)��������-(Y/N)" << endl;
			if (switch_yes_or_no())
				account_state.saving_password_state = true;
			else
				account_state.saving_password_state = false;
			break;
		case'3':
			show_password(account_state);
			break;
		case'4':
			cout << "�˳��˺�����" << endl;
			get_down = true;
			break;
		default:
			system("cls");
			cout << "�������" << endl;
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
	cout << "��ȷ���˳���������:Y/N" << endl;
	getmake = getchar();
	if (getmake == 'Y' || getmake == 'y')
		exit = true;
	else
		return;
}

void back_menu(bool& back) {
	cout << "��V������һ����������B���ز˵�" << endl;
	char temp = _getch();
	if (temp == 'V' || temp == 'v')
		return;
	else
		back = true;
}

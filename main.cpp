#define EXCLUDE_FILE
#ifdef EXCLUDE_FILE



#include "contact.h"

void put_data(fstream& push,vector<contac>& data);

void push_data(fstream& put, vector<contac>& data);

int main() {


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
		if (contact_menu_port(con_data, file, exit)) {
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



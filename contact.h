#pragma once
#ifndef __CONTACT__
#define __CONTACT__

#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>
#include <conio.h>
#include  <cstdlib>
#include <vector>
#include <thread>
#include <iomanip>

using namespace std;

struct contac {
	long long number = EOF;
	string name;
};



void contact_menu();

bool contact_menu_port(vector<contac>&condata,fstream& file,bool& exit);

#endif
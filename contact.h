#pragma once
#ifndef __CONTACT__
#define __CONTACT__

#include "base.h"

struct contac 
{
	long long number = EOF;
	string name;
};




void contact_menu();

bool contact_menu_port(vector<contac>&condata,fstream& file,bool& exit);

#endif
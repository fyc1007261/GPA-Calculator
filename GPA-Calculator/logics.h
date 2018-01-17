#pragma once
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class Courses {
public:
	string name;
	string credit;
	string semester;
	string compulsory;
	string major;
	string score;
	string gpa;
	bool selected = 1;

	void loadFromString(string str);
};

vector<Courses> readFile(string);
bool detectFile(string filename);



#include "stdafx.h"
#include "logics.h"
using namespace std;

bool detectFile(string filename)
{
	fstream f(filename);
	if (f.is_open())
	{	
		f.close();
		return true;
	}
	return false;
}

vector<Courses> readFile(string filename)
{
	vector<Courses> vec;
	ifstream f(filename);
	f.seekg(0);
	string s;
	getline(f, s);
	while (!f.eof()) {
		Courses course;
		getline(f, s);
		if (s == "") break;
		course.loadFromString(s);
		vec.push_back(course);
	}
	f.close();
	return vec;
}

void Courses::loadFromString(string str)
{
	int len = str.size();
	int i = 0;
	string t_name = "";
	while (str[i] != ',') {
		t_name += str[i];
		i++;
	}
	i++;
	name = t_name;
	
	string t_sem = "";
	while (str[i] != ',') {
		t_sem += str[i];
		i++;
	}
	i++;
	semester = t_sem;
	
	string t_cre = "";
	while (str[i] != ',') {
		t_cre += str[i];
		i++;
	}
	i++;
	credit = t_cre;

	string t_scr = "";
	while (str[i] != ',') {
		t_scr += str[i];
		i++;
	}
	i++;
	score = t_scr;

	string t_gpa = "";
	while (str[i] != ',') {
		t_gpa += str[i];
		i++;
	}
	i++;
	gpa = t_gpa;

	string t_cmp = "";
	while (str[i] != ',') {
		t_cmp += str[i];
		i++;
	}
	i++;
	compulsory = t_cmp;

	string t_maj = "";
	t_maj += str[i];
	major = t_maj;
}

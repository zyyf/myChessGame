#pragma once
#include <vector>

using namespace std;

class Value;
class Array
{
	vector <Value> vec;
public:
	Array();
	~Array();
	Value &operator[](int index);
	vector<Value>::iterator begin();
	vector<Value>::iterator end();
	void clear();
	const bool empty();
	const int size();
	void pushBack(const Value & val);
	string toJson();
};


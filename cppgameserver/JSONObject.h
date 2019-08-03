#pragma once
#include <map>
#include <string>


using namespace std;
class Value;
class JSONObject
{
	map<string, Value> obj_map;
public:
	JSONObject();
	JSONObject(const string &jsonStr);
	~JSONObject();
	Value &operator[](const string &key);
	map<string, Value>::iterator find(const string &key);
	map<string, Value>::iterator insert(const string &key, Value val);
	void erase(const string &key);
	map<string, Value>::iterator begin();
	map<string, Value>::iterator end();
	const int size();
	void clear();
	const bool empty();
	string toJson();
};


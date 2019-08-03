#pragma once
#include <string>
#include <sstream>
#include "Array.h"
#include "JSONObject.h"

enum ValueType {
	INT, FLOAT, BOOL, STRING, OBJECT, ARRAY, NIL  //NIL means JSON is null
};
class JSONObject;
class Array;
class Value
{
	string stringValue;
	double floatValue;
	int intValue;
	bool boolValue;
	JSONObject objectValue;
	Array arrayValue;
	ValueType type;
public:
	Value();
	Value(char *v);
	Value(string v);
	Value(double v);
	Value(int v);
	Value(bool v);
	Value(JSONObject v);
	Value(Array v);
	~Value();
	Value &operator = (const char* v);
	Value &operator = (const string &v);
	Value &operator = (const double &floatVal);
	Value &operator = (const int &intVal);
	Value &operator = (const bool &boolVal);
	Value &operator = (const JSONObject &objVal);
	Value &operator = (const Array &arrayVal);
	Value &operator[] (const int index);
	Value &operator[] (const char *key);
	void pushBack(const Value &val);
	string toString();
	double toFloat();
	int toInt();
	bool toBool();
	string toJson();
	ValueType getType();
	const int size();
};


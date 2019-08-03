#pragma once
#include <string>
#include "JSONObject.h"
#include "Value.h"
#include "Array.h"

using namespace std;
class Read
{
public:
	static JSONObject readObject(const string &str, int &p);
	static Value readValue(const string &str, int &p);
	static Array readArray(const string &str, int &p);
	static string readString(const string &str, int &p);
	static bool readBool(const string &str, int &p);
	static Value readNumber(const string &str, int &p);
	static void readChar(const string &str, int &p, char c);
	static char nextChar(const string &str, int &p);
public:
	Read();
	~Read();
};


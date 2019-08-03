#include "Read.h"


JSONObject Read::readObject(const string & str, int & p)
{
	JSONObject obj;
	readChar(str, p, '{');
	while (1) {
		string key = readString(str, p);
		readChar(str, p, ':');
		Value val = readValue(str, p);
		obj[key] = val;
		if (nextChar(str,p) == '}') {
			readChar(str, p, '}');
			break;
		}
		else {
			readChar(str, p, ',');
		}
	}
	return obj;
}

Value Read::readValue(const string & str, int & p)
{
	Value val;
	switch (nextChar(str, p))
	{
	case '{':
		val = Value(readObject(str, p));
		break;
	case '\"':
		val = Value(readString(str, p));
		break;
	case '[':
		val = Value(readArray(str, p));
		break;
	case 't':
		val = Value(readBool(str, p));
		break;
	case 'f':
		val = Value(readBool(str, p));
		break;
	case '-':
		val = readNumber(str, p);
		break;
	default:
		if (isdigit(nextChar(str, p))) {
			val = readNumber(str, p);
		}
		break; 
	}
	return val;
}

Array Read::readArray(const string & str, int & p)
{
	Array arr;
	readChar(str, p, '[');
	while (1) {
		if (nextChar(str, p) == ']') {
			readChar(str, p, ']');
			break;
		}
		else if (nextChar(str, p) == ',') {
			readChar(str, p, ',');
		}
		else {
			arr.pushBack(readValue(str, p));
		}
	}
	return arr;
}

string Read::readString(const string & str, int & p)
{
	string s;
	readChar(str, p, '\"');
	while (1) {
		if (nextChar(str, p) != '\"' && nextChar(str, p) != '\\') {
			s += str[p];
			++p;
		}
		else if (nextChar(str, p) == '\"') {
			readChar(str, p, '\"');
			break;
		}
	}
	return s;
}

bool Read::readBool(const string & str, int & p)
{
	if (nextChar(str, p) == 't') {
		readChar(str, p, 't');
		readChar(str, p, 'r');
		readChar(str, p, 'u');
		readChar(str, p, 'e');
		return true;
	}
	else if (nextChar(str, p) == 'f') {
		readChar(str, p, 'f');
		readChar(str, p, 'a');
		readChar(str, p, 'l');
		readChar(str, p, 's');
		readChar(str, p, 'e');
		return false;
	}
}

Value Read::readNumber(const string & str, int & p)
{
	string num;
	int numType = 0;	//0 is int,1 is float
	if (nextChar(str, p) == '-') {
		num += '-';
		readChar(str, p, '-');
	}
	if (nextChar(str, p) == '0') {
		num += '0';
		readChar(str, p, '0');
	}
	else if (isdigit(nextChar(str, p))) {
		while (isdigit(nextChar(str, p))) {
			num += nextChar(str, p);
			char c = nextChar(str, p);
			readChar(str, p, c);
		}
	}
	if (nextChar(str, p) == '.') {
		num += '.';
		readChar(str, p, '.');
		while (isdigit(nextChar(str, p))) {
			char c = nextChar(str, p);
			num += c;
			readChar(str, p, c);
		}
		numType = 1;
	}
	if (nextChar(str, p) == 'e' || nextChar(str, p) == 'E') {
		char c = nextChar(str, p);
		num += c;
		readChar(str, p, c);
		c = nextChar(str, p);
		num += c;
		readChar(str, p, c);
		while (isdigit(nextChar(str, p))) {
			c = nextChar(str, p);
			num += c;
			readChar(str, p, c);
		}
	}
	stringstream ssNum;
	ssNum << num;
	if (numType == 0) {
		int numInt;
		ssNum >> numInt;
		return Value(numInt);
	}
	else {
		double numFloat;
		ssNum >> numFloat;
		return Value(numFloat);
	}
}

void Read::readChar(const string & str, int & p, char c)
{
	while (1)
	{
		if (str[p] == c) {
			++p;
			break;
		}
		else {
			++p;
		}
	}
}

char Read::nextChar(const string & str, int & p)
{
	int i = p;
	while (1) {
		if (str[i] == ' ') {
			++i;
		}
		else {
			return str[i];
		}
	}
}

Read::Read()
{
}


Read::~Read()
{
}

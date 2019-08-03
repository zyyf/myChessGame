#include "Array.h"
#include "Value.h"



Array::Array()
{
}


Array::~Array()
{
}

Value & Array::operator[](int index)
{
	return vec[index];
}

vector<Value>::iterator Array::begin()
{
	return vec.begin();
}

vector<Value>::iterator Array::end()
{
	return vec.end();
}

void Array::clear()
{
	vec.clear();
}

const bool Array::empty()
{
	return vec.empty();
}

const int Array::size()
{
	return vec.size();
}

void Array::pushBack(const Value & val)
{
	vec.push_back(val);
}

string Array::toJson()
{
	string arrayStr = "[";
	for (auto i = vec.begin(); i != vec.end(); ++i) {
		if (i != vec.begin()) {
			arrayStr += ", ";
		}
		arrayStr += i->toJson();
	}
	arrayStr += "]";
	return arrayStr;
}

#include <iostream>
#include "Value.h"
#include "Array.h"



Value::Value()
{
	type = NIL;
}

Value::Value(char * v):stringValue(v), type(STRING)
{
}

Value::Value(string v): stringValue(v), type(STRING)
{
}

Value::Value(double v): floatValue(v), type(FLOAT)
{
}

Value::Value(int v): intValue(v), type(INT)
{
}

Value::Value(bool v): boolValue(v), type(BOOL)
{
}

Value::Value(JSONObject v): objectValue(v), type(OBJECT)
{
}

Value::Value(Array v): arrayValue(v), type(ARRAY)
{
}


Value::~Value()
{
}

Value & Value::operator=(const char * v)
{
	type = STRING;
	stringValue = v;
	return *this;
}

Value & Value::operator=(const string & v)
{
	type = STRING;
	stringValue = v;
	return *this;
}

Value & Value::operator=(const double & floatVal)
{
	type = FLOAT;
	floatValue = floatVal;
	return *this;
}

Value & Value::operator=(const int & intVal)
{
	type = INT;
	intValue = intVal;
	return *this;
}

Value & Value::operator=(const bool & boolVal)
{
	type = BOOL;
	boolValue = boolVal;
	return *this;
}

Value & Value::operator=(const JSONObject & objVal)
{
	type = OBJECT;
	objectValue = objVal;
	return *this;
}

Value & Value::operator=(const Array &arrayVal)
{
	type = ARRAY;
	arrayValue = arrayVal;
	return *this;
}

Value & Value::operator[](const int index)
{
	return arrayValue[index];
}

Value & Value::operator[](const char * key)
{
	return objectValue[key];
}

void Value::pushBack(const Value & val)
{
	arrayValue.pushBack(val);
}

string Value::toString()
{
	return stringValue;
}

double Value::toFloat()
{
	return floatValue;
}

int Value::toInt()
{
	return intValue;
}

bool Value::toBool()
{
	return boolValue ? true : false;
}


string Value::toJson()
{
	ostringstream ossInt;
	ostringstream ossFloat;
	switch (type)
	{
	case INT:
		ossInt << intValue;
		return ossInt.str();
	case FLOAT:
		ossFloat << floatValue;
		return ossFloat.str();
	case BOOL:
		return boolValue ? "true" : "false";
	case STRING:
		return "\"" + stringValue + "\"";
	case OBJECT:
		return objectValue.toJson();
	case ARRAY:
		return arrayValue.toJson();
	default:
		break;
	}
}

ValueType Value::getType()
{
	return type;
}

const int Value::size()
{
	return arrayValue.size();
}

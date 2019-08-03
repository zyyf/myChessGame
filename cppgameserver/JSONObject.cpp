#include "JSONObject.h"
#include "Value.h"
#include "Read.h"



JSONObject::JSONObject()
{
}

JSONObject::JSONObject(const string & jsonStr)
{
	int position = 0;
	*this = Read::readObject(jsonStr, position);
}


JSONObject::~JSONObject()
{
}

Value & JSONObject::operator[](const string & key)
{
	return obj_map[key];
}

map<string, Value>::iterator JSONObject::find(const string & key)
{
	return obj_map.find(key);
}

map<string, Value>::iterator JSONObject::insert(const string & key, Value val)
{
	return obj_map.insert(make_pair(key, val)).first;
}

void JSONObject::erase(const string & key)
{
	obj_map.erase(key);
}

map<string, Value>::iterator JSONObject::begin()
{
	return obj_map.begin();
}

map<string, Value>::iterator JSONObject::end()
{
	return obj_map.end();
}

const int JSONObject::size()
{
	return obj_map.size();
}

void JSONObject::clear()
{
	obj_map.clear();
}

const bool JSONObject::empty()
{
	return obj_map.empty();
}

string JSONObject::toJson()
{
	string jsonstr = "{";
	for (auto i = obj_map.begin(); i != obj_map.end(); ++i) {
		if (i != obj_map.begin()) {
			jsonstr += ", ";
		}
		jsonstr += "\"" + i->first + "\":" + i->second.toJson();
		//jsonstr += "\"" + i->first + "\":";
	}
	jsonstr += "}";
	return jsonstr;
}


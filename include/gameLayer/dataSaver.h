#pragma once
#include <ctime>
#include <vector>
#include <singleton.h>
#include <iostream>
#include <fstream>
using namespace std;
class DataSaver:public Singleton<DataSaver>
{
private:
	friend class Singleton<DataSaver>;
	DataSaver() {}
public:
	float highScore = 0;
	time_t timestamp;
	inline void Load() {
		// Object to read from file
		ifstream file_obj;

		// Opening file in input mode
		file_obj.open(RESOURCES_PATH "data.txt", ios::in);

		// Reading from file into object "obj"
		file_obj.read((char*)this, sizeof(*this));
		file_obj.close();
	}
	inline void Save() {
		// Object to write in file
		ofstream file_obj;

		// Opening file in append mode
		file_obj.open(RESOURCES_PATH "data.txt", ios::out);

		// Writing the object's data in file
		file_obj.write((char*)this, sizeof(*this));
	}
};
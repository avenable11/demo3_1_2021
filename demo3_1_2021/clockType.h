#pragma once
#include <string>
#include <stdexcept>
#include <sstream>
#include <iomanip>
#include <iostream>

using std::string;
using std::invalid_argument;
using std::ostringstream;
using std::setw;
using std::setfill;
using std::ostream;
using std::istream;

enum timeType { AM, PM };
string timeTypeToString(timeType t);

class clockType
{
public:
	void setTime(int, int, int, timeType);
	void getTime(int&, int&, int&, timeType&) const;
	
	void printTime() const;
	
	bool equalTime(const clockType&) const;
	clockType(int h = 12, int m = 0, int s = 0, timeType t = AM);
	~clockType();
	static int getNumClocks();
	static int numClocks;
	clockType& operator+(int); //myClock + 7*60
	int operator-(clockType) const;
	clockType operator++();
	clockType operator++(int);
	friend ostream& operator<<(ostream&, clockType&);
	friend istream& operator>>(istream&, clockType&);
private:
	int hour;
	int min;
	int sec;
	timeType timeOfDay;
	string to_string() const;
	void incrementSeconds();
	void incrementMinutes();
	void incrementHours();

};



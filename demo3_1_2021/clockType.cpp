#include <iostream>
#include <cmath>

#include "clocktype.h"

using std::cout;
using std::endl;

int clockType::numClocks = 0;

clockType::clockType(int h, int m, int s, timeType t)
{
	setTime(h, m, s, t);
	numClocks++;
}

void clockType::setTime(int h, int m, int s, timeType t)
{

	try
	{
		if (h >= 1 && h <= 12)
			hour = h;
		else
		{
			throw invalid_argument("The hour must be between 1 and 12. Hour has been set to 12.");
		}

	}
	catch (invalid_argument e)
	{
		hour = 12;
		throw;
	}
	if (m >= 0 && m < 60)
		min = m;
	else
	{
		min = 0;
		throw invalid_argument("The minutes must be between 0 and 59. Minutes have been set to 0.");
	}
	if (s >= 0 && s < 60)
		sec = s;
	else
	{
		sec = 0;
		throw invalid_argument("The seconds must be between 0 and 59. Seconds have been set to 0.");
	}
	if (t != AM && t != PM)
		throw invalid_argument("Time of day should be AM or PM.");
	else
		timeOfDay = t;
}

void clockType::getTime(int& h, int& m, int& s, timeType& t) const
{
	h = hour;
	m = min;
	s = sec;
	t = timeOfDay;
}

void clockType::printTime() const
{

	cout << hour << ":" << min << ":" << sec << endl;
}

void clockType::incrementSeconds()
{
	if (sec + 1 >= 60)
	{
		sec = 0;
		incrementMinutes();
	}
	else
		sec++;
}

void clockType::incrementMinutes()
{
	if (min + 1 >= 60)
	{
		min = 0;
		incrementHours();
	}
	else
		min++;
}

void clockType::incrementHours()
{
	if (hour + 1 > 12)
	{
		hour = 1;
		if (timeOfDay == AM)
			timeOfDay = PM;
		else
			timeOfDay = AM;
	}
	else
		hour++;
}

bool clockType::equalTime(const clockType& othClock) const
{
	return hour == othClock.hour && min == othClock.min && sec == othClock.sec;
}




clockType::~clockType()
{
	//cout << "Destructor called" << endl;
	numClocks--;
	//cout << "The number of clocks is " << numClocks << endl;
}

int clockType::getNumClocks()
{
	return numClocks;
}

string clockType::to_string() const
{
	ostringstream out;
	out << setfill('0');
	out << setw(2) << hour << ":" << setw(2) << min << ":" << setw(2) << sec << " " << timeTypeToString(timeOfDay);
	return out.str();
}

string timeTypeToString(timeType t)
{
	switch (t)
	{
	case AM: return "AM";
	case PM: return "PM";
	default: return "Unknown";
	}
}

ostream& operator<<(ostream& out, clockType& theClock)
{
	out << theClock.to_string();
	return out;
}

istream& operator>>(istream& in, clockType& theClock)
{
	int h, m, s;
	timeType timeOfDay = AM;
	in >> h >> m >> s;
	if (h >= 12)
	{
		timeOfDay = PM;
		if (h != 12)
			h = h - 12;
	}
	else {
		if (h == 0)
			h = 12;
	}
	theClock.setTime(h, m, s, timeOfDay);
	
	return in;
}


clockType& clockType::operator+(int x)
{
	for (int i = 0; i < x; i++)
	{
		this->incrementSeconds();
	}
	return *this;

}

int clockType::operator-(clockType othClock) const
{
	int adjHour = this->hour, othAdjHour = othClock.hour;
	if (this->timeOfDay == PM)
	{
		if(this->hour != 12)
		adjHour += 12;
	}
	else
	{
		if (this->hour == 12)
			adjHour = 0;
	}
	if (othClock.timeOfDay == PM)
	{
		if (othClock.hour != 12)
		othAdjHour += 12;
	}
	else
	{
		if (othClock.hour == 12)
			othAdjHour = 0;
	}
	int thisSeconds, othSeconds, diffSeconds;
	thisSeconds = adjHour * 60 * 60 + this->min * 60 + this->sec;
	othSeconds = othAdjHour * 60 * 60 + othClock.min * 60 + othClock.sec;
	diffSeconds = abs(thisSeconds - othSeconds);

	return diffSeconds;
}

clockType clockType::operator++()
{
	incrementSeconds();
	return *this;
}

clockType clockType::operator++(int)
{
	clockType oldValue = *this;
	++(*this);
	return oldValue;
}



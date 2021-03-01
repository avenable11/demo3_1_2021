#include <iostream>
#include <string>
#include <fstream>
#include "clockType.h"

using namespace std;

int main()
{
	clockType myClock;
	cout << "The time on my clock is: " << myClock << endl;
	myClock = myClock + 7 * 60;
	cout << "The time on my clock is now: " << myClock << endl;
	clockType yourClock;
	int diffClock = myClock - yourClock;
	cout << "the difference is " << diffClock << " seconds" << endl;

	cout << "Enter the hours, min, and seconds for the clock in 24 hour time: ";
	cin >> yourClock;
	cout << endl;

	cout << "You entered " << yourClock << endl;


	ifstream test; 
	test.open("time.txt");
	while (!test.eof() && test.is_open())
	{
		clockType newClock;
		
		try 
		{
			test >> newClock;
			cout << newClock << endl;
			for (int i = 0; i < 5 * 60 *60; i++)
			{
				++newClock;
			}
			cout << newClock << endl;
		}
		catch (invalid_argument e)
		{
			cout << "There was an error with setting the clock." << endl;
		}
	}

	return 0;
}



#pragma once

#include <ctime>
#include <string>
#include <sstream>

using namespace std;

#define DATE_DELIM '-'

class Date
{
public :

	int day;
	int month;
	int year;

	Date() : day{ 0 }, month{ 0 }, year{ 0 }
	{}

	Date(int day, int month, int year) : day{ day }, month{ month }, year{ year }
	{
		
	}

	Date(const std::string& input)
	{
		std::istringstream in(input);

		std::string str;

		getline(in, str, DATE_DELIM);
		year = stoi(str);

		getline(in, str, DATE_DELIM);
		month = stoi(str);

		getline(in, str);
		day = stoi(str);
	}

	static int DateDifference(const Date& date1, const Date& date2)
	{
		// date1 - date2
		std::tm time1 = { 0, 0, 0, date1.day, date1.month - 1, date1.year - 1900 };
		std::tm time2 = { 0, 0 , 0, date2.day, date2.month - 1, date2.year - 1900};

		

		std::time_t t1 = mktime(&time1);
		std::time_t t2 = mktime(&time2);

		double dif = -1;


		if (t1 != (time_t)(-1) && t2 != (time_t)(-1))
		{
			dif = difftime(t1, t2) / (60 * 60 * 24);
		}
		else
		{
			std::cout << "there is a problem in finding difference " << std::endl; // this is just for test 
		}

		return dif;		
	}

	bool operator==(const Date& other)
	{
		if (this->day != other.day)
		{
			return false;
		}

		if (this->month != other.month)
		{
			return false;
		}

		if (this->year != other.year)
		{
			return false;
		}

		return true;
	}

	bool operator<(const Date& other)
	{
		if (this->year > other.year)
		{
			return false;
		}

		if (this->year < other.year)
		{
			return true;
		}

		if (this->month > other.month)
		{
			return false;
		}

		if (this->month < other.month)
		{
			return true;
		}

		if (this->day > other.day)
		{
			return false;
		}

		if (this->day < other.day)
		{
			return true;
		}

		return false;


	}

	operator std::string()
	{
		std::ostringstream output;

		output << setfill('0');
		output << year << DATE_DELIM;
		output << setw(2) << month << DATE_DELIM;
		output << setw(2) << day;

		return output.str();
	}

	

private :
	/*long long int _stamp;*/
};

const Date referenceDate = { 1, 1, 2000 };

std::ostream& operator<<(std::ostream& output, Date& date)
{
	output << setfill('0');
	output << date.year << DATE_DELIM;
	output << setw(2) << date.month << DATE_DELIM;
	output << setw(2) << date.day;

	output << setfill(' ');

	return output;
}
std::istream& operator>>(std::istream& input, Date& date)
{
	string aux;

	/*input >> aux;*/

	getline(input, aux);

	date = aux;

	return input;
}
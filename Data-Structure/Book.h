#pragma once
#include <string>
#include <utility>
#include "Queue.h"
#include "Queue.cpp"
#include "Date.h"
#include <sstream>

#define BOOK_DELIMITER ' '

class Book
{
public:
	static int count;

	

	Book() : id{ -1 },
		genere{ "" },
		title{ "" },
		author{ "" },
		publishDate{ referenceDate },
		isAvailable{ true },
		borrowerId{ -1 },
		numberOfExtensions{ 0 },
		lastAvailableDate{ referenceDate }		
	{
		count++;
		id = count;

		
	}


	Book(const std::string& input_string)
	{
		std::istringstream input(input_string);

		//string str;
		//// id
		//getline(input, str, DELIMITER);
		//id = stoi(str);

		//getline(input, str, DELIMITER);
		//title = str;

		//getline(input, str, DELIMITER);
		//author = str;

		//getline(input, str, DELIMITER);
		//publishDate = str;

		//getline(input, str, DELIMITER);
		//isAvailable = 

		//getline(input, str, DELIMITER);
		//borrowerId = stoi(str);
		
		std::string aux;

		input >> id;
		input >> title;
		input >> author;
		input >> aux; publishDate = aux;
		input >> isAvailable;
		input >> borrowerId;
		input >> numberOfExtensions;
		input >> aux; lastAvailableDate = aux;

		


	}

	/*Book(const Book& book)
	{
		std::cout << "hello";
	}*/

	

	operator std::string()
	{
		std::ostringstream output;

		output << id << BOOK_DELIMITER;
		output << title << BOOK_DELIMITER;
		output << author << BOOK_DELIMITER;
		output << (std::string)publishDate << BOOK_DELIMITER;
		output << isAvailable << BOOK_DELIMITER;
		output << borrowerId << BOOK_DELIMITER;
		output << numberOfExtensions << BOOK_DELIMITER;
		output << (std::string)lastAvailableDate;


		return output.str();
	}



	int id;
	std::string genere;
	std::string title;
	std::string author;
	Date publishDate;
	bool isAvailable;
	int borrowerId;
	int numberOfExtensions;
	Date lastAvailableDate;

	Queue<int> reserveQueue; // store the id of users that reserved this book



	/*~Book()
	{
		if (reserveQueue != nullptr)
		{
			delete reserveQueue;
			reserveQueue = nullptr;
		}
			
	}*/

	~Book()
	{
		Book::count--;
	}


private:


};

int Book::count = 0;

std::ostream& operator<<(std::ostream& output, Book& book)
{
	output << (std::string)book;
	output << '\n';

	if (book.reserveQueue.size() <= 0)
	{
		return output;
	}


	int length = book.reserveQueue.size();

	int* temp_arr = new int[length];

	for (int i = 0; i < length; ++i)
	{
		temp_arr[i] = book.reserveQueue.Dequeue();
		output << temp_arr[i] << BOOK_DELIMITER;
	}

	for (int i = 0; i < length; ++i)
	{
		book.reserveQueue.Enqueue(temp_arr[i]);
	}

	delete [] temp_arr;

	return output;

}

std::istream& operator>>(std::istream& input, Book& book)
{
	std::string aux;

	getline(input, aux);

	book = aux;

	int temp;



	while (input >> temp)
	{
		book.reserveQueue.Enqueue(temp);
	}

	return input;
}
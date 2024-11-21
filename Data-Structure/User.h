#pragma once

#include <string>
#include "Double_linked_list.h"
#include "Double_linked_list.cpp"
#include <utility>
#include "Date.h"
#include <sstream>



#define USER_DELIMITER ' '

class User
{
public:
	static int count;

	User() : name{ "" },
		code{ "" },
		userName{ "" },
		password{ "" }
	{
		id = count;
		count++;

		//bookList = new Double_linked_list<std::pair<int, Date>>();
	}

	
	User(const std::string& userName, const std::string& password)
	{
		this->userName = userName;
		this->password = password;
		name = "";
		code = "";
		//bookList = nullptr;
		id = count;
		count++;
		//bookList = new Double_linked_list<std::pair<int, Date>>();
	}

	int id;
	std::string name;
	std::string code;
	std::string userName;
	std::string password;

	Double_linked_list <std::pair<int, Date>> bookList; // store id of the book and date it was borrowed from library

	// append the given user to the file with the given path ( make sure that the file specified by the path exists )
	static void AppendToFile(const User& user, const char* path)
	{
		FILE* fp;
		fopen_s(&fp, path, "a");

		if (fp == NULL)
		{ 
			// err
			return;
		}
		
		fwrite(&user, sizeof(User), 1, fp);
	}

	User(const std::string& input_string)
	{
		std::istringstream input(input_string);

		input >> id;
		input >> name;
		input >> code;
		input >> userName;
		input >> password;
	}

	operator std::string()
	{
		std::ostringstream output;

		output << id << USER_DELIMITER;
		output << name << USER_DELIMITER;
		output << code << USER_DELIMITER;
		output << userName << USER_DELIMITER;
		output << password;

		return output.str();
	}

	~User()
	{
		User::count--;
	}

private:

};
int User::count = 0;


User Admin("admin", "1234");

std::istream& operator>>(std::istream& input, User& user)
{
	std::string aux;

	getline(input, aux);

	user = aux;

	int temp_id;
	//Date temp_date;


	while (input >> temp_id)
	{
		input >> aux;

		//temp_date = aux;

		user.bookList.push_back(make_pair(temp_id, aux));
	}

	return input;
}

std::ostream& operator<<(std::ostream& output, User& user)
{
	output << (std::string)user;
	output << '\n';

	if (user.bookList.get_size() <= 0)
	{
		return output;
	}
	
	for (int i = 0; i < user.bookList.get_size(); ++i)
	{
		auto elem = user.bookList[i];

		output << elem.first << USER_DELIMITER;
		output << elem.second << USER_DELIMITER;
	}

	return output;


}


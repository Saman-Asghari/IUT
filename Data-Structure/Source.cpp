#include <iostream>
#include <filesystem>
#include <string>
#include <algorithm>
#include "User.h"
#include "Book.h"
#include "Double_linked_list.h"
#include <conio.h>
#include <fstream>




using namespace std;

namespace fs = std::filesystem;


#pragma region MACROS

#define INVALID_OPTION -1 
#define EXTENSION_DAYS 5
#define BORROW_INTERVAL 10
#define PENALTY_FEE 5
#define CLEAR system("cls")

#pragma endregion





void ReadKey()
{
	cout << "press  enter to continue ..." << endl;
	_getch();
}


//path
auto project_path = fs::current_path();
fs::path users_path = project_path / "users";
fs::path library_path = project_path / "library";
fs::path books_path = library_path / "books";
fs::path counts_path = project_path / "counts.txt";
//
//// replace
//vector<User*> users; // later will be linked list
//vector<Book*> books;

Double_linked_list<User*> users;
Double_linked_list<Book*> books;



//int User::count = 0;
//int Book::count = 0;

Date today = referenceDate;

void create_text_file(fs::path& path, const char* text_file_name)
{
	FILE* fp;
	string file_path = (path / text_file_name).string();

	fopen_s(&fp, file_path.c_str(), "w");

	if (fp == NULL)
	{
		cout << "problem opening " << file_path << endl;
		return;
		//except ...
	}

	fclose(fp);


}


#pragma region UI_UTILITY

void print_menu(const char** options, size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		printf("%d. %s\n", i + 1, options[i]);
	}

	cout << "choose an option (enter a number) : " << endl;
}

int input_option(int limit)
{
	string input;
	//cin >> input;
	getline(cin, input);

	if (input.size() > 1)
	{
		return INVALID_OPTION;
	}

	/*if (!isdigit(input[0]))
	{
		return INVALID_OPTION;
	}*/

	int option = input[0] - '0';

	if (!(0 < option && option <= limit))
	{
		return INVALID_OPTION;
	}

	return option;
}

#pragma endregion


#pragma region Sign-In-Out

void sign_up()
{
	// get info

	string userName, password, name, code;

	cout << "enter UserName : " << endl;
	/*cin >> userName;*/
	getline(cin, userName);
	cout << "enter password : " << endl;
	//cin >> password;
	getline(cin, password);

	cout << "enter name : " << endl;
	getline(cin, name);

	cout << "enter your code meli : " << endl;
	getline(cin, code);

	// check for duplicate user name  ...



	/*User* user = new User();
	user->userName = userName;
	user->password = password;*/

	User* user = new User(userName, password);
	user->code = code;
	user->name = name;

	/*User::count++;
	user.id = User::count;*/


	// create a file for each user that contains info about books that is borrowed
	/*FILE* fp;
	string str = (users_path / (user.name)).string();
	fopen_s(&fp, str.c_str(), "w");
	if (fp != NULL)
	{
		fclose(fp);
	}
	else
	{
		cout << "there is a problem creating the file for user { " << userName << " } " << endl;
		
	}*/

	//create_text_file(users_path, user->userName.c_str());

	// write the user to a general file that containing all users 

	users.push_back(user);

	cout << "user created now  you can login" << endl;
	ReadKey();
	CLEAR;
}

User* login()
{
	string userName;
	string password;

	cout << "enter username : " << endl;
	/*cin >> userName;*/
	getline(cin, userName);
	cout << "enter password : " << endl;
	//cin >> password;
	getline(cin, password);

	User temp_user(userName, password);

	// search for it in a linked list

	/*for (auto elem : users)
	{
		if (elem->userName == userName && elem->password == password)
		{
			return elem;
		}
	}*/

	int userIndex = 
		users.does_exist(&temp_user, [](User* a, User* b)->bool {
		return (a->userName == b->userName && a->password == b->password);
		});

	if (userIndex == -1)
	{
		return nullptr;
	}
	else
	{
		return users[userIndex];
	}

	



}

#pragma endregion




#pragma region Admin

void addBook()
{
	// input book

	string title;
	string author;
	string publishDate;

	cout << "enter the title of the book : " << endl;
	//cin >> title;
	getline(cin, title);
	cout << "enter the author of the book : " << endl;
	//cin >> author;
	getline(cin, author);
	/*cout << "enter publish date : " << endl;
	cin >> publishDate;*/

	//check for duplicate  ... 

	//Book::count++;



	Book* book = new Book();
	book->title = title;
	//book->id = Book::count;
	book->lastAvailableDate = today;
	book->author = author;
	//book->publishDate = publishDate;

	// this file stores reserve queue for each book
	//create_text_file(library_path, title.c_str());

	////replace
	//books.push_back(book);

	books.push_back(book);

	cout << "book added !" << endl;

	ReadKey();
	CLEAR;

}

void lendBook()
{
	// who is lending

	string inputUsername;

	cout << "what is your username ? " << endl;

	//cin >> inputUsername;
	getline(cin, inputUsername);

	User temp_user(inputUsername, "");

	// check whether this user is valid or not 

	int userIndex = -1;

	/*for (int i = 0; i < users.get_size(); ++i)
	{
		if (users[i]->userName == inputUsername)
		{
			userIndex = i;
			break;
		}
	}*/

	userIndex = users.does_exist(&temp_user, [](User* a, User* b)->bool {
		return (a->userName == b->userName);
		});

	if (userIndex == -1)
	{
		cout << "there is no such user !" << endl;
		ReadKey();
		CLEAR;
		return;
	}

	//users.search(inputUsername, predicate);
	

	// what do you want to borrow 

	string bookTitle;

	cout << "enter the title of book you want to borrow : " << endl;
	//cin >> bookTitle;
	getline(cin, bookTitle);

	Book temp_book;

	temp_book.title = bookTitle;

	// does the book exist  (search in linked list)

	// books.search(bookTitle, predicate);

	int bookIndex = -1;
	/*for (int i = 0; i < books.get_size(); ++i)
	{
		if (books[i]->title == bookTitle)
		{
			bookIndex = i;
			break;
		}
	}*/

	bookIndex = books.does_exist(&temp_book, [](Book* a, Book* b)->bool {
		return (a->title == b->title);
		});

	if (bookIndex == -1)
	{
		cout << "there is no such book" << endl;
		ReadKey();
		CLEAR;
		return;
	}
	
	// is the book available
		// if(!books[i].isAvailable)
		// do you want to reserve 
			// books[i].reserveQueue.append(make_pair(users[i], today_date)
	if (!books[bookIndex]->isAvailable)
	{
		cout << "the book is not currently available to borrow. do you want to borrow it ? (y/n)" << endl;
		cout << "there are " << books[bookIndex]->reserveQueue.size() << " users in queue." << endl;
		if (cin.get() == 'y')
		{
			books[bookIndex]->reserveQueue.Enqueue(users[userIndex]->id);

			cout << "reserved ! " << endl;
			ReadKey();
			CLEAR;
		}

		return;
		
	}

	// is there any reserve ?
		// validate books[i].reserveQueue
		// 
	
	int elapsed_days = Date::DateDifference(today, books[bookIndex]->lastAvailableDate);
	for (int i = (elapsed_days / 3); i > 0; --i)
	{
		if (books[bookIndex]->reserveQueue.size() <= 0)
		{
			break;
		}
		else
		{
			books[bookIndex]->reserveQueue.Dequeue();
		}
	}

	books[bookIndex]->lastAvailableDate = today;


		// 
		// if(books[i].reserveQueue.size() == 0 )
		//		lend book
		
	if (books[bookIndex]->reserveQueue.size() <= 0)
	{
		// lend book

		books[bookIndex]->isAvailable = false;
		books[bookIndex]->borrowerId = users[userIndex]->id;

		users[userIndex]->bookList.push_back(make_pair(books[bookIndex]->id, today));
	}
	

	//	 else if(books[i]->reserveQueus.top().userId == userId)
	//			lend book & dequeue
	else if (books[bookIndex]->reserveQueue.first_one_to_out() == users[userIndex]->id)
	{
		// lend book
		books[bookIndex]->isAvailable = false;
		books[bookIndex]->borrowerId = users[userIndex]->id;
		books[bookIndex]->reserveQueue.Dequeue();

		users[userIndex]->bookList.push_back(make_pair(books[bookIndex]->id, today));

		cout << "the book : { " << books[bookIndex]->title << " } is borrowed by : { "
			<< users[userIndex]->userName << " } " << endl;

		ReadKey();
		CLEAR;
		return;
	}

		// else do you want to reserve ?
	else
	{
		cout << "the book is not currently available to borrow. do you want to borrow it ? (y/n)" << endl;
		cout << "there are " << books[bookIndex]->reserveQueue.size() << " users in queue." << endl;
		if (cin.get() == 'y')
		{
			books[bookIndex]->reserveQueue.Enqueue(users[userIndex]->id);
			cout << "reserved ! " << endl;
			ReadKey();
			CLEAR;
			return;
		}
	}
		

}

void getBack()
{
	// who is getting back ? 
	string userName;
	cout << "enter your username : " << endl;
	//cin >> userName;
	getline(cin, userName);

	// check if this user exist ...

	int userIndex = -1;

	/*for (int i = 0; i < users.get_size(); ++i)
	{
		if (users[i]->userName == userName)
		{
			userIndex = i;
			break;
		}
	}*/

	User temp_user(userName, "");

	userIndex = users.does_exist(&temp_user, [](User* a, User* b) {
		return (a->userName == b->userName);
		});

	if (userIndex == -1)
	{
		cout << "no such user" << endl;
		ReadKey();
		CLEAR;
		return;
	}



	// what do you want to return 
	string bookTitle;
	cout << "enter the title of book you want to return : " << endl;
	//cin >> bookTitle;
	getline(cin, bookTitle);

	// check if this book exist ...

	Book temp_book;
	temp_book.title = bookTitle;

	int bookIndex = -1;

	bookIndex = books.does_exist(&temp_book, [](Book* a, Book* b)->bool {
		return (a->title == b->title);
		});


	if (bookIndex == -1)
	{
		cout << "no such book exist ! " << endl;
		ReadKey();
		CLEAR;
		return;
	}

	// check if this book belongs to this person
		// if(book.borrowerId != user.Id) -> this book isn't yours

	if (books[bookIndex]->borrowerId != users[userIndex]->id)
	{
		cout << "this book is not yours ! " << endl;
		ReadKey();
		CLEAR;
		return;
	}

	// else -> book.borrowerId = -1 & book.lastAvailableDate = today

	

	// delete this book from the user list of books



	int bill = 0;

	int max_delay = BORROW_INTERVAL + (books[bookIndex]->numberOfExtensions * EXTENSION_DAYS);

	int dateDiff = Date::DateDifference(today, books[bookIndex]->lastAvailableDate);

	if (dateDiff > max_delay)
	{
		cout << "Your penalty is : " << (dateDiff - max_delay) * PENALTY_FEE << endl;
	}
	else
	{
		cout << "You returned your book";
	}


	books[bookIndex]->borrowerId = -1;
	books[bookIndex]->isAvailable = true;
	books[bookIndex]->lastAvailableDate = today;
	books[bookIndex]->numberOfExtensions = 0;

	ReadKey();
	CLEAR;
	return;

}

void extension()
{
	// who wants to extend ?

	string userName;
	cout << "enter your user name : " << endl;
	/*cin >> userName;*/
	getline(cin, userName);

	// check this user exists
		// if(users.exist(userName, predicate))
	User temp_user(userName, "");

	int userIndex = users.does_exist(&temp_user, [](User* a, User* b)->bool {
		return (a->userName == b->userName);
		});

	if (userIndex == -1)
	{
		cout << "no such user !" << endl;
		ReadKey();
		CLEAR;
		return;
	}

	string bookTitle;
	cout << "enter title of the book you want to extend : " << endl;
	//cin >> bookTitle;
	getline(cin, bookTitle);

	Book temp_book;
	temp_book.title = bookTitle;

	// check this book exists 
		// if(books.exist(bookTitle, predicate))
	int bookIndex = books.does_exist(&temp_book, [](Book* a, Book* b)->bool {
		return (a->title == b->title);
		});
	if (bookIndex == -1)
	{
		cout << "no such book ! " << endl;
		ReadKey();
		CLEAR;
		return;
	}



		
	// check this book belongs to this person
		// if(books[id].borrowerId == user.Id)
	
	if (books[bookIndex]->borrowerId != users[userIndex]->id)
	{
		cout << "this book does not belong to you ! " << endl;
		ReadKey();
		CLEAR;
		return;
	}

	// check the reserve list to be empty
		// if(books[id].reserveQueue.size() != 0) -> can't extend

	if (books[bookIndex]->reserveQueue.size() > 0)
	{
		cout << "the book is reserved can not extend ! ";
		ReadKey();
		CLEAR;
		return;
	}


	// check remaining days are less than 2

	//extend

	books[bookIndex]->numberOfExtensions++;
	cout << "book is extended ! ";
	ReadKey();
	CLEAR;
	return;
}

void admin_page()
{
	// add book
	// lend book ???
	// reserve book
	// get back book

	static const char* options[] = { "Add book","Lend Book", "Get Back Book", "Extension", "exit"};

	int option_size = sizeof(options) / sizeof(char*);


	while (true)
	{
		CLEAR;
		print_menu(options, option_size);


		int option = input_option(option_size);

		switch (option)
		{

		//add
		case 1:
			addBook();
			break;

		//lend
		case 2:

			lendBook();
			break;

		// get back
		case 3:
			getBack();
			break;
		
		// extension
		case 4:
			extension();
			break;

		// exit
		case 5:
			ReadKey();
			CLEAR;
			return;

		default:
			CLEAR;

			break;
		}


	}
}




#pragma endregion


#pragma region User
void showAllBooks()
{
	for (int i = 0; i < books.get_size(); ++i)
	{
		cout << i << ". " << books[i]->title << endl;
	}
	ReadKey();
	CLEAR;
	return;
	// add sorting later ...
}

void showMyBooks(User* user) // or giving the user itself to this function like : showMyBooks(const User& user);
{
	if (user->bookList.get_size() <= 0)
	{
		cout << "there is nothing here ... " << endl;
		ReadKey();
		CLEAR;
		return;
	}
	Book temp_book;
	auto bookList = user->bookList;

	for (int i = 0; i < bookList.get_size(); ++i)
	{
		temp_book.id = bookList[i].first;

		int bookIndex = books.does_exist(&temp_book, [](Book* a, Book* b)->bool {
			return (a->id == b->id);
			});

		if (bookIndex == -1)
		{
			// err ...
		}
		else
		{
			cout << (std::string)*books[bookIndex] << endl;
		}
	}

	ReadKey();
	CLEAR;
	return;
}

void user_page(User* user)
{
	const char* options[] = { "show books", "my books", "exit" };
	int option_size = sizeof(options) / sizeof(char*);

	while (true)
	{
		CLEAR;
		cout << "User Name : " << user->userName << endl;
		cout << "Code Meli : " << user->code << endl;
		print_menu(options, option_size);

		int option = input_option(option_size);

		switch (option)
		{
			// show all books
		case 1:

			showAllBooks();

			break;

			// show my books
		case 2:
			showMyBooks(user);
			break;
			// exit from account
		case 3:
			ReadKey();
			CLEAR;
			return;
			break;

		default:

			break;
		}
	}

}


#pragma endregion



int main()
{
	ifstream input_stream;
	ofstream output_stream;


	//check for availability of folders

	if (!fs::exists(project_path / "users"))
	{
		fs::create_directory(project_path / "users");
	}

	if (!fs::exists(project_path / "library"))
	{
		fs::create_directory(project_path / "library");
	}

	if (!fs::exists(books_path))
	{
		fs::create_directory(books_path);
	}

	if (!fs::exists(counts_path))
	{
		User::count = 1;
		Book::count = 0;

		output_stream.open(counts_path, ios_base::out);

		output_stream << User::count << endl;
		output_stream << Book::count;

		output_stream.close();

	}

	users.push_back(&Admin);

	// input data from file ... 
	
	input_stream.open(counts_path, ios_base::in);
	input_stream >> User::count;
	input_stream >> Book::count;
	input_stream.close();

	// input books
	fs::path p = books_path;
	fs::directory_iterator book_dir_iter(p);

	for (auto& elem : book_dir_iter)
	{
		//cout << elem << endl;
		input_stream.open(elem);
		Book* temp = new Book();
		input_stream >> *temp;

		books.push_back(temp);

		input_stream.close();
	}

	// input users
	fs::directory_iterator user_dir_iter(users_path);
	for (auto& elem : user_dir_iter)
	{
		input_stream.open(elem);
		User* temp = new User();
		input_stream >> *temp;
		users.push_back(temp);
		input_stream.close();
	}

	/*cout << books[0]->reserveQueue->size() << endl;
	cout << books[1]->reserveQueue->size() << endl;*/


	// enter what date is it today >


	while (true)
	{
		bool backToDatePage = false;
		cout << "enter date : (format : yyyy-mm-dd) " << endl;

		//test
		/*
		cin >> today.year;
		cin >> today.month;
		cin >> today.year;*/

		try
		{
			cin >> today;
		}
		catch (...)
		{
			exit(1);
		}



		//string inputDate;
		//getline(cin, inputDate);

		// check for validity ...


		const char* menu[] = { "login", "sign-up", "exit" };
		int option_size = sizeof(menu) / sizeof(char*);


		User* logged_in = nullptr;

		while (true)
		{
			if (backToDatePage) break;
			CLEAR;
			cout << "User count : " << User::count << endl;
			cout << "Book count : " << Book::count << endl;

			print_menu(menu, option_size);
			int option = input_option(option_size);

			switch (option)
			{
				// login
			case 1:

				logged_in = login();
				if (logged_in == nullptr)
				{
					cout << "no such user";
					ReadKey();
					CLEAR;
					break;
				}

				if (logged_in->id == 0)
				{
					admin_page();
				}
				else
				{
					user_page(logged_in);
				}

				break;


				// sign-up
			case 2:

				sign_up();

				break;
				// exit
			case 3:
				// store in file

				output_stream.open(counts_path, ios_base :: out);
				output_stream << User::count << endl;
				output_stream << Book::count;
				output_stream.close();

				for (int i = 0; i < books.get_size(); ++i)
				{
					output_stream.open((books_path / (books[i]->title + ".txt")), ios_base::out);
					output_stream << *books[i];
					output_stream.close();
				}

				for (int i = 1; i < users.get_size(); ++i)
				{
					output_stream.open((users_path / (users[i]->userName + ".txt")), ios_base::out);
					output_stream << *users[i];
					output_stream.close();
				}
				backToDatePage = true;
				CLEAR;
				break;

			default:
				CLEAR;

				break;
			}

			// input an option

			//sign up



			//login 


		}
	}

	
	
	
}
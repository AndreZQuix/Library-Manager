#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
#include <Windows.h>

using namespace std;

class Date
{
	int day;
	int month;
	int year;

public:
	Date()								// the earliest default date
	{
		day = 1;
		month = 1;
		year = 1000;
	}
	Date(int day, int month, int year)
	{
		this->day = day;
		this->month = month;
		this->year = year;

	}

	Date set_date();
	friend ostream& operator<<(ostream& out, const Date& date);
};

class Library
{
public:
	void menu();

	class Patron					// A library visitor who can rent books
	{
		string name;
		int card_number;
		int balance;

	public:
		Patron(string name, int card_number, int balance)
		{
			this->name = name;
			this->card_number = card_number;
			this->balance = balance;
		}

		void set_name(const string& name) { this->name = name; }
		string get_name() { return name; }
		int get_card_number() { return card_number; }
		void set_balance(const int& balance) { this->balance = balance; }
		int get_balance() { return balance; }
		bool check_patron_membership(const int& patron_number);
		friend bool operator==(Patron& p1, Patron& p2);
	};

	class Book
	{
	public:
		enum class GENRE
		{
			FICTION = 1, PROSE, PERIODIC, BIOGRAPHY, CHILDRENS
		};

	private:
		string name;
		string isbn;
		string author;
		bool is_available;
		GENRE genre;
		Date date;

	public:
		Book(string name, string isbn, string author, bool is_available, GENRE genre, Date date)
		{
			this->name = name;
			this->isbn = isbn;
			this->author = author;
			this->is_available = is_available;
			this->genre = genre;
			this->date = date;
		}

		bool get_availability() { return is_available; }
		void set_availability(const bool& is_available) { this->is_available = is_available; }
		friend ostream& operator<<(ostream& out, const Book& book);
	};

	struct Transaction						// A struct to keep the books the patron have rented
	{
		vector<Book> rented_books;
		Patron patron;
	};

	void set_patron();
	void change_patron_data();

	void set_book();
	void print_book();

	void rent_book(const int& b_num, const int& p_num);
	void check_library_content();
	friend ostream& operator<<(ostream& out, Library& library_manager);

protected:
	vector<Book> books;						// The list of all library books
	vector<Patron> patrons;					// The list of all library visitors
	vector<Transaction> transactions;
};

Library library_manager;
int current_year = 2021;
int membership_fee = 0;

ostream& operator<<(ostream& out, const Library::Book& book)
{
	book.name[0] == '"' ? out << book.name : out << "\"" << book.name << "\"";		// set book's name with double quotes
	out << " " << book.author << " " << book.date << " " << book.isbn << " ";
	switch (book.genre)
	{
	case Library::Book::GENRE::FICTION:
		out << "fiction";
		break;
	case Library::Book::GENRE::PROSE:
		out << "prose";
		break;
	case Library::Book::GENRE::PERIODIC:
		out << "periodic";
		break;
	case Library::Book::GENRE::BIOGRAPHY:
		out << "biography";
		break;
	case Library::Book::GENRE::CHILDRENS:
		out << "children's literature";
		break;
	}
	return out;
}

ostream& operator<<(ostream& out, Library& library_manager)
{
	for (int i = 0; i < library_manager.patrons.size(); i++)
	{
		cout << i + 1 << ". " << "Name: " << library_manager.patrons[i].get_name();
		cout << " Card number: " << library_manager.patrons[i].get_card_number();
		cout << " Balance: " << library_manager.patrons[i].get_balance() << " | MF was paid: ";
		library_manager.patrons[i].check_patron_membership(i) ? out << "YES" : out << "NO";
		cout << endl;

		for (int b = 0; b < library_manager.transactions.size(); b++)						// Check if the patron has rented books
		{
			if (library_manager.transactions[b].patron == library_manager.patrons[i])
			{
				cout << "Rented books:" << endl;
				for (int a = 0; a < library_manager.transactions[b].rented_books.size(); a++)
				{
					out << library_manager.transactions[b].rented_books[a] << endl;
				}
				cout << endl;
			}
		}
	}
	return out;
}

bool operator==(Library::Patron& p1, Library::Patron& p2)
{
	return (p1.get_name() == p2.get_name() && p1.get_card_number() == p2.get_card_number());
}

ostream& operator<<(ostream& out, const Date& date)
{
	date.day <= 9 ? out << '0' << date.day : out << date.day;
	out << '.';
	date.month <= 9 ? out << '0' << date.month : out << date.month;
	out << '.' << date.year;
	return out;
}

bool check_date(const int& day, const int& month, const int& year)
{
	if ((day < 0 || day > 31) || (month < 1 || month > 12) || (year < 1000 || year > current_year))
	{
		cout << "Incorrect date" << endl;
		return 0;
	} if ((day > 29 && month == 2) || (day > 30 && (month == 4 || month == 6 || month == 9 || month == 11)))
	{
		cout << "Incorrect date" << endl;
		return 0;
	}
	return 1;
}

Date Date::set_date()					// check the date and convert from int to Date
{
	int day;
	int month;
	int year;
	string str_date;
	while (true)
	{
		getline(cin, str_date);
		if (str_date.size() != 10)
			cout << "Incorrect date" << endl;
		else
		{
			day = (str_date[0] - '0') * 10 + (str_date[1] - '0');
			month = (str_date[3] - '0') * 10 + (str_date[4] - '0');
			year = (str_date[6] - '0') * 1000 + (str_date[7] - '0') * 100 + (str_date[8] - '0') * 10 + (str_date[9] - '0');

			if (check_date(day, month, year) == true)
			{
				return Date(day, month, year);
			}
		}
	}
}

string check_isbn()
{
	string isbn;
	while (true)
	{
		cin >> isbn;
		if (isbn.size() == 7)
		{
			for (int i = 0; i < isbn.size(); i++)
			{
				if (isbn[i] >= '0' && isbn[i] <= '9' && isbn[i + 1] == '-')
				{
					i++;
				}
				else
				{
					cout << "Incorrect ISBN" << endl;
					break;
				}
				cin.ignore();
				return isbn;
			}
		}
		else cout << "Incorrect ISBN" << endl;
	}
}

int check_genre()
{
	int genre_index = 0;
	while (true)
	{
		cin >> genre_index;
		if (genre_index >= 1 && genre_index <= 5)
		{
			return genre_index;
		}
		else
		{
			cout << "Incorrect genre number" << endl;
		}
	}
}

void Library::set_book()				// check data and convert to Book class
{
	string name;
	string isbn;
	string author;
	Library::Book::GENRE genre;
	bool is_available;
	Date date;
	int books_count = 0;

	cout << "How many books you want to add?" << endl;
	cin >> books_count;
	cin.ignore();

	for (int i = 0; i < books_count; i++)
	{
		cout << "\nWrite book's name:" << endl;
		getline(cin, name);

		cout << "\nType the book's ISBN [N-N-N-X] where N is a number, X is a number or letter:" << endl;
		isbn = check_isbn();

		cout << "\nType the author's name:" << endl;
		getline(cin, author);

		cout << "\nType the date of publishing [DD.MM.YYYY] with 0, for example: 05.01.2000" << endl;
		date.set_date();

		cout << "\nType the number of book genre: [1. FICTION; 2. PROSE; 3. PERIODIC; 4. BIOGRAPHY; 5. CHILDREN'S LITERATURE]" << endl;
		genre = Library::Book::GENRE(check_genre());

		cout << "\nIs the book available? 1 for YES; 0 for NO" << endl;
		cin >> is_available;
		cin.ignore();

		Book book = Book(name, isbn, author, is_available, genre, date);
		library_manager.books.push_back(book);
	}
}

void Library::print_book()
{
	cout << "You have " << library_manager.books.size() << " books" << endl;
	for (int i = 0; i < library_manager.books.size(); i++)
	{
		cout << i + 1 << ". " << library_manager.books[i];
		library_manager.books[i].get_availability() == true ? cout << ": available" << endl : cout << ": not available" << endl;
	}
}

void Library::set_patron()				// check data and convert to Patron class
{
	string name;
	int card_number;
	int balance;
	int patrons_count = 0;

	cout << "How many patrons you want to add to the archive?" << endl;
	cin >> patrons_count;
	cin.ignore();

	for (int i = 0; i < patrons_count; i++)
	{
		cout << "\nType patron's name:" << endl;
		getline(cin, name);

		cout << "\nType card number of a patron:" << endl;
		cin >> card_number;

		cout << "\nMoney balance for paying a membership fee in USD:" << endl;
		cin >> balance;
		cin.ignore();

		Patron patron = Patron(name, card_number, balance);
		library_manager.patrons.push_back(patron);
	}
}

void Library::rent_book(const int& b_num, const int& p_num)					// set patrons and their rented books at the transaction vector
{
	for (int i = 0; i < library_manager.transactions.size(); i++)
	{
		if (library_manager.patrons[p_num] == library_manager.transactions[i].patron)				// check if there already a patron with rented books
		{																							// if so, find it and add other rented books in vector
			library_manager.transactions[i].rented_books.push_back(library_manager.books[b_num]);
			library_manager.books[i].set_availability(false);
			cout << library_manager << endl;
			return;
		}
	}

	vector<Book> patrons_book;																		// else create new struct object
	patrons_book.push_back(library_manager.books[b_num]);
	Transaction TRANSACTION = { patrons_book, library_manager.patrons[p_num] };
	library_manager.transactions.push_back(TRANSACTION);
	library_manager.books[b_num].set_availability(false);
	cout << library_manager << endl;
}

void Library::check_library_content()					// check if there is an opportunity to rent a book
{
	while (true)
	{
		if (library_manager.patrons.size() == 0 || library_manager.books.size() == 0)
		{
			cout << "You can't give a book, you have 0 books OR 0 patrons" << endl;
			return;
		}

		library_manager.print_book();
		cout << "\nType the number of book you want to give" << endl;
		int book_number;
		cin >> book_number;
		if (book_number > library_manager.books.size() || book_number <= 0) cout << "Incorrect book number";
		else
		{
			while (true)
			{
				cout << "\n" << library_manager;
				cout << "\nType the number of patron:" << endl;
				int patron_number;
				cin >> patron_number;
				cout << endl;
				if (patron_number > library_manager.patrons.size() || patron_number <= 0)
				{
					cout << "\nIncorrect patron number";
				}
				else if (library_manager.patrons[patron_number - 1].check_patron_membership(patron_number - 1) == true && library_manager.books[book_number - 1].get_availability() == true)
				{
					library_manager.rent_book(book_number - 1, patron_number - 1);
					return;
				}
				else cout << "This book is not available OR the patron didn't pay the membership fee" << endl;
				if (library_manager.patrons.size() == 1) return;
			}
		}
	}
}

void Library::change_patron_data()
{
	cout << library_manager;
	int p_number;
	cout << "Type the number of patron:" << endl;
	while (true)
	{
		cin >> p_number;
		if (p_number > 0 && p_number <= library_manager.patrons.size())
		{
			p_number--;
			break;
		}
		else cout << "Incorrect patron's number" << endl;
	}
	cout << "\nWhat do you want to change?\n1. Name\n2. Balance\n" << endl;
	int new_balance;
	string new_name;
	switch (_getch())
	{
	case '1':
		cout << "Type the new name: " << endl;
		cin.ignore();
		getline(cin, new_name);
		library_manager.patrons[p_number].set_name(new_name);
		break;
	case '2':
		cout << "Type the new money balance: " << endl;
		cin >> new_balance;
		library_manager.patrons[p_number].set_balance(new_balance);
		break;
	default:
		cout << "Incorrect number" << endl;
	}
}

bool Library::Patron::check_patron_membership(const int& patron_number)
{
	return library_manager.patrons[patron_number].get_balance() >= membership_fee;
}

int set_membership()
{
	cout << "\nType the cost of the membership in USD:" << endl;
	cin >> membership_fee;
	return membership_fee;
}

void Library::menu()
{
	cout << "What do you need? Press the number button:" << endl;
	while (true)
	{
		cout << "\n1. Set books in library\n2. Print the list of books" << endl;
		cout << "3. Set membership fee\n4. Type a new patron\n5. Check patrons\n6. Rent a book to a patron" << endl;
		cout << "7. Change patron's data\n8. Exit\n" << endl;
		cout << "YOU HAVE " << library_manager.books.size() << " BOOKS AND " << library_manager.patrons.size() << " PATRONS" << endl;
		cout << "MEMBERSHIP FEE IS " << membership_fee << " USD" << endl;
		switch (_getch())
		{
		case '1':
			library_manager.set_book();
			system("cls");
			break;
		case '2':
			system("cls");
			library_manager.print_book();
			break;
		case '3':
			set_membership();
			system("cls");
			break;
		case '4':
			library_manager.set_patron();
			system("cls");
			break;
		case '5':
			system("cls");
			cout << library_manager;
			break;
		case '6':
			system("cls");
			library_manager.check_library_content();
			break;
		case '7':
			system("cls");
			library_manager.change_patron_data();
			cout << "Data changed" << endl;
			break;
		case '8':
			cout << "\nGoodbye!" << endl;
			exit(0);
		default:
			system("cls");
			cout << "This option doesn't exist" << endl;
			break;
		}
	}
}

int main()
{
	cout << "Hello! It's a library program" << endl;
	library_manager.menu();
}

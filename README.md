# Library-Manager
A console application to keep records of books and patrons at your library. Solution of the task from "The C++ Programming Language" by Bjarne Stroustrup.

The app keeps records of library books with information about its name, author, ISBN number, genre, date of publishing, and availability. Also, it keeps the information about visitors (patrons): their names, unique card number and balance (to pay a membership fee). Patrons can rent books: the information is keeping at transactions vector.

Program functions:
1. Set books: add books to the library.
2. Print books: print the list of all library's books.
3. Set membership fee.
4. Type a new patron: add patrons to the library.
5. Check patrons: print all the pieces of information about the patrons: names, rented books, etc.
6. Rent book to a patron: transactions vector keep records only of patrons who have any book from the library.
7. Change patron data: change patron's name or balance.

Note: library_manager is an object that keeps all library information.

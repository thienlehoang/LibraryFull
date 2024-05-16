#pragma once
#include <stdio.h>
#include <string.h>
#include <conio.h> // For _getch() function
#include <stdlib.h>
#define MAX_BOOKS 100
typedef struct {
	int isbn;
	char name[100];
	char author[100];
	char publisher[100];
	int publishingYear;
	char category[100];
	int price;
	int count;
} Book;

inline void showBookList1(Book books[MAX_BOOKS],int size) {
	printf("Book List:\n");
	printf("%-5s| %-20.20s| %-20.20s| %-20.20s| %-20s| %-20.20s| %-6s| %-5s\n", "ID", "Name", "Author", "Publisher", "Publishing Year ", "Category", "Price", "Count");
	printf("---------------------------------------------------------------------------------------------------------------------------------------\n");
	for (int i = 0; i < size; i++) {
		//printf("%-5d| %-20.20s| %-20.20s| %-20.20s| %-20d| %-20.20s| %-6d| %-5d\n", isbns[i], names[i], authors[i], publishers[i], publishingYears[i], categories[i], prices[i], counts[i]);
		printf("%-5d| %-20.20s| %-20.20s| %-20.20s| %-20d| %-20.20s| %-6d| %-5d\n", books[i].isbn, books[i].name, books[i].author, books[i].publisher, books[i].publishingYear, books[i].category, books[i].price, books[i].count);
	}
}


inline int searchBookById1(Book books[], int id, int size) {
	for (int i = 0; i < size; i++) {
		if (books[i].isbn == id) {
			return i; // Book found, return its index
		}
	}
	return -1; // Book not found
}


inline int searchBookByName1(Book books[], const char* name, int size) {
	for (int i = 0; i < size; i++) {
		if (strcmp(books[i].name,name)==0) {
			return i; // Book found, return its index
		}
	}
	return -1; // Book not found
}

inline void deleteBook1(Book books[], int *bookCount, int id) {
	int index = -1;
	// Search for the book based on the provided ID
	for (int i = 0; i < *bookCount; i++) {
		if (books[i].isbn == id) {
			index = i;
			break;
		}
	}

	if (index == -1) {
		printf("Book with ID %d not found.\n", id);
		return;
	}

	// Update the book count
	(*bookCount)--;

	// Shift elements to overwrite the deleted book
	for (int i = index; i < *bookCount; i++) {
		books[i] = books[i + 1];
	}

	// Update the file to reflect the changes
	FILE* file;
	FILE* tempFile;

	if (fopen_s(&file, "Sach.txt", "r") != 0 || fopen_s(&tempFile, "tempSach.txt", "w") != 0) {
		printf("Error opening file.\n");
		return;
	}

	char buffer[1024];
	int i = 0;
	while (fgets(buffer, sizeof(buffer), file)) {
		char* token;
		char* context = NULL;
		token = strtok_s(buffer, "|", &context);
		int currentId = atoi(token);

		if (currentId != id) {
		fprintf(tempFile, "%d|%s|%s|%s|%d|%s|%d|%d\n", books[i].isbn, books[i].name, books[i].author,
			books[i].publisher, books[i].publishingYear, books[i].category, books[i].price, books[i].count);	
		}
		i++;
	}

	fclose(file);
	fclose(tempFile);

	// Remove the original file and rename the temporary file
	remove("Sach.txt");
	rename("tempSach.txt", "Sach.txt");

	printf("Book with ID %d deleted successfully.\n", id);
}


inline void addNewBook(Book books[], int* bookCount) {
	// Check if the array is full
	if (*bookCount >= MAX_BOOKS) {
		printf("Cannot add more books. Maximum capacity reached.\n");
		return;
	}

	// Prompt the user to input the details of the new book
	printf("Enter the details of the new book:\n");
	Book newBook;
	printf("ISBN: ");
	scanf_s("%d", &newBook.isbn);
	for (int i = 0; i < *bookCount; i++) {
		if (newBook.isbn == books[i].isbn) {
			printf("Book with ID %d already exists.\n", newBook.isbn);
			return;
		}
	}
	printf("Name: ");
	getchar();
	scanf_s("%[^\n]", newBook.name, sizeof(newBook.name));

	printf("Author: ");
	getchar();
	scanf_s(" %[^\n]", newBook.author, sizeof(newBook.name));
	printf("Publisher: ");
	getchar();
	scanf_s(" %[^\n]", newBook.publisher, sizeof(newBook.publisher));
	printf("Publishing Year: ");
	scanf_s("%d", &newBook.publishingYear);
	printf("Category: ");
	getchar();
	scanf_s(" %[^\n]", newBook.category, sizeof(newBook.category));
	printf("Price: ");
	scanf_s("%d", &newBook.price);
	printf("Count: ");
	scanf_s("%d", &newBook.count);

	// Add the new book to the array of books
	books[*bookCount] = newBook;
	(*bookCount)++;

	// Add the new book to the file
	FILE* file;
	if (fopen_s(&file, "./Sach.txt", "a") != 0) {
		printf("Error opening file for reading.\n");
		return;
	}

	// Write book information to the file
	fprintf(file, "%d|%s|%s|%s|%d|%s|%d|%d\n", newBook.isbn, newBook.name, newBook.author,
		newBook.publisher, newBook.publishingYear, newBook.category, newBook.price, newBook.count);
	fflush(file);
	fclose(file); // Close the file


	printf("New book added successfully.\n");
}

inline void modifyBook1(Book books[], int bookCount, const char* filename, int id) {
	// Search for the book based on the provided ID
	int index = -1;
	index = searchBookById1(books, id, bookCount);

	if (index == -1) {
		printf("Book with ID %d not found.\n", id);
		return;
	}

	// Prompt the user to input new information for the book
	printf("Enter new information for the book:\n");
	printf("Name: ");
	getchar();
	scanf_s("%[^\n]", books[index].name, sizeof(books[index].name));
	printf("Author: ");
	getchar();
	scanf_s("%[^\n]", books[index].author, sizeof(books[index].author));

	printf("Publisher: ");
	getchar();
	scanf_s(" %[^\n]", books[index].publisher, sizeof(books[index].publisher));
	printf("Publishing Year: ");
	scanf_s("%d", &books[index].publishingYear);
	printf("Category: ");
	getchar();
	scanf_s(" %[^\n]", books[index].category, sizeof(books[index].category));
	printf("Price: ");
	scanf_s("%d", &books[index].price);
	printf("Count: ");
	scanf_s("%d", &books[index].count);
	// Add prompts for other fields as needed

	// Update the book's information in the file
	FILE* file;
	FILE* tempFile;

	if (fopen_s(&file, "./Sach.txt", "r") != 0 || fopen_s(&tempFile, "./tempSach.txt", "w") != 0) {
		printf("Error opening file.\n");
		return;
	}

	char buffer[1024];
	int i = 0;
	while (fgets(buffer, sizeof(buffer), file) && i<bookCount) {
		char* token;
		char* context = NULL; // Initialize context pointer for strtok_s
		token = strtok_s(buffer, "|", &context);
		int currentId = atoi(token); // Convert the first token to integer

		fprintf(tempFile, "%d|%s|%s|%s|%d|%s|%d|%d\n", books[i].isbn, books[i].name, books[i].author,
				books[i].publisher, books[i].publishingYear, books[i].category, books[i].price, books[i].count);
		i++;
	}

	fclose(file);
	fclose(tempFile);

	// Delete the original file and rename the temporary file
	remove("Sach.txt");
	rename("tempSach.txt", "Sach.txt");

	printf("Book information modified successfully.\n");
}

inline void thongkeSoluongSach(Book books[], int bookCount) {
	int total = 0;
	for (int i = 0; i < bookCount;i++) {
		total += books[i].count;
	}
	printf("Tong so luong sach co trong thu vien la: %d.", total);
}

inline void thongkeSoluongSachTheoTheLoai(Book books[], int bookCount, const char* theloai) {
	int total = 0;
	for (int i = 0; i < bookCount;i++) {
		if (strcmp(books[i].category, theloai) == 0) {
			total += books[i].count;
		}
	}
	printf("Tong so luong sach co trong thu vien theo the loai '%s'la: % d.", theloai, total);
}
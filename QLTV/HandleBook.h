
#include <stdio.h>
#include <string.h>
#include <conio.h> // For _getch() function
#include <stdlib.h>
#define MAX_BOOKS 100

inline void showBookList(int isbns[], char names[][100], char authors[][100], char publishers[][100], int publishingYears[], char categories[][100], int prices[], int counts[], int size) {
	printf("Book List:\n");
	printf("%-5s| %-20.20s| %-20.20s| %-20.20s| %-20s| %-20.20s| %-6s| %-5s\n", "ID", "Name", "Author", "Publisher", "Publishing Year ", "Category" , "Price" , "Count");
	printf("---------------------------------------------------------------------------------------------------------------------------------------\n");
	for (int i = 0; i < size; i++) {
		printf("%-5d| %-20.20s| %-20.20s| %-20.20s| %-20d| %-20.20s| %-6d| %-5d\n", isbns[i], names[i], authors[i], publishers[i], publishingYears[i], categories[i], prices[i], counts[i]);
	}
}

inline int searchBookById(int isbns[], int id, int size) {
	for (int i = 0; i < size; i++) {
		if (isbns[i] == id) {
			return i; // Book found, return its index
		}
	}
	return -1; // Book not found
}

inline int searchBookByName(char names[][100], const char* name, int size) {
	for (int i = 0; i < size; i++) {
		if (strcmp(names[i], name) == 0) {
			return i; // Book found, return its index
		}
	}
	return -1; // Book not found
}

inline void deleteBook(int isbns[], char names[][100], char authors[][100], char publishers[][100], int publishingYears[], char categories[][100], int prices[], int counts[], int* size, int id) {
	int index = searchBookById(isbns, id, *size);
	if (index != -1) {
		// Shift elements to overwrite the deleted book
		for (int i = index; i < *size - 1; i++) {
			isbns[i] = isbns[i + 1];
			strcpy_s(names[i], names[i + 1]);
			strcpy_s(authors[i], authors[i + 1]);
			strcpy_s(publishers[i], publishers[i+1]);
			publishingYears[i] = publishingYears[i+1];
			strcpy_s(categories[i], categories[i+1]);
			prices[i] = prices[i+1];
			counts[i] = counts[i+1];
		}
		(*size)--; // Decrement the size of the array
		printf("Book with ID %d deleted successfully.\n", id);
	}
	else {
		printf("Book with ID %d not found.\n", id);
	}
}


inline void addBook(int isbns[], char names[][100], char authors[][100], char publishers[][100], int publishingYears[], char categories[][100], int prices[], int counts[], int* size, int id, char name[], char author[], char publisher[], int publishingYear, char category[], int price, int count) {
	for (int i = 0; i < *size; i++) {
		if (isbns[i] == id) {
			printf("Book with ID %d already exists.\n", id);
			return;
		}
	}
	// Expand arrays dynamically
	isbns[*size] = id;
	strcpy_s(names[*size], name);
	strcpy_s(authors[*size], author);
	strcpy_s(publishers[*size], publisher);
	publishingYears[*size] = publishingYear;
	strcpy_s(categories[*size], category);
	prices[*size] = price;
	counts[*size] = count;
	(*size)++; // Increment the size of the array
	printf("Book added successfully.\n");
}

// Function to modify information of a book
inline void modifyBook(int isbns[], char names[][100], char authors[][100], char publishers[][100], int publishingYears[], char categories[][100], int prices[], int counts[], int size, int id) {
	// Search for the book index based on its ID
	int index = searchBookById(isbns, id, size);

	// If book not found, return
	if (index == -1) {
		printf("Book with ID %d not found.\n", id);
		return;
	}

	printf("Nhap ten sach: ");
	char newName[100];
	getchar();
	scanf_s("%[^\n]", newName, sizeof(newName));

	printf("Nhap tac gia: ");
	char newAuthor[100];
	getchar();
	scanf_s("%[^\n]", newAuthor, sizeof(newAuthor));

	printf("Nhap nha xuat ban: ");
	char newPublisher[100];
	getchar();
	scanf_s("%[^\n]", newPublisher, sizeof(newPublisher));

	printf("Nhap nam xuat ban: ");
	int newPublishingYear;
	scanf_s("%d", &newPublishingYear);

	printf("Nhap gia: ");
	int newPrice;
	scanf_s("%d", &newPrice);

	printf("Nhap so luong: ");
	int newCount;
	scanf_s("%d", &newCount);

	printf("Nhap the loai: ");
	char newCategory[100];
	getchar();
	scanf_s("%[^\n]", newCategory, sizeof(newCategory));
	newCategory[strcspn(newCategory, "\n")] = '\0';



	// Update book information
	strcpy_s(names[index], sizeof(names[index]), newName);
	strcpy_s(authors[index], sizeof(authors[index]), newAuthor);
	strcpy_s(publishers[index], newPublisher);
	publishingYears[index] = newPublishingYear;
	strcpy_s(categories[index], newCategory);
	prices[index] = newPrice;	
	counts[index] = newCount;

	printf("Book information modified successfully.\n");
}


inline void thongkeSoluongSach(int counts[100], int size) {
	int total = 0;
	for (int i = 0; i < size;i++) {
		total += counts[i];
	}
	printf("Tong so luong sach co trong thu vien la: %d.",total);
}

inline void thongkeSoluongSachTheoTheLoai(int counts[100], int size, char categories[][100], const char* theloai ) {
	int total = 0;
	for (int i = 0; i < size;i++) {
		if (strcmp(categories[i], theloai) == 0) {
			total += counts[i];
		}
	}
	printf("Tong so luong sach co trong thu vien theo the loai '%s'la: % d.",theloai, total);
}
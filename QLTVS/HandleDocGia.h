#pragma once

#include <stdio.h>
#include <string.h>
#include <conio.h> // For _getch() function
#include <stdlib.h>
#define MAX_DOCGIAS 100
typedef struct {
	int madocgia;
	char hoten[100];
	char cmnd[100];
	int ngaysinh[3]; // Array for day, month, and year
	char gioitinh[100];
	char email[100];
	char diachi[100];
	int ngaylapthe[3];
	int ngayhethan[3];
} DocGia;
inline int isLeapYear(int year) {
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// Function to get the number of days in a given month of a given year
inline int daysInMonth(int month, int year) {
	int days[] = { 31, 28 + isLeapYear(year), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	return days[month - 1];
}

// Function to add days to a given date
inline void addDays(int* day, int* month, int* year, int daysToAdd) {
	*day += daysToAdd;
	while (*day > daysInMonth(*month, *year)) {
		*day -= daysInMonth(*month, *year);
		(*month)++;
		if (*month > 12) {
			*month = 1;
			(*year)++;
		}
	}
}

inline int isValidDate(int day, int month, int year) {
	// Check if the year is valid (positive)
	if (year <= 0) {
		return 0;
	}
	// Check if the month is valid (between 1 and 12)
	if (month < 1 || month > 12) {
		return 0;
	}
	// Check if the day is valid for the given month
	if (day < 1 || day > daysInMonth(month, year)) {
		return 0;
	}
	return 1;
}

inline void showDocGiaList(int madocgias[], char hotens[][100], char cmnds[][100], int ngaysinhs[][3], char gioitinhs[][100], char emails[][100], char diachis[][100], int ngaylapthes[][3], int ngayhethans[][3], int size) {
	printf("Reader List:\n");
	printf("Ma doc gia  | Ho ten          | CMND      | Ngay thang nam sinh | Gioi tinh | Email              | Dia chi                    | Ngay lam the | Ngay het han\n");
	printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	for (int i = 0; i < size; i++) {
		printf("%-4d| %-20.20s| %-13.13s| %02d/%02d/%-8d | %-6s | %-30.30s| %-50.50s | %02d/%02d/%-8d | %02d/%02d/%-8d\n",
			madocgias[i], hotens[i], cmnds[i], ngaysinhs[i][0], ngaysinhs[i][1], ngaysinhs[i][2],
			gioitinhs[i], emails[i], diachis[i], ngaylapthes[i][0], ngaylapthes[i][1], ngaylapthes[i][2],
			ngayhethans[i][0], ngayhethans[i][1], ngayhethans[i][2]);
	}
}

inline void showDocGiaList1(DocGia docgias[], int size) {
	printf("Reader List:\n");
	printf("Ma doc gia  | Ho ten          | CMND      | Ngay thang nam sinh | Gioi tinh | Email              | Dia chi                    | Ngay lam the | Ngay het han\n");
	printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	for (int i = 0; i < size; i++) {
		printf("%-4d| %-20.20s| %-13.13s| %02d/%02d/%-8d | %-6s | %-30.30s| %-50.50s | %02d/%02d/%-8d | %02d/%02d/%-8d\n",
			docgias[i].madocgia, docgias[i].hoten, docgias[i].cmnd, docgias[i].ngaysinh[0], docgias[i].ngaysinh[1], docgias[i].ngaysinh[2],
			docgias[i].gioitinh, docgias[i].email, docgias[i].diachi, docgias[i].ngaylapthe[0], docgias[i].ngaylapthe[1], docgias[i].ngaylapthe[2],
			docgias[i].ngayhethan[0], docgias[i].ngayhethan[1], docgias[i].ngayhethan[2]);
	}
}


inline int searchDocGiaById(int madocgias[], int id, int size) {
	for (int i = 0; i < size; i++) {
		if (madocgias[i] == id) {
			return i; // Reader found, return its index
		}
	}
	return -1; // Reader not found
}
inline int searchDocGiaById1(DocGia docgias[], int id, int size) {
	for (int i = 0; i < size; i++) {
		if (docgias[i].madocgia == id) {
			return i; // Reader found, return its index
		}
	}
	return -1; // Reader not found
}

inline int searchDocGiaByCMND(DocGia docgias[], char cmnd[100], int size) {
	for (int i = 0; i < size; i++) {
		if (strcmp(docgias[i].cmnd, cmnd) == 0) {
			return i; // DocGia found, return its index
		}
	}
	return -1; // Reader not found
}

inline int searchDocGiaByName(DocGia docgias[], const char* name, int size) {
	for (int i = 0; i < size; i++) {
		if (strcmp(docgias[i].hoten, name) == 0) {
			return i; // DocGia found, return its index
		}
	}
	return -1; // DocGia not found
}

// Function to delete a reader from the list by ID
inline void deleteDocGia1(DocGia docgias[], int* docgiaCount, int id) {
	int index = -1;
	// Search for the book based on the provided ID
	index = searchDocGiaById1(docgias, id, *docgiaCount);

	if (index == -1) {
		printf("Book with ID %d not found.\n", id);
		return;
	}

	// Update the book count
	(*docgiaCount)--;

	// Shift elements to overwrite the deleted book
	for (int i = index; i < *docgiaCount; i++) {
		docgias[i] = docgias[i + 1];
	}


	// Update the file to reflect the changes
	FILE* file;
	FILE* tempFile;

	if (fopen_s(&file, "DocGia.txt", "r") != 0 || fopen_s(&tempFile, "tempSach.txt", "w") != 0) {
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
			fprintf(tempFile, "%d|%s|%s|%d/%d/%d|%s|%s|%s|%d/%d/%d|%d/%d/%d\n",
				docgias[i].madocgia, docgias[i].hoten, docgias[i].cmnd,
				docgias[i].ngaysinh[0], docgias[i].ngaysinh[1], docgias[i].ngaysinh[2],
				docgias[i].gioitinh, docgias[i].email, docgias[i].diachi,
				docgias[i].ngaylapthe[0], docgias[i].ngaylapthe[1], docgias[i].ngaylapthe[2],
				docgias[i].ngayhethan[0], docgias[i].ngaylapthe[1], docgias[i].ngaylapthe[2]);
		}
		i++;
	}

	fclose(file);
	fclose(tempFile);

	// Remove the original file and rename the temporary file
	remove("DocGia.txt");
	rename("tempSach.txt", "DocGia.txt");

	printf("Reader with ID %d deleted successfully.\n", id);
}

inline void addNewDocGia(DocGia docgias[], int* bookCount) {
	// Check if the array is full
	if (*bookCount >= MAX_DOCGIAS) {
		printf("Cannot add more books. Maximum capacity reached.\n");
		return;
	}

	// Prompt the user to input the details of the new book
	printf("Enter the details of the new book:\n");
	DocGia newDocgia;
	printf("Nhap ID doc gia muon tao moi: ");
	scanf_s("%d", &newDocgia.madocgia);
	for (int i = 0; i < *bookCount; i++) {
		if (newDocgia.madocgia == docgias[i].madocgia) {
			printf("Doc gia da ton tai.\n", newDocgia.madocgia);
			return;
		}
	}

	printf("Nhap ho ten: ");
	getchar();
	scanf_s("%[^\n]", newDocgia.hoten, sizeof(newDocgia.hoten));

	printf("Nhap cmnd: ");
	getchar();
	scanf_s("%[^\n]", newDocgia.cmnd, sizeof(newDocgia.cmnd));

	do {
		printf("Nhap ngay sinh(DD/MM/YYYY): \n");
		scanf_s("%d %d %d", &newDocgia.ngaysinh[0], &newDocgia.ngaysinh[1], &newDocgia.ngaysinh[2]);
		if (!isValidDate(newDocgia.ngaysinh[0], newDocgia.ngaysinh[1], newDocgia.ngaysinh[2])) {
			printf("Invalid date. Please enter a valid date.\n");
		}
	} while (!isValidDate(newDocgia.ngaysinh[0], newDocgia.ngaysinh[1], newDocgia.ngaysinh[2]));


	printf("Nhap gioi tinh: ");
	getchar();
	scanf_s("%[^\n]", newDocgia.gioitinh, sizeof(newDocgia.gioitinh));

	printf("Nhap email: ");
	getchar();
	scanf_s("%[^\n]", newDocgia.email, sizeof(newDocgia.email));

	printf("Nhap dia chi: ");
	getchar();
	scanf_s("%[^\n]", newDocgia.diachi, sizeof(newDocgia.diachi));

	do {
		printf("Nhap ngay lap the(DD/MM/YYYY): ");
		scanf_s("%d %d %d", &newDocgia.ngaylapthe[0], &newDocgia.ngaylapthe[1], &newDocgia.ngaylapthe[2]);
		if (!isValidDate(newDocgia.ngaylapthe[0], newDocgia.ngaylapthe[1], newDocgia.ngaylapthe[2])) {
			printf("Invalid date. Please enter a valid date.\n");
		}
	} while (!isValidDate(newDocgia.ngaylapthe[0], newDocgia.ngaylapthe[1], newDocgia.ngaylapthe[2]));

	int day = newDocgia.ngaylapthe[0];
	int month = newDocgia.ngaylapthe[1];
	int year = newDocgia.ngaylapthe[2];
	addDays(&day, &month, &year, 40);
	newDocgia.ngayhethan[0] = day;
	newDocgia.ngayhethan[1] = month;
	newDocgia.ngayhethan[2] = year;

	// Add the new book to the array of books
	docgias[*bookCount] = newDocgia;
	(*bookCount)++;

	// Add the new book to the file
	FILE* file;
	if (fopen_s(&file, "./DocGia.txt", "a") != 0) {
		printf("Error opening file for reading.\n");
		return;
	}

	// Write book information to the file
	fprintf(file, "%d|%s|%s|%d/%d/%d|%s|%s|%s|%d/%d/%d|%d/%d/%d\n", 
		newDocgia.madocgia, newDocgia.hoten, newDocgia.cmnd,
		newDocgia.ngaysinh[0], newDocgia.ngaysinh[1], newDocgia.ngaysinh[2],
		newDocgia.gioitinh, newDocgia.email, newDocgia.diachi,
		newDocgia.ngaylapthe[0], newDocgia.ngaylapthe[1], newDocgia.ngaylapthe[2],
		newDocgia.ngayhethan[0], newDocgia.ngaylapthe[1], newDocgia.ngaylapthe[2]);
		
	fflush(file);
	fclose(file); // Close the file


	printf("New book added successfully.\n");
}

// Function to modify information of a DocGia
inline void modifyDocGia1(DocGia docgias[], int docgiaCount, int id) {
	// Search for the book based on the provided ID
	int index = -1;
	index = searchDocGiaById1(docgias, id, docgiaCount);

	if (index == -1) {
		printf("Doc gia voi ID %d khong tim thay.\n", id);
		return;
	}

	// Prompt the user to input new information for the book
	printf("Nhap ho ten: ");
	getchar();
	scanf_s("%[^\n]", docgias[index].hoten, sizeof(docgias[index].hoten));

	printf("Nhap cmnd: ");
	getchar();
	scanf_s("%[^\n]", docgias[index].cmnd, sizeof(docgias[index].cmnd));

	do {
		printf("Nhap ngay sinh(DD/MM/YYYY): \n");
		scanf_s("%d %d %d", &docgias[index].ngaysinh[0], &docgias[index].ngaysinh[1], &docgias[index].ngaysinh[2]);
		if (!isValidDate(docgias[index].ngaysinh[0], docgias[index].ngaysinh[1], docgias[index].ngaysinh[2])) {
			printf("Invalid date. Please enter a valid date.\n");
		}
	} while (!isValidDate(docgias[index].ngaysinh[0], docgias[index].ngaysinh[1], docgias[index].ngaysinh[2]));


	printf("Nhap gioi tinh: ");
	getchar();
	scanf_s("%[^\n]", docgias[index].gioitinh, sizeof(docgias[index].gioitinh));

	printf("Nhap email: ");
	getchar();
	scanf_s("%[^\n]", docgias[index].email, sizeof(docgias[index].email));

	printf("Nhap dia chi: ");
	getchar();
	scanf_s("%[^\n]", docgias[index].diachi, sizeof(docgias[index].diachi));

	do {
		printf("Nhap ngay lap the(DD/MM/YYYY): ");
		scanf_s("%d %d %d", &docgias[index].ngaylapthe[0], &docgias[index].ngaylapthe[1], &docgias[index].ngaylapthe[2]);
		if (!isValidDate(docgias[index].ngaylapthe[0], docgias[index].ngaylapthe[1], docgias[index].ngaylapthe[2])) {
			printf("Invalid date. Please enter a valid date.\n");
		}
	} while (!isValidDate(docgias[index].ngaylapthe[0], docgias[index].ngaylapthe[1], docgias[index].ngaylapthe[2]));

	int day = docgias[index].ngaylapthe[0];
	int month = docgias[index].ngaylapthe[1];
	int year = docgias[index].ngaylapthe[2];
	addDays(&day, &month, &year, 40);
	docgias[index].ngayhethan[0] = day;
	docgias[index].ngayhethan[1] = month;
	docgias[index].ngayhethan[2] = year;

	// Update the book's information in the file
	FILE* file;
	FILE* tempFile;
	if (fopen_s(&file, "./DocGia.txt", "r") != 0 || fopen_s(&tempFile, "./tempSach.txt", "w") != 0) {
		printf("Error opening file.\n");
		return;
	}
	char buffer[1024];
	int i = 0;
	while (fgets(buffer, sizeof(buffer), file) && i < docgiaCount) {
		char* token;
		char* context = NULL; // Initialize context pointer for strtok_s
		token = strtok_s(buffer, "|", &context);
		int currentId = atoi(token); // Convert the first token to integer

	// Write book information to the file
		fprintf(tempFile, "%d|%s|%s|%d/%d/%d|%s|%s|%s|%d/%d/%d|%d/%d/%d\n",
			docgias[i].madocgia, docgias[i].hoten, docgias[i].cmnd,
			docgias[i].ngaysinh[0], docgias[i].ngaysinh[1], docgias[i].ngaysinh[2],
			docgias[i].gioitinh, docgias[i].email, docgias[i].diachi,
			docgias[i].ngaylapthe[0], docgias[i].ngaylapthe[1], docgias[i].ngaylapthe[2],
			docgias[i].ngayhethan[0], docgias[i].ngaylapthe[1], docgias[i].ngaylapthe[2]);
		i++;
	}
	fclose(file);
	fclose(tempFile);

	// Delete the original file and rename the temporary file
	remove("DocGia.txt");
	rename("tempSach.txt", "DocGia.txt");


	printf("Reader with id %d is modified successfully.\n",docgias[index].madocgia);
}

inline void thongkeSoluongDocGia(int sizeDocGia) {
	int total = 0;
	for (int i = 0; i < sizeDocGia;i++) {
		total += 1;
	}
	printf("Tong so luong doc gia la: %d.", total);
}

inline void thongkeSoluongDocGiaTheoGioiTinh(DocGia docgias[], char gioitinh[], int count) {
	int total = 0;
	for (int i = 0; i < count;i++) {
		if (strcmp(docgias[i].gioitinh, gioitinh) == 0) {
			total += 1;
		}
	}
	printf("Tong so luong doc gia theo gioi tinh '%s'la: % d.", gioitinh, total);
}

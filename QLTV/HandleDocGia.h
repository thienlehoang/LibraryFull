#pragma once

#include <stdio.h>
#include <string.h>
#include <conio.h> // For _getch() function
#include <stdlib.h>
#define MAX_DOCGIAS 100
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


inline int searchDocGiaById(int madocgias[], int id, int size) {
	for (int i = 0; i < size; i++) {
		if (madocgias[i] == id) {
			return i; // Reader found, return its index
		}
	}
	return -1; // Reader not found
}
inline int searchDocGiaByCMND(char cmnds[][100], char cmnd[100], int size) {
	for (int i = 0; i < size; i++) {
		if (strcmp(cmnds[i], cmnd) == 0) {
			return i; // DocGia found, return its index
		}
	}
	return -1; // Reader not found
}

inline int searchDocGiaByName(char hotens[][100], const char* name, int size) {
	for (int i = 0; i < size; i++) {
		if (strcmp(hotens[i], name) == 0) {
			return i; // DocGia found, return its index
		}
	}
	return -1; // DocGia not found
}

// Function to delete a reader from the list by ID
inline void deleteDocGia(int madocgias[], char hotens[][100], char cmnds[][100], int ngaysinhs[][3], char gioitinhs[][100], char emails[][100], char diachis[][100], int ngaylapthes[][3], int ngayhethans[][3], int* size, int id) {
	int index = searchDocGiaById(madocgias, id, *size);
	if (index != -1) {
		// Shift elements to overwrite the deleted reader
		for (int i = index; i < *size - 1; i++) {
			madocgias[i] = madocgias[i + 1];
			strcpy_s(hotens[i], hotens[i + 1]);
			strcpy_s(cmnds[i], cmnds[i + 1]);
			ngaysinhs[i][0] = ngaysinhs[i + 1][0];
			ngaysinhs[i][1] = ngaysinhs[i + 1][1];
			ngaysinhs[i][2] = ngaysinhs[i + 1][2];
			strcpy_s(gioitinhs[i], gioitinhs[i + 1]);
			strcpy_s(emails[i], emails[i + 1]);
			strcpy_s(diachis[i], diachis[i + 1]);
			ngaylapthes[i][0] = ngaylapthes[i + 1][0];
			ngaylapthes[i][1] = ngaylapthes[i + 1][1];
			ngaylapthes[i][2] = ngaylapthes[i + 1][2];
			ngayhethans[i][0] = ngayhethans[i + 1][0];
			ngayhethans[i][1] = ngayhethans[i + 1][1];
			ngayhethans[i][2] = ngayhethans[i + 1][2];
		}
		(*size)--; // Decrement the size of the array
		printf("Doc gia voi ma doc gia %d da duoc xoa thanh cong.\n", id);
	}
	else {
		printf("Doc gia voi ma doc gia %d khong tim thay.\n", id);
	}
}



inline void addDocGia(int madocgias[], char hotens[][100], char cmnds[][100], int ngaysinhs[][3], char gioitinhs[][100], char emails[][100], char diachis[][100], int ngaylapthes[][3], int ngayhethans[][3], int* size, int id, char hoten[], char cmnd[], int ngaysinh[], char gioitinh[], char email[], char diachi[], int ngaylapthe[]) {
	for (int i = 0; i < *size; i++) {
		if (madocgias[i] == id) {
			printf("Doc Gia voi ma doc gia %d da ton tai.\n", id);
			return;
		}
	}

	// Expand arrays dynamically
	madocgias[*size] = id;
	strcpy_s(hotens[*size], hoten);
	strcpy_s(cmnds[*size], sizeof(cmnds[*size]), cmnd);
	ngaysinhs[*size][0] = ngaysinh[0];
	ngaysinhs[*size][1] = ngaysinh[1];
	ngaysinhs[*size][2] = ngaysinh[2];
	strcpy_s(gioitinhs[*size], sizeof(gioitinhs[*size]), gioitinh);
	strcpy_s(emails[*size], sizeof(emails[*size]), email);
	strcpy_s(diachis[*size], sizeof(diachis[*size]), diachi);
	ngaylapthes[*size][0] = ngaylapthe[0];
	ngaylapthes[*size][1] = ngaylapthe[1];
	ngaylapthes[*size][2] = ngaylapthe[2];
	int day = ngaylapthes[*size][0];
	int month = ngaylapthes[*size][1];
	int year = ngaylapthes[*size][2];
	addDays(&day, &month, &year, 40);
	ngayhethans[*size][0] = day;
	ngayhethans[*size][1] = month;
	ngayhethans[*size][2] = year;
	(*size)++;
	printf("Doc Gia added successfully.\n");
}

// Function to modify information of a DocGia
inline void modifyDocGia(int madocgias[], char hotens[][100], char cmnds[][100], int ngaysinhs[][3], char gioitinhs[][100], char emails[][100], char diachis[][100], int ngaylapthes[][3], int ngayhethans[][3], int size, int id) {
	// Search for the DocGia index based on its ID
	int index = searchDocGiaById(madocgias, id, size);

	// If DocGia not found, return
	if (index == -1) {
		printf("Doc gia với ma doc gia %d khong tim thay.\n", id);
		return;
	}

	printf("Nhap ho ten: ");
	char newName[100];
	getchar();
	scanf_s("%[^\n]", newName, sizeof(newName));

	printf("Nhap cmnd: ");
	char newCMND[100];
	getchar();
	scanf_s("%[^\n]", newCMND, sizeof(newCMND));

	int newNgaysinh[3];
	do {
		printf("Nhap ngay sinh(DD/MM/YYYY): \n");
		scanf_s("%d %d %d", &newNgaysinh[0], &newNgaysinh[1], &newNgaysinh[2]);
		if (!isValidDate(newNgaysinh[0], newNgaysinh[1], newNgaysinh[2])) {
			printf("Invalid date. Please enter a valid date.\n");
		}
	} while (!isValidDate(newNgaysinh[0], newNgaysinh[1], newNgaysinh[2]));


	printf("Nhap gioi tinh: ");
	char newGioitinh[100];
	getchar();
	scanf_s("%[^\n]", newGioitinh, sizeof(newGioitinh));

	printf("Nhap email: ");
	char newEmail[100];
	getchar();
	scanf_s("%[^\n]", newEmail, sizeof(newEmail));

	printf("Nhap dia chi: ");
	char newDiachi[100];
	getchar();
	scanf_s("%[^\n]", newDiachi, sizeof(newDiachi));

	int newNgaylapthe[3];
	do {
		printf("Nhap ngay lap the(DD/MM/YYYY): ");
		scanf_s("%d %d %d", &newNgaylapthe[0], &newNgaylapthe[1], &newNgaylapthe[2]);
		if (!isValidDate(newNgaylapthe[0], newNgaylapthe[1], newNgaylapthe[2])) {
			printf("Invalid date. Please enter a valid date.\n");
		}
	} while (!isValidDate(newNgaylapthe[0], newNgaylapthe[1], newNgaylapthe[2]));

	
	//newNgaysinh[strcspn(newNgaysinh, "\n")] = '\0';



	// Update DocGia information
	strcpy_s(hotens[index], sizeof(hotens[index]), newName);
	strcpy_s(cmnds[index], sizeof(cmnds[index]), newCMND);
	ngaysinhs[index][0] = newNgaysinh[0];
	ngaysinhs[index][1] = newNgaysinh[1];
	ngaysinhs[index][2] = newNgaysinh[2];
	strcpy_s(gioitinhs[index], sizeof(gioitinhs[index]), newGioitinh);
	strcpy_s(emails[index], sizeof(emails[index]), newEmail);
	strcpy_s(diachis[index], sizeof(diachis[index]), newDiachi);
	ngaylapthes[index][0] = newNgaylapthe[0];
	ngaylapthes[index][1] = newNgaylapthe[1];
	ngaylapthes[index][2] = newNgaylapthe[2];
	int day = ngaylapthes[index][0];
	int month = ngaylapthes[index][1];
	int year = ngaylapthes[index][2];
	addDays(&day, &month, &year, 40);
	ngayhethans[index][0] = day;
	ngayhethans[index][1] = month;
	ngayhethans[index][2] = year;

	printf("Doc gia with id %d information modified successfully.\n",id);
}

inline void thongkeSoluongDocGia(int sizeDocGia) {
	int total = 0;
	for (int i = 0; i < sizeDocGia;i++) {
		total += 1;
	}
	printf("Tong so luong doc gia la: %d.", total);
}

inline void thongkeSoluongDocGiaTheoGioiTinh( int size, char gioitinhs[][100], char gioitinh[]) {
	int total = 0;
	for (int i = 0; i < size;i++) {
		if (strcmp(gioitinhs[i], gioitinh) == 0) {
			total += 1;
		}
	}
	printf("Tong so luong doc gia theo gioi tinh '%s'la: % d.", gioitinh, total);
}

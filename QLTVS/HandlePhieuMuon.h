#include <stdio.h>
#include <stdbool.h>
#include "HandleDocGia.h"
#include "HandleBook.h"

#define MAX_BORROW_RECORDS 100
#define MAX_ISBN_LENGTH 20

// Các mảng lưu trữ thông tin mượn sách
//int madocgias[MAX_BORROW_RECORDS];
//int isbnList[MAX_BORROW_RECORDS][MAX_ISBN_LENGTH];
//int ngaymuon[MAX_BORROW_RECORDS][3]; // ngay muon
//int dueDates[MAX_BORROW_RECORDS][3];
//int actualReturnDates[MAX_BORROW_RECORDS][3];
//int borrowRecordCount = 0;
typedef struct 
{
	int borrowRecordReaderIds;
	int borrowRecordBookISBNs;
	int ngaymuon[3];
	int ngaydukientra[3];
} PhieuMuon;

// ham xem danh sach phieu muon sach
inline void xemPhieuMuonSach(int borrowRecordReaderIds[], int borrowRecordBookISBNs[], int ngaymuon[][3], int ngaydukientra[100][3], int borrowRecordCount) {
	printf("%-5s| %-20.20s| %-20.20s| %-20.20s\n", "Ma doc gia", "Ma sach", "Ngay muon", "Ngay du kien tra");
	printf("---------------------------------------------------------------------------------------------------------------------------------------\n");
	for (int i = 0; i < borrowRecordCount; i++) {
		printf("%-5d| %-20d | %02d/%02d/%-8d| %02d/%02d/%-8d |", borrowRecordReaderIds[i], borrowRecordBookISBNs[i], ngaymuon[i][0], ngaymuon[i][1], ngaymuon[i][2], ngaydukientra[i][0], ngaydukientra[i][1], ngaydukientra[i][2]);
	}
}
inline void xemPhieuMuonSach1(PhieuMuon phieumuons[], int borrowRecordCount) {
	printf("%-5s| %-20.20s| %-20.20s| %-20.20s\n", "Ma doc gia", "Ma sach", "Ngay muon", "Ngay du kien tra");
	printf("---------------------------------------------------------------------------------------------------------------------------------------\n");
	for (int i = 0; i < borrowRecordCount; i++) {
		printf("%-5d| %-20d | %02d/%02d/%-8d| %02d/%02d/%-8d\n", phieumuons[i].borrowRecordReaderIds, phieumuons[i].borrowRecordBookISBNs, phieumuons[i].ngaymuon[0], phieumuons[i].ngaymuon[1], phieumuons[i].ngaymuon[2], phieumuons[i].ngaydukientra[0], phieumuons[i].ngaydukientra[1], phieumuons[i].ngaydukientra[2]);
	}
}
inline int searchBorrowById(int array[], int id, int size) {
	for (int i = 0; i < size; i++) {
		if (array[i] == id) {
			return i; // Book found, return its index
		}
	}
	return -1; // Book not found
}
inline int searchBorrowById1(PhieuMuon phieumuons[], int option, int sizeofArray, int maid) {
	int result = -1;
	for (int i = 0; i < sizeofArray; i++) {
		if (option == 0) {
			//search docgia
			if (phieumuons[i].borrowRecordReaderIds == maid) {
				result = i;
				break;
			}
		}
		else if (option == 1) {
			//search book
			if (phieumuons[i].borrowRecordBookISBNs == maid) {
				result = i;
				break;
			}
		}
	}
	return result;
}

inline int checkvalidReturnDate(int returnDate[3], PhieuMuon phieumuon) {
	// ngay tra < duedate => -1
	// ngay tra nam trong pham vi : => 1
	// ngay tra nam ngoai pham vi: => 2
	if (returnDate[2] < returnDate[2] ||
		(returnDate[2] == phieumuon.ngaymuon[2] && returnDate[1] < phieumuon.ngaymuon[1]) ||
		(returnDate[2] == phieumuon.ngaymuon[2] && returnDate[1] == phieumuon.ngaymuon[1] && returnDate[0] < phieumuon.ngaymuon[0])) {
		printf("Loi: Ngay tra thuc te khong the som hon ngay muon. Vui long nhap lai.\n");
		return -1;
	}
	int daysDifference = 0;
	daysDifference += (returnDate[2] - phieumuon.ngaymuon[2]) * 365; // Số ngày trong năm
	daysDifference += (returnDate[1] - phieumuon.ngaymuon[1]) * 30;  // Số ngày trong tháng (ước lượng)
	daysDifference += (returnDate[0] - phieumuon.ngaymuon[0]);        // Số ngày trong tháng

	// Kiểm tra xem số ngày giữa dueDates và actualReturnDates có lớn hơn 7 không
	if (daysDifference > 7) {
		//printf("Loi: Ngay tra thuc te qua han. Vui long nhap lai.\n");
		return daysDifference;
	}
	else return 1;
}
inline void deleteBorrowReader(int borrowRecordReaderIds[], int borrowRecordBookISBNs[100], int ngaymuon[][3], int ngaydukientra[100][3], int* borrowRecordCount, int id) {
	int index = searchBorrowById(borrowRecordReaderIds, id, *borrowRecordCount);
	if (index != -1) {
		// Shift elements to overwrite the deleted book
		for (int i = index; i < *borrowRecordCount - 1; i++) {
			borrowRecordReaderIds[i] = borrowRecordReaderIds[i + 1];
			borrowRecordBookISBNs[i] = borrowRecordBookISBNs[i + 1];
			ngaymuon[i][0] = ngaymuon[i + 1][0];
			ngaymuon[i][1] = ngaymuon[i + 1][1];
			ngaymuon[i][2] = ngaymuon[i + 1][2];
			ngaydukientra[i][0] = ngaydukientra[i + 1][0];
			ngaydukientra[i][1] = ngaydukientra[i + 1][1];
			ngaydukientra[i][2] = ngaydukientra[i + 1][2];
		}
		(*borrowRecordCount)--; // Decrement the size of the array
	}
	else {
		printf("Thong tin khong phu hop.\n", id);
	}
}
inline void deleteBorrowReader1(PhieuMuon phieumuons[], int* borrowRecordCount, int id) {
	int index = searchBorrowById1(phieumuons,0, *borrowRecordCount,id);
	(*borrowRecordCount)--; // Decrement the size of the array
	if (index != -1) {
		// Shift elements to overwrite the deleted book
		for (int i = index; i < *borrowRecordCount; i++) {
			phieumuons[i] = phieumuons[i + 1];
		}

		xemPhieuMuonSach1(phieumuons, *borrowRecordCount);

		FILE* file;
		FILE* tempFile;

		if (fopen_s(&file, "./PhieuMuon.txt", "r") != 0 || fopen_s(&tempFile, "./tempSach.txt", "w") != 0) {
			printf("Error opening file.\n");
			return;
		}

		char buffer[1024];
		int i = 0;
		while (fgets(buffer, sizeof(buffer), file) && i < *borrowRecordCount) {
			char* token;
			char* context = NULL; // Initialize context pointer for strtok_s
			token = strtok_s(buffer, "|", &context);
			int currentId = atoi(token); // Convert the first token to integer
			fprintf(tempFile, "%d|%d|%d/%d/%d|%d/%d/%d\n",
				phieumuons[i].borrowRecordReaderIds, phieumuons[i].borrowRecordBookISBNs,
				phieumuons[i].ngaymuon[0],
				phieumuons[i].ngaymuon[1],
				phieumuons[i].ngaymuon[2],
				phieumuons[i].ngaydukientra[0],
				phieumuons[i].ngaydukientra[1],
				phieumuons[i].ngaydukientra[2]);
			i++;
		}

		fclose(file);
		fclose(tempFile);
		remove("PhieuMuon.txt");
		rename("tempSach.txt", "PhieuMuon.txt");
		printf("Thong tin da cap nhat vao file.\n", id);
	}
	else {
		printf("Thong tin khong phu hop.\n", id);
	}
}


//inline bool validateDocGia(int array[], int sizeofArray, int maid) {
//	bool result = false;;
//	for (int i = 0; i < sizeofArray; i++) {
//		if (array[i] == maid) {
//			result = true;
//			break;
//		}
//	}
//	return result;
//}

inline bool validateDocGia1(DocGia docgias[], int sizeofArray, int maid) {
	bool result = false;;
	for (int i = 0; i < sizeofArray; i++) {
		if (docgias[i].madocgia == maid) {
			result = true;
			break;
		}
	}
	return result;
}
inline bool validateSach1(Book books[], int sizeofArray, int maid) {
	bool result = false;;
	for (int i = 0; i < sizeofArray; i++) {
		if (books[i].isbn == maid) {
			result = true;
			break;
		}
	}
	return result;
}

inline int findSachPrice(Book books[], int sizeofArray, int maid) {
	int result = 0;
	for (int i = 0; i < sizeofArray; i++) {
		if (books[i].isbn == maid) {
			result = books[i].price;
			break;
		}
	}
	return result;
}




// Hàm lập phiếu mượn sách
inline void lapPhieuMuonSach1(PhieuMuon phieumuons[], int* phieumuonCount, DocGia docgias[], Book books[], int size, int docgiacount) {
	// Kiểm tra xem số lượng phiếu mượn đã đạt tối đa chưa
	if (*phieumuonCount >= MAX_BORROW_RECORDS) {
		printf("Khong the tao them phieu muon vi da dat so luong toi da.\n");
		return;
	}

	// Lập phiếu mượn sách
	printf("Nhap thong tin muon sach:\n");

	//nhap id sach
	printf("Nhap ISBN cua sach muon\n");
	do {
		scanf_s("%d", &phieumuons[*phieumuonCount].borrowRecordBookISBNs);

		if (!validateSach1(books, size, phieumuons[*phieumuonCount].borrowRecordBookISBNs)) {
			printf("Ma sach khong ton tai. Hay nhap lai. \n");
		}
	} while (!validateSach1(books, size, phieumuons[*phieumuonCount].borrowRecordBookISBNs));

	//nhap thong tin ma doc gia
	do {
		printf("Nhap ma doc gia: ");
		scanf_s("%d", &phieumuons[*phieumuonCount].borrowRecordReaderIds);

		if (!validateDocGia1(docgias, docgiacount, phieumuons[*phieumuonCount].borrowRecordReaderIds)) {
			printf("Ma doc gia khong ton tai. Hay nhap lai. \n");
		}
	} while (!validateDocGia1(docgias, docgiacount, phieumuons[*phieumuonCount].borrowRecordReaderIds));

	//nhap ngay muon sach
	do {
		printf("Nhap ngay muon(DD/MM/YYYY): \n");
		scanf_s("%d %d %d", &phieumuons[*phieumuonCount].ngaymuon[0], &phieumuons[*phieumuonCount].ngaymuon[1], &phieumuons[*phieumuonCount].ngaymuon[2]);
		if (!isValidDate(phieumuons[*phieumuonCount].ngaymuon[0], phieumuons[*phieumuonCount].ngaymuon[1], phieumuons[*phieumuonCount].ngaymuon[2])) {
			printf("Invalid date. Please enter a valid date.\n");
		}
	} while (!isValidDate(phieumuons[*phieumuonCount].ngaymuon[0], phieumuons[*phieumuonCount].ngaymuon[1], phieumuons[*phieumuonCount].ngaymuon[2]));
	//scanf_s("%d %d %d", &phieumuons[*phieumuonCount].ngaymuon[0], &ngaymuon[*phieumuonCount][1], &ngaymuon[*phieumuonCount][2]);

	int day = phieumuons[*phieumuonCount].ngaymuon[0];
	int month = phieumuons[*phieumuonCount].ngaymuon[1];
	int year = phieumuons[*phieumuonCount].ngaymuon[2];
	addDays(&day, &month, &year, 7);
	phieumuons[*phieumuonCount].ngaydukientra[0] = day;
	phieumuons[*phieumuonCount].ngaydukientra[1] = month;
	phieumuons[*phieumuonCount].ngaydukientra[2] = year;


	// Tăng số lượng phiếu mượn
	FILE* file;
	if (fopen_s(&file, "./PhieuMuon.txt", "a") != 0) {
		printf("Error opening file for reading.\n");
		return;
	}

	// Write book information to the file
	fprintf(file, "%d|%d|%d/%d/%d|%d/%d/%d\n",
		phieumuons[*phieumuonCount].borrowRecordReaderIds, phieumuons[*phieumuonCount].borrowRecordBookISBNs,
		phieumuons[*phieumuonCount].ngaymuon[0], 
		phieumuons[*phieumuonCount].ngaymuon[1], 
		phieumuons[*phieumuonCount].ngaymuon[2],
		phieumuons[*phieumuonCount].ngaydukientra[0],
		phieumuons[*phieumuonCount].ngaydukientra[1],
		phieumuons[*phieumuonCount].ngaydukientra[2]);

	fflush(file);
	fclose(file); // Close the file
	(*phieumuonCount)++;
	printf("count:%d\n", *phieumuonCount);
	xemPhieuMuonSach1(phieumuons, *phieumuonCount);


	printf("Tao phieu muon sach thanh cong.\n");
}


//Hàm lập phiếu tra sach
inline void lapPhieuTraSach1(PhieuMuon phieumuons[], int* phieumuonCount, DocGia docgias[], Book books[], int bookCount, int docgiaCount) {
	// Kiểm tra xem số lượng phiếu mượn đã đạt tối đa chưa
	//if (borrowRecordCount >= MAX_BORROW_RECORDS) {
	//    printf("Khong the tao them phieu muon vi da dat so luong toi da.\n");
	//    return;
	//}

	// Lập phiếu mượn sách
Lapphieutrasach:
	printf("Nhap thong tin tra sach:\n");

	int idSach;
	printf("Nhap ISBN cua sach:");
	do {
		scanf_s("%d", &idSach);

		if (!validateSach1(books, bookCount, idSach)) {
			printf("Ma sach khong ton tai. Hay nhap lai. \n");
		}
	} while (!validateSach1(books, bookCount, idSach));

	//nhap thong tin ma doc gia
	int idDocGia;
	do {
		printf("Nhap ma doc gia: ");
		scanf_s("%d", &idDocGia);

		if (!validateDocGia1(docgias, docgiaCount, idDocGia)) {
			printf("Ma doc gia khong ton tai. Hay nhap lai. \n");
		}
	} while (!validateDocGia1(docgias, docgiaCount, idDocGia));

	//nhap ngay tra sach


	bool validateData = false;
	int index = -1;
	//printf("doc gia id:%d %d", searchBorrowById(borrowRecordReaderIds, idDocGia, sizeDocGia), searchBorrowById(borrowRecordBookISBNs, idSach, size));
	if (searchBorrowById1(phieumuons, 0, *phieumuonCount, idDocGia) != -1 && searchBorrowById1(phieumuons, 1, *phieumuonCount, idSach) != -1) {
		printf("nguoi muon ids: %d", searchBorrowById1(phieumuons, 0, *phieumuonCount, idDocGia));
		if (searchBorrowById1(phieumuons, 0, *phieumuonCount, idDocGia) == searchBorrowById1(phieumuons, 1, *phieumuonCount, idSach)) {
			validateData = true;
			index = searchBorrowById1(phieumuons, 1, *phieumuonCount, idSach);
		}
	}
	if (validateData) {
		int matsach;
		printf("Neu lam mat sach, nhap 1, khong thi nhap 0\n");
		do {
			scanf_s("%d", &matsach);
			if (matsach == 0 || matsach == 1) {
				if (matsach == 1) {
					//xu li truong hop mat sach. phat 200% gia sach
					// xu li: tim sach => tim duoc gia sach => tinh tien phat
					books[index].count--;
					FILE* file;
					FILE* tempFile;

					if (fopen_s(&file, "./Sach.txt", "r") != 0 || fopen_s(&tempFile, "./tempSach.txt", "w") != 0) {
						printf("Error opening file.\n");
						return;
					}

					char buffer[1024];
					int i = 0;
					while (fgets(buffer, sizeof(buffer), file) && i < bookCount) {
						char* token;
						char* context = NULL; // Initialize context pointer for strtok_s
						token = strtok_s(buffer, "|", &context);
						int currentId = atoi(token); // Convert the first token to integer

						if (i == index) {

						}
						fprintf(tempFile, "%d|%s|%s|%s|%d|%s|%d|%d\n", books[i].isbn, books[i].name, books[i].author,
							books[i].publisher, books[i].publishingYear, books[i].category, books[i].price, books[i].count);
						i++;
					}

					fclose(file);
					fclose(tempFile);
					remove("Sach.txt");
					rename("tempSach.txt", "Sach.txt");

					printf("Ban da lam mat sach. Ban se bi phat %d dong\n", findSachPrice(books, bookCount, idSach) * 2);
					deleteBorrowReader1(phieumuons,phieumuonCount,idDocGia);
				}
				else {
					//xu li sach khong bi mat
					int ngaytra[3];
					//printf("Nhap ngay tra (dd mm yyyy): ");
					//scanf_s("%d %d %d", &ngaytra[0], &ngaytra[1], &ngaytra[2]);
					do {
						printf("Nhap ngay tra(DD/MM/YYYY): \n");
						scanf_s("%d %d %d", &ngaytra[0], &ngaytra[1], &ngaytra[2]);
						if (!isValidDate(ngaytra[0], ngaytra[1], ngaytra[2])) {
							printf("Invalid date. Please enter a valid date.\n");
						}
					} while (!isValidDate(ngaytra[0], ngaytra[1], ngaytra[2]) && checkvalidReturnDate(ngaytra, phieumuons[index]) == -1);
					if (checkvalidReturnDate(ngaytra,phieumuons[index]) == 1) {
						// neu nam trong khoang cho phep
						printf("Sach da duoc tra thanh cong trong thoi gian cho phep\n");
					}
					else {
						int soNgayTre = checkvalidReturnDate(ngaytra, phieumuons[index]);
						printf("Da qua thoi han cho phep. Xin vui long nop phat %d dong\n", (soNgayTre - 7) * 5000);
					}

					deleteBorrowReader1(phieumuons, phieumuonCount, idDocGia);
				}
			}
			else {
				printf("Gia tri khong hop le vui long nhap lai\n");
			}
		} while (matsach != 0 && matsach != 1);
		printf("Tao phieu tra sach thanh cong.\n");
	}
	else {
		printf("Thong tin nguoi muon va id sach khong co trong danh sach muon. Ban co muon nhap lai hay khong. Co nhan 1. Nhan bat ky nut khac de thoat");
		char choice;
		choice = _getch();
		if (choice == '1') {
			goto Lapphieutrasach;
		}
	}

	//xemPhieuMuonSach( borrowRecordReaderIds,  borrowRecordBookISBNs,  ngaymuon,  ngaydukientra,  borrowRecordCount);
}




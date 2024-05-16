#include <stdio.h>
#include <stdbool.h>
#include "HandleDocGia.h"

#define MAX_BORROW_RECORDS 100
#define MAX_ISBN_LENGTH 20

// Các mảng lưu trữ thông tin mượn sách
//int madocgias[MAX_BORROW_RECORDS];
//int isbnList[MAX_BORROW_RECORDS][MAX_ISBN_LENGTH];
//int ngaymuon[MAX_BORROW_RECORDS][3]; // ngay muon
//int dueDates[MAX_BORROW_RECORDS][3];
//int actualReturnDates[MAX_BORROW_RECORDS][3];
//int borrowRecordCount = 0;

// ham xem danh sach phieu muon sach
inline void xemPhieuMuonSach(int borrowRecordReaderIds[], int borrowRecordBookISBNs[], int ngaymuon[][3], int ngaydukientra[100][3], int borrowRecordCount) {
    printf("%-5s| %-20.20s| %-20.20s| %-20.20s\n", "Ma doc gia", "Ma sach", "Ngay muon","Ngay du kien tra");
    printf("---------------------------------------------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < borrowRecordCount; i++) {
        printf("%-5d| %-20d | %02d/%02d/%-8d| %02d/%02d/%-8d |", borrowRecordReaderIds[i], borrowRecordBookISBNs[i], ngaymuon[i][0], ngaymuon[i][1], ngaymuon[i][2], ngaydukientra[i][0], ngaydukientra[i][1], ngaydukientra[i][2]);
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

inline int checkvalidReturnDate(int returnDate[3],int dueDate[3]) {
	// ngay tra < duedate => -1
	// ngay tra nam trong pham vi : => 1
	// ngay tra nam ngoai pham vi: => 2
	if (returnDate[2] < returnDate[2] ||
		(returnDate[2] == dueDate[2] && returnDate[1] < dueDate[1]) ||
		(returnDate[2] == dueDate[2] && returnDate[1] == dueDate[1] && returnDate[0] < dueDate[0])) {
		printf("Loi: Ngay tra thuc te khong the som hon ngay muon. Vui long nhap lai.\n");
		return -1;
	}
	int daysDifference = 0;
	daysDifference += (returnDate[2] - returnDate[2]) * 365; // Số ngày trong năm
	daysDifference += (returnDate[1] - dueDate[1]) * 30;  // Số ngày trong tháng (ước lượng)
	daysDifference += (returnDate[0] - dueDate[0]);        // Số ngày trong tháng

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

inline bool validateDocGia(int array[], int sizeofArray, int maid) {
	bool result = false;;
	for (int i = 0; i < sizeofArray; i++) {
		if (array[i] == maid) {
			result = true;
			break;
		}
	}
	return result;
}
// Hàm lập phiếu mượn sách
inline void lapPhieuMuonSach(int borrowRecordReaderIds[], int borrowRecordBookISBNs[], int ngaymuon[][3], int ngaydukientra[100][3], int *borrowRecordCount, int madocgias[], int isbns[], int size, int sizeDocGia) {
	// Kiểm tra xem số lượng phiếu mượn đã đạt tối đa chưa
	if (*borrowRecordCount >= MAX_BORROW_RECORDS) {
		printf("Khong the tao them phieu muon vi da dat so luong toi da.\n");
		return;
	}

	// Lập phiếu mượn sách
	printf("Nhap thong tin muon sach:\n");

	//nhap id sach
	printf("Nhap ISBN cua sach muon\n");
	do {
		scanf_s("%d", &borrowRecordBookISBNs[*borrowRecordCount]);

		if (!validateDocGia(isbns, size, borrowRecordBookISBNs[*borrowRecordCount])) {
			printf("Ma sach khong ton tai. Hay nhap lai. \n");
		}
	} while (!validateDocGia(isbns, size, borrowRecordBookISBNs[*borrowRecordCount]));

	//nhap thong tin ma doc gia
	do {
		printf("Nhap ma doc gia: ");
		scanf_s("%d", &borrowRecordReaderIds[*borrowRecordCount]);

		if (!validateDocGia(madocgias, sizeDocGia, borrowRecordReaderIds[*borrowRecordCount])) {
			printf("Ma doc gia khong ton tai. Hay nhap lai. \n");
		}
	} while (!validateDocGia(madocgias, sizeDocGia, borrowRecordReaderIds[*borrowRecordCount]));

	//nhap ngay muon sach
	printf("Nhap ngay muon (dd/mm/yyyy): ");
	scanf_s("%d %d %d", &ngaymuon[*borrowRecordCount][0], &ngaymuon[*borrowRecordCount][1], &ngaymuon[*borrowRecordCount][2]);

	int day = ngaymuon[*borrowRecordCount][0];
	int month = ngaymuon[*borrowRecordCount][1];
	int year = ngaymuon[*borrowRecordCount][2];
	addDays(&day, &month, &year, 7);
	ngaydukientra[*borrowRecordCount][0] = day;
	ngaydukientra[*borrowRecordCount][1] = month;
	ngaydukientra[*borrowRecordCount][2] = year;


	// Tăng số lượng phiếu mượn
	(*borrowRecordCount)++;
	printf("count:%d\n", *borrowRecordCount);
	xemPhieuMuonSach( borrowRecordReaderIds,  borrowRecordBookISBNs,  ngaymuon,  ngaydukientra, *borrowRecordCount);
	printf("Tao phieu muon sach thanh cong.\n");
}


//Hàm lập phiếu tra sach
inline void lapPhieuTraSach(int borrowRecordReaderIds[], int borrowRecordBookISBNs[100], int ngaymuon[][3], int ngaydukientra[100][3], int* borrowRecordCount, int madocgias[], int isbns[],int counts[], int prices[], int size, int sizeDocGia) {
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

		if (!validateDocGia(isbns, size, idSach)) {
			printf("Ma sach khong ton tai. Hay nhap lai. \n");
		}
	} while (!validateDocGia(isbns, size, idSach));

	//nhap thong tin ma doc gia
	int idDocGia;
	do {
		printf("Nhap ma doc gia: ");
		scanf_s("%d", &idDocGia);

		if (!validateDocGia(madocgias, sizeDocGia, idDocGia)) {
			printf("Ma doc gia khong ton tai. Hay nhap lai. \n");
		}
	} while (!validateDocGia(madocgias, sizeDocGia, idDocGia));

	//nhap ngay tra sach


	bool validateData = false;
	int index = -1;
	//printf("doc gia id:%d %d", searchBorrowById(borrowRecordReaderIds, idDocGia, sizeDocGia), searchBorrowById(borrowRecordBookISBNs, idSach, size));
	if (searchBorrowById(borrowRecordReaderIds, idDocGia, *borrowRecordCount)!=-1 && searchBorrowById(borrowRecordBookISBNs, idSach, *borrowRecordCount)!=-1) {
		printf("nguoi muon ids: %d", searchBorrowById(borrowRecordReaderIds, idDocGia, sizeDocGia));
		if (searchBorrowById(borrowRecordReaderIds, idDocGia, sizeDocGia) == searchBorrowById(borrowRecordBookISBNs, idSach, size)) {
			validateData = true;
			index = searchBorrowById(isbns, idSach, size);
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
					counts[index]--;
					printf("Ban da lam mat sach. Ban se bi phat %d dong\n", prices[index]*2);
					deleteBorrowReader(borrowRecordReaderIds, borrowRecordBookISBNs, ngaymuon, ngaydukientra, borrowRecordCount, idDocGia);
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
					} while (!isValidDate(ngaytra[0], ngaytra[1], ngaytra[2]) && checkvalidReturnDate(ngaytra,ngaymuon[searchBorrowById(borrowRecordReaderIds, idDocGia, sizeDocGia)])==-1);
					if (checkvalidReturnDate(ngaytra, ngaymuon[searchBorrowById(borrowRecordReaderIds, idDocGia, sizeDocGia)]) == 1) {
						// neu nam trong khoang cho phep
						printf("Sach da duoc tra thanh cong trong thoi gian cho phep\n");
					}
					else {
						printf("Da qua thoi han cho phep. Xin vui long nop phat %d dong\n", (checkvalidReturnDate(ngaytra, ngaymuon[searchBorrowById(borrowRecordReaderIds, idDocGia, sizeDocGia)]) - 7)*5000);
					}
					deleteBorrowReader(borrowRecordReaderIds, borrowRecordBookISBNs, ngaymuon, ngaydukientra, borrowRecordCount, idDocGia);
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




#include <stdio.h>
#include <string.h>
#include <conio.h> // For _getch() function
#include <stdlib.h>
#include "HandleBook.h"
#include "HandleDocGia.h"
#include "HandlePhieuMuon.h"

#define MAX_BORROW_RECORDS 100

int main() {
	// Example list of books
	int isbns[] = { 1, 2, 3, 4 };
	char names[MAX_BOOKS][100] = { "The Great Gatsby", "To Kill a Mockingbird", "1984", "Pride and Prejudice" };
	char authors[MAX_BOOKS][100] = { "F. Scott Fitzgerald", "Harper Lee", "George Orwell", "Jane Austen" };
	char publishers[MAX_BOOKS][100] = { "publishers1","publishers2","publishers3","publishers4" };
	int publishingYears[MAX_BOOKS] = { 1999,2000,2001,1998 };
	char categories[MAX_BOOKS][100] = { "trinh tham","truyen ma","ngon tinh","tieu thuyet" };
	int prices[MAX_BOOKS] = { 100000,200000,340000,80000 };
	int counts[MAX_BOOKS] = { 4,100,50,2 };


	//Example list cho DOCGIA:
	int madocgias[] = { 1, 2, 3, 4 };
	char hotens[MAX_DOCGIAS][100] = { "The Great Gatsby", "To Kill a Mockingbird", "1984", "Pride and Prejudice" };
	char cmnds[MAX_DOCGIAS][100] = { "082200000199", "083300000199", "12300202", "092200000188" };
	int ngaysinhs[MAX_DOCGIAS][3] = { {12,12,2000},{9,11,2000},{11,02,1999},{27,10,2004} };
	char gioitinhs[MAX_DOCGIAS][100] = { "nam","nu","nam","nam" };
	char emails[MAX_DOCGIAS][100] = { "truyen@gmail.com","ykhoa@gmail.com","dxc@gmail.com","90mlink@gmail.com" };
	char diachis[MAX_DOCGIAS][100] = { "58 Hoa Bang, Tan Quy, Tan Phu","123 Cach Mang Thang 8, p 13, Tan Binh","13 Tan Ky Tan Quy, Tan Quy, Tan Phu","khong ro" };
	int ngaylapthes[MAX_DOCGIAS][3] = { {12,12,2000},{12,11,2010},{11,02,2009},{17,10,2014} };
	int ngayhethans[MAX_DOCGIAS][3] = { {21,1,2001},{22,12,2010},{23,03,2009},{26,11,2014} };


	int borrowRecordReaderIds[MAX_BORROW_RECORDS]; // Mảng lưu trữ mã độc giả của các phiếu mượn sách
	int borrowRecordBookISBNs[MAX_BORROW_RECORDS]; // Mảng lưu trữ ISBN của sách được mượn trong các phiếu mượn sách
	int ngaymuon[MAX_BORROW_RECORDS][3]; // Mảng lưu trữ ngày mượn của các phiếu mượn sách
	int ngaydukientra[MAX_BORROW_RECORDS][3]; // Mảng lưu trữ ngày trả dự kiến của các phiếu mượn sách

	int givebackRecordReaderIds[MAX_BORROW_RECORDS]; // Mảng lưu trữ mã độc giả của các phiếu mượn sách



	int borrowRecordCount = 0; // Số lượng phiếu mượn sách hiện tại
	int soluongSachMuon = 0;
	int givebackCount = 0; // Số lượng phiếu trả sách hiện tại


	// Calculate the size of the arrays
	int size = sizeof(isbns) / sizeof(isbns[0]);
	int sizeDocGia = 4;


	char choice;
	do {
		// Display menu
	Menu:
		system("cls");
		printf("\nMenu:\n");
		printf("1. Quan li sach\n");
		printf("2. Quan li doc gia\n");
		printf("3. Lap phieu muon sach\n");
		printf("4. Lap phieu tra sach\n");
		printf("5. Cac thong ke co ban\n");
		printf("Press Esc to exit\n");
		printf("Press your choice: ");
		//scanf_s(" %c", &choice);
		choice = _getch();

		switch (choice) {
		case '1': {
			// Display the menu of book handle
		BookMenu:
			system("cls");
			printf("\nThao tac voi sach:\n");
			printf("1. Xem danh sach cac sach trong thu vien\n");
			printf("2. Them sach\n");
			printf("3. Chinh sua thong tin mot quyen sach\n");
			printf("4. Xoa thong tin sach\n");
			printf("5. Tim kiem sach theo ISBN\n");
			printf("6. Tim kiem sach theo ten sach\n");
			printf("Enter your choice: ");
			printf("Press Esc to come back\n");
			printf("Press your choice");
			char bookMenu;
			bookMenu = _getch();
			//bookMenu = fgetc(stdin);
			switch (bookMenu)
			{
			case '1':
			{
				// Display the list of books in a new screen
				system("cls");
				showBookList(isbns, names, authors, publishers, publishingYears, categories, prices, counts, size);
				printf("\nPress any key to return to the menu...");
				_getch(); // Wait for any key pressX
				goto BookMenu;
				break;
			}
			case '2':
			{
				// Add book
				system("cls");
				printf("Nhap ID sach muon tao moi: ");
				int newId;
				scanf_s("%d", &newId);
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




				//scanf_s(" %[^\n]", newAuthor);
				addBook(isbns, names, authors, publishers, publishingYears, categories, prices, counts, &size, newId, newName, newAuthor, newPublisher, newPublishingYear, newCategory, newPrice, newCount);
				_getch();
				goto BookMenu;
				break;
			}
			case '3':
			{
				// Edit book
				system("cls");
				printf("Nhap id quyen sach muon sua: ");
				int modifyId;
				scanf_s("%d", &modifyId);
				modifyBook(isbns, names, authors, publishers, publishingYears, categories, prices, counts, size, modifyId);
				_getch();
				goto BookMenu;
				break;
			}
			case '4':
			{
				// delete book
				system("cls");
				printf("Enter the ID of the book to delete: ");
				int deleteId;
				scanf_s("%d", &deleteId);
				deleteBook(isbns, names, authors, publishers, publishingYears, categories, prices, counts, &size, deleteId);
				_getch();
				goto BookMenu;
				break;
			}
			case '5':
			{
				// Display the list of books in a new screen
				system("cls");
				printf("Enter the ID of the book to search: ");
				int searchId;
				scanf_s("%d", &searchId);
				int index = searchBookById(isbns, searchId, size);
				if (index != -1) {
					printf("%-5s| %-20.20s| %-20.20s| %-20.20s| %-20s| %-20.20s| %-6s| %-5s\n", "ID", "Name", "Author", "Publisher", "Publishing Year ", "Category", "Price", "Count");
					printf("---------------------------------------------------------------------------------------------------------------------------------------\n");
					printf("%-5d| %-20.20s◘| %-20.20s| %-20.20s| %-20d| %-20.20s| %-6d| %-5d\n", isbns[index], names[index], authors[index], publishers[index], publishingYears[index], categories[index], prices[index], counts[index]);
				}
				else {
					printf("Book with ID %d not found.\n", searchId);
				}
				_getch();
				goto BookMenu;
				break;
			}
			case '6':
			{
				// Display the list of books in a new screen
				system("cls");
				printf("Enter the name of the book to search: ");
				char searchName[100];
				getchar(); // Clear input buffer
				fgets(searchName, sizeof(searchName), stdin);
				searchName[strcspn(searchName, "\n")] = '\0'; // Remove trailing newline character
				int index = searchBookByName(names, searchName, size);
				if (index != -1) {
					printf("%-5s| %-20.20s| %-20.20s| %-20.20s| %-20s| %-20.20s| %-6s| %-5s\n", "ID", "Name", "Author", "Publisher", "Publishing Year ", "Category", "Price", "Count");
					printf("---------------------------------------------------------------------------------------------------------------------------------------\n");
					printf("%-5d| %-20.20s◘| %-20.20s| %-20.20s| %-20d| %-20.20s| %-6d| %-5d\n", isbns[index], names[index], authors[index], publishers[index], publishingYears[index], categories[index], prices[index], counts[index]);
				}
				else {
					printf("Book with this name not found.\n");
				}
				_getch();
				goto BookMenu;
				break;
			}
			case 27: {
				goto Menu;
				break;
			}
			default:
				goto BookMenu;
			}
			break;
		}
		case '2':
		{
			// Display the menu of book handle
		AuthorMenu:
			system("cls");
			printf("\nThao tac voi doc gia:\n");
			printf("1. Xem danh sach doc gia trong thu vien\n");
			printf("2. Them doc gia\n");
			printf("3. Chinh sua thong tin mot doc gia\n");
			printf("4. Xoa thong tin doc gia\n");
			printf("5. Tim kiem sach theo CMND\n");
			printf("6. Tim kiem doc gia theo ho ten\n");
			printf("Press Esc to come back\n");
			printf("Press your choice");
			char authorMenu;
			//scanf_s(" %c", &authorMenu);
			authorMenu = _getch();
			//bookMenu = fgetc(stdin);
			switch (authorMenu)
			{
			case '1':
			{
				// Display the list of books in a new screen
				system("cls");
				printf("%d", size);
				showDocGiaList(madocgias, hotens, cmnds, ngaysinhs, gioitinhs, emails, diachis, ngaylapthes, ngayhethans, sizeDocGia);
				printf("\nPress any key to return to the menu...");
				_getch(); // Wait for any key pressX
				goto AuthorMenu;
				break;
			}
			case '2':
			{
				// Add book
				system("cls");
				//int index = searchDocGiaById(madocgias, newId, size);
				int newId;
				do
				{
					printf("Nhap ID sach muon tao moi: ");
					scanf_s("%d", &newId);
				} while (searchDocGiaById(madocgias, newId, size) != -1);

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

				//scanf_s(" %[^\n]", newAuthor);
				addDocGia(madocgias, hotens, cmnds, ngaysinhs, gioitinhs, emails, diachis, ngaylapthes, ngayhethans, &sizeDocGia, newId, newName, newCMND, newNgaysinh, newGioitinh, newEmail, newDiachi, newNgaylapthe);
				_getch();
				goto AuthorMenu;
				break;
			}
			case '3':
			{
				// Edit book
				system("cls");
				printf("Nhap ma doc gia muon sua: ");
				int modifyId;
				scanf_s("%d", &modifyId);
				modifyDocGia(madocgias, hotens, cmnds, ngaysinhs, gioitinhs, emails, diachis, ngaylapthes, ngayhethans, sizeDocGia, modifyId);
				_getch();
				goto AuthorMenu;
				break;
			}
			case '4':
			{
				// delete book
				system("cls");
				printf("Nhap ma doc gia muon xoa : ");
				int deleteId;
				scanf_s("%d", &deleteId);
				deleteDocGia(madocgias, hotens, cmnds, ngaysinhs, gioitinhs, emails, diachis, ngaylapthes, ngayhethans, &sizeDocGia, deleteId);
				_getch();
				goto AuthorMenu;
				break;
			}
			case '5':
			{
				// Display the list of books in a new screen
				system("cls");
				printf("Nhap CMND muon tim kiem: ");
				char searchCMND[100];
				getchar();
				scanf_s("%[^\n]", searchCMND, sizeof(searchCMND));
				int i = searchDocGiaByCMND(cmnds, searchCMND, sizeDocGia);
				if (i != -1) {
					printf("%-4d| %-20.20s| %-13.13s| %02d/%02d/%-8d | %-6s | %-30s| %-40s | %02d/%02d/%-8d | %02d/%02d/%-8d\n",
						madocgias[i], hotens[i], cmnds[i], ngaysinhs[i][0], ngaysinhs[i][1], ngaysinhs[i][2],
						gioitinhs[i], emails[i], diachis[i], ngaylapthes[i][0], ngaylapthes[i][1], ngaylapthes[i][2],
						ngayhethans[i][0], ngayhethans[i][1], ngayhethans[i][2]);
				}
				else {
					printf("Doc gia voi cmnd: %d khong co trong du lieu.\n", searchCMND);
				}
				_getch();
				goto AuthorMenu;
				break;
			}
			case '6':
			{
				// Display the list of books in a new screen
				system("cls");
				printf("Nhap ten doc gia can tim: ");
				char searchName[100];
				getchar(); // Clear input buffer
				fgets(searchName, sizeof(searchName), stdin);
				searchName[strcspn(searchName, "\n")] = '\0'; // Remove trailing newline character
				int i = searchDocGiaByName(hotens, searchName, sizeDocGia);
				if (i != -1) {
					printf("%-4d| %-20.20s| %-13.13s| %02d/%02d/%-8d | %-6s | %-30s| %-40s | %02d/%02d/%-8d | %02d/%02d/%-8d\n",
						madocgias[i], hotens[i], cmnds[i], ngaysinhs[i][0], ngaysinhs[i][1], ngaysinhs[i][2],
						gioitinhs[i], emails[i], diachis[i], ngaylapthes[i][0], ngaylapthes[i][1], ngaylapthes[i][2],
						ngayhethans[i][0], ngayhethans[i][1], ngayhethans[i][2]);
				}
				else {
					printf("Doc gia voi ten: %s khong co trong du lieu.\n", searchName);
				}
				_getch();
				goto AuthorMenu;
				break;
			}
			case 27: {
				goto Menu;
				break;
			}
			default:
				goto AuthorMenu;
			}
			break;
		}
		case '3':
		{
		Lapphieumuon:
			// Implement borrowing books (if needed)
			system("cls");
			lapPhieuMuonSach(borrowRecordReaderIds, borrowRecordBookISBNs, ngaymuon, ngaydukientra, &borrowRecordCount, madocgias, isbns, size, sizeDocGia);
			_getch();
			break;
		}
		case '4':
		{
			// Implement borrowing books (if needed)
			system("cls");
			lapPhieuTraSach(borrowRecordReaderIds, borrowRecordBookISBNs, ngaymuon, ngaydukientra, &borrowRecordCount, madocgias, isbns, counts, prices, size, sizeDocGia);
			_getch();
			break;
		}
		case '6':
		{
			// Implement borrowing books (if needed)
			system("cls");
			xemPhieuMuonSach(borrowRecordReaderIds, borrowRecordBookISBNs, ngaymuon, ngaydukientra, borrowRecordCount);
			_getch();
			break;
		}
		case '5':
		{
			// Display the menu of book handle
		Thongke:
			system("cls");
			printf("\nThong ke co ban:\n");
			printf("1. Thong ke so luong sach trong thu vien\n");
			printf("2. Thong ke so luong sach theo the loai\n");
			printf("3. Thong ke so luong doc gia\n");
			printf("4. Thong ke so luong doc gia theo gioi tinh\n");
			printf("5. Thong ke so sach dang duoc muon\n");
			printf("6. Thong ke danh sach doc gia bi tre han\n");
			printf("Press Esc to come back\n");
			printf("Press your choice");
			char authorMenu;
			//scanf_s(" %c", &authorMenu);
			authorMenu = _getch();
			//bookMenu = fgetc(stdin);
			switch (authorMenu)
			{
			case '1':
			{
				// Display the list of books in a new screen
				system("cls");
				thongkeSoluongSach(counts, size);
				printf("\nPress any key to return to the menu...");
				_getch(); // Wait for any key pressX
				goto Thongke;
				break;
			}
			case '2':
			{
				system("cls");
				printf("Nhap the loai sach:");
				char theloai[100];
				//getchar();
				scanf_s("%[^\n]", theloai, sizeof(theloai));
				theloai[strcspn(theloai, "\n")] = '\0';
				thongkeSoluongSachTheoTheLoai(counts, size, categories, theloai);
				printf("\nPress any key to return to the menu...");
				_getch(); // Wait for any key pressX
				goto Thongke;
				break;
			}
			case '3':
			{
				// Edit book
				system("cls");
				thongkeSoluongDocGia(size);
				printf("\nPress any key to return to the menu...");
				_getch(); // Wait for any key pressX
				goto Thongke;
				break;
			}
			case '4':
			{
				// delete book
				system("cls");
				printf("Nhap gioi tinh: \n");
				char gioitinh[100];
				//getchar();
				scanf_s("%[^\n]", gioitinh, sizeof(gioitinh));
				gioitinh[strcspn(gioitinh, "\n")] = '\0';
				thongkeSoluongDocGiaTheoGioiTinh(size, gioitinhs, gioitinh);
				printf("\nPress any key to return to the menu...");
				_getch(); // Wait for any key pressX
				goto Thongke;
				break;
			}
			case '5':
			{
				// Display the list of books in a new screen
				system("cls");
				printf("Tong so sach dang duoc muon: %d", borrowRecordCount);
				xemPhieuMuonSach(borrowRecordReaderIds, borrowRecordBookISBNs, ngaymuon, ngaydukientra, borrowRecordCount);
				_getch();
				goto Thongke;
				break;
			}
			case '6':
			{
				// Display the list of books in a new screen
				system("cls");

				if (borrowRecordCount == 0) {
					printf("Khong co sach nao bi tre han\n");
				}
				else {
					int ngaytra[3];
					int total = 0;
					//printf("Nhap ngay tra (dd mm yyyy): ");
					//scanf_s("%d %d %d", &ngaytra[0], &ngaytra[1], &ngaytra[2]);
					do {
						printf("Nhap ngay hom nay(DD/MM/YYYY): \n");
						scanf_s("%d %d %d", &ngaytra[0], &ngaytra[1], &ngaytra[2]);
						if (!isValidDate(ngaytra[0], ngaytra[1], ngaytra[2])) {
							printf("Invalid date. Please enter a valid date.\n");
						}
					} while (!isValidDate(ngaytra[0], ngaytra[1], ngaytra[2]));
					for (int i = 0;i < borrowRecordCount;i++) {
						if (checkvalidReturnDate(ngaytra, ngaymuon[i]) != 1) {
							// neu nam trong khoang cho phep
							printf("Thong tin sach tre han thu %d:\n", total + 1);
							printf("%-5d| %-20d | %02d/%02d/%-8d| %02d/%02d/%-8d |\n", borrowRecordReaderIds[i], borrowRecordBookISBNs[i], ngaymuon[i][0], ngaymuon[i][1], ngaymuon[i][2], ngaydukientra[i][0], ngaydukientra[i][1], ngaydukientra[i][2]);
							total += 1;
						}
					}
					if (total != 0) {
						printf("Tong danh sach doc gia bi tre han:%d\n", total);
					}
					else {
						printf("Khong co sach nao bi tre han");
					}
				}

				_getch();
				goto Thongke;
				break;
			}
			case 27: {
				goto Menu;
				break;
			}
			default:
				goto Thongke;
			}
			break;
		}
		case 27: // ASCII code for Esc key
			printf("Exiting...\n");
			//goto BookMenu;
			break;
		default:
			printf("Invalid choice. Please try again.\n");
			_getch();
			break;
		}
	} while (choice != 27);
	return 0;
}

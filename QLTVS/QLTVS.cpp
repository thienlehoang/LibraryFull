#include <stdio.h>
#include <string.h>
#include <conio.h> // For _getch() function
#include <stdlib.h>
#include "HandleBook.h"
#include "HandleDocGia.h"
//#include "HandlePhieuMuon.h"
#include "HandleLoadFile.h"


#define MAX_BOOKS 100

void addBookToFile(const Book* book) {
	FILE* file;
	if (fopen_s(&file, "./Sach.txt", "a") != 0) {
		printf("Error opening file for reading.\n");
		return;
	}

	// Write book information to the file
	fprintf(file, "%d|%s|%s|%s|%d|%s|%d|%d\n", book->isbn, book->name, book->author,
		book->publisher, book->publishingYear, book->category, book->price, book->count);
	fflush(file);
	fclose(file); // Close the file
}

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



	int borrowRecordCount = 0; // Số lượng phiếu mượn sách hiện tại
	int soluongSachMuon = 0;
	int givebackCount = 0; // Số lượng phiếu trả sách hiện tại


	// Calculate the size of the arrays
	int size = sizeof(isbns) / sizeof(isbns[0]);
	int sizeDocGia = 4;

	Book books[MAX_BOOKS];
	int bookCount = 0;

	DocGia docgias[MAX_DOCGIAS];
	int docgiacount = 0;

	PhieuMuon phieumuons[MAX_BORROW_RECORDS];
	int phieumuonCount = 0;
	

	loadBooksFromFile(books, &bookCount);
	readReadersFromFile(docgias, &docgiacount);
	readPhieuMuonsFromFile(phieumuons, &phieumuonCount);

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
				//printf("%-5d| %-20.20s| %-20.20s| %-20.20s| %-20d| %-20.20s| %-6d| %-5d\n", books[0].isbn, books[0].name, books[0].author, books[0].publisher, books[0].publishingYear, books[0].category, books[0].price, books[0].count);
				showBookList1(books, bookCount);
				printf("\nPress any key to return to the menu...");
				_getch(); // Wait for any key pressX
				goto BookMenu;
				break;
			}
			case '2':
			{
				// Add book
				system("cls");
				addNewBook(books, &bookCount);
				//addBookToFile(&books[bookCount-1]);
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
				//modifyBook(isbns, names, authors, publishers, publishingYears, categories, prices, counts, size, modifyId);
				modifyBook1(books,bookCount,"./Sach.txt",modifyId);
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
				//deleteBook(isbns, names, authors, publishers, publishingYears, categories, prices, counts, &size, deleteId);
				deleteBook1(books, &bookCount, deleteId);
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
				int index = searchBookById1(books, searchId, size);
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
				int index = searchBookByName1(books, searchName, size);
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
				//showDocGiaList(madocgias, hotens, cmnds, ngaysinhs, gioitinhs, emails, diachis, ngaylapthes, ngayhethans, sizeDocGia);
				showDocGiaList1(docgias, docgiacount);
				printf("\nPress any key to return to the menu...");
				_getch(); // Wait for any key pressX
				goto AuthorMenu;
				break;
			}
			case '2':
			{
				// Add book
				system("cls");
				addNewDocGia(docgias, &docgiacount);
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
				modifyDocGia1(docgias, docgiacount, modifyId);
				//modifyDocGia(madocgias, hotens, cmnds, ngaysinhs, gioitinhs, emails, diachis, ngaylapthes, ngayhethans, sizeDocGia, modifyId);
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
				deleteDocGia1(docgias, &docgiacount, deleteId);
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
				int i = searchDocGiaByCMND(docgias, searchCMND, sizeDocGia);
				if (i != -1) {
					printf("%-4d| %-20.20s| %-13.13s| %02d/%02d/%-8d | %-6s | %-30s| %-40s | %02d/%02d/%-8d | %02d/%02d/%-8d\n",
						docgias[i].madocgia, docgias[i].hoten, docgias[i].cmnd, docgias[i].ngaysinh[0], docgias[i].ngaysinh[1], docgias[i].ngaysinh[2],
						docgias[i].gioitinh, docgias[i].email, docgias[i].diachi, docgias[i].ngaylapthe[0], docgias[i].ngaylapthe[1], docgias[i].ngaylapthe[2],
						docgias[i].ngayhethan[0], docgias[i].ngayhethan[1], docgias[i].ngayhethan[2]);
				}
				else {
					printf("Doc gia voi cmnd: %s khong co trong du lieu.\n", searchCMND);
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
				int i = searchDocGiaByName(docgias, searchName, sizeDocGia);
				if (i != -1) {
					printf("%-4d| %-20.20s| %-13.13s| %02d/%02d/%-8d | %-6s | %-30s| %-40s | %02d/%02d/%-8d | %02d/%02d/%-8d\n",
						docgias[i].madocgia, docgias[i].hoten, docgias[i].cmnd, docgias[i].ngaysinh[0], docgias[i].ngaysinh[1], docgias[i].ngaysinh[2],
						docgias[i].gioitinh, docgias[i].email, docgias[i].diachi, docgias[i].ngaylapthe[0], docgias[i].ngaylapthe[1], docgias[i].ngaylapthe[2],
						docgias[i].ngayhethan[0], docgias[i].ngayhethan[1], docgias[i].ngayhethan[2]);
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
			//lapPhieuMuonSach(borrowRecordReaderIds, borrowRecordBookISBNs, ngaymuon, ngaydukientra, &borrowRecordCount, madocgias, isbns, size, sizeDocGia);
			lapPhieuMuonSach1(phieumuons,&phieumuonCount,docgias,books,bookCount,docgiacount);
			_getch();
			break;
		}
		case '4':
		{
			// Implement borrowing books (if needed)
			system("cls");
			lapPhieuTraSach1(phieumuons, &phieumuonCount, docgias,books,bookCount,docgiacount);
			_getch();
			break;
		}
		case '6':
		{
			// Implement borrowing books (if needed)
			system("cls");
			xemPhieuMuonSach1(phieumuons, phieumuonCount);
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
				thongkeSoluongSach(books,bookCount);
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
				thongkeSoluongSachTheoTheLoai(books, bookCount, theloai);
				printf("\nPress any key to return to the menu...");
				_getch(); // Wait for any key pressX
				goto Thongke;
				break;
			}
			case '3':
			{
				// Edit book
				system("cls");
				thongkeSoluongDocGia(docgiacount);
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
				thongkeSoluongDocGiaTheoGioiTinh(docgias,gioitinh,docgiacount);
				printf("\nPress any key to return to the menu...");
				_getch(); // Wait for any key pressX
				goto Thongke;
				break;
			}
			case '5':
			{
				// Display the list of books in a new screen
				system("cls");
				printf("Tong so sach dang duoc muon: %d", phieumuonCount);
				xemPhieuMuonSach1(phieumuons, phieumuonCount);
				_getch();
				goto Thongke;
				break;
			}
			case '6':
			{
				// Display the list of books in a new screen
				system("cls");

				if (phieumuonCount == 0) {
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
					for (int i = 0;i < phieumuonCount;i++) {
						if (checkvalidReturnDate(ngaytra, phieumuons[i]) != 1) {
							// neu nam trong khoang cho phep
							printf("Thong tin sach tre han thu %d:\n", total + 1);
							printf("%-5d| %-20d | %02d/%02d/%-8d| %02d/%02d/%-8d |\n", phieumuons[i].borrowRecordReaderIds, phieumuons[i].borrowRecordBookISBNs, phieumuons[i].ngaymuon[0], phieumuons[i].ngaymuon[1], phieumuons[i].ngaymuon[2], phieumuons[i].ngaydukientra[0], phieumuons[i].ngaydukientra[1], phieumuons[i].ngaydukientra[2]);
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

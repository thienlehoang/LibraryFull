#include <stdio.h>
#include <stdlib.h>
#include "HandlePhieuMuon.h"


 
inline void loadBooksFromFile(Book books[100], int* bookCount) {
    FILE* file;
    if (fopen_s(&file, "./Sach.txt", "r") != 0) {
        printf("Error opening file for reading.\n");
        return;
    }

    *bookCount = 0; // Reset book count before loading data

    while (*bookCount < MAX_BOOKS && fscanf_s(file, "%d|%[^|]|%[^|]|%[^|]|%d|%[^|]|%d|%d\n",
        &books[*bookCount].isbn, books[*bookCount].name, sizeof(books[*bookCount].name),
        books[*bookCount].author, sizeof(books[*bookCount].author), books[*bookCount].publisher,
        sizeof(books[*bookCount].publisher), &books[*bookCount].publishingYear, books[*bookCount].category,
        sizeof(books[*bookCount].category), &books[*bookCount].price, &books[*bookCount].count) == 8) {
        (*bookCount)++;
    }

    fclose(file);
}
inline void readReadersFromFile(DocGia readers[], int* readerCount) {
    FILE* file1;
    errno_t err = fopen_s(&file1, "./DocGia.txt", "r");
    if (err != 0) {
        printf("Error opening file for reading. Error code: %d\n", err);
        return;
    }

    *readerCount = 0; // Number of readers read from file

    while (*readerCount < MAX_DOCGIAS && fscanf_s(file1, "%d|%[^|]|%[^|]|%d/%d/%d|%[^|]|%[^|]|%[^|]|%d/%d/%d|%d/%d/%d\n",
        &readers[*readerCount].madocgia,
        readers[*readerCount].hoten, sizeof(readers[*readerCount].hoten),
        readers[*readerCount].cmnd, sizeof(readers[*readerCount].cmnd),
        &readers[*readerCount].ngaysinh[0], &readers[*readerCount].ngaysinh[1], &readers[*readerCount].ngaysinh[2],
        readers[*readerCount].gioitinh, sizeof(readers[*readerCount].gioitinh),
        readers[*readerCount].email, sizeof(readers[*readerCount].email),
        readers[*readerCount].diachi, sizeof(readers[*readerCount].diachi),
        &readers[*readerCount].ngaylapthe[0], &readers[*readerCount].ngaylapthe[1], &readers[*readerCount].ngaylapthe[2],
        &readers[*readerCount].ngayhethan[0], &readers[*readerCount].ngayhethan[1], &readers[*readerCount].ngayhethan[2]) == 15) {
        (*readerCount)++;
    }

    fclose(file1);
}


inline void readPhieuMuonsFromFile(PhieuMuon phieumuons[], int* phieumuonCount) {
    FILE* file1;
    errno_t err = fopen_s(&file1, "./PhieuMuon.txt", "r");
    if (err != 0) {
        printf("Error opening file for reading. Error code: %d\n", err);
        return;
    }

    *phieumuonCount = 0; // Number of readers read from file

    while (*phieumuonCount < MAX_DOCGIAS && fscanf_s(file1, "%d|%d|%d/%d/%d|%d/%d/%d\n",
        &phieumuons[*phieumuonCount].borrowRecordReaderIds,
        &phieumuons[*phieumuonCount].borrowRecordBookISBNs,
        &phieumuons[*phieumuonCount].ngaymuon[0],
        &phieumuons[*phieumuonCount].ngaymuon[1],
        &phieumuons[*phieumuonCount].ngaymuon[2],
        &phieumuons[*phieumuonCount].ngaydukientra[0],
        &phieumuons[*phieumuonCount].ngaydukientra[1],
        &phieumuons[*phieumuonCount].ngaydukientra[2]
        ) == 8) {
        (*phieumuonCount)++;
    }

    fclose(file1);
}

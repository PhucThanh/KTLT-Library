#include "library.h"
void listBorrowing() 
{
	BOOK b;
	FILE *fp = fopen("book.csv", "r");
	char line[LINE_LENGTH];
	char tmp[LINE_LENGTH];
	printf("===================================================================================================================================================\n");
	printf("||  %-15s%-40s%-25s%-10s%-25s%-20s   ||\n", "ISBN", "Ten sach", "Tac gia", "Gia tien", "So luong tai thu vien", "So luong dang duoc muon");
	printf("===================================================================================================================================================\n");
	while (fgets(line, LINE_LENGTH, fp))
	{
		b = stringToBOOK(line);
		if (b.borrowing != 0) 
		{
			printf("||  %-15s%-40s%-25s%-10d%-25d%-20d      ||\n", b.ISBN, b.name, b.author, b.price, b.stock-b.borrowing, b.borrowing);
		}
	}
	fclose(fp);
}
void listLate() 
{
	FILE *fp = fopen("borrow.csv", "r");
	char line[LINE_LENGTH];
	printf("==========================================================================================================================\n");
	printf("%-20s%-30s%-20s%-20s%-20s%-20s\n", "Ma doc gia","Ho va ten", "Ngay muon", "Ngay tra du kien", "So ngay tre han", "So sach muon");
	printf("==========================================================================================================================\n");
	BORROW b;
	while (fgets(line, LINE_LENGTH, fp))
	{
		b = stringToBORROW(line);
		int dayPassed = dateBetween(b.end, getCurrentTime(0, 0, 0));
		if (dayPassed > 0)
		{
			READER r;
			int count;//So sach muon
			
			if (checkReaderID(b.reader, r))
			{
				char tmpDay[10],tmpDay2[10];
				strcpy(tmpDay, DATEToString(b.start));
				strcpy(tmpDay2, DATEToString(b.end));

				
				//DEm so luong sach
				int count = 0;
				ref p;
				for (p = b.bookList;p;p = p->next)
					count++;
				printf("%-20s%-30s%-20s%-20s%-20d%-20d\n", r.id, r.name, tmpDay, tmpDay2, dayPassed,count );
			}
		}
	}
	fclose(fp);
}
char *getcategory(char line[])
{
	char *tok;
	tok = strtok(line, ";");
	tok = strtok(NULL, ";");
	tok = strtok(NULL, ";");
	tok = strtok(NULL, ";");
	tok = strtok(NULL, ";");
	return tok;
}

void bookReport()
{
	char line[LINE_LENGTH];
	char tmp[LINE_LENGTH];
	char *tok;
	printf("========================================================================================================================================================================================\n");
	printf("||  %-15s%-35s%-25s%-20s%-15s%-10s%-20s%-20s%-15s||\n", "ISBN", "Ten", "Tac gia", "NXB", "The loai", "Nam", "Gia", "So luong trong kho","So luong duoc muon");
	printf("========================================================================================================================================================================================\n");
	int stock = 0, borrowing = 0;
	FILE *fp = fopen("book.csv", "r");
	if (fp == NULL)
		printf("Chua co du lieu !!! \n");
	else
	{
		while (fgets(line, LINE_LENGTH, fp))
		{
			strcpy(tmp, line);
			BOOK b = stringToBOOK(tmp);

			strcpy(tmp, line);
			tok = strtok(tmp, ";");
			printf("||  %-15s", tok);

			tok = strtok(NULL, ";");
			printf("%-35.34s", tok);

			tok = strtok(NULL, ";");
			printf("%-25s", tok);

			tok = strtok(NULL, ";");
			printf("%-20.19s", tok);

			tok = strtok(NULL, ";");
			printf("%-15.14s", tok);

			tok = strtok(NULL, ";");
			printf("%-10s", tok);

			tok = strtok(NULL, ";");
			printf("%-20s", tok);

			tok = strtok(NULL, ";");
			printf("%-20s", tok);

			tok = strtok(NULL, ";");
			printf("%s", tok);

			stock = stock + b.stock;
			borrowing = borrowing + b.borrowing;
		}
		printf("\nSo sach trong kho: %d\n", stock);
		printf("So sach dang muon: %d\n", borrowing);
	}
	fclose(fp);

}

void categoryReport()
{
	printf("Nhap the loai sach ban muon thong ke: \n");
	char input[TEXT_LENGTH];
	getchar();
	gets_s(input, TEXT_LENGTH);
	char *tok;
	printf("\n");
	printf("=================================================================================================================================================================\n");
	printf("||  %-15s%-35s%-25s%-25s%-15s%-10s%-20s%-10s||\n", "ISBN", "Ten", "Tac gia", "NXB", "The loai", "Nam XB", "Gia", "So luong");
	printf("=================================================================================================================================================================\n");
	FILE *fp = fopen("book.csv", "r");
	char line[LINE_LENGTH];
	char Category[LINE_LENGTH];
	char tmp[LINE_LENGTH];
	int stock = 0, borrowing = 0;
	if (fp == NULL)
		printf("Chua co du lieu !!!\n");
	else
	{
		while (fgets(line, LINE_LENGTH, fp))
		{
			strcpy(tmp, line);
			strcpy(Category, getcategory(tmp));
			if (strcmp(input, Category) == 0)
			{
				BOOK b = stringToBOOK(line);
				strcpy(tmp, line);
				tok = strtok(tmp, ";");
				printf("||  %-15s", tok);

				tok = strtok(NULL, ";");
				printf("%-35.34s", tok);

				tok = strtok(NULL, ";");
				printf("%-25s", tok);

				tok = strtok(NULL, ";");
				printf("%-25.24s", tok);

				tok = strtok(NULL, ";");
				printf("%-15.14s", tok);

				tok = strtok(NULL, ";");
				printf("%-10s", tok);

				tok = strtok(NULL, ";");
				printf("%-20s", tok);

				tok = strtok(NULL, ";");
				printf("%s\n", tok);

				stock = stock + b.stock;
				borrowing = borrowing + b.borrowing;
			}
		}
		printf("\nSo sach trong kho: %d\n", stock);
		printf("So sach dang muon: %d\n", borrowing);
	}
	fclose(fp);
}
void readerReport()
{
	system("cls");
	char line[LINE_LENGTH];
	char tmp[LINE_LENGTH];
	char *tok = (char*)malloc(TEXT_LENGTH);
	int count = 0;
	printf("============================================================================================================================================================\n");
	printf("|| %-13s%-25s%-15s%-12s%-10s%-25s%-25s%-15s%-15s\n", "ID", "Ho va ten", "CMND", "Ngay sinh", "Gioi tinh", "Email", "Dia chi", "Ngay lam the", "Ngay het han");
	printf("============================================================================================================================================================\n");
	FILE *fp = fopen("reader.csv", "r");
	if (fp == NULL)
		printf("Chua co du lieu !!! \n");
	else
	{
		while (fgets(line, LINE_LENGTH, fp))
		{
			strcpy(tmp, line);
			tok = strtok(tmp, ";");
			printf("|| %-13s", tok);

			tok = strtok(NULL, ";");
			printf("%-25s", tok);

			tok = strtok(NULL, ";");
			printf("%-15s", tok);

			tok = strtok(NULL, ";");
			printf("%-12s", tok);


			tok = strtok(NULL, ";");
			if (atoi(tok) == 1)
			{
				printf("%-10s", "Nam");
			}
			else
			{
				printf("%-10s", "Nu");
			}

			tok = strtok(NULL, ";");
			printf("%-25.24s", tok);

			tok = strtok(NULL, ";");
			printf("%-25.24s", tok);

			tok = strtok(NULL, ";");
			printf("%-15s", tok);

			tok = strtok(NULL, ";");
			printf("%s", tok);
			count++;
		}
		printf("\n So luong doc gia: %d\n", count);
	}
	fclose(fp);
}

void genderReport()
{
	system("cls");
	char line[LINE_LENGTH];
	char tmp[LINE_LENGTH];
	char *tok = (char*)malloc(TEXT_LENGTH);
	int count0 = 0, count1 = 0;
	printf("> DOC GIA NU : \n");
	printf("============================================================================================================================================================\n");
	printf("|| %-13s%-25s%-15s%-12s%-10s%-25s%-25s%-15s%-15s\n", "ID", "Ho va ten", "CMND", "Ngay sinh", "Gioi tinh", "Email", "Dia chi", "Ngay lam the", "Ngay het han");
	printf("============================================================================================================================================================\n");
	FILE *fp = fopen("reader.csv", "r");
	if (fp == NULL)
		printf("Chua co du lieu !!! \n");
	else
	{
		while (fgets(line, LINE_LENGTH, fp))
		{
			strcpy(tmp, line);
			READER a = stringToReader(line);
			if (!a.gender)
			{
				tok = strtok(tmp, ";");
				printf("|| %-13s", tok);

				tok = strtok(NULL, ";");
				printf("%-25s", tok);

				tok = strtok(NULL, ";");
				printf("%-15s", tok);

				tok = strtok(NULL, ";");
				printf("%-12s", tok);


				tok = strtok(NULL, ";");
				if (atoi(tok) == 1)
				{
					printf("%-10s", "Nam");
				}
				else
				{
					printf("%-10s", "Nu");
				}

				tok = strtok(NULL, ";");
				printf("%-25.24s", tok);

				tok = strtok(NULL, ";");
				printf("%-25.24s", tok);

				tok = strtok(NULL, ";");
				printf("%-15s", tok);

				tok = strtok(NULL, ";");
				printf("%s", tok);
				count0++;
			}
		}
	}
	printf("> DOC GIA NAM : \n");
	printf("============================================================================================================================================================\n");
	printf("|| %-13s%-25s%-15s%-12s%-10s%-25s%-25s%-15s%-15s\n", "ID", "Ho va ten", "CMND", "Ngay sinh", "Gioi tinh", "Email", "Dia chi", "Ngay lam the", "Ngay het han");
	printf("============================================================================================================================================================\n");
	//FILE *fp = fopen("reader.csv", "r");
	fseek(fp, 0, SEEK_SET);
	while (fgets(line, LINE_LENGTH, fp))
	{
		strcpy(tmp, line);
		READER a = stringToReader(line);
		if (a.gender)
		{
			tok = strtok(tmp, ";");
			printf("|| %-13s", tok);

			tok = strtok(NULL, ";");
			printf("%-25s", tok);

			tok = strtok(NULL, ";");
			printf("%-15s", tok);

			tok = strtok(NULL, ";");
			printf("%-12s", tok);


			tok = strtok(NULL, ";");
			if (atoi(tok) == 1)
			{
				printf("%-10s", "Nam");
			}
			else
			{
				printf("%-10s", "Nu");
			}
			//printf("%-10s", tok);

			tok = strtok(NULL, ";");
			printf("%-25.24s", tok);

			tok = strtok(NULL, ";");
			printf("%-25.24s", tok);

			tok = strtok(NULL, ";");
			printf("%-15s", tok);

			tok = strtok(NULL, ";");
			printf("%s", tok);
			count1++;
		}
	}
	printf("\n");
	printf("> So luong doc gia NU: %d\n", count0);
	printf("> So luong doc gia NAM: %d\n", count1);
	fclose(fp);
}
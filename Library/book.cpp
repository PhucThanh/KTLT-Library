#include "library.h"
void printBook(BOOK b)
{
	printf("=================================\n");
	printf("> ISBN : %s\n", b.ISBN);
	printf("> Ten sach : %s\n", b.name);
	printf("> Tac gia : %s\n", b.author);
	printf("> NXB : %s\n", b.publisher);
	printf("> The loai : %s\n", b.category);
	printf("> Nam SX : %d\n", b.year);
	printf("> Gia tien : %d\n", b.price);
	printf("> So luong tai thu vien: %d\n", b.stock);
	printf("> So luong dang duoc muon : %d\n", b.borrowing);
	printf("=================================\n");
}
void BookList()
{
	char line[LINE_LENGTH];
	char tmp[LINE_LENGTH];
	char *tok;
	printf("======================================================================================================================================================================\n");
	printf("||  %-15s%-40s%-25s%-25s%-15s%-10s%-20s%-10s||\n", "ISBN", "Ten sach", "Tac gia", "Nha xuat ban", "The loai", "Nam XB", "Gia tien", "So luong");
	printf("======================================================================================================================================================================\n");
	FILE *fp = fopen("book.csv", "r");
	while (fgets(line, LINE_LENGTH, fp))
	{
		strcpy(tmp, line);
		tok = strtok(tmp, ";");
		printf("||  %-15s", tok);

		tok = strtok(NULL, ";");
		printf("%-40.39s", tok);

		tok = strtok(NULL, ";");
		printf("%-25s", tok);

		tok = strtok(NULL, ";");
		printf("%-25.24s", tok);

		tok = strtok(NULL, ";");
		printf("%-15s", tok);

		tok = strtok(NULL, ";");
		printf("%-10s", tok);

		tok = strtok(NULL, ";");
		printf("%-20s", tok);

		tok = strtok(NULL, ";");
		printf("%s\n", tok);

	}
	fclose(fp);
}
void addBook()
{
	printf(" ______________________________________\n");
	printf("|                                      |\n");
	printf("|               THEM SACH              |\n");
	printf("|______________________________________|\n");
	char line[256] = "", input[30];
	const char *text[8];
	text[0] = "> ISBN : ";
	text[1] = "> Ten sach : ";
	text[2] = "> Tac gia : ";
	text[3] = "> NXB : ";
	text[4] = "> The loai : ";
	text[5] = "> Nam xuat ban: ";
	text[6] = "> Gia: ";
	text[7] = "> So luong: ";
	getchar();
	for (int i = 0; i < 8; i++)
	{
		printf("%s", text[i]);
		gets_s(input, 30);
		strcat(line, input);
		strcat(line, ";");
	}
	strcat(line, "0\n");//So luong muon
	FILE*fp = fopen("book.csv", "a+");
	fputs(line, fp);
	fclose(fp);
}
void deleteBook()
{
	printf(" ______________________________________\n");
	printf("|                                      |\n");
	printf("|          XOA THONG TIN SACH          |\n");
	printf("|______________________________________|\n");
	char id[TEXT_LENGTH];
	printf("> Nhap ISBN sach can xoa : ");
	scanf("%s", &id);
	BOOK tmp;
	if (checkISBN(id,tmp))
	{
		FILE *fp = fopen("book.csv", "r");
		FILE *fptmp = fopen("temp", "w");

		char line[LINE_LENGTH];
		char tmp[LINE_LENGTH];
		char* tok;
		while (fgets(line, LINE_LENGTH, fp))
		{
			strcpy(tmp, line);
			tok = strtok(tmp, ";");
			if (strcmp(tok, id) == 0)
			{

			}
			else
			{
				fputs(line, fptmp);
			}
		}
		fclose(fp);
		fclose(fptmp);
		remove("book.csv");
		rename("temp", "book.csv");
	}
	else
	{
		printf("> Khong tim thay sach co ISBN tren\n");
	}
}
void updateBookInfo()
{
	BOOK b;
	printf(" ______________________________________\n");
	printf("|                                      |\n");
	printf("|        CAP NHAT THONG TIN SACH       |\n");
	printf("|______________________________________|\n");
	char input[TEXT_LENGTH];
	printf("> Nhap ISBN : ");
	scanf("%s", input);
	if (checkISBN(input, b)) 
	{
		printf("> Chinh sua thong tin cho sach #%s:\n", b.ISBN);
		getchar();
		printf("> Ten sach : ");
		gets_s(b.name, TEXT_LENGTH);

		printf("> Tac gia : ");
		gets_s(b.author, TEXT_LENGTH);

		printf("> NXB : ");
		gets_s(b.publisher, TEXT_LENGTH);

		printf("> The loai : ");
		gets_s(b.category, TEXT_LENGTH);

		printf("> Nam xuat ban: ");
		scanf("%d", &b.year);

		printf("> Gia tien : ");
		scanf("%d", &b.price);

		saveBook(b);
	}
	else 
	{
		printf("> Khong tim thay sach\n");
	}
}
void saveBook(BOOK b)
{
	FILE *fp = fopen("book.csv", "r");
	FILE *fptmp = fopen("temp", "w");

	char line[LINE_LENGTH];
	char tmp[LINE_LENGTH];
	char* tok;

	while (fgets(line, LINE_LENGTH, fp))
	{
		strcpy(tmp, line);
		tok = strtok(tmp, ";");
		if (strcmp(tok, b.ISBN) == 0)
		{
			char str[LINE_LENGTH];
			strcpy(str, BOOKtoString(b));
			fputs(str, fptmp);
		}
		else
		{
			fputs(line, fptmp);
		}
	}

	fclose(fp);
	fclose(fptmp);

	remove("book.csv");
	rename("temp", "book.csv");
}

void findISBN()
{
	printf(" ______________________________________\n");
	printf("|                                      |\n");
	printf("|        TIM KIEM SACH BANG ISBN       |\n");
	printf("|______________________________________|\n");
	printf("> Nhap ISBN sach can tim : ");
	char input[TEXT_LENGTH];
	scanf("%s", &input);
	FILE *fp = fopen("book.csv", "r");

	char line[LINE_LENGTH];
	char idHolder[TEXT_LENGTH];
	char tmp[LINE_LENGTH];
	while (fgets(line, LINE_LENGTH, fp))
	{
		strcpy(tmp, line);
		strcpy(idHolder, getISBN(tmp));
		if (strcmp(input, idHolder) == 0)
		{
			printBook(stringToBOOK(line));
			fclose(fp);
			return;
		}
	}
	fclose(fp);
	printf("> Khong tim thay sach\n");
}

int checkISBN(char str[], BOOK &book)	
{
	FILE *fp = fopen("book.csv", "r");

	char line[LINE_LENGTH];

	while (fgets(line, LINE_LENGTH, fp))
	{
		book=stringToBOOK(line);
		if (strcmp(book.ISBN,str)==0) 
		{
			if (book.stock - book.borrowing > 0) 
			{
				fclose(fp);
				return 1;
			}
			fclose(fp);
			return -1;
		}
	}
	fclose(fp);
	return 0;
}
char * getISBN(char line[])
{
	char *tok;
	tok = strtok(line, ";");
	return tok;
}

void findname()
{
	printf(" ______________________________________\n");
	printf("|                                      |\n");
	printf("|        TIM SACH THEO TEN SACH        |\n");
	printf("|______________________________________|\n");
	printf("> Nhap ten sach can tim : ");
	char input[TEXT_LENGTH];
	//scanf("%s", &input);
	getchar();
	gets_s(input, TEXT_LENGTH);
	FILE *fp = fopen("book.csv", "r");

	char line[LINE_LENGTH];
	char nameHolder[LINE_LENGTH];
	char tmp[LINE_LENGTH];

	while (fgets(line, LINE_LENGTH, fp))
	{
		strcpy(tmp, line);
		strcpy(nameHolder, getname(tmp));
		if (strcmp(input, nameHolder) == 0)
		{
			printBook(stringToBOOK(line));
			fclose(fp);
			return;
		}
	}
	fclose(fp);

}

char *getname(char line[])
{
	char *tok;
	tok = strtok(line, ";");
	tok = strtok(NULL, ";");
	return tok;
}
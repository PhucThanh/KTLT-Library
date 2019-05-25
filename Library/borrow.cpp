#include "library.h"

void printfBorrow(BORROW borrow) 
{
	printf("============================\n");
	printf("> ID : %s\n", borrow.reader);

	int count=0;
	ref p;
	for (p = borrow.bookList;p;p = p->next)
	{
		count++;
	}
	printf("> So luong sach muon : %d\n", count);
	char *tmp = (char*)malloc(TEXT_LENGTH);
	strcpy(tmp, DATEToString(borrow.start));
	printf("> Ngay muon : %s\n", tmp);
	strcpy(tmp, DATEToString(borrow.start));
	printf("> Ngay tra : %s\n", tmp);
	printf("> ISBN cua cac sach dang muon : \n");
	for (p = borrow.bookList;p;p = p->next)
	{
		printf("> %s\n", p->isbn);
	}
	printf("============================\n");
}

void addBorrow() 
{
	FILE *fp = fopen("borrow.csv", "a+");
	BORROW borrow;
	borrow.bookList = NULL;
	char input[TEXT_LENGTH];
	getchar();
	printf(" ______________________________________\n");
	printf("|                                      |\n");
	printf("|         LAP PHIEU MUON SACH          |\n");
	printf("|______________________________________|\n");
	printf("> Nhap ma doc gia muon sach: ");
	gets_s(input, TEXT_LENGTH);
	READER tmpReader;
	if (checkReaderID(input,tmpReader)) 
	{
		if (!checkReaderBorrowing(input) )
		{
			strcpy(borrow.reader, input);
			printReader(tmpReader);
		}
		else
		{
			printf("> Doc gia nay co sach dang muon\n");
			printf("> Vui long tra lai sach de muon tiep\n");
			return;
		}
	}
	else
	{
		printf("> Ma doc gia khong ton tai\n");
		return;
	}
	//Ngay muong ngay tra
	borrow.start = getCurrentTime(0, 0, 0);
	borrow.end = getCurrentTime(7, 0, 0);

	int count=0;//So sach muon
	printf("=================================\n");
	printf("> Nhap ISBN sach muon:\n");
	printf("> Luu y :\n");
	printf(" - Mot sach chi duong muon mot cuon\n");
	printf(" - Duoc muon toi da 3 sach\n");
	printf(" * Nhap [-1] de hoan tat \n");
	printf("=================================\n");

	BOOK tmpBook[3];
	do 
	{
		printf("> ISBN:");
		scanf("%s", &input);
		if (strcmp(input, "-1") != 0) 
		{
			int t = checkISBN(input,tmpBook[count]);
			switch (t) 
			{
			case 1:
				addLast(borrow.bookList, input);
				printBook(tmpBook[count]);
				printf("> Da them sach vao phieu muon\n");
				printf("=================================\n");
				//tmpBook[count].stock--;	//Giam so luong sach
				tmpBook[count].borrowing++;
				count++;
				break;
			case 0:
				printf("> Ma ISBN khong ton tai\n");
				break;
			case -1:
				printf("> So luong sach da het\n");
			}
		}
	} while ((strcmp(input,"-1")!=0) && (count<3));
	if (count > 0)
	{
		//ADD NEW BORROW
		char tmp[LINE_LENGTH];
		strcpy(tmp, BORROWToString(borrow));
		fprintf(fp, tmp);
		fclose(fp);
		//Giam so luong sach
		for (int i = 0;i < count;i++) 
		{
			saveBook(tmpBook[i]);
		}
		printfBorrow(borrow);
	}
	else
	{
		printf("> Khong muon cuon sach nao\n");
	}
	fclose(fp);
}
ref getNode(char text[]) 
{
	ref p;
	p = (ref)malloc(sizeof(struct node));
	if (p == NULL) 
	{
		exit(0);
	}
	strcpy(p->isbn, text);
	p->next = NULL;
	return p;
}
void addLast(ref &S, char text[]) 
{
	ref p;
	if (S == NULL) 
	{
		S = getNode(text);
	}
	else
	{
		p = S;
		while (p->next) 
		{
			p = p->next;
		}
		p->next = getNode(text);
	}
}

bool checkReaderBorrowing(char str[]) 
{
	FILE*fp = fopen("borrow.csv", "r");
	char line[LINE_LENGTH];
	char *tok;
	while (fgets(line, LINE_LENGTH, fp))
	{
		tok = strtok(line, ";");
		if (strcmp(str, tok) == 0)
		{
			fclose(fp);
			return true;
		}
	}
	fclose(fp);
	return false;
}

void returnBook() 
{
	printf("> Ma doc gia tra sach :\n>");
	char input[TEXT_LENGTH];
	char tmp[TEXT_LENGTH];
	scanf("%s", input);

	int money = 0;
	FILE*fp = fopen("borrow.csv", "r");
	BOOK tmpBook[3];
	bool returned = false;
	int i = 0;

	DATE today = getCurrentTime(0, 0, 0);

	char line[LINE_LENGTH];
	while (fgets(line, LINE_LENGTH, fp))
	{
		BORROW borrow = stringToBORROW(line);
		if (strcmp(borrow.reader, input) == 0) 
		{
			strcpy(tmp, DATEToString(borrow.start));
			printf("> Ngay muon sach : %s\n",tmp);
			strcpy(tmp, DATEToString(borrow.start));
			printf("> Ngay tra du kien : %s\n", tmp);
			strcpy(tmp, DATEToString(borrow.end));
			printf("> Ngay tra thuc te : %s\n", tmp);

			int lateDay = dateBetween(borrow.end, today);
			if (lateDay > 0)
				printf("> Tre hang %d ngay, tien phat : %d\n", lateDay, lateDay * 5000);
			else
				lateDay = 0;

			printf("> Nhap trang thai cua sach : (0: Sach bi mat , 1: Sach khong bi mat)\n");
			printf("============================\n");
			int n;

			ref p;
			
			for (p=borrow.bookList;p;p=p->next) 
			{
				if (checkISBN(p->isbn, tmpBook[i])!=0)
				{
					printf("> ISBN - %s : ", tmpBook[i].ISBN);
					scanf("%d", &n);
					if (n == 0)
					{
						money += tmpBook[i].price * 2;
						printf("> Sach bi mat, gia bia : %d\n", tmpBook[i].price);
						tmpBook[i].stock--;
					}
					tmpBook[i].borrowing--;
				}
				else
				{
					if (strcmp(p->isbn, "\n") != 0)
						printf("> Khong tim thay sach co ISBN = %s .Co ve nhu sach da bi xoa khoi CSDL\n", p->isbn);
				}
				i++;
			}
			returned = true;
			money += lateDay * 5000;
			printf("> Tong so tien phai tra la %d\n", money);

			RETURNTICKET r;
			r.bookList = borrow.bookList;
			strcpy(r.reader, borrow.reader);
			r.start = borrow.start;
			r.end = borrow.end;
			r.returnDay = today;
			r.money = money;
			FILE *fr = fopen("return.csv", "a+");
			char temp[LINE_LENGTH];
			strcpy(temp, RETURNTICKETToString(r));
			fputs(temp,fr);
			fclose(fr);
			break;
		}
	}
	fclose(fp);
	if (returned)
	{
		deleteBorrow(input);
		//Update lai so luong sach va xoa borrow
		for (int c = 0;c < i;c++)
		{
			saveBook(tmpBook[c]);
		}
	}
	else
		printf("> Khong tim thay doc gia trong danh sach phieu muon\n");
}

void deleteBorrow(char id[])
{
	FILE *fp = fopen("borrow.csv", "r");
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
	remove("borrow.csv");
	rename("temp", "borrow.csv");
}
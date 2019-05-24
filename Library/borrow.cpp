#include "library.h"
char* BORROWToString(BORROW borrow) 
{
	char line[LINE_LENGTH];
	strcpy(line, borrow.reader);
	strcat(line, ";");
	strcat(line, DATEToString(borrow.start));
	strcat(line, ";");
	strcat(line, DATEToString(borrow.end));
	strcat(line, ";");
	
	char *bookList=(char*)malloc(LINE_LENGTH);
	strcpy(bookList, "");
	ref p;
	for (p = borrow.begin;p;p=p->next) 
	{
		strcat(bookList, p->isbn);
		strcat(bookList, ",");
	}
	strcat(line, bookList);
	strcat(line, "\n");
	return line;
}

void printfBorrow(BORROW borrow) 
{
	printf("============================\n");
	printf("> ID : %s\n", borrow.reader);

	int count=0;
	ref p;
	for (p = borrow.begin;p;p = p->next)
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
	for (p = borrow.begin;p;p = p->next)
	{
		printf("> %s\n", p->isbn);
	}
	printf("============================\n");
}

void addBorrow() 
{
	FILE *fp = fopen("borrow.csv", "a+");
	BORROW borrow;
	borrow.begin = NULL;
	char input[TEXT_LENGTH];
	getchar();
	printf("LAP PHIEU MUON SACH\n");
	printf("Nhap ma doc gia muon sach: ");
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
		printf("Ma doc gia khong ton tai\n");
		return;
	}
	//Ngay muong ngay tra
	borrow.start = getCurrentTime(0, 0, 0);
	borrow.end = getCurrentTime(7, 0, 0);

	int count=0;//So sach muon
	printf("=================================\n");
	printf("Nhap ISBN sach muon , chon [-1] de hoan tat: \n");
	printf("Luu y :\n");
	printf(" - Mot sach chi duong muon mot cuon\n");
	printf(" - Duoc muon toi da 3 sach\n");
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
				add(borrow.begin, input);
				printBook(tmpBook[count]);
				printf("> Da them sach vao phieu muon\n");
				printf("=================================\n");
				//tmpBook[count].stock--;	//Giam so luong sach
				tmpBook[count].borrowing++;
				count++;
				break;
			case 0:
				printf("Ma ISBN khong ton tai\n");
				break;
			case -1:
				printf("So luong sach da het\n");
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
void add(ref &S, char text[]) 
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
/*void saveBorrow(BORROW borrow)
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
		if (strcmp(tok, borrow.reader) == 0)
		{
			char str[LINE_LENGTH];
			strcpy(str, BORROWToString(borrow));
			fputs(str, fptmp);
		}
		else
		{
			fputs(line, fptmp);
		}
	}
	fclose(fp);
	fclose(fptmp);
}*/
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
	printf("Ma doc gia tra sach :\n>");
	char input[TEXT_LENGTH];
	scanf("%s", input);

	int money=0;
	FILE*fp = fopen("borrow.csv", "r");
	char line[LINE_LENGTH];
	char tmp[LINE_LENGTH];
	char *tok,*tok2;
	BOOK tmpBook[3];
	bool returned = false;
	int c = 0;
	DATE today = getCurrentTime(0, 0, 0);

	while (fgets(line, LINE_LENGTH, fp))
	{
		strcpy(tmp, line);
		tok = strtok(tmp, ";");
		if (strcmp(input, tok) == 0)
		{
			
			tok = strtok(NULL, ";");
			printf("> Ngay muon sach : %s\n",tok);
			tok = strtok(NULL, ";");
			printf("> Ngay tra du kien : %s\n",tok);
			char DATEtmp[TEXT_LENGTH];
			strcpy(DATEtmp,DATEToString(today));
			printf("> Ngay tra thuc te : %s\n",DATEtmp );
			DATE returnDay= stringToDATE(tok);
			int lateDay = dateBetween(returnDay, today);
			if (lateDay > 0)
				printf("Tre hang %d ngay, tien phat : %d\n", lateDay, lateDay * 5000);
			else
				lateDay = 0;
			tok = strtok(NULL, ";");
			printf("> Nhap trang thai cua sach : (0: Sach bi mat , 1: Sach khong bi mat)\n");
			printf("============================\n");
			
			int n;
			
			tok2 = strtok_s(tok, ",",&tok);//tok2 = isbn1
			for (int i = 0;i < 3;i++) 
			{
				if (checkISBN(tok2, tmpBook[i]) != 0)
				{
					printf("> ISBN - %s : ", tmpBook[i].ISBN);
					scanf("%d", &n);
					if (n == 0)
					{
						money += tmpBook[i].price*2;
						printf("> Sach bi mat, gia bia : %d\n", tmpBook[i].price);
					}
					else
					{
						
					}
					tmpBook[i].borrowing--;
				}
				else
				{
					if (strcmp(tok2,"\n")!=0)
						printf("> Khong tim thay sach co ISBN = %s .Co ve nhu sach da bi xoa khoi CSDL\n", tok2);
				}
				tok2 = strtok_s(NULL, ",", &tok);
				c++;
				if (strcmp(tok2,"\n")==0) break;
			}
			returned = true;
			money += lateDay * 5000;
			printf("> Tong so tien phai tra la %d\n", money);
			break;
		}
	}
	
	fclose(fp);
	if (returned)
	{
		deleteBorrow(input);
		//Update lai so luong sach va xoa borrow
		for (int i = 0;i < c;i++)
		{
			saveBook(tmpBook[i]);
		}
	}
	else
		printf("Khong tim thay doc gia trong danh sach phieu muon\n");
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
#include "library.h"
int main()
{
	USER *current_user = (USER*)malloc(sizeof(USER));
	
	FILE *fp = fopen("user", "rb");
	if (!fp) 
	{
		createAdmin();
	}
	else
		fclose(fp);


	*current_user = login();
	system("pause");

	int n = 0;
	do
	{
		if ((current_user->status) != 0)
		{
			printMenu(*current_user, n);
		}
		else
		{
			system("cls");
			printf("> Tai khoan dang bi khoa\n");
			printf("> Vui long lien he admin de mo khoa\n");
			printf("> Nhan bat ky phim nao de dang xuat\n");
			logOut(*current_user);
		}
	} while (n != -1);
	
	return 0;
}
#include "user.h"

#include "borrow.h"
int main()
{
	USER *current_user = (USER*)malloc(sizeof(USER));
	current_user->type = 0;
	int n=0;
	do
	{
		printMenu(*current_user,n);
	} while (n != -1);

	
	//addBORROW();

	BOOK *current_book;
	return 0;
}
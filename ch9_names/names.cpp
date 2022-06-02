#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>

#include	"platform.h"
#include	"names.h"

static	void	process_number(int *);
static	bool	process_names(int);
static	void	print_names(int);
static  bool	alloc_mem(int);
static	void	final(int);
extern	bool	str_digit(char []);

static struct	name_info *name_n_count = NULL;

void	main()
{
	int number=0,
		exit_status = EXIT_FAILURE;

	process_number(&number);
	alloc_mem(number);

	final(number);

	exit(exit_status);
}

void	process_number(int * number)
{
	short	valid_number	=	false;
	long	hold_area;
	char	char_number[BUFSIZ + 1];


	while( !valid_number)
	{
		printf("Enter number of names:");
		fflush(stdin);
		gets(char_number);

		if(str_digit(char_number))
		{
			hold_area = atol(char_number);
			if(hold_area > 0 && hold_area < (NUMNAMES + 1) )
			{
				*number = hold_area;
				valid_number = true;
			}
			else
				printf("The Item Number must between 1 and %d inclusive\n",NUMNAMES);
		}
		else
				printf("The Item Number must be numeric\n");
	}
}

bool	process_names(int number)
{
	char	name[BUFSIZ + 1];
	bool	bad_name,
			process_success = true;


	for(int inx = 0; inx < number;inx++)
	{
		bad_name = true;
		while(bad_name && process_success)
		{
			printf("Enter the %1d name:",(inx + 1));
			fflush(stdin);
			gets(name);
			bad_name=false;
			for(int jnx = 0;name[jnx] != '\0';jnx++)
				if(name[jnx] != ' ')
					(name_n_count + inx)->char_count++;
			(name_n_count+inx)->names = (char *)malloc((strlen(name) + 1) * sizeof(char));
			if ((name_n_count + inx)->names != NULL)
				strcpy((name_n_count + inx)->names,name);
			else
				process_success = false;
		}
	}
	return process_success;
}

void	print_names(int number)
{
	for(int inx=0;inx < number;inx++)
		printf("There are %d characters in the %1d name:%s:\n",(name_n_count + inx)->char_count,(inx + 1),(name_n_count + inx)->names);
}


bool	alloc_mem(int number)
{
	bool alloc_success = false;

	if ((name_n_count = (struct name_info *)calloc(number, sizeof(struct name_info))) != NULL )
	{
		alloc_success = true;
		if (process_names(number))
			print_names(number);		
	}
	else
		printf("Failure to allocate memory for %1d occurances of name and count\n");

	return alloc_success;
}

void final(int number)
{
	for(int inx= 0; inx < number;inx++)
		if ((name_n_count + inx)->names != NULL)
			free((name_n_count + inx)->names);

	if(name_n_count != NULL)
		free(name_n_count);
}
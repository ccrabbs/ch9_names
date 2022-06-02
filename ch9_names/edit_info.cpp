#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "names.h"

bool	str_digit(char passed[])
{
	bool	is_a_real_number = true;

	for(int inx=0;passed[inx] != '\0';inx++)
		if(!(isdigit(passed[inx]) && is_a_real_number))
			is_a_real_number = false;
			
		
	return is_a_real_number;
}

void	str_upper(char conv_char[])
{
	for(int inx = 0;conv_char[inx] != '\0';inx++)
		conv_char[inx]=toupper(conv_char[inx]);
}


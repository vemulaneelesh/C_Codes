#include<stdio.h>

void main ()

{
	char str[20] = {"aaabbbbcccdd"};
	int i = 0, x = 1, counter = 1;

	while(str[i] != '\0')
	{
		while(str[i] == str[x])
		{
			x++;
			counter++;
		}
		printf("%s%d", str[i] ,counter);
		i = x;
		x = i + 1;
		counter = 1;
	}
}
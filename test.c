#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


void test(char *filename, char *ss)
{
	// strcpy(ss, "vvvv");
	filename += 2;
	// filename = "fsdf";
	printf("%s\n", filename);

}

int main()
{
	char *filename = malloc(sizeof(char) * 5);
	strcpy(filename, "abcd");

	printf("%s\n", filename);

	test(filename, filename);

	printf("%s\n", filename);

}
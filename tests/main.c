#include <stdlib.h>
#include <stdio.h>
#include "get_next_line.h"

int main(int argc, char **argv)
{
	printf("%d %s\n", argc, argv[0]);
	system("ls");
	system("pwd");
	FILE *file = fopen("test-01.txt", "r");
	int fd = fileno(file);
	char *line = get_next_line(fd);
	printf("%s", line);
	free(line);
	return 0;
}
#!/bin/bash

cc -Wall -Wextra -Werror main.c ../task/get_next_line.c \
	../task/get_next_line_utils.c -I../task -o test-01.exe
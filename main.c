/*
* ---------------------------------------------------------------------
* #############################################
* Copyright (c) 2015-2035 kuramal All rights reserved.
* #############################################
*
* Name:  main.c
* Date:  2015-04-28 21:47
* Author:   kuramal
* Desc:  
*
* ---------------------------------------------------------------------
*/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

int file_porter(char *src_dir, char *dst_dir)
{
	int ret;
	DIR *cur_dir;
	struct dirent *dir_ptr = NULL;
	
	if (access(dst_dir, F_OK) != 0){

		ret = mkdir(dst_dir, 0);
		if (ret){
			printf("mkdir %s ERR\n", dst_dir);
			return ret;
		}
	}

	cur_dir = opendir(src_dir);

	while( (dir_ptr = (readdir(cur_dir))) != NULL){
		printf("%s \n", dir_ptr->d_name);
	}

	closedir(cur_dir);
	
	return 0;
}

int main(int argc, char **argv)
{
	
	char *src_dir = "./";
	char *encrypt_dir = "./wakeup";

	file_porter(src_dir, encrypt_dir);	

        return 0;
}


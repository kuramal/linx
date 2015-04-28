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


int copy_file(char *src_dir, char *dst_dir, char *file_name) 
{
	FILE *dst_ptr;
	char src_file[256] = {'\0',};
	char dst_file[256] = {'\0',};

	snprintf(src_file, sizeof(src_file), "%s/%s", src_dir, file_name);
	snprintf(dst_file, sizeof(dst_file), "%s/%s", dst_dir, file_name);

	dst_ptr = fopen(dst_file, "w");	

	fclose(dst_ptr);
	return 0;
}

int file_porter(char *src_dir, char *dst_dir)
{
	int ret;
	DIR *cur_dir;

	printf("src dir %s\n", src_dir);
	printf("dst dir %s\n", dst_dir);
	printf("#######################\n");

	char new_src_dir[256] = {'\0',};
	char new_dst_dir[256] = {'\0',};

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

		if (strncmp(dir_ptr->d_name, ".", 1) == 0 || strcmp(dir_ptr->d_name, "wakeup") == 0){
			continue;
		}

		if (dir_ptr->d_type == DT_DIR){
			
			snprintf(new_src_dir, sizeof(new_src_dir), "%s/%s", src_dir, dir_ptr->d_name);			
			snprintf(new_dst_dir, sizeof(new_dst_dir), "%s/%s", dst_dir, dir_ptr->d_name);			

			file_porter(new_src_dir, new_dst_dir);

		}else if (dir_ptr->d_type == DT_REG){
			
			copy_file(src_dir, dst_dir, dir_ptr->d_name);	
		}
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


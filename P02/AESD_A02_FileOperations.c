#include <stdio.h>
#include <stdlib.h>


FILE * FileOp_ptrF; 							//File Pointer

int main()
{
	printf("File Fun! \n");
	FileOp_ptrF = fopen("FileOp_fOutput.txt","w");			//Open a File for writing
	if(FileOp_ptrF == NULL)
	{
		printf("Error : File does not exist \n");
		exit(1);
	}
	chmod("FileOp_fOutput.txt",0666); 				//Editing file permissions to read-write
	fputc('t',FileOp_ptrF);
	fclose(FileOp_ptrF);
	FileOp_ptrF = NULL;

	FileOp_ptrF = fopen("FileOp_fOutput.txt","a");			//Open a File in Append Mode
	if(FileOp_ptrF == NULL)
	{
		printf("Error : File does not exist \n");
		exit(1);
	}	
	int FileOp_lenArr = 124; 					//Number of Array Elements
	char * FileOp_aptrStr = (char *)malloc(sizeof(char) * FileOp_lenArr);
	printf("Enter a string to append to the file : \n");
	fgets(FileOp_aptrStr,FileOp_lenArr,stdin);
	fputs(FileOp_aptrStr,FileOp_ptrF); 
	fflush(FileOp_ptrF);
	

	FileOp_ptrF = fopen("FileOp_fOutput.txt","r");			//Open the File in Read Mode
	if(FileOp_ptrF == NULL)
	{
		printf("Error : File does not exist \n");
		exit(1);
	}
	
	char FileOp_chTemp = fgetc(FileOp_ptrF);
	printf("Single Character from file : %c \n",FileOp_chTemp);
	
	printf("String of Characters from file : \n");
	while(!feof(FileOp_ptrF))
	{
		FileOp_chTemp =  fgetc(FileOp_ptrF); 
		printf("%c",FileOp_chTemp);
	}
	printf("\n");
	fclose(FileOp_ptrF);
	free(FileOp_aptrStr);
	FileOp_ptrF = NULL;
}

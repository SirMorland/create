#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define NAME	"create"
#define VERSION	"0.1"

char* argv0;
const char* fileType;
const char* fileName = "out";
char* content;

int handleFlag(const char* argv[], int index)
{
	for (int i = 1; i < strlen(argv[index]); i++)
	{
		switch (argv[index][i])
		{
			case 'o':
				if (argv[index + 1] != NULL)
				{
					fileName = argv[index + 1];
					return 1;
				}
				else
				{
					printf("File name is required with flag \"-o\"\n");
					return -1;
				}
			case 'h':
				printf("Usage:\n\tcreate filetype [-o filename] [-\033[1m\033[30mh\033[0melp] [-\033[1m\033[30mv\033[0mersion]\n");
				return -1;
			case 'v':
				printf(NAME " " VERSION "\n");
				return -1;
			default:
				return 0;
		}
	}
}

int getFileType(const char* argument)
{
	char type[strlen(argument) + 1];

	for (int i = 0; i <= strlen(argument); i++)
	{
		type[i] = tolower(argument[i]);
	}

	char filePath[strlen(argv0) + strlen("defaults/") + strlen(type) * 2 + 1];
	strcpy(filePath, argv0);
	strcat(filePath, "defaults/");
	strcat(filePath, type);
	strcat(filePath, ".");
	strcat(filePath, type);
	FILE *file = fopen(filePath, "r");

	if (file != NULL)
	{
		fileType = argument;

		fseek(file, 0, SEEK_END);
		int size = ftell(file);
		rewind(file);

		content = (char*)malloc(sizeof(char) * (size + 1));
		fread(content, sizeof(char), size, file);
		content[size] = '\0';

		fclose(file);
	}
	else
	{
		printf("\"%s\" filetype is not yet supported. Please create \"%s.%s\" file to %sdefaults/ directory.\n", type, type, type, argv0);
		return -1;
	}
}

int main (int argc, const char* argv[])
{
	argv0 = (char*)malloc(sizeof(char) * (strlen(argv[0]) - strlen(NAME)));
	for (int i = 0; i < strlen(argv[0]) - strlen(NAME); i++)
	{
		argv0[i] = argv[0][i];
	}

	for (int i = 1; i < argc; i++)
	{
		if (argv[i][0] == '-')
		{
			int a = handleFlag(argv, i);
			if (a > 0)
			{
				i += a;
			}
			if (a == -1)
			{
				return -1;
			}
		}
		else
		{
			int success = getFileType(argv[i]);
			if (success == -1)
			{
				return -1;
			}
		}
	}

	if (fileType == NULL)
	{
		printf("File type is required!\n");
		return -1;
	}

	FILE *file = fopen(fileName, "w");
	fprintf(file, "%s", content);
	fclose(file);

	printf("Created file %s!\n", fileName);

	return 0;
}

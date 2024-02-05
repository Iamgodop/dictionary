#include <stdio.h>
#include <string.h>
#define get_next_token() (strtok(NULL, delimitor))

void main()
{
	char api[200], word[50], file_content[5000], delimitor[] = "\"", vlc_cmd[100], *buffer = malloc(100);
	printf("Enter word: ");
	gets(word);
	sprintf(api, "curl \"https://api.dictionaryapi.dev/api/v2/entries/en/%s\" > word_data.txt", word);
	system(api);
	FILE *fp_word = fopen("word_data.txt", "r");
	fgets(file_content, 5000, fp_word);
	buffer = strtok(file_content, delimitor);
	do
	{
		buffer = get_next_token();
	}while (strcmp(buffer, "audio"));
	buffer = get_next_token();
	buffer = get_next_token();
	sprintf(vlc_cmd, "%s%s\"", "start vlc \"", buffer);
	while (strcmp(buffer,"definition"))
	{
		buffer = get_next_token();
	}
	buffer = get_next_token();
	buffer = get_next_token();
	printf("\nThe meaning for word %s: %s.\n", word, buffer);
	printf("Play pronounciation[YES:1/No:0]: ");
	if (getch() == '1')
	{
		system(vlc_cmd);
	}
}
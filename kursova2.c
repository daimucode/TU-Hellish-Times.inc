#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Dictionary{

	char transWordEng[20];
	char transWordBg[20];
	char transWordGer[20];
	char typeOfWord[20];
	char exampLine[50];
	char date[21];
	float rating;
	struct Dictionary *next;
}Dictionary;

Dictionary* readFile(char filename[]){

	FILE *fp=fopen(filename,"rb");
	Dictionary *current = (Dictionary*)malloc(sizeof(Dictionary));
	Dictionary *head = NULL; 
	Dictionary *prev = NULL;
	while(fread(current, sizeof(Dictionary), 1, fp) == 1) {
		if(prev == NULL)
			head = current;

		current->next = (Dictionary*)malloc(sizeof(Dictionary));
		prev = current;
		
		current = current->next;
	}
	fclose(fp);

	free(prev->next);
	prev->next = NULL;

	return head;
}

void addWord(){
	
	int lang;
	printf("Lang:\n");
	scanf("%d",&lang);
	
	FILE *fp;
	Dictionary *newWord=(Dictionary*)malloc(sizeof(Dictionary));

	printf("If there is no translation, insert -1\n");
	
	if(lang==1){
		fp = fopen("eng.lang","ab");

		printf("\n\tEnter english word: ");
		scanf("%s", newWord->transWordEng);

		printf("\n\tNow enter bulgarian translation: ");
		scanf("%s", newWord->transWordBg);

		printf("\n\tNow enter german translation: ");
		scanf("%s", newWord->transWordGer);
	}
	else if(lang==2){
		fp = fopen("bg.lang","ab");

		printf("\n\tEnter bulgarian word: ");
		scanf("%s", newWord->transWordBg);

		printf("\n\tNow enter english translation: ");
		scanf("%s", newWord->transWordEng);

		printf("\n\tNow enter german translation: ");
		scanf("%s", newWord->transWordGer);
	}
	else if(lang==3){
		fp = fopen("ger.lang","ab");

		printf("\n\tEnter german word: ");
		scanf("%s", newWord->transWordGer);

		printf("\n\tNow enter english translation: ");
		scanf("%s", newWord->transWordEng);

		printf("\n\tNow enter bulgarian translation: ");
		scanf("%s", newWord->transWordBg);	
	}

	printf("\n\tEnter the class of the word(noun, verb, adjective): ");
	scanf("%s", newWord->typeOfWord);

	printf("\n\tEnter an example translation: ");
	scanf("%s", newWord->exampLine);

	printf("\n\tEnter the date of adding(DD/MM/YY): ");
	scanf("%s", newWord->date);

	printf("\n\tEnter a rating of the translation(0 to 10): ");
	scanf("%f", newWord->rating);
	
	fwrite(newWord,sizeof(Dictionary),1,fp);
	free(newWord);
	fclose(fp);
}

void search(){

	char word[20];
	int lang;

	printf("Insert a word:\n");
	scanf("%s", word);
	printf("Choose a language to be searched.\n1.English\n2.Bulgarian\n3.German;");
	scanf("%d", &lang);

	Dictionary *dict=(Dictionary*)malloc(sizeof(Dictionary));
	Dictionary *head;
	
	if(lang==1){
		head=readFile("eng.lang");
	}
	else if(lang==2){
		head=readFile("bg.lang");
	}
	else if(lang==3){
		head=readFile("ger.lang");
	}

	dict=head;
	
	while(dict!=NULL){
		
	if(lang==1){
		if(strcmp(dict->transWordEng, word)==0){
			printf("In english: %s\nIn bulgarian: %s\nIn german: %s\nClass of word: %s\nExample: %s\nDate added: %f\nRating: %f\n", 
				dict->transWordEng, dict->transWordBg, dict->transWordGer, dict->typeOfWord, dict->exampLine, dict->date, dict->rating);
		}
		
	}
	else if(lang==2){
		if(strcmp(dict->transWordBg, word)==0){
			printf("In bulgarian: %s\nIn english: %s\nIn german: %s\nClass of word: %s\nExample: %s\nDate added: %f\nRating: %f\n", 
				 dict->transWordBg, dict->transWordEng, dict->transWordGer, dict->typeOfWord, dict->exampLine, dict->date, dict->rating);
		}
	}
	else if(lang==3){
		if(strcmp(dict->transWordGer, word)==0){
			printf("In german: %s\nIn english: %s\nIn bulgarian: %s\nClass of word: %s\nExample: %s\nDate added: %f\nRating: %f\n", 
				dict->transWordGer, dict->transWordEng, dict->transWordBg,  dict->typeOfWord, dict->exampLine, dict->date, dict->rating);
		}
	}
		dict = dict->next;
	}
	free(dict);
}

void unique(){
	Dictionary *dict=(Dictionary*)malloc(sizeof(Dictionary));
	Dictionary *dict2=(Dictionary*)malloc(sizeof(Dictionary));
	Dictionary *dict3=(Dictionary*)malloc(sizeof(Dictionary));

	Dictionary *head1;
	Dictionary *head2;
	Dictionary *head3;
	
	head1=readFile("eng.lang");
	head2=readFile("bg.lang");
	head3=readFile("ger.lang");

	int isWordFound = 0;

	for (dict = head1; dict != NULL; dict=dict->next) {
		for (dict2 = head2; dict2!=NULL; dict2=dict2->next) {
			if(strcmp(dict->transWordEng, dict2->transWordBg) == 0)	
				isWordFound = 1;		
		}

		for (dict3 = head3; dict3!=NULL; dict3=dict3->next) {
			if(strcmp(dict->transWordEng, dict3->transWordGer) == 0)	
				isWordFound = 1;		
		}
		
		if(!isWordFound)
			printf("%s\n", dict->transWordEng);

		isWordFound = 0;
	}
}

int main(int argc, char** argv) {

	int menu;

			start:
			printf("1.Add word.\n");
			printf("2.Search for a word in a dictionary.\n");
			printf("3.Print all unique words.\n");
			printf("4.Exit\n");
			scanf("%d", &menu);
			switch (menu){
				case 1:
					addWord();
					break;
				case 2:
					search();
					break;
				case 3:
					unique();
					break;
				case 5:
					exit(1);
				default:
					printf("Wrong choice. Enter again.\n");
					goto start;
					break;
			}

	return 0;
}



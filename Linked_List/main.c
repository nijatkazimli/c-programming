#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LENGTH 46

typedef struct {
	char string[MAX_WORD_LENGTH + 1];
	int len;
} Word;

typedef struct LE {
	Word word;
	struct LE *prev;
	struct LE *next;
} ListElement;

typedef struct {
	ListElement *head;
	ListElement *tail;
} List;

void PrintWord(const Word *d) {
	printf("%s ", d->string);
}

//1p
Word SetWord(const char *word);

ListElement *CreateElement(const char *str);

//2p
void InsertFirst(ListElement *el, List *list);

void PrintListRev(const List *list);

void DeleteList(List *list);

//1p
double AvgWordsLength(const List *list);

void BuildList(List *list, char *str)
{

	char *p;
	p = strtok(str, " \t,.");
	while (p) {
		InsertFirst(CreateElement(p), list);
		p = strtok(NULL, " \t,.");
	}
}


//4p
ListElement *UnlinkElement(List *list, ListElement *el);


int main(void)
{
	
	puts("----- PART 1 ------");
	Word tmp_label;
	ListElement *le;
	tmp_label = SetWord("test");
	printf("Word \"%s\" has %d  characters\n", tmp_label.string, tmp_label.len);
	PrintWord(&tmp_label);
	le = CreateElement("Last");
	PrintWord(&le->word);
	
	//2p
	
	puts("\n----- PART 2 ------");
	List mylist = { NULL,NULL };
	InsertFirst(le, &mylist);
	InsertFirst(CreateElement("Next one"), &mylist);
	PrintListRev(&mylist);
	DeleteList(&mylist);
	

	//1p
	
	puts("\n----- PART 3 ------");
	char str[80];
	strcpy(str, "xyz test abc mix of words for Programming1");
	BuildList(&mylist, str);
	PrintListRev(&mylist);
	printf("Average length of words = %lf\n", AvgWordsLength(&mylist));
	DeleteList(&mylist);
	PrintListRev(&mylist);
	
	puts("\nBye!");
	return 0;
}

Word SetWord(const char* word)
{
	Word wrd;
	strncpy(wrd.string, word, MAX_WORD_LENGTH);
	wrd.len = (int)strlen(word);
	return wrd;
}

ListElement* CreateElement(const char* str)
{
	ListElement* el = (ListElement*)malloc(sizeof(ListElement));
	if (!el)
		return NULL;
	else
	{
		el->word = SetWord(str);
		el->next = NULL;
		el->prev = NULL;
		return el;
	}
}

void InsertFirst(ListElement* el, List* list)
{
	if (list->head == NULL)
	{
		list->head = el;
		list->tail = el;
	}
	else
	{
		el->next = list->head;
		list->head->prev = el;
		list->head = el;
	}
}

void PrintListRev(const List* list)
{
	if (list->head == NULL || list == NULL)
		printf("The list is empty!\n");
	else
	{
		ListElement* temp = list->tail;
		printf("List: ");
		while (temp)
		{
			PrintWord(&temp->word);
			temp = temp->prev;
		}
		printf("\n");
	}
}

void DeleteList(List* list)
{
	while(list->head)
	{
		ListElement* temp = list->head;
		list->head = list->head->next;
		free(temp);
	}
}

double AvgWordsLength(const List* list)
{
	if (list->head == NULL)
		return 0;
	double sum = 0;
	int counter = 0;
	ListElement* temp = list->head;
	while(temp)
	{
		sum += temp->word.len;
		counter++;
		temp = temp->next;
	}
	return sum / counter;
}

ListElement* UnlinkElement(List* list, ListElement* el)
{
	if (list->head == NULL)
		return NULL;
	else if (list->head == el && list->tail == el)
	{
		list->head = list->tail = NULL;
		return el;
	}
	else if (list->head == el && list->head->next != NULL)
	{
		list->head = list->head->next;
		list->head->prev = NULL;
		el->next = NULL;
		return el;
	}
	else if (list->tail == el && list->head != el)
	{
		list->tail = list->tail->prev;
		list->tail->next = NULL;
		el->prev = NULL;
		return el;
	}
	else
	{
		el->prev->next = el->next;
		el->next->prev = el->prev;
		el->next = NULL;
		el->prev = NULL;
		return el;
	}
}

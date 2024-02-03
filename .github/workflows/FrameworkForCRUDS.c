// Framework for CRUDS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LENGTH_OF_FIELD_DATA 100
#define LENGTH_OF_FIELD_NAME 100
#define LENGTH_OF_CUSTOMIZED_MESSAGE 100
#define COUNT_OF_CUSTOMIZED_MESSAGES 4
#define FIELD_NAMES_FILE "FieldNames.cfg"
#define MENU_FILE "Menu.cfg"
#define FRAMEWORKS_DATA_FILE "Frameworks.dat"
#define CUSTOMIZED_MESSAGES_FILE "CustomizedMessages.cfg"

FILE *fpFieldNames;
FILE *fpMenu;
FILE *fpFrameworks;
FILE *fpCustomizecMessages;

int CounterOfFieldNames;
int CountOfFieldNames = 0;

char FieldName[LENGTH_OF_FIELD_NAME];
char FieldData[LENGTH_OF_FIELD_DATA];
char CustomizedMessages[COUNT_OF_CUSTOMIZED_MESSAGES][LENGTH_OF_CUSTOMIZED_MESSAGE];
char Active = 'A';
char Deleted = 'D';
char Status;
char SearchRecordId[LENGTH_OF_FIELD_DATA];
char **FieldNames;

void ShowMenu();
void Create();
void ShowAllRecords();
void UpdateRecord();
void DeleteRecord();
void SearchRecord();
void GetFieldsArray();
void GetCustomizedMessagesArray();
void CountFieldNames();
void RemoveNewLineCharacterFromFieldName();
void ShowRecordData();
char* GetRecordId();
int IsFileNotEmpty();

void main()
{
	fpFieldNames = fopen(FIELD_NAMES_FILE, "r");

	CountFieldNames();
	GetFieldsArray();

	fclose(fpFieldNames);

	GetCustomizedMessagesArray();

	fpMenu = fopen(MENU_FILE, "r");

	while (1)
	{
		ShowMenu();
	}	

	fclose(fpMenu);
}

void GetCustomizedMessagesArray()
{
	int CounterOfCustomizedMessages;
	int LastIndexOfCustomizedMessage;

	fpCustomizecMessages = fopen(CUSTOMIZED_MESSAGES_FILE, "r");

	for (CounterOfCustomizedMessages = 0; CounterOfCustomizedMessages < COUNT_OF_CUSTOMIZED_MESSAGES; CounterOfCustomizedMessages++)
	{
		fgets(CustomizedMessages[CounterOfCustomizedMessages], LENGTH_OF_CUSTOMIZED_MESSAGE * sizeof(char), fpCustomizecMessages);

		LastIndexOfCustomizedMessage = strlen(CustomizedMessages[CounterOfCustomizedMessages]);

		if (CustomizedMessages[CounterOfCustomizedMessages][LastIndexOfCustomizedMessage - 1] == '\n')
		{
			CustomizedMessages[CounterOfCustomizedMessages][LastIndexOfCustomizedMessage - 1] = '\0';
		}

	}

	fclose(fpCustomizecMessages);
}

void GetFieldsArray()
{

	FieldNames = (char**)malloc(CountOfFieldNames * sizeof(char*));

	for (CounterOfFieldNames = 0; CounterOfFieldNames < CountOfFieldNames; CounterOfFieldNames++)
	{

		fgets(FieldName, sizeof(FieldName), fpFieldNames);

		RemoveNewLineCharacterFromFieldName(FieldName);

		FieldNames[CounterOfFieldNames] = (char*)malloc(LENGTH_OF_FIELD_NAME * sizeof(char));

		strcpy(FieldNames[CounterOfFieldNames], FieldName);

	}
}

void RemoveNewLineCharacterFromFieldName()
{
	int LastIndexOfFieldName = strlen(FieldName);

	if (FieldName[LastIndexOfFieldName - 1] == '\n')
	{
		FieldName[LastIndexOfFieldName - 1] = '\0';
	}
}

void ShowMenu()
{

	fseek(fpMenu, 0, SEEK_END);

	int LengthOfMenu = ftell(fpMenu);

	char Menu[LengthOfMenu];

	rewind(fpMenu);

	if (LengthOfMenu != 0)
	{
		fread(Menu, LengthOfMenu * sizeof(char), 1, fpMenu);

		fwrite(Menu, LengthOfMenu * sizeof(char) - 6, 1, stdout);
	}

	int Choice;

	printf("\nEnter your choice here: ");
	scanf("%d", &Choice);

	switch (Choice)
	{
		case 1: Create();
			break;

		case 2: ShowAllRecords();
			break;

		case 3: UpdateRecord(GetRecordId());
			break;

		case 4: DeleteRecord(GetRecordId());
			break;

		case 5: SearchRecord(GetRecordId());
			break;

		case 0: exit(0);

		default: printf("\nEntered invalid choice.\n");
	}
}

void Create()
{
	Status = Active;

	fpFrameworks = fopen(FRAMEWORKS_DATA_FILE, "a");

	if (fpFrameworks != NULL)
	{
		fwrite(&Status, sizeof(char), 1, fpFrameworks);

		for (CounterOfFieldNames = 0; CounterOfFieldNames < CountOfFieldNames; CounterOfFieldNames++)
		{
			printf("Enter %s: ", FieldNames[CounterOfFieldNames]);
			scanf(" %[^\n]s", FieldData);

			fwrite(FieldData, sizeof(FieldData), 1, fpFrameworks);
		}

		printf("\n%s\n", CustomizedMessages[0]);
	}
	else
	{
		printf("\nError occured while opening file.\n");
	}

	fclose(fpFrameworks);
}

void ShowAllRecords()
{

	if (IsFileNotEmpty() != 0)
	{
		fpFrameworks = fopen(FRAMEWORKS_DATA_FILE, "r");

		while (fread(&Status, sizeof(char), 1, fpFrameworks))
		{
			if (Status == Active)
			{
				ShowRecordData();
			}
			else
			{
				fseek(fpFrameworks, CounterOfFieldNames * sizeof(FieldData), SEEK_CUR);
			}	

		}

		fclose(fpFrameworks);
	}	
}

void ShowRecordData()
{
	printf("\n");

	for (CounterOfFieldNames = 0; CounterOfFieldNames < CountOfFieldNames; CounterOfFieldNames++)
	{
		fread(FieldData, sizeof(FieldData), 1, fpFrameworks);

		printf("%s: %s\n", FieldNames[CounterOfFieldNames], FieldData);
	}

	printf("***************************************************************\n");
}

int GetRrecordPosition(char *SearchRecordId)
{
	if (IsFileNotEmpty != 0)
	{
		int RecordPosition = -1;

		fpFrameworks = fopen(FRAMEWORKS_DATA_FILE, "r");

		while (fread(&Status, sizeof(char), 1, fpFrameworks) != 0)
		{
			if (Status == Active)
			{
				fread(FieldData, sizeof(FieldData), 1, fpFrameworks);

				if (strcmp(FieldData, SearchRecordId) == 0)
				{
					RecordPosition = ftell(fpFrameworks);
				}
				else
				{
					fseek(fpFrameworks, (CountOfFieldNames - 1) * sizeof(FieldData), SEEK_CUR);
				}
			}
			else
			{
				fseek(fpFrameworks, CountOfFieldNames * sizeof(FieldData), SEEK_CUR);
			}
		}

		if (RecordPosition < 0)
		{
			printf("\n%s %s is not found.\n", FieldNames[0], SearchRecordId);
		}

		return RecordPosition;
	}
}
void UpdateRecord(char *SearchRecordId)
{
	int RecordPosition = GetRrecordPosition(SearchRecordId);

	if (RecordPosition > 0)
	{
		int ChoiceForUpdate;

		for (CounterOfFieldNames = 1; CounterOfFieldNames < CountOfFieldNames; CounterOfFieldNames++)
		{
			printf("		%d. Update %s\n", (CounterOfFieldNames - 1), FieldNames[CounterOfFieldNames]);
		}

		printf("Enter your choice: ");
		scanf("%d", &ChoiceForUpdate);

		printf("Enter %s: ", FieldNames[(ChoiceForUpdate + 1)]);
		scanf(" %[^\n]", FieldData);

		fpFrameworks = fopen(FRAMEWORKS_DATA_FILE, "r+");

		fseek(fpFrameworks, RecordPosition * sizeof(char), SEEK_SET);
		fseek(fpFrameworks, ChoiceForUpdate * sizeof(FieldData), SEEK_CUR);

		fwrite(&FieldData, sizeof(FieldData), 1, fpFrameworks);

		fclose(fpFrameworks);

		printf("\n%s\n", CustomizedMessages[1]);
	}
}

void DeleteRecord(char *SearchRecordId)
{
	int RecordPosition = GetRrecordPosition(SearchRecordId);

	if (RecordPosition > 0)
	{
		Status = Deleted;

		fpFrameworks = fopen(FRAMEWORKS_DATA_FILE, "r+");

		fseek(fpFrameworks, RecordPosition * sizeof(char), SEEK_SET);
		fseek(fpFrameworks, -sizeof(FieldData), SEEK_CUR);
		fseek(fpFrameworks, -sizeof(char), SEEK_CUR);

		fwrite(&Status, sizeof(char), 1, fpFrameworks);

		fclose(fpFrameworks);

		printf("\n%s\n", CustomizedMessages[2]);
	}
}

void SearchRecord(char *SearchRecordId)
{
	int RecordPosition = GetRrecordPosition(SearchRecordId);

	if (RecordPosition > 0)
	{
		fpFrameworks = fopen(FRAMEWORKS_DATA_FILE, "r");

		fseek(fpFrameworks, RecordPosition * sizeof(char), SEEK_SET);
		fseek(fpFrameworks, -sizeof(FieldData), SEEK_CUR);

		ShowRecordData();

		fclose(fpFrameworks);
	}
}

int IsFileNotEmpty()
{
	int FileStatus = 0;

	fpFrameworks = fopen(FRAMEWORKS_DATA_FILE, "r");

	fseek(fpFrameworks, 0, SEEK_END);

	if (ftell(fpFrameworks) > 0)
	{
		FileStatus = 1;
	}
	else
	{
		printf("\n%s\n", CustomizedMessages[4]);
	}

	fclose(fpFrameworks);

	return FileStatus;
}

char* GetRecordId()
{
	printf("Enter %s: ", FieldNames[0]);
	scanf(" %[^\n]", SearchRecordId);

	return SearchRecordId;
}

void CountFieldNames()
{
	if (fpFieldNames != NULL)
	{
		while (fgets(FieldName, sizeof(FieldName), fpFieldNames) != 0)
		{
			CountOfFieldNames++;
		}
	}
	else
	{
		printf("\nError occured while opening file.\n");
	}

	rewind(fpFieldNames);
}

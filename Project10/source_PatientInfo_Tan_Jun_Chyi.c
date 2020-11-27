#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"date.h"
#include"general.h"
#include"GroupUseFunction.h"
#pragma warning (push , 4)
#pragma warning (disable : 4090 4996 4204)
/// leader add
#ifndef GROUP_USE_FUNCTION_INLINE
#define TRUE 1
#define FALSE 0
#define PATIENT_FILE "bfpatient.dat"

typedef struct Struct_patient {
	char     patientID[11];
	char     name[51];
	Gender   gender;
	char     contactNum[51];
	char     allergies[51];
	DateTime birthday;
}PatientInfo;

PatientInfo const NULL_PATIENT = { "<ID>","<name>",'\0',"<contact>","<allergies>",
									{ 0,0,0,"00/00/0000","00:00xx", 0, 0 } };

#define SIZE_PATIENT 50
/// intergration add
#endif
int index = 0;
PatientInfo patient[SIZE_PATIENT];

/// module
void delete_patient_TJC(void);
void patient_search_TJC(void);
void patient_modify_TJC(void);
void patient_display_TJC(void);
void patient_add_TJC(void);

/// Input Function
void scanf_patient(PatientInfo *data);
void get_patient_ID(PatientInfo *data);

/// Output Function
void printf_Header_TJC();
void printf_MaxLine_TJC();
void printf_patient_TJC(PatientInfo data, int i);

/// Unformated Stream I/O
void fwrite_patient(PatientInfo *data);
int fread_patient(PatientInfo *data);
void creat_patient_file();

void patientInfo_Menu()
{
	int checkSave = FALSE;
	int loop = FALSE;
	int selection;
	int selection2;
	// Initialise Data
	for (int i = 0; i < SIZE_PATIENT; i++)
	{
		patient[i] = NULL_PATIENT;
	}
	creat_patient_file();
	checkSave = TRUE;
	do {
		system_logo();
		selection = get_selection_int(7,
			"Search Patient",
			"Modify Patient",
			"Display Patient",
			"Add Patient",
			"Save Patient",
			"Delete Patient",
			"Exit");
		index = fread_patient(patient);
		if (selection != 7)
			out_MessageBox("System Is Reading The Data From File");
		system_loading();
		switch (selection)
		{
		case 1:
			patient_search_TJC();
			loop = TRUE;
			break;
		case 2:
			patient_modify_TJC();
			checkSave = FALSE;
			loop = TRUE;
			system_loading();
			break;
		case 3:
			patient_display_TJC();
			loop = TRUE;
			system_loading();
			break;
		case 4:
			system_logo();
			patient_add_TJC();
			checkSave = FALSE;
			loop = TRUE;
			system_loading();
			break;
		case 5:
			system_logo();
			selection2 = get_selection_int(2, "Comfirm Save Data", "Exit");
			if (selection2 == 1)
			{
				fwrite_patient(patient);
				out_MessageBox("The Following Data Is Saved");
				checkSave = TRUE;
			}
			loop = TRUE;
			system_loading();
			break;
		case 6:
			delete_patient_TJC();
			checkSave = FALSE;
			loop = TRUE;
			system_loading();
			break;
		case 7:
			system_logo();
			if (checkSave == FALSE)
			{
				out_MessageBox("Do You Want To Exit Without Saving!!");
				selection2 = get_selection_int(2, "Yes", "No");
				if (selection2 == 1)
					loop = FALSE;
				else
				{
					loop = TRUE;
					system("cls");
				}
			}
			else
			{
				out_MessageBox("Exited From Patient Application");
				loop = FALSE;
			}
			break;
		}
		fwrite_patient(patient);
	} while (loop);
}

void patient_search_TJC(void)
{
	int loop = FALSE;
	int selection;
	int searchCount = 0;
	char userinput[51];
	Gender userinput2 = NULL_GENDER;
	DateTime userinput3 = NULL_DATETIME;
	do {
		system_logo();
		printf(MAX_BLANK_SHORT"Search by the following choice : \n");
		selection = get_selection_int(7,
			"Patient Name",
			"Patient Gender",
			"Contact Number",
			"Allergies Of Patient",
			"Patient ID",
			"Patient Birthday",
			"Exit");
		rewind(stdin);
		system_loading();
		switch (selection)
		{
		case 1:
			system_logo();
			printf(INPUT_OFFSET"PLease enter patient name : ");
			scanf("%[^\n]", userinput);
			loop = TRUE;
			rewind(stdin);
			printf_MaxLine_TJC();
			printf_Header_TJC();
			printf_MaxLine_TJC();
			break;
		case 2:
			system_logo();
			userinput2 = get_Gender();
			loop = TRUE;
			rewind(stdin);
			printf_MaxLine_TJC();
			printf_Header_TJC();
			printf_MaxLine_TJC();
			break;
		case 3:
			system_logo();
			printf(INPUT_OFFSET"PLease enter contact number of patient : ");
			scanf("%[^\n]", userinput);
			loop = TRUE;
			rewind(stdin);
			printf_MaxLine_TJC();
			printf_Header_TJC();
			printf_MaxLine_TJC();
			break;
		case 4:
			system_logo();
			printf(INPUT_OFFSET"PLease enter allergies of patient : ");
			scanf("%[^\n]", userinput);
			loop = TRUE;
			rewind(stdin);
			printf_MaxLine_TJC();
			printf_Header_TJC();
			printf_MaxLine_TJC();
			break;
		case 5:
			system_logo();
			printf(INPUT_OFFSET"PLease enter ID of patient : ");
			scanf("%[^\n]", userinput);
			loop = TRUE;
			rewind(stdin);
			printf_MaxLine_TJC();
			printf_Header_TJC();
			printf_MaxLine_TJC();
			break;
		case 6:
			system_logo();
			do {
				get_In_fDate("Birthday", &userinput3);
			} while (!isDate(userinput3));
			rewind(stdin);
			printf_MaxLine_TJC();
			printf_Header_TJC();
			printf_MaxLine_TJC();
			break;
		case 7:
			loop = FALSE;
			break;
		}
		searchCount = 0;
		for (int i = 0; i < SIZE_PATIENT; i++)
		{
			switch (selection)
			{
			case 1:
				strupr(userinput);
				if (strcmp(userinput, patient[i].name) == 0)
				{
					printf_patient_TJC(patient[i], searchCount);
					searchCount++;
				}
				break;
			case 2:
				if ((userinput2 == patient[i].gender))
				{
					printf_patient_TJC(patient[i], searchCount);
					searchCount++;
				}
				break;
			case 3:
				if (strcmp(userinput, patient[i].contactNum) == 0)
				{
					printf_patient_TJC(patient[i], searchCount);
					searchCount++;
				}
				break;
			case 4:
				strupr(userinput);
				if (strcmp(userinput, patient[i].allergies) == 0)
				{
					printf_patient_TJC(patient[i], searchCount);
					searchCount++;
				}
				break;
			case 5:
				if (strcmp(userinput, patient[i].patientID) == 0)
				{
					printf_patient_TJC(patient[i], searchCount);
					searchCount++;
				}
				break;
			case 6:
				if (cmpDate(&userinput3, &patient[i].birthday))
				{
					printf_patient_TJC(patient[i], searchCount);
					searchCount++;
				}
				break;
			}
		}
		if(loop)
		{
			printf_MaxLine_TJC();
			puts("\n\n\n");
			system_loading();
		}
	} while (loop);
}

void patient_modify_TJC(void)
{
	int loop = TRUE;
	int selection;
	int modify;
	out_MessageBox("Select you modify choice :");
	patient_display_TJC();
	printf(INPUT_OFFSET"PLease enter the No. need to modify (Other = EXIT)--> ");
	scanf("%d", &modify);
	if (modify >= 1 && modify <= index)
	{
		system_loading();
		modify = modify - 1;
		do {
			system_logo();
			selection = get_selection_int(7,
				"Patient Name",
				"Patient Gender",
				"Contact Number",
				"Allergies Of Patient",
				"Patient Birthday",
				"Modify All",
				"Exit");
			rewind(stdin);
			switch (selection)
			{
			case 1:
				printf(INPUT_OFFSET"PLease enter patient name : ");
				scanf("%[^\n]", patient[modify].name);
				strupr(patient[modify].name);
				loop = TRUE;
				break;
			case 2:
				patient[modify].gender = get_Gender();
				loop = TRUE;
				break;
			case 3:
				printf(INPUT_OFFSET"PLease enter contact number of patient : ");
				scanf("%[^\n]", patient[modify].contactNum);
				loop = TRUE;
				break;
			case 4:
				printf(INPUT_OFFSET"PLease enter allergies of patient : ");
				scanf("%[^\n]", patient[modify].allergies);
				strupr(patient[modify].allergies);
				loop = TRUE;
				break;
			case 5:
				do {
					get_In_fDate("Birthday", &patient[modify].birthday);
				} while (!isDate(patient[modify].birthday));
				loop = TRUE;
				break;
			case 6:
				// name
				rewind(stdin);
				printf(INPUT_OFFSET"Please Enter The Patient name");
				scanf("%[^\n]", patient[modify].name);
				strupr(patient[modify].name);
				// gender
				patient[modify].gender = get_Gender();
				// contact num
				rewind(stdin);
				printf(INPUT_OFFSET"Please Enter The Contect Number");
				scanf("%[^\n]", patient[modify].contactNum);
				// allergies
				rewind(stdin);
				printf(INPUT_OFFSET"Please Enter The Allergies Type");
				scanf("%[^\n]", patient[modify].allergies);
				strupr(patient[modify].allergies);
				rewind(stdin);
				// birthday
				do {
					get_In_fDate("Birthday", &patient[modify].birthday);
				} while (!isDate(patient[modify].birthday));
				loop = TRUE;
				break;
			case 7:
				loop = FALSE;
				break;
			default:
				break;
			}
			rewind(stdin);
			if (loop)
				system_loading();
		} while (loop);
	}
}

void patient_display_TJC(void)
{
	out_MessageBox("ALL THE PATIENT INFO");
	printf_MaxLine_TJC();
	printf_Header_TJC();
	printf_MaxLine_TJC();
	for (int i = 0; i < index; i++)
	{
		printf_patient_TJC(patient[i], i);
	}
}

void patient_add_TJC(void)
{
	int selection;
	index = fread_patient(patient);
	scanf_patient(&patient[index]);
	while (!isPatient(&patient[index]))
	{
		out_MessageBox("Invalid Input Data Please Re-enter");
		scanf_patient(&patient[index]);
	}
	selection = get_selection_int(2, "Comfirm Add Data", "No");
	if (selection == 1)
	{
		get_patient_ID(&patient[index]);
		out_MessageBox("The Following Data Is Added IN To FILE");
		fwrite_patient(patient);
		index++;
	}
}

void scanf_patient(PatientInfo *data)
{
	// name
	rewind(stdin);
	printf(INPUT_OFFSET"Please Enter The Patient name");
	scanf("%[^\n]", data->name);
	strupr(data->name);
	// gender
	data->gender = get_Gender();
	// contact num
	rewind(stdin);
	printf(INPUT_OFFSET"Please Enter The Contect Number");
	scanf("%[^\n]", data->contactNum);
	// allergies
	rewind(stdin);
	printf(INPUT_OFFSET"Please Enter The Allergies Type");
	scanf("%[^\n]", data->allergies);
	strupr(data->allergies);
	rewind(stdin);
	// birthday
	do 
	{
		get_In_fDate("Birthday", &data->birthday);
	} while (!isDate(data->birthday));
}

void delete_patient_TJC()
{
	int deleteData;
	int selection;
	patient_display_TJC();
	printf(INPUT_OFFSET"Please Enter The Number You Want To Delete --> ");
	scanf("%d", &deleteData);
	while (!isRange(1, index, deleteData))
	{
		printf(INPUT_OFFSET"Invalid Range Please Re-enter Agian In Range (%2d - %2d)\n", 1, index);
		printf(INPUT_OFFSET"Please Enter The Number You Want To Delete --> ");
		scanf("%d", &deleteData);
	}
	deleteData -= 1;
	selection = get_selection_int(2, "Comfirm Delete Data", "EXIT");
	if (selection == 1)
	{
		for (int i = 0; i < index; i++)
		{
			if (i >= deleteData)
			{
				if (deleteData == i)
					index--;

				patient[i] = patient[i + 1];
			}
		}
	}
}
void printf_Header_TJC()
{
	printf("No. Name           Patient ID      Gender     Contact Number  Allergies       Birthday      \n");
}
void printf_MaxLine_TJC()
{
	printf("====================================================================================================\n");
}
void printf_patient_TJC(PatientInfo data, int i)
{
	printf("%2d %-15s %-15s ", i + 1, data.name, data.patientID);
	if (data.gender == FEMALE)
		printf("Female    ");
	else
		printf("Male      ");
	printf(" %-15s %-15s %-10s\n", data.contactNum, data.allergies, data.birthday.sddmmyyyy);
}
/// Other Module are acess this function
void fwrite_patient(PatientInfo *data)
{
	FILE * stream;
	stream = fopen(PATIENT_FILE, "w");
	for (int i = 0; i < index; i++)
		fwrite(&data[i], sizeof(PatientInfo), 1, stream);
	fclose(stream);
}
/// Other Module are acess this function
int fread_patient(PatientInfo *data)
{
	FILE * stream;
	int count = 0;
	stream = fopen(PATIENT_FILE, "r");
	while (fread(&data[count], sizeof(PatientInfo), 1, stream) != 0)
	{
		if (strcmp(data[count].name, NULL_PATIENT.name) != 0)
			count++;
	}
	fclose(stream);
	return count;
}

void get_patient_ID(PatientInfo *patient2)
{
	int x;
	char str[10];
	FILE * fp;
	PatientInfo temp;
	extern DateTime todayDate;
	fp = fopen(PATIENT_FILE, "r");
	if (fp == NULL)
	{
		sprintf(patient2->patientID, "P%d#%03d", todayDate.year, 1);
	}
	else
	{
		while (fread(&temp, sizeof(PatientInfo), 1, fp) != 0)
		{
		}
		sscanf(temp.patientID, "%[^#]#%d", str, &x);
		sprintf(patient2->patientID, "P%d#%03d", todayDate.year, (x + 1));
		fclose(fp);
	}
}

void creat_patient_file()
{
	PatientInfo data[10] = {
	{"P2016#001", "LIM SAI KEAT", 'M', "012-3492834",
	"DRUG ALLERGIES",{ 12,12,1999,"12/12/1999","00:00xx", 0, 0 } },
	{"P2016#002", "ANG ZI LING", 'F', "018-2346543", 
	"SINUSITIS",{ 1,2,1983,"00/00/0000","00:00xx", 0, 0 } },
	{"P2016#003", "YONG JIAN HUA", 'M', "012-4734830",
	"NONE",{ 21,4,1957,"00/00/0000","00:00xx", 0, 0 } },
	{"P2016#004", "MR CHENG BOON", 'M', "017-8345920",
	"SINUSITIS",{ 28,2,1987,"00/00/0000","00:00xx", 0, 0 } },
	{"P2017#005", "CHONG LING", 'F', "016-6417375",
	"NONE",{ 19,3,2001,"00/00/0000","00:00xx", 0, 0 } },
	{"P2017#006", "YEE LING", 'F', "010-2923543",
	"SINUSITIS",{ 7,7,1999,"00/00/0000","00:00xx", 0, 0 } },
	{"P2017#007", "MUHAMAD FARAH", 'F', "013-4312943",
	"ASTHMA",{ 31,8,1984,"00/00/0000","00:00xx", 0, 0 } },
	{"P2017#008", "ITSUKA KOTORI", 'F', "018-3749324",
	"NONE",{ 4,4,1980,"00/00/0000","00:00xx", 0, 0 } },
	{"P2017#009", "LIM TIAN SHI", 'F', "012-3247326",
	"FOOD ALLERGIES",{ 19,3,2001,"00/00/0000","00:00xx", 0, 0 } },
	{"P2018#010", "SOON JONG RE", 'M', "018-4858495",
	"SINUSITIS",{ 28,2,1987,"00/00/0000","00:00xx", 0, 0 } }
	};
	FILE * stream;
	index = 10;
	stream = fopen(PATIENT_FILE, "rb");
	if (stream == NULL)
	{
		stream = fopen(PATIENT_FILE, "wb");
		for (int i = 0; i < index; i++)
		{
			get_str_Date(&data[i].birthday);
			fwrite(&data[i], sizeof(PatientInfo), 1, stream);
		}
	}
	fclose(stream);
}
#pragma warning (pop)
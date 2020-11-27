#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include"date.h"
#include"general.h"
#include"GroupUseFunction.h"

#pragma warning(push , 4)
#pragma warning (disable: 4996 4204)

#ifndef  GROUP_USE_FUNCTION_INLINE
#define VISIT_FILE "bfpatientVisit.dat"
// lee jing wei (Visits) structure
typedef struct Struct_visit{
	DateTime t;
	char patientId[11];
	char staffId[5];
	char diagnosis[51];
	double charge;
}Visits;

static Visits const NULL_VISITS = {
	{0,0,0,"00/00/0000","00:00xx", 0, 0},
	"< ID >", "<ID>", "<diagnosis>", 0.00
};
#endif

#define DISPLAY_FORMAT MAX_BLANK_LONG"|   %02d %02d-%02d-%04d      %10s       %4s        %-20s  %-8.2lf  |\n" 
#define HEADER__FORMAT MAX_BLANK_LONG"|   No. Visits Date     Patient ID      Staff ID    Diagnosis             Charge    |\n" MAX_LINE


// Function Prototype
int visit_selection();
void display_header_LJW();
// Add 
void visit_add();
// Search
void visit_search();
	int search_selection_LJW();
	void search_datetime_LJW();
	void search_patientid_LJW();
	void search_staffid_LJW();
	void search_diagnosis_LJW();
// Modify
void visit_modify();
// Delete
void visit_delete();
// Display
void visit_display();

void patientVisits_Menu()
{
	int choice = 0;
	int countloop = 0;
	do {
		system_logo();
		display_header_LJW();
		choice = visit_selection();
		switch (choice) {
		case 1:
			system_loading();
			visit_add();
			system_loading();
			break;
		case 2:
			system_loading();
			visit_search();
			system_loading();
			break;
		case 3:
			system_loading();
			printf("%-35s===============================\n", "");
			printf("%-35s=       Visits Details        =\n", "");
			printf("%-35s===============================\n", "");
			printf("\n");
			visit_display();
			system_loading();
			break;
		case 4:
			system_loading();
			visit_modify();
			system_loading();
			break;
		case 5:
			system_loading();
			visit_delete();
			system_loading();
			break;
		default:
			if (choice != -999)
				printf("Invalid Choice\n");
		}

		if (countloop >= 100)
		{
			// Intergration add prevent infinity loop
			out_MessageBox("Error of system looping");
			break;
		}
	} while (choice != -999);
}
void display_header_LJW() {
	printf("%-35s===============================\n", "");
	printf("%-35s=        Patient Visit        =\n", "");
	printf("%-35s===============================\n", "");
}
int visit_selection() {
	int selection;
	printf("%-35s===============================\n", "");
	printf("%-35s=                             =\n", "");
	printf("%-35s=       1.Add Record          =\n", "");
	printf("%-35s=       2.Search Record       =\n", "");
	printf("%-35s=       3.Display Record      =\n", "");
	printf("%-35s=       4.Modify Record       =\n", "");
	printf("%-35s=       5.Delete Record       =\n", "");
	printf("%-35s=                             =\n", "");
	printf("%-35s===============================\n", "");
	printf("\n"INPUT_OFFSET"Please Enter Your Choice (Exit = -999)>");
	scanf("%d", &selection);
	return selection;
}
void visit_add() {
	int selection;
	FILE *fp1;
	Visits patientvisit;
	fp1 = fopen(VISIT_FILE, "ab");
	PatientInfo patient;
	StaffInfo staff;
	if (fp1 == NULL) {
		printf("Unable to open file.\n");
		exit(-1);
	}
	do {
		printf(INPUT_OFFSET"Enter Date(dd/mm/yyyy) :");
		scanf("%d/%d/%d", &patientvisit.t.day, &patientvisit.t.month, &patientvisit.t.year);
		while (isDate(patientvisit.t) == FALSE)
		{
			printf(INPUT_OFFSET"Please Enter Agian The Date(dd/mm/yyyy) :");
			scanf("%d/%d/%d", &patientvisit.t.day, &patientvisit.t.month, &patientvisit.t.year);
		}
		get_patient(&patient);
		strcpy(patientvisit.patientId, patient.patientID);
		get_Staff(&staff, ALL_STAFF);
		strcpy(patientvisit.staffId, staff.staffID);
		printf(INPUT_OFFSET"Enter Diagnosis :");
		scanf(" %[^\n]", &patientvisit.diagnosis);
		printf(INPUT_OFFSET"Enter Charges :");
		scanf("%lf", &patientvisit.charge);
		fwrite(&patientvisit, sizeof(Visits), 1, fp1);
		printf("\nPatient Added.\n");
		printf("\n"
			"%34s====================================\n"
			"%34s=     1.Continue Add               =\n"
			"%34s=     2.Return to Patient Visit.   =\n"
			"%34s====================================\n",
			"","","","");
		printf("\n"INPUT_OFFSET"Enter Your Selection : ");
		scanf("%d", &selection);
		
	} while (selection == 1);
	fclose(fp1);
}
void visit_search() {
	int choice, selection;
	do {
		choice = search_selection_LJW();
		switch (choice) {
		case 1:
			search_datetime_LJW();
			break;
		case 2:
			search_patientid_LJW();
			break;
		case 3:
			search_staffid_LJW();
			break;
		case 4:
			search_diagnosis_LJW();
			break;
		default:
			printf("\nInvalid Search Type\n");
		}
		printf("\n"
			"%-32s==============================\n"
			"%-32s= 1.Continue Search          =\n"
			"%-32s= 2.Return to Patient Visit. =\n"
			"%-32s==============================\n", 
			"", "", "", "");
		printf("\n"INPUT_OFFSET"Enter Your Selection : ");
		scanf("%d", &selection);

	} while (selection == 1);
}
void search_datetime_LJW() {
	int count = 0;
	DateTime search;
	FILE *fp1;
	Visits patientvisit;
	fp1 = fopen(VISIT_FILE, "rb");
	if (fp1 == NULL) {
		printf("Unable to open file.\n");
		exit(-1);
	}
	printf(INPUT_OFFSET"Enter date (dd/mm/yyyy) :");
	scanf("%d/%d/%d", &search.day, &search.month, &search.year);
	while (isDate(search) == FALSE)
	{
		printf("Please Enter Again!\n");
		printf(INPUT_OFFSET"Enter date (dd/mm/yyyy) :");
		scanf("%d/%d/%d", &search.day, &search.month, &search.year);
	}
	printf(MAX_LINE HEADER__FORMAT);
	while (fread(&patientvisit, sizeof(Visits), 1, fp1) != 0) {
		if (patientvisit.t.day == search.day&&patientvisit.t.month == search.month&&patientvisit.t.year == search.year) {
			printf(DISPLAY_FORMAT,
				count + 1, patientvisit.t.day, patientvisit.t.month, patientvisit.t.year,
				patientvisit.patientId, patientvisit.staffId, patientvisit.diagnosis,
				patientvisit.charge);
			count++;
		}
	}
	printf(MAX_LINE);
	printf("\n]\t%d patients found.\n", count);
	fclose(fp1);
}
void search_patientid_LJW() {
	int count = 0;
	char tempid[11];
	FILE *fp1;
	Visits patientvisit;
	printf(INPUT_OFFSET"Enter Patient ID :");
	scanf(" %s", &tempid);
	fp1 = fopen(VISIT_FILE, "rb");
	if (fp1 == NULL) {
		printf("Unable to open file.\n");
		exit(-1);
	}
	printf(MAX_LINE);
	printf(HEADER__FORMAT);
	while (fread(&patientvisit, sizeof(Visits), 1, fp1) != 0) {
		if (strcmp(patientvisit.patientId, tempid) == 0) {
			printf(DISPLAY_FORMAT,
				count + 1, patientvisit.t.day, patientvisit.t.month, patientvisit.t.year,
				patientvisit.patientId, patientvisit.staffId, patientvisit.diagnosis,
				patientvisit.charge);
			count++;
		}
	}
	printf(MAX_LINE);
	fclose(fp1);
	printf("\n]\t%d patients found.\n", count);
}
void search_staffid_LJW() {
	int count = 0;
	FILE *fp1;
	Visits patientvisit;
	char tempstaff[5];
	printf(INPUT_OFFSET"Enter Staff ID :");
	scanf(" %s", &tempstaff);
	fp1 = fopen(VISIT_FILE, "rb");
	if (fp1 == NULL) {
		printf("Unable to open file.\n");
		exit(-1);
	}
	printf(MAX_LINE);
	printf(HEADER__FORMAT);
	while (fread(&patientvisit, sizeof(Visits), 1, fp1) != 0) {
		if (strcmp(patientvisit.staffId, tempstaff) == 0) {
			printf(DISPLAY_FORMAT,
				count + 1, patientvisit.t.day, patientvisit.t.month, patientvisit.t.year,
				patientvisit.patientId, patientvisit.staffId, patientvisit.diagnosis,
				patientvisit.charge);
			count++;
		}
	}
	printf(MAX_LINE);
	fclose(fp1);
	printf("\n]\t%d patients found.\n", count);
}
void search_diagnosis_LJW() {
	FILE *fp1;
	Visits patientvisit;
	int count = 0;
	char tempdiagnosis[51];
	printf(INPUT_OFFSET"Enter Diagnosis  :");
	scanf(" %[^\n]", &tempdiagnosis);
	fp1 = fopen(VISIT_FILE, "rb");
	if (fp1 == NULL) {
		printf("Unable to open file.\n");
		exit(-1);
	}
	printf(MAX_LINE);
	printf(HEADER__FORMAT);
	while (fread(&patientvisit, sizeof(Visits), 1, fp1) != 0) {
		if (strcmp(patientvisit.diagnosis, tempdiagnosis) == 0) {
			printf(DISPLAY_FORMAT,
				count + 1, patientvisit.t.day, patientvisit.t.month, patientvisit.t.year, 
				patientvisit.patientId, patientvisit.staffId, patientvisit.diagnosis, 
				patientvisit.charge);
			count++;
		}
	}
	printf(MAX_LINE);
	fclose(fp1);
	printf("\n\t%d patients found.\n", count);
}
int search_selection_LJW() {
	int choice;
	printf("                                           =======================\n");
	printf("                                           =   1.Date            =\n");
	printf("                                           =   2.Patient ID      =\n");
	printf("                                           =   3.Staff ID        =\n");
	printf("                                           =   4.Diagnosis       =\n");
	printf("                                           =======================\n");
	printf("\n"INPUT_OFFSET"Choose Search Type >");
	scanf("%d", &choice);
	return choice;
}
void visit_display() {
	FILE *fp1;
	Visits patientvisit;
	int count = 0;
	fp1 = fopen(VISIT_FILE, "rb");
	printf(MAX_LINE);
	printf(HEADER__FORMAT);
	while (fread(&patientvisit, sizeof(Visits), 1, fp1) != 0) {
		count++;
		printf(DISPLAY_FORMAT
			, count, patientvisit.t.day, patientvisit.t.month, patientvisit.t.year, 
			patientvisit.patientId, patientvisit.staffId, patientvisit.diagnosis, 
			patientvisit.charge);
	}
	printf(MAX_LINE);
	fclose(fp1);
}
void visit_modify() {
	int i = 0, pcount, modicount = 0;
	int modify;
	char confirm, more;
	Visits temp;
	StaffInfo staff;
	FILE *fp1;
	Visits patientmodify[30];

	visit_display();

	fp1 = fopen(VISIT_FILE, "rb");
	if (fp1 == NULL) {
		printf("Unable to open file.\n");
		exit(-1);
	}
	i = 0;
	while (fread(&patientmodify[i], sizeof(Visits), 1, fp1) != 0) {
		i++;
	}
	pcount = i;
	fclose(fp1);
	do {
		printf(INPUT_OFFSET"Enter Number of Patient to be modify :");
		scanf("%d", &modify);
		modify--;
		printf(MAX_LINE HEADER__FORMAT);
		printf(DISPLAY_FORMAT,
			0 + 1, 
			patientmodify[modify].t.day, 
			patientmodify[modify].t.month, 
			patientmodify[modify].t.year,
			patientmodify[modify].patientId, 
			patientmodify[modify].staffId, 
			patientmodify[modify].diagnosis, 
			patientmodify[modify].charge);
			
		printf(MAX_LINE);
		printf("\n"INPUT_OFFSET"Update Visit Date (dd/mm/yyyy): ");
		scanf("%d/%d/%d", &temp.t.day, &temp.t.month, &temp.t.year);
		while (isDate(temp.t) == FALSE)
		{
			printf("Please Enter Again!\n");
			printf(INPUT_OFFSET"Enter date (dd/mm/yyyy) :");
			scanf("%d/%d/%d", &temp.t.day, &temp.t.month, &temp.t.year);
		}
		printf(INPUT_OFFSET"Update Diagnosis : ");
		scanf(" %[^\n]", &temp.diagnosis); 
		get_Staff(&staff, ALL_STAFF);
		strncpy(temp.staffId, staff.staffID, 5);
		printf(INPUT_OFFSET"Update Charge : ");
		scanf("%lf", &temp.charge);
		strncpy(temp.patientId, patientmodify[modify].patientId, 10);
		printf(INPUT_OFFSET"\nConfirm to modify?(Y/y=yes)");
		scanf(" %c", &confirm);
		if (toupper(confirm) == 'Y') {
			patientmodify[modify] = temp;
			modicount++;
			printf("\nUpdated Record\n");
			printf(MAX_LINE HEADER__FORMAT);
			printf(DISPLAY_FORMAT, 
				0 + 1, 
				patientmodify[modify].t.day,
				patientmodify[modify].t.month,
				patientmodify[modify].t.year,
				patientmodify[modify].patientId,
				patientmodify[modify].staffId,
				patientmodify[modify].diagnosis,
				patientmodify[modify].charge);
			printf(MAX_LINE);
		}
		
		printf("\n"INPUT_OFFSET"Any more record to modify (Y=yes)? ");
		rewind(stdin);
		scanf("%c", &more);
	} while (toupper(more) == 'Y');
	fp1 = fopen(VISIT_FILE, "wb");
	for (i = 0; i < pcount; i++) 
	{
		fwrite(&patientmodify[i], sizeof(Visits), 1, fp1);
	}
	fclose(fp1);
	printf("\n\t%d Record(s) modified.\n\n", modicount);
}

void visit_delete() {
	int i = 0, pcount = 0, selection, tdelete;
	char confirm1;
	FILE * fp1;
	Visits pdelete[30];

	visit_display();

	fp1 = fopen(VISIT_FILE, "rb");
	if (fp1 == NULL) {
		printf("Unable to open file.\n");
		exit(-1);
	}
	while (fread(&pdelete[i], sizeof(Visits), 1, fp1) != 0) {
		i++;
	}
	pcount = i;
	fclose(fp1);
	do {
		// Input get number delete
		printf(INPUT_OFFSET"Enter No. to be delete : ");
		scanf("%d", &tdelete);
		tdelete--;
		printf("\n"INPUT_OFFSET"Confirm To Delete? (Y/y=yes)\n");
		scanf(" %c", &confirm1);
		if (toupper(confirm1) == 'Y') 
		{
			fp1 = fopen(VISIT_FILE, "wb");
			if (fp1 == NULL) 
			{
				printf("Unable to open file.\n");
				exit(-1);
			}
			for (i = 0; i < pcount; i++) 
			{
				if (tdelete != i )
				{
					fwrite(&pdelete[i], sizeof(Visits), 1, fp1);
				}
			}
			fclose(fp1);
		}
		printf("\n\tPatient Deleted.\n");
		printf("\n"
			"%35s=============================\n"
			"%35s= 1.Continue Delete         =\n"
			"%35s= 2.Return to Patient Visit.=\n"
			"%35s=============================\n",
			"", "", "", "");
		printf("\n"INPUT_OFFSET"Enter Your Selection : ");
		scanf("%d", &selection);
	} while (selection == 1);
}

#pragma warning(pop)

#pragma once
#include<ctype.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"date.h"
#include"general.h"
#include"GroupUseFunction.h"
#pragma warning(push , 4)
#pragma warning (disable : 4090 4996 4204)
#define DEFAULT_NUM 20
#define BACKUP_STAFF_FILE "staff backup.txt"
#define MAXLINE_EXTENT "====================================================================================================\n"
#define MAX_LINE_EX2M_EXTENT "|==================================================================================================|\n"

// Prevent redefination
#ifndef GROUP_USE_FUNCTION_INLINE

typedef struct Struct_staff {
	char staffID[5];
	char designation[31];// JOB
	char name[31];
	DateTime dateemployed;
	char qualification[31];
	char sarftPassword[31];
	char position[20];
}StaffInfo;

#define STAFF_FILE "fstaff.txt"
#endif

// Decalation 
// Void main
void staffInfo_Menu(); 

// Other 
void add_KY(); 
void del_KY(); 
int  Menu_KY(); 
void show_KY(); 
void search_KY(); 
void modify_KY(); 
void autoBackup_KY();
void manualBackup_KY(); 


void comfirm_have_file();
void backupBackNormal_KY(); 
void printf_heading_StaffInfo();
int  isStaffInfo(StaffInfo staff);                    // check staff and return true or false
void get_staff_Id(StaffInfo *staff);                  // auto generate ID return to a staff
void scanf_StaffInfo(StaffInfo *staff);               // scanf oriented to one staff(struct)
void printf_staff_detail(StaffInfo tempStaff);        // display detail oriented to one staff(struct)
int  fscanf_staff(StaffInfo *staff, FILE * fp);       // fscanf oriented to staff(struct)
void fprintf_staff(StaffInfo staff, FILE * fp);       // fprintf oriented to staff(struct)
void printf_body_StaffInfo(StaffInfo staff, int i);   // display oriented to one staff(struct)


// Staff MODULES(main)
void staffInfo_Menu()
{
	int asking;
	do {
		asking = Menu_KY();
		system_loading();
		switch (asking)
		{
		case 1:
			show_KY();
			autoBackup_KY();
			break;
		case 2:
			add_KY();
			autoBackup_KY();
			break;
		case 3:
			search_KY();
			autoBackup_KY();
			break;
		case 4:
			modify_KY();
			autoBackup_KY();
			break;
		case 5:
			del_KY();
			autoBackup_KY();
			break;
		case 6:
			manualBackup_KY();
			system_logo();
			out_MessageList(2, "Backuping the following data", "Please wait a while !!!");
			_sleep(2000);
			break;
		case 7:
			system_logo();
			out_MessageBox("Exiting StaffInfo, Please wait a while!!");
			break;
		default:
			system_logo();
			out_MessageBox("Error selection");
		}
		if (asking != 7)
			system_loading();
	} while (asking != 7);
}
int Menu_KY() {
	int selection = 0; 
	system_logo();
	printf(MAX_BLANK_SHORT" ============================================\n");
	printf(MAX_BLANK_SHORT" |     Staff Menu :                         |\n");
	printf(MAX_BLANK_SHORT" |     1.Display staff                      |\n");
	printf(MAX_BLANK_SHORT" |     2.Add staff                          |\n");
	printf(MAX_BLANK_SHORT" |     3.Search staff                       |\n");
	printf(MAX_BLANK_SHORT" |     4.Modify staff                       |\n");
	printf(MAX_BLANK_SHORT" |     5.Delete staff                       |\n");
	printf(MAX_BLANK_SHORT" |     6.Backup staff                       |\n");
	printf(MAX_BLANK_SHORT" |     7.Quit                               |\n");
	printf(MAX_BLANK_SHORT" ============================================\n");
	printf(INPUT_OFFSET"Selection : ");
	scanf("%d", &selection); 
	return selection;
}
void show_KY() {

	FILE *read; 
	int i, total;
	StaffInfo staff[DEFAULT_NUM];
	comfirm_have_file();
	read = fopen(STAFF_FILE, "r");
	if (read != NULL) {
		system_logo();
		printf_heading_StaffInfo();
		i = 0;
		while (fscanf_staff(&staff[i], read) != EOF)
		{
			i++;
		}
		total = i;
		fclose(read);
		for (i = 0; i < total; i++)
			printf_body_StaffInfo(staff[i], i);

		printf(MAXLINE_EXTENT);
		printf("%d staff(s) found.\n", total);
	}
	else {
		out_MessageBox("No File found...");
	}
}
void add_KY() {
	StaffInfo temp;
	FILE * add; 
	system_logo();
	scanf_StaffInfo(&temp);
	get_staff_Id(&temp);
	while (!isStaffInfo(temp))
	{
		out_Error_Reenter(InvalidDataType);
		scanf_StaffInfo(&temp);
	}
	add = fopen(STAFF_FILE, "a");
	fprintf_staff(temp, add); 
	fclose(add); 
}

void search_KY() {

	FILE *search; 
	int i, total = 0, none = 0;
	StaffInfo staff[DEFAULT_NUM], searchSource; 
	comfirm_have_file();
	search = fopen(STAFF_FILE, "r");
	if (search != NULL) {
		i = 0;
		while (fscanf_staff(&staff[i], search) != EOF)
		{
			i++;
		}
		total = i;
		system_logo();
		printf(INPUT_OFFSET"Search staff by ID:");
		rewind(stdin);
		scanf("%[^\n]", searchSource.staffID); 
		rewind(stdin);

		for (i = 0; i < total; i++) 
		{ 
			if (strncmp(searchSource.staffID, staff[i].staffID, 5) == 0) 
			{ 
				printf_staff_detail(staff[i]);
				i = total; 
			} 
			else 
				none++; 
		} 
		if (none == total) 
			out_MessageBox("No staff with selected ID found...");
	}
	else {
		out_MessageBox("No file found...");
	}
	fclose(search);

}

void modify_KY() {
	char conti; 
	FILE *modify;
	int i, selection, num2modi, numOfData = 0; 
	StaffInfo staff[DEFAULT_NUM], needModify;
	comfirm_have_file();
	modify = fopen(STAFF_FILE, "r");
	if (modify != NULL) {
		fclose(modify);
		do {
			system("cls");
			system_logo();
			printf_heading_StaffInfo();
			numOfData = 0;
			modify = fopen(STAFF_FILE, "r");
			while (fscanf_staff(&staff[numOfData], modify) != EOF)
			{
				printf_body_StaffInfo(staff[numOfData], numOfData); numOfData++;
			}
			printf(MAXLINE_EXTENT);
			fclose(modify);
			printf(INPUT_OFFSET"Modify which Number : ");
			scanf("%d", &num2modi);
			while (!isRange(1, numOfData, num2modi))
			{
				printf("%30sThe accepted range is only from (1 - %d)%30s\n", "", numOfData, "");
				printf(INPUT_OFFSET"Please re-enter agian number need to modify: ");
				scanf("%d", &num2modi);
			}
			system_loading();
			num2modi = num2modi - 1;
			needModify = staff[num2modi];
			do {
				system_logo();
				selection = get_selection_int(7, "Modify Name", "Modify Date",
					"Modify Qualification", "Modify Position", "Modify All",
					"Modify Password", "Exit");
				switch (selection)
				{
				case 1:
					printf(INPUT_OFFSET"Name : ");
					scanf(" %[^\n]", &staff[num2modi].name);
					while (!isStaffInfo(staff[num2modi]))
					{
						printf(INPUT_OFFSET"Name : ");
						scanf(" %[^\n]", &staff[num2modi].name);
					}

					strupr(staff[num2modi].name);
					if (staff[num2modi].name[0] == '\0')
						strncpy(staff[num2modi].name, NULL_STAFF.name, 7);
					break;
				case 2:
					get_In_fDate("Varrancy", &staff[num2modi].dateemployed);
					while (!isDate(staff[num2modi].dateemployed))
					{
						printf("Invalid Input Data Please reenter \n");
						get_In_fDate("Varrancy", &staff[num2modi].dateemployed);
					}
					break;
				case 3:
					printf(INPUT_OFFSET"Qualification : ");
					scanf(" %[^\n]", &staff[num2modi].qualification);
					while (!isStaffInfo(staff[num2modi]))
					{
						printf(INPUT_OFFSET"Qualification : ");
						scanf(" %[^\n]", &staff[num2modi].qualification);
					}

					strupr(staff[num2modi].qualification);
					if (staff[num2modi].qualification[0] == '\0')
						strncpy(staff[num2modi].qualification, NULL_STAFF.qualification, 16);
					break;
				case 4:
					printf(INPUT_OFFSET"Position : ");
					scanf(" %[^\n]", &staff[num2modi].position);
					while (!isStaffInfo(staff[num2modi]))
					{
						printf(INPUT_OFFSET"Position : ");
						scanf(" %[^\n]", &staff[num2modi].position);
					}

					strupr(staff[num2modi].position);
					if (staff[num2modi].position[0] == '\0')
						strncpy(staff[num2modi].position, NULL_STAFF.position, 11);
					break;
				case 5:
					printf(INPUT_OFFSET"Name : ");
					scanf(" %[^\n]", &staff[num2modi].name);
					while (!isStaffInfo(staff[num2modi]))
					{
						printf(INPUT_OFFSET"Name : ");
						scanf(" %[^\n]", &staff[num2modi].name);
					}
					get_In_fDate("Varrancy", &staff[num2modi].dateemployed);
					while (!isDate(staff[num2modi].dateemployed))
					{
						out_MessageBox("Invalid Input Data Please reenter");
						get_In_fDate("Varrancy", &staff[num2modi].dateemployed);
					}
					printf(INPUT_OFFSET"Qualification : ");
					scanf(" %[^\n]", &staff[num2modi].qualification);
					while (!isStaffInfo(staff[num2modi]))
					{
						printf(INPUT_OFFSET"Qualification : ");
						scanf(" %[^\n]", &staff[num2modi].qualification);
					}
					printf(INPUT_OFFSET"Position : ");
					scanf(" %[^\n]", &staff[num2modi].position);
					while (!isStaffInfo(staff[num2modi]))
					{
						printf(INPUT_OFFSET"Position : ");
						scanf(" %[^\n]", &staff[num2modi].position);
					}

					// Back ground program
					strupr(staff[num2modi].qualification);
					strupr(staff[num2modi].name);
					strupr(staff[num2modi].position);

					if (staff[num2modi].position[0] == '\0')
						strncpy(staff[num2modi].position, NULL_STAFF.position, 11);
					if (staff[num2modi].name[0] == '\0')
						strncpy(staff[num2modi].name, NULL_STAFF.name, 7);
					if (staff[num2modi].qualification[0] == '\0')
						strncpy(staff[num2modi].qualification, NULL_STAFF.qualification, 16);

					break;
				case 6:
					printf(INPUT_OFFSET"Old password : ");
					scanf(" %[^\n]", &needModify.sarftPassword);
					if (staffcmp(needModify, staff[num2modi]) == TRUE)
					{
						do {
							printf(INPUT_OFFSET"New password : ");
							scanf(" %[^\n]", &staff[num2modi].sarftPassword);
						} while (staff[num2modi].sarftPassword[0] == '\0');
					}
					else
					{
						out_MessageBox("Wrong password !!!");
					}
					break;
				}
				system_loading();
			} while (selection != 7);
			conti = 'N';
			system_logo();
			printf(INPUT_OFFSET"Make sure modify(y = yes) ? : ");
			scanf(" %c", &conti);
			system_loading();
			if (tolower(conti) == 'y')
			{
				system_logo();
				out_MessageBox("Modify Sucessful!!");
				modify = fopen(STAFF_FILE, "w");
				for (i = 0; i < numOfData; i++)
				{
					fprintf_staff(staff[i], modify);
				}
				fclose(modify); conti = 'N';
			}
			else
			{
				system_logo();
				out_MessageBox("Modify Unsucessful!!");
			}
			printf(INPUT_OFFSET"Continue Modify Other Staff ? (y = yes): ");
			scanf(" %c", &conti);
		} while (tolower(conti) != 'n');
	}
	else 
	{
		out_MessageBox("No file found...");
	}

}

void del_KY() {
	FILE *del; 
	char delConfirm, conti; 
	StaffInfo staff[DEFAULT_NUM];
	int i, total = 0, deletes = 0;
	comfirm_have_file();
	do {
		del = fopen(STAFF_FILE, "r");
		system_logo();
		printf_heading_StaffInfo();
		total = 0;
		while (fscanf_staff(&staff[total], del) != EOF) 
		{ 
			printf_body_StaffInfo(staff[total], total); 
			total++; 
		}
		printf(MAXLINE_EXTENT);
		fclose(del); 
		rewind(stdin);
		printf(INPUT_OFFSET"Delete which Number : ");
		scanf("%d", &deletes);
		if (isRange(1, total, deletes))
		{
			deletes = deletes - 1;
			rewind(stdin);
			printf(INPUT_OFFSET"Are you sure want to delete ? (y = yes) :");
			rewind(stdin);
			scanf(" %c", &delConfirm);
			system_loading();
			if (tolower(delConfirm) == 'y')
			{
				system_logo();
				out_MessageBox("Deleting The Selected Staff.. !!");
				system_loading();
				del = fopen("fstaff.txt", "w");
				for (i = 0; i < total; i++) {
					if (i != deletes)
					{
						fprintf_staff(staff[i], del);
					}
				}
				fclose(del);
			}
			else
			{
				system_logo();
				out_MessageBox("The staff is not deleted!!");
			}
		}
		else
		{
			out_MessageBox("Invalid input data");
		}
		system("cls");
		system_logo();
		printf(INPUT_OFFSET"Continue To Delete Other Staff? (y = yes):");
		rewind(stdin); 
		scanf(" %c", &conti);
		if(tolower(conti) == 'y')
			system_loading();
	} while (tolower(conti) == 'y');
}

void backupBackNormal_KY() {

	StaffInfo staff[DEFAULT_NUM];
	int i; int total = 0; FILE* f1, *f2; 
	f1 = fopen(BACKUP_STAFF_FILE, "r");
	f2 = fopen(STAFF_FILE, "w");
	i = 0;
	while (fscanf_staff(&staff[i], f2) != EOF)
	{
		i++;
	}
	total = i;
	fclose(f1);
	for (i = 0; i < total; i++) { fprintf_staff(staff[i], f2); } fclose(f2);
}

void manualBackup_KY() {

	StaffInfo staff[DEFAULT_NUM];
	int i; int total = 0; FILE *fp; FILE *backup;
	fp = fopen(STAFF_FILE, "r");
	i = 0;
	while (fscanf_staff(&staff[i], fp) != EOF)
	{
		i++;
	}
	total = i;
	fclose(fp); 
	backup = fopen(BACKUP_STAFF_FILE, "w"); 
	for (i = 0; i < total; i++) {
		fprintf_staff(staff[i], backup);
	} fclose(backup);
}

void autoBackup_KY() {
	int i= 0, total = 0; 
	FILE * fp, * autobackup;
	StaffInfo staff[DEFAULT_NUM];

	fp = fopen(STAFF_FILE, "r");
	i = 0;
	while (fscanf_staff(&staff[i], fp) != EOF)
	{
		i++;
	}
	total = i;
	fclose(fp); 
	autobackup = fopen(BACKUP_STAFF_FILE, "w");
	for (i = 0; i < total; i++) {
		fprintf_staff(staff[i], autobackup);
	} fclose(autobackup);
}

// This Function Other Module Using Use Back This Format
int fscanf_staff(StaffInfo *staffdata, FILE * fp)
{
	/// Dont Change* any more
	int result;// to support EOF checking
	result = fscanf(fp,
		"%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]\n",
		staffdata->dateemployed.sddmmyyyy,
		staffdata->designation,
		staffdata->name,
		staffdata->qualification,
		staffdata->staffID,
	    staffdata->sarftPassword,
		staffdata->position);
	get_Date_read_str(&staffdata->dateemployed);
	return result;
}

// This function Other module using
void fprintf_staff(StaffInfo staffdata, FILE * fp)
{
	/// Dont Change* any more
	fprintf(fp, "%s|%s|%s|%s|%s|%s|%s\n",
		staffdata.dateemployed.sddmmyyyy,
		staffdata.designation,
		staffdata.name,
		staffdata.qualification,
		staffdata.staffID,
		staffdata.sarftPassword,
		staffdata.position);
}
// Other module Might Use
int isStaffInfo(StaffInfo staffdata)
{
	int result = TRUE;
	// Check Data Validation //
	printf("\n\n");
	if (!isDate(staffdata.dateemployed))
	{
		result = FALSE;
		printf("\t\t\t\t\tInvalid Date Employed   : %s\n", staffdata.dateemployed.sddmmyyyy);
	}
	if (!isalspace_str(staffdata.designation))
	{
		result = FALSE;
		printf("\t\t\t\t\tInvalid Designation     : %s\n", staffdata.designation);
	}
	if (!isalspace_str(staffdata.name))
	{
		result = FALSE;
		printf("\t\t\t\t\tInvalid Staff Name      : %s\n", staffdata.name);
	}
	if (!isalspace_str(staffdata.qualification))
	{
		result = FALSE;
		printf("\t\t\t\t\tInvalid Qualitification : %s\n", staffdata.qualification);
	}
	if (!isalnum_str(staffdata.sarftPassword))
	{
		result = FALSE;
		printf("\t\t\t\t\tInvalid Password        : %s\n", staffdata.sarftPassword);
	}
	return result;
}

void scanf_StaffInfo(StaffInfo *staffdata)
{
	int selection;
	// function pormpt and request user key in All staff info
	
	get_In_fDate("Hiring", &staffdata->dateemployed);
	selection = get_selection_int(3, DOCTOR, NURSE, PHAMACY);
	switch (selection)
	{
	case 1:
		strcpy(staffdata->designation, DOCTOR);
		break;
	case 2:
		strcpy(staffdata->designation, NURSE);
		break;
	case 3:
		strcpy(staffdata->designation, PHAMACY);
		break;
	}
	rewind(stdin); printf(INPUT_OFFSET"Name          : ");
	scanf("%[^\n]", &staffdata->name); 
	rewind(stdin); printf(INPUT_OFFSET"Qualification : ");
	scanf("%[^\n]", &staffdata->qualification); 
	rewind(stdin); printf(INPUT_OFFSET"Position      : ");
	scanf("%[^\n]", &staffdata->position); 
	rewind(stdin); printf(INPUT_OFFSET"Password      : ");
	scanf("%[^\n]", &staffdata->sarftPassword); 
	rewind(stdin);

	// Background Program

	if (staffdata->name[0] == '\0')
		strncpy(staffdata->name, NULL_STAFF.name, 7);
	else
		strupr(staffdata->name);

	if (staffdata->position[0] == '\0')
		strncpy(staffdata->position, NULL_STAFF.position, 11);
	else
		strupr(staffdata->position);

	if (staffdata->qualification[0] == '\0')
		strncpy(staffdata->qualification, NULL_STAFF.qualification, 16);
	else
		strupr(staffdata->qualification);

}
void printf_heading_StaffInfo() 
{
	printf(MAXLINE_EXTENT); 
	printf("|                                             Staff Detail                                         |\n");
	printf(MAX_LINE_EX2M_EXTENT);
	printf("|    %-15s %-10s %-20s %-20s %-6s %-16s  |\n", "Employed Date", "Desigation", "Staff Name", "qualification", "ID", "Position");
	printf(MAX_LINE_EX2M_EXTENT);
}
void printf_body_StaffInfo(StaffInfo tempStaff, int i) 
{ 
	printf("|%-3d %-15s %-10s %-20s %-20s %-6s %-18s|\n", 
		i + 1, 
		tempStaff.dateemployed.sddmmyyyy, 
		tempStaff.designation, 
		tempStaff.name,
		tempStaff.qualification,
		tempStaff.staffID,
		tempStaff.position); 
}
// This Other Module Using *Dont Change
int staffcmp(StaffInfo staff1, StaffInfo staff2)
{
	if (!strcmp(staff2.staffID, staff1.staffID) && 
		!strcmp(staff1.sarftPassword, staff2.sarftPassword))
		return TRUE;
	else
		return FALSE;
}
void get_staff_Id(StaffInfo *tempStaff) {
	int id; 
	char id2; 
	FILE *fp; 
	StaffInfo temp;
	fp = fopen(STAFF_FILE, "r");
	if (fp == NULL)
	{
		sprintf(tempStaff->staffID, "%c%03d",
			tempStaff->designation[0], 1);
	}
	else
	{
		while (fscanf_staff(&temp, fp) != EOF)
		{
		}
		fclose(fp);
		sscanf(temp.staffID, "%c%d", &id2, &id);
		sprintf(tempStaff->staffID, "%c%03d",
			tempStaff->designation[0], id + 1);
	}
} 
void printf_staff_detail(StaffInfo tempStaff) {

	printf(MAX_BLANK_SHORT"  ");
	printf("===========================================\n");
	printf(MAX_BLANK_SHORT"  ");
	printf("|Name          : %-25s| \n", tempStaff.name);
	printf(MAX_BLANK_SHORT"  ");
	printf("|ID            : %-25s| \n", tempStaff.staffID);
	printf(MAX_BLANK_SHORT"  ");
	printf("|Varrany       : %-25s| \n", tempStaff.dateemployed.sddmmyyyy);
	printf(MAX_BLANK_SHORT"  ");
	printf("|Designation   : %-25s| \n", tempStaff.designation);
	printf(MAX_BLANK_SHORT"  ");
	printf("|Qualification : %-25s| \n", tempStaff.qualification);
	printf(MAX_BLANK_SHORT"  ");
	printf("|Position      : %-25s| \n", tempStaff.position);
	printf(MAX_BLANK_SHORT"  ");
	printf("===========================================\n");
}

// Main Function Using This Function *Don't Change
StaffInfo staff_Login()
{
	FILE * fp;
	int foundID = 0;
	char userID[51];
	char password[51];
	StaffInfo result = NULL_STAFF;
	fp = fopen(STAFF_FILE, "r");
	if (fp == NULL)
	{
		// frist time use the file have no data
		out_MessageList(3, 
			"Welcome frist time using this system", 
			"Please add a staff information frist",
			"To continue!!!");
		add_KY();

		_sleep(1000);
		fp = fopen_Check_exit(STAFF_FILE, "r");
		fscanf_staff(&result, fp);
		fclose(fp);
		return result;
	}
	else
	{
		// foloowing time use
		get_In_stringf(userID, "Please Enter Your STAFF ID   : ");
		while (fscanf_staff(&result, fp) != EOF)
		{
			if (!strncmp(userID, result.staffID, 5))
			{
				foundID = TRUE;
				get_In_stringf(password, "Please Enter Your Password   : ");
				if (!strcmp(password, result.sarftPassword))
				{
					fclose(fp);
					system_loading();
					return result;
				}
			}
		}
		if (foundID)
		{
			out_MessageBox("Wrong Password!!!");
		}
		else
		{
			out_MessageBox("The ID not found!!!");
		}
	}
	fclose(fp);
	return NULL_STAFF;
}

void comfirm_have_file()
{
	FILE * fp;
	fp = fopen(STAFF_FILE, "r");
	if (fp == NULL)
	{
		out_MessageList(2, "Original File not found !!!", "Prepair using backup file now ...");
		fp = fopen(BACKUP_STAFF_FILE, "r");
		fclose(fp);
		if (fp != NULL) {
			backupBackNormal_KY();
		}
	}
	fclose(fp);
}

void password_Key(const char * password, char* protectedPassword)
{
	int i = 0;
	char *p = password;
	char data[1000] = "", x[31] = "";
	while (*(p+i) != '\0')
	{
		x[0] = ((i * *(p + i)) % 122);
		if (*(p + i) <= 119)
			x[1] = (*(p + i) + 9);
		else
			x[1] = (*(p + i) - 119);
		i++;
		if (!isdigit(x[0]))
			sprintf(data, "%s%c%d", data, x[0], x[1]);
		else
			sprintf(data, "%s%c%d", data, x[0] - 16, x[1]);
	}
	strcpy(protectedPassword, data);
}
#define GET_VALUE(x) x >= 0 && x <= 9? 1: x >= 10 && x <= 99? 2 : x >= 100 && x <= 999? 3 : 0
void password_unlockKey(char * password, const char* protectedPassword)
{
	int i = 0, value, j = 0;
	char *p = protectedPassword, x;
	char data[1000] = "";
	while (*(p + i) != '\0')
	{
		sscanf((p + i), "%c%d", &x, &value);
		i += (1 + GET_VALUE(value));
		if (isRange(0, 8, value))
		{
			data[j] = (char)(value + 119);
			j++;
		}
		else
		{
			data[j] = (char)(value - 9);
			j++;
		}
	}
	strcpy(password, data);
}
#pragma warning (pop)

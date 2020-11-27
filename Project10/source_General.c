
// Do not edit this file function (use only)
// add this file in source/External file
// #include"general.h" in your program
#pragma once 

#pragma warning (push, 4)
#pragma warning (disable :4996)

#include"date.h"
#include<ctype.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdarg.h>
#include<corecrt.h>
#include<Windows.h>

#ifndef GROUP_USE_FUNCTION_INLINE

	#ifndef DEFINED_USING_ENUM
	#define DEFINED_USING_ENUM
	typedef enum Enum_gender{
		MALE = 'M',
		FEMALE = 'F',
		NULL_GENDER = '\0'
	}Gender;
	// error massage use
	enum InvalidType {
		NULL_message,
		InvalidDataType,
		PlsReenter,
		FileNotFound,
		InvalidRange,
		WrongElement,
		FileOpenFailed,
		InvalidData
	};
	#endif // !DEFINED_USING_ENUM

	#ifndef DATE_STRUCT_DEFINED
	#define DATE_STRUCT_DEFINED
	typedef struct Struct_date {
		int  day;
		int  month;
		int  year;
		char sddmmyyyy[11];
		char sTime[11];
		int  minute;
		int  hours;
	}DateTime;
	static DateTime const NULL_DATETIME = {0,0,0,"00/00/0000","00:00xx",0,0};
	#endif

// lim kang yee (StaffInfo)
typedef struct Struct_staff {
	char staffID[5];
	char designation[51];
	char name[51];
	DateTime dateemployed;
	char qualification[51];
	char sarftPassword[51];
}StaffInfo;

#define ISSAME_STR        !
#define TRUE              1
#define FALSE             0
#define BOOL_ONLY         !!
#define MAX_LINE          "        ==========================================="   \
                          "==========================================       \n"
#define MAX_EMPTY_EX2M    "        |                                          "   \
                          "                                         |       \n"
#define MAX_LINE_EX2M     "        |=========================================="   \
                          "=========================================|       \n"
#define MAX_LINE_SHORT    "                           ========================"   \
                          "=======================                          \n"
#define MAX_LINE_S_EX2M   "                           |                       "   \
                          "                      |                          \n"
#define MAX_BLANK_LONG    "        "
#define MAX_BLANK_SHORT   "                           "
#define MAX_LINE_S_E_EX2M MAX_LINE_S_EX2M 
#define STAFF_FILE        "fstaff.txt"
#define DOCTOR            "DOCTOR"                   // Staff designation
#define NURSE             "NURSE"                    // Staff designation
#define PHAMACY           "PHAMACY"                  // Staff designation
#define INPUT_OFFSET      "         "MAX_BLANK_LONG

#endif

extern DateTime todayDate;

/// Boolean Function //
__crt_bool isRange(
	const int range1,
	const int range2,
	const int check
);
__crt_bool isalspace_str(
	const char * string
);
__crt_bool isalnum_str(
	const char * string
);
__crt_bool isalpha_str(
	const char * string
);
__crt_bool isGender(
	const Gender gender
);
__crt_bool isPhoneNumber(
	const char *data
);

/// FILE stream function //
FILE *fopen_Check_exit(
	const char * filename,
	const char * mode
); 
int fscanf_staff(
	StaffInfo * staff,
	FILE      * fp
);

/// Input and Output Function //
int get_In_intf_rtn(
	const char* const format,
	...
);
char get_In_charf_rtn(
	const char *       mode,
	const char * const format,
	...
);
void get_In_stringf(
	      char *       destination,
	const char * const format,
	...
);
void get_In_vstring(
	char       *       destination,
	const char * const format,
	va_list            arglist
);
char get_selection_char(
	const char        maxChar,
	const char* const selectionList,
	...
);
int get_selection_int(
	const int         maxInt,
	const char* const selectionList,
	...
);
// private use 1 = int, 0 = char
int get_mode_selection_v(
	const int         maxChoise,
	const char* const selectionList,
	va_list           argList,
	const int         mode
);
Gender get_Gender(
);

/// Output Function //
void out_private_Error(
	const enum InvalidType mode1,
	const enum InvalidType mode2
);
void out_Error(
	const enum InvalidType mode
);
void out_Error_Reenter(
	const enum InvalidType mode
);
void out_MessageBox(
	const char * const buffer48
);
void out_MessageList(
	const int          numBuffer,
	const char * const bufferList,
	...
);
void out_MessageList_Long(
	const int          numBuffer,
	const char * const bufferList,
	...
);
void out_MessageBody_private(
	const char * const buffer,
	const char * const maxBlank,
	const int          maxBufferCount
);

void system_loading(
);

/************************************************************************
*                                                                       *
*				 OUTPUT STREAM FUNCTION DEFINATION AREA                 *
*                                                                       *
*************************************************************************/
// must start with out_
void out_private_Error(
	const enum InvalidType mode1, 
	const enum InvalidType mode2)
{
	// max lenght 27 str
	const char* title = "  == Error Message ==  ";
	const char * InvalidData[8] = {
		"",                           //0
		"  Invalid Input Data Type  ",//1
		"   Please re-Enter Agian   ",//2
		" FILE Address is not found ",//3
		"    Invalid Data Range     ",//4
		"   Entered Wrong Element   ",//5
		"   FILE open unsucessful   ",//6
		"    Invalid Input Data     ",//7
	}; // !index
	if (mode2 != NULL_message || mode2 != mode1)
		out_MessageList(3, title, InvalidData[mode1], InvalidData[mode2]);
	else
		out_MessageList(2, title, InvalidData[mode1]);
}
void out_Error(const enum InvalidType mode)
{
	out_private_Error(mode, NULL_message);
}
void out_Error_Reenter(const enum InvalidType mode)
{
	out_private_Error(mode, PlsReenter);
}
void out_MessageBody_private(
	const char * const buffer,
	const char * const maxBlank,
	const int          maxBufferCount)
{
	char formatStr[101] = "";
	if (*buffer != '|')
	{
		// Updated Version Not Need Count Yourself
		// Olso not Need Write Module 
		int count = 0;
		while (*(buffer + count) != '\0')
		{
			if (*(buffer + count) == '\n')
			{
				system_loading();
				printf("\nError: \'\\n\' Character is "
					"writen in out_Message format\n\n\n\n");
				system("pause");
				exit(-4);
			}
			count++;
		}
		if (count <= (maxBufferCount - 3))
		{
			if (count % 2 == 0)
				sprintf(formatStr, "%%s|%%-%ds%%s%%-%ds|\n", (((maxBufferCount - 2) - count) / 2), (((maxBufferCount - 2) - count) / 2) - 1);
			else
				sprintf(formatStr, "%%s|%%-%ds%%s%%-%ds|\n", (((maxBufferCount - 1) - count) / 2) - 1, (((maxBufferCount - 1) - count) / 2) - 1);
			printf(formatStr, maxBlank, "", buffer, "");
		}
		else
		{
			sprintf(formatStr, "%%s|%%-%d.%ds...|\n", (maxBufferCount - 7), (maxBufferCount - 7 + 1));
			// updated Version 2 Makesure Box not outline
			printf(formatStr, maxBlank, buffer);
		}
	}
	else if (*(buffer + maxBufferCount - 2) == '|' && *buffer == '|')
	{
		sprintf(formatStr, "%%s%%-%d.%ds\n", (maxBufferCount), (maxBufferCount - 1));
		// Old Version need to count spacing and write module
		printf(formatStr, maxBlank, buffer);
	}
	else
		printf("Error: The Message Box Output Format Incorrect\n");
}
void out_MessageList(
	const int numBuffer,
	const char * const bufferList,
	...)
{
	va_list argList;
	va_start(argList, bufferList);
	printf(MAX_LINE_SHORT MAX_LINE_S_EX2M);
	out_MessageBody_private(bufferList, MAX_BLANK_SHORT, 48);
	for (int i = 0; i < (numBuffer-1); i++)
	{
		out_MessageBody_private(va_arg(argList, char*), MAX_BLANK_SHORT, 48);
	}
	printf(MAX_LINE_S_EX2M MAX_LINE_SHORT);
	va_end(argList);
}

void out_MessageBox(
	const char * const buffer48)
{
	printf(MAX_LINE_SHORT MAX_LINE_S_EX2M);
	out_MessageBody_private(buffer48, MAX_BLANK_SHORT, 48);
	printf(MAX_LINE_S_EX2M MAX_LINE_SHORT);
}

void out_MessageList_Long(
	const int numBuffer,
	const char * const bufferList, 
	...)
{
	va_list argList;
	va_start(argList, bufferList);
	printf(MAX_LINE MAX_EMPTY_EX2M);
	out_MessageBody_private(bufferList, MAX_BLANK_LONG, 86);
	for (int i = 0; i < (numBuffer - 1); i++)
	{
		out_MessageBody_private(va_arg(argList, char*), MAX_BLANK_LONG, 86);
	}
	printf(MAX_EMPTY_EX2M MAX_LINE);
	va_end(argList);
}


/************************************************************************
*                                                                       *
*				 STREAM In/Out FUNCTION DEFINATION AREA                 *
*				    & GET FUNCTION DEFINATION AREA                      *
*                                                                       *
*************************************************************************/

// return a int with printf format
int get_In_intf_rtn(
	const char * const format, 
	...)
{
	va_list arglist;
	char temp[20];
	va_start(arglist, format);
	get_In_vstring(temp, format, arglist);
	va_end(arglist);
	return atoi(temp);
	// use string is better to prevent logic error
}
// return a char with printf format
// mode is toupper , tolower else not change
// toupper = "toupper", tolower = "tolower", else no change
char get_In_charf_rtn(
	const char * mode,
	const char * const format, 
	...)
{
	va_list arglist;
	char temp[30];
	va_start(arglist, format);
	get_In_vstring(temp, format, arglist);
	va_end(arglist);
	if (ISSAME_STR strncmp(mode, "toupper", 7))
		return (char)toupper(temp[0]);
	else if (ISSAME_STR strncmp(mode, "tolower", 7))
		return (char)tolower(temp[0]);
	else
		return temp[0];
	// get string and choose the frist word return as best fit  
	// this way can reduce logic error
}

// return a string from parameter with printf format
void get_In_stringf(
	char * destination,
	const char * const format, 
	...)
{
	va_list arglist;
	va_start(arglist, format);
	get_In_vstring(destination, format, arglist);
	va_end(arglist);
}

// with printf format support va_list
// main function of get user input
void get_In_vstring(
	char * destination,
	const char * const format, 
	va_list arglist)
{
	// vprintf is a function support pass va_list
	// Format for printf
	printf(INPUT_OFFSET);
	vprintf(format, arglist);
	rewind(stdin);
	scanf("%[^\n]", destination);
	rewind(stdin);
}

char get_selection_char(
	const char maxChar,
	const char* const selectionList, 
	...)
{
	char result;
	int maxChoiseR;
	va_list arglist; 
	maxChoiseR = (toupper(maxChar) - 'A' + 1);
	va_start(arglist, selectionList);
	result = (char)get_mode_selection_v(maxChoiseR, selectionList, arglist, 0);
	va_end(arglist);
	return result;
}

int get_selection_int(
	const int maxInt,
	const char* const selectionList,
	...)
{
	int result;
	va_list arglist;
	va_start(arglist, selectionList);
	result = get_mode_selection_v(maxInt, selectionList, arglist, 1);
	va_end(arglist);
	return result;
}

// make it easy to change output format
// private use 1 = int, 0 = char
int get_mode_selection_v(
	 const int maxChoise, 
	 const char* const selectionList,
	 va_list argList, 
	 const int mode)
{
	char data[71];
	int result = 0;
	int initial = 0;
	int maxC = maxChoise;
	__crt_bool exitNor = FALSE;
	__crt_bool returnNor = FALSE;
	const char* const formatStr[2] = {
		MAX_BLANK_LONG"|          %1c. --> %-66.65s|\n",
		MAX_BLANK_LONG"|         %02d. --> %-66.65s|\n"
	};
	const char* const formatStr2[2] = {
			"Please Enter Selection [%c - %c] --> ",
			"Please Enter Selection [%02d - %02d] --> "
	};
	initial = mode == 1 ? 1 : ('A');

	// Display all the selection
	printf(MAX_LINE MAX_EMPTY_EX2M);
	printf(formatStr[mode], initial, selectionList);
	for (int i = 0; i < (maxChoise-1); i++)
	{
		_sleep(50);
		strcpy(data, va_arg(argList, char*));
		if ((
			toupper(*(data + 0)) == 'E' && toupper(*(data + 1)) == 'X' &&
			toupper(*(data + 2)) == 'I' && toupper(*(data + 3)) == 'T') &&
			(maxChoise - 2) == i)
		{
			exitNor = TRUE;
			returnNor = FALSE;
			maxC--;
			break;
		}
		else if ((
			toupper(*(data + 0)) == 'R' && toupper(*(data + 1)) == 'E' &&
			toupper(*(data + 2)) == 'T' && toupper(*(data + 3)) == 'U' &&
			toupper(*(data + 4)) == 'R' && toupper(*(data + 5)) == 'N') &&
			(maxChoise - 2) == i)
		{
			exitNor = FALSE;
			returnNor = TRUE;
			maxC--;
			break;
		}
		else
			printf(formatStr[mode], 1 + i + initial, data);
	} 
	maxC += initial;

	if (exitNor)
		printf(formatStr[mode], maxC, "EXIT");
	else if (returnNor)
		printf(formatStr[mode], maxC, "RETURN");
	else
		maxC--;

	printf(MAX_EMPTY_EX2M MAX_LINE"\n");

	// Get the data from user
	if (mode == 1)
		result = get_In_intf_rtn(formatStr2[mode], initial, maxC);
	else
		result = (int)get_In_charf_rtn("toupper", formatStr2[mode], (char)initial, (char)maxC);

	// Check data validation
	while (!isRange(initial, maxC, result))
	{
		out_Error_Reenter(InvalidRange);
		if (mode == 1)
			result = get_In_intf_rtn(formatStr2[mode], initial, maxC);
		else
			result = (int)get_In_charf_rtn("toupper", formatStr2[mode], (char)initial, (char)maxC);
	}
	_sleep(60);
	return result;
}

Gender get_Gender()
{
	char temp = '\0';
	Gender result = NULL_GENDER;
	out_MessageList(2, " \'F\' --> Female ", " \'M\' --> Male   ");
	temp = get_In_charf_rtn("toupper", "Please Select A Gender --> ");
	switch (temp)
	{
	case 'M':
		result = MALE;
		break;
	case 'F':
		result = FEMALE;
		break;
	}
	while (!isGender(result))
	{
		out_Error_Reenter(InvalidDataType);
		temp = get_In_charf_rtn("toupper", "Please Select A Gender --> ");
		switch (temp)
		{
		case 'M':
			result = MALE;
			break;
		case 'F':
			result = FEMALE;
			break;
		}
	}
	return result;
}

/************************************************************************
*                                                                       *
*				   FILE STREAM FUNCTION DEFINATION AREA                 *
*                                                                       *
*************************************************************************/
FILE *fopen_Check_exit(
	const char * filename, 
	const char *mode)
{
	FILE* stream = NULL;
	char choice = '\0';
	// Support Type "wb" "w" "r + w"
	if (*mode == 'w' || *(mode + 4) == 'w' || *mode == 'a' || *(mode + 4) == 'a')
	{
		// Comform From User Want To Overwrite File
		if (*mode == 'w' || *(mode + 4) == 'w')
		{
			out_MessageList(2, "====      MESSAGE !!    ====", "  Do you sure to overwrite  ");
		}
		else if (*mode == 'a' || *(mode + 4) == 'a')
		{
			out_MessageList(2, "====      MESSAGE !!    ====", "  Do you sure to appendent  ");
		}
		choice = get_selection_char('B', "Yes", "No");
		if (choice != 'A')
			return NULL;
	}
	stream = fopen(filename, mode);
	if (stream == NULL)
	{
		system_loading();
		out_MessageBox(filename);
		out_private_Error(FileOpenFailed, FileNotFound); 
		system("pause");
		exit(-1);
	}
	return stream;
}

/************************************************************************
*                                                                       *
*				    BOOLEAN FUNCTION DEFINATION AREA                    *
*                                                                       *
*************************************************************************/
// in C bool is cant work int 8 bit as best fit 
// start with 'is', return __crt_bool only

// check str is only space character and alphabet eg.(name)
__crt_bool isalspace_str(const char * string)
{
	const char *p = string;
	if (*p == '<')
		return TRUE;
	
	while (*p != '\0')
	{
		if (!(BOOL_ONLY isalpha(*p) || BOOL_ONLY isspace(*p)))
		{
			return FALSE;
		}
		p++;
	}
	return TRUE;
}

// check 'a'-'z'||'A'-'Z'||'1'-'0'
// eg. password character, id, username
__crt_bool isalnum_str(const char * string)
{
	const char *p = string;
	if (*p == '<')
		return TRUE;

	while (*p != '\0')
	{
		if (!isalnum(*p))
			return FALSE;

		p++;
	}
	return TRUE;
}
// check for alpha character ony
__crt_bool isalpha_str(const char * string)
{
	const char *p = string;
	if (*p == '<')
		return TRUE;
	while (*p != '\0')
	{
		if (!isalpha(*p))
			return FALSE;

		p++;
	}
	return TRUE;
}
// check gender is valid or not
__crt_bool isGender(const Gender gender)
{
	return (
		gender == FEMALE ||
		gender == MALE ?
		TRUE : FALSE);
}

__crt_bool isPhoneNumber(const char *data)
{
	long body = 0;
	char head[11] = "";
	if (!(*(data + 2) == '-' || *(data + 3) == '-' || *(data + 4) == '-'))
		return FALSE;
	sscanf(data, "%[^-]-%ld", head, &body);
	if ((ISSAME_STR strncmp(head, "03", 3) ||
		ISSAME_STR strncmp(head, "01", 2) ||
		ISSAME_STR strncmp(head, "601", 3)) &&
		(body >= 100000 && body <= 999999999))
		return TRUE;
	else
		return FALSE;
}

__crt_bool isRange(
	const int range1,
	const int range2, 
	const int check)
{
	if (range1 > range2)
		return (check <= range1 && check >= range2 ? TRUE : FALSE);
	else
		return (check <= range2 && check >= range1 ? TRUE : FALSE);
}

void system_loading()
{
	printf("\n\n");
	_sleep(10);
	printf(MAX_BLANK_LONG"%-20s", "");
	printf("Loading ...");
	_sleep(120);
	printf("...");
	_sleep(80);
	printf("....");
	_sleep(20);
	printf(".....");
	_sleep(10);
	printf(".......");
	_sleep(28);
	printf("..............\n\n\n\n\n");
	if (!cmpDate(&todayDate, &NULL_DATETIME))
		printf("%02d/%02d/%04d%90s\n", todayDate.day, todayDate.month, todayDate.year, "Delta Clinic");
	else
		printf("%100s\n", "Delta Clinic");
	system("pause");
	system("cls");
}


#pragma warning (pop)

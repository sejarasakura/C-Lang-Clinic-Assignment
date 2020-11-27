
#pragma once
// EXIT -1 FILE WAS NULL POINTER TYPE
// EXIT -2 WITHOUT LOGIN EXIT SYSTEM
/************************************************************************
*						GROUP ASSGINMENT PCDII
*
*						      GROUP MEMBER
*					    	1. LIM SAI KEAT
*					    	2. LIM KANG YEE
*					    	3. TAN JUN CHYI
*					    	4. LEE JING WEI
************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<wincontypes.h>
#include"date.h"
#include"general.h"
#include"GroupUseFunction.h"
#pragma warning(push , 4)
// warning c4090 diffrent 'Modifier'
#pragma warning (disable : 4090 4996 4204)

//VARIABLE(GLOBAL) eccess in other c file use extern keyword
StaffInfo dutyStaff;
DateTime  todayDate;

void password_Key(const char * password, char* protectedPassword);
void password_unlockKey(char * password, const char* protectedPassword);
/************************************************************************
*                                                                       *
*						   MAIN PORGRAM AREA                            *
*                                                                       *
*************************************************************************/
void main()
{
	int banded = 0;
	int loginWrong = 0;
	char buffer[51];
	int selection;
	int selection2;
	const char* data[3] = { "753nf9svdj", "Aa73218324%^", "ourgeo49v" };
	char protect[100] = "", password[100] ="";
	for (size_t i = 0; i < 3; i++)
	{
		strcpy(password, data[i]);
		printf("Passwod = %s\n Protected Password = %s\n", password, data[i]);
		password_Key(password, protect);
		printf("Passwod = %s\n Protected Password = %s\n", password, protect);
		password_unlockKey(password, protect);
		printf("Passwod = %s\n Protected Password = %s\n", password, protect);
		password_Key(password, protect);
		printf("Passwod = %s\n Protected Password = %s\n", password, protect);
	}
	system_Welcome_M();
	initialisingTask();
	do{
	// MODULE
		if (staffcmp(dutyStaff, NULL_STAFF))
		{
			loginWrong ++;
			system_logo();
			selection = get_selection_int(2, "Log In", "Exit");
			system("cls");

			if (selection == 1 && loginWrong < 3)
			{
				system_logo();
				out_MessageBox("Please Log In Frist!");
				dutyStaff = staff_Login();
			}
			else if (selection == 1 && isRange(0, 40, loginWrong))
			{
				banded++;
				system(SYSTEM_COLOR COLOUR_CODE_RED COLOUR_CODE_BRIGHY_WHITE);
				system_logo();
				puts("\n\n\n");
				sprintf(buffer, "Please Try Agian In %d Munuite",
					loginWrong * banded);
				out_MessageList(3,
					"You are login wrong more than 3 time",
					"Cause of security problem",
					buffer);
				puts("\n\n");
				_sleep((60 * loginWrong * banded * 1000));
				system("cls");
				system(SYSTEM_COLOR COLOUR_CODE_BRIGHY_WHITE COLOUR_CODE_BLACK);
				system_logo();
				dutyStaff = staff_Login();
			}
			else if (selection == 1 && loginWrong > 40)
			{
				system_loading();
				system_logo();
				out_MessageBox("Exiting The Program With code (-2) !!");
				printf("\n\n\n"MAX_BLANK_SHORT);
				system("pause");
				exit(-2);
			}
		}
		else
		{
			loginWrong = 0;
			system_logo();
			selection = get_selection_int(7, "Staff Info", "Patient Info",
				"Patient Visits", "Appointment", "Log Out", "Change Date", "EXIT");
			menu_Loading();
			switch (selection)
			{
			case 1:
				staffInfo_Menu();
				menu_Loading();
				break;
			case 2:
				patientInfo_Menu();
				menu_Loading();
				break;
			case 3:
				patientVisits_Menu();
				menu_Loading();
				break;
			case 4:
				appointment_Menu();
				menu_Loading();
				break;
			case 5:
				dutyStaff = NULL_STAFF;
				out_MessageBox("Please Log In To View Detail?");
				system_logo();
				dutyStaff = staff_Login();
				menu_Loading();
				break;
			case 6:
				system_logo();
				selection2 = get_selection_int(4,
					"Yesterday", "Tommorrow", "Enter Date", "Return");
				switch (selection2)
				{
				case 1:
					cal_Date(&todayDate, (-1));
					break;
				case 2:
					cal_Date(&todayDate, (1));
					break;
				case 3:
					do {
						get_In_fDate("Current Date", &todayDate);
					} while (!isDate(todayDate));
					break;
				case 4:
					out_MessageBox("The Date Are Remain The Same");
					break;
				}
				sprintf(buffer, "The Date Are Changed to(%10s)", todayDate.sddmmyyyy);
				out_MessageBox(buffer);
				menu_Loading();
				break;
			case 7:
				out_MessageBox("EXITED PROGRAM !!!");
				break;
				// fuction call get selection only allow user enter 1 to n
			}
		}
	} while (isRange(1, 6, selection));

	system_ThankYou_M();
	printf("\n\n\n\n"); 
	system("pause");
}

void system_Welcome_M()
{

	printf("                                         CLINIC MANAGEMENT SYSTEM                                        \n");
	printf("=========================================================================================================\n");
	printf("|                  _     _   _______   ___       _______   _______   __   __   _______                  |\n");
	printf("|                 | | _ | | |       | |   |     |       | |       | |  |_|  | |       |                 |\n");
	printf("|                 | || || | |    ___| |   |     |       | |   _   | |       | |    ___|                 |\n");
	printf("|                 |       | |   |___  |   |     |       | |  | |  | |       | |   |___                  |\n");
	printf("|                 |       | |    ___| |   |___  |      _| |  |_|  | |       | |    ___|                 |\n");
	printf("|                 |   _   | |   |___  |       | |     |_  |       | | ||_|| | |   |___                  |\n");
	printf("|                 |__| |__| |_______| |_______| |_______| |_______| |_|   |_| |_______|                 |\n");
	printf("|                                                                                                       |\n");
	printf("|   ####     <---------------------------------    ooo |+ |   WELCOME                                   |\n");
	printf("|   #######           _|_  E = Mc2  _|_         o   Al | -|   ======================      / /\\ \\        |\n");
	printf("|   #########          |   -------   |         o       |+ |   DELTA CLINIC               / /  \\ \\       |\n");
	printf("|   ###    ###================================o  Na    | -|   Healthcare Facilities     / /    \\ \\      |\n");
	printf("|   ###     ###      ________________________o      O  |+ |   INFNITY R                / /      \\ \\     |\n");
	printf("|   ###     ###     {________________________o}        | -|   Policlinic              / /   __   \\ \\    |\n");
	printf("|   ###     ###                              o  H      |+ |   Open hours 10am-10pm   / /   {__}   \\ \\   |\n");
	printf("|   ###    ###================================o      K | -|   Dr. Lim Kang Yee      / /            \\ \\  |\n");
	printf("|   #########                                  o  Fe   |+ |   ==================== / /______________\\ \\ |\n");
	printf("|   #######       ___CHEMICAL_TECHNOLOGY___      o     | -|                                             |\n");
	printf("|   ####     --------------------------------->    ooo |+ |         WELCOME TO DELTA CLINIC !!!         |\n");
	printf("|                                                                                                       |\n");
	printf("=========================================================================================================\n");
}

void system_logo()
{
	printf("\n              ________         .__   __           _________ .__  .__       .__        \n");
	printf("              \\______ \\   ____ |  |_/  |______    \\_   ___ \\|  | |__| ____ |__| ____  \n");
	printf("               |    |  \\_/ __ \\|  |\\   __\\__  \\   /    \\  \\/|  | |  |/    \\|  |/ ___\\ \n");
	printf("               |    `   \\  ___/|  |_|  |  / __ \\_ \\     \\___|  |_|  |   |  \\  \\  \\___ \n");
	printf("              /_______  /\\___  >____/__| (____  /  \\______  /____/__|___|  /__|\\___  >\n");
	printf("                      \\/     \\/               \\/          \\/             \\/        \\/ \n\n");
}

void initialisingTask()
{
	int loop = 0;
	int banded = 0;
	char buffer[51] = "";
	__crt_bool check = TRUE;
	SMALL_RECT windowSize = {0, 0, 120, 80};
	SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &windowSize);
	SetConsoleActiveScreenBuffer(GetStdHandle(STD_OUTPUT_HANDLE));
	// Global variable initialising
	do{
		system_loading();
		system_logo();
		check = TRUE;
		out_MessageBox("Please Enter Today Date !!");
		puts("\n");
		get_In_Date("Today", &todayDate);
		if (!isDate(todayDate))
		{
			out_Error(InvalidData);
			check = FALSE;
		}
	} while (!check);
	loop = 0;
	do{
		system_loading();
		system_logo();
		check = TRUE;
		loop++;
		out_MessageBox("Please Log In !!");
		puts("\n");
		dutyStaff = staff_Login();
		
		if (loop % 3 == 0 && staffcmp(dutyStaff, NULL_STAFF))
		{
			banded++;
			system_loading();
			system(SYSTEM_COLOR COLOUR_CODE_RED COLOUR_CODE_BRIGHY_WHITE);
			system_logo();
			puts("\n");
			sprintf(buffer, "Please Try Agian In %d Munuite", loop * banded);
			out_MessageList(3,"You are login wrong more than 3 time","Cause of security problem", buffer);
			puts("\n\n");
			_sleep((60 * loop * banded * 1000));
			system("cls");
			check = FALSE;
			system(SYSTEM_COLOR COLOUR_CODE_BRIGHY_WHITE COLOUR_CODE_BLACK);
		}
		else if (staffcmp(dutyStaff, NULL_STAFF))
		{
			out_Error(InvalidData);
			check = FALSE;
		}
		else
		{
			system("cls");
			system_logo();
			out_MessageList(2, "Welcome !!!", dutyStaff.name);
			_sleep(500);
		}

	} while (!check);
	system(SYSTEM_COLOR COLOUR_CODE_BRIGHY_WHITE COLOUR_CODE_BLACK);
	menu_Loading();
}

void menu_Loading()
{
	int y;
	static const char *const logo[7] = 
	{

		"   ___              _      _                        ___      _       _               _            ",
		"  |   \\    ___     | |    | |_    __ _      o O O  / __|    | |     (_)    _ _      (_)     __    ",
		"  | |) |  / -_)    | |    |  _|  / _` |    o      | (__     | |     | |   | ' \\     | |    / _|   ",
		"  |___/   \\___|   _|_|_   _\\__|  \\__,_|   TS__[O]  \\___|   _|_|_   _|_|_  |_||_|   _|_|_   \\__|_  ",
		"_|\"\"\"\"\"|_|\"\"\"\"\"|_|\"\"\"\"\"|_|\"\"\"\"\"|_|\"\"\"\"\"| {======|_|\"\"\"\"\"|_|\"\"\"\"\"|_|\"\"\"\"\"|_|\"\"\"\"\"|_|\"\"\"\"\"|_|\"\"\"\"\"| ",
		"\"`-0-0-\'\"`-0-0-\'\"`-0-0-\'\"`-0-0-\'\"`-0-0-\'./o--000\'\"`-0-0-\'\"`-0-0-\'\"`-0-0-\'\"`-0-0-\'\"`-0-0-\'\"`-0-0-\' ",
		"           Loading . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .            "
	};
	// 98 - 10 = 88
	for (int i = 0; i < 6; i++)
	{
		printf("%s\n", logo[i]);
		_sleep(200);
	}
	printf("%10.10s", logo[6]);
	for (int x = 0; x < 22; x++)
	{
		//y = mx + c
		y = (4 * x) + 10;
		printf("%4.4s", (logo[6] + y));
		_sleep(50 + (x * 2));
	}
	printf("\n\n\n\n");
	system("pause");
	system("cls");
}

void system_ThankYou_M()
{
	out_MessageList_Long(11,
		"                                                                                     ",
		"                   "   ".----."        "  _____ _            _                       ",
		"    .---------.    "   "| == |"        " |_   _| |_ ____ ___| |_                     ",
		"    |.-\"\"\"\"\"-.|    |----|"        "   | | |   |  .\'|   | \'_|                    ",
		"    ||       ||    "   "| == |"        "   |_| |_|_|___,|_|_|_,_|                    ",
		"    ||       ||    "   "|----|"        "                                             ",
		"    |\'-.....-\'|    " "|::::|"        "                             _ _ ___ _ _     ",
		"    `\"\")---(\"\"`    |___.|"         "          Bye Bye           | | | . | | |    ",
		"   /:::::::::::\\   "  "\"    \""      "      SEE YOU AGIAN !!!     |_  |___|___|    ",
		"  /:::=======:::\\        "            "                            |___|            ",
		"  `\"\"\"\"\"\"\"\"\"\"\"\"\"`        ""                                             "
	);
}

#pragma warning (pop)

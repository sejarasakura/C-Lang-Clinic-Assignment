
/************************************************************************
*
*				DEFINE, PRAGMA AND INCLUDING TASK AREA
*
************************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#define GLOBAL_VARIABLE_INLINE

#pragma once

// include needed standard library
#include<ctype.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdarg.h>

#include"date.h"
#include"general.h"
#include"GroupUseFunction.h"

#pragma warning(push , 4)
#pragma warning (disable : 4090 4996 4204)
/************************************************************************
*                                                                       *
*					         DECLALATION AREA                           *
*                                                                       *
*************************************************************************/
 
#define OUT_PUT               "output.txt"
#define SAVE_OPEN             0
#define SAVE_CLOSE            1
#define SAVE_APPENT_ONLY      2
#define SAVE_WRITE            3
#define SAVE_READ             4
#define SAVE_APPENT_DISPLAY   5
#define MAXC_MAIN_NOR         8
#define MAXC_MAIN             13
#define OUT_DISPLAY_ALL_ONLY -1
#define OUT_SEARCH            0
#define OUT_DISPLAY_ALL       1
#define OUT_SEARCH_DATE       6        

#ifndef GROUP_USE_FUNCTION_INLINE

#define APPOINTMENT_FILE "fappointment.txt"
typedef struct Struct_appointment {
	DateTime    applyDate;
	char        sarftDuty[51];
	DateTime    appointmentTime;
	PatientInfo patient;
	char        preferDoctor[51];
	char        email[51];
	char        remark[51];
}Appointment;

static Appointment const NULL_APPOINT = {
	{0,0,0,"00/00/0000","00:00xx", 0, 0}, "<staff>",
	{0,0,0,"00/00/0000","00:00xx", 0, 0},
	{"< ID >", "<name>", NULL_GENDER, "<concact num>",
	"<allergies>",{0,0,0,"00/00/0000","00:00xx", 0, 0}},
	"<doctor>","<email>","<remark>"
};
#endif // !GROUP_USE_FUNCTION_INLINE


/// I/O Function//
int get_appNum();
int get_modify();
int get_search();
int get_appNum();
int get_App_add();
int select_History();
int get_main_selection();
char get_Next(
	const char        * contiWhat
);
void get_Staff(
	      StaffInfo   * staff,
	const char        * designationStaff
);
void get_patient(
	      PatientInfo * desigination
);
void get_backupCode(
	      char        * code
);
void get_In_Appointment(
	      Appointment * data,
	const PatientInfo * info
);
void get_In_new_Appointment(
	      Appointment * data
);
void get_valid_patient_appoinment(
	      PatientInfo * data
);

/// Output function
void out_appointment_Logo();
void out_Appointment_Haeder();
void outOnly_Appointment_Haeder();
void out_histogram_bar(
	const int           frequency,
	const char        * yAxis
);
void physics_check_Error(
	const Appointment * data
);
void out_Appointment_Body(
	const Appointment * data,
	const int           i
);
void out_Appointment_Detail(
	const Appointment * data
);
void out_Appointment_Maxline(
);
void outOnly_Appointment_Body(
	const Appointment * data,
	const int           i
);

/// Boolean Function//    
__crt_bool isApp(
	const Appointment * data
);
__crt_bool isEmail(
	const char        * string
);
__crt_bool isPatient(
	const PatientInfo * data
);

/// file stream function //
int savef(
	const char * const format,
	...
);
int printsavef(
	const char * const format,
	...
);
int vprint_savef(
	const char * const format,
	      va_list      argList
);
int source_save_output(
	const int          mode,
	const char * const format,
	      va_list      argList
);
int backup_fscanf(
	      Appointment * data,
	      FILE        * stream
);
int fscanf_App_LSK(
	      Appointment * data,
	      FILE        * stream
);

size_t foreach_scanBackup(
	const char        * code,
	      Appointment * aryPtr
);

void fscanf_output();
void fclose_output();
void foverwrite_output();
void fscanf_output_source(
	const char        * staStr,
	const char        * endStr,
	const int           staCount,
	const int           endCount
);
void fprintf_App_LSK(
	const Appointment * data,
	      FILE        * stream
);
void foreach_App_Backup(
	const int           count,
	const Appointment * ary,
	      FILE        * stream
);


/// Sub Function//
void admin_Secure_Login();
void initialising_AppFile();
void get_In_selected_Appointment(
	      Appointment * data
);
void appointment_outList(
	const int           mode
);
void dairy_Appointment(
	const DateTime *       date,
	const char     * const fTitle66
);

/// Question Request Funtion //
void app_Add_LSK();
void app_Search_LSK();
void app_Modify_LSK();
void app_Delete_LSK();
void app_History_LSK();
void app_Display_LSK();
void app_Repatient_LSK();
void app_Histogram_LSK();
void app_save_backup_LSK();
void app_Recover_Backup_LSK();
void app_Recover_Delete_LSK();
void app_Today_LSK(const DateTime today);

/// main function 
void appointment_Menu();
void app_MainPage();
/************************************************************************
*                                                                       *
*                      Appointmet MAIN PORGRAM AREA                     *
*                                                                       *
*************************************************************************/

/// GLOBAL VARIEBLE //
extern StaffInfo dutyStaff;
extern DateTime todayDate;

void appointment_Menu()
{
	// Initialising Task
	printf("\n\n");
	savef("App->>>APPOINTMENT START\n");
	savef("App->>>USING DATE :%s\n", todayDate.sddmmyyyy);
	initialising_AppFile(APPOINTMENT_FILE);
	out_appointment_Logo();
	app_Today_LSK(todayDate);
	system_loading();


	// Menu layer
	app_MainPage();

	// Ending Task
	printf("\n\n");
	out_appointment_Logo();
	out_MessageList(2, " EXITED APPOINTMENT !!! ", "Thank you for using!!!");
	savef("App->>>APPOINTMENT END\n");
	fclose_output();    // savef stream is alway opning
}

void app_MainPage()
{
	char next = '\0';
	int selection = 0;
	__crt_bool isdoctor = FALSE;
	const char* const title[MAXC_MAIN] = {
			"ADD APPOINTMENT",
			"MODIFY APPOINTMENT APPLICATION",
			"SEARCH APPOINTMENT APPLICATION",
			"DISPLAY APPOINTMENT LIST",
			"DELETE APPOINTMENT APPLICATION",
			"DAIRY APPOINTMENT APPLICATION",
			"RENEW PATIENT APPOINTMENT APPLICATION",
			"VIEW DIARY APPOINTMENT HISTORGRAM",
			"CHECK ACTIVITY (ADMIN) ",
			"SAVE CURRENT DATA IN FILE AS BACKUP",
			"RECOVER CURRENT FILE",
			"RECOVER DELETED APPOINTMENT"
	};
	// check the staff is doctor or not
	isdoctor = ISSAME_STR strncmp(dutyStaff.designation, DOCTOR, 7);

	do {
		// get selection from user 
		out_appointment_Logo();
		selection = get_main_selection();
		system_loading();


		switch (selection)
		{
		case 1:
			system_logo();
			out_MessageBox(title[(selection - 1)]);
			app_Add_LSK();
			system_loading();
			break;
		case 2:
			system_logo();
			out_MessageBox(title[(selection - 1)]);
			app_Modify_LSK();
			system_loading();
			break;
		case 3:
			system_logo();
			out_MessageBox(title[(selection - 1)]);
			app_Search_LSK();
			system_loading();
			break;
		case 4:
			system_logo();
			out_MessageBox(title[(selection - 1)]);
			app_Display_LSK();
			break;
		case 5:
			system_logo();
			out_MessageBox(title[(selection - 1)]);
			app_Delete_LSK();
			system_loading();
			break;
		case 6:
			system_logo();
			out_MessageBox(title[(selection - 1)]);
			app_Today_LSK(todayDate);
			system_loading();			
			break;
		case 7:
			if (isdoctor)
			{
				admin_Secure_Login();
				system_logo();
				out_MessageBox(title[(selection - 1)]);
				app_Repatient_LSK();
				system_loading();
			}
			else
			{
				system_logo();
				puts("\n");
				out_MessageList(2, "Only doctor can open this page", "You are unable to use this application!");
				system_loading();
			}
			break;
		case 8:
			system_logo();
			out_MessageBox(title[(selection - 1)]);
			app_Histogram_LSK();
			system_loading();
			break;
		case 9:
			if (isdoctor)
			{
				admin_Secure_Login();
				system_logo();
				out_MessageBox(title[(selection - 1)]);
				app_History_LSK();
				system_loading();
			}
			else
			{
				system_logo();
				puts("\n");
				out_MessageList(2, "Only doctor can open this page", "You are unable to use this application");
				system_loading();
			}
			break;
		case 10:
			if (isdoctor)
			{
				system_logo();
				out_MessageBox(title[(selection - 1)]);
				app_save_backup_LSK();
			}
			else
			{
				system_logo();
				puts("\n");
				out_MessageList(2, "Only doctor can open this page", "You are unable to use this application");
				system_loading();
			}
			break;
		case 11:
			if (isdoctor)
			{
				admin_Secure_Login();
				do {
					system_logo();
					out_MessageBox(title[(selection - 1)]);
					app_Recover_Backup_LSK();
					next = get_Next("read backup");
				} while (next == 'Y');
			}
			else
			{
				system_logo();
				puts("\n");
				out_MessageList(2, "Only doctor can open this page", "You are unable to use this application");
			}
			system_loading();
			break;
		case 12:
			if (isdoctor)
			{
				do {
					system_logo();
					out_MessageBox(title[(selection - 1)]);
					app_Recover_Delete_LSK();
					next = get_Next("recover other");
				} while (next == 'Y');
			}
			else
			{
				system_logo();
				puts("\n");
				out_MessageList(2, "Only doctor can open this page", "You are unable to use this application");
			}
			system_loading();
			break;
		}

		// Validation is done at get selection
	} while (isRange(1, MAXC_MAIN - 1, selection));
}

/************************************************************************
*                                                                       *
*				 STREAM OUTPUT FUNCTION DEFINATION AREA                 *
*                                                                       *
*************************************************************************/

void physics_check_Error(
	const Appointment * data)
{
	__crt_bool x[13];
	x[ 0] = isOpenTime(&data->appointmentTime);
	x[ 1] = isDate(data->appointmentTime);
	x[ 2] = isDate(data->applyDate);
	x[ 3] = isEmail(data->email);
	x[ 4] = TRUE; //Duty staff need to login
	x[ 5] = TRUE; //Prefer doctor is provide selection
	x[ 6] = isPatient(&data->patient);
	x[ 7] = isGender(data->patient.gender);
	x[ 8] = isPhoneNumber(data->patient.contactNum);
	x[ 9] = TRUE; //Patient ID auto generate not need check
	x[10] = isalspace_str(data->patient.name);
	x[11] = isalspace_str(data->patient.allergies);
	x[12] = isalspace_str(data->remark);
	const char* buffer[2] = { 
		"(X) ERROR TYPE -> ",
		"(O) VALID TYPE -> " 
	};


	printf(
		MAX_BLANK_SHORT"\tclinic open time : %s%s\n"
		MAX_BLANK_SHORT"\tAppointment Date : %s%s\n"
		MAX_BLANK_SHORT"\tApply Date       : %s%s\n"
		MAX_BLANK_SHORT"\tEmail Address    : %s%s\n"
		MAX_BLANK_SHORT"\tStaff Duty       : %s%s\n"
		MAX_BLANK_SHORT"\tPrefer Doctor    : %s%s\n"
		MAX_BLANK_SHORT"\tremark           : %s%s\n"
		MAX_BLANK_SHORT"\tPatient Info     : %s%s\n", 
		buffer[x[0]], data->appointmentTime.sTime, 
		buffer[x[1]], data->appointmentTime.sddmmyyyy,
		buffer[x[2]], data->applyDate.sddmmyyyy, 
		buffer[x[3]], data->email, 
		buffer[x[4]], data->staffDuty ,
		buffer[x[5]], data->preferDoctor, 
		buffer[x[12]], data->remark ,
		buffer[x[6]], "Detail");


	if (!x[6])
		printf(
			MAX_BLANK_SHORT"\tPatient Gender   : %s%c\n"
			MAX_BLANK_SHORT"\tContect Number   : %s%s\n"
			MAX_BLANK_SHORT"\tPatient ID       : %s%s\n"
			MAX_BLANK_SHORT"\tPatient Name     : %s%s\n"
			MAX_BLANK_SHORT"\tPatient Allegies : %s%s\n",
			buffer[x[7]], data->patient.gender,
			buffer[x[8]], data->patient.contactNum,
			buffer[x[9]], data->patient.patientID,
			buffer[x[10]], data->patient.name,
			buffer[x[11]], data->patient.allergies);
}

void out_Appointment_Maxline()
{
	printsavef(MAX_LINE_EX2M);
}

void outOnly_Appointment_Haeder()
{
	// 85 - 64  = 17
	printf(MAX_BLANK_LONG"| No %-18.19s %-15.16s %-25.26s %-17.18s |\n",
		"Patient Name",
		"Patient ID",
		"Appointment Date&Time",
		"Prefer Doctor"
	);
}

void out_Appointment_Haeder()
{
	// 85 - 64  = 17
	printsavef(MAX_BLANK_LONG"| No %-18.19s %-15.16s %-25.26s %-17.18s |\n",
		"Patient Name",
		"Patient ID",
		"Appointment Date&Time",
		"Prefer Doctor"
	);
}

void out_histogram_bar(
	const int frequency, 
	const char * yAxis)
{
	//13 + 50 
	if (ISSAME_STR strcmp(yAxis, ""))
		printf(MAX_BLANK_LONG"|%10s|", yAxis);
	else
	{
		printf(MAX_BLANK_LONG"|%10s+", yAxis);
		savef("."MAX_BLANK_SHORT"|%16s%6s|%12d%10s|\n",
			yAxis, " ", frequency, " ");
	}
	for (int j = 0; j < 10; j++)
	{
		if (frequency <= j)
			printf("     ");
		else
			printf("*****");
	}
	printf("%22s|\n", "");
}

void out_appointment_Logo()
{
	_sleep(20);
	out_MessageList_Long(10,
		"  _  _  _  _  _  _  _  _  _  _  _  _  _  _  _  _  _  _  _  _  _  _  _  _  _  _  ",
		" [_][_][_][_][_][_][_][_][_][_][_][_][_][_][_][_][_][_][_][_][_][_][_][_][_][_] ",
		" |             *        ||____________________________||                      | ",
		" |        *  .          ||         APPOINTMENT        ||   WELCOME TO USING   | ",
		" |     *    / \\         ||____________________________||     THIS SYSTEM,     | ",
		" |   *     /   \\        ||                            ||                      | ",
		" |  *     /_____\\       ||           MODULES          ||    ( ^ _VV_ ^||| )   | ",
		" | *       DELTA        ||____________________________||_  _  _  _  _  _  _  _| ",
		" [_][_][_][_][_][_][_][_][_][_][_][_][_][_][_][_][_][_][_][_][_][_][_][_][_][_] ",
		"");
	_sleep(20);
}

void out_Appointment_Body(
	const Appointment * data, 
	const int i)
{
	printsavef(MAX_BLANK_LONG"| %02d %-18.19s %-15.16s %-10.11s %-14.15s %-17.18s |\n",
		i + 1, data->patient.name, 
		data->patient.patientID, 
		data->appointmentTime.sddmmyyyy,
		data->appointmentTime.sTime,
		data->preferDoctor
	);
	_sleep(20);
}

void outOnly_Appointment_Body(
	const Appointment * data,
	const int i)
{
	printf(MAX_BLANK_LONG"| %02d %-18.19s %-15.16s %-10.11s %-14.15s %-17.18s |\n",
		i + 1, data->patient.name,
		data->patient.patientID,
		data->appointmentTime.sddmmyyyy,
		data->appointmentTime.sTime,
		data->preferDoctor
	);
	_sleep(20);
}

void out_Appointment_Detail(
	const Appointment * data)
{
	char str[11][65];
	const char* const strMax[4] = 
	{
		" +-=-+-=-+-=-+-=-+-=-+-=-+-=-+-=-+-=-+-=-+-=-+-=-+-=-+-=-+-=-+ ",
		" |                     Appointment Detail                    | ",
		" |                                                           | ",
	};


	// set the format output
	sprintf(str[0], " + Today Date            : %-34.34s+ ", data->applyDate.sddmmyyyy);
	sprintf(str[1], " | Sarft On Duty         : %-34.34s| ", data->staffDuty);
	sprintf(str[2], " + Appointment Date Time : %10s-%-23.23s+ ", data->appointmentTime.sddmmyyyy, data->appointmentTime.sTime);
	sprintf(str[3], " | Prefer Doctor         : %-34.33s| ", data->preferDoctor);
	sprintf(str[4], " + Patient ID            : %-34.34s+ ", data->patient.patientID);
	sprintf(str[5], " | Name                  : %-34.34s| ", data->patient.name);
	sprintf(str[6], " + Gender                : %-34.34s+ ", data->patient.gender == 'M' ? "Male" : "Female");
	sprintf(str[7], " | Contat Number         : %-34.34s| ", data->patient.contactNum);
	sprintf(str[8], " + Allergies             : %-34.34s+ ", data->patient.allergies);
	sprintf(str[9], " | Email Address         : %-34.34s| ", data->email);
	sprintf(str[10]," + Remark                : %-34.34s+ ", data->remark);


	// Display everything
	out_MessageList_Long(18, "", strMax[0], strMax[1], strMax[0], strMax[2], str[0], str[1], str[2], 
		str[3], str[4], str[5], str[6], str[7], str[8], str[9], str[10], strMax[2], strMax[0]);
}

/************************************************************************
*                                                                       *
*				 STREAM In/Out FUNCTION DEFINATION AREA                 *
*				    & GET FUNCTION DEFINATION AREA                      *
*                                                                       *
*************************************************************************/
// output and input

void get_valid_patient_appoinment(PatientInfo *data)
{
	int selection;
	__crt_bool ispatient = FALSE;
	PatientInfo temp = *data;
	do {
		// Patient validation do until accept by system
		out_MessageBox("Select patient to edit :");

		// get the changing catorgery
		selection = get_selection_int(7,
			"Patient Name",
			"Patient Gender",
			"Contact Number",
			"Allergies Of Patient",
			"Patient Birthday",
			"Edit All",
			"Return");
		switch (selection)
		{
		case 1:
			get_In_stringf(temp.name, "Please Enter The Patient name");
			break;
		case 2:
			temp.gender = get_Gender();
			break;
		case 3:
			get_In_stringf(temp.contactNum, "Please Enter The Contect Number");
			break;
		case 4:
			get_In_stringf(temp.allergies, "Please Enter The Allergies Type");
			break;
		case 5:
			get_In_fDate("Birthday", &temp.birthday);
			break;
		case 6:
			// name
			get_In_stringf(temp.name, "Please Enter The Patient name");
			// gender
			temp.gender = get_Gender();
			// contact num
			get_In_stringf(temp.contactNum, "Please Enter The Contect Number");
			// allergies
			get_In_stringf(temp.allergies, "Please Enter The Allergies Type");
			// birthday
			get_In_fDate("Birthday", &temp.birthday);
			break;
		}
		ispatient = isPatient(&temp);
	} while (!ispatient);
	*data = temp;
}

void get_In_new_Appointment(
	Appointment * data)
{
	char selection = '\0';
	FILE * stream = NULL;
	StaffInfo doctor = NULL_STAFF;
	PatientInfo patient = NULL_PATIENT;

	// Add a new patien frist by using add module of patient
	out_MessageBox("Please Add the Patient Frist");
	patient_add_TJC();

	// Get the last data added in file
	stream = fopen(PATIENT_FILE, "r");
	while (fread(&patient, sizeof(PatientInfo), 1, stream) != 0)
	{
		// Want get the last patient in patient file
	}
	fclose(stream);
	system_loading();

	*data = NULL_APPOINT;
	// get appoinment detail of patient (Input program)
	out_MessageBox("|      PLEASE ENTER THE APOINTMENT INFO       |");
	get_In_fDate("Appointment", &data->appointmentTime);
	get_In_stringf(data->appointmentTime.sTime, "Please Enter The Appointment Time  : ");
	selection = get_selection_char('B', "Have any remark ?", "No remark !!");
	if (selection == 'A')
	{
		get_In_stringf(data->remark, "Please Enter The Remark            : ");
		strupr(data->remark);
	}
	else
	{
		printf("         Remark                           : %s\n", data->remark);
	}
	selection = get_selection_char('B', "Add Email?", "No Email !!");
	if (selection == 'A')
		get_In_stringf(data->email, "Please Enter Patiant Email         : ");
	else
		printf("         Patiant Email                   : %s\n", data->email);
	get_Staff(&doctor, DOCTOR);


	// Background Program
	data->applyDate = todayDate;
	strncpy(data->preferDoctor, doctor.name, strlen(doctor.name) + 1);
	strncpy(data->staffDuty, dutyStaff.name, strlen(dutyStaff.name) + 1);
	get_Time_read_str(&data->appointmentTime);
	data->patient = patient;
}

// Use define ALL_STAFF
void get_Staff(
	StaffInfo *staff, 
	const char * designationStaff)
{
	size_t size = 0;
	int count = 0;
	int selection = 0;
	StaffInfo *temp, check;
	FILE * fp;

	// Check the number of data staff have and open a place
	fp = fopen_Check_exit(STAFF_FILE, "r");
	while (fscanf_staff(&check, fp) != EOF)
		size++;
	temp = malloc(sizeof(StaffInfo) * (size + 1));
	rewind(fp);

	// Display the staff need to display
	printf(MAX_LINE_SHORT MAX_LINE_S_EX2M);
	printf(MAX_BLANK_SHORT "| %-3.4s%10s%s|%-19.20s| %-3.4s |\n", "No.", designationStaff, " Name", "Qualitification", "ID");
	printf(MAX_LINE_SHORT);
	if (!strncmp(designationStaff, ALL_STAFF, 6))
	{
		// all
		while (fscanf_staff(&temp[count], fp) != EOF)
		{
			printf(MAX_BLANK_SHORT "| %02d.%-15.15s|%-19.19s|%-4.4s |\n", count + 1, temp[count].name, temp[count].qualification, temp[count].staffID);
			count++;
		}
	}
	else
	{
		// A part of staff
		while (fscanf_staff(&temp[count], fp) != EOF)
		{
			if (!strcmp(temp[count].designation, designationStaff))
			{
				printf(MAX_BLANK_SHORT "| %02d.%-15.15s|%-19.19s|%-4.4s |\n", count + 1, temp[count].name, temp[count].qualification, temp[count].staffID);
				count++;
			}
		}
	}
	printf(MAX_LINE_S_EX2M MAX_LINE_SHORT);


	// Get the staff need to return
	selection = get_In_intf_rtn("Select Your Prefer %s (%d - %d) : ", designationStaff, 1 , count);
	while (!isRange(1, count, selection))
	{
		out_Error_Reenter(InvalidRange);
		selection = get_In_intf_rtn("Select Your Prefer %s (%d - %d) : ", designationStaff, 1, count);
	}

	// return the selected staff
	*staff = *(temp + selection - 1);
	free(temp);
}

void get_In_Appointment(
	Appointment * data,
	const PatientInfo * info)
{
	char selection = '\n';
	StaffInfo doctor = NULL_STAFF;
	out_MessageBox("|      PLEASE ENTER THE APOINTMENT INFO       |");

	// get input from user
	get_In_fDate("Appointment", &data->appointmentTime);
	get_In_stringf(data->appointmentTime.sTime, "Please Enter The Appointment Time  : ");
	selection = get_selection_char('B', "Have any remark ?", "No remark !!");
	if (selection == 'A')
	{
		get_In_stringf(data->remark, "Please Enter The Remark            : ");
		strupr(data->remark);
	}
	else
	{
		printf("         Remark                           : %s\n", data->remark);
	}
	selection = get_selection_char('B', "Add Email?", "No Email !!");
	if (selection == 'A')
		get_In_stringf(data->email, "Please Enter Patiant Email         : ");
	else
		printf("         Patiant Email                   : %s\n", data->email);
	get_Staff(&doctor, DOCTOR);


	//todayDate date duty sarft is set by background
	data->applyDate = todayDate;
	strncpy(data->preferDoctor, doctor.name, strlen(doctor.name) + 1);
	strncpy(data->staffDuty, dutyStaff.name, strlen(dutyStaff.name) + 1);
	get_Time_read_str(&data->appointmentTime);
	data->patient = *info;
}
// do checking
int get_search()
{
	int result = 0;
	printf("\n                         Search By The Following Cetergory                           \n");
	result = get_selection_int(10, // Max = 10
		"Display All",      // 1
		"Patient ID",       // 2
		"Patient Name",     // 3
		"Patient Gender",   // 4
		"Apply Date",       // 5
		"Appointment Date", // 6
		"Prefer Doctor",    // 7
		"Appointment Month",// 8
		"Appointment Year", // 9
		"RETURN");          // 10
	return result;
}
// do checking
int get_modify()
{
	int result = 0;
	printf("\n"MAX_BLANK_LONG"                            Choose The Changing Catogery                             \n");
	result = get_selection_int(10, // Max= 10
		"Appointed Time", // 1
		"Appointed Date", // 2
		"Patient Name",   // 3 
		"Patient Gender", // 4
		"Patient Email",  // 5
		"Contact Number", // 6
		"Allergies Type", // 7
		"Prefer Doctor",  // 8
		"Remark",         // 9
		"RETURN");        // 10
	printf("\n");
	return result;
}
// do checking
int get_main_selection()
{
	int result;
	result = get_selection_int(MAXC_MAIN,             // Max = 12
		"Add Appointment",                            // 1
		"Modify Appointment",                         // 2
		"Search Appointment",                         // 3 
		"Display All Appointment",                    // 4
		"Delete Appointment",                         // 5
		"View Today Appointment",                     // 6
		"Foward Appointment Data From Patient File",  // 7
		"View Appointment Histogram",                 // 8
		"Check Using History",                        // 9
		"Save a backup copy",                         // 10
		"Recover backup copy",                        // 11
		"Recover delete data",                        // 11
		"exit"                                        // 12
	    );
	printf("\n");
	return result;
}
// do checking
int get_App_add()
{
	int result;
	result = get_selection_int(3,// Max = 3
		"New Patient", // 1
		"Came Before", // 2
		"Return");     // 3
	printf("\n");
	return result;
}

int select_History()
{
	return get_selection_int(11,                 // Max = 11
		"Display All Using History",                  // 1
		"Display \'Adding\' Using History",           // 2
		"Display \'Modify\' Using History",           // 3
		"Display \'Search\' Using History",           // 4
		"Display \'Display\' Using History",          // 5
		"Display \'Delete\' Using History",           // 6
		"Display \'View Dairy\' History",             // 7
		"Display \'Update patient\' Using History",   // 8
		"Display \'View Histogram\' History",         // 9
		"Clear History",                              // 10
		"Return");                                    // 11
}

int get_appNum()
{
	FILE * fp;
	int result = 0;
	Appointment temp;
	fp = fopen_Check_exit(APPOINTMENT_FILE, "r");
	while (fscanf_App_LSK(&temp, fp) != EOF)
	{
		result++;
	}
	fclose(fp);
	return result;
}

char get_Next(const char * contiWhat)
{
	char result;
	char buffer[45];
	system("cls");
	system_logo();
	printf("\n"MAX_BLANK_SHORT"Do You Want To Continue %s ?\n\n", contiWhat);
	sprintf(buffer, "\'Y\' --> Yes, Continue %-13s", contiWhat);
	out_MessageList(2, buffer, "\'N\' --> No, Return !!!              ");
	do {
		printf("\n");
		result = get_In_charf_rtn("toupper", "Please Enter Your Selection (Y/N) --> ");
	} while (!(result == 'Y' || result == 'N'));
	return result;
}

void get_backupCode(char * code)
{
	int codeCount = 0;
	char temp[200] = "";
	char temp2[20] = "";
	char tempCode[15] = "";

	FILE * fp = NULL;
	__crt_bool foundCode = FALSE;
	__crt_bool appointmentLine = FALSE;

	// need to close the static file pointer frist before use
	fclose_output();

	// read backup code might can use by user
	fp = fopen_Check_exit(OUT_PUT, "r");
	while (fscanf(fp, "%[^\n]\n", temp) != EOF)
	{
		if (ISSAME_STR strncmp(temp, "App->>>APPOINTMENT START", 24))
			appointmentLine = TRUE;
		else if (ISSAME_STR strncmp(temp, "App->>>APPOINTMENT END", 22))
			appointmentLine = FALSE;
		else if (ISSAME_STR strncmp(temp, "App->>>BACKUP :", 15))
		{
			sscanf(temp, "%[^:]:%s", temp2, tempCode);
			foundCode = TRUE;
		}
		else;
	}
	fclose(fp);

	// if found code than base on previose code generate one
	// otherwise creat the frist code
	if(foundCode)
	{
		sscanf(tempCode, "%[^>]>%d", temp2, &codeCount);
		sprintf(code, "%02d%02d%4.4s>%03d", todayDate.day, todayDate.month, dutyStaff.staffID, codeCount + 1);
	}
	else
	{
		sprintf(code, "%02d%02d%4.4s>%03d", todayDate.day, todayDate.month, dutyStaff.staffID, 1);
	}
}

void get_patient(PatientInfo * desigination)
{
	int count = 0;
	int userinput = 0;
	PatientInfo patient[SIZE_PATIENT] = { NULL_PATIENT };

	// Initial patient file
	count = fread_patient(patient);

	// display patient
	printf(MAX_LINE_SHORT MAX_LINE_S_EX2M);
	printf(MAX_BLANK_SHORT "|    No.  %-15.15s%-15.15s      |\n", "Patient ID", "Patient Name");
	printf(MAX_LINE_S_EX2M MAX_LINE_SHORT MAX_LINE_S_EX2M);
	for (int i = 0; i < count; i++)
	{
		printf(MAX_BLANK_SHORT "|    %02d--> %-15.15s %-15.15s    |\n", i + 1, patient[i].patientID, patient[i].name);
	}
	printf(MAX_LINE_S_EX2M MAX_LINE_SHORT);

	// get user input selected patient
	userinput = get_In_intf_rtn("Select The Patient -->");
	while (!isRange(1, count, userinput))
	{
		out_Error_Reenter(InvalidRange);
		userinput = get_In_intf_rtn("Select The Patient -->");
	}

	// return patient
	*desigination = patient[(userinput - 1)];
}

/************************************************************************
*                                                                       *
*				   FILE STREAM FUNCTION DEFINATION AREA                 *
*                                                                       *
*************************************************************************/
// start with fwrite_ / fread_ / fscanf_ / fprintf_ only
void fprintf_App_LSK(
	const Appointment *data, 
	FILE* stream)
{
	fprintf(stream, "Today Date            : %s\n", data->applyDate.sddmmyyyy);
	fprintf(stream, "Sarft On Duty         : %s\n", data->staffDuty);
	fprintf(stream, "Appointment Date Time : %10s-%s\n", data->appointmentTime.sddmmyyyy, data->appointmentTime.sTime);
	fprintf(stream, "Prefer Doctor         : %s\n", data->preferDoctor);
	fprintf(stream, "Patient ID            : %s\n",	data->patient.patientID);
	fprintf(stream, "Name                  : %s\n",	data->patient.name);
	fprintf(stream, "Gender                : %c\n",	data->patient.gender);
	fprintf(stream, "Contat Number         : %s\n",	data->patient.contactNum);
	fprintf(stream, "Allergies             : %s\n",	data->patient.allergies);
	fprintf(stream, "Emil Address          : %s\n",	data->email);
	fprintf(stream, "Remark                : %s\n",	data->remark);
}

void foreach_App_Backup(
	const int count, 
	const Appointment * ary,
	FILE * stream)
{
	// save all the data as back up
	for (int i = 0; i < count; i++)
	{
		fprintf(stream, "%s|%s|%s|%s\n",
			(ary + i)->applyDate.sddmmyyyy,
			(ary + i)->staffDuty,
			(ary + i)->appointmentTime.sddmmyyyy,
			(ary + i)->appointmentTime.sTime);
		fprintf(stream, "%s|%s|%s|%c\n",
			(ary + i)->preferDoctor,
			(ary + i)->patient.patientID,
			(ary + i)->patient.name,
			(ary + i)->patient.gender);
		fprintf(stream, "%s|%s|%s|%s\n",
			(ary + i)->patient.contactNum,
			(ary + i)->patient.allergies,
			(ary + i)->email,
			(ary + i)->remark);
	}
}

int backup_fscanf(
	Appointment * data,
	FILE * stream)
{
	// scanf all the backup in same format
	char temp[200];
	fscanf(stream, "%[^\n]\n", temp);
	if (ISSAME_STR strncmp("App->>>EOF", temp, 10))
	{
		return EOF;
	}
	else
	{
		sscanf(temp, "%[^|]|%[^|]|%[^|]|%s",
			data->applyDate.sddmmyyyy,
			data->staffDuty,
			data->appointmentTime.sddmmyyyy,
			data->appointmentTime.sTime);
		fscanf(stream, "%[^|]|%[^|]|%[^|]|%c\n",
			data->preferDoctor,
			data->patient.patientID,
			data->patient.name,
			&(char)(data->patient.gender));
		fscanf(stream, "%[^|]|%[^|]|%[^|]|%[^\n]\n",
			data->patient.contactNum,
			data->patient.allergies,
			data->email,
			data->remark);

		// read the string in file --> int
		get_Date_read_str(&data->applyDate);
		get_Date_read_str(&data->appointmentTime);
		get_Time_read_str(&data->appointmentTime);
		return 0;
	}
}

size_t foreach_scanBackup(
	const char * code, 
	Appointment * aryPtr)
{
	char temp[200] = "";
	char temp2[20] = "";
	char tempCode[15] = "";

	FILE * fp = NULL;
	size_t count = 0;
	size_t arySize = 0;
	__crt_bool scanArea = FALSE;
	__crt_bool appointmentLine = FALSE;

	if (aryPtr != NULL)
		arySize = sizeof(aryPtr) / sizeof(Appointment);
	else
		aryPtr = malloc(sizeof(Appointment) * 20);
	fclose_output();
	fp = fopen_Check_exit(OUT_PUT, "r");
	while (fscanf(fp, "%[^\n]\n", temp) != EOF)
	{
		// do string application check the same code
		if (ISSAME_STR strncmp(temp,	"App->>>APPOINTMENT START", 24))
			appointmentLine = TRUE;
		else if (ISSAME_STR strncmp(temp, "App->>>APPOINTMENT END", 22))
			appointmentLine = FALSE;
		else if (ISSAME_STR strncmp(temp, "App->>>BACKUP :", 15))
		{
			sscanf(temp, "%[^:]:%s", temp2, tempCode);
			if (ISSAME_STR strcmp(tempCode, code))
				scanArea = TRUE;
		}
		else;

		// if checked is the match code it will scan all the data in file 
		if (appointmentLine && scanArea)
		{
			count = 0;
			backup_fscanf((aryPtr + count), fp);
			count++;
			while (backup_fscanf((aryPtr + count), fp) != EOF)
			{
				count++;
				if (count + 1 == arySize)
				{
					arySize ++;
					realloc(aryPtr, (sizeof(Appointment) * (arySize)));
				}
			}
			break;
		}
	}
	fclose(fp);
	if (arySize > count)
		return arySize;
	else
		return count;
}

int fscanf_App_LSK(
	Appointment * data,
	FILE        * stream)
{
	int result = 0;
	char temp[64] = "";
	char tempGender;
	result = fscanf(stream, "%[^:]: %[^\n]\n", 	temp, data->applyDate.sddmmyyyy);
	result = fscanf(stream, "%[^:]: %[^\n]\n",	temp, data->staffDuty);
	result = fscanf(stream, "%[^:]: %[^-]-%[^\n]\n", temp, data->appointmentTime.sddmmyyyy, data->appointmentTime.sTime);
	result = fscanf(stream, "%[^:]: %[^\n]\n", 	temp, data->preferDoctor);
	result = fscanf(stream, "%[^:]: %[^\n]\n", 	temp, data->patient.patientID);
	result = fscanf(stream, "%[^:]: %[^\n]\n",	temp, data->patient.name);
	result = fscanf(stream, "%[^:]: %c\n", 	temp, &tempGender);
	result = fscanf(stream, "%[^:]: %[^\n]\n", 	temp, data->patient.contactNum);
	result = fscanf(stream, "%[^:]: %[^\n]\n", temp, data->patient.allergies);
	result = fscanf(stream, "%[^:]: %[^\n]\n", temp, data->email);
	result = fscanf(stream, "%[^:]: %[^\n]\n", temp, data->remark);
	data->patient.gender = tempGender == 'M' ? MALE : FEMALE;
	get_Date_read_str(&data->applyDate);
	get_Date_read_str(&data->appointmentTime);
	get_Time_read_str(&data->appointmentTime);
	return result;
}

void fscanf_output()
{
	fscanf_output_source("App->>>START", "App->>>END", 12, 10);
}

void fscanf_output_source(
	const char* staStr,
	const char* endStr,
	const int staCount,
	const int endCount)
{
	FILE * fp = NULL;
	char temp[200] = "";
	__crt_bool found = FALSE;
	__crt_bool display = FALSE;
	__crt_bool appointmentLine = FALSE;

	// Close file in output.txt in case is open
	fclose_output();
	fp = fopen_Check_exit(OUT_PUT, "r");

	// Start read all the content in file
	// And fine the content can display
	while (fscanf(fp, "%[^\n]\n", temp) != EOF)
	{
		// Logic check can display area
		if (ISSAME_STR strncmp(temp, "App->>>APPOINTMENT START", 24))
		{
			display = FALSE;
			appointmentLine = TRUE;
		}
		else if (ISSAME_STR strncmp(temp, "App->>>APPOINTMENT END", 22))
			appointmentLine = FALSE;
		else if (ISSAME_STR strncmp(temp, staStr, staCount))
			display = TRUE;
		else if (ISSAME_STR strncmp(temp, endStr, endCount))
			display = FALSE;
		else;
		
		// if in display area display all the data
		if (appointmentLine && display)
		{
			if (ISSAME_STR strncmp(temp, "App->>>", 7) && !!strncmp(temp, "App->>>START", 12) && !!strncmp(temp, "App->>>END", 10))
			{
				_sleep(8);
				out_MessageBox((temp + 7));
				found = TRUE;
			}
			else if(!!strncmp(temp, "App->>>", 7))
			{
				printf("%s\n", temp);
				found = TRUE;
			}
			else;

			_sleep(18);
		}
	}
	fclose(fp);

	// in case nothing display info user no data match
	if (!found)
	{
		out_MessageBox("No History found !!");
	}
}

int printsavef(
	const char * const format,
	...)
{
	int result;
	va_list argList;
	va_start(argList, format);
	result = source_save_output(SAVE_APPENT_DISPLAY, format, argList);
	va_end(argList);
	return result;
}

int savef(
	const char * const format,
	...)
{
	int result;
	va_list argList;
	va_start(argList, format);
	result = source_save_output(SAVE_APPENT_ONLY, format, argList);
	va_end(argList);
	return result;
}

int vprint_savef(
	const char * const format,
	va_list           argList)
{
	return source_save_output(SAVE_APPENT_DISPLAY, format, argList);
}

void fclose_output()
{
	source_save_output(SAVE_CLOSE, "", NULL);
}

void foverwrite_output()
{
	source_save_output(SAVE_WRITE, "", NULL);
}

int source_save_output(
	const int mode,
	const char * const format,
	va_list           argList)
{
	int result = 0;
	static FILE* outputStream = NULL;
	switch (mode)
	{
	case SAVE_OPEN:
		outputStream = fopen(OUT_PUT, "a");
		break;
	case SAVE_CLOSE:
		if (outputStream != NULL)
		{
			fclose(outputStream);
			outputStream = NULL;
		}
		result = 0;
		break;
	case SAVE_APPENT_ONLY:
		if (outputStream == NULL)
			outputStream = fopen(OUT_PUT, "a");
		else
			outputStream = freopen(OUT_PUT, "a", outputStream);
		result = vfprintf(outputStream, format, argList);
		break;
	case SAVE_WRITE:
		if (outputStream == NULL)
			outputStream = fopen(OUT_PUT, "w");
		else
			outputStream = freopen(OUT_PUT, "w", outputStream);
		result = vfprintf(outputStream, format, argList);
		break;
	case SAVE_READ:
		if (outputStream == NULL)
			outputStream = fopen(OUT_PUT, "r");
		else
			outputStream = freopen(OUT_PUT, "r", outputStream);
		break;
	case SAVE_APPENT_DISPLAY:
		if (outputStream == NULL)
			outputStream = fopen(OUT_PUT, "a");
		else
			outputStream = freopen(OUT_PUT, "a", outputStream);
		result = vfprintf(outputStream, format, argList);
		result = vfprintf(stdout, format, argList);
		break;
	}
	_sleep(5);
	return result;
}

/************************************************************************
*                                                                       *
*				     BOOLEAN FUNCTION DEFINATION AREA                   *
*                                                                       *
*************************************************************************/
// check email support type
// eg. Example@gmail.com, Example@student.tarc.edu.my
__crt_bool isEmail(
	const char * sString)
{
	int year = 0;
	const char *check = sString;
	char emailEnd[20] = "";
	char joinYear[10] = "";
	char realName[20] = "";
	char emailName[30] = "";
	char emailType[20] = "";
	__crt_bool format[3] = { FALSE,FALSE,FALSE };
	
	if (*sString == '<')
		return TRUE;
	
	while (*check != '\0')
	{
		if (*check == '@')
			format[0] = TRUE;
		else if (*check == '.' && format[0])
			format[1] = TRUE;
		else if (*check == '-')
			format[2] = TRUE;

		check++;
	}

	// Example@gmail.com (gmail)(hotmail)(yahhomail)
	// Example@student.tarc.edu.my
	if (format[0] && format[1])
	{
		sscanf(sString, "%[^@]@%[^.].%s", emailName, emailType, emailEnd);
		if (ISSAME_STR strncmp(emailType, "student", 7) && ISSAME_STR strncmp(emailEnd, "tarc.edu.my", 11) && format[2])
		{
			// (emailName)-XX(year)@stuent.tarc.edu.my
			sscanf(emailName, "%[^-]-%s", realName, joinYear);
			year = atoi((joinYear + 2));
			if (isalpha_str(realName) && isRange(10, 18, year))
				return TRUE;
			else
				return FALSE;
		}
		else if (ISSAME_STR strncmp(emailType, "worker", 6) && ISSAME_STR strncmp(emailEnd, "emp.my", 11) && format[2])
		{
			// (emailName)-XX(year)@stuent.tarc.edu.my
			sscanf(emailName, "%[^-]-%s", realName, joinYear);
			// year is (wm18) (year + 2) is = (18)
			year = atoi((joinYear + 2));
			if (isalpha_str(realName) && isRange(0, 18, year))
				return TRUE;
			else
				return FALSE;
		}
		else if (isalnum_str(emailName) &&
			ISSAME_STR strncmp(emailType, "gmail", 5) ||
			ISSAME_STR strncmp(emailType, "icloud", 6) ||
			ISSAME_STR strncmp(emailType, "outlook", 7) ||
			ISSAME_STR strncmp(emailType, "yahhomail", 9) ||
			ISSAME_STR strncmp(emailType, "hotmail", 7)
		)
		{
			if (ISSAME_STR strncmp(emailEnd, "com", 3))
				return TRUE;
			else
				return FALSE;
		}
	}

	return FALSE;
	
}


__crt_bool checkEmail() {
}

__crt_bool isApp(
	const Appointment *data)
{
	__crt_bool result = TRUE;
	result &= isOpenTime(&data->appointmentTime);
	result &= isDate(data->appointmentTime);
	result &= isDate(data->applyDate);
	result &= isEmail(data->email);
	result &= isalspace_str(data->remark);
	result &= isPatient(&data->patient);
	return result;
}

__crt_bool isPatient(
	const PatientInfo *data)
{
	return(
		isGender(data->gender) &&
		isPhoneNumber(data->contactNum) &&
		isalspace_str(data->allergies) &&
		isalspace_str(data->name) ?
		TRUE : FALSE);
}

/************************************************************************
*                                                                       *
*						 SPECIAL SUB PORGRAM AREA                       *
*                                                                       *
*************************************************************************/
// mix of calculate, stream, I/O, logic Checking, and storing/read data

void initialising_AppFile()
{
	FILE * stream;
	FILE* appStream = fopen(APPOINTMENT_FILE, "r");
	if (appStream == NULL)
	{
		out_MessageBox("| System Are Taking Time To Process Data .... |");
		_sleep(100);

		Appointment appointment[10] = {
		{{11,11,2018,"11/11/2018","00:00xx", 0, 0}
		, "LAI YUH CHAU",
		{1,11,2018,"01/11/2018","11:45am",  45,11},
		{"P2016#001", "LIM SAI KEAT", 'M', "012-3492834",
		"DRUG ALLERGIES",{ 12,12,1999,"12/12/1999","00:00xx", 0, 0 } },
		"J FERNANDO","sejarasakura@gmail.com", "MEDICENT CARE"
		},{
		{12,11,2018,"12/11/2018","00:00xx", 0, 0}, "SITI FATIMAH",
		{5,11,2018,"05/11/2018","12:45pm", 45,12},
		{"P2017#009", "LIM TIAN SHI", 'F', "012-3247326",
		"FOOD ALLERGIES",{ 19,3,2001,"00/00/0000","00:00xx", 0, 0 }},
		"ALAN ALBELT", "bkng19@yahoomail.com", "BLOOD TEST"
		},{
		{9,11,2018,"09/11/2018", "00:00xx", 0, 0}, "LAI YUH CHAU",
		{14,11,2018,"14/11/2018", "01:45pm", 45, 13},
		{"P2017#008", "ITSUKA KOTORI", 'F', "018-3749324",
		"NONE",{ 4,4,1980,"00/00/0000","00:00xx", 0, 0 } },
		"CHIN LIN JACK", "yamakichi@gmail.com", "<remark>"
		},{
		{8,10,2018,"08/10/2018", "00:00xx", 0, 0}, "SHIN HUI",
		{13,11,2018,"13/11/2018", "11:45am", 45, 11},
		{"P2016#001", "LIM SAI KEAT", 'M', "012-3492834", 
		"DRUG ALLERGIES",{ 12,12,1999,"12/12/1999","00:00xx", 0, 0 } },
		"NG WEN JUN", "yukichan@hotmail.com", "X RAY SCAN"
		},{
		{31,10,2018, "31/10/2018","00:00xx", 0, 0},"WONG KAR JUN",
		{11,11,2018, "11/11/2018", "2:45pm", 45, 14}, 
		{"P2018#010", "SOON JONG RE", 'M', "018-4858495",
		"SINUSITIS",{ 28,2,1987,"00/00/0000","00:00xx", 0, 0 } },
		"MAX LEONG", "boonTheChuan@gmail.com", "<remark>"
		},{
		{1,11,2018,"01/11/2018","00:00xx", 0, 0}, "LAW SHIN HUA",
		{11,11,2018,"11/11/2018","08:45pm", 45, 20},
		{"P2017#007", "MUHAMAD FARAH", 'F', "013-4312943",
		"ASTHMA",{ 31,8,1984,"00/00/0000","00:00xx", 0, 0 } },
		"WONG KAR HAO", "foundud2111@gmail.com", "<remark>"
		},{
		{28,10,2018, "28/10/2018","00:00xx", 0, 0}, "CHIN XIAO HUI",
		{13,11,2018, "13/11/2018","04:45pm", 45, 16},
		{"P2017#008", "ITSUKA KOTORI", 'F', "018-3749324",
		"NONE",{ 4,4,1980,"00/00/0000","00:00xx", 0, 0 } },
		"MAX LEONG", "yeongYing@hotmail.com", "BLOOD TEST"
		},{
		{9,11,2018,"09/11/2018","00:00xx", 0, 0}, "WONG KAR JUN",
		{14,11,2018,"14/11/2018","06:45pm", 45, 18},
		{"P2016#003", "YONG JIAN HUA", 'M', "012-4734830",
		"NONE",{ 21,4,1957,"00/00/0000","00:00xx", 0, 0 } },
		"ALAN ALBELT", "foundud2111@gmail.com", "BLOOD TEST"
		},{
		{1,11,2018,"01/11/2018","00:00xx", 0, 0}, "LAW SHIN HUA",
		{13,11,2018,"13/11/2018", "12:45pm", 45, 21},
		{"P2016#002", "ANG ZI LING", 'F', "018-2346543",
		"SINUSITIS",{ 1,2,1983,"00/00/0000","00:00xx", 0, 0 } },
		"J FERNANDON", "limjin@student.tarc.edu.my", "<remark>"
		},{
		{7,10,2018,"07/10/2018","00:00xx", 0, 0}, "LAI YUH CHAU",
		{10,11,2018,"10/11/2018", "5:45pm", 47, 17},
		{"P2016#004", "MR CHENG BOON", 'M', "017-8345920",
		"SINUSITIS",{ 28,2,1987,"00/00/0000","00:00xx", 0, 0 } },
		"ALAN ALBELT", "haixiao@student.tarc.edu.my", "MEDICENT CARE"
		}
		};
		_sleep(100);
		out_MessageBox("|         Appointment File Is Greated         |");
		savef("App->>>The Appointment File Is Greated\n");
		_sleep(100);

		// Great and Write all the data in to file
		stream = fopen(APPOINTMENT_FILE, "w");
		for (int i = 0; i < 10; i++)
		{
			get_str_Date(&appointment[i].patient.birthday);
			fprintf_App_LSK(&appointment[i], stream);
		}
		savef("App->>>The Appointment Data is writen in the file\n");
		fclose(stream);
	}
}

void dairy_Appointment(
	const DateTime * date,
	const char * const fTitle48)
{
	int count = 0;
	int size = 0;
	char buffer[31] = "";

	FILE* stream = NULL;
	Appointment *data = NULL;

	//allocate a space to keep all the data in file
	size = get_appNum();
	data = malloc(sizeof(Appointment) * (size + 1));

	// read data from file
	stream = fopen_Check_exit(APPOINTMENT_FILE, "r");
	while (fscanf_App_LSK((data + count), stream) != EOF)
	{
		if (cmpDate(date, &data[count].appointmentTime))
		{
			count++;
		}
	}
	fclose(stream);

	// Display the data if have
	if (count > 0)
	{
		savef("App->>>START DAIRY\n");
		savef("App->>>%s view APPOINTMENT DATE %s\n", dutyStaff.staffID, date->sddmmyyyy);
		out_MessageBox(fTitle48);
		printsavef(MAX_LINE MAX_EMPTY_EX2M);
		out_Appointment_Haeder();
		out_Appointment_Maxline();
		for (int i = 0; i < count; i++)
		{
			out_Appointment_Body((data + i), i);
		}
		printsavef(MAX_EMPTY_EX2M MAX_LINE);
		sprintf(buffer, "%d record is found!!", count);
		out_MessageBox(buffer);
		savef("App->>>END DAIRY\n");
	}
	else
	{
		// In case did not found !!!
		out_MessageList(2, "No record is found in !!", date->sddmmyyyy);
	}

	free(data);
}

void admin_Secure_Login()
{
	StaffInfo staff = NULL_STAFF;
	__crt_bool isDutyDoctor = FALSE;

	//Frist time login
	system_logo();
	puts("\n\n");
	staff = staff_Login();
	for (int i = 0; i < 3; i++)
	{
		isDutyDoctor = 
			(ISSAME_STR strncmp(dutyStaff.designation, DOCTOR, 7) && 
			 ISSAME_STR strncmp(dutyStaff.staffID, staff.staffID, 5));
		if (i == 2 && !isDutyDoctor)
		{
			// After login 3 time
			system_loading();
			system(SYSTEM_COLOR COLOUR_CODE_RED
				COLOUR_CODE_BRIGHY_WHITE);
			system_logo();
			puts("\n\n");
			out_MessageList(4,
				"You are login wrong more than 3 time",
				"Cause of security problem",
				"You Are Be Banded",
				"You are not allow login agian");
			system_loading();
			exit(-3);
		}
		else if (!isDutyDoctor)
		{
			// After login 1 time
			system_loading();
			system_logo();
			puts("\n\n");
			out_MessageList(4,
				"Please Take Note!",
				"Login Is Only Able For Duty Doctor",
				staff.staffID,
				"You are not able to login");
			staff = staff_Login();
		}
		else
		{
			break;
		}
	}
}

void get_In_selected_Appointment(
	Appointment * data)
{
	// Modify sub function
	int selection = 0;
	StaffInfo doctor = NULL_STAFF;
	__crt_bool looped = FALSE;
	__crt_bool isAppointment = FALSE;
	do {
		isAppointment = isApp(data);
		if (!isAppointment && looped)
		{
			system_loading();
			system_logo();
			out_Error_Reenter(InvalidData);
			physics_check_Error(data);
			system_loading();
		}
		system("cls");
		system_logo();
		selection = get_modify();
		system_loading();
		if (isRange(1, 9, selection))
		{
			system_logo();
			out_Appointment_Detail(data);
		}
		switch (selection)
		{
		case 1:
			get_In_stringf(data->appointmentTime.sTime,"Please Enter The Appointment Time  :");
			get_Time_read_str(&data->appointmentTime);
			break;
		case 2:
			get_In_Date("Appointment", &data->appointmentTime);
			get_Date_read_str(&data->appointmentTime);
			break;
		case 3:
			get_In_stringf(data->patient.name,"Please Enter Patiant Name          :");
			strupr(data->patient.name);
			break;
		case 4:
			data->patient.gender = get_Gender();
			break;
		case 5:
			get_In_stringf(data->email,"Please Enter Patiant Email         :");
			break;
		case 6:
			get_In_stringf(data->patient.contactNum,"Please Enter Patiant Concact Number:");
			break;
		case 7:
			get_In_stringf(data->patient.allergies,"Please Enter Patiant Allergies Type:");
			strupr(data->patient.allergies);
			break;
		case 8:
			get_Staff(&doctor, DOCTOR);
			strcpy(data->preferDoctor, doctor.name);
			break;
		case 9:
			get_In_stringf(data->remark,"Please Enter the Remark            :");
			strupr(data->remark);
			break;
		}
		looped = TRUE;
	} while (selection != 10 || !isAppointment);
}

// Only read data from file and display
void appointment_outList(
	const int mode)
{
	int count = 0;
	int arySize = 0;
	int realMode = 0;
	int veiwDetail = 0;
	char userinput[51] = "";
	char foundinfo[51] = "";

	FILE * fp = NULL;
	__crt_bool found = FALSE;
	Appointment *data = NULL;
	Gender userinput3 = NULL_GENDER;
	StaffInfo userinput4 = NULL_STAFF;
	DateTime userinput2 = NULL_DATETIME;

	const char * const request[] = {
		"Enter The Patient ID to search-->",
		"Enter The Patient Name to search-->",
		"Enter The Patient Gender to search-->",
		"Enter The Apply Date to search (dd/mm/yyyy)-->",
		"Enter The Appointment Time (dd/mm/yyyy-XX:XXpm/am)-->",
		"Enter The Prefer Doctor to seacrch-->",
		"Enter The Appointment Month to search-->",
		"Enter The Appointment Year to seacrch-->"
	};
	const char * const saveType[] = {
		"PATIENT ID",
		"PATIENT NAME",
		"PATIENT GENDER",
		"APPLY DATE",
		"APPOINTMENT TIME",
		"PREFER DOCTOR",
		"APPOINTMENT MONTH",
		"APPOINTMENT YEAR"
	};

	// allocate the needed space base on file 
	arySize = get_appNum();
	data = malloc(sizeof(Appointment) * (arySize + 1));


	// get the real mode to display
	if (mode == OUT_DISPLAY_ALL_ONLY)
		realMode = OUT_DISPLAY_ALL;
	else
		realMode = mode;

	// if real mode not display case
	savef("App->>>Staff Hander : %s\n", dutyStaff.staffID);
	if ((realMode != OUT_DISPLAY_ALL))
	{
		system_logo();
		if (realMode == 4)
		{
			userinput3 = get_Gender();
		}
		else if (realMode == 7)
		{
			get_Staff(&userinput4, DOCTOR);
		}
		else
		{
			printf("\n\n\n");
			get_In_stringf(userinput, request[(realMode - 2)]);
		}
		printf("\n");
		savef("App->>>%s:SEARCH:%s:%s\n", dutyStaff.staffID, saveType[(realMode - 2)], userinput);
	}

	// storing data and counting data in the file
	fp = fopen_Check_exit(APPOINTMENT_FILE, "r");
	count = 0;
	while (fscanf_App_LSK((data + count), fp) != EOF)
	{
		switch (realMode)
		{
		case 1:
			found = TRUE;
			count++;
			break;
		case 2:
			if (ISSAME_STR strcmp(data[count].patient.patientID, userinput))
			{
				found = TRUE;
				count++;
			}
			break;
		case 3:
			if (ISSAME_STR strcmp(data[count].patient.name, userinput))
			{
				found = TRUE;
				count++;
			}
			break;
		case 4:
			if((userinput3 == (data[count].patient.gender)))
			{
				found = TRUE;
				count++;
			}
		case 5:
			userinput2 = new_sDateTime(userinput);
			if (cmpDate(&data[count].applyDate, &userinput2))
			{
				found = TRUE;
				count++;
			}
			break;
		case 6:
			userinput2 = new_sDateTime(userinput);
			if (userinput2.hours == 0)
			{
				if (cmpDate(&data[count].appointmentTime, &userinput2))
				{
					found = TRUE;
					count++;
				}
			}
			else
			{
				if (cmpDate(&data[count].appointmentTime, &userinput2) && cmpTime(&data[count].appointmentTime, &userinput2))
				{
					found = TRUE;
					count++;
				}
			}
			break;
		case 7:
			if (ISSAME_STR strcmp(data[count].preferDoctor, userinput4.name))
			{
				found = TRUE;
				count++;
			}
			break;
		case 8:
			if (atoi(userinput) == data[count].appointmentTime.month)
			{
				found = TRUE;
				count++;
			}
			break;
		case 9:
			if (atoi(userinput) == data[count].appointmentTime.year)
			{
				found = TRUE;
				count++;
			}
			break;
		}
	}
	fclose(fp);

	// Display the data in a list from 
	if (found)
	{
		// Display number of record and record found
		sprintf(foundinfo, "%d record is found", count);
		out_MessageBox(foundinfo);
		printsavef(MAX_LINE MAX_EMPTY_EX2M);
		out_Appointment_Haeder();
		out_Appointment_Maxline();
		for (int i = 0; i < count; i++)
		{
			if (isRange(1, 9, realMode))
				out_Appointment_Body((data + i), i);
		}
		printsavef(MAX_EMPTY_EX2M MAX_LINE);
		printf("\n");

		// allow user to view detail if mode != -1
		if (mode != OUT_DISPLAY_ALL_ONLY)
		{
			do {
				veiwDetail = get_In_intf_rtn("Enter The No. to view detail (-1 to exit): ");
				if (isRange(1, count, veiwDetail))
				{
					savef("App->>>%s VIEW DETAIL APPOINTMENT NO. %d\n", dutyStaff.staffID, veiwDetail);
					out_Appointment_Detail(&data[(veiwDetail - 1)]);
				}
				else if (veiwDetail != -1)
					out_Error_Reenter(InvalidRange);
			} while (veiwDetail != -1);
			printf("\n");
		}
	}
	else
	{
		// in case not found
		system("cls");
		system_logo();
		puts("\n");
		out_MessageList(3,"Base on the category you search","System had not found any record","please search with other category");
	}
	free(data);
}


/************************************************************************
*                                                                       *
*                        SPECIAL SUB PORGRAM AREA                       *
*                        QUSETIN REQUEST FUNCTION                       *
*                                                                       *
*************************************************************************/
// compund of calculate, stream, I/O, logic Checking, and storing/read data

void app_Add_LSK()
{
	int change = 0;
	int selection = 0;
	char confirm = '\0';
	FILE *appointfp = NULL;
	__crt_bool isAppointment = FALSE;
	PatientInfo patient = NULL_PATIENT;
	Appointment appointment = NULL_APPOINT;

	// get the selection
	selection = get_App_add();
	if (selection != 3)
		system_loading();


	switch (selection)
	{
	case 1:
		// Get input appointment (New)
		get_In_new_Appointment(&appointment);
		out_Appointment_Detail(&appointment);
		isAppointment = isApp(&appointment);
		for (int i = 0; i < 10; i++)
		{
			// display valid or not valid 
			system_loading();
			system_logo();
			physics_check_Error(&appointment);
			if (!isAppointment)
			{
				// Incase invalid input data
				out_Error_Reenter(InvalidData);
				get_In_Appointment(&appointment, &patient);
				isAppointment = isApp(&appointment);
			}
			else
			{
				// valid than not need loop
				break;
			}
		}
		// Save the using activity
		savef("App->>>START ADD\n");
		savef("App->>>%s ADD NEW APPOINTMENT\n", dutyStaff.staffID);
		break;
	case 2:
		// get input appointment(came before)
		get_patient(&patient);
		get_In_Appointment(&appointment, &patient);
		isAppointment = isApp(&appointment);
		for (int i = 0; i < 10; i++)
		{
			// display valid or not valid 
			system_loading();
			system_logo();
			physics_check_Error(&appointment);
			if (!isAppointment)
			{
				// Incase invalid input data
				out_Error_Reenter(InvalidData);
				change = get_In_intf_rtn("Change patient or not?? (Yes = 1): ");
				if (change == 1)
					get_patient(&patient);
				get_In_Appointment(&appointment, &patient);
				isAppointment = isApp(&appointment);
			}
			else
			{
				// valid than not need loop
				break;
			}
		}

		// Save the using activity
		savef("App->>>START ADD\n");
		savef("App->>>%s ADD %s APPOINTMENT\n", dutyStaff.staffID, patient.patientID);
		break;
	}


	if (selection != 3)
	{
		// check back with user to add data to file
		system_loading();
		out_MessageBox("Confirm The Following Data");
		out_Appointment_Detail(&appointment);
		confirm = get_In_charf_rtn("toupper",
			"Confirm Add New Data To File(Y = yes) --> ");
		system_loading();
		system_logo();
		if (confirm == 'Y')
		{
			// start add new data in file
			appointfp = fopen_Check_exit(APPOINTMENT_FILE, "a");
			fprintf_App_LSK(&appointment, appointfp);
			out_MessageBox("New Appointment Is Added In FILE");
			fclose(appointfp);
		}
		else
		{
			// Did not save the data
			out_MessageBox("Appointment Is Not Add In To FILE");
		}
		savef("App->>>END ADD\n");
	}
}

void app_Search_LSK()
{
	// Initialise task
	char next = '\0';
	int userchoise = 0;
	savef("App->>>START SEARCH\n");

	do {
		// Friendly user setting
		_sleep(10);
		system("cls");

		// Get number of search
		system_logo();
		userchoise = get_search();
		system_loading();

		// Display data in file
		appointment_outList(userchoise);

		// Ask about next or not 
		system_loading();
		next = get_Next("Search");
	} while (next == 'Y');

	//Ending Task
	savef("App->>>END SEARCH\n");
}

void app_Display_LSK()
{
	// Display every thing 
	savef("App->>>START DISPLAY\n");
	appointment_outList(OUT_DISPLAY_ALL);
	savef("App->>>END DISPLAY\n");
	system_loading();
}

void app_Delete_LSK()
{
	int size = 0;
	int count = 0;
	char next = '\0';
	int userchoice = 0;
	char overwriteP = 0;
	FILE * fp = NULL;
	FILE * fp2 = NULL;
	Appointment *data = NULL;
	__crt_bool deleted = FALSE;

	// Allocate The enough memory space to store all the data 
	size = get_appNum();
	data = malloc(sizeof(Appointment) * (size + 1));

	do {
		// read data from file
		fp = fopen_Check_exit(APPOINTMENT_FILE, "r");
		count = 0;
		while (fscanf_App_LSK((data + count), fp) != EOF)
			count++;
		fclose(fp);

		// DISPLAY ALL DATA IN FILE
		savef("App->>>START DELETE\n");
		appointment_outList(OUT_DISPLAY_ALL_ONLY);
		savef("App->>>END DELETE\n");

		// get number of delete
		userchoice = get_In_intf_rtn("Enter The No. to delete data in File (-1 to exit): ");
		userchoice--;

		// delete process
		deleted = FALSE;
		for (int i = 0; i < count; i++)
		{
			if (userchoice == i && !deleted)
			{
				// Save Backup
				savef("App->>>DELETE BACKUP:%s\n", data[i].patient.patientID);
				fclose_output();
				fp2 = fopen(OUT_PUT, "a");
				foreach_App_Backup(1, &data[i], fp2);
				savef("App->>>DELETE EOF\n");
				fclose(fp2);

				// Delete process
				out_MessageBox("Found the data need To delete");
				savef("App->>>START DELETE\n");
				savef("App->>>DELETE:%s DELETED %d\n", dutyStaff.staffID, i + 1);
				deleted = TRUE;
				count--;
				data[i] = data[(i + 1)];
			}
			else if (deleted)
			{
				// deleted process
				data[i] = data[(i + 1)];
			}
			else;
		}

		// OverWrite Pomision
		if (deleted)
		{
			system_loading();
			system_logo();
			overwriteP = get_In_charf_rtn("toupper","\n\n\nDo you sure want delete the data in file(Y = yes): ");
			if (overwriteP == 'Y')
			{
				// Save data
				savef("App->>>%s CONFIRM TO DELETE\n", dutyStaff.staffID);
				fp = fopen_Check_exit(APPOINTMENT_FILE, "w");
				system_loading();
				system_logo();
				if (fp != NULL)
				{
					// write everything to file
					for (int i = 0; i < count; i++)
						fprintf_App_LSK((data + i), fp);
					fclose(fp);

					// Display save successful
					out_MessageList(2,"Done, Deleted Sucessfull !!","CONFRIM THE UPDATED DATA");
					appointment_outList(OUT_DISPLAY_ALL_ONLY);
				}
				else
				{
					// Open file rejected
					savef("App->>>Open File Error Not Deleted\n");
					out_MessageList(2,"Deleting Unsucessfull !!","Get the overwrite pomision Fail");
				}
			}
			else
			{
				// Display Did not save data
				system_loading();
				system_logo();
				out_MessageBox("Data in file is still remain !!");
				savef("App->>>%s NOT DELETE THE DATA\n", dutyStaff.staffID);
			}
			savef("App->>>END DELETE\n");
		}
		else
		{
			// The choice is out of range
			system_logo();
			out_MessageList(2,"Invalid choice of selection !!","System are not found number need to delete");
		}
		// Ask user next
		system_loading();
		next = get_Next("Delete");
	} while (next == 'Y');
	
	// Ending task
	free(data);
}

void app_Modify_LSK()
{
	int size = 0;
	int count = 0;
	char next = 0;
	char comfirm = 0;
	int numModify = 0;
	FILE * fp = NULL;
	Appointment *data = NULL;

	// Allocate the enought space for store all the date in file
	size = get_appNum();
	data = malloc(sizeof(Appointment) * (size + 1));


	savef("App->>>START MODIFY\n");
	do {
		// DISPLAY ALL DATA IN FILE
		appointment_outList(OUT_DISPLAY_ALL_ONLY);

		// read the data in the file
		fp = fopen_Check_exit(APPOINTMENT_FILE, "r");
		count = 0;
		while (fscanf_App_LSK((data + count), fp) != EOF)
			count++;
		fclose(fp);
		printf("\n");

		// get number need to modify
		numModify = get_In_intf_rtn("Enter The No. to modify data in File (-1 to exit): ");
		system_loading();
		if (numModify != -1)
		{
			numModify--;

			if (isRange(0, count - 1, numModify))
			{
				// modify process
				savef("App->>>%s MODIFYED NO. %d\n", dutyStaff.staffID, numModify + 1);
				get_In_selected_Appointment((data + numModify));
				out_MessageList(2, "The Updated Data Is Shown As Below", "CONFRIM THE UPDATED DATA");
				out_Appointment_Detail((data + numModify));

				// OverWrite Pomision
				comfirm = get_In_charf_rtn("toupper", "Do you sure want to change the data in file(Y = yes): ");
				if (comfirm == 'Y')
				{
					// Start overwrite
					system_loading();
					savef("App->>>%s CONFIRM TO MAKE THE CHANGES\n");
					fp = fopen_Check_exit(APPOINTMENT_FILE, "w");
					if (fp != NULL)
					{
						// start save laa the data in file
						for (int i = 0; i < count; i++)
							fprintf_App_LSK((data + i), fp);
						fclose(fp);
						out_MessageBox("Done, Saving Sucessfull !!");
					}
					else
					{
						// reject overwrite from user
						out_MessageBox("The Following data is not saved !!");
					}
				}
				else
				{
					// Rejected change from user
					out_MessageList(2, "Modify Rejected by user", "Modify Unsuccessful !!");
				}
				system_loading();
			}
			else
			{
				// The choice is out of range
				system_logo();
				out_MessageList(2, "Invalid choice of selection !!", "System are not found number need to modify");
			}
			// ASk next or not
			next = get_Next("Modify");
		}
		else
		{
			system_loading();
			system_logo();
			out_MessageBox("Exiting Modify sub Module !!");
			next = 'N';
		}
		if (next == 'Y')
		{
			system("cls");
			system_logo();
		}
	} while (next == 'Y');

	// Ending task
	savef("App->>>END MODIFY\n");
	free(data);
}

void app_Repatient_LSK()
{
	int size = 0;
	int count = 0;
	int userchoice = 0;
	int patientSize = 0;
	char overwriteP = 0;
	FILE * fp = NULL;
	Appointment *data = NULL;
	PatientInfo patient[SIZE_PATIENT] = {NULL_PATIENT};


	//prepair a space enought to store all the data in file
	size = get_appNum();
	data = malloc(sizeof(Appointment) * (size + 1));


	//Read all the appointment form file
	fp = fopen_Check_exit(APPOINTMENT_FILE, "r");
	while (fscanf_App_LSK(&data[count], fp) != EOF)
		count++;
	fclose(fp);


	//Read all the patient data from file
	patientSize = fread_patient(patient);


	//Display and get input from user forvert data number
	savef("App->>>START RENEW\n");
	appointment_outList(OUT_DISPLAY_ALL_ONLY);
	printf("\n");
	userchoice = get_In_intf_rtn("Enter The No. to update Latest Data From Patient File (-1 for All): ");
	userchoice--;


	//Start forvert patient data base on ID
	system_loading();
	for (int i = 0; i < patientSize; i++)
	{
		for (int j = 0; j < count; j++)
		{
			if (ISSAME_STR strncmp(patient[i].patientID, data[j].patient.patientID, 9))
			{
				if ((userchoice + 1) == -1)
				{
					// in case user select all igt will overwrite all
					savef(".            %s UPDATED %d FROM PATIEN FILE\n", dutyStaff.staffID, j + 1);
					data[j].patient = patient[i];
					printf(MAX_BLANK_SHORT "%d was updated to lastest information\n", j + 1);
				}
				else
				{
					if (userchoice == i)
					{
						// User only select particular appointment
						savef(".            %s UPDATED %d FROM PATIEN FILE\n", dutyStaff.staffID, userchoice + 1);
						data[userchoice].patient = patient[i];
						printf(MAX_BLANK_SHORT "%d was updated to lastest information\n", userchoice + 1);
						break;
					}
				}
			}
		}
	}
	
	//Comfirm the updated data
	system("pause");
	system_loading();
	out_MessageBox("CONFRIM THE UPDATED DATA");
	printf(MAX_LINE MAX_EMPTY_EX2M);
	outOnly_Appointment_Haeder();
	printf(MAX_LINE);
	for (int i = 0; i < count; i++)
		outOnly_Appointment_Body(&data[i], i);
	printf(MAX_EMPTY_EX2M MAX_LINE);


	// get overwrite pomision
	overwriteP = get_In_charf_rtn("toupper", "Do you sure want to change the data in file(Y = yes): ");
	system_loading();
	system_logo();


	if (overwriteP == 'Y')
	{
		//Start overwrite appointment file
		savef("App->>>%s CONFIRM TO MAKE THE CHANGES OF APPOINTMENT FILE\n", dutyStaff.staffID);
		fp = fopen(APPOINTMENT_FILE, "w");
		for (int i = 0; i < count; i++)
			fprintf_App_LSK(&data[i], fp);
		fclose(fp);
		out_MessageList(3, "Done, Saving data In TEXT FILE Sucessfull !!", "The Latest Data From Patient File", "is Tranfer to the appoinment file");
	}
	else
	{
		// Did not save the latest data
		savef("App->>>%s CONFIRM TO REJECT THE CHANGES OF FORVERT DATA\n", dutyStaff.staffID);
		out_MessageList(2, "The Data Saving is rejected by user!!", "Saving unsucessful !!");
	}

	// Ending task
	savef("App->>>END RENEW\n");
	free(data);
}

void app_Histogram_LSK()
{
	int size = 0;
	int count = 0;
	int dataStatic[10] = { 0 };
	FILE * fp = NULL;
	Appointment *data = NULL;
	DateTime date[10] = { NULL_DATETIME };

	//prepair a space that enought to keep all the data
	size = get_appNum();
	data = malloc(sizeof(Appointment) * (size + 1));
	out_MessageBox("System Are Take Time Fromating The Graph");


	// calculate date
	for (int i = 0; i < 10; i++) 
	{
		date[i] = todayDate;
		cal_Date(&date[i], i);
		dataStatic[i] = 0;
	}

	//read appointment file
	fp = fopen_Check_exit(APPOINTMENT_FILE, "r");
	while (fscanf_App_LSK((data + count), fp) != EOF)
	{
		_sleep(20);
		count++;
	}
	fclose(fp);

	//calculate the data of static 
	for (int i = 0; i < 10; i++)
	{
		_sleep(50);
		for (int j = 0; j < count; j++)
		{
			if (cmpDate(&data[j].appointmentTime, &date[i]))
			{
				dataStatic[i]++;
			}
		}
	}
	system_loading();

	//Display and save the histogram in box
	savef("App->>>START HISTOGRAM\n");
	savef("App->>>Staff Hander : %s\n", dutyStaff.staffID);
	savef("."MAX_LINE_SHORT"."MAX_LINE_S_EX2M);
	savef("."MAX_BLANK_SHORT"|%-22s|%-22s|\n""."MAX_LINE_SHORT, "        Y-Axis", "    frequency");
	printf(MAX_LINE MAX_EMPTY_EX2M);
	printf(MAX_BLANK_LONG"|          y%22s%-50s|\n", "", "Next 10 Day Appointment List");
	printf(MAX_BLANK_LONG"|          ^%22s%50s|\n", "", "");
	printf(MAX_BLANK_LONG"|          |%72s|\n", "");
	for (int i = 0; i < 10; i++)
	{
		out_histogram_bar(dataStatic[(9 - i)], "");
		out_histogram_bar(dataStatic[(9 - i)], date[(9 - i)].sddmmyyyy);
		out_histogram_bar(dataStatic[(9 - i)], "");
		printf(MAX_BLANK_LONG"|          |%72s|\n", "");
	}
	printf(MAX_BLANK_LONG"|        --+----+----+----+----+----+----+--"
		   "--+----+----+----+----> X               |\n");
	printf(MAX_BLANK_LONG"|         0|    1    2    3    4    5    6  "
	  	   "  7    8    9    10                     |\n");
	printf(MAX_EMPTY_EX2M MAX_LINE);
	printf("\n\n\n"MAX_BLANK_SHORT);
	savef("."MAX_LINE_S_EX2M "."MAX_LINE_SHORT);
	savef("App->>>END HISTOGRAM\n");
	
	free(data);
}

void app_History_LSK()
{
	int selection = 0;
	char next = 0;
	do {
		// Display all the selection
		selection = select_History();
		system_loading();

		// Perform history application
		switch (selection)
		{
		case 1:
			fscanf_output();
			break;
		case 2:
			fscanf_output_source("App->>>START ADD","App->>>END ADD",16, 14);
			break;
		case 3:
			fscanf_output_source("App->>>START MODIFY","App->>>END MODIFY",19, 17);
			break;
		case 4:
			fscanf_output_source("App->>>START SEARCH","App->>>END SEARCH",19, 17);
			break;
		case 5:
			fscanf_output_source("App->>>START DISPLAY","App->>>END DISPLAY",20, 18);
			break;
		case 6:
			fscanf_output_source("App->>>START DELETE","App->>>END DELETE",19, 17);
			break;
		case 7:
			fscanf_output_source("App->>>START DAIRY","App->>>END DAIRY",18, 16);
			break;
		case 8:
			fscanf_output_source("App->>>START RENEW","App->>>END RENEW",18, 16);
			break;
		case 9:
			fscanf_output_source("App->>>START HISTOGRAM","App->>>END HISTOGRAM",22, 20);
			break;
		case 10:
			foverwrite_output();
			savef("App->>>History Clear By %s\n", dutyStaff.staffID);
			savef(MAX_LINE);
			break;
		}

		// ask about next 
		system_loading();
		next = get_Next("view History");
		if (next == 'Y')
			system("cls");


	} while (next == 'Y');
}

void app_Today_LSK(
	const DateTime today)
{
	int day = 0;
	char selection = '\0';
	char buffer[101] = "";
	DateTime temp = today;
	__crt_bool isrange = FALSE;

	// Display Today appointment list 
	dairy_Appointment(&today, "TODAY APPOINTMENT LIST");
	system_loading();
	do {

		// Let user choose view yesterday nor other day appointment list
		system_logo();
		selection = get_selection_char('F',             // Max is F
			"View Previous Day Appointment List",       // A
			"View Next Day Appointment List",           // B
			"Find Appointment List",                    // C
			"Find Next (n) Day Appointment List",       // D
			"Find Pevious (n) Day Appointment List",    // E
			"Return");                                  // F
		if (isRange('A', 'E', selection))
			system_loading();


		switch (selection)
		{
		case 'A':
			// Previous Day APPOINTMENT LIST
			cal_Date(&temp, -1);
			system_logo();
			sprintf(buffer,"|  Previous Day APPOINTMENT LIST (%10.10s) |",temp.sddmmyyyy);
			dairy_Appointment(&temp, buffer);
			break;
		case 'B':
			// Next Day APPOINTMENT LIST
			cal_Date(&temp, 1);
			system_logo();
			sprintf(buffer,"|    Next Day APPOINTMENT LIST (%10.10s)   |",temp.sddmmyyyy);
			dairy_Appointment(&temp, buffer);
			break;
		case 'C':
			// Search for the appointment list
			appointment_outList(OUT_SEARCH_DATE);
			break;
		case 'D':
			// Next (n)Day APPOINTMENT LIST
			system_logo();
			day = get_In_intf_rtn("Please Enter The Next (n) DaY : ");
			system_loading();
			cal_Date(&temp, day);
			system_logo();
			sprintf(buffer,"Next (n)Day APPOINTMENT LIST (%10.10s)",temp.sddmmyyyy);
			dairy_Appointment(&temp, buffer);
			break;
		case 'E':
			// Pevious (n)Day APPOINTMENT LIST
			system_logo();
			day = get_In_intf_rtn("Please Enter The Previos (n) Day : ");
			system_loading();
			day *= -1;
			cal_Date(&temp, day);
			system_logo();
			sprintf(buffer,"Pevious (n)Day APPOINTMENT LIST (%10.10s)",temp.sddmmyyyy);
			dairy_Appointment(&temp, buffer);
			break;
		}

		// check condition
		isrange = isRange('A', 'E', selection);
		if (isrange)
			system_loading();

	} while (isrange);
}

void app_save_backup_LSK()
{
	int size = 0;
	int count = 0;
	int conti = 0;
	char code[51] = "";
	FILE * fp = NULL;
	FILE * fp2 = NULL;
	Appointment *data = NULL;

	// allocate the structure pointer
	size = get_appNum();
	data = malloc(sizeof(Appointment) * (size + 1));

	// read data from file
	fp = fopen_Check_exit(APPOINTMENT_FILE, "r");
	count = 0;
	while (fscanf_App_LSK((data + count), fp) != EOF)
		count++;
	fclose(fp);

	// Comfirm save backup 
	savef("App->>>START BACKUP\n");
	appointment_outList(OUT_DISPLAY_ALL_ONLY);
	printf("\n\n\n"MAX_BLANK_SHORT);
	system("pause");
	system_loading();
	system_logo();
	printf("\n\n");
	conti = get_In_intf_rtn("Do you sure want ""Save following data as back up (Yes = 1) -->");

	
	if (conti == 1)
	{
		// Get the back up code prompt and save
		get_backupCode(code);
		out_MessageList(2, "This is your backup code: ", code);
		savef("App->>>%s saved the backup\n", dutyStaff.staffID);
		savef("App->>>BACKUP :%s\n", code);

		// start saving all the data into file
		fp2 = fopen(OUT_PUT, "a");
		foreach_App_Backup(count, data, fp2);
		savef("App->>>EOF:%s\n", code);
		fclose(fp2);

		// confirm with user
		out_MessageBox("Done, the data is saved in output.txt");
	}
	else
	{
		// Save rejected by user
		out_MessageBox("The following data is not saved as backup");
	}

	// Ending Task
	savef("App->>>END BACKUP\n");
	free(data);
	system_loading();
}

void app_Recover_Backup_LSK()
{
	int codeI = 0;
	int count = 0;
	char conti = '\0';
	char temp[200] = "";
	char temp2[20] = "";
	char code[20][16] = { "" };
	size_t size = 0;
	FILE * fp = NULL;
	FILE * bfp = NULL;
	Appointment *data = NULL;

	// allocate the structure pointer
	size = (size_t)get_appNum();
	data = malloc(sizeof(Appointment) * (size + 10));

	// Read all code in the file
	fclose_output();
	bfp = fopen_Check_exit(OUT_PUT, "r");
	count = 0;
	while (fscanf(bfp, "%[^\n]\n", temp) != EOF)
	{
		if (ISSAME_STR strncmp(temp, "App->>>BACKUP :", 15))
		{
			// scan the code and store in array
			sscanf(temp, "%[^:]:%s", temp2, code[count]);
			count++;
		}
	}
	fclose(bfp);

	// run here if have code
	if (count > 0)
	{
		// display all the code
		printf(MAX_LINE_SHORT MAX_LINE_S_EX2M);
		for (int i = 0; i < count; i++)
		{
			printf(MAX_BLANK_SHORT);
			printf("| %02d. %-40s|\n", i + 1, code[i]);
		}
		printf(MAX_LINE_S_EX2M MAX_LINE_SHORT);


		// Get code from user
		do {
			codeI = get_In_intf_rtn("Please select a code --> ");
		} while (!isRange(1, count + 1, codeI));
		system_loading();
		codeI--;


		// read backup data
		size = foreach_scanBackup(code[codeI], data);


		// Display data in backup file
		printf(MAX_LINE MAX_EMPTY_EX2M);
		outOnly_Appointment_Haeder();
		printf(MAX_LINE);
		for (size_t i = 0; i < size; i++)
		{
			outOnly_Appointment_Body((data + i), (int)i);
		}
		printf(MAX_EMPTY_EX2M MAX_LINE);
		printf("\n\n\n"MAX_BLANK_SHORT);
		system("pause");
		system_loading();


		// get overwrite pomision
		conti = get_selection_char('B',"Recover the following data to file","return");
		system_loading();
		if (conti == 'A')
		{
			// overwrite and info user
			fp = fopen(APPOINTMENT_FILE, "w");
			for (size_t i = 0; i < size; i++)
			{
				fprintf_App_LSK((data + i), fp);
			}
			fclose(fp);
			out_MessageList(3,"Update Appoinment.txt successful","All the the selected backup data","is copied from output.txt to Appoinment.txt");
		}
		else
		{
			// info usr did not overwrite the file 
			out_MessageList(3,"Update Appoinment.txt Unsuccessful","All the the selected backup data","is not copied to Appoinment.txt");
		}
	}
	else
	{
		// in case no backup found
		out_MessageList(3,"Did not found any Backup data!!","In \"output.txt\"(FILE)","Please backup frist before read");
	}

	// Ending task
	free(data);
}

void app_Recover_Delete_LSK()
{
	int input = 0;
	int count = 0;
	char conti = '\0';
	char temp[200] = "";
	char checkBuffer[200] = "";
	size_t size = 0;
	FILE * fp = NULL;
	FILE * bfp = NULL;
	__crt_bool found = FALSE;
	Appointment *data = NULL;
	PatientInfo patient = NULL_PATIENT;

	// allocate the structure pointer
	size = (size_t)get_appNum();
	data = malloc(sizeof(Appointment) * (size + 10));

	// Get user input
	system("cls");
	get_patient(&patient);

	// Read and display patient ID in the file
	fclose_output();
	bfp = fopen_Check_exit(OUT_PUT, "r");
	sprintf(checkBuffer, "App->>>DELETE BACKUP:%s", patient.patientID);
	printf(MAX_LINE MAX_EMPTY_EX2M);
	outOnly_Appointment_Haeder();
	printf(MAX_LINE);
	count = 0;
	while (fscanf(bfp, "%[^\n]\n", temp) != EOF)
	{
		if (ISSAME_STR strncmp(temp, checkBuffer, 32))
		{
			backup_fscanf(&data[count], bfp);
			outOnly_Appointment_Body(&data[count], count);
			count++;
			found = 1;
		}
	}
	fclose(bfp);
	printf(MAX_EMPTY_EX2M MAX_LINE);

	// Starting recover
	if (found)
	{
		// get the number need to recover
		input = get_In_intf_rtn("Please enter number need to recover: ");

		// appent the file by using data in file
		conti = get_selection_char('B',"Add back the following data to file","no return");
		system_loading();
		system_logo();
		if (conti == 'A')
		{
			// start appent the data back to current file using
			fp = fopen(APPOINTMENT_FILE, "a");
			fprintf_App_LSK((data + input - 1), fp);
			fclose(fp);

			// info user update sucessful
			out_MessageList(3,"Update Appoinment.txt successful","All the the selected backup data","is copied from output.txt to Appoinment.txt");
		}
		else
		{
			// info user update rejected and unsucessful
			out_MessageList(3,"Update Appoinment.txt Unsuccessful","All the the selected backup data","is not copied to Appoinment.txt");
		}
	}
	else
	{
		// cannot found
		out_MessageList(3,"The patient data is not found","in back up file !!!","Please try for other patient");
	}

	// Ending task
	system_loading();
	free(data);
}

#pragma warning(pop)

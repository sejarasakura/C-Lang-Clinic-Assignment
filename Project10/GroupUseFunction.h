/**********************************************************************
*
*       ALL THE SHARING FUNCTIOM, CONST AND SYRUCT DECALATION AREA
*
***********************************************************************/
#pragma once

#define GROUP_USE_FUNCTION_INLINE
#include<stdio.h>                                   // FILE and __crt_bool
// DEFINE AREA (CONSTANT)
#define TRUE              1                         // Boolean Use
#define FALSE             0                         // Boolean Use
#define BOOL_ONLY         !!                        // 1 && 0 only
#define ISSAME_STR        !                         // strcmp use
#define NO_CHANGE         (-1)                      // assgined use
#define DOCTOR            "DOCTOR"                  // Staff designation
#define NURSE             "NURSE"                   // Staff designation
#define PHAMACY           "PHAMACY"                 // Staff designatiom
#define ALL_STAFF         "STAFF"                   // Staff designatiom
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
#define MAX_LINE_S_E_EX2M        MAX_LINE_S_EX2M 
#define APPOINTMENT_FILE         "fappointment.txt"
#define PATIENT_FILE             "bfpatient.dat"
#define STAFF_FILE               "fstaff.txt"
#define VISIT_FILE               "bfpatientVisit.dat"
#define SIZE_PATIENT             50
// system command
#define SYSTEM_COLOR             "COLOR "
#define COLOUR_CODE_BLACK        "0"
#define COLOUR_CODE_RED          "4"
#define COLOUR_CODE_BRIGHY_WHITE "F"
#define INPUT_OFFSET             "         "MAX_BLANK_LONG
// set negetif to 0 set as define function is to prevent convertion data


/************************************************************************
*                                                                       *
*						GLOBAL DECALATION AREA                          *
*		   (MEMORY CONSTANT, STRUCTURE, ENUM AND VARIALBLE)             *
*                                                                       *
*************************************************************************/


//ENUM
#ifndef DEFINED_USING_ENUM
#define DEFINED_USING_ENUM
typedef enum Enum_gender {
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


//STRUCT || UNION 

#ifndef DATE_STRUCT_DEFINED
#define DATE_STRUCT_DEFINED
// Date share use
typedef struct Struct_date {
	int         day;
	int         month;
	int         year;
	char        sddmmyyyy[11];
	char        sTime[11];
	int         minute;
	int         hours;
}DateTime;
static DateTime const NULL_DATETIME = { 0,0,0,"00/00/0000","00:00xx",0,0 };
#endif
// tan jun chyi (PatientInfo)
typedef struct Struct_patient {
	char        patientID[11];
	char        name[51];
	Gender      gender;
	char        contactNum[51];
	char        allergies[51];
	DateTime    birthday;
}PatientInfo;

// lim kang yee (StaffInfo)
typedef struct Struct_staff {
	char staffID[5];
	char designation[31];
	char name[31];
	DateTime dateemployed;
	char qualification[31];
	char sarftPassword[31];
	char position[20];
}StaffInfo;

// lim sai keat (Appointment)
typedef struct Struct_appointment{
	DateTime    applyDate;
	char        staffDuty[51];
	DateTime    appointmentTime;
	PatientInfo patient;
	char        preferDoctor[51];
	char        email[51];
	char        remark[51];
}Appointment;

// lee jing wei (Visits)
typedef struct Struct_visit {
	DateTime t;
	char patientId[11];
	char staffId[5];
	char diagnosis[51];
	double charge;
}Visits;

// memory CONST
// use static to allow all file use the same variable / const
// use static to prevent redefination or (reinitialising)
// all struct must be have a NULL_ to do initialising task
static PatientInfo const NULL_PATIENT = { 
	"<ID>", "<name>", NULL_GENDER, "<concact num>", "<allergies>",
	{ 0,0,0,"00/00/0000","00:00xx", 0, 0 }
};
static StaffInfo const   NULL_STAFF = { 
	"<ID>", "<designation>", "<name>", 
	{ 0,0,0,"00/00/0000","00:00xx", 0, 0 }, 
	"<qualification>" ,"<password>", "<position>"
};
static Appointment const NULL_APPOINT = {
	{0,0,0,"00/00/0000","00:00xx", 0, 0}, "<staff>",
	{0,0,0,"00/00/0000","00:00xx", 0, 0},
	{"< ID >", "<name>", NULL_GENDER, "<concact num>", 
	"<allergies>",{0,0,0,"00/00/0000","00:00xx", 0, 0}}, 
	"<doctor>","<email>","<remark>"
};
static Visits const      NULL_VISITS = {
	{0,0,0,"00/00/0000","00:00xx", 0, 0},
	"< ID >", "<ID>", "<diagnosis>", 0.00
};


/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
 |                                                                       
 +					 FUNCTION CALL DECALATION AREA                      
 |                                                                      
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 Only decare the funtion need to public use/


/************************************************************************
*                                                                       *
*				 STREAM OUTPUT FUNCTION DECLARATION AREA                *
*                                                                       *
*************************************************************************/


/// PATIENT
void printf_Header_TJC();
void printf_MaxLine_TJC();
void printf_patient_TJC(PatientInfo data, int i);

/// APPOINTMENT
void out_Appointment_Maxline();
void out_Appointment_Haeder();
void out_Appointment_Detail(
	const Appointment *data);
void out_Appointment_Body(
	const Appointment * data,
	const int i);

/// STAFF
void printf_heading_StaffInfo();
void printf_body_StaffInfo(
	StaffInfo staff, 
	int i);

/// VISITS
void display_header_LJW();


/************************************************************************
*                                                                       *
*				 STREAM In/Out FUNCTION DECLARATION AREA                *
*				    & GET FUNCTION DECLARATION AREA                     *
*                                                                       *
*************************************************************************/


/// PATIENT
void scanf_patient(
	PatientInfo *data);
void get_patient_ID(
	PatientInfo *data);

/// APPOINTMENT
void get_In_Appointment(
	Appointment       * data,
	const PatientInfo * info
);
void get_In_new_Appointment(
	Appointment * data
);;
void get_Staff(
	StaffInfo *staff,
	const char * designationStaff
);
void get_patient(
	PatientInfo * desigination
);

/// STAFF
void scanf_StaffInfo(
	StaffInfo *staff);
void get_staff_Id(
	StaffInfo *staff);

/// VISITS

/************************************************************************
*                                                                       *
*				    BOOLEAN FUNCTION DECLARATION AREA                   *
*                                                                       *
*************************************************************************/
// in C bool is cant work __crt_bool as best fit decition is maked by complier
// start with 'is', return __crt_bool only (TRUE or FALSE)

/// PATIENT

/// APPOINTMENT
// check the hold struct (Appointment) is a valid data
__crt_bool isApp(
	const Appointment *data);

// check the struct(Patient info)
__crt_bool isPatient(
	const PatientInfo *data);

/// STAFF
// Only Check Key In Validation
int isStaffInfo(
	StaffInfo staff);
// Compare Staff
int staffcmp(
	StaffInfo staff1,
	StaffInfo staff2);

/// VISITS



/************************************************************************
*                                                                       *
*				  FILE STREAM FUNCTION DECLARATION AREA                 *
*                                                                       *
*************************************************************************/


/// PATIENT
void fwrite_patient(
	PatientInfo *data);
int fread_patient(
	PatientInfo *data);

/// APPOINTMENT
void fprintf_App_LSK(
	const Appointment *data,
	FILE * stream);
int fscanf_App_LSK(
	Appointment *data,
	FILE *stream);

/// STAFF
int fscanf_staff(
	StaffInfo *staff,
	FILE * fp);
void fprintf_staff(
	StaffInfo staff,
	FILE * fp);

/// VISITS


/************************************************************************
*                                                                       *
*			        	SUB MODULE DECALATION AREA	        	        *
*                                                                       *
*************************************************************************/
// most in this area is a combination function of 
// mix of calculate, stream, I/O, logic Checking, and storing/read data
// Question Request Function

/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
  |
  +                             APPOINTMENT
  |
  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-*/
/// LIM SAI KEAT

// main modules of appointment
void appointment_Menu();
// SEARCH MODULES
void app_Search_LSK();
// MODIFY MODULES
void app_Modify_LSK();
// DISPLAY MODULES
void app_Display_LSK();
// ADD RECORD MODULES
void app_Add_LSK();
// DELETE RECORD MODULE 
void app_Delete_LSK();
// VIEW DIARY MODULE(1 day)ONLY
void dairy_Appointment(
	const DateTime * date,
	const char * const fTitle66
);

/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
  |
  +                                PATIENT
  |
  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-*/
/// TAN JUN CHYI

// PATIENT MODULES
void patientInfo_Menu(void);
// SEARCH MODULES
void patient_search_TJC(void);
// MODIFY MODULES
void patient_modify_TJC(void);
// DISPLAY MODULES
void patient_display_TJC(void);
// ADD RECORD MODULES
void patient_add_TJC(void);



/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
  |
  +                                VISITS
  |
  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-*/
/// LEE JING WEI

// Visits MODULES
void patientVisits_Menu();
void visit_add();
void visit_search();
void visit_modify();
void visit_display();
void visit_delete();

/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
  |
  +                                STAFF
  |
  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-*/
/// LIM KANG YEE

// Staff MODULES
void staffInfo_Menu();
// SEARCH MODULES
void search_KY();
// MODIFLY MODULES
void modify_KY();
// DISPLAY MODULES
void show_KY();
// DELETE MODULES
void del_KY();
// ADD RECORD MODULES
void add_KY();
StaffInfo staff_Login();


/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
  |
  +                                vMAIN
  |
  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-*/

void system_Welcome_M();
void initialisingTask();
void system_ThankYou_M();
void menu_Loading();
void system_logo();
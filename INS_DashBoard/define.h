#ifndef DEFINE_H
#define DEFINE_H

#include <QString>
#include <QDebug>

#define WINDOWS_POSX 0
#define WINDOWS_POSY 0

#define WINDOWS_SIZEX 1280
#define WINDOWS_SIZEY 1024

#define STR_KOR(x)      QString::fromLocal8Bit((x))
#define STR_UTF8(x)     QString::fromUtf8((x))


/*******         #define DB_HOST "SDD 서버"			   *******/
#define DB_HOST "10.10.11.182"
#define DB_USER "SDDUser"
#define DB_PASS "SDDUser"
#define DB_NAME "INS_Dashboard"
#define DB_PORT 3306
#define CHOP(x) x[strlen(x) - 1] = ' '

/*******         #define JSON_URL "SDD 서버"			*******/
#define JSON_URL_ALL "http://10.10.12.158/ConvenienceServer/Convenience_Server.jsp?msg=all"
#define JSON_URL_DEVICELIST "http://10.10.12.158/ConvenienceServer/Convenience_Server.jsp?msg=devicelist"
#define JSON_URL_INSPACKTION "http://10.10.12.158/ConvenienceServer/Convenience_Server.jsp?msg=all"


/*******         #define PTT_HOST "PTT 서버"		    *******/
#define PPT_HOST "10.10.11.182"
#define PPT_PORT 4957

#define PPT_TALKTIME_SEC 3
#define MAX_CONNECTING_TIME 10000    /* ms */


/*******         TAG & AP Disable chack Interval 		*******/
#define ACTIVE_INTERVAL		8000
#define TIME_FORMAT			"yyyy-MM-dd hh:mm:ss.000zzz"


/******* FLAG **************************************************/
//#define _TESTCODE_DASHBOARD	// Test Code


#define DECK_SIZE 3

typedef struct {
	uint nTagTotal;
	uint nTagEnable;
	uint nTagDisable;
	uint nAPTotal;
	uint nAPEnable;
	uint nAPDisable;
	uint nPeopleTotal;
	uint nPeopleEnable;
	uint nPeopleDisable;
}CountSection;

typedef enum {
	NONE_DATA = 0,
	DASHBOARD_DATA,
	DEVICETYPE_DATA,
	DEVICELIST_DATA,
	INSPACKTION_DATA
}DATASET_KIND;

typedef enum {
	TAG_NO = 0,
	CALC_DATE,
	IN_CLS,
	XPOS,
	YPOS,
	ZPOS,
	SRC,
	POSKIND,
	ACC_V,
	BAT_V,
}ColumeIndex_TAG;

typedef enum {
	APID = 0,
	APDATE,
	APXPOS,
	APYPOS,
	APZPOS,
	APSRC,
	APPOSKIND,
	APBAT,
}ColumeIndex_AP;

typedef enum {
	DeviceID = 0,
	DeviceName,
	LocX,
	LocY,
	LocZ,
	DeviceType,
	DisasterType,
	ManagerID,
}ColumeIndex_DEVICE;

typedef struct {
	uint requestID;
	uint dataKind;
	bool chk;
	QList<QStringList> recode;
} resultTable;


struct colIndex {
	QString name;
	QString key;
	int index;
};

struct naming {
	QString name;
	int index;
};

struct SQL_Query {
	int index;
	QByteArray query;
};

const struct SQL_Query gSQL_Query[] = {
	{ NONE_DATA, ""},
	{ DASHBOARD_DATA, "select * from taginfo" },
	{ DEVICETYPE_DATA, "select * from enumsafetydevice" },
	{ DEVICELIST_DATA, "select * from safetydevicemanagment" },
	{ INSPACKTION_DATA, "" },
};

const struct colIndex gTAG_INDEX[] = {
	{ STR_KOR("TAG 이름"), "TAG_NO", TAG_NO },
	{ STR_KOR("수신 날짜"), "CALC_DATE", CALC_DATE },
	{ STR_KOR("Zone ID"), "IN_CLS", IN_CLS },
	{ STR_KOR("X좌표"), "XPOS", XPOS },
	{ STR_KOR("Y좌표"), "YPOS", YPOS },
	{ STR_KOR("Z좌표"), "ZPOS", ZPOS },
	{ STR_KOR("측위 소스"), "SRC", SRC },
	{ STR_KOR("태그 종류"), "POSKIND", POSKIND },
	{ STR_KOR("가속도"), "ACC_V", ACC_V },
	{ STR_KOR("베터리 잔량"), "BAT_V", BAT_V },
};

const struct colIndex gAP_INDEX[] = {  // 수정 필요
	{ STR_KOR("TAG 이름"), "TAG_NO", TAG_NO },
	{ STR_KOR("수신 날짜"), "CALC_DATE", CALC_DATE },
	{ STR_KOR("Zone ID"), "IN_CLS", IN_CLS },
	{ STR_KOR("X좌표"), "XPOS", XPOS },
	{ STR_KOR("Y좌표"), "YPOS", YPOS },
	{ STR_KOR("Z좌표"), "ZPOS", ZPOS },
	{ STR_KOR("측위 소스"), "SRC", SRC },
	{ STR_KOR("태그 종류"), "POSKIND", POSKIND },
	{ STR_KOR("가속도"), "ACC_V", ACC_V },
	{ STR_KOR("베터리 잔량"), "BAT_V", BAT_V },
};

const struct colIndex gDEVICE_INDEX[] = {
	{ STR_KOR("장비번호"),	"DeviceID",		DeviceID },
	{ STR_KOR("장비명"),	"DeviceName",	DeviceName },
	{ STR_KOR("X좌표"),		"LocX",			LocX },
	{ STR_KOR("Y좌표"),		"LocY",			LocY },
	{ STR_KOR("데크"),		"LocZ",			LocZ },
	{ STR_KOR("장비분류"),	"DeviceType",	DeviceType },
	{ STR_KOR("재난분류"),	"DisasterType", DisasterType },
	{ STR_KOR("담당자"),	"ManagerID",	ManagerID },
};

const struct naming gNAME_SRC[] = {
	{"TAG RTT", 0},
	{"TAG RSS", 1},
	{"TAG LQI", 2},
	{"Phone RSS", 3},
	{ "융합", 4},
};

const struct naming gNAME_POSKIND[] = {
	{ "ZigBee", 1 },
	{ "UWB", 2 },
};

//resultTable gDB_Result;

#endif // DEFINE_H

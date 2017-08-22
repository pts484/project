#ifndef DEFINE_H
#define DEFINE_H

#include <QString>
#include <QDebug>

#define WINDOWS_POSX 0
#define WINDOWS_POSY 0

#define WINDOWS_SIZEX 1600
#define WINDOWS_SIZEY 1200

#define STR_KOR(x)      QString::fromLocal8Bit((x))
#define STR_UTF8(x)     QString::fromUtf8((x))


/*******         #define DB_HOST "SDD 서버"			   *******/
#define DB_HOST "10.10.11.182"
#define DB_USER "SDDUser"
#define DB_PASS "SDDUser"
#define DB_NAME "INS_Dashboard"
#define DB_PORT 3306
#define CHOP(x) x[strlen(x) - 1] = ' '


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



typedef struct {
	bool chk;
	QList<QStringList> recode;
} resultTable;

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
} CountSection;

typedef enum {

	TagID = 0,
	TagDATE,
	TagINCLS,
	TagXPOS,
	TagYPOS,
	TagZPOS,
	TagSRC,
	TagPOSKIND,
	TAGACC,
	TagBAT,

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
}ColumeIndex_Device;

#endif // DEFINE_H

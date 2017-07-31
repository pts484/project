#ifndef DEFINE_H
#define DEFINE_H

#include <QString>
#include <QDebug>
#include <qtextcodec.h>

#define WINDOWS_POSX 0
#define WINDOWS_POSY 0

#define WINDOWS_SIZEX 1600
#define WINDOWS_SIZEY 1200

//#define DB_HOST "koto.i234.me"
#define DB_HOST "kotoko.iptime.org"
#define DB_USER "dbuser"
#define DB_PASS "qwe123"
#define DB_NAME "INS_Dashboard"
#define DB_PORT 3307
#define CHOP(x) x[strlen(x) - 1] = ' '

#define STR_KOR(x)      QString::fromLocal8Bit((x))
#define STR_UTF8(x)     QString::fromUtf8((x))

#endif // DEFINE_H

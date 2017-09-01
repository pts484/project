#ifndef CUSTOMLABEL_H_
#define CUSTOMLABEL_H_

#include "css3_code.h"
#include <QLabel>

class CustomLabel : public QLabel {
	Q_OBJECT

public:
	CustomLabel(QWidget *parent = 0);
	~CustomLabel() {};

	void setCSS3Style(const char *, const char *);
};


#endif
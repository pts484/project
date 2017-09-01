#include "CustomLabel.h"

CustomLabel::CustomLabel(QWidget *parent)
	: QLabel(parent) {

	this->setAlignment(Qt::AlignLeft | Qt::AlignTop);
	this->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
	this->setMargin(0);

	this->setText("ABCDEF");
	this->setCSS3Style(BASE_BG_COLOR, BASE_BODER_COLOR);

}

void CustomLabel::setCSS3Style(const char *bgColor, const char *boderColor) {

	QString &styleSheet = QString(CUSTOMLABEL_STYLE).arg(bgColor).arg(boderColor);
	this->setStyleSheet(styleSheet);
}
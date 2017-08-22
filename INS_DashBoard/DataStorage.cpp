#include "DataStorage.h"




/*********************************************************************************/
/* Buffer */
/*********************************************************************************/
Buffer::Buffer(void) {
	Clear();
}

Buffer::~Buffer(void) {

	if (!pTotal) delete pTotal;
	if (!pEnable) delete pEnable;
	if (!pDisable) delete pDisable;

	this->clear();
	viewItems.clear();
}



const QStringList& Buffer::findRecode(QString key) {
	return this->find(key).value();
}



void Buffer::addRecode(QString key, QStringList &recode) {

	this->insert(key, recode);

	rowGroup *tmp;

	ViewBuffer::Iterator i = viewItems.find(key);

	if (i != viewItems.end()) { /** Update Data **/
		tmp = &i.value();

		for (int i = 0; i < recode.size(); ++i) {
			tmp->recode.at(i)->setText(recode.at(i));
		}
		
		qDebug() << "update Add Buffer :" << this->size();
		qDebug() << "update Add VIewer :" << viewItems.size();

	} else {					/** New add Data **/
		tmp = new rowGroup();
		tmp->recode.clear();
		tmp->isActive = false;

		for (int i = 0; i < recode.size(); ++i) {
			QStandardItem *pObj = new QStandardItem(recode.at(i));
			tmp->recode << pObj;
		}
		viewItems.insert(key, *tmp);
		
		qDebug() << "new Add Buffer :" << this->size();
		qDebug() << "new Add VIewer :" << viewItems.size();
	}

	tmp->isActive = true;
}



void Buffer::deleteRecode(QString key) {

	if (this->size() <= 0 && viewItems.size() <= 0) {
		qDebug() << "buffer is Empty : deleteRecode()";
		return;
	}

	this->remove(key);

	rowData *row = &viewItems.find(key).value().recode;
	for (int i = 0; i < row->size(); ++i) {
		delete row->at(i);
	}
	row->clear();
	viewItems.remove(key);

	qDebug() << "Del Buffer :" << this->size();
	qDebug() << "Del VIewer :" << viewItems.size();
}

void Buffer::updateModel(void) {

	viewModel.clear();
	int rowNum = 0;

	ViewBuffer::Iterator i = viewItems.begin();
	while (i != viewItems.end()) {
	
		qDebug() << i.value().recode;
		viewModel.insertRow(rowNum, i.value().recode);
		++rowNum;
		++i;
	}
}

void Buffer::checkToActive(const uint &Inteval, int index) {

	if (this->size() <= 0 && viewItems.size() <= 0) {
		qDebug() << "buufer is Empty : checkToActive()";
		return;
	}

	uint curTime = QDateTime::currentDateTime().toTime_t();
	QString format = TIME_FORMAT;

	ViewBuffer::Iterator i = viewItems.begin();
	while (i != viewItems.end()) {

		rowGroup *pObj = &i.value();
		QDateTime dataTime = QDateTime::fromString(pObj->recode.at(index)->text(), format);

		uint inverval = curTime - dataTime.toTime_t();

		if (inverval < Inteval) {
			pObj->isActive = true;
		} else {
			pObj->isActive = false;
		}
		++i;

		qDebug() << pObj->recode.at(index-1)->text()<< " : " << inverval << " : " << pObj->isActive;
	}
	checkToNumber();
}

void Buffer::checkToNumber(void) {
	if (this->size() <= 0 && viewItems.size() <= 0) {
		*pTotal = 0;
		*pEnable = 0;
		*pDisable = 0;
		return;
	}

	ViewBuffer::Iterator i = viewItems.begin();
	while (i != viewItems.end()) {

		rowGroup *pObj = &i.value();

		if (pObj->isActive) {
			++(*pEnable);
		}
		else {
			++(*pDisable);
		}


		++(*pTotal);
		++i;

		qDebug() << "Number Count() : "<< *pTotal << " = " << *pEnable << " + " << *pDisable;
	}
}

void Buffer::setViewHeader(QStringList list) {
	viewModel.setHorizontalHeaderLabels(list);

}


void Buffer::Clear(void) {

	pTotal = new uint(0);
	pEnable = new uint(0);
	pDisable = new uint(0);

	this->clear();
	viewItems.clear();
}

void Buffer::Clear(uint *_Total, uint *_Enable, uint *_Disable) {

	pTotal = _Total;
	pEnable = _Enable;
	pDisable = _Disable;

	*pTotal = 0;
	*pEnable = 0;
	*pDisable = 0;

	this->clear();
	viewItems.clear();
}



/*********************************************************************************/
/* DataStorage																	 */
/*********************************************************************************/

DataStorage::DataStorage(void){

	mCountData = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	mTagBuffer.Clear(&mCountData.nTagTotal, &mCountData.nTagEnable, &mCountData.nTagDisable);
	mAPBuffer.Clear(&mCountData.nAPTotal, &mCountData.nAPEnable, &mCountData.nAPDisable);
		

#ifdef _TESTCODE_DASHBOARD
	/************ test Code ********************************************************/
	QStringList rrecode[10];
	rrecode[0] << "7718106562570" << "2017-08-09 15:09:29.000938" << "Room6" \
		<< "36.3400000" << "32.8300000" << "21.90000" << "1" << "1" << "0" << "3";
	rrecode[1] << "7718106562571" << "2017-08-07 15:09:29.000938" << "Room6" \
		<< "36.3400000" << "32.8300000" << "21.90000" << "1" << "1" << "0" << "3";
	rrecode[2] << "7718106562572" << "2017-08-14 15:09:29.000938" << "Room6" \
		<< "36.3400000" << "32.8300000" << "21.90000" << "1" << "1" << "0" << "3";
	rrecode[3] << "7718106562573" << "2017-08-12 15:09:29.000938" << "Room6" \
		<< "36.3400000" << "32.8300000" << "21.90000" << "1" << "1" << "0" << "3";

	mTagBuffer.addRecode(rrecode[0].at(ColumeIndex_TAG::TagID), rrecode[0]);
	mTagBuffer.addRecode(rrecode[1].at(ColumeIndex_TAG::TagID), rrecode[1]);
	mTagBuffer.addRecode(rrecode[2].at(ColumeIndex_TAG::TagID), rrecode[2]);
	mTagBuffer.addRecode(rrecode[3].at(ColumeIndex_TAG::TagID), rrecode[3]);

	mTagBuffer.checkToActive(ACTIVE_INTERVAL, ColumeIndex_TAG::TagDATE);
	mTagBuffer.deleteRecode(rrecode[0].at(ColumeIndex_TAG::TagID));

	mTagBuffer.checkToActive(ACTIVE_INTERVAL, ColumeIndex_TAG::TagDATE);
	qDebug() << mCountData.nTagTotal << mCountData.nTagEnable << mCountData.nTagDisable;
	/*******************************************************************************/
#endif 
	
}

DataStorage::~DataStorage(){
}


void DataStorage::checkToPeople(void) {

	uint *_Total = &mCountData.nPeopleTotal;
	uint *_Safe = &mCountData.nPeopleEnable;
	uint *_Denger = &mCountData.nPeopleDisable;

	if (mTagBuffer.size() <= 0 && mTagBuffer.getViewItems()->size() <= 0) {
		*_Total = 0;
		*_Safe = 0;
		*_Denger = 0;
		return;
	}

	ViewBuffer::const_iterator i = (mTagBuffer.getViewItems())->begin();
	while (i != (mTagBuffer.getViewItems())->end()) {

		const rowGroup *pObj = &i.value();

		double z_pos = pObj->recode.at(TagZPOS)->text().toDouble();

		if (z_pos >= 3.0) { //Evacuation condition
			++(*_Safe);
		} else {
			++(*_Denger);
		}
		
		++(*_Total);
		++i;

		qDebug() << "Safe Count() : " << *_Total << " = " << *_Safe << " + " << *_Denger;
	}
}

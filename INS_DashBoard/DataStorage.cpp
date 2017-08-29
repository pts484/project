#include "DataStorage.h"

/*********************************************************************************/
/* Buffer */
/*********************************************************************************/
Buffer::Buffer(void) {
	Clear();
}

Buffer::~Buffer(void) {

	this->clear();
}



const QStringList& Buffer::findRecode(QString key) {
	return this->find(key).value().recode;
}



void Buffer::addRecode(QString key, QStringList &recode, int colIndex, const uint &Inteval) {

	rowGroup tmp;
	tmp.isActive = false;
	tmp.recode.clear();

	//Time Check && Counting
	uint curTime = QDateTime::currentDateTime().toTime_t();
	QDateTime dataTime = QDateTime::fromString(recode.at(colIndex), QString(TIME_FORMAT));
	uint inverval = curTime - dataTime.toTime_t();

	if (inverval < Inteval) {
		tmp.isActive = true;

	} else {
		tmp.isActive = false;
	}
	tmp.recode = recode;

	
	// Add Recode 
	this->insert(key, tmp);
}



void Buffer::deleteRecode(QString key) {
	this->remove(key);
	//qDebug() << "Del Buffer :" << this->size();
}

void Buffer::updateModel(void) {


	QStringList DisableKey;
	DisableKey.clear();
	viewModel.clear();

	//get Disable Tag
	HashBuffer::const_iterator i = this->constBegin();
	for (; i != this->constEnd(); ++i) {
		if (i.value().isActive == false) {
			DisableKey << i.key();
		}
	}
	
	uint disableSize  = DisableKey.size();
	uint ModelSize = viewModel.rowCount();


	for (int i = 0; i < DisableKey.size(); ++i) {

		QList<QStandardItem *> tmp = viewModel.findItems(DisableKey.at(i));
		QStringList tmplist = findRecode(DisableKey.at(i));

		if (tmp.size() <= 0) {
		
			for (int j = 0; j < tmplist.size(); ++j) {
				QStandardItem *tmptime = new QStandardItem(tmplist.at(j));
				tmp << tmptime;
			}
			viewModel.appendRow(tmp);

		} else {

			// 검증 안됨 ------------------------------------
			QList<QStandardItem *> tmp = viewModel.takeRow(i);
			for (int j = 0; j < tmplist.size(); ++j) {
				tmp.at(j)->setData(tmplist.at(j));
			}
			viewModel.appendRow(tmp);
		}
	}
	if ((ModelSize - disableSize) > 0) {
		viewModel.removeRows(disableSize+1, (ModelSize - disableSize));
	}

}

inline void Buffer::checkToNumber(void) {
	if (this->size() <= 0) {
		mTotal = 0;
		mEnable = 0;
		mDisable = 0;
		return;
	}

	mTotal = 0;
	mEnable = 0;
	mDisable = 0;

	HashBuffer::ConstIterator i = this->constBegin();
	while (i != this->end()) {

		if (i.value().isActive) {
			++mEnable;
		}
		else {
			++mDisable;
		}
		++mTotal;
		++i;
	}
}

void Buffer::setViewHeader(QStringList list) {
	viewModel.setHorizontalHeaderLabels(list);
}

void Buffer::Clear(void) {

	mTotal = 0;
	mEnable = 0;
	mDisable = 0;

	this->clear();
}

void Buffer::updateBuffer(resultTable *result) {

	while (!result->recode.isEmpty()) {
		QStringList &pObj = result->recode.takeFirst();
		addRecode(pObj.at(ColumeIndex_TAG::TAG_NO), pObj, CALC_DATE);
	}
	checkToNumber();
	updateModel();
}


/*********************************************************************************/
/* TreeBuffer																	 */
/*********************************************************************************/
TreeBuffer::TreeBuffer() {

}
TreeBuffer::~TreeBuffer() {
}

void TreeBuffer::addDevice(QString key, QStringList &_device) {

	QHash<QString, rowData>::const_iterator it = this->constFind(key);

	if (it == this->constEnd()) { //장비가 없으면 추가
		rowData tmp;
		tmp.clear();

		for each(QString str in _device) {
			tmp << new QStandardItem(str);
		}
		this->insert(key, tmp);
		qDebug() << "device insert ::" << key;
	} else {						//장비가 있으면 값 수정

		int i = 0;
		for each(QString str in _device) {
			it.value().at(i)->setData(str);
			++i;
		}
		qDebug() << "device update ::" << key;
	}
}

void TreeBuffer::delDevice(QString key) {
	rowData mObj = this->take(key);
	for each(QStandardItem *obj in mObj) {
		if (obj != NULL) {
			delete obj;
			obj = NULL;
		}
	}
}

void TreeBuffer::setViewHeader(QStringList list) {
	treeModel.setHorizontalHeaderLabels(list);
}

void TreeBuffer::updateModel() {

	QHash<QString, rowData>::iterator it = this->begin();
	for (; it != this->end(); ++it) {
		QString type = it.value().at(ColumeIndex_DEVICE::DeviceType)->text();

		QHash<QString, QStandardItem *>::iterator pRoot = rootItem.find(type);

		if (pRoot != rootItem.end()) {
			pRoot.value()->appendRow(it.value());
		} else {
			QStandardItem *pRootItem = new QStandardItem(type);
			rootItem.insert(type, pRootItem);
			pRootItem->appendRow(it.value());
			treeModel.appendRow(pRootItem);
		}
	}
}

void TreeBuffer::updateType() {

	//treeModel.findItems();
}

void TreeBuffer::updateBuffer(resultTable *result) {

	while (!result->recode.isEmpty()) {
		QStringList *pObj = &result->recode.takeFirst();
		addDevice(pObj->at(ColumeIndex_DEVICE::DeviceID), *pObj);
	}

	updateModel();
}
/*********************************************************************************/
/* DataStorage																	 */
/*********************************************************************************/

DataStorage::DataStorage(void){
		
	mSafety = 0;
	mDenger = 0;

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

	/*******************************************************************************/
#endif 
	
}

DataStorage::~DataStorage(){
}


void DataStorage::checkToPeople(void) {

	mSafety = 0;
	mDenger = 0;

	HashBuffer::const_iterator i = mTagBuffer.constBegin();
	for (; i != mTagBuffer.constEnd(); ++i) {

		if (i.value().recode.at(ZPOS).toDouble() >= 3.0) {
			++mSafety;
		} else {
			++mDenger;
		}
	}
}

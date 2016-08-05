#include "paramgroup.h"
ParamGroup::ParamGroup(QString name,QWidget*parent):QGroupBox(name,parent){
	QLayout*outer=new QVBoxLayout(this);
	outer->setContentsMargins(0,0,0,0);
	QWidget*frame=new QWidget(this);
	outer->addWidget(frame);
	frame->setLayout(layout);
	layout->addLayout(line);
	setStyleSheet("font-weight:bold");
	frame->setStyleSheet("font-weight:normal");
	setCheckable(true);
	connect(this,&QGroupBox::toggled,frame,&QWidget::setVisible);
}
void ParamGroup::enable(){
	for(auto param:*this)param->setEnabled(true);
}
void ParamGroup::disable(){
	for(auto param:*this)param->setEnabled(false);
}
bool ParamGroup::hdf5read(hid_t loc){
	bool result=true;
	QByteArray array=title().toUtf8();
	hid_t group=h5group(array.data(),loc);
	for(Param*param:*this)result&=param->hdf5read(group);
	H5Gclose(group);
	return result;
}
bool ParamGroup::hdf5write(hid_t loc){
	bool result=true;
	QByteArray array=title().toUtf8();
	hid_t group=h5group(array.data(),loc);
	for(Param*param:*this)result&=param->hdf5write(group);
	H5Gclose(group);
	return result;
}
void ParamGroup::add(Param*param,bool inlined){
	if(!inlined)layout->addLayout(line=new QHBoxLayout());
	line->addWidget(param);
	push_back(param);
}
#include "registerdata.h"

RegisterData::RegisterData()
{
    _bActive = false;
    _bUnsigned = false;
    _scaleFactor = 1;
    _reg = 0;
    _text = "";
    _color = QColor("-1");
}

void RegisterData::CopyTo(RegisterData * pData)
{
    pData->setActive(this->isActive());
    pData->setColor(this->color());
    pData->setRegisterAddress(this->registerAddress());
    pData->setScaleFactor(this->scaleFactor());
    pData->setText(this->text());
    pData->setUnsigned(this->isUnsigned());
}


bool RegisterData::isUnsigned() const
{
    return _bUnsigned;
}

void RegisterData::setUnsigned(bool value)
{
    _bUnsigned = value;
}

double RegisterData::scaleFactor() const
{
    return _scaleFactor;
}

void RegisterData::setScaleFactor(double value)
{
    _scaleFactor = value;
}

QString RegisterData::text() const
{
    return _text;
}

void RegisterData::setText(const QString &value)
{
    _text = value;
}

QColor RegisterData::color() const
{
    return _color;
}

void RegisterData::setColor(const QColor &value)
{
    _color = value;
}

quint16 RegisterData::registerAddress() const
{
    return _reg;
}

void RegisterData::setRegisterAddress(const quint16 &value)
{
    _reg = value;
}

bool RegisterData::isActive() const
{
    return _bActive;
}

void RegisterData::setActive(bool value)
{
    _bActive = value;
}

bool RegisterData::sortRegisterDataList(const RegisterData& s1, const RegisterData& s2)
{
    return s1.registerAddress() < s2.registerAddress();
}


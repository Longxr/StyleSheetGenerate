#include "WidgetNameModel.h"

WidgetNameModel::WidgetNameModel()
{

}

WidgetNameModel::WidgetNameModel(const WidgetNameModel &other)
{
    this->m_className = other.GetWidgetClassName();
    this->m_objectName = other.GetWidgetObjectName();
    this->m_qss = other.GetQssString();
}

WidgetNameModel &WidgetNameModel::operator=(const WidgetNameModel &other)
{
    if(&other != this){
        this->m_className = other.GetWidgetClassName();
        this->m_objectName = other.GetWidgetObjectName();
        this->m_qss = other.GetQssString();
    }

    return *this;
}

WidgetNameModel::~WidgetNameModel()
{

}

//****************************Getter && Setter*************************************
QString WidgetNameModel::GetWidgetClassName() const
{
    return m_className;
}

QString WidgetNameModel::GetWidgetObjectName() const
{
    return m_objectName;
}

QString WidgetNameModel::GetQssString() const
{
    return m_qss;
}

void WidgetNameModel::SetWidgetClassName(const QString &str)
{
    m_className = str;
}

void WidgetNameModel::SetWidgetObjectName(const QString &str)
{
    m_objectName = str;
}

void WidgetNameModel::SetQssString(const QString &str)
{
    m_qss = str;
}

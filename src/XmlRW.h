#ifndef XMLRW_H
#define XMLRW_H

#include <QObject>
#include <QtXml>
#include "DataModel/WidgetNameModel.h"

class XmlRW : public QObject
{
    Q_OBJECT
public:
    explicit XmlRW(QObject *parent = 0);

    bool ImportFromUI(const QString& strPath);
    bool ExportToQSS(const QString& strPath);

private:
    void ReadXBEL();
    void ReadWidget();
    void ReadLayout();
    void ReadItem();
    void ReadQssProperty();

    QXmlStreamReader xml;
    QString m_tsFilePath;
    QList<WidgetNameModel> m_list;
};

#endif // XMLRW_H

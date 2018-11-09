#include "XmlRW.h"

#include <QDebug>
#include <QDomNodeList>

#define ROOT_ELEMENT        "ui"
#define WIDGET_ELEMENT      "widget"
#define PROPERTY_ELEMENT    "property"
#define LAYOUT_ELEMENT      "layout"
#define ITEM_ELEMENT        "item"

XmlRW::XmlRW(QObject *parent) : QObject(parent)
{

}

bool XmlRW::ImportFromUI(const QString& strPath)
{
    QFile file(strPath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }
    else {
        xml.setDevice(&file);
        m_list.clear();

        if (xml.readNextStartElement()) {
            QString strName = xml.name().toString();
            if (strName== ROOT_ELEMENT) {
                QXmlStreamAttributes attributes = xml.attributes();
                if (attributes.hasAttribute("version")) {
                    QString strVersion = attributes.value("version").toString();
                    qDebug() << "version : " << strVersion;
                }

                ReadXBEL();
            }
            else {
                xml.raiseError("XML file format error.");
            }
        }

        file.close();

        return true;
    }
}

bool XmlRW::ExportToQSS(const QString& strPath)
{
    QFile file(strPath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return false;
    }
    else {
        QTextStream outStream(&file);

        foreach(WidgetNameModel model, m_list) {
            qDebug() << "calss:" << model.GetWidgetObjectName() << "qss:" << model.GetQssString();

            if(model.GetQssString().isEmpty()) {
                continue;
            }

            outStream << "/* " << model.GetWidgetClassName() << "#" << model.GetWidgetObjectName() << " */\n";

            QString strQss = model.GetQssString();

            if(!strQss.contains("{")) {
                strQss.insert(0, "{");
                if(strQss.right(1) != ";") {
                    strQss.append(";\n}");
                }
                else {
                    strQss.append("\n}");
                }
            }

            int index1 = strQss.indexOf("{");
            int index2 = strQss.indexOf("#");

            if(-1 == index2 || index1 < index2) {
                if(0 == index1) {
                    strQss.insert(0, "#" + m_list.at(0).GetWidgetObjectName() + " " + model.GetWidgetClassName() + "#" + model.GetWidgetObjectName());
                }
                else if(-1 != strQss.indexOf(model.GetWidgetClassName())) {
                    QString strNew = /*"#" + m_list.first().GetWidgetObjectName()*/m_list.first().GetWidgetObjectName() + " " + model.GetWidgetClassName() + "#" + model.GetWidgetObjectName();
                    strQss.replace(model.GetWidgetClassName() , strNew);
                }
            }
            else {
                QString strNew = /*"#" + m_list.first().GetWidgetObjectName()*/m_list.first().GetWidgetObjectName() + " " + model.GetWidgetClassName();
                strQss.replace(model.GetWidgetClassName() , strNew);
            }

            outStream << strQss << "\n\n\n";
        }
    }

    file.close();

    return true;
}

void XmlRW::ReadXBEL()
{
    Q_ASSERT(xml.isStartElement() && xml.name().toString() == ROOT_ELEMENT);

    while (xml.readNextStartElement()) {
        if (xml.name().toString() == WIDGET_ELEMENT) {
            ReadWidget();
        }
        else {
            xml.skipCurrentElement();
        }
    }
}

void XmlRW::ReadWidget()
{
    Q_ASSERT(xml.isStartElement() && xml.name().toString() == WIDGET_ELEMENT);

    QXmlStreamAttributes attributes = xml.attributes();
    WidgetNameModel model;
    model.SetWidgetClassName(attributes.value("class").toString());
    model.SetWidgetObjectName(attributes.value("name").toString());
    m_list.append(model);

    while (xml.readNextStartElement()) {
        if(xml.name().toString() == PROPERTY_ELEMENT) {
            QXmlStreamAttributes attributes = xml.attributes();
            if (attributes.hasAttribute("name")) {
                if("styleSheet" == attributes.value("name").toString()) {
                    ReadQssProperty();
                }
                else {
                    xml.skipCurrentElement();
                }
            }
        }
        else if(xml.name().toString() == LAYOUT_ELEMENT) {
            ReadLayout();
        }
        else if(xml.name().toString() == WIDGET_ELEMENT) {
            ReadWidget();
        }
        else {
            xml.skipCurrentElement();
        }
    }
}

void XmlRW::ReadLayout()
{
    Q_ASSERT(xml.isStartElement() && xml.name().toString() == LAYOUT_ELEMENT);

    while (xml.readNextStartElement()) {
        if (xml.name().toString() == ITEM_ELEMENT) {
            ReadItem();
        }
        else {
            xml.skipCurrentElement();
        }
    }
}

void XmlRW::ReadItem()
{
    Q_ASSERT(xml.isStartElement() && xml.name().toString() == ITEM_ELEMENT);

    while (xml.readNextStartElement()) {
        if (xml.name().toString() == WIDGET_ELEMENT) {
            ReadWidget();
        }
        else if (xml.name().toString() == LAYOUT_ELEMENT) {
            ReadLayout();
        }
        else {
            xml.skipCurrentElement();
        }
    }
}

void XmlRW::ReadQssProperty()
{
    Q_ASSERT(xml.isStartElement() && xml.name().toString() == PROPERTY_ELEMENT);

    QString strQss;

    while (xml.readNextStartElement()) {
        if (xml.name().toString() == "string") {
            strQss = xml.readElementText();
            if(!strQss.isEmpty()) {
                m_list.last().SetQssString(strQss);
            }
        }
        else {
            xml.skipCurrentElement();
        }
    }
}

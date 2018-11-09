#ifndef WIDGETNAMEMODEL_H
#define WIDGETNAMEMODEL_H

#include <QString>

class WidgetNameModel
{
public:
    explicit WidgetNameModel();
    WidgetNameModel(const WidgetNameModel&);
    WidgetNameModel &operator= (const WidgetNameModel&);
    ~WidgetNameModel();

    QString GetWidgetClassName() const;
    QString GetWidgetObjectName() const;
    QString GetQssString() const;

    void SetWidgetClassName(const QString &str);
    void SetWidgetObjectName(const QString &str);
    void SetQssString(const QString &str);

private:
    QString m_className;
    QString m_objectName;
    QString m_qss;
};

#endif // WIDGETNAMEMODEL_H

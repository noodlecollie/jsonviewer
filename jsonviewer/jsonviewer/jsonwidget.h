#ifndef JSONWIDGET_H
#define JSONWIDGET_H

#include <QWidget>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

class QTreeView;
class QVBoxLayout;
class QStandardItemModel;
class QStandardItem;
class QSplitter;
class QTextEdit;

#define STR_OBJ         "{...}"
#define STR_OBJ_EMPTY   "{}"
#define STR_ARR         "[...]"
#define STR_ARR_EMPTY   "[]"
#define STR_KV_DELIMIT  ": "

class JsonWidget : public QWidget
{
    Q_OBJECT
public:
    explicit JsonWidget(QWidget *parent = 0);
    ~JsonWidget();
    
signals:
    
public slots:
    void readFrom(const QJsonDocument &doc);
    
private:
    void init();
    
    static void addJsonArray(const QJsonArray &arr, QStandardItem* item);
    static void addJsonObject(const QJsonObject &obj, QStandardItem* item);
    static QString labelForValue(const QJsonValue &val);
    
    QVBoxLayout*        m_pLayout;
    QTreeView*          m_pView;
    QStandardItemModel* m_pModel;
    QSplitter*          m_pSplitter;
    QTextEdit*          m_pText;
};

#endif // JSONWIDGET_H

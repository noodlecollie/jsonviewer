#include "jsonwidget.h"
#include <QTreeView>
#include <QVBoxLayout>
#include <QStandardItemModel>
#include <QSplitter>
#include <QTextEdit>

JsonWidget::JsonWidget(QWidget *parent) :
    QWidget(parent), m_pLayout(NULL), m_pView(NULL), m_pModel(NULL), m_pSplitter(NULL), m_pText(NULL)
{
    init();
}

JsonWidget::~JsonWidget()
{
    if ( m_pModel )
    {
        delete m_pModel;
        m_pModel = NULL;
    }
}

void JsonWidget::init()
{
    // Set up layout.
    m_pLayout = new QVBoxLayout();
    setLayout(m_pLayout);
    
    // Create splitter.
    m_pSplitter = new QSplitter(Qt::Horizontal);
    
    // Add tree view to splitter.
    m_pView = new QTreeView();
    m_pView->setAnimated(true);
    m_pView->setHeaderHidden(true);
    m_pView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_pSplitter->addWidget(m_pView);
    
    // Add text edit to splitter.
    m_pText = new QTextEdit();
    m_pText->setReadOnly(true);
    m_pText->setWordWrapMode(QTextOption::NoWrap);
    m_pSplitter->addWidget(m_pText);
    
    // Add splitter to layout;
    m_pLayout->addWidget(m_pSplitter);
    
    // Set model for tree view.
    m_pModel = new QStandardItemModel();
    m_pView->setModel(m_pModel);
}

void JsonWidget::readFrom(const QJsonDocument &doc)
{
    if ( !m_pModel ) return;
    
    // Clear the model.
    m_pModel->clear();
    
    // If the document is invalid, exit.
    if ( doc.isNull() || doc.isEmpty() ) return;
    
    // Export to the text window first.
    m_pText->setPlainText(QString(doc.toJson()));
    
    // Do different things depending on the type of the document.
    if ( doc.isArray() )
    {
        addJsonArray(doc.array(), m_pModel->invisibleRootItem());
        return;
    }
    
    if ( doc.isObject() )
    {
        addJsonObject(doc.object(), m_pModel->invisibleRootItem());
        return;
    }
    
    // We shouldn't get here!
    Q_ASSERT(false);
}

QString JsonWidget::labelForValue(const QJsonValue &val)
{
    switch ( val.type() )
    {
        case QJsonValue::Bool:
        {
            return QString(val.toBool() ? "true" : "false");
        }
        
        case QJsonValue::Double:
        {
            return QString::number(val.toDouble());
        }
        
        case QJsonValue::String:
        {
            return val.toString();
        }
        
        case QJsonValue::Null:
        {
            return QString("null");
        }
        
        case QJsonValue::Array:
        {
            return QString(val.toArray().count() < 1 ? STR_ARR_EMPTY : STR_ARR);
        }

        case QJsonValue::Object:
        {
            return QString(val.toObject().count() < 1 ? STR_OBJ_EMPTY : STR_OBJ);
        }
        
        default:
        {
            return QString("Undefined");
        }
    }
}

// Adds all items in arr as children of item.
void JsonWidget::addJsonArray(const QJsonArray &arr, QStandardItem *item)
{
    if ( !item ) return;
    
    // Run through each element in the array and add it as a child of the current item.
    for ( QJsonArray::const_iterator it = arr.constBegin(); it != arr.constEnd(); it++ )
    {
        // If the value is not an array or list, add a new entry containing just the value.
        if ( !((*it).isArray()) && !((*it).isObject()) )
        {
            item->appendRow(new QStandardItem(labelForValue(*it)));
            continue;
        }
        
        // If the value is an array, add a new entry containing brackets and add all children of the array to this entry.
        if ( (*it).isArray() )
        {
            QStandardItem* i = new QStandardItem(labelForValue(*it));
            addJsonArray((*it).toArray(), i);
            item->appendRow(i);
            continue;
        }
        
        // If the value is an object, add a new entry containing brackets and add all children of the object to this entry.
        if ( (*it).isObject() )
        {
            QStandardItem* i = new QStandardItem(labelForValue(*it));
            addJsonObject((*it).toObject(), i);
            item->appendRow(i);
            continue;
        }
    }
}

// Adds all kv pair items in obj as children of item.
void JsonWidget::addJsonObject(const QJsonObject &obj, QStandardItem *item)
{
    if ( !item ) return;
    
    // Run through each key-value pair.
    for (QJsonObject::const_iterator it = obj.constBegin(); it != obj.constEnd(); it++ )
    {
        // If the value is not an array or list, add a new entry which contains the key and the value.
        if ( !it.value().isArray() && !it.value().isObject() )
        {
            item->appendRow(new QStandardItem(it.key() + STR_KV_DELIMIT + labelForValue(it.value())));
            continue;
        }
        
        // If the value is an array, add an entry which contains the key and some brackets, then add all children of the array to this item.
        if ( it.value().isArray() )
        {
            QStandardItem* i = new QStandardItem(it.key() + STR_KV_DELIMIT + labelForValue(it.value()));
            addJsonArray(it.value().toArray(), i);
            item->appendRow(i);
            continue;
        }
        
        // If the value is an object, add an entry which contains the key and some brackets, then add all children of the object to this item.
        if ( it.value().isObject() )
        {
            QStandardItem* i = new QStandardItem(it.key() + STR_KV_DELIMIT + labelForValue(it.value()));
            addJsonObject(it.value().toObject(), i);
            item->appendRow(i);
            continue;
        }
    }
}

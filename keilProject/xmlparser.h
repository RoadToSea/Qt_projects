#ifndef XMLPARSER_H
#define XMLPARSER_H

#include "config.h"
#include <QString>
#include <QDomDocument>
#include <QFileSystemWatcher>


class XmlParser:public QObject
{
    Q_OBJECT
public:
    static XmlParser* getInstance(QString filePath = QString());

    //禁用拷贝构造和赋值构造
    XmlParser(const XmlParser&) = delete;
    XmlParser& operator=(const XmlParser&) = delete;

    ~XmlParser();
    //判断xml文件是否有效
    bool& isValid(void);
    //加载xml文件
    bool loadXml(const QString& path);
    //构造File节点
    QDomElement  constructDom(QString filePath);
    //插入文件
    bool fileInsert(QString tagName,QString path);
    //插入目录
    void dirInsert(QString tagName,QString dirPath);
    //插入组
    void groupInsert(QString tagName);
    //插入Include
    void addInclude(QString path);
    //插入目录
    void dirInsertHelper(QDomElement& files,QString dirPath);
    //删除文件
    void fileDelete(QString fileName);
    void groupDelete(QString groupName);
    void save();
    //获取相对于项目的相对路径
    QString getRelativePath(const QString& filePath);
    //获取项目的路径
    QString getPjPath(void);
    //获取项目的名称
    QString getPjName(void);
    //获取每个Group的名称
    QStringList getGpName(void);
    //获取Group下所有文件的地址
    QStringList getGpFilePath(QString groupName);
    QMap<QString,QVector<keilFile>> getGpFileName(void);
private:
    explicit XmlParser(QString filePath);
    static XmlParser* instance;
    QString m_operator;
    QDomDocument m_dom;
    QFileSystemWatcher* m_watcher;
    bool    m_valid;
private slots:
    void slot_fileChanged(const QString& path);
signals:
    void sign_keilPjChanged(void);
};

#endif // XMLPARSER_H

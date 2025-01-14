#include "xmlparser.h"
#include <QFile>

#include <QDebug>
#include <QDir>
#include <QTextStream>

XmlParser* XmlParser::instance = nullptr;

XmlParser::XmlParser(QString filePath):QObject(nullptr),m_operator(filePath),m_valid(false)
{
    //加载xml;
    loadXml(m_operator);

    //开始监听文件
    m_watcher = new QFileSystemWatcher(this);
    m_watcher->addPath(m_operator);
    connect(m_watcher,&QFileSystemWatcher::fileChanged,this,&XmlParser::slot_fileChanged);

}

XmlParser *XmlParser::getInstance(QString filePath)
{
    if(instance==nullptr)
    {
        if(filePath.isEmpty())
            return nullptr;
        instance = new XmlParser(filePath);
    }
    return instance;
}

XmlParser::~XmlParser()
{
    save();
    delete m_watcher;
}

bool &XmlParser::isValid()
{
    return m_valid;
}

bool XmlParser::loadXml(const QString &path)
{
    //如果给的路径不能打开文件
    QFile file(path);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return false;
    }
    //如果加载xml失败
    if(!m_dom.setContent(&file))
    {
        m_valid = false;
        file.close();
        qDebug()<<"xml加载失败,xml加载路径:"<<m_operator;
        return false;
    }

    //如果加载成功
    file.close();
    m_valid = true;
    return true;
}

QDomElement XmlParser::constructDom(QString filePath)
{
    // 创建 <File> 根节点
    QDomElement fileElement = m_dom.createElement("File");

    // 创建 <FileName> 节点
    QFileInfo fileInfo(filePath);
    QDomElement fileNameElement = m_dom.createElement("FileName");
    QDomText fileNameText = m_dom.createTextNode(fileInfo.fileName());
    fileNameElement.appendChild(fileNameText);

    // 创建 <FileType> 节点
    QString type;
    QDomElement fileTypeElement = m_dom.createElement("FileType");
    QString suffix = fileInfo.suffix();
    if(suffix=="c")
    {
        type = "1";
    }
    else if(suffix == "s")
    {
        type = "2";
    }
    else if(suffix == "h")
    {
        type = "5";
    }
    QDomText fileTypeText = m_dom.createTextNode(type); // 假定 FileType 固定为 1
    fileTypeElement.appendChild(fileTypeText);

    // 创建 <FilePath> 节点
    QDomElement filePathElement = m_dom.createElement("FilePath");
    QDomText filePathText = m_dom.createTextNode(getRelativePath(filePath));
    filePathElement.appendChild(filePathText);

    // 将子节点添加到 <File>
    fileElement.appendChild(fileNameElement);
    fileElement.appendChild(fileTypeElement);
    fileElement.appendChild(filePathElement);

    return fileElement;
}

bool XmlParser::fileInsert(QString tagName,QString path)
{
    //如果xml打开失败,直接返回
    if(!m_valid)
    {
        qDebug()<<"fileInsert: xml未加载";
        return false;
    }

    //定位根节点
    QDomNodeList groupList= m_dom.elementsByTagName("Group");
    if(groupList.isEmpty())
        return false;
    qDebug()<<"找到了Group";

    //遍历寻找和创建标签
    for(int i=0;i<groupList.size();i++)
    {
        QDomElement cur = groupList.at(i).toElement();
        QDomNodeList groupNameList = cur.elementsByTagName("GroupName");
        //找到了对应的节点位置
        if(!groupNameList.isEmpty()&&groupNameList.at(0).toElement().text()==tagName)
        {
            qDebug()<<"找到了GroupName";
            //寻找Files节点,插入到Files下面
            QDomNodeList filesList = cur.elementsByTagName("Files");

            QDomElement files;
            //如果不存在Files节点,就创建一个
            if(filesList.isEmpty())
            {
                qDebug()<<"创建Files";
                QDomElement element = m_dom.createElement("Files");
                cur.appendChild(element);
                files = element;
            }
            else
            {
                files = filesList.at(0).toElement();
            }

            //创建一个File节点并添加进Files中
            QDomElement file = constructDom(path);
            if(!file.isNull())
            {
                files.appendChild(file);
                qDebug()<<"添加成功:"+path;
            }
            //添加成功直接退出
            break;
        }
    }
    return true;

}

void XmlParser::dirInsert(QString tagName,QString dirPath)
{
    //如果xml打开失败,直接返回
    if(!m_valid)
    {
        qDebug()<<"dirInsert: xml未加载";
        return;
    }

    //定位根节点
    QDomNodeList groupList= m_dom.elementsByTagName("Group");
    //没找到直接返回
    if(groupList.isEmpty())
        return;

    //遍历寻找和创建标签
    for(int i=0;i<groupList.size();i++)
    {
        QDomElement cur = groupList.at(0).toElement();
        QDomNodeList groupNameList = cur.elementsByTagName("GroupName");
        //找到了对应的节点位置
        if(!groupNameList.isEmpty()&&groupNameList.at(0).toElement().text()==tagName)
        {
            //寻找Files节点,插入到Files下面
            QDomNodeList filesList = cur.elementsByTagName("Files");

            QDomElement files;
            //如果不存在Files节点,就创建一个
            if(filesList.isEmpty())
            {
                QDomElement element = m_dom.createElement("Files");
                cur.appendChild(element);
                files = element;
            }
            else
            {
                files = filesList.at(0).toElement();
            }
            //递归添加
            dirInsertHelper(files,dirPath);
            //找到了合适的group节点,添加完直接退出循环
            break;
        }
    }
}

void XmlParser::groupInsert(QString tagName)
{

    //如果xml打开失败,直接返回
    if(!m_valid)
    {
        qDebug()<<"fileInsert: xml未加载";
        return;
    }

    QDomNodeList groupList = m_dom.elementsByTagName("Group");
    if(groupList.isEmpty())
        return;

    QDomElement newGroup = m_dom.createElement("Group");
    QDomElement newGroupName = m_dom.createElement("GroupName");
    QDomText newGroupNameText = m_dom.createTextNode(tagName);
    newGroupName.appendChild(newGroupNameText);
    newGroup.appendChild(newGroupName);
    
    QDomElement lastGroup = groupList.at(groupList.size()-1).toElement();
    // 获取最后一个 Group 后的父节点
    QDomNode parentNode = lastGroup.parentNode();
    // 将新节点插入到最后一个 Group 节点后面
    parentNode.insertBefore(newGroup, lastGroup.nextSibling());
}

void XmlParser::addInclude(QString path)
{
    //如果xml打开失败,直接返回
    if(!m_valid)
    {
        qDebug()<<"addInclude: xml未加载";
        return;
    }

    //找到VariousControls节点
    QDomNodeList VariousControlsList = m_dom.elementsByTagName("VariousControls");
    if(VariousControlsList.isEmpty())
        return;
    QDomElement vc = VariousControlsList.at(0).toElement();

    //找到IncludePath节点
    QDomNodeList incList = vc.elementsByTagName("IncludePath");
    //没找到直接返回
    if(incList.isEmpty())
        return;

    //取出IncludePath节点
    QDomElement inc = incList.at(0).toElement();
    QString incPath = inc.text();

    //将路径添加到头文件包含路径中
    path = ";"+getRelativePath(path);
    incPath.append(path);
    qDebug()<<"incPath:"<<incPath;
    //将修改过的路径保存回去
    QDomText incText = inc.firstChild().toText();
    incText.setNodeValue(incPath);

}


void XmlParser::dirInsertHelper(QDomElement& files,QString dirPath)
{
    //如果xml打开失败,直接返回
    if(!m_valid)
    {
        qDebug()<<"fileInsert: xml未加载";
        return;
    }

    // 打开目录
    QDir dir(dirPath);
    if(dir.isEmpty())
        return;

    // 获取目录中的所有条目
    QFileInfoList entryList = dir.entryInfoList(QDir::NoDotAndDotDot | QDir::AllEntries);

    // 遍历目录中的所有条目
    for (const QFileInfo &entry : entryList)
    {
        if (entry.isDir())
        {
            // 如果是子文件夹，递归调用自身
            dirInsertHelper(files,entry.absoluteFilePath());
        }
        else
        {
            QString fullPath = dir.absoluteFilePath(entry.absoluteFilePath()); // 获取完整路径

            // 创建 <File> 节点
            QDomElement file = constructDom(fullPath);
            if (!file.isNull()) {
                files.appendChild(file); // 添加到 <Files>
            } else {
                qDebug() << "Failed to construct <File> for" << fullPath;
            }
        }
    }
}

void XmlParser::fileDelete(QString fileName)
{
    //如果xml打开失败,直接返回
    if(!m_valid)
    {
        qDebug()<<"fileInsert: xml未加载";
        return;
    }

    QDomNodeList list = m_dom.elementsByTagName("File");
    if(list.isEmpty())
        return;
    //逐个查找每个File节点下的FileName
    for(int i=0;i<list.size();i++)
    {
        QDomElement fileElm = list.at(i).toElement();
        QDomNodeList fileNameList = fileElm.elementsByTagName("FileName");
        if(fileNameList.at(0).toElement().text()==fileName)
        {
            //找到当前File节点的父节点Files
            QDomNode filesElm = fileElm.parentNode();
            if(!filesElm.isNull())
            {
                filesElm.removeChild(fileElm);
            }
            break;
        }

    }
}

void XmlParser::groupDelete(QString groupName)
{
    //如果xml打开失败,直接返回
    if(!m_valid)
    {
        qDebug()<<"fileInsert: xml未加载";
        return;
    }

    QDomNodeList groupList = m_dom.elementsByTagName("Group");
    if(groupList.isEmpty())
        return;

    for(int i=0;i<groupList.size();i++)
    {
        QDomElement groupElm = groupList.at(i).toElement();
        QDomNodeList groupNameList = groupElm.elementsByTagName("GroupName");
        QDomElement groupNameElm = groupNameList.at(0).toElement();
        if(groupNameElm.text() == groupName)
        {
            QDomNode groupsNode = groupElm.parentNode();
            groupsNode.removeChild(groupElm);
            break;
        }
    }
}

void XmlParser::save()
{
    m_watcher->removePath(m_operator);
    QFile file(m_operator);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qWarning() << "Failed to open file for writing:" << m_operator;
        return;
    }

    //将xml写入文件流
    QTextStream out(&file);
    out.setEncoding(QStringConverter::Utf8);
    m_dom.save(out,4);

    // 检查写入是否成功
    if (out.status() != QTextStream::Ok)
    {
        qWarning() << "Error while writing XML to file:" << m_operator;
    }
    else
    {
        qDebug() << "XML document saved successfully to:" << m_operator;
    }

    // 关闭文件
    file.close();
    m_watcher->addPath(m_operator);
}

QString XmlParser::getRelativePath(const QString& filePath)
{

    //如果输入的路径已经是相对路径,直接返回输入值
    if(QDir::isRelativePath(filePath))
        return filePath;
    int lastSlashIndex = m_operator.lastIndexOf("/");  //找到最后一个反斜杠的位置
    QString result = m_operator.left(lastSlashIndex ); // 截取到最后一个反斜杠的位置（包括反斜杠）
    QDir baseDir(result);
    return baseDir.relativeFilePath(filePath);

}

QString XmlParser::getPjPath()
{
    return m_operator;
}

QString XmlParser::getPjName(void)
{

    QDomNodeList list = m_dom.elementsByTagName("TargetName");
    if(list.isEmpty())
        return QString();
    return list.at(0).toElement().text();
}

QStringList XmlParser::getGpName(void)
{
    QStringList ret;
    QDomNodeList list = m_dom.elementsByTagName("GroupName");
    if(list.isEmpty())
        return ret;
    for(int i=0;i<list.size();i++)
    {
        ret.append(list.at(i).toElement().text());
    }
    return ret;
}

QStringList XmlParser::getGpFilePath(QString groupName)
{
    QStringList ret;
    //如果xml打开失败,直接返回
    if(!m_valid)
    {
        qDebug()<<"fileInsert: xml未加载";
        return ret;
    }

    QDomNodeList groupList = m_dom.elementsByTagName(groupName);
    if(groupList.isEmpty())
        return ret;

    QDomElement groupElm = groupList.at(0).toElement();
    QDomNodeList filePathsList = groupElm.elementsByTagName("FilePath");
    for(int i=0;i<filePathsList.size();i++)
    {
        ret.append(filePathsList.at(i).toElement().text());
    }
    return ret;
}

QMap<QString, QVector<keilFile> > XmlParser::getGpFileName()
{
    QMap<QString, QVector<keilFile> > ret;
    QString groupName;
    QString fileName;
    QString filePath;
    //1.查找节点Group
    QDomNodeList groupList = m_dom.elementsByTagName("Group");
    for(int groupIndex=0;groupIndex<groupList.size();groupIndex++)
    {
        QDomElement groupElm= groupList.at(groupIndex).toElement();
        //2.查找GroupName
        QDomNodeList groupNameList = groupElm.elementsByTagName("GroupName");
        groupName = groupNameList.at(0).toElement().text();
        //3.查找File
        QDomNodeList filesList = groupElm.elementsByTagName("File");
        for(int fileIndex=0;fileIndex<filesList.size();fileIndex++)
        {
            QDomElement fileElm = filesList.at(fileIndex).toElement();
            fileName = fileElm.firstChildElement("FileName").text();
            filePath = fileElm.firstChildElement("FilePath").text();
            keilFile file;
            file.fileName = fileName;
            file.filePath = filePath;
            ret[groupName].append(file);
        }
    }
    return ret;
}

void XmlParser::slot_fileChanged(const QString &path)
{
    m_dom.clear();
    loadXml(path);
    emit sign_keilPjChanged();
}
















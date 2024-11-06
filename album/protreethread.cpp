#include "protreethread.h"

proTreeThread::proTreeThread(QTreeWidgetItem *root, QString &src_path, QString &dst_path,
                             int &file_count, QObject *parent)
    :QThread(parent),m_root(root),m_srcPath(src_path),m_dstPath(dst_path),fileCount(file_count)
{

}

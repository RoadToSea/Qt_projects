#ifndef CONFIG_H
#define CONFIG_H

#include <QString>






enum TreeItemType{
    file=0,
    group=1,
    project=2
};


enum DeleteType{
    deleteFile=0,
    onlyRemove,
    Cancel
};

typedef struct keilfile{
    QString fileName;
    QString filePath;
} keilFile;







#endif // CONFIG_H

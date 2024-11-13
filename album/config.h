#ifndef CONFIG_H
#define CONFIG_H


enum TreeItemType{
    TreeItemPro = 1, //表示项目的根目录
    TreeItemDir = 2, //表示项目的文件夹
    TreeItemPic = 3, //表示项目的图片
};


#define LEFT_CLICKED        ":/res/icon/left_clicked.svg"
#define LEFT_HOVER          ":/res/icon/left_hover.svg"
#define LEFT_NORMAL         ":/res/icon/left_normal.svg"
#define RIGHT_CLICKED       ":/res/icon/right_clicked.svg"
#define RIGHT_HOVER         ":/res/icon/right_hover.svg"
#define RIGHT_NORMAL        ":/res/icon/right_normal.svg"


#endif // CONFIG_H

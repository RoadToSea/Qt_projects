#ifndef CONFIG_H
#define CONFIG_H


enum TreeItemType{
    TreeItemPro = 1, //表示项目的根目录
    TreeItemDir = 2, //表示项目的文件夹
    TreeItemPic = 3, //表示项目的图片
};

namespace album {
enum buttonState {
    playNormal,   // 播放按钮的正常状态
    playHover,    // 播放按钮的悬停状态
    playPress,    // 播放按钮的按下状态
    stopNormal,   // 停止按钮的正常状态
    stopHover,    // 停止按钮的悬停状态
    stopPress     // 停止按钮的按下状态
};
}

#define PRELISTITEM_SIZE     180
#define PRELISTITEM_INTERVAL    20

#define LEFT_CLICKED        ":/res/icon/left_clicked.svg"
#define LEFT_HOVER          ":/res/icon/left_hover.svg"
#define LEFT_NORMAL         ":/res/icon/left_normal.svg"
#define RIGHT_CLICKED       ":/res/icon/right_clicked.svg"
#define RIGHT_HOVER         ":/res/icon/right_hover.svg"
#define RIGHT_NORMAL        ":/res/icon/right_normal.svg"

// 定义按钮状态对应的路径宏
#define PLAY_NORMAL ":/res/icon/play.png"
#define PLAY_HOVER  ":/res/icon/play_hover.png"
#define PLAY_PRESS  ":/res/icon/play_press.png"
#define STOP_NORMAL ":/res/icon/pause.png"
#define STOP_HOVER  ":/res/icon/pause_hover.png"
#define STOP_PRESS  ":/res/icon/pause_press.png"
#define CLOSE_NORMAL   ":/res/icon/closeshow.png"
#define CLOSE_HOVER    ":/res/icon/closeshow_hover.png"
#define CLOSE_PRESS    ":/res/icon/closeshow_press.png"

#endif // CONFIG_H

#ifndef CONFIG_H
#define CONFIG_H

//曲线图横坐标最大值
#define GRAPH_MAX_X     30


/*
 * 待存入传感器数据个数
 * 三轴重力加速度、温湿度、大气压力、光照传感器数据
*/
#define SENSOR_NUM      8


/*
 * 待存入数据库数据个数
 * 多了个id便于查询
*/
#define DATABASE_NUM    9


//tabelWid
//表头固定高度
#define HEADER_HEIGHT   50
//单元格固定高度
#define CELL_HEIGHT     30


//datastorethread
//默认一次性储存个数(到达这个数量才存入数据库)
#define MIN_STORE       30


//datastorethread




enum Label{
    upStair,
    running,
    walking,
    driving
};


/*更新模式:自动根据输入更新
        100ms更新一次
        200ms更新一次
        300ms更新一次
        400ms更新一次
        500ms更新一次
*/
enum UpdateType{
    AutoUpdate=-1,
    _100msUpdate=100,
    _200msUpdate=200,
    _300msUpdate=300,
    _400msUpdate=400,
    _500msUpdate=500
};




#endif // CONFIG_H

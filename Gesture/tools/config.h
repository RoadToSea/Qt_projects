#ifndef CONFIG_H
#define CONFIG_H




#define GRAPH_MAX_X     30


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

#ifndef MYcustomEvent_H
#define MYCUSTOMEVENT_H

#include <QEvent>

class MycustomEvent : public QEvent
{
public:
    int m_data;
    MycustomEvent(int data):QEvent(customType),m_data(data){};
    static const QEvent::Type customType  ;

};

#endif // MYMycustomEvent_H

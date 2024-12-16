#ifndef PREDICT_H
#define PREDICT_H

#include <QObject>

class predict : public QObject
{
    Q_OBJECT
public:
    explicit predict(QObject *parent = nullptr);
    void callModel(const QString &scriptPath, const QList<float> &ax, const QList<float> &ay, const QList<float> &az);

private:
    QString pythonPath;
signals:
};

#endif // PREDICT_H

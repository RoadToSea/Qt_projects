#ifndef LINEAREA_H
#define LINEAREA_H

#include <QWidget>
#include "codeeditor.h"

class LineArea : public QWidget
{
    Q_OBJECT
public:
    LineArea(CodeEditor *editor) : QWidget(editor), codeEditor(editor)
    {}

    QSize sizeHint() const override
    {
        return QSize(codeEditor->lineNumberAreaWidth(), 0);
    }

protected:
    void paintEvent(QPaintEvent *event) override
    {
        codeEditor->lineNumberAreaPaintEvent(event);
    }

private:
    CodeEditor *codeEditor;

signals:
};

#endif // LINEAREA_H

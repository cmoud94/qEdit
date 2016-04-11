#ifndef LINENUMBERS_H
#define LINENUMBERS_H

#include <QWidget>
#include <QPlainTextEdit>
#include <QTextDocument>
#include <QTextBlock>
#include <QFont>
#include <QtMath>

class Editor;

class LineNumbers : public QWidget
{
    Q_OBJECT
public:
    LineNumbers(Editor *parent, QFont font);
    ~LineNumbers();

    void update();
    void scroll_update(QRect rect, int dy);

    QPlainTextEdit *get_line_widget();

private:
    Editor *parent;

    QPlainTextEdit *line_widget;
    QFont font;

    int get_font_width();
};

#endif // LINENUMBERS_H

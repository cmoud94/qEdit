#include "linenumbers.h"

#include "editor.h"

LineNumbers::LineNumbers(Editor *parent, QFont font)
{
    this->parent = parent;
    this->font = font;

    line_widget = new QPlainTextEdit();
    line_widget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    line_widget->setDisabled(true);
    line_widget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    line_widget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    line_widget->setFont(font);
    line_widget->setStyleSheet("background: #e0e0e0; color: #333");
    line_widget->setFixedWidth(get_font_width());
}

LineNumbers::~LineNumbers()
{

}

void LineNumbers::update()
{
    printf("__FUNCTION__ = %s\n", __FUNCTION__);

    QTextDocument *document = parent->text_edit()->document();
    QTextBlock textBlock = document->firstBlock();

    line_widget->clear();

    int i = 1;
    while(textBlock.isValid()) {
        int text_width = QFontMetrics(font).width(textBlock.text());
        int n_wraps = qCeil(text_width / parent->text_edit()->width());
        QString ln = QString::number(i) + "\n";

        printf("tw: %d\tnw: %d\n", text_width, n_wraps);

        printf("ln: %d\t", i);

        if(ln.length() > line_widget->width()) {
            line_widget->setFixedWidth(ln.length());
        }

        for(int j = 0; j < n_wraps; j++) {
            i++;
            ln.append("\n");
            printf("X\t");
        }
        textBlock = textBlock.next();
        line_widget->appendPlainText(ln);
        printf("\n");
    }
}

void LineNumbers::scroll_update(QRect rect, int dy)
{
    if(dy) {
        line_widget->scroll(0, dy);
    }
//    else { // ?
//        line_widget->update(0, rect.y(), line_widget->width(), rect.height());
//    }
}

QPlainTextEdit *LineNumbers::get_line_widget()
{
    return line_widget;
}

int LineNumbers::get_font_width()
{
    return QFontMetrics(font).maxWidth();
}

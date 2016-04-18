/**
    qEdit - Lightweight IDE
    Copyright (C) 2016  Marek Kouřil

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

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
    update();
    line_widget->moveCursor(QTextCursor::Start);
}

LineNumbers::~LineNumbers()
{

}

QPlainTextEdit *LineNumbers::get_line_widget()
{
    return line_widget;
}

int LineNumbers::get_font_width()
{
    return QFontMetrics(font).averageCharWidth();
}

int LineNumbers::get_max_font_width()
{
    return QFontMetrics(font).maxWidth();
}

void LineNumbers::update()
{
    printf("__FUNCTION__ = %s\n", __FUNCTION__);

    QTextDocument *document = parent->text_edit()->document();
    QTextBlock textBlock = document->firstBlock();

    line_widget->clear();

    int i = 1;
    while(textBlock.isValid()) {
        int text_width = textBlock.text().length() * get_font_width();
        int n_wraps = qCeil(text_width / parent->text_edit()->width());
        QString ln = QString::number(i);

        if(ln.length() * get_max_font_width() > line_widget->width()) {
            line_widget->setFixedWidth(ln.length() * get_max_font_width());
        }

        if(n_wraps > 0) n_wraps++;
        for(int j = 0; j < n_wraps; j++) {
            ln.append("\n");
        }
        textBlock = textBlock.next();
        line_widget->appendPlainText(ln);
        i++;
    }
}

void LineNumbers::scroll_update(QRect rect, int dy)
{
    if(dy) {
        line_widget->scroll(0, dy);
    }
}

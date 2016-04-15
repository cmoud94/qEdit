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

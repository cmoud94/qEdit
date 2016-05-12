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

#include "help.h"
#include "mainwindow.h"

//*****************************************************************************
Help::Help ( MainWindow* parent )
{
    QHBoxLayout* layout = new QHBoxLayout ( );
    QPlainTextEdit* text_widget = new QPlainTextEdit ( this );
    layout->addWidget ( text_widget );
    layout->setContentsMargins ( 0, 0, 0, 0 );
    setLayout ( layout );
    setModal ( true );
    setMinimumWidth ( 600 );
    setMinimumHeight ( 400 );

    QFile f ( ":/files/files/help.txt" );

    if ( !f.open ( QFile::ReadOnly | QFile::Text ) )
    {
        return;
    }

    QTextStream in ( &f );

    QString content = in.readAll ( );

    f.close ( );

    text_widget->insertPlainText ( content );
    text_widget->setReadOnly ( true );
    text_widget->setHorizontalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    text_widget->setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
}

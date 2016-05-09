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

#include "editor.h"
#include "mainwindow.h"

//*****************************************************************************
Editor::Editor ( MainWindow *parent, QString title, QString content, QString path, int document_status )
{
    m_parent = parent;
    m_title = title;
    m_path = path;
    m_document_status = ( document_status_t ) document_status;
    m_default_document_status = ( document_status_t ) document_status;

    m_widget = new QWidget ( );
    m_layout = new QHBoxLayout ( m_widget );
    m_text_widget = new QPlainTextEdit ( m_widget );

    m_layout->addWidget ( m_text_widget );
    m_widget->setLayout ( m_layout );

    m_layout->setContentsMargins ( 0, 0, 0, 0 );

    m_text_widget->setUndoRedoEnabled ( false );
    m_text_widget->setPlainText ( content );
    m_text_widget->setUndoRedoEnabled ( true );

    connect ( m_text_widget, SIGNAL ( textChanged ( ) ), this, SLOT ( document_status_change ( ) ) );
}

//*****************************************************************************
QWidget* Editor::widget ( )
{
    return m_widget;
}

//*****************************************************************************
QPlainTextEdit* Editor::text_edit ( )
{
    return m_text_widget;
}

//*****************************************************************************
QString Editor::title_from_path ( QString path )
{
    QStringList tmp = path.split ( "/" );
    return tmp.at ( tmp.size ( ) - 1 );
}

//*****************************************************************************
Editor::document_status_t Editor::document_status ( )
{
    return m_document_status;
}

//*****************************************************************************
QString Editor::title ( )
{
    return m_title;
}

//*****************************************************************************
void Editor::document_status_change ( )
{
    if ( m_document_status == document_status_t::MODIFIED )
    {
        return;
    }

    m_document_status = document_status_t::MODIFIED;


}

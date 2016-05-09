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
    connect ( m_text_widget, SIGNAL ( modificationChanged ( bool ) ), this, SLOT ( document_status_change ( ) ) );
    connect ( this, SIGNAL ( path_changed ( QString ) ), this, SLOT ( path_change ( QString ) ) );
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
void Editor::set_document_status ( document_status_t new_status )
{
    m_document_status = new_status;
    emit document_status_changed ( m_parent->tab_widget ( )->currentIndex ( ) );
}

//*****************************************************************************
Editor::document_status_t Editor::default_document_status ( )
{
    return m_default_document_status;
}

//*****************************************************************************
void Editor::set_default_document_status ( Editor::document_status_t new_status )
{
    m_default_document_status =  new_status;
}

//*****************************************************************************
QString Editor::title ( )
{
    return m_title;
}

//*****************************************************************************
QString Editor::path ( )
{
    return m_path;
}

//*****************************************************************************
void Editor::set_path ( QString new_path )
{
    m_path = new_path;
    emit path_changed ( new_path );
}

//*****************************************************************************
void Editor::document_status_change ( )
{
    if ( m_text_widget->document ( )->isModified ( ) )
    {
        m_document_status = document_status_t::MODIFIED;
    }
    else
    {
        m_document_status = m_default_document_status;
    }

    int index = m_parent->tab_widget ( )->currentIndex ( );
    emit document_status_changed ( index );
}

//*****************************************************************************
void Editor::path_change ( QString new_path )
{
    m_title = Editor::title_from_path ( new_path );
    m_parent->tab_widget ( )->setTabText ( m_parent->tab_widget ( )->currentIndex ( ), m_title );
}

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

#include "find.h"

//*****************************************************************************
Find::Find ( MainWindow* parent, bool replace )
{
    m_parent = parent;

    m_layout = new QVBoxLayout ( );

    QLabel* lbl_find = new QLabel ( "Find:" );
    m_line_edit_find = new QLineEdit ( this );
    QHBoxLayout* find_layout = new QHBoxLayout ( );
    find_layout->addWidget ( lbl_find );
    find_layout->addWidget ( m_line_edit_find );
    m_layout->addLayout ( find_layout );

    if ( replace )
    {
        QLabel* lbl_replace = new QLabel ( "Replace:" );
        m_line_edit_replace = new QLineEdit ( this );
        QHBoxLayout* replace_layout = new QHBoxLayout ( );
        replace_layout->addWidget ( lbl_replace );
        replace_layout->addWidget ( m_line_edit_replace );
        m_layout->addLayout ( replace_layout );

        lbl_find->setFixedWidth ( 60 );
        lbl_replace->setFixedWidth ( 60 );
    };

    m_match_word = new QCheckBox ( "Match entire word", this );
    m_layout->addWidget ( m_match_word );

    m_ignore_case = new QCheckBox ( "Ignore case", this );
    m_layout->addWidget ( m_ignore_case );

    m_regexp = new QCheckBox ( "Regexp", this );
    m_layout->addWidget ( m_regexp );

    m_backwards = new QCheckBox ( "Search backwards", this );
    m_layout->addWidget ( m_backwards );

    QHBoxLayout* btns_layout = new QHBoxLayout ( );
    m_btn_close = new QPushButton ( "Close", this );
    btns_layout->addWidget ( m_btn_close );

    if ( replace )
    {
        m_btn_replace = new QPushButton ( "Replace", this );
        btns_layout->addWidget ( m_btn_replace );
        m_btn_replace_all = new QPushButton ( "Replace All", this );
        btns_layout->addWidget ( m_btn_replace_all );
    }

    m_btn_find = new QPushButton ( "Find", this );
    btns_layout->addWidget ( m_btn_find );
    m_layout->addLayout ( btns_layout );

    setLayout ( m_layout );
}

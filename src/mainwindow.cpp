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

#include <QMenuBar>
#include <QMenu>
#include <QToolBar>
#include <QTabWidget>
#include <QStatusBar>
#include <QList>
#include <QIcon>
#include <QMessageBox>
#include <QToolButton>

#include <stdio.h>
#include <stdlib.h>

#include "mainwindow.h"

//*****************************************************************************
/**
 * @brief MainWindow::MainWindow
 * @param parent
 */
MainWindow::MainWindow ( QMainWindow* parent )
{
    setWindowTitle ( WIN_TITLE );
    setMinimumWidth ( WIN_MIN_WIDTH );
    setMinimumHeight ( WIN_MIN_HEIGHT );
    setWindowIcon ( QIcon ( ":/icons/qEdit_icon.png" ) );

    menu_bar_init ( );

    tool_bar_init ( );

    tab_widget_init ( );

    setFocus ( );
}

//*****************************************************************************
/**
 * @brief MainWindow::~MainWindow
 */
MainWindow::~MainWindow ( )
{

}

//*****************************************************************************
void MainWindow::window_title_update ( QString new_title )
{
    printf ( "%s\n", __FUNCTION__ );
}

//*****************************************************************************
void MainWindow::file_new ( )
{
    printf ( "%s\n", __FUNCTION__ );
}

//*****************************************************************************
void MainWindow::file_open ( )
{
    printf ( "%s\n", __FUNCTION__ );
}

//*****************************************************************************
void MainWindow::file_save ( )
{
    printf ( "%s\n", __FUNCTION__ );
}

//*****************************************************************************
void MainWindow::file_save_as ( )
{
    printf ( "%s\n", __FUNCTION__ );
}

//*****************************************************************************
void MainWindow::file_close ( )
{
    printf ( "%s\n", __FUNCTION__ );
}

//*****************************************************************************
void MainWindow::file_quit ( )
{
    printf ( "%s\n", __FUNCTION__ );
}

//*****************************************************************************
void MainWindow::edit_undo ( )
{
    printf ( "%s\n", __FUNCTION__ );
}

//*****************************************************************************
void MainWindow::edit_redo ( )
{
    printf ( "%s\n", __FUNCTION__ );
}

//*****************************************************************************
void MainWindow::edit_cut ( )
{
    printf ( "%s\n", __FUNCTION__ );
}

//*****************************************************************************
void MainWindow::edit_copy ( )
{
    printf ( "%s\n", __FUNCTION__ );
}

//*****************************************************************************
void MainWindow::edit_paste ( )
{
    printf ( "%s\n", __FUNCTION__ );
}

//*****************************************************************************
void MainWindow::edit_preferences ( )
{
    printf ( "%s\n", __FUNCTION__ );
}

//*****************************************************************************
void MainWindow::search_find ( )
{
    printf ( "%s\n", __FUNCTION__ );
}

//*****************************************************************************
void MainWindow::search_replace ( )
{
    printf ( "%s\n", __FUNCTION__ );
}

//*****************************************************************************
void MainWindow::help ( )
{
    printf ( "%s\n", __FUNCTION__ );
}

//*****************************************************************************
void MainWindow::help_about ( )
{
    printf ( "%s\n", __FUNCTION__ );
}

//*****************************************************************************
void MainWindow::tab_close_shortcut ( )
{
    printf ( "%s\n", __FUNCTION__ );
}

//*****************************************************************************
/**
 * @brief MainWindow::menu_bar_init
 */
void MainWindow::menu_bar_init ( )
{
    m_menu_bar = new QMenuBar ( this );

    // File menu
    m_menu_file = new QMenu ( "&File", m_menu_bar );
    m_menu_file->addAction ( "&New", this, SLOT ( file_new ( ) ), QKeySequence ( "Ctrl+N" ) );
    m_menu_file->addAction ( "&Open", this, SLOT ( file_open ( ) ), QKeySequence ( "Ctrl+O" ) );
    m_menu_file->addSeparator ( );
    m_menu_file->addAction ( "&Save", this, SLOT ( file_save ( ) ), QKeySequence ( "Ctrl+S" ) );
    m_menu_file->addAction ( "Save as...", this, SLOT ( file_save_as ( ) ), QKeySequence ( "Ctrl+Shift+S" ) );
    m_menu_file->addSeparator ( );
    m_menu_file->addAction ( "&Close", this, SLOT ( file_close ( ) ), QKeySequence ( "Ctrl+W" ) );
    m_menu_file->addSeparator ( );
    m_menu_file->addAction ( "&Quit", this, SLOT ( file_quit ( ) ), QKeySequence ( "Ctrl+Q" ) );
    m_menu_bar->addMenu ( m_menu_file );

    // Edit menu
    m_menu_edit = new QMenu ( "&Edit", m_menu_bar );
    m_menu_edit->addAction ( "Undo", this, SLOT ( edit_undo ( ) ), QKeySequence ( "Ctrl+Z" ) );
    m_menu_edit->addAction ( "Redo", this, SLOT ( edit_redo ( ) ), QKeySequence ( "Ctrl+Shift+Z" ) );
    m_menu_edit->addSeparator ( );
    m_menu_edit->addAction ( "Cut", this, SLOT ( edit_cut ( ) ), QKeySequence ( "Ctrl+X" ) );
    m_menu_edit->addAction ( "Copy", this, SLOT ( edit_copy ( ) ), QKeySequence ( "Ctrl+C" ) );
    m_menu_edit->addAction ( "Paste", this, SLOT ( edit_paste ( ) ), QKeySequence ( "Ctrl+V" ) );
    m_menu_edit->addSeparator ( );
    m_menu_edit->addAction ( "Preferences", this, SLOT ( edit_preferences ( ) ), QKeySequence ( "Ctrl+." ) );
    m_menu_bar->addMenu ( m_menu_edit );

    // Search menu
    m_menu_search = new QMenu ( "&Search", m_menu_bar );
    m_menu_search->addAction ( "&Find", this, SLOT ( search_find ( ) ), QKeySequence ( "Ctrl+F" ) );
    m_menu_search->addAction ( "&Replace", this, SLOT ( search_replace ( ) ), QKeySequence ( "Ctrl+R" ) );
    m_menu_bar->addMenu ( m_menu_search );

    // Help menu
    m_menu_help = new QMenu ( "&Help", m_menu_bar );
    m_menu_help->addAction ( "Help", this, SLOT ( help ( ) ), QKeySequence ( "F1" ) );
    m_menu_help->addAction ( "&About", this, SLOT ( help_about ( ) ), QKeySequence ( "" ) );
    m_menu_bar->addMenu ( m_menu_help );

    setMenuBar ( m_menu_bar );
}

//*****************************************************************************
/**
 * @brief MainWindow::tool_bar_init
 */
void MainWindow::tool_bar_init ( )
{
    m_tool_bar_icons = new QList< QIcon >( );
    m_tool_bar = new QToolBar ( this );
    m_tool_bar->setMovable ( false );

    QToolButton* btn;

    // New file
    btn = new QToolButton ( m_tool_bar );
    m_tool_bar_icons->append ( QIcon ( ":/24x24/icons/24x24/document-new-8.png" ) );
    btn->setIcon ( m_tool_bar_icons->at ( m_tool_bar_icons->size ( ) - 1 ) );
    btn->setToolTip ( "New file" );
    m_tool_bar->addWidget ( btn );
    connect ( btn, SIGNAL ( clicked ( bool ) ), this, SLOT ( file_new ( ) ) );

    // Open file
    btn = new QToolButton ( m_tool_bar );
    m_tool_bar_icons->append ( QIcon ( ":/24x24/icons/24x24/document-open-7.png" ) );
    btn->setIcon ( m_tool_bar_icons->at ( m_tool_bar_icons->size ( ) - 1 ) );
    btn->setToolTip ( "Open file" );
    m_tool_bar->addWidget ( btn );
    connect ( btn, SIGNAL ( clicked ( bool ) ), this, SLOT ( file_open ( ) ) );

    // Save file
    btn = new QToolButton ( m_tool_bar );
    m_tool_bar_icons->append ( QIcon ( ":/24x24/icons/24x24/document-save-2.png" ) );
    btn->setIcon ( m_tool_bar_icons->at ( m_tool_bar_icons->size ( ) - 1 ) );
    btn->setToolTip ( "Save file" );
    m_tool_bar->addWidget ( btn );
    connect ( btn, SIGNAL ( clicked ( bool ) ), this, SLOT ( file_save ( ) ) );

    // Separator **************************************************************
    m_tool_bar->addSeparator ( );

    // Undo
    btn = new QToolButton ( m_tool_bar );
    m_tool_bar_icons->append ( QIcon ( ":/24x24/icons/24x24/edit-undo-5.png" ) );
    btn->setIcon ( m_tool_bar_icons->at ( m_tool_bar_icons->size ( ) - 1 ) );
    btn->setToolTip ( "Undo" );
    m_tool_bar->addWidget ( btn );
    connect ( btn, SIGNAL ( clicked ( bool ) ), this, SLOT ( edit_undo ( ) ) );

    // Redo
    btn = new QToolButton ( m_tool_bar );
    m_tool_bar_icons->append ( QIcon ( ":/24x24/icons/24x24/edit-redo-5.png" ) );
    btn->setIcon ( m_tool_bar_icons->at ( m_tool_bar_icons->size ( ) - 1 ) );
    btn->setToolTip ( "Redo" );
    m_tool_bar->addWidget ( btn );
    connect ( btn, SIGNAL ( clicked ( bool ) ), this, SLOT ( edit_redo ( ) ) );

    // Separator **************************************************************
    m_tool_bar->addSeparator ( );

    // Cut
    btn = new QToolButton ( m_tool_bar );
    m_tool_bar_icons->append ( QIcon ( ":/24x24/icons/24x24/edit-cut.png" ) );
    btn->setIcon ( m_tool_bar_icons->at ( m_tool_bar_icons->size ( ) - 1 ) );
    btn->setToolTip ( "Cut" );
    m_tool_bar->addWidget ( btn );
    connect ( btn, SIGNAL ( clicked ( bool ) ), this, SLOT ( edit_cut ( ) ) );

    // Copy
    btn = new QToolButton ( m_tool_bar );
    m_tool_bar_icons->append ( QIcon ( ":/24x24/icons/24x24/edit-copy.png" ) );
    btn->setIcon ( m_tool_bar_icons->at ( m_tool_bar_icons->size ( ) - 1 ) );
    btn->setToolTip ( "Copy" );
    m_tool_bar->addWidget ( btn );
    connect ( btn, SIGNAL ( clicked ( bool ) ), this, SLOT ( edit_copy ( ) ) );

    // Paste
    btn = new QToolButton ( m_tool_bar );
    m_tool_bar_icons->append ( QIcon ( ":/24x24/icons/24x24/edit-paste-2.png" ) );
    btn->setIcon ( m_tool_bar_icons->at ( m_tool_bar_icons->size ( ) - 1 ) );
    btn->setToolTip ( "Paste" );
    m_tool_bar->addWidget ( btn );
    connect ( btn, SIGNAL ( clicked ( bool ) ), this, SLOT ( edit_paste ( ) ) );

    // Separator **************************************************************
    m_tool_bar->addSeparator ( );

    // Find
    btn = new QToolButton ( m_tool_bar );
    m_tool_bar_icons->append ( QIcon ( ":/24x24/icons/24x24/edit-find-5.png" ) );
    btn->setIcon ( m_tool_bar_icons->at ( m_tool_bar_icons->size ( ) - 1 ) );
    btn->setToolTip ( "Find" );
    m_tool_bar->addWidget ( btn );
    connect ( btn, SIGNAL ( clicked ( bool ) ), this, SLOT ( search_find ( ) ) );

    // Replace
    btn = new QToolButton ( m_tool_bar );
    m_tool_bar_icons->append ( QIcon ( ":/24x24/icons/24x24/edit-find-and-replace-2.png" ) );
    btn->setIcon ( m_tool_bar_icons->at ( m_tool_bar_icons->size ( ) - 1 ) );
    btn->setToolTip ( "Find & Replace" );
    m_tool_bar->addWidget ( btn );
    connect ( btn, SIGNAL ( clicked ( bool ) ), this, SLOT ( search_replace ( ) ) );

    addToolBar ( m_tool_bar );
}

//*****************************************************************************
void MainWindow::tab_widget_init ( )
{
    m_tab_widget = new QTabWidget ( this );
    m_tab_widget->setTabBarAutoHide ( true );
    m_tab_widget->setTabsClosable ( true );

    setCentralWidget ( m_tab_widget );
}

//*****************************************************************************
void MainWindow::status_bar_init ( )
{
    printf ( "%s\n", __FUNCTION__ );
}

//*****************************************************************************
void MainWindow::tab_new ( )
{
    printf ( "%s\n", __FUNCTION__ );
}

//*****************************************************************************
/**
 * @brief MainWindow::dialog_show
 * @param text
 * @param secondary_text
 * @param icon
 * @param buttons
 * @param default_button
 * @return
 */
int MainWindow::dialog_show ( QString text, QString secondary_text, int icon, int buttons, int default_button )
{
    QMessageBox msg;
    msg.setText ( text );
    msg.setInformativeText ( secondary_text );
    msg.setIcon ( ( QMessageBox::Icon ) icon );
    msg.setStandardButtons ( ( QMessageBox::StandardButtons ) buttons );
    msg.setDefaultButton ( ( QMessageBox::StandardButton ) default_button );
    return msg.exec ( );
}

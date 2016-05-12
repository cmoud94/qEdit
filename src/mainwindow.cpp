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

#include "mainwindow.h"
#include "editor.h"
#include "preferences.h"
#include "help.h"
#include "find.h"

//*****************************************************************************
MainWindow::MainWindow ( QMainWindow* parent )
{
    m_editors = new QList< Editor* >( );

    load_supported_file_types ( );

    setWindowTitle ( WIN_TITLE );
    setMinimumWidth ( WIN_MIN_WIDTH );
    setMinimumHeight ( WIN_MIN_HEIGHT );
    setWindowIcon ( QIcon ( ":/icons/qEdit_icon.png" ) );

    menu_bar_init ( );
    tool_bar_init ( );
    tab_widget_init ( );
//	status_bar_init ( );

    Preferences* p = new Preferences ( this );
    p->get_config ( &m_config_keys, &m_config );
    delete p;

    QSettings settings ( "cmoud94", "qEdit" );

    settings.beginGroup ( "Window" );

    setGeometry ( settings.value ( "geometry", QVariant ( QRect ( 10, 10, WIN_MIN_WIDTH, WIN_MIN_HEIGHT ) ) ).toRect ( ) );

    settings.endGroup ( );

    setFocus ( );

    toggle_actions_enabled ( false );
}

//*****************************************************************************
MainWindow::~MainWindow ( )
{
    delete m_tool_bar_icons;
    delete m_editors;
}

//*****************************************************************************
QTabWidget* MainWindow::tab_widget ( )
{
    return m_tab_widget;
}

//*****************************************************************************
QList< Editor* >* MainWindow::editors ( )
{
    return m_editors;
}

//*****************************************************************************
void MainWindow::window_title_update ( QString new_title )
{
    if ( new_title == "" )
    {
        m_window_title = WIN_TITLE;
    }
    else
    {
        m_window_title = new_title + " - " + WIN_TITLE;
    }

    setWindowTitle ( m_window_title );
}

//*****************************************************************************
void MainWindow::document_status_changed ( int index )
{
    QString new_title = "";

    if ( m_editors->at ( index )->document_status ( ) == Editor::document_status_t::MODIFIED )
    {
        new_title = "* " + m_editors->at ( index )->title ( );
    }
    else
    {
        new_title = m_editors->at ( index )->title ( );
    }

    m_tab_widget->setTabText ( index, new_title );
    emit tab_changed ( index );
}

//*****************************************************************************
void MainWindow::file_new ( )
{
    tab_new ( "Untitled", "", "", Editor::document_status_t::NEW );
}

//*****************************************************************************
void MainWindow::file_open ( )
{
    QFileDialog d;
    QString path = d.getOpenFileName ( this,
                                       "Open file",
                                       QDir::homePath ( ),
                                       m_file_type_filter,
                                       &m_default_file_type );

    if ( path == "" )
    {
        return;
    }

    QFile f ( path );

    if ( !f.open ( QFile::ReadOnly | QFile::Text ) )
    {
        dialog_show ( "Can't open file.",
                      "Can't open file [" + path + "].",
                      QMessageBox::Critical,
                      QMessageBox::Ok,
                      QMessageBox::Ok );
        return;
    }

    QString title = Editor::title_from_path ( path );
    QTextStream in ( &f );

    QString content = in.readAll ( );

    f.close ( );

    tab_new ( title, content, path, Editor::document_status_t::SAVED );
}

//*****************************************************************************
void MainWindow::file_save ( )
{
    int index = m_tab_widget->currentIndex ( );

    if ( index == -1 )
    {
        return;
    }

    Editor* editor = m_editors->at ( index );

    if ( editor->path ( ) != "" &&
         editor->default_document_status ( ) == Editor::document_status_t::SAVED )
    {
        file_write ( editor->path ( ), editor );
    }
    else if ( editor->path ( ) == "" &&
              editor->default_document_status ( ) == Editor::document_status_t::NEW )
    {
        QFileDialog d;
        QString path = d.getSaveFileName ( this,
                                           "Save file",
                                           QDir::homePath ( ),
                                           m_file_type_filter,
                                           &m_default_file_type );

        if ( path != "" )
        {
            file_write ( path, editor );
            editor->set_path ( path );
            editor->set_default_document_status ( Editor::document_status_t::SAVED );
        }
    }
}

//*****************************************************************************
void MainWindow::file_save_as ( )
{
    int index = m_tab_widget->currentIndex ( );

    if ( index == -1 )
    {
        return;
    }

    Editor* editor = m_editors->at ( index );

    QFileDialog d;
    QString path = d.getSaveFileName ( this,
                                       "Save file as ...",
                                       QDir::homePath ( ),
                                       m_file_type_filter,
                                       &m_default_file_type );

    if ( path != "" )
    {
        file_write ( path, editor );
        editor->set_path ( path );
        editor->set_default_document_status ( Editor::document_status_t::SAVED );
    }
}

//*****************************************************************************
void MainWindow::file_close ( )
{
    int index = m_tab_widget->currentIndex ( );

    if ( index == -1 )
    {
        return;
    }

    Editor* editor = m_editors->at ( index );

    if ( editor->document_status ( ) != Editor::document_status_t::SAVED &&
         editor->document_status ( ) != editor->default_document_status ( ) )
    {
        int r = dialog_show ( "File not saved.",
                              "Do you want to save file [" + editor->title ( ) + "] before closing?",
                              QMessageBox::Question,
                              QMessageBox::Discard | QMessageBox::Cancel | QMessageBox::Yes,
                              QMessageBox::Yes );

        switch ( r )
        {
            case QMessageBox::Cancel:
                return;
                break;
            case QMessageBox::Yes:
                file_save ( );
                break;
            default:
                break;
        }
    }

    tab_close ( index );
}

//*****************************************************************************
void MainWindow::file_quit ( )
{
    for ( int i = m_editors->size ( ) - 1; i >= 0; i-- )
    {
        m_tab_widget->setCurrentIndex ( i );
        file_close ( );
    }

    QSettings settings ( "cmoud94", "qEdit" );

    settings.beginGroup ( "Window" );

    settings.setValue ( "geometry", QVariant ( geometry ( ) ) );

    settings.endGroup ( );

    close ( );
}

//*****************************************************************************
void MainWindow::edit_undo ( )
{
    int index = m_tab_widget->currentIndex ( );

    if ( index == -1 )
    {
        return;
    }

    m_editors->at ( index )->text_edit ( )->undo ( );
}

//*****************************************************************************
void MainWindow::edit_redo ( )
{
    int index = m_tab_widget->currentIndex ( );

    if ( index == -1 )
    {
        return;
    }

    m_editors->at ( index )->text_edit ( )->redo ( );
}

//*****************************************************************************
void MainWindow::edit_cut ( )
{
    int index = m_tab_widget->currentIndex ( );

    if ( index == -1 )
    {
        return;
    }

    m_editors->at ( index )->text_edit ( )->cut ( );
}

//*****************************************************************************
void MainWindow::edit_copy ( )
{
    int index = m_tab_widget->currentIndex ( );

    if ( index == -1 )
    {
        return;
    }

    m_editors->at ( index )->text_edit ( )->copy ( );
}

//*****************************************************************************
void MainWindow::edit_paste ( )
{
    int index = m_tab_widget->currentIndex ( );

    if ( index == -1 )
    {
        return;
    }

    m_editors->at ( index )->text_edit ( )->paste ( );
}

//*****************************************************************************
void MainWindow::edit_preferences ( )
{
    Preferences* p = new Preferences ( this );

    connect ( p,
              SIGNAL ( config_changed ( QList< QVariant >* ) ),
              this,
              SLOT ( config_changed ( QList< QVariant >* ) )
              );

    p->exec ( );

    delete p;
}

//*****************************************************************************
void MainWindow::search_find ( )
{
    Find f ( this, false );
    f.exec ( );
}

//*****************************************************************************
void MainWindow::search_replace ( )
{
    Find f ( this, true );
    f.exec ( );
}

//*****************************************************************************
void MainWindow::help ( )
{
    Help h ( this );
    h.exec ( );
}

//*****************************************************************************
void MainWindow::help_about ( )
{
    dialog_show ( "qEdit Lightweight IDE\nCreator: Marek Kouřil (KOU0120)",
                  "URO 2016",
                  QMessageBox::Information,
                  QMessageBox::Ok,
                  QMessageBox::Ok );
}

//*****************************************************************************
void MainWindow::tab_close ( int index )
{
    m_tab_widget->removeTab ( index );
    m_editors->removeAt ( index );

    if ( m_tab_widget->currentIndex ( ) == -1 )
    {
        toggle_actions_enabled ( false );
    }
}

//*****************************************************************************
void MainWindow::tab_changed ( int index )
{
    if ( index == -1 )
    {
        window_title_update ( "" );
        return;
    }

    window_title_update ( m_tab_widget->tabText ( index ) );
}

//*****************************************************************************
void MainWindow::config_changed ( QList< QVariant >* new_config )
{
    m_config = * new_config;

    if ( m_editors == NULL )
    {
        return;
    }

    for ( int i = 0; i < m_editors->size ( ); i++ )
    {
        m_editors->at ( i )->config_set ( new_config );
    }
}

//*****************************************************************************
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
    m_tab_widget->setTabsClosable ( true );

    setCentralWidget ( m_tab_widget );

    connect ( m_tab_widget, SIGNAL ( tabCloseRequested ( int ) ), this, SLOT ( file_close ( ) ) );
    connect ( m_tab_widget, SIGNAL ( currentChanged ( int ) ), this, SLOT ( tab_changed ( int ) ) );
}

//*****************************************************************************
void MainWindow::status_bar_init ( )
{

}

//*****************************************************************************
void MainWindow::tab_new ( QString title, QString content, QString path, int document_status )
{
    if ( m_tab_widget->currentIndex ( ) == -1 )
    {
        toggle_actions_enabled ( true );
    }

    Editor* editor = new Editor ( this, title, content, path, document_status, &m_config, &m_config_keys );
    m_editors->append ( editor );
    int r = m_tab_widget->addTab ( editor->widget ( ), QIcon ( ":/icons/document-new-7.png" ), title );
    m_tab_widget->setCurrentIndex ( r );
    editor->text_edit ( )->setFocus ( );

    connect ( editor, &Editor::document_status_changed, this, &MainWindow::document_status_changed );
}

//*****************************************************************************
int MainWindow::dialog_show ( QString text, QString secondary_text, int icon, int buttons, int default_button )
{
    QMessageBox* msg = new QMessageBox ( this );
    msg->setText ( text );
    msg->setInformativeText ( secondary_text );
    msg->setIcon ( ( QMessageBox::Icon ) icon );
    msg->setStandardButtons ( ( QMessageBox::StandardButtons ) buttons );
    msg->setDefaultButton ( ( QMessageBox::StandardButton ) default_button );
    return msg->exec ( );
}

//*****************************************************************************
void MainWindow::load_supported_file_types ( )
{
    QFile f ( ":/files/files/supported_file_extensions.txt" );

    if ( !f.open ( QFile::ReadOnly | QFile::Text ) )
    {
        dialog_show ( "File save",
                      "Can't load supported file types.",
                      QMessageBox::Critical,
                      QMessageBox::Ok,
                      QMessageBox::Ok );
        return;
    }

    QString content = "";

    while ( !f.atEnd ( ) )
    {
        QString line = f.readLine ( );
        QString name = line.split ( "=" ).at ( 0 );
        QString type = line.split ( "=" ).at ( 1 ).split ( "\n" ).at ( 0 );
        content += name + "(*." + type + ");;";
    }

    f.close ( );

    m_file_type_filter = content;
    m_default_file_type = content.split ( ";;" ).at ( 0 );
}

//*****************************************************************************
void MainWindow::file_write ( QString path, Editor* editor )
{
    QFile f ( path );

    if ( !f.open ( QFile::WriteOnly | QFile::Text ) )
    {
        dialog_show ( "Can't save file.",
                      "Can't save file [" + path + "].",
                      QMessageBox::Critical,
                      QMessageBox::Ok,
                      QMessageBox::Ok );
        return;
    }

    f.reset ( );

    QTextStream out ( &f );

    out << editor->text_edit ( )->document ( )->toPlainText ( );

    f.close ( );

    editor->set_document_status ( Editor::document_status_t::SAVED );
}

void MainWindow::closeEvent ( QCloseEvent* event )
{
    file_quit ( );
    event->accept ( );
}

//*****************************************************************************
void MainWindow::toggle_actions_enabled ( bool val )
{
    // Tool bar actions
    QList< QAction* > actions = m_tool_bar->actions ( );

    for ( int i = 2; i < actions.size ( ); i++ )
    {
        actions.at ( i )->setEnabled ( val );
    }

    // File menu
    actions = m_menu_file->actions ( );

    for ( int i = 2; i < actions.size ( ) - 1; i++ )
    {
        actions.at ( i )->setEnabled ( val );
    }

    // Edit menu
    actions = m_menu_edit->actions ( );

    for ( int i = 0; i < actions.size ( ) - 1; i++ )
    {
        actions.at ( i )->setEnabled ( val );
    }

    // Search menu
    actions = m_menu_search->actions ( );

    for ( int i = 0; i < actions.size ( ); i++ )
    {
        actions.at ( i )->setEnabled ( val );
    }
}

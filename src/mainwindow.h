#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QMenuBar;
class QToolBar;
class QTabWidget;
class QStatusBar;
class QIcon;
class QMessageBox;
class Editor;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow ( QMainWindow* parent = 0 );

    ~MainWindow ( );

public slots:
    void window_title_update ( QString new_title );

private slots:
    void file_new ( );

    void file_open ( );

    void file_save ( );

    void file_save_as ( );

    void file_close ( );

    void file_quit ( );

    void edit_undo ( );

    void edit_redo ( );

    void edit_cut ( );

    void edit_copy ( );

    void edit_paste ( );

    void edit_preferences ( );

    void search_find ( );

    void search_replace ( );

    void help ( );

    void help_about ( );

    void tab_close ( int index );

private:
    const QString WIN_TITLE = "qEdit";

    const int WIN_MIN_WIDTH = 400;

    const int WIN_MIN_HEIGHT = 300;

    QString m_window_title;

    QMenuBar* m_menu_bar;

    QMenu* m_menu_file;

    QMenu* m_menu_edit;

    QMenu* m_menu_search;

    QMenu* m_menu_help;

    QToolBar* m_tool_bar;

    QList< QIcon >* m_tool_bar_icons;

    QTabWidget* m_tab_widget;

    QList< Editor* >* m_editors;

    QStatusBar* m_status_bar;

    void menu_bar_init ( );

    void tool_bar_init ( );

    void tab_widget_init ( );

    void status_bar_init ( );

    void tab_new ( QString title, QString content, QString path );

    int dialog_show ( QString text, QString secondary_text, int icon, int buttons, int default_button );
};

#endif // MAINWINDOW_H

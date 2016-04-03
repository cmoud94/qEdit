#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QMainWindow>
#include <QKeySequence>
#include <QIcon>
#include <QList>
#include <QMenuBar>
#include <QMenu>
#include <QToolBar>
#include <QToolButton>
#include <QTabWidget>
#include <QStatusBar>

#include "editor.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QMainWindow *parent = 0);
    ~MainWindow();

private:
    void init_menu_bar();
    void init_tool_bar();
    void init_tabs();
    void init_status_bar();
    void tab_new(QString title);

    QString window_title;

    QMenuBar *menu_bar;
    QMenu *menu_file;
    QMenu *menu_edit;
    QMenu *menu_search;
    QMenu *menu_help;

    QToolBar *tool_bar;
    QList<QIcon> *tool_bar_icons;

    QTabWidget *tab_widget;

    QStatusBar *status_bar;

private slots:
    // File slots
    void new_file();
    void open_file();
    void save_file();
    void save_file_as();
    void quit();

    // Edit slots
    void undo();
    void redo();
    void cut();
    void copy();
    void paste();
    void preferences();

    // Search slots
    void find();
    void replace();

    // Help slots
    void help();
    void about();

    // Other slots
    void tab_close(int index);
};

#endif // MAINWINDOW_H
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QWidget>
#include <QMainWindow>
#include <QKeySequence>
#include <QIcon>
#include <QList>
#include <QMenuBar>
#include <QMenu>
#include <QToolBar>
#include <QToolButton>
#include <QTabWidget>
#include <QTextEdit>
#include <QStatusBar>

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
};

#endif // MAINWINDOW_H

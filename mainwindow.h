#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QWidget>
#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QMainWindow *parent = 0);
    ~MainWindow();

private:
    void init_menu_bar();

    QString window_title;

    QMenuBar *menu_bar;
    QMenu *menu_file;
    QMenu *menu_edit;
    QMenu *menu_search;
    QMenu *menu_help;
};

#endif // MAINWINDOW_H

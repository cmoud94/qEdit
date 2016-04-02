#include "mainwindow.h"

MainWindow::MainWindow(QMainWindow *parent) : QMainWindow(parent)
{
    window_title = "qEdit";

    setWindowTitle(window_title);
    setMinimumSize(500, 300);

    init_menu_bar();
}

MainWindow::~MainWindow()
{

}

void MainWindow::init_menu_bar()
{
    menu_bar = new QMenuBar(0);

    menu_file = menu_bar->addMenu(QString("&File"));
    menu_edit = menu_bar->addMenu(QString("&Edit"));
    menu_search = menu_bar->addMenu(QString("&Search"));
    menu_help = menu_bar->addMenu(QString("&Help"));

    setMenuBar(menu_bar);
}

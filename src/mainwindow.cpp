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
    menu_bar = new QMenuBar(this);

    menu_file = new QMenu(tr("&File"), menu_bar);
    menu_file->addAction(tr("&Quit"), this, SLOT(close()), QKeySequence(tr("Ctrl+Q")));
    menu_bar->addMenu(menu_file);

    setMenuBar(menu_bar);
}

#include "mainwindow.h"

MainWindow::MainWindow(QMainWindow *parent) : QMainWindow(parent)
{
    // Window config
    window_title = "qEdit";
    setWindowTitle(window_title);
    setMinimumSize(500, 300);

    // Init
    init_menu_bar();
    init_tool_bar();
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

void MainWindow::init_tool_bar()
{
    tool_bar = new QToolBar(this);
    tool_bar_icons = new QList<QIcon>();

    // New file button
    QToolButton *btn_new_file = new QToolButton(tool_bar);
    tool_bar_icons->append(QIcon(tr(":/24x24/icons/24x24/document-new-8.png")));
    btn_new_file->setIcon(tool_bar_icons->at(tool_bar_icons->size() - 1));
    tool_bar->addWidget(btn_new_file);

    // Open file button
    QToolButton *btn_open_file = new QToolButton(tool_bar);
    tool_bar_icons->append(QIcon(tr(":/24x24/icons/24x24/document-open-7.png")));
    btn_open_file->setIcon(tool_bar_icons->at(tool_bar_icons->size() - 1));
    tool_bar->addWidget(btn_open_file);

    addToolBar(tool_bar);
}

void MainWindow::init_tabs()
{

}

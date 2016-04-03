#include "mainwindow.h"

MainWindow::MainWindow(QMainWindow *parent) : QMainWindow(parent)
{
    // Window config
    window_title = "qEdit";
    setWindowTitle(window_title);
    setMinimumSize(500, 300);
    setWindowIcon(QIcon(tr(":/icons/qEdit_icon.png")));

    // Init
    init_menu_bar();
    init_tool_bar();
    init_tabs();
    init_status_bar();

    setCentralWidget(tab_widget);
}

MainWindow::~MainWindow()
{
    delete tool_bar_icons;
}

void MainWindow::init_menu_bar()
{
    menu_bar = new QMenuBar(this);

    // File menu
    menu_file = new QMenu(tr("&File"), menu_bar);
    menu_file->addAction(tr("&New"), this, SLOT(new_file()), QKeySequence(tr("Ctrl+N")));
    menu_file->addAction(tr("&Open"), this, SLOT(open_file()), QKeySequence(tr("Ctrl+O")));
    menu_file->addAction(tr("&Save"), this, SLOT(save_file()), QKeySequence(tr("Ctrl+S")));
    menu_file->addAction(tr("Save as..."), this, SLOT(save_file_as()), QKeySequence(tr("Ctrl+Shift+S")));
    menu_file->addSeparator();
    menu_file->addAction(tr("&Quit"), this, SLOT(quit()), QKeySequence(tr("Ctrl+Q")));
    menu_bar->addMenu(menu_file);

    // Edit menu
    menu_edit = new QMenu(tr("&Edit"), menu_bar);
    menu_edit->addAction(tr("Undo"), this, SLOT(undo()), QKeySequence(tr("Ctrl+Z")));
    menu_edit->addAction(tr("Redo"), this, SLOT(redo()), QKeySequence(tr("Ctrl+Shift+Z")));
    menu_edit->addSeparator();
    menu_edit->addAction(tr("Cut"), this, SLOT(cut()), QKeySequence(tr("Ctrl+X")));
    menu_edit->addAction(tr("Copy"), this, SLOT(copy()), QKeySequence(tr("Ctrl+C")));
    menu_edit->addAction(tr("Paste"), this, SLOT(paste()), QKeySequence(tr("Ctrl+v")));
    menu_edit->addSeparator();
    menu_edit->addAction(tr("Preferences"), this, SLOT(preferences()), QKeySequence(tr("Ctrl+.")));
    menu_bar->addMenu(menu_edit);

    // Search menu
    menu_search = new QMenu(tr("&Search"), menu_bar);
    menu_search->addAction(tr("&Find"), this, SLOT(find()), QKeySequence(tr("Ctrl+F")));
    menu_search->addAction(tr("&Replace"), this, SLOT(replace()), QKeySequence(tr("Ctrl+R")));
    menu_bar->addMenu(menu_search);

    // Help menu
    menu_help = new QMenu(tr("&Help"), menu_bar);
    menu_help->addAction(tr("&Help"), this, SLOT(help()), QKeySequence(tr("F1")));
    menu_help->addAction(tr("&About"), this, SLOT(about()));
    menu_bar->addMenu(menu_help);

    setMenuBar(menu_bar);
}

void MainWindow::init_tool_bar()
{
    tool_bar_icons = new QList<QIcon>();
    tool_bar = new QToolBar(this);
    tool_bar->setMovable(false);

    // New file button
    QToolButton *btn_new_file = new QToolButton(tool_bar);
    tool_bar_icons->append(QIcon(tr(":/24x24/icons/24x24/document-new-8.png")));
    btn_new_file->setIcon(tool_bar_icons->at(tool_bar_icons->size() - 1));
    tool_bar->addWidget(btn_new_file);
    connect(btn_new_file, SIGNAL(clicked(bool)), this, SLOT(new_file()));

    // Open file button
    QToolButton *btn_open_file = new QToolButton(tool_bar);
    tool_bar_icons->append(QIcon(tr(":/24x24/icons/24x24/document-open-7.png")));
    btn_open_file->setIcon(tool_bar_icons->at(tool_bar_icons->size() - 1));
    tool_bar->addWidget(btn_open_file);
    connect(btn_open_file, SIGNAL(clicked(bool)), this, SLOT(open_file()));

    // Save file button
    QToolButton *btn_save_file = new QToolButton(tool_bar);
    tool_bar_icons->append(QIcon(tr(":/24x24/icons/24x24/document-save-2.png")));
    btn_save_file->setIcon(tool_bar_icons->at(tool_bar_icons->size() - 1));
    tool_bar->addWidget(btn_save_file);
    connect(btn_save_file, SIGNAL(clicked(bool)), this, SLOT(save_file()));

    // Separator
    tool_bar->addSeparator();

    // Undo button
    QToolButton *btn_undo = new QToolButton(tool_bar);
    tool_bar_icons->append(QIcon(tr(":/24x24/icons/24x24/edit-undo-5.png")));
    btn_undo->setIcon(tool_bar_icons->at(tool_bar_icons->size() - 1));
    tool_bar->addWidget(btn_undo);
    connect(btn_undo, SIGNAL(clicked(bool)), this, SLOT(undo()));

    // Redo button
    QToolButton *btn_redo = new QToolButton(tool_bar);
    tool_bar_icons->append(QIcon(tr(":/24x24/icons/24x24/edit-redo-5.png")));
    btn_redo->setIcon(tool_bar_icons->at(tool_bar_icons->size() - 1));
    tool_bar->addWidget(btn_redo);
    connect(btn_redo, SIGNAL(clicked(bool)), this, SLOT(redo()));

    // Separator
    tool_bar->addSeparator();

    // Cut button
    QToolButton *btn_cut = new QToolButton(tool_bar);
    tool_bar_icons->append(QIcon(tr(":/24x24/icons/24x24/edit-cut.png")));
    btn_cut->setIcon(tool_bar_icons->at(tool_bar_icons->size() - 1));
    tool_bar->addWidget(btn_cut);
    connect(btn_cut, SIGNAL(clicked(bool)), this, SLOT(cut()));

    // Copy button
    QToolButton *btn_copy = new QToolButton(tool_bar);
    tool_bar_icons->append(QIcon(tr(":/24x24/icons/24x24/edit-copy.png")));
    btn_copy->setIcon(tool_bar_icons->at(tool_bar_icons->size() - 1));
    tool_bar->addWidget(btn_copy);
    connect(btn_copy, SIGNAL(clicked(bool)), this, SLOT(copy()));

    // Paste button
    QToolButton *btn_paste = new QToolButton(tool_bar);
    tool_bar_icons->append(QIcon(tr(":/24x24/icons/24x24/edit-paste-2.png")));
    btn_paste->setIcon(tool_bar_icons->at(tool_bar_icons->size() - 1));
    tool_bar->addWidget(btn_paste);
    connect(btn_paste, SIGNAL(clicked(bool)), this, SLOT(paste()));

    // Separator
    tool_bar->addSeparator();

    // Find button
    QToolButton *btn_find = new QToolButton(tool_bar);
    tool_bar_icons->append(QIcon(tr(":/24x24/icons/24x24/edit-find-5.png")));
    btn_find->setIcon(tool_bar_icons->at(tool_bar_icons->size() - 1));
    tool_bar->addWidget(btn_find);
    connect(btn_find, SIGNAL(clicked(bool)), this, SLOT(find()));

    // Replace button
    QToolButton *btn_replace = new QToolButton(tool_bar);
    tool_bar_icons->append(QIcon(tr(":/24x24/icons/24x24/edit-find-and-replace-2.png")));
    btn_replace->setIcon(tool_bar_icons->at(tool_bar_icons->size() - 1));
    tool_bar->addWidget(btn_replace);
    connect(btn_replace, SIGNAL(clicked(bool)), this, SLOT(replace()));

    addToolBar(tool_bar);
}

void MainWindow::init_tabs()
{
    tab_widget = new QTabWidget(this);
    tab_widget->setTabsClosable(true);
    //tab_widget->setMovable(true);

    QToolButton *btn = new QToolButton(tab_widget);
    btn->setText(tr("Testing..."));
    btn->setToolButtonStyle(Qt::ToolButtonTextOnly);
    tab_widget->addTab(btn, tr("Test..."));

    QToolButton *btn2 = new QToolButton(tab_widget);
    btn2->setText(tr("Testing 2..."));
    btn2->setToolButtonStyle(Qt::ToolButtonTextOnly);
    tab_widget->addTab(btn2, tr("Test 2..."));

    connect(tab_widget, SIGNAL(tabCloseRequested(int)), this, SLOT(tab_close(int)));
}

void MainWindow::init_status_bar()
{

}

void MainWindow::tab_new(QString title)
{
    Editor *editor = new Editor(tab_widget, title);
    tab_widget->addTab(editor->get_text_edit(), title);
    tab_widget->setCurrentIndex(tab_widget->count() - 1);
}

void MainWindow::new_file()
{
    printf("__FUNCTION__ = %s\n", __FUNCTION__);
}

void MainWindow::open_file()
{
    printf("__FUNCTION__ = %s\n", __FUNCTION__);
}

void MainWindow::save_file()
{
    printf("__FUNCTION__ = %s\n", __FUNCTION__);
}

void MainWindow::save_file_as()
{
    printf("__FUNCTION__ = %s\n", __FUNCTION__);
}

void MainWindow::quit()
{
    printf("__FUNCTION__ = %s\n", __FUNCTION__);
    close();
}

void MainWindow::undo()
{
    printf("__FUNCTION__ = %s\n", __FUNCTION__);
}

void MainWindow::redo()
{
    printf("__FUNCTION__ = %s\n", __FUNCTION__);
}

void MainWindow::cut()
{
    printf("__FUNCTION__ = %s\n", __FUNCTION__);
}

void MainWindow::copy()
{
    printf("__FUNCTION__ = %s\n", __FUNCTION__);
}

void MainWindow::paste()
{
    printf("__FUNCTION__ = %s\n", __FUNCTION__);
}

void MainWindow::preferences()
{
    printf("__FUNCTION__ = %s\n", __FUNCTION__);
}

void MainWindow::find()
{
    printf("__FUNCTION__ = %s\n", __FUNCTION__);
}

void MainWindow::replace()
{
    printf("__FUNCTION__ = %s\n", __FUNCTION__);
}

void MainWindow::help()
{
    printf("__FUNCTION__ = %s\n", __FUNCTION__);
}

void MainWindow::about()
{
    printf("__FUNCTION__ = %s\n", __FUNCTION__);
}

void MainWindow::tab_close(int index)
{
    QString tab_text = tab_widget->tabText(index);
    tab_widget->removeTab(index);
}

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

MainWindow::MainWindow(QMainWindow *parent) : QMainWindow(parent)
{
    editors = new QList<Editor*>();

    window_title = "qEdit";
    setWindowTitle(window_title);
    setMinimumSize(500, 300);
    setWindowIcon(QIcon(tr(":/icons/qEdit_icon.png")));

    new QShortcut(QKeySequence(tr("Ctrl+W")), this, SLOT(tab_close_shortcut()));
    new QShortcut(QKeySequence(tr("Ctrl+D")), this, SLOT(print_debug_info()));

    // Init
    init_menu_bar();
    init_tool_bar();
    init_tabs();
    init_status_bar();

    supported_file_types = load_supported_file_types();

    setCentralWidget(tab_widget);
    setFocus();
}

MainWindow::~MainWindow()
{
    delete tool_bar_icons;
    delete editors;
}

void MainWindow::update_title(QString str)
{
    if(str == 0) {
        if(tab_widget->currentIndex() != -1) {
            QString title = editors->at(tab_widget->currentIndex())->document_name();
            setWindowTitle(window_title + " - " + title);
        } else {
            setWindowTitle(window_title);
        }
    } else {
        setWindowTitle(window_title + " - " + str);
    }
}

QTabWidget *MainWindow::get_tab_widget()
{
    return tab_widget;
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
    btn_new_file->setToolTip("New file");
    tool_bar->addWidget(btn_new_file);
    connect(btn_new_file, SIGNAL(clicked(bool)), this, SLOT(new_file()));

    // Open file button
    QToolButton *btn_open_file = new QToolButton(tool_bar);
    tool_bar_icons->append(QIcon(tr(":/24x24/icons/24x24/document-open-7.png")));
    btn_open_file->setIcon(tool_bar_icons->at(tool_bar_icons->size() - 1));
    btn_open_file->setToolTip("Open file");
    tool_bar->addWidget(btn_open_file);
    connect(btn_open_file, SIGNAL(clicked(bool)), this, SLOT(open_file()));

    // Save file button
    QToolButton *btn_save_file = new QToolButton(tool_bar);
    tool_bar_icons->append(QIcon(tr(":/24x24/icons/24x24/document-save-2.png")));
    btn_save_file->setIcon(tool_bar_icons->at(tool_bar_icons->size() - 1));
    btn_save_file->setToolTip("Save file");
    tool_bar->addWidget(btn_save_file);
    connect(btn_save_file, SIGNAL(clicked(bool)), this, SLOT(save_file()));

    // Separator
    tool_bar->addSeparator();

    // Undo button
    QToolButton *btn_undo = new QToolButton(tool_bar);
    tool_bar_icons->append(QIcon(tr(":/24x24/icons/24x24/edit-undo-5.png")));
    btn_undo->setIcon(tool_bar_icons->at(tool_bar_icons->size() - 1));
    btn_undo->setToolTip("Undo");
    tool_bar->addWidget(btn_undo);
    connect(btn_undo, SIGNAL(clicked(bool)), this, SLOT(undo()));

    // Redo button
    QToolButton *btn_redo = new QToolButton(tool_bar);
    tool_bar_icons->append(QIcon(tr(":/24x24/icons/24x24/edit-redo-5.png")));
    btn_redo->setIcon(tool_bar_icons->at(tool_bar_icons->size() - 1));
    btn_redo->setToolTip("Redo");
    tool_bar->addWidget(btn_redo);
    connect(btn_redo, SIGNAL(clicked(bool)), this, SLOT(redo()));

    // Separator
    tool_bar->addSeparator();

    // Cut button
    QToolButton *btn_cut = new QToolButton(tool_bar);
    tool_bar_icons->append(QIcon(tr(":/24x24/icons/24x24/edit-cut.png")));
    btn_cut->setIcon(tool_bar_icons->at(tool_bar_icons->size() - 1));
    btn_cut->setToolTip("Cut");
    tool_bar->addWidget(btn_cut);
    connect(btn_cut, SIGNAL(clicked(bool)), this, SLOT(cut()));

    // Copy button
    QToolButton *btn_copy = new QToolButton(tool_bar);
    tool_bar_icons->append(QIcon(tr(":/24x24/icons/24x24/edit-copy.png")));
    btn_copy->setIcon(tool_bar_icons->at(tool_bar_icons->size() - 1));
    btn_copy->setToolTip("Copy");
    tool_bar->addWidget(btn_copy);
    connect(btn_copy, SIGNAL(clicked(bool)), this, SLOT(copy()));

    // Paste button
    QToolButton *btn_paste = new QToolButton(tool_bar);
    tool_bar_icons->append(QIcon(tr(":/24x24/icons/24x24/edit-paste-2.png")));
    btn_paste->setIcon(tool_bar_icons->at(tool_bar_icons->size() - 1));
    btn_paste->setToolTip("Paste");
    tool_bar->addWidget(btn_paste);
    connect(btn_paste, SIGNAL(clicked(bool)), this, SLOT(paste()));

    // Separator
    tool_bar->addSeparator();

    // Find button
    QToolButton *btn_find = new QToolButton(tool_bar);
    tool_bar_icons->append(QIcon(tr(":/24x24/icons/24x24/edit-find-5.png")));
    btn_find->setIcon(tool_bar_icons->at(tool_bar_icons->size() - 1));
    btn_find->setToolTip("Find");
    tool_bar->addWidget(btn_find);
    connect(btn_find, SIGNAL(clicked(bool)), this, SLOT(find()));

    // Replace button
    QToolButton *btn_replace = new QToolButton(tool_bar);
    tool_bar_icons->append(QIcon(tr(":/24x24/icons/24x24/edit-find-and-replace-2.png")));
    btn_replace->setIcon(tool_bar_icons->at(tool_bar_icons->size() - 1));
    btn_replace->setToolTip("Find & Replace");
    tool_bar->addWidget(btn_replace);
    connect(btn_replace, SIGNAL(clicked(bool)), this, SLOT(replace()));

    addToolBar(tool_bar);
}

void MainWindow::init_tabs()
{
    tab_widget = new QTabWidget(this);
    tab_widget->setTabsClosable(true);
    //tab_widget->setMovable(true);

    connect(tab_widget, SIGNAL(tabCloseRequested(int)), this, SLOT(tab_close(int)));
}

void MainWindow::init_status_bar()
{

}

QString MainWindow::load_supported_file_types()
{
    QFile file(tr(":/files/files/supported_file_extensions.txt"));
    QString content = "";

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        printf("\tCan't open supported file types file.\n");
        return "";
    }

    while(!file.atEnd()) {
        QString line = file.readLine();
        content += line;
    }

    file.close();

    QString ret = "";
    QStringList lines = content.split('\n');
    for(int i = 0; i < lines.size(); i++) {
        QStringList line_data = lines.at(i).split('=');
        if(line_data.size() == 2) {
            ret += line_data.at(0) + " (*." + line_data.at(1) + ");;";
        }
    }

    return ret;
}

void MainWindow::tab_new(QString path, QString name, QString content, document_status_t status)
{
    printf("__FUNCTION__ = %s\n", __FUNCTION__);

    Editor *editor = new Editor(this, path, name, content, status);
    editors->append(editor);

    tab_widget->setCurrentIndex(tab_widget->addTab(editor->container(), name));
    editor->text_edit()->setFocus();
}

void MainWindow::new_file()
{
    printf("__FUNCTION__ = %s\n", __FUNCTION__);

    tab_new("", "Document", "", document_status_t::DOCUMENT_NEW);
}

void MainWindow::open_file()
{
    printf("__FUNCTION__ = %s\n", __FUNCTION__);

    QString path = QDir::homePath() + "/Desktop";
    QString active_filter = supported_file_types.split(";;").at(0);
    QString file_path = QFileDialog::getOpenFileName(this, tr("Open file"), path, supported_file_types, &active_filter);

    if(file_path == "") {
        printf("\tNo file was selected or 'Cancel' pressed.\n");
        return;
    }

    QStringList path_strips = file_path.split("/");
    QString file_name = path_strips.at(path_strips.size() - 1);
    QFile file(file_path);
    QString content = "";

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        printf("\tIOError while opening file [%s]\n", file_path.toLatin1().data());
        return;
    }

    while(!file.atEnd()) {
        QString line = file.readLine();
        content += line;
    }

    file.close();

    printf("\tfile_path = %s\n", file_path.toLatin1().data());
    printf("\tfile_name = %s\n", file_name.toLatin1().data());
    //printf("\tcontent = %s\n", content.toLatin1().data());

    tab_new(file_path, file_name, content, document_status_t::DOCUMENT_SAVED);
}

void MainWindow::save_file()
{
    printf("__FUNCTION__ = %s\n", __FUNCTION__);

    int current_tab_index = tab_widget->currentIndex();

    if(current_tab_index == -1) {
        printf("\tNothing to save here...\n");
        return;
    }

    Editor *editor = editors->at(current_tab_index);

    if(editor->document_status() == document_status_t::DOCUMENT_MODIFIED) {
        if(editor->default_document_status() == document_status_t::DOCUMENT_SAVED) {
            QFile file(editor->document_path());

            if(!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                printf("\tIOError while opening file [%s]\n", editor->document_path().toLatin1().data());
                return;
            }

            file.write(editor->text_edit()->document()->toPlainText().toUtf8());

            file.close();

            editor->setDocument_status(document_status_t::DOCUMENT_SAVED);
            editor->setdefault_document_status(document_status_t::DOCUMENT_SAVED);
        } else if(editor->default_document_status() == document_status_t::DOCUMENT_NEW) {
            QString path = QDir::homePath() + "/Desktop";
            QString active_filter = supported_file_types.split(";;")[0];
            QString file_path = QFileDialog::getSaveFileName(this, tr("Save file"), path, supported_file_types, &active_filter);

            if(file_path == "") {
                printf("\tNo file selected or 'Cancel' pressed.");
                return;
            }

            QStringList path_strips = file_path.split("/");
            QString file_name = path_strips.at(path_strips.size() - 1);
            QFile file(file_path);

            if(!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                printf("\tIOError while opening file [%s]\n", editor->document_path().toLatin1().data());
                return;
            }

            file.write(editor->text_edit()->document()->toPlainText().toUtf8());

            file.close();

            editor->setDocument_name(file_name);
            editor->setDocument_path(file_path);
            editor->setDocument_status(document_status_t::DOCUMENT_SAVED);
            editor->setdefault_document_status(document_status_t::DOCUMENT_SAVED);
        }

        printf("\tFile sucessfully saved!\n");
    } else {
        printf("\t%s is not modified.\n", editor->document_name().toLatin1().data());
        return;
    }
}

void MainWindow::save_file_as()
{
    printf("__FUNCTION__ = %s\n", __FUNCTION__);
}

void MainWindow::quit()
{
    printf("__FUNCTION__ = %s\n", __FUNCTION__);

    for(int i = editors->size() - 1; i >= 0; i--) {
        Editor *editor = editors->at(i);

        if(editor->document_status() == document_status_t::DOCUMENT_MODIFIED) {
            QMessageBox *msg = new QMessageBox(this);
            msg->setWindowModality(Qt::WindowModal);
            msg->setIcon(QMessageBox::Question);
            msg->setText("Document \"" + editor->document_name() + "\" is modified.");
            msg->setInformativeText("Do you want to save it?");
            msg->setStandardButtons(QMessageBox::Save | QMessageBox::Discard);
            msg->setDefaultButton(QMessageBox::Save);
            int ret = msg->exec();
            switch(ret) {
                case QMessageBox::Save:
                    tab_widget->setCurrentIndex(i);
                    save_file();
                    tab_close(i);
                    break;
                default:
                    break;
            }
        }
    }

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
    printf("__FUNCTION__ = %s\n", __FUNCTION__);

    if(index == -1) {
        return;
    }

    tab_widget->setCurrentIndex(index);

    Editor *editor = editors->at(index);

    if(editor->document_status() == document_status_t::DOCUMENT_MODIFIED) {
        QMessageBox *msg = new QMessageBox(this);
        msg->setWindowModality(Qt::WindowModal);
        msg->setIcon(QMessageBox::Question);
        msg->setText("Document \"" + editor->document_name() + "\" is modified.");
        msg->setInformativeText("Do you want to save it?");
        msg->setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msg->setDefaultButton(QMessageBox::Save);
        int ret = msg->exec();
        switch(ret) {
            case QMessageBox::Save:
                save_file();
                break;
            case QMessageBox::Cancel:
                return;
                break;
            default:
                break;
        }
    }

    editors->removeAt(index);
    tab_widget->removeTab(index);

    delete editor;
    update_title();
}

void MainWindow::tab_close_shortcut()
{
    tab_close(tab_widget->currentIndex());
}

void MainWindow::print_debug_info()
{
    int index = tab_widget->currentIndex();
    if(index == -1) {
        return;
    }

    Editor *editor = editors->at(index);

    QString status;

    switch(editor->document_status()) {
        case document_status_t::DOCUMENT_NEW:
            status = "New";
            break;
        case document_status_t::DOCUMENT_SAVED:
            status = "Saved";
            break;
        case document_status_t::DOCUMENT_MODIFIED:
            status = "Modified";
            break;
        default:
            status = "Unknown";
            break;
    }

    printf("*** DEBUG ***\n");
    printf("\tDocument name: %s\n", editor->document_name().toLatin1().data());
    printf("\tDocument path: %s\n", editor->document_path().toLatin1().data());
    printf("\tDocument status: %s\n", status.toLatin1().data());
}

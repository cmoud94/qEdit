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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QToolBar>
#include <QToolButton>
#include <QTabWidget>
#include <QStatusBar>
#include <QKeySequence>
#include <QIcon>
#include <QList>
#include <QFileDialog>
#include <QFile>
#include <QShortcut>
#include <QMessageBox>

class Editor;
enum class document_status_t;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QMainWindow *parent = 0);
    ~MainWindow();

    void update_title(QString str = "");

    QTabWidget *get_tab_widget();

private:
    void init_menu_bar();
    void init_tool_bar();
    void init_tabs();
    void init_status_bar();
    QString load_supported_file_types();
    void tab_new(QString path, QString name, QString content, document_status_t status);

    QString window_title;
    QString supported_file_types;

    QMenuBar *menu_bar;
    QMenu *menu_file;
    QMenu *menu_edit;
    QMenu *menu_search;
    QMenu *menu_help;

    QToolBar *tool_bar;
    QList<QIcon> *tool_bar_icons;

    QTabWidget *tab_widget;
    QList<Editor*> *editors;

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
    void tab_close_shortcut();
    void print_debug_info();
};

#endif // MAINWINDOW_H

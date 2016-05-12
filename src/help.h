#ifndef HELP_H
#define HELP_H

#include <QDialog>
#include <QPlainTextEdit>
#include <QHBoxLayout>
#include <QFile>
#include <QTextStream>

class MainWindow;

class Help : public QDialog
{
    Q_OBJECT

public:
    Help ( MainWindow* parent );
};

#endif // HELP_H

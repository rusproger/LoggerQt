#ifndef CLOGGER_H
#define CLOGGER_H

#include <QDate>
#include <QTime>
#include <QFile>
#include <QString>
#include <QWidget>
#include <QTextEdit>


class Logger : QObject
{
public:
    static Logger *Instance()
    {
        static Logger logger;
        return &logger;
    }
    static void setTextEdit(QTextEdit *ptr);
    static void journal(const QString& text,
               const QColor& color = QColor(Qt::black));
private:
    QTextEdit *tedit;
    QDate date;
    bool isopen;
    QFile logFile;

    Logger();
    ~Logger();
};

#endif // CLOGGER_H

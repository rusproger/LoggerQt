#include <QDir>
#include <QTextStream>
#include "logger.h"

// Имя директории для файлов с логами
#define LOG_DIR  "log"
// Формат имени файла с логами
#define FORMAT_LOG_FILENAME  "yyyyMMdd"
// Формат вывода даты в строку регистрации
#define FORMAT_LINE_DATE  "dd.MM.yyyy"
// Формат вывода времени в строку регистрации
#define FORMAT_LINE_TIME  "hh:mm:ss"



Logger::Logger()
    : tedit(NULL)
{
    QDir dir(QDir::currentPath());

    if(!dir.exists(LOG_DIR))
        dir.mkdir(LOG_DIR);

    isopen = false;
    date = QDate::currentDate();
}

Logger::~Logger()
{
    if (isopen)
    {
        logFile.close();
    }
}

void Logger::setTextEdit(QTextEdit *ptr)
{
    Logger *logger = Logger::Instance();
    logger->tedit = dynamic_cast<QTextEdit*>(ptr);
}

// Печать текста (в окно журнала и в файл)
void Logger::journal(const QString& text, const QColor& color)
{
    Logger *logger = Logger::Instance();
    QString head, tail;

    // Проверка наступления нового дня или попытка открыть новый файл
    if(logger->date != QDate::currentDate() || !logger->isopen)
    {
        // Закрываем ранее открытый файл
        if (logger->isopen)
        {
            logger->logFile.close();
        }
        // Формируем новую дату
        logger->date = QDate::currentDate();
        logger->logFile.setFileName(QString("%1/%2.txt").arg(LOG_DIR).arg(logger->date.toString(FORMAT_LOG_FILENAME)));
        logger->isopen = logger->logFile.open(QIODevice::Append | QIODevice::Text);
    }

    // Формирование строки регистрации
    head = QString("%1 %2 => ").arg(QDate::currentDate().toString(FORMAT_LINE_DATE)).arg(QTime::currentTime().toString(FORMAT_LINE_TIME));
    tail = text;
    tail.append('\n');

    // Запись в QTextEdit
    if (logger->tedit)
    {
        logger->tedit->moveCursor(QTextCursor::End);
        logger->tedit->setTextColor(Qt::black);
        logger->tedit->insertPlainText(head);

        logger->tedit->moveCursor(QTextCursor::End);
        logger->tedit->setTextColor(color);
        logger->tedit->insertPlainText(tail);
    }

    if(logger->isopen)
    {
        // Печать в файл
        QTextStream out(&logger->logFile);
        out << head << tail;
    }

}


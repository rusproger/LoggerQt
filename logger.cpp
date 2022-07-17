#include <QDir>
#include <QTextStream>
#include "logger.h"

// ��� ���������� ��� ������ � ������
#define LOG_DIR  "log"
// ������ ����� ����� � ������
#define FORMAT_LOG_FILENAME  "yyyyMMdd"
// ������ ������ ���� � ������ �����������
#define FORMAT_LINE_DATE  "dd.MM.yyyy"
// ������ ������ ������� � ������ �����������
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

// ������ ������ (� ���� ������� � � ����)
void Logger::journal(const QString& text, const QColor& color)
{
    Logger *logger = Logger::Instance();
    QString head, tail;

    // �������� ����������� ������ ��� ��� ������� ������� ����� ����
    if(logger->date != QDate::currentDate() || !logger->isopen)
    {
        // ��������� ����� �������� ����
        if (logger->isopen)
        {
            logger->logFile.close();
        }
        // ��������� ����� ����
        logger->date = QDate::currentDate();
        logger->logFile.setFileName(QString("%1/%2.txt").arg(LOG_DIR).arg(logger->date.toString(FORMAT_LOG_FILENAME)));
        logger->isopen = logger->logFile.open(QIODevice::Append | QIODevice::Text);
    }

    // ������������ ������ �����������
    head = QString("%1 %2 => ").arg(QDate::currentDate().toString(FORMAT_LINE_DATE)).arg(QTime::currentTime().toString(FORMAT_LINE_TIME));
    tail = text;
    tail.append('\n');

    // ������ � QTextEdit
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
        // ������ � ����
        QTextStream out(&logger->logFile);
        out << head << tail;
    }

}


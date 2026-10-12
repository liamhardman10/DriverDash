#include "AppController.h"

#include <QCoreApplication>

AppController::AppController(QObject *parent)
    : QObject(parent)
{
}

void AppController::setCurrentPage(const QString &page)
{
    if (m_currentPage == page)
        return;

    m_currentPage = page;
    emit currentPageChanged();
}

void AppController::quit()
{
    QCoreApplication::quit();
}
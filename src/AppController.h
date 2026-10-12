#pragma once

#include <QObject>
#include <QString>

class AppController : public QObject
{
    Q_OBJECT

    // Exposed to QML as `app.currentPage`
    Q_PROPERTY(QString currentPage READ currentPage WRITE setCurrentPage NOTIFY currentPageChanged)

    // Exposed as `app.greeting` — trivial proof the bridge works
    Q_PROPERTY(QString greeting READ greeting CONSTANT)

public:
    explicit AppController(QObject *parent = nullptr);

    QString currentPage() const { return m_currentPage; }
    void setCurrentPage(const QString &page);

    QString greeting() const { return QStringLiteral("Hello from C++"); }

    // Exposed as `app.quit()` — callable from QML
    Q_INVOKABLE void quit();

signals:
    void currentPageChanged();

private:
    QString m_currentPage = QStringLiteral("home");
};
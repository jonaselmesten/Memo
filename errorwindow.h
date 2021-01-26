#ifndef ERRORWINDOW_H
#define ERRORWINDOW_H

#include <QDialog>
#include <QString>

namespace Ui {
class ErrorWindow;
}

/**
 * @brief The ErrorWindow class
 * Simple class that represents an error-window that displays a message.
 */
class ErrorWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ErrorWindow(QWidget *parent = nullptr);

    ~ErrorWindow();

    void setMessage(QString message);

private:
    Ui::ErrorWindow *ui;
};

#endif // ERRORWINDOW_H

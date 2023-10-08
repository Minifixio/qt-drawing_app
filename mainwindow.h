#ifndef MAIN_H
#define MAIN_H

#include <QMainWindow>
#include <ToolPanel.h>

QT_BEGIN_NAMESPACE
namespace Ui { class Main; }
QT_END_NAMESPACE

class Main : public QMainWindow
{
    Q_OBJECT

public:
    Main(QWidget *parent = nullptr);
    ~Main();

private:
    Ui::Main *ui;
    ToolPanel* toolPanel;
};
#endif // MAIN_H

#ifndef MAIN_H
#define MAIN_H

#include <DrawingPanel.h>
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

private slots:
    void on_shapeSelectEllipseBtn_clicked();
    void on_shapeSelectRectangleBtn_clicked();
    void on_shapeSelectLineBtn_clicked();
    void on_shapeSelectTriangleBtn_clicked();

    void on_chooseColorBtn_clicked();

    void on_eraseAllBtn_clicked();
    void on_undoBtn_clicked();

    void on_lineStyleSolidRadioBtn_toggled(bool t);
    void on_lineStyleDashedRadioBtn_toggled(bool t);
    void on_lineThicknessSlider_valueChanged(int v);

    void on_fillColorBtn_clicked();

    void on_moveBtn_clicked();
    void on_resizeBtn_clicked();

    void chooseColor();
};
#endif // MAIN_H

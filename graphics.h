#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <QDialog>
#include <QtCharts> // Añadimos la librería

namespace Ui {
class graphics;
}

class graphics : public QDialog
{
    Q_OBJECT

public:
    explicit graphics(QWidget *parent = nullptr);
    ~graphics();

    // Función pública para que MainWindow le envíe los datos
    void updateGraph(double time, double angle, double setpoint, double pwm);

private:
    Ui::graphics *ui;

    // Elementos de la gráfica
    QChart *chart;
    QLineSeries *angleSeries;
    QLineSeries *setpointSeries;
    QValueAxis *axisX;
    QValueAxis *axisY;
};

#endif // GRAPHICS_H

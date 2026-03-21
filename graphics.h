#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <QDialog>
#include <QtCharts>

namespace Ui {
class graphics;
}

class graphics : public QDialog
{
    Q_OBJECT

public:
    explicit graphics(QWidget *parent = nullptr);
    ~graphics();

    // Nueva función que recibe todos los datos
    void updateTelemetry(double time, double angle, double setpoint, int lineError, int turnPwm, int sumIR, int state);

private:
    Ui::graphics *ui;

    // Elementos de la Gráfica 1 (Equilibrio)
    QChart *chartBalance;
    QLineSeries *angleSeries;
    QLineSeries *setpointSeries;
    QValueAxis *axisX_bal;
    QValueAxis *axisY_bal;

    // Elementos de la Gráfica 2 (Seguidor)
    QChart *chartLine;
    QLineSeries *errorSeries;
    QLineSeries *pwmSeries;
    QValueAxis *axisX_line;
    QValueAxis *axisY_line;
};

#endif // GRAPHICS_H

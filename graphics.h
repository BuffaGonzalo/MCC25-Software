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

    void updatePID(double time, double p, double i, double d, double out);

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

    // Variables para la Gráfica 3 (Términos del PID)
    QLineSeries *pSeries;
    QLineSeries *iSeries;
    QLineSeries *dSeries;
    QLineSeries *outSeries;

    QChart *chartPID;
    QValueAxis *axisX_pid;
    QValueAxis *axisY_pid;

    double currentYMin = -10.0; // Valor inicial razonable
    double currentYMax = 10.0;
};

#endif // GRAPHICS_H

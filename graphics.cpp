#include "graphics.h"
#include "ui_graphics.h"

graphics::graphics(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::graphics)
{
    ui->setupUi(this);

    // --- GRÁFICA 1: EQUILIBRIO ---
    angleSeries = new QLineSeries();
    angleSeries->setName("Ángulo Actual (°)");
    setpointSeries = new QLineSeries();
    setpointSeries->setName("Setpoint (°)");

    chartBalance = new QChart();
    chartBalance->addSeries(angleSeries);
    chartBalance->addSeries(setpointSeries);
    chartBalance->setTitle("Dinámica de Equilibrio (Cabeceo)");
    chartBalance->layout()->setContentsMargins(0,0,0,0);

    axisX_bal = new QValueAxis(); axisX_bal->setRange(0, 10);
    axisY_bal = new QValueAxis(); axisY_bal->setRange(-90, 90); // Ajusta según tu necesidad

    chartBalance->addAxis(axisX_bal, Qt::AlignBottom);
    chartBalance->addAxis(axisY_bal, Qt::AlignLeft);
    angleSeries->attachAxis(axisX_bal); angleSeries->attachAxis(axisY_bal);
    setpointSeries->attachAxis(axisX_bal); setpointSeries->attachAxis(axisY_bal);

    ui->visorBalancin->setChart(chartBalance);
    ui->visorBalancin->setRenderHint(QPainter::Antialiasing);

    // --- GRÁFICA 3: TÉRMINOS DEL PID DE EQUILIBRIO ---
    pSeries = new QLineSeries(); pSeries->setName("Proporcional (P)");
    iSeries = new QLineSeries(); iSeries->setName("Integral (I)");
    dSeries = new QLineSeries(); dSeries->setName("Derivativo (D)");
    outSeries = new QLineSeries(); outSeries->setName("Output Total");

    chartPID = new QChart();
    chartPID->addSeries(pSeries);
    chartPID->addSeries(iSeries);
    chartPID->addSeries(dSeries);
    chartPID->addSeries(outSeries);
    chartPID->setTitle("Aportes del PID (Balancín)");
    chartPID->layout()->setContentsMargins(0,0,0,0);

    axisX_pid = new QValueAxis(); axisX_pid->setRange(0, 10);
    axisY_pid = new QValueAxis(); axisY_pid->setRange(-1500, 1500); // Rango de PWM, ajustalo si necesitas

    chartPID->addAxis(axisX_pid, Qt::AlignBottom);
    chartPID->addAxis(axisY_pid, Qt::AlignLeft);

    pSeries->attachAxis(axisX_pid); pSeries->attachAxis(axisY_pid);
    iSeries->attachAxis(axisX_pid); iSeries->attachAxis(axisY_pid);
    dSeries->attachAxis(axisX_pid); dSeries->attachAxis(axisY_pid);
    outSeries->attachAxis(axisX_pid); outSeries->attachAxis(axisY_pid);

    ui->visorPID->setChart(chartPID);
    ui->visorPID->setRenderHint(QPainter::Antialiasing);
}

graphics::~graphics()
{
    delete ui;
}

void graphics::updateTelemetry(double time, double angle, double setpoint, int lineError, int turnPwm, int sumIR, int state)
{
    // Actualizar Gráficas
    angleSeries->append(time, angle);
    setpointSeries->append(time, setpoint);
    errorSeries->append(time, lineError);
    pwmSeries->append(time, turnPwm);

    // Scroll del eje X (Ventana de 10 segundos)
    if (time > 10.0) {
        axisX_bal->setRange(time - 10.0, time);
        axisX_line->setRange(time - 10.0, time);
    }
}

void graphics::updatePID(double time, double p, double i, double d, double out)
{
    pSeries->append(time, p);
    iSeries->append(time, i);
    dSeries->append(time, d);
    outSeries->append(time, out);

    // Scroll del eje X para que avance con el tiempo
    if (time > 10.0) {
        axisX_pid->setRange(time - 10.0, time);
    }
}

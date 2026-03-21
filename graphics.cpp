#include "graphics.h"
#include "ui_graphics.h"

graphics::graphics(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::graphics)
{
    ui->setupUi(this);

    // 1. Inicializar las series (líneas)
    angleSeries = new QLineSeries();
    angleSeries->setName("Ángulo Actual");

    setpointSeries = new QLineSeries();
    setpointSeries->setName("Setpoint");

    // 2. Crear la gráfica y añadir las series
    chart = new QChart();
    chart->addSeries(angleSeries);
    chart->addSeries(setpointSeries);
    chart->setTitle("Telemetría PID Balancín");

    // 3. Configurar los Ejes (X: Tiempo, Y: Ángulo)
    axisX = new QValueAxis();
    axisX->setTitleText("Tiempo (s)");
    axisX->setRange(0, 10); // Veremos ventanas de 10 segundos
    chart->addAxis(axisX, Qt::AlignBottom);

    axisY = new QValueAxis();
    axisY->setTitleText("Ángulo (°)");
    axisY->setRange(-45, 45); // Rango de caída del balancín
    chart->addAxis(axisY, Qt::AlignLeft);

    // Vincular ejes a las series
    angleSeries->attachAxis(axisX);
    angleSeries->attachAxis(axisY);
    setpointSeries->attachAxis(axisX);
    setpointSeries->attachAxis(axisY);

    // 4. Crear el visualizador e insertarlo en la ventana
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Creamos un Layout para que la gráfica llene toda la subventana
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(chartView);
    setLayout(layout);
}

graphics::~graphics()
{
    delete ui;
}

void graphics::updateGraph(double time, double angle, double setpoint, double pwm)
{
    // Añadir los nuevos puntos a las líneas
    angleSeries->append(time, angle);
    setpointSeries->append(time, setpoint);

    // Desplazar el eje X para crear el efecto de "osciloscopio" (Scroll)
    if (time > 10.0) {
        axisX->setRange(time - 10.0, time);
    }
}

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QResizeEvent>

#include <QtSerialPort/QSerialPort>
#include <QtNetwork/QUdpSocket>
#include <QLabel>
#include <QInputDialog>
#include <QTimer>
#include <QTime>
#include <QSerialPortInfo>

#include <QQuickWidget>
#include <QQuickItem>

#include <QElapsedTimer>

#include "graphics.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void dataReceived();

    void decodeData(uint8_t *datosRx, uint8_t source);

    void timeOut();

    void OnUdpRxData();

    void on_pushButton_connectSerial_clicked();

    void on_pushButton_sendSerial_clicked();

    void on_pushButton_connectUdp_clicked();

    void getData();



    /**
     * @brief sendSerial - Comando utilizado para enviar datos por el puerto serial en segundo plano
     * @param buf - Comando enviado por serial
     * @param length - longitud del comando en bytes
     */

    void sendSerial(uint8_t *buf, uint8_t length);

    /**
     * @brief sendUdp - Comando utilizado para enviar datos por wifi median udp en segundo plano
     * @param buf - Comando enviado por serial
     * @param length - longitud del comando en bytes
     */
    void sendUdp(uint8_t *buf, uint8_t length);

    /**
     * @brief sendCommand - Evalúa qué conexión está abierta (Serial o UDP) y envía la trama.
     * @param buf - Puntero al buffer de datos
     * @param length - longitud del comando en bytes
     */
    void sendCommand(uint8_t *buf, uint8_t length);

    bool eventFilter(QObject *watched, QEvent *event);

    void on_pushButton_clicked();

    void on_sendBalanceKp_clicked();
    void on_sendBalanceKi_clicked();
    void on_sendBalanceKd_clicked();
    void on_sendLineKp_clicked();
    void on_sendLineKd_clicked();

    void on_sendPIDMIN_clicked();
    void on_sendPIDMAX_clicked();
    void on_sendSetpoint_clicked();
    void on_sendAttackSetpoint_clicked();

    void on_sendPWML_clicked();
    void on_sendPWMR_clicked();
    void on_sendOFFSETL_clicked();
    void on_sendOFFSETR_clicked();
    void on_sendCustomTurn_clicked();
    void on_sendCounterAngle_clicked();

private:
    Ui::MainWindow *ui;
    QSerialPort *QSerialPort1;
    QLabel *statusMode;

    //Debug *myDebug;

    //timers
    QTimer  *timer1;
    QTimer  *timer2;


    graphics *myGraphics;

    //variables comunicacion udp
    QUdpSocket *QUdpSocket1;
    QHostAddress RemoteAddress;
    quint16 RemotePort;
    QHostAddress clientAddress;
    int puertoremoto;

    //otras
    bool firExe; //bool utilizado para dibujar el fondo del radar
    bool servoDir; //bool utilizado para modificar el sentido de giro del servo
    bool firRadarExe;
    int contadorAlive=0;
    int angle;
    bool paramsSynced = false;

    uint32_t lftEncData;
    uint32_t rhtEncData;

    QElapsedTimer runtimeTimer;

    typedef enum{
        START,
        HEADER_1,
        HEADER_2,
        HEADER_3,
        NBYTES,
        TOKEN,
        ID,
        PAYLOAD,
    }_eProtocolo;

    _eProtocolo estadoProtocolo,estadoProtocoloUdp;

    typedef enum{
        UDP=0,
        SERIE=1,
        ACK=0x0D,

        GETALIVE=0xA0,
        GETFIRMWARE=0xA1,
        GETMPU=0xA2,
        GETADC=0xA3,

        SETPWML=0xA4, // -> divisible en 2
        SETPWMR=0xA5,

        SETPWMLIMMAX=0xA6, //-> divisible en max y min
        SETPWMLIMMIN=0xA7,

        SETBALANCEKP=0XA8, //->kp,kd,ki
        SETBALANCEKD=0xA9,
        SETBALANCEKI=0xAA,

        SETSETPOINT=0xAB,

        SETLINEKP=0xAC,
        SETLINEKD=0xAD,

        GETINTERNALDATA = 0xF0, // ->revision exaustiva
        GETPIDBALANCE = 0xF1,

        SETOFFSETL=0xAE,
        SETOFFSETR=0xAF,

        SETCUSTOMTURN = 0xB0, //Valor de rotacion al seguir linea
        SETSPEED = 0xB1, //angulo de ataque movimiento
        SETBKANG = 0xB2, //angulo contra para evitar el aumento de velocidad

        UNKNOWCMD=0xFF,
        OTHERS
    }_eCmd;

    typedef struct{
        uint8_t timeOut;
        uint8_t cheksum;
        uint8_t payLoad[256];
        uint8_t nBytes;
        uint8_t index;
    }_sDatos ;

    _sDatos rxData, rxDataUdp;

    typedef union {
        double  d32;
        float f32;
        int i32;
        unsigned int ui32;
        unsigned short ui16[2];
        short i16[2];
        uint8_t ui8[4];
        char chr[4];
        unsigned char uchr[4];
        int8_t  i8[4];
    }_udat;

    _udat myWord;


    QQuickWidget *view3D;
    float yawAcumulado = 0.0f; // Para acumular la rotación del giroscopio

};
#endif // MAINWINDOW_H

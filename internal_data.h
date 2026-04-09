#ifndef INTERNAL_DATA_H
#define INTERNAL_DATA_H

#include <QDialog>

namespace Ui {
class internal_data;
}

class internal_data : public QDialog
{
    Q_OBJECT

public:
    explicit internal_data(QWidget *parent = nullptr);
    ~internal_data();

    void actualizarDatosLinea(int32_t sum, int32_t err, int32_t abs_err, int32_t lin, int32_t quad, int32_t offset, int16_t kp, int16_t kq);

private:
    Ui::internal_data *ui;
};

#endif // INTERNAL_DATA_H

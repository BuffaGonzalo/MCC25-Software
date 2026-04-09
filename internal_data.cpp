#include "internal_data.h"
#include "ui_internal_data.h"

internal_data::internal_data(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::internal_data)
{
    ui->setupUi(this);
}

internal_data::~internal_data()
{
    delete ui;
}

void internal_data::actualizarDatosLinea(int32_t sum, int32_t err, int32_t abs_err, int32_t lin, int32_t quad, int32_t offset, int16_t kp, int16_t kd)
{
}

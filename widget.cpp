#include "widget.h"
#include "ui_widget.h"



Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    if(ui->radioBinDec->isChecked())
    {
        ui->lineInput->setPlaceholderText("Input: BIN-DEC -> 100111.1101");
    }
    if(ui->radioDecBin->isChecked())
    {
        ui->lineInput->setPlaceholderText("Input: DEC-BIN -> 2356.106784");
    }
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_lineInput_editingFinished()
{

}

void Widget::on_lineInput_returnPressed()
{
    QString line = ui->lineInput->text();
    std::string input = line.toStdString();

    if(ui->radioBinDec->isChecked())
    {
        line = QString::fromStdString(Convertitore_start_BinDec(input));
        ui->lineOutput->setText(line);
        cleanDB();

    }

    if(ui->radioDecBin->isChecked())
    {
        line = QString::fromStdString(Convertitore_start_DecBin(input));
        ui->lineOutput->setText(line);
        cleanDB();
    }

    ui->lineInput->selectAll();

}

void Widget::on_radioBinDec_clicked()
{
    ui->lineInput->clear();
    ui->lineOutput->clear();
    ui->lineInput->setPlaceholderText("Input: BIN-DEC -> 100111.1101");
}

void Widget::on_radioDecBin_clicked()
{
    ui->lineInput->clear();
    ui->lineOutput->clear();
    ui->lineInput->setPlaceholderText("Input: DEC-BIN -> 2356.106784");
}



#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <iostream>

void cleanDB(void);

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    bool Convertitore_Leggi_Input_Bin_Dec(std::string str);
    bool Convertitore_Leggi_Input_Dec_Bin(std::string str);
    const std::string Convertitore_start_BinDec(std::string str);
    const std::string Convertitore_start_DecBin(std::string str);

private slots:

    void on_lineInput_editingFinished();

    void on_lineInput_returnPressed();

    void on_radioBinDec_clicked();

    void on_radioDecBin_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H

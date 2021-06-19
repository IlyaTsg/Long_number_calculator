#pragma once
#include <QWidget>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QPushButton>

class MainWindow : public QWidget
{
    Q_OBJECT

private:
    QTextEdit* inputEdit;       // Поле ввода

    QPushButton* classLL;       // ll
    QPushButton* classRA;       // rational
    QPushButton* classNA;       // natural
    QPushButton* classPO;       // polinom

    QPushButton* resButton;     // =
//  Для всех классов
    QPushButton* plusButton;    // +
    QPushButton* multButton;    // *
    QPushButton* remaButton;    // %
    QPushButton* inteButton;    // /
//  Для натуральных чисел
    QPushButton* factButton;    // !
    QPushButton* fiboButton;    // Фибоначи
    QPushButton* gcdButton;
    QPushButton* lcmButton;
//  Для целых цисел
    QPushButton* sinButton;     // sin
    QPushButton* cosButton;     // cos
    QPushButton* tanButton;     // tan
    QPushButton* ctgButton;     // ctg
    QPushButton* absButton;     // abs
//  Для полиномов
    QPushButton* derButton;     // Производная
    QPushButton* znaButton;     // Значение в точке
//  Кроме натуральных
    QPushButton* minuButton;    // -

    std::string numOne;
    std::string numTwo;

    int flag;

public:
    MainWindow(QWidget* parent = 0);

public slots:
    void onStart(bool flag);
    void checkBoxWidget();
    void forLL();
    void forRA();
    void forNA();
    void forPO();

    std::string scanText();
    void printText(std::string str);

    void onPlus();
    void onMinu();
    void onMult();
    void onRema();
    void onInte();

    void onSin();
    void onCos();
    void onTan();
    void onCtg();

    void onAbs();

    void onFact();
    void onFibo();

    void onDer();

    void onResu();

    void onZna();

    void onGcd();
    void onLcm();

};

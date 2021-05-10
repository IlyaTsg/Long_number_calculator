#include "MainWindow.h"

#include "ll.h"
#include "rational.h"
#include "natural.h"
#include "polinom.h"

MainWindow::MainWindow(QWidget* parent) : QWidget(parent)
{
    setWindowTitle("Long_number_calculator");
    setFixedSize(600, 900);

    inputEdit = new QTextEdit(this);

    classLL = new QPushButton(this);
    classLL->setText("LL");
    classLL->setCheckable(true);

    classRA = new QPushButton(this);
    classRA->setText("RA");
    classRA->setCheckable(true);

    classNA = new QPushButton(this);
    classNA->setText("NA");
    classNA->setCheckable(true);

    classPO = new QPushButton(this);
    classPO->setText("PO");
    classPO->setCheckable(true);

    resButton = new QPushButton(this);     // =
    resButton->setText("=");
    //  Для всех классов
    plusButton = new QPushButton(this);    // +
    plusButton->setText("+");
    multButton = new QPushButton(this);    // *
    multButton->setText("*");
    remaButton = new QPushButton(this);    // %
    remaButton->setText("%");
    inteButton = new QPushButton(this);    // /
    inteButton->setText("/");
    //  Для натуральных чисел
    factButton = new QPushButton(this);    // !
    factButton->setText("!");
    fiboButton = new QPushButton(this);    // Фибоначи
    fiboButton->setText("fibo");
    lcmButton = new QPushButton(this);    // НОК
    lcmButton->setText("lcm");
    gcdButton = new QPushButton(this);    // НОД
    gcdButton->setText("gcd");
    //  Для целых цисел
    sinButton = new QPushButton(this);     // sin
    sinButton->setText("sin");
    cosButton = new QPushButton(this);     // cos
    cosButton->setText("cos");
    tanButton = new QPushButton(this);     // tan
    tanButton->setText("tan");
    ctgButton = new QPushButton(this);     // ctg
    ctgButton->setText("ctg");
    absButton = new QPushButton(this);     // abs
    absButton->setText("abs");
    //  Для полиномов
    derButton = new QPushButton(this);     // Производная
    derButton->setText("f'");
    intButton = new QPushButton(this);     // Интеграл
    intButton->setText("F(x)");
    korButton = new QPushButton(this);     // Корни многочлена
    korButton->setText("f(x) = 0");
    znaButton = new QPushButton(this);     // Значение в точке
    znaButton->setText("f(x)");
    //  Кроме натуральных
    minuButton = new QPushButton(this);    // -
    minuButton->setText("-");


    inputEdit->setFixedSize(575, 300);

    //Classes
    classLL->setFixedSize(140, 70);
    classNA->setFixedSize(140, 70);
    classPO->setFixedSize(140, 70);
    classRA->setFixedSize(140, 70);

    QHBoxLayout* lay1 = new QHBoxLayout();
    lay1->addWidget(classLL);
    lay1->addWidget(classRA);
    lay1->addWidget(classNA);
    lay1->addWidget(classPO);

    //All
    plusButton->setFixedSize(140, 70);
    multButton->setFixedSize(140, 70);
    inteButton->setFixedSize(140, 70);
    minuButton->setFixedSize(140, 70);

    QHBoxLayout* lay2 = new QHBoxLayout();
    lay2->addWidget(plusButton);
    lay2->addWidget(multButton);
    lay2->addWidget(inteButton);
    lay2->addWidget(minuButton);

    //Nat
    remaButton->setFixedSize(140, 70);
    factButton->setFixedSize(140, 70);
    fiboButton->setFixedSize(140, 70);
    absButton->setFixedSize(140, 70);

    QHBoxLayout* lay3 = new QHBoxLayout();
    lay3->addWidget(remaButton);
    lay3->addWidget(factButton);
    lay3->addWidget(fiboButton);
    lay3->addWidget(absButton);


    //trig
    sinButton->setFixedSize(65, 70);
    cosButton->setFixedSize(65, 70);
    tanButton->setFixedSize(65, 70);
    ctgButton->setFixedSize(65, 70);
    lcmButton->setFixedSize(135, 70);
    gcdButton->setFixedSize(135, 70);

    QHBoxLayout* lay4 = new QHBoxLayout();
    lay4->addWidget(sinButton);
    lay4->addWidget(cosButton);
    lay4->addWidget(tanButton);
    lay4->addWidget(ctgButton);
    lay4->addWidget(lcmButton);
    lay4->addWidget(gcdButton);
    


    //Polinom
    derButton->setFixedSize(140, 70);
    intButton->setFixedSize(140, 70);
    korButton->setFixedSize(140, 70);
    znaButton->setFixedSize(140, 70);

    QHBoxLayout* lay5 = new QHBoxLayout();
    lay5->addWidget(derButton);
    lay5->addWidget(intButton);
    lay5->addWidget(korButton);
    lay5->addWidget(znaButton);


    resButton->setFixedSize(575, 70);

    QVBoxLayout* vLayout = new QVBoxLayout(this);
    vLayout->addWidget(inputEdit);
    vLayout->addLayout(lay1);
    vLayout->addLayout(lay2);
    vLayout->addLayout(lay3);
    vLayout->addLayout(lay4);
    vLayout->addLayout(lay5);
    vLayout->addWidget(resButton);

    onStart(false);

    connect(classLL, SIGNAL(clicked(bool)), this, SLOT(forLL()));
    connect(classRA, SIGNAL(clicked(bool)), this, SLOT(forRA()));
    connect(classNA, SIGNAL(clicked(bool)), this, SLOT(forNA()));
    connect(classPO, SIGNAL(clicked(bool)), this, SLOT(forPO()));

    connect(plusButton, SIGNAL(clicked(bool)), this, SLOT(onPlus()));
    connect(minuButton, SIGNAL(clicked(bool)), this, SLOT(onMinu()));
    connect(multButton, SIGNAL(clicked(bool)), this, SLOT(onMult()));
    connect(remaButton, SIGNAL(clicked(bool)), this, SLOT(onRema()));
    connect(inteButton, SIGNAL(clicked(bool)), this, SLOT(onInte()));

    connect(sinButton, SIGNAL(clicked(bool)), this, SLOT(onSin()));
    connect(cosButton, SIGNAL(clicked(bool)), this, SLOT(onCos()));
    connect(tanButton, SIGNAL(clicked(bool)), this, SLOT(onTan()));
    connect(ctgButton, SIGNAL(clicked(bool)), this, SLOT(onCtg()));

    connect(absButton, SIGNAL(clicked(bool)), this, SLOT(onAbs()));

    connect(factButton, SIGNAL(clicked(bool)), this, SLOT(onFact()));
    connect(fiboButton, SIGNAL(clicked(bool)), this, SLOT(onFibo()));

    connect(derButton, SIGNAL(clicked(bool)), this, SLOT(onDer()));

    connect(resButton, SIGNAL(clicked(bool)), this, SLOT(onResu()));

    connect(znaButton, SIGNAL(clicked(bool)), this, SLOT(onZna()));
    connect(intButton, SIGNAL(clicked(bool)), this, SLOT(onInt()));

    connect(gcdButton, SIGNAL(clicked(bool)), this, SLOT(onGcd()));
    connect(lcmButton, SIGNAL(clicked(bool)), this, SLOT(onLcm()));



}

void MainWindow::checkBoxWidget()
{
    classLL->setChecked(false);
    classRA->setChecked(false);
    classNA->setChecked(false);
    classPO->setChecked(false);
}

void MainWindow::onStart(bool flag)
{
    inputEdit->setEnabled(flag);
    inputEdit->setFontPointSize(15);

    plusButton->setEnabled(flag);
    multButton->setEnabled(flag);
    inteButton->setEnabled(flag);
    minuButton->setEnabled(flag);

    remaButton->setEnabled(flag);
    factButton->setEnabled(flag);
    fiboButton->setEnabled(flag);
    absButton->setEnabled(flag);

    gcdButton->setEnabled(flag);
    lcmButton->setEnabled(flag);
    sinButton->setEnabled(flag);
    cosButton->setEnabled(flag);
    tanButton->setEnabled(flag);
    ctgButton->setEnabled(flag);


    derButton->setEnabled(flag);
    intButton->setEnabled(flag);
    korButton->setEnabled(flag);
    znaButton->setEnabled(flag);

    resButton->setEnabled(flag);
}

void MainWindow::forLL()
{
    onStart(true);
    factButton->setEnabled(false);
    fiboButton->setEnabled(false);

    derButton->setEnabled(false);
    intButton->setEnabled(false);
    korButton->setEnabled(false);
    znaButton->setEnabled(false);
    lcmButton->setEnabled(false);
    gcdButton->setEnabled(false);

    inputEdit->setEnabled(true);
    inputEdit->clear();

    checkBoxWidget();
    classLL->setChecked(true);
}

void MainWindow::forRA()
{
    forLL();
    remaButton->setEnabled(false);

    absButton->setEnabled(false);

    sinButton->setEnabled(false);
    cosButton->setEnabled(false);
    tanButton->setEnabled(false);
    ctgButton->setEnabled(false);
    lcmButton->setEnabled(false);
    gcdButton->setEnabled(false);

    checkBoxWidget();
    classRA->setChecked(true);
}

void MainWindow::forNA()
{
    forRA();

    factButton->setEnabled(true);
    fiboButton->setEnabled(true);
    remaButton->setEnabled(true);
    lcmButton->setEnabled(true);
    gcdButton->setEnabled(true);

    minuButton->setEnabled(false);

    checkBoxWidget();
    classNA->setChecked(true);
}

void MainWindow::forPO()
{
    onStart(true);
    absButton->setEnabled(false);
    factButton->setEnabled(false);
    fiboButton->setEnabled(false);
    sinButton->setEnabled(false);
    cosButton->setEnabled(false);
    tanButton->setEnabled(false);
    ctgButton->setEnabled(false);
    lcmButton->setEnabled(false);
    gcdButton->setEnabled(false);

    inputEdit->setEnabled(true);
    inputEdit->clear();

    checkBoxWidget();
    classPO->setChecked(true);
}

std::string MainWindow::scanText()
{
    std::string str = (inputEdit->toPlainText()).toStdString();
    inputEdit->clear();
    return str;
}

void MainWindow::printText(std::string str)
{
    inputEdit->clear();
    inputEdit->setText("Result: " + QString::fromUtf8(str.c_str()));
}

void MainWindow::onPlus()
{
    numOne = scanText();
    flag = 0;
}

void MainWindow::onMinu()
{
    numOne = scanText();
    flag = 1;
}

void MainWindow::onMult()
{
    numOne = scanText();
    flag = 2;
}

void MainWindow::onRema()
{
    numOne = scanText();
    flag = 3;
}

void MainWindow::onInte()
{
    numOne = scanText();
    flag = 4;
}

void MainWindow::onZna()
{
    numOne = scanText();
    flag = 5;
}

void MainWindow::onInt()
{
    numOne = scanText();
    flag = 6;
}

void MainWindow::onLcm()
{
    numOne = scanText();
    flag = 7;
}

void MainWindow::onGcd()
{
    numOne = scanText();
    flag = 8;
}


void MainWindow::onSin()
{
    numOne = scanText();
    std::ostringstream string;
    string << sin(ll(numOne));
    printText(string.str());
}

void MainWindow::onCos()
{
    numOne = scanText();
    std::ostringstream string;
    string << cos(ll(numOne));
    printText(string.str());
}

void MainWindow::onTan()
{
    numOne = scanText();
    std::ostringstream string;
    string << tg(ll(numOne));
    printText(string.str());
}

void MainWindow::onCtg()
{
    numOne = scanText();
    std::ostringstream string;
    string << ctg(ll(numOne));
    printText(string.str());
}

void MainWindow::onAbs()
{
    numOne = scanText();
    printText(toString(ll(numOne).abs()));
}

void MainWindow::onFact()
{
    numOne = scanText();
    printText(toString(fact(std::stoi(numOne))));
}

void MainWindow::onFibo()
{
    numOne = scanText();
    printText(toString(fib(std::stoi(numOne))));
}

void MainWindow::onDer()
{
    numOne = scanText();
    polinom<int, int> num1(numOne);
    printText(toString(derivative(num1)));
}

void MainWindow::onResu()
{
    numTwo = scanText();

    if (classLL->isChecked()) {
        ll num1{ numOne }, num2{ numTwo };
        switch (flag)
        {
        case 0:
            printText(toString(num1 + num2));
            break;
        case 1:
            printText(toString(num1 - num2));
            break;
        case 2:
            printText(toString(num1 * num2));
            break;
        case 3:
            printText(toString(num1 % num2));
            break;
        case 4:
            printText(toString(num1 / num2));
            break;
        }
    }
    else if (classRA->isChecked()) {
        rational<ll> num1(numOne), num2(numTwo);
        switch (flag)
        {
        case 0:
            printText(toString(num1 + num2));
            break;
        case 1:
            printText(toString(num1 - num2));
            break;
        case 2:
            printText(toString(num1 * num2));
            break;
        case 4:
            printText(toString(num1 / num2));
            break;
        }
    }
    else if (classNA->isChecked()) {
        vln num1(numOne), num2(numTwo);
        switch (flag)
        {
        case 0:
            printText(toString(num1 + num2));
            break;
        case 2:
            printText(toString(num1 * num2));
            break;
        case 3:
            printText(toString(num1 % num2));
            break;
        case 4:
            printText(toString(num1 / num2));
            break;
        case 7:
            printText(toString(lcm(num1, num2)));
            break;
        case 8:
            printText(toString(gcd(num1, num2)));
            break;
        }
    }
    else if (classPO->isChecked()) {
        polinom<int, int> num1(numOne), num2(numTwo);
        int num3;
        switch (flag)
        {
        case 0:
            printText(toString(num1 + num2));
            break;
        case 1:
            printText(toString(num1 - num2));
            break;
        case 2:
            printText(toString(num1 * num2));
            break;
        case 3:
            printText(toString(num1 % num2));
            break;
        case 4:
            printText(toString(num1 / num2));
            break;
        case 5:
            num3 = std::stoi(numTwo);
            printText(toString(substitution(num1, num3)));
            break;
        case 6:
            num3 = std::stoi(numTwo);
            printText(toString(integral(num1, num3)));
            break; 

        }
    }
}

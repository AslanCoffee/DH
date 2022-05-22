#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "main.cpp"

long long int shivrovka(long long int a, long long int b, long long int P)
{
    if(b==1)return a;
    else return (((long long int)pow(a, b)) % P);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString encode(QString input, int offset) {
    for(int i = 0; i < input.length(); i++) {
        int sym = 0;
        if(input[i].toLatin1() > 64 && input[i].toLatin1() < 91 && (sym = input[i].toLatin1() + offset) > 90)
            //Если буква большая и если буква + смещение превышает код буквы Z
            input[i] = QChar(sym - 90 + 64);
        //sym - 90 получаем, насколько превышает код буквы Z, + 65 прибавляем к коду символа до A полученный результат
        //Теперь тоже самое но с проверкой на маленькую букву
        else if(input[i].toLatin1() > 96 && input[i].toLatin1() < 123 && (sym = input[i].toLatin1() + offset) > 122)
            //Если буква маленькая и если буква + смещение превышает код буквы z
            input[i] = QChar(sym - 122 + 96);
        //sym - 90 получаем, насколько превышает код буквы z, + 65 прибавляем к коду символа до a полученный результат
        else input[i] = QChar(input[i].toLatin1() + offset);
    }
    return input;
}

QString decode(QString input, int offset) {
    for(int i = 0; i < input.length(); i++) {
        int sym = 0;
        if(input[i].toLatin1() > 64 && input[i].toLatin1() < 91 && (sym = input[i].toLatin1() - offset) < 65)
            //Если буква большая и если буква - смещение меньше кода буквы A
            input[i] = QChar(sym - 64 + 90);
        //Получаем исходный символ (обратно sym - 90 + 64)
        //Теперь тоже самое но с проверкой на маленькую букву
        else if(input[i].toLatin1() > 96 && input[i].toLatin1() < 123 && (sym = input[i].toLatin1() - offset) < 97)
            //Если буква маленькая и если буква - смещение меньше кода буквы a
            input[i] = QChar(sym - 96 + 122);
        //Получаем исходный символ (обратно sym - 122 + 96)
        else input[i] = QChar(input[i].toLatin1() - offset);
    }
    return input;
}


void MainWindow::on_ButShifr_clicked()
{
    QString text = ui->OText->text();
    int P = ui->Ptext->text().toInt();
    int G = ui->Gtext->text().toInt();
    int A = ui->Atext->text().toInt();
    int B = ui->Btext->text().toInt();
    int x = (shivrovka(G,A,P));//key Alice
    int y = (shivrovka(G,B,P));//key Bob
    int ky = (shivrovka(y,A,P));//Alice for Bob
    int kx = (shivrovka(x,B,P));//Bob for Alice
    QString kxs = QString::number(kx);//Alice
    QString kys = QString::number(ky);//Bob
    ui->Akey->setText("");
    ui->Bkey->setText("");
    ui->Akey->setText(ui->Akey->text() + kxs);
    ui->Bkey->setText(ui->Bkey->text() + kys);
    ui->Shifr->setText("");
    ui->Shifr->setText(encode(text,kx));
}


void MainWindow::on_pushButton_clicked()
{
    int key = ui->KeyDeshifr->text().toInt();
    ui->deshifr->setText("");
    QString str = ui->Shifr->text();
    ui->deshifr->setText(decode(str,key));
}


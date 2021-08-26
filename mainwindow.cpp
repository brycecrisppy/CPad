#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
    setWindowTitle("CrustyPad");
}

MainWindow::~MainWindow() {
    delete ui;
}

// Slot Methods:
void MainWindow::on_actionNew_triggered() {
    setWindowTitle("CrustyPad");
    currentFilename.clear();
    ui->textEdit->setText(QString());
}

void MainWindow::on_actionOpen_triggered() {
    QString filename = QFileDialog::getOpenFileName(this, "Open File");
    QFile file(filename);

    currentFilename = filename;

    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return;
    }

    setWindowTitle(filename);

    QTextStream in(&file);
    QString text = in.readAll();

    ui->textEdit->setText(text);

    file.close();
}

void MainWindow::on_actionSaveAs_triggered() {
    QString filename = QFileDialog::getSaveFileName(this, "Save File");
    QFile file(filename);

    currentFilename = filename;

    if (!file.open(QIODevice::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }

    setWindowTitle(filename);

    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();

    out << text;

    file.close();
}

void MainWindow::on_actionSave_triggered() {
    QFile file(currentFilename);
    QTextStream stream(&file);

    if (!file.open(QIODevice::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }

    QString text = ui->textEdit->toPlainText();

    stream << text;

    file.close();
}

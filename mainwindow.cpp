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

void MainWindow::on_actionExit_triggered() {
    QApplication::quit();
}

void MainWindow::on_actionCopy_triggered() {
    ui->textEdit->copy();
}

void MainWindow::on_actionPaste_triggered() {
    ui->textEdit->paste();
}

void MainWindow::on_actionCut_triggered() {
    ui->textEdit->cut();
}

void MainWindow::on_actionUndo_triggered() {
    ui->textEdit->undo();
}

void MainWindow::on_actionRedo_triggered() {
    ui->textEdit->redo();
}

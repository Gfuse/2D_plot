/*
 * imagecompare.h
 *
 *  Created on: 25 Nov 2019
 *      Author: Majid
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QDir>
#include <QMessageBox>
#include <QCloseEvent>
#include <QFileDialog>
#include <QComboBox>
#include <QScreen>
#include <iostream>
#include <cmath>
#include "signal.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    Ui::MainWindow *ui=nullptr;
    Signal<double>* root=nullptr;
private slots:
    void plot(const QString& name, const QString &parent);
};
#endif

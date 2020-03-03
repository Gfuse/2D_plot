/*
 * imagecompare.cpp
 *
 *  Created on: 6 jan 2020
 *      Author: Majid
 */
#include "mainwindow.h"
#include "ui_mainwindow.h"

int main(int argc, char** argv)
 {
    QApplication a(argc, argv);
    MainWindow w;
    if(a.exec()==0)return 0;
 }

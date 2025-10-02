#ifndef CHOISEALGORITHMMENU_H
#define CHOISEALGORITHMMENU_H

#include <QVBoxLayout>
#include <QDialog>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QLineEdit>
#include <QLabel>
#include <QApplication>
#include <QPushButton>

#include "ProjectInfo.h"

class ChoiseAlgorithmMenu : public QDialog
{
    Q_OBJECT
public:
    explicit ChoiseAlgorithmMenu(QWidget* parent = nullptr);

private slots:
    void jarvisbtn();
    void grahambtn();
    void andrewbtn();

};

#endif // CHOISEALGORITHMMENU_H

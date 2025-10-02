#include "choisealgorithmmenu.h"




ChoiseAlgorithmMenu::ChoiseAlgorithmMenu(QWidget* parent) : QDialog(parent){
    setWindowTitle("Choise algorithm");
    setModal(true);

    resize(400, 150);


    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QHBoxLayout* buttonsLayout = new QHBoxLayout();

    QPushButton* jarvisMarch = new QPushButton("Jarvis march");
    QPushButton* grahamScan = new QPushButton("Graham scan");
    QPushButton* andrewsMonotonsChain = new QPushButton("Andrew monotans chain");

    buttonsLayout->addWidget(jarvisMarch);
    buttonsLayout->addWidget(grahamScan);
    buttonsLayout->addWidget(andrewsMonotonsChain);

    mainLayout->addLayout(buttonsLayout);

    connect(jarvisMarch, &QPushButton::clicked, this, &ChoiseAlgorithmMenu::jarvisbtn);
    connect(grahamScan, &QPushButton::clicked, this, &ChoiseAlgorithmMenu::grahambtn);
    connect(andrewsMonotonsChain, &QPushButton::clicked, this, &ChoiseAlgorithmMenu::andrewbtn);
}


void ChoiseAlgorithmMenu::jarvisbtn(){

}

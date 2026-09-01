#include <QApplication>
#include <QLineEdit>
#include <QObject>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    QWidget window;
    window.setWindowTitle("QtCalc");

    auto *display = new QLineEdit("0");
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);

    auto *oneButton = new QPushButton("1");

    auto *keypadLayout = new QGridLayout();

    keypadLayout->addWidget(new QPushButton("7"), 0, 0);
    keypadLayout->addWidget(new QPushButton("8"), 0, 1);
    keypadLayout->addWidget(new QPushButton("9"), 0, 2);

    keypadLayout->addWidget(new QPushButton("4"), 1, 0);
    keypadLayout->addWidget(new QPushButton("5"), 1, 1);
    keypadLayout->addWidget(new QPushButton("6"), 1, 2);

    keypadLayout->addWidget(oneButton, 2, 0);
    keypadLayout->addWidget(new QPushButton("2"), 2, 1);
    keypadLayout->addWidget(new QPushButton("3"), 2, 2);

    keypadLayout->addWidget(new QPushButton("0"), 3, 1);

    auto *layout = new QVBoxLayout(&window);
    layout->addWidget(display);
    layout->addLayout(keypadLayout);

    QObject::connect(oneButton, &QPushButton::clicked, [display]() {
        display->setText("1");
    });

    window.resize(250, 150);
    window.show();

    return app.exec();
}
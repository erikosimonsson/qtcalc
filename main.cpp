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

    auto *layout = new QVBoxLayout(&window);
    layout->addWidget(display);
    layout->addWidget(oneButton);

    QObject::connect(oneButton, &QPushButton::clicked, [display]() {
        display->setText("1");
    });

    window.resize(250, 150);
    window.show();

    return app.exec();
}
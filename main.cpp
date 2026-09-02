#include <QApplication>
#include <QLineEdit>
#include <QObject>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QGridLayout>
#include <QStringList>

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    QWidget window;
    window.setWindowTitle("QtCalc");

    auto *display = new QLineEdit("0");
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);

    auto *oneButton = new QPushButton("1");

    auto *keypadLayout = new QGridLayout();

    const QStringList buttonLabels = {
        "7", "8", "9",
        "4", "5", "6",
        "1", "2", "3",
        "0", "."
    };

    for (int i = 0; i < buttonLabels.size(); ++i){
        const QString buttonText = buttonLabels[i];
        auto *button = new QPushButton(buttonText);
        const int row = i / 3;
        const int col = i % 3;

        keypadLayout->addWidget(button, row, col);

        QObject::connect(button, &QPushButton::clicked, [display, buttonText]() {
            const QString currentText = display->text();
            if (buttonText == "." && currentText.contains('.')) {
                return;
            }

            if (currentText == "0" && buttonText != ".") {
                display->setText(buttonText);
            } else {
                display->setText(currentText + buttonText);
            }
        });
    }

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
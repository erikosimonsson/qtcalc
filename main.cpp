#include <QApplication>
#include <QLineEdit>
#include <QObject>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QGridLayout>
#include <QStringList>
#include <QSizePolicy>

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    QWidget window;
    window.setWindowTitle("QtCalc");

    window.setStyleSheet(R"(
        QLineEdit {
            font-size: 28px;
            padding: 8px;
        }
        QPushButton {
            font-size: 20px;
        }
    )");

    auto *display = new QLineEdit("0");
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);
    display->setMinimumHeight(65);

    double firstOperand = 0.0;
    QString pendingOperator;
    bool startNewNumber = false;

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
        button->setSizePolicy(
            QSizePolicy::Expanding,
            QSizePolicy::Expanding
        );
        const int row = i / 3;
        const int col = i % 3;

        keypadLayout->addWidget(button, row, col);

        QObject::connect(button, &QPushButton::clicked, [display, buttonText, &startNewNumber]() {
            if (startNewNumber) {
                display->setText("0");
                startNewNumber = false;
            }

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

    const QStringList operatorLabels = { "/", "*", "-", "+" };

    for (int row = 0; row < operatorLabels.size(); ++row) {
        const QString operatorText = operatorLabels[row];
        auto *operatorButton = new QPushButton(operatorText);
        operatorButton->setSizePolicy(
            QSizePolicy::Expanding,
            QSizePolicy::Expanding
        );

        keypadLayout->addWidget(operatorButton, row, 3);

        QObject::connect(operatorButton, &QPushButton::clicked, [display, operatorText, &firstOperand, &pendingOperator, &startNewNumber]() {
            firstOperand = display->text().toDouble();
            pendingOperator = operatorText;
            startNewNumber = true;
        });
    }

    auto *clearButton = new QPushButton("C");
    clearButton->setSizePolicy(
        QSizePolicy::Expanding,
        QSizePolicy::Expanding
    );

    keypadLayout->addWidget(clearButton, 3, 2);

    QObject::connect(clearButton, &QPushButton::clicked, [display, &firstOperand, &pendingOperator, &startNewNumber]() {
        display->setText("0");
        firstOperand = 0.0;
        pendingOperator.clear();
        startNewNumber = false;
    });

    auto *equalsButton = new QPushButton("=");
    equalsButton->setSizePolicy(
        QSizePolicy::Expanding,
        QSizePolicy::Expanding
    );

    keypadLayout->addWidget(equalsButton, 4, 0, 1, 4);

    QObject::connect(equalsButton, &QPushButton::clicked, [display, &firstOperand, &pendingOperator, &startNewNumber]() {
        if (pendingOperator.isEmpty() || startNewNumber) {
            return;
        }

        const double secondOperand = display->text().toDouble();
        double result = 0.0;

        if (pendingOperator == "+") {
            result = firstOperand + secondOperand;
        } else if (pendingOperator == "-") {
            result = firstOperand - secondOperand;
        } else if (pendingOperator == "*") {
            result = firstOperand * secondOperand;
        } else if (pendingOperator == "/") {
            if (secondOperand != 0.0) {
                result = firstOperand / secondOperand;
            } else {
                display->setText("Error");
                return;
            }
        }
        
        display->setText(QString::number(result, 'g', 15));

        firstOperand = result;
        pendingOperator.clear();
        startNewNumber = true;
    });

    for (int column = 0; column < 4; ++column) {
        keypadLayout->setColumnStretch(column, 1);
    }

    for (int row = 0; row < 5; ++row) {
        keypadLayout->setRowStretch(row, 1);
    }

    auto *layout = new QVBoxLayout(&window);
    layout->addWidget(display);
    layout->addLayout(keypadLayout, 1);

    window.resize(350, 500);
    window.show();

    return app.exec();
}
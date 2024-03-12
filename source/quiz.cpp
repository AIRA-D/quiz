#include "quiz.h"
#include "./ui_quiz.h"

#include <vector>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

std::vector<Question> questions;

void initQuiz() {
    QFile inputFile(":/questions_data.txt");
    if (!inputFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(nullptr, "Error", "Unable to open file");
        return;
    }

    QTextStream in(&inputFile);
    in.setCodec("UTF-8"); // Устанавливаем кодек UTF-8 для корректного чтения данных

    Question currentQuestion;
    int answerCount = 0;
    while (!in.atEnd()) {
        QString line = in.readLine();

        if (answerCount < 4) {
            currentQuestion.answers[answerCount] = line;
            ++answerCount;
        } else {
            currentQuestion.question = line;
            in >> currentQuestion.correctAnswer;
            in.readLine(); // Пропускаем символ новой строки

            questions.push_back(currentQuestion); // Добавляем вопрос в вектор
            answerCount = 0; // Сбрасываем счетчик ответов
        }
    }

    inputFile.close();
}

int current = 0;

Quiz::Quiz(QWidget *parent) : QWidget(parent), ui(new Ui::Quiz)
{
    ui->setupUi(this);
    initQuiz();
    ui->QuestionLabel->setText(questions[current].question);

    for (int i = 0; i < 4; i++) {
        auto *button = findChild<QPushButton*>("Button_"+QString::number(i));
        button->setText(questions[current].answers[i]);
        connect(button, SIGNAL(clicked()), this, SLOT(checkAnswer()));
    }
}

Quiz::~Quiz()
{
    delete ui;
}


void Quiz::checkAnswer()
{
    auto *button = qobject_cast<QPushButton*>(sender());
    if (!button) {
        return; // Проверка на nullptr
    }

    int answer = button->objectName().remove("Button_").toInt(); // get the index of the answer selected

    if (current >= questions.size()) {
        return; // проверяем, чтобы не обращаться к элементам за пределами
    }

    if (answer == questions[current].correctAnswer) {
        current++;

        if (current < questions.size()) {
            ui->QuestionLabel->setText(questions[current].question);

            for (int i = 0; i < 4; i++) {
                auto *newButton = findChild<QPushButton*>("Button_" + QString::number(i));
                if (newButton) {
                    newButton->setText(questions[current].answers[i]);
                }
            }
        } else {
            QMessageBox::information(this, "Вот и конец.", "Отлично справились!");
        }
    } else {
        QMessageBox::warning(this, "Упс, ошибочка!", "Ответик неверный. Попробуйте еще раз!");
    }
}


# quiz
A small, minimalistic app for creating small quizzes/surveys. 
It can serve as a basis for more complex applications, such as automatic test checks in digital education programs. 

## How to use:
All you need to do to customize your quiz is to edit the **questions_data.txt** file according to the sample:
```
[question text]
[answer 0]
[answer 1]
[answer 2]
[answer 3]
[correct answer number]
```
#### Example:
```
What is malware?
Microsoft software
Development for anonymous surfing
Programs to harm your computer or information
Linux operating system
2
What is a CSRF attack?
Authentication attack
Cross-site scripting
Injecting malicious code into requests
Password mining
0
What is the abbreviation for XSS?
Cross-Site Scripting
XML Security Suite
Extra Secure Software
Cross Security System
0
```
Also inside the program you can customize text warnings about wrong answers and congratulations on test completion.
```cpp
void Quiz::checkAnswer() {
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
            QMessageBox::information(this, "The End.", "Well Done!");    // Here u can change messages
        }
    } else {
        QMessageBox::warning(this, "Mistake/!", "Try again!");
    }
}
```
P.S. Maybe this app will come in handy for someone, but for now I'll just keep using it on my younger cousin to make him study hard, hehehe. =]

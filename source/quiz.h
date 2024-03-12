#ifndef QUIZ_H
#define QUIZ_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class Quiz; }
QT_END_NAMESPACE

struct Question{
    QString question;
    QString answers[4];
    int correctAnswer;
};

class Quiz : public QWidget
{
    Q_OBJECT

public:
    explicit Quiz(QWidget *parent = nullptr);
    ~Quiz() override;

private slots:
    void checkAnswer();

private:
    Ui::Quiz *ui;
};
#endif // QUIZ_H

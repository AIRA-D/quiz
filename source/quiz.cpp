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

/*Question questions[12] = {
{"Что такое \"вредоносное ПО\"?", {"Программное обеспечение от Microsoft", "Разработка для анонимного серфинга", "Программы, для нанесения вреда компьютеру или информации", "Операционная система Linux" }, 2},
{"Что такое CSRF атака?", {"Атака на аутентификацию", "Межсайтовый скриптинг", "Введение вредоносного кода в запросы", "Подбор пароля"}, 0},
{"Каково сокращение XSS?", {"Cross-Site Scripting", "XML Security Suite", "Extra Secure Software", "Cross Security System"}, 0},
{"Почему Java и C++ не могут найти общий язык?", {"Потому что они все время борются за управление памятью", "Потому что они слишком разные", "Потому что Java слишком медлительно договаривается", "Потому что они пытаются инкапсулировать свои чувства"}, 2},
{"Какие типы атак включает в себя атака MITM (Man-in-the-Middle)?", {"DDoS, Phishing, Ransomware", "SQL Injection, Spoofing, Session Hijacking", "DNS Spoofing, Packet Sniffing, Replay Attack", "Keylogger, Trojan, Rootkit"}, 2},
{"Почему Python - веселый язык?", {"Потому что в нем есть графика", "Потому что в нем много библиотек для шуток", "Потому что с ним не больно", "Потому что грустный язык \"питоном\" не назовут"}, 3},
{"Элемент инфраструктуры для фильтрации сетевого трафика?", {"Proxy-сервер", "Хаб", "Маршрутизатор", "Коммутатор"}, 0},
{"Уязвимость безопасности, для выполния кода на удаленной машине?", {"Phishing", "Hacking", "Spoofing", "Remote Code Execution"}, 3},
{"Как звали создателя Си?", {"Линус Торвальдс", "Эндрю Таненбаум", "Ларри Уолл", "Деннис Ритчи"}, 3},
{"Что такое OSI (Open Systems Interconnection)?", {"Модель сетевой архитектуры", "Служба облачного хранения", "База данных для криптографии", "Официальный стандарт интернета"}, 0},
{"Что такое бэкдор в компьютерной безопасности?", {"Задняя дверь для внедрения в систему", "Сквозное отверстие в брандмауэре", "Программное средство для маскировки вредоносного кода", "Атака на виртуальную сеть"}, 0},
{"Что означает термин \"Zero-Day Exploit\"?", {"Эксплуатация незакрытых уязвимостей", "Атака на системы, неимеющие обновлений", "Эксплуатация недавно обнаруженной уязвимости", "Работа в сети без ограничений времени"}, 2},
/*{{"12) Какая атака подразумевает создание активной сети Wi-Fi с точно таким же именем как и у легитимной сети для получения доступа к информации?", {"Spoofing", "Bluejacking", "Evil Twin", "Phishing"}, 2},
{"13) Что означает термин PII в контексте безопасности данных?", {"Personal Information Integrity", "Protected Internet Interaction", "Personal Identity Information", "Personally Identifiable Information"}, 3},
{"14) Какая из атак направлена на отправку ложной информации в узел сети для перехвата настоящей информации?", {"XML Injection", "Sniffing Attack", "Replay Attack", "Spoofing Attack"}, 3},
{"15) Что такое DoS-атака?", {"Атака на базы данных", "Отказ в обслуживании системы", "Атака на аутентификацию", "Атака на Wi-Fi сети"}, 1},
"Какое понятие относится к ситуации, когда атакующий перехватывает и повторяет перехваченный трафик с целью обмануть узел сети?", {"Blockchain Attack", "Man-in-the-Middle Attack", "Session Hijacking", "Replay Attack"}, 3},
{"17) Что такое OSI (Open Systems Interconnection)?", {"Модель сетевой архитектуры", "Служба облачного хранения", "База данных для криптографии", "Официальный стандарт интернета"}, 0},
{"18) Какая из нижеперечисленных программ является вирусом?", {"Firewall", "Antivirus", "Adware", "Trojan"}, 2},
{"19) Что такое phishing?", {"Атака на персональные данные пользователей", "Атака на внутреннюю сеть компании", "Атака на защищенные программы", "Атака на операционную систему"}, 0},
{"20) Что такое атака социальной инженерии?", {"Атака на компьютерные сети", "Атака на базы данных", "Атака с использованием человеческого фактора", "Атака на вирусы и трояны"}, 2},
{"21) Чем отличается атака от уязвимости в информационной безопасности?", {"Атака - дефект в программном обеспечении, уязвимость - попытка проникновения", "Атака - попытка нарушения целостности информации, уязвимость - слабое место в информационной системе", "Атака - результат уязвимости, уязвимость - успешность атаки", "Атака - процесс внедрения в систему, уязвимость - попытка завладения данными"}, 1},
{"22) Что означает термин \"Zero-Day Exploit\"?", {"Эксплуатация незакрытых уязвимостей", "Атака на системы, неимеющие обновлений", "Эксплуатация недавно обнаруженной уязвимости", "Работа в сети без ограничений времени"}, 2},
{"23) Что такое баг-баунти (Bug Bounty) в области информационной безопасности?", {"Награда за нахождение и сообщение о безопасностях", "Обучающий курс по информационной безопасности", "Премия за лучшее применение криптографии", "Публичное тестирование информационной системы"}, 0}

 };
*/
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


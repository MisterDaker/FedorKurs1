// Курсовая работа "Технология Программирования" Авдеев Ф.А. ИСТ-361
// "Ремонт бытовой техники": заказы, скидки, клиенты, ассортемент

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <sstream>

using namespace std;

// Создаем класс для мастера
class Master {
public:
    string name;
    int time;
    double price;

    // Конструктор
    Master(string t, int s, double p) : name(t), time(s), price(p) {}
};

// Глобальный массив объектов Master
const int numMasters = 5;
Master masters[numMasters] = {
    Master("Ремонт крупной бытовой техники", 4, 3000),
    Master("Ремонт мелкой бытовой техники", 2, 1000),
    Master("Ремонт цифровой техники", 2, 500),
    Master("Ремонт электро-инструментов", 2, 200),
    Master("Подключение и установка", 3, 1500)
};

// Объявление функций, чтобы их можно было вызывать из main()
void order(vector<string>& cart);
void menu();
string getCouponDiscount(const string& coupon);
void read_file(string cin_file);
int start();
void repeat();

// Главная функция
int main() {
    setlocale(LC_ALL, "Russian");
    start();

    return 0;
}

// Основное меню выбора
int start() {
    string userName;
    ofstream users;
    ofstream orders;
    ofstream sales;

    cout << "\033[2J\033[1;1H";

// Главное меню
    cout << "Спасибо, что обратились к нам!" << endl;
    cout << "1 - Наши услуги" << endl;
    cout << "2 - Наши последние клиенты" << endl;
    cout << "3 - Наши последние заказы" << endl;
    cout << "4 - Скидки для вас" << endl;
    cout << "5 - Оформить заказ" << endl;
    cout << "6 - Выйти" << endl;

    unsigned long long numUser;

    while (!(cin >> numUser) || (cin.peek() != '\n')) {
        cin.clear();
        while (cin.get() != '\n');
        cout << "Вы ввели неверное число, выберите вариант от 1 до 6: ";
    }

    // Действия после выбора пользователя
    // Наши услуги
    if (numUser == 1) {
        menu();
        repeat();
    }
    // Наши последние клиенты
    else if (numUser == 2) {
        read_file("clients.txt");
        repeat();
    }
    // Наши последние заказы
    else if (numUser == 3) {
        read_file("orders.txt");
        repeat();
    }
    // Скидки для вас
    else if (numUser == 4) {
        read_file("sales.txt");
        repeat();
    }
    // Оформить заказ
    else if (numUser == 5) {
        vector<string> cart; // Создаем вектор для хранения заказов
        order(cart); // Передаем вектор по ссылке для сохранения заказов
        repeat();
    }
    else if (numUser == 6) {
        cout << "Завершение задачи";
    }

    else {
        cout << "В меню можно вводить только от 1 до 6" << endl;
        start();
    }


    return 0;
}

// Функция для перехода в главное меню по выбору пользователя
void repeat() {
    cout << "Вернуться в меню? (Y/N)" << endl;
    char Yes_No = 'y';
    cin >> Yes_No;
    if (Yes_No == 'Y' || Yes_No == 'y') {
        cout << "\n" << endl;
        start();
    }
    else if (Yes_No == 'n' || Yes_No == 'N') {
        cout << "Завершение задачи";
    }
    else {
        repeat();
    }
}

void read_file(string cin_file) {
    ifstream file(cin_file); // Открытие файла для чтения
    string line;

    if (file.is_open()) {
        // Чтение файла построчно и вывод содержимого на экран
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close(); // Закрытие файла после использования
    }
    else {
        cerr << "Невозможно открыть файл" << endl;
    }
}

// Определение функции menu()
void menu() {
    cout << "Доступное меню услуг:" << "\n" << endl;
    for (int i = 0; i < numMasters; ++i) {
        cout << "Услуга " << i + 1 << ":" << endl;
        cout << "Наименование: " << masters[i].name << endl;
        cout << "Время: " << masters[i].time << " часа" << endl;
        cout << "Цена: " << masters[i].price << " рублей" << endl;
        cout << endl;
    }
}

// Определение функции order()
void order(vector<string>& cart) { // Принимаем вектор по ссылке для сохранения заказов
    string userName;
    ofstream users; // Заменяем ofstream на ifstream
    ofstream orders;
    int price = 0;

    menu(); // Показываем меню обслуживания

    cout << "Напишите ваше имя на латинице" << endl;
    cin >> userName;

    // Запись имени клиента в файл clients.txt
    users.open("clients.txt", ios::app);
    if (users.is_open()) {
        users << userName << endl;
    }

    // Начало записи заказа клиента в orders.txt
    orders.open("orders.txt", ios::app);
    if (orders.is_open()) {
        orders << "---" << endl;
        orders << "Имя: " << userName << endl;
    }

    // Заказ обслуживания
    char userWant = 'y'; // Используем символьный тип для ответа пользователя
    while (userWant == 'y' || userWant == 'Y') { // Проверяем на 'y' или 'Y' для продолжения цикла
        cout << "Выберите обслуживание мастера (введите её номер), которое вам нужно" << endl;
        int selectUser;
        cin >> selectUser;
        if (selectUser < 1 || selectUser > numMasters) {
            cout << "Вы ввели неверное число" << endl;
        }
        else {
            cart.push_back(masters[selectUser - 1].name); // Добавляем название выбранного обслуживания в корзину
            price += masters[selectUser - 1].price;
        }

        cout << "Нужно ещё обслуживание? (y/n)" << endl;
        cin >> userWant;

        // Добавляем проверку, чтобы выйти из цикла, если пользователь ввел 'n' или 'N'
        if (userWant != 'y' && userWant != 'Y') {
            // Выводим список выбранного обслуживания в файл заказов
            for (const auto& master: cart) {
                orders << "Услуга: " << master << endl;
            }
            break;
        }
    }

    orders << "Цена заказа: " << price << " рублей" << endl;

    // Проверка наличия скидки у покупателя
    cout << "У Вас есть купон на скидку? (y/n)" << endl;
    char userSale;
    cin >> userSale;
    if (userSale == 'y' || userSale == 'Y') {
        // Запрос купона у пользователя
        cout << "Введите купон: ";
        string userCoupon;
        cin >> userCoupon;

        // Получение и вывод скидки по купону
        string userDiscount = getCouponDiscount(userCoupon);
        int discount = stoi(userDiscount);

        price -= price * discount / 100;
        orders << "Цена заказа со скидкой: " << price << " рублей" << endl;
    }


    // Заканчиваем запись заказа клиента и закрываем файл
    orders << "---" << "\n" << endl;
    orders.close();
}

string getCouponDiscount(const string& coupon) {
    ifstream file("sales.txt"); // Открытие файла с купонами и скидками для чтения
    map<string, string> coupons; // Контейнер для хранения купонов и скидок

    if (!file.is_open()) {
        cerr << "Не получилось открыть файл." << endl;
        return "Error: Не получилось открыть файл.";
    }

    // Чтение купонов и скидок из файла
    string fileCoupon, discount;
    while (file >> fileCoupon >> discount) {
        coupons[fileCoupon] = discount;
    }

    file.close(); // Закрытие файла

    // Поиск скидки по купону
    auto it = coupons.find(coupon);
    if (it != coupons.end()) {
        return it->second;
    }
    else {
        return "Купон не найден.";
    }
}
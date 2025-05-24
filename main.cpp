#include <iostream>
#include <tuple>
#include "math.h"
#include "crypto.h"
#include <cstdint>
#include <vector>

using namespace std;

enum class CryptoOption {
    FERMAT = 1,
    EXTENDED_EUCLID,
    INVERSE_MOD,
    ELGAMAL,
    CONTINUED_FRACTION,
    ATTACK_SIMULATION,
    EXIT = 0
};

int main() {
    int choice;
    do {
        cout << "\n1. Реализация a^x mod p через теорему Ферма\n";
        cout << "2. Алгоритм Евклида для вычисления с*d mod m=1 (через u и v)\n";
        cout << "3. Алгоритм Евклида для вычисления взаимообратного числа с^-1 mod m=d\n";
        cout << "4. Шифрование алгоритмом Эль-Гамаля\n";
        cout << "5. Решение уравнение через цепную дробь\n";
        cout << "6. Эмуляция атаки\n";
        cout << "0. Выход\n";
        cout << "Выберите опцию: ";
        cin >> choice;

        try {
            switch(static_cast<CryptoOption>(choice)) {
                case CryptoOption::FERMAT: {
                    try {
                        uint64_t a, x, p;
                        cout << "Введите a: ";
                        cin >> a;
                        cout << "Введите x: ";
                        cin >> x;
                        cout << "Введите p: ";
                        cin >> p;

                        if (!is_prime(p)) {
                            throw std::invalid_argument("p должно быть простым.");
                        }

                        if (gcd(a, p) != 1) {
                            throw std::invalid_argument("a и p должны быть взаимно просты.");
                        }

                        cout << "Результат (Ферма): " << fermat_method(a, x, p) << endl;
                        cout << "Результат (Бинарный): " << binary_exponentiation(a, x, p) << endl;

                        if (fermat_method(a, x, p) != binary_exponentiation(a, x, p)) {
                            throw std::runtime_error("Алгоритмы дали разные результаты.");
                        } else {
                            cout << "Результаты совпадают!" << endl;
                        }
                    } catch (const std::exception& e) {
                        cout << "Ошибка: " << e.what() << endl;
                    }
                    break;
                }
                case CryptoOption::EXTENDED_EUCLID: {
                    try {
                        int c, m;
                        cout << "Введите число c: ";
                        cin >> c;
                        cout << "Введите число m: ";
                        cin >> m;

                        auto result = Euclid(c, m);
                        cout << "u = " << get<1>(result) << ", v = " << get<2>(result) << endl;
                        cout << "Проверка: " << c << " * " << get<1>(result) << " + " << m << " * " << get<2>(result)
                             << " = " << c * get<1>(result) + m * get<2>(result) << endl;
                    } catch (const std::exception& e) {
                        cout << "Ошибка: " << e.what() << endl;
                    }
                    break;
                }
                case CryptoOption::INVERSE_MOD: {
                    try {
                        int c, m;
                        cout << "Введите число c: ";
                        cin >> c;
                        cout << "Введите модуль m: ";
                        cin >> m;

                        auto [d, u, v] = Euclid(c, m);

                        if (d != 1) {
                            throw std::runtime_error("Обратного элемента не существует (НОД ≠ 1)");
                        }

                        int inverse = (u % m + m) % m;
                        cout << "Обратный элемент d = " << inverse << endl;
                        cout << c << "^-1 mod " << m << " = " << inverse << endl;
                    } catch (const std::exception& e) {
                        cout << "Ошибка: " << e.what() << endl;
                    }
                    break;
                }
                case CryptoOption::ELGAMAL: {
                    try {
                        uint64_t p, k, g, x;
                        cout << "Введите значения для генерации открытого ключа" << endl;
                        cout << "Введите p (простое число): ";
                        cin >> p;
                        cout << "Введите k (случайное число<p): ";
                        cin >> k;
                        cout << "Введите g (генератор < p): ";
                        cin >> g;
                        cout << "Введите x (закрытый ключ): ";
                        cin >> x;
                        cin.ignore();

                        if (!is_prime(p)) {
                            throw std::invalid_argument("p должно быть простым числом.");
                        }

                        uint64_t y = fast_pow(g, x, p);
                        cout << "Открытым ключом является значение: " << y << endl;

                        string message;
                        cout << "Введите сообщение для шифрования: ";
                        getline(cin, message);

                        auto encrypted = encrypt(message, p, k, g, y);
                        cout << "\nЗашифрованное сообщение:\n";
                        for (const auto& pair : encrypted) {
                            cout << "(" << pair.first << ", " << pair.second << ") ";
                        }

                        string decrypted = decrypt(encrypted, p, x);
                        cout << "\nРасшифрованное сообщение: " << decrypted << endl;
                    } catch (const std::exception& e) {
                        cout << "Ошибка: " << e.what() << endl;
                    }
                    break;
                }
                case CryptoOption::CONTINUED_FRACTION: {
                    try {
                        uint64_t p, q;
                        cin >> p;
                        cout << "/" << endl;
                        cin >> q;
                        vector<uint64_t> result = continuedFraction(p, q);
                        cout << p << "/" << q << " в виде цепной дроби = [";
                        for (size_t i = 0; i < result.size(); i++) {
                            cout << result[i];
                            if (i + 1 < result.size()) cout << ", ";
                        }
                        cout << "]" << endl;

                        cout << "\nРешение уравнения 1256a + 847b = 119 в целых числах:" << endl;
                        int a_coeff = 1256;
                        int b_coeff = 847;
                        int c = 119;

                        auto [gcd_val, x0, y0] = Euclid(a_coeff, b_coeff);

                        if (c % gcd_val != 0) {
                            throw std::runtime_error("Решений нет, так как НОД не делит правую часть.");
                        } else {
                            int factor = c / gcd_val;
                            int x_part = x0 * factor;
                            int y_part = y0 * factor;

                            cout << "Частное решение: a = " << x_part << ", b = " << y_part << endl;
                            cout << "Общее решение:" << endl;
                            cout << "a = " << x_part << " + " << (b_coeff / gcd_val) << " * k" << endl;
                            cout << "b = " << y_part << " - " << (a_coeff / gcd_val) << " * k" << endl;
                            cout << "где k — любое целое число." << endl;
                        }
                    } catch (const std::exception& e) {
                        cout << "Ошибка: " << e.what() << endl;
                    }
                    break;
                }
                case CryptoOption::ATTACK_SIMULATION: {
                    try {
                        uint64_t p, k, g, x;
                        cout << "Введите p (простое число): ";
                        cin >> p;
                        cout << "Введите k (cессионый ключ < p): ";
                        cin >> k;
                        cout << "Введите g (генератор < p): ";
                        cin >> g;
                        cout << "Введите x (закрытый ключ): ";
                        cin >> x;
                        cin.ignore();

                        uint64_t y = fast_pow(g, x, p);
                        cout << "Открытый ключ (y): " << y << endl;

                        string message;
                        cout << "Введите сообщение: ";
                        getline(cin, message);

                        auto encrypted = encrypt(message, p, k, g, y);

                        cout << "Зашифрованное сообщение:\n";
                        for (const auto& pair : encrypted)
                            cout << "(" << pair.first << ", " << pair.second << ") ";
                        cout << endl;

                        string decrypted = decrypt(encrypted, p, x);
                        cout << "Расшифрованое сообщение: " << decrypted << endl;

                        cout << "\nЭмуляция атаки...\n";
                        string attacked = attack(encrypted, p, g, y);
                        if (!attacked.empty())
                            cout << "Результат атаки: " << attacked << endl;
                    } catch (const std::exception& e) {
                        cout << "Ошибка: " << e.what() << endl;
                    }
                    break;
                } 
                case CryptoOption::EXIT:
                    cout << "Выход из программы...\n";
                    break;
                default:
                    cout << "Неверный выбор. Попробуйте снова.\n";
            }
        } catch (const std::exception& e) {
            cout << "Необработанная ошибка: " << e.what() << endl;
        } catch (...) {
            cout << "Произошла неизвестная ошибка." << endl;
        }
    } while(choice != 0);

    return 0;
}
# Лабораторная работа №2 «Вычисление значений числовых рядов и функций с заданной точностью»

Необходимо спроектировать и реализовать на языке C **две** программы, позволяющие вычислять
значения некоторой заданной функции.

Программа № 1 должна обеспечивать возможность вычисления значения функции при определённых значениях параметров, указанных пользователем. При этом, пользователь должен иметь возможность указать количество членов ряда, которое необходимо использовать при вычислениях.

Ключевым компонентом программы № 1 должна быть некоторая функция, на вход которой передаются значения параметров и количество членов ряда, необходимое для проведения вычислений.
Возвращаемым значением для указанной функции должно быть вычисленное значение.

Программа № 2 должна обеспечивать возможность вычисления значения функции при определённых значениях параметров, указанных пользователем. При этом, пользователь должен иметь возможность указать точность, с которой должно быть вычислено значение функции.

Ключевым компонентом программы № 2 должна быть некоторая функция, на вход которой передаются значения параметров и точность, с которой необходимо вычислить результат. В качестве результата функция должна возвращать вычисленное значение и количество членов ряда, которое потребовалось вычислить для обеспечения заданной точности (данное значение необходимо вернуть через параметр).

Примечания:

1. Логически законченные части алгоритмов решения задачи должны быть оформлены в виде
отдельных функций с параметрами. Использование глобальных переменных не допускается.

2. Исходные коды программ должны быть логичным образом разбиты на несколько файлов.
3. Программы должны осуществлять проверку корректности вводимых данных и, в случае ошибок, выдавать соответствующие сообщения, после чего продолжать работу.
4. Программа должна корректным образом работать с памятью, для проверки необходимо использовать соответствующие программные средства, например: `valgrind` (при тестировании и отладке программы ее необходимо запускать командой вида `valgrind ./lab2,` а при анализе
производительности — `./lab2`).

## Индивидуальное задание (Вариант №23)

Вычислить значение функции $y = \sqrt[n]{a}$ в точке по итерационной формуле:

$$
y_{i+1} = \frac 1 n ((n-1)y_i + \frac{a}{y^{n-1}_i})
$$

где $y_0 = a$.

### Тип данных

Число с плавающей точкой двойной точности — `double` (спецификатор формата: `%lf`).
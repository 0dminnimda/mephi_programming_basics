# Лабораторная работа № 3 «Работа с массивами данных»

Необходимо спроектировать и реализовать на языке C программу, осуществляющую по запросам
пользователя ввод, обработку и вывод последовательности данных, которая представляется в виде
массива.
Программа должна реализовывать следующую функциональность:

1. Инициализация массива (заполнение массива в цикле).

2. Вставка нового элемента в массив по индексу.
3. Удаление элемента массива по индексу.
4. Обработка данных (в соответствии с индивидуальным заданием).
5. Вывод текущего состояния массива.

Примечания:

1. Взаимодействие программы с пользователем должно быть выстроено с помощью диалогового меню. Штатный способ завершения работы программы — через соответствующий пункт диалогового меню.

2. Программа должна осуществлять проверку корректности вводимых данных и, в случае ошибок, выдавать соответствующие сообщения, после чего продолжать работу.
3. Обрабатываемые последовательности должны быть представлены в виде массива элементов, которые имеют соответствующий тип данных.
4. Память под массивы обрабатываемых данных должна выделяться и освобождаться динамически, с использованием функций `calloc()`, `malloc()`, `realloc()` и `free()` из состава стандартной библиотеки.
5. Использование VLA (массивов переменной длины) не допускается.
6. При удалении элемента массива с указанным индексом, элементы массива с большим индексом должны «сдвигаться влево».
7. При вставке в массив нового элемента по индексу, значение которого превышает максимально допустимое (оно соответствует длине массива), необходимо осуществлять вставку в конец массива.
8. Логически законченные части алгоритма решения задачи должны быть оформлены в виде отдельных функций с параметрами. Использование глобальных переменных не допускается.
9. Исходные коды программы должны быть логичным образом разбиты на несколько файлов (необходимо использовать как `*.c`-файлы, так и `*.h`-файлы).
10. Согласно условиям индвидуального задания, может требоваться наличие нескольких исходных последовательностей. В таком случае, пользователь должен иметь возможность интерактивного взаимодействия с каждой из них.
11. Программа должна корректным образом работать с памятью, для проверки необходимо использовать соответствующие программные средства, например: `valgrind` (при тестировании и отладке программы необходимо запускать её командой вида `valgrind ./lab3`).

## Индивидуальное задание (Вариант №11)

В исходной последовательности вещественных чисел найти те, дробная часть которых, представленная в виде целого числа, превышает по модулю их целую часть. Сформировать из данных чисел
новую последовательность, удалив их из исходной.

### Правила изменения размера выделенной под массив области памяти

Размер выделенной под массив области памяти задаётся пользователем вручную через соответствующие пунты меню.
Любые операции по изменению размера выделенной области памяти выполняются только по явному запросу со стороны пользователя
**36.	Найти частоту степеней вершин и отсортировать вершины по возрастанию степени вершины (пузырьковая сортировка)**
=====================================================================================================================
Программа реализована на основе дз3 представленного здесь https://github.com/4i4urin/fleita/blob/master/graph.c
-------------------------
**Алгоритм**
-----------------------------------------
* Подсчёт стпенеи врешини осущесвляется при добавлении врешин пользователем в функции add
![alt tag](https://github.com/4i4urin/fleita/blob/master/dz_4/add%20(2).png "лол")
При вводе пользователя происходит выделение памяти в двумерный массив и его заролнение в месте с этим заполняется структура title.
В неё записывается имя вершини и добавляется степнь
* Сортировка графа по степени вершин сортировка пузырьком
![alt tag](https://github.com/4i4urin/fleita/blob/master/dz_4/sort_graph.jpg "Да да это код с гитхаба")
Реализация функция swap_line и swap_column 
![alt tag](https://github.com/4i4urin/fleita/blob/master/dz_4/swap.png "Как будто самому сложно файл открыть")
Код функции вывода степеней вершин
![alt tag](https://github.com/4i4urin/fleita/blob/master/dz_4/list.png "Файл frequincy_graph.c если что")
Структурная схема данного алгоритма
![alt tag](https://github.com/4i4urin/fleita/blob/master/dz_4/sort_graph.png "Структурная схема и всё. Без мам пап и кредитов")
* Пример работы программы
Создание графа
![alt tag](https://github.com/4i4urin/fleita/blob/master/dz_4/input_graph.png "Код работает вот это прикол")
Визулизация начального графа
![alt tag](https://github.com/4i4urin/fleita/blob/master/dz_4/visualization_1.png "Ля какой")
Сортировка графа и вывод степеней вершин
![alt tag](https://github.com/4i4urin/fleita/blob/master/dz_4/sorting.png "Вот это цифры!!!1!")
Визуализация отсортированного графа
![alt tag](https://github.com/4i4urin/fleita/blob/master/dz_4/visualization_2.png "Красивый как горы на кавказе")
* P.S Структурная схема функции main с пояснениями основных алгоритмов
![alt tag](https://github.com/4i4urin/fleita/blob/master/dz_4/main.png "Не зря же делал")






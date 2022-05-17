# Задача 1
Серилизация и десерилизация меньше чем за `О(N^2)` двусвязного списка, в котором есть ссылки на:
* Предыдущий елемент
* Следующий елемент
* Рандомный елемент

## Идея решения
## Изменения
Я понял, я перезаписывал node->Data для удобства ориентации и данные обратно не возвращал, исправил.
Ещё проблема была в сохраниении строк с `\n` (но на всякий случай есть еще одна запасная идея как точно должно работать). Теперь сохраняю ещё длину ListNode->Data чтобы точно знать какой длины строку нужно десерилизовать и соответственно десерилизую пока не забьем всю длинну. 
Добавил функцию `replaseAll` для того, чтобы при просмотре данных изменять `\n` на `\\n`.

### Сериализация
* Проходимся по всему списку и сохраняем список в словарь, а сам в самом списке значение `Data` меняем на ключ в словаре (где находится этот элемент)
* Проходимся ещё раз и если есть ссылка на рандомный элемент, то берем поле `Data` этого рандомного элемента, а там у нас уже ключ этого элемента в таблице и таким образом сохраняем в словаре ещё одно поле `Rand` 
* Проходимся по словарю и сохраняем его в вид [псевдоЯМЛ](data.myaml)
```
1:
Rand: nullptr
LengthData: 15
Data:
data_a
data_a2

2:
Rand: 2
LengthData: 14
Data:
data_b
data_b2
3:
Rand: 1
LengthData: 8
Data:
data_c	

4:
Rand: 2
LengthData: 6
Data:
data_d
```
### Десериализация
* Читаем файл и переводим его в два словаря
1. Словарь где хранятся ключи к рандомным элементам
2. Словарь где хранятся ListNode с пустыми ссылками и заполненной датой
* Проходимся одновременно по двум словарям и расставляем ссылки на все элементы

#### Вывод программы (для проверки)
```
Before serialization: 
Data: data_a\ndata_a2 Next: data_b\ndata_b2 Prev: nullptr Rand: nullptr
Data: data_b\ndata_b2 Next: data_c      \n Prev: data_a\ndata_a2 Rand: data_b\ndata_b2
Data: data_c    \n Next: data_d Prev: data_b\ndata_b2 Rand: data_a\ndata_a2
Data: data_d Next: nullptr Prev: data_c \n Rand: data_b\ndata_b2
After deserialization:
Data: data_a\ndata_a2 Next: data_b\ndata_b2 Prev: nullptr Rand: nullptr
Data: data_b\ndata_b2 Next: data_c      \n Prev: data_a\ndata_a2 Rand: data_b\ndata_b2
Data: data_c    \n Next: data_d Prev: data_b\ndata_b2 Rand: data_a\ndata_a2
Data: data_d Next: nullptr Prev: data_c \n Rand: data_b\ndata_b2
```
# Задача 2
[Behavior Tree](imgs/BevaviorTree.png)




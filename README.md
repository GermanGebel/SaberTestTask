# Задача 1
Серилизация и десерилизация меньше чем за `О(N^2)` двусвязного списка, в котором есть ссылки на:
* Предыдущий елемент
* Следующий елемент
* Рандомный елемент

## Идея решения
## Изменения
Добавил функцию `replaseAll` для того, чтобы при сериализации\десериализации изменять в данных `\n` на `\\n` и обратно для удобства записи\чтения из файла и чтобы данные не портились.

### Сериализация
* Проходимся по всему списку и сохраняем список в словарь, а сам в самом списке значение `Data` меняем на ключ в словаре (где находится этот элемент)
* Проходимся ещё раз и если есть ссылка на рандомный элемент, то берем поле `Data` этого рандомного элемента, а там у нас уже ключ этого элемента в таблице и таким образом сохраняем в словаре ещё одно поле `Rand` 
* Проходимся по словарю и сохраняем его в вид [псевдоЯМЛ](data.myaml)
```
1:
	Rand: nullptr
	Data: data_a\ndata_a2
2:
	Rand: 2
	Data: data_b\ndata_b2
3:
	Rand: 1
	Data: data_c	\n
4:
	Rand: 2
	Data: data_d
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




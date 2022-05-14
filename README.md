# Задача 1
Серилизация и десерилизация меньше чем за `О(N^2)` двусвязного списка, в котором есть ссылки на:
* Предыдущий елемент
* Следующий елемент
* Рандомный елемент

## Идея решения
### Сериализация
* Проходимся по всему списку и сохраняем список в словарь, а сам в самом списке значение `Data` меняем на ключ в словаре (где находится этот элемент)
* Проходимся ещё раз и если есть ссылка на рандомный элемент, то берем поле `Data` этого рандомного элемента, а там у нас уже ключ этого элемента в таблице и таким образом сохраняем в словаре ещё одно поле `Rand` 
* Проходимся по словарю и сохраняем его в вид [псевдоЯМЛ](data.myaml)
```
1:
	Data: data_a
	Rand: nullptr
2:
	Data: data_b
	Rand: 2
3:
	Data: data_c
	Rand: 1
4:
	Data: data_d
	Rand: 2
```
### Десериализация
* Читаем файл и переводим его в два словаря
1. Словарь где хранятся ключи к рандомным элементам
2. Словарь где хранятся ListNode с пустыми ссылками и заполненной датой
* Проходимся одновременно по двум словарям и расставляем ссылки на все элементы

#### Вывод программы (для проверки)
```
Before serialization:
Data: data_a Next: data_b Prev: nullptr Rand: nullptr
Data: data_b Next: data_c Prev: data_a Rand: data_b
Data: data_c Next: data_d Prev: data_b Rand: data_a
Data: data_d Next: nullptr Prev: data_c Rand: data_b
After deserialization:
Data: data_a Next: data_b Prev: nullptr Rand: nullptr
Data: data_b Next: data_c Prev: data_a Rand: data_b
Data: data_c Next: data_d Prev: data_b Rand: data_a
Data: data_d Next: nullptr Prev: data_c Rand: data_b
```
# Задача 2
[Behavior Tree](imgs/BevaviorTree.png)




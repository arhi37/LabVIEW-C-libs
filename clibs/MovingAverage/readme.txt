﻿Модуль MovingAverage реализует метод скользящего среднего.

Можно использовать двумя способами:

1) Класс movingAverage
Создаёте экземпляр класса, устанавливаете период скользящего среднего при помощи метода
	void setPeriod(qint32	period);
и начинаете работу. По умолчанию период равняется 5. При изменении периода все значения нового массива значений устанавливаются в значение среднего по прошлым данным. 

Пример:
Если у вас был поток данных 3 4 3 5 7 4 2 5 7 8 5 5, а период равнялся 5, то скользящее среднее равняется (5+7+8+5+5)/5 = 6. Когда вы измените период, скажем на 7, состояние объекта класса movingAverage станет таким, как если бы поток был следующим: 6 6 6 6 6.

Есть возможность сбросить историю объекта методом
	void reset(double count/* = 0*/);
в данном случае, если вы не задаёте параметр count, его значение принимается за 0.

Пример:
Если у вас был поток данных 3 4 3 5 7 4 2 5 7 8 5 5, а период равнялся 5, то в памяти объект хранит только необходимые, последние 5 значений, а именно 5 7 8 5 5. Если вызвать метод reset(3), то все значения в памяти станут равны 3, соответственно объект примет состояние, как если бы поток данных был 3 3 3 3 3.

Добавить очередное значение можно методом void addPoint(double point);

Узнать текущее значение скользящего среднего можно при помощи метода double getValue();

2) Обёртка Си.

В случае dll нет возможности напрямую использовать классы и объекты, поэтому реализован другой механизм.
Ниже представлены ф-ии этого механизма:
	qint32 initMovingAverage(); - создаёт в памяти объект скользящего среднего и возвращает его идентификатор
	void removeMovingAverage(qint32 movAvId); - удаляет объект из памяти
	Следующие ф-ии - всего лишь обёртки к методам класса, параметр movAvId - идентификатор объекта.
	void addPoint(qint32 movAvId, double point);
	double getValue(qint32 movAvId);
	void setPeriod(qint32 movAvId, qint32	period);
	void reset(qint32 movAvId, double count/* = 0*/);

При помощи идентификаторов можно использовать множество объектов скользящего среднего одновременно.
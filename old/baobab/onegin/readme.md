# Приложение Онегин.

## Что может?

* Может проводить сортировку по прямой и обратной компарации слов в тексте.
* Работать с разными кодировками
* Писать бредостихотворения
* Работать в GUI режиме при использовании подмодуля Elix в фреймворке Ellipse

## Зависимости

* Фреймворк Ellipse
* Подмодуль фреймворка Ellipse / Elix (для работы с графикой)


## Как собрать?

**Перед сборкой проекта, обязательно проинициализируй репозиторий подмодуля Ellipse и Elix!**

Для начала убедись что у тебя установлена система сборки CMake и генератор сборки Ninja

* Для конфигурации системы сборки:

```shell
cmake -B build
```

* Для сборки проекта:

```shell
cmake --build build
```

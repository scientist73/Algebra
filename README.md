# Algebra

## Пару слов о проекте
Данный фреймворк пишется одним программистом исключительно в учебных целях. Основная цель - научиться разрабатывать архитектуру ПО и программировать на c++. 

## О фреймворке
Algebra - фреймворк, поддерживающий алгебраические операции. Он поддерживает работу с различными скалярными алг. типами (например, дейсвительные числа или многочлены). Имеется парсер, способный упросить выражение. Так же имеется модуль для решения уравнений.

## Состояние проекта
09.09.24 - реализованна основная функциональность, написаны и проходят модульные тесты. В дальшейшем планируется:
* рефакторинг кода
* обработка исключений
* работа над пространствами имен
* написания документации
* настройки CI/CD

## Модули фрейворка

### Краткий обзор модулей
Здесь указаны все модули фреймворка с их кратким описанием. За подробными примера кода можно обратиться к модульным тестам.

#### Планируемые модули
1) num::scalar::ScalarType - скаляр
1) num::scalar::ScalarConventer - преобразование скаляра в другие типы
1) EquationSolver -- решение алгебраических уравнений

#### Модули в разработке
1) по сути все нижеперечисленные модули хоть и работают, но находятся все еще в разработке

#### Реализованные модули
1) num::NumType - произвольный алг. тип с динамической типизацией
1) num::Complex - комплексное число
1) num::Real - действительное число
1) calc::tok::TokenType - токены
1) calc::tok::TokenGenerator - генератор токенов (вспомогательный модуль)
1) calc::lex::Lexer - лексер
1) calc::Calculator - упрощение мат. выражений (может использоваться как калькулятор)
1) calc::pars::Parser - парсер

## num
В данном модуле представлены 4 подмодуля, которые могут быть использованы независимо друг от друга. Центральным модулем фреймворка является NumType, представляющий элемент произвольной алгебры. В данной архитектуре несложно будет в будущем добавить Polynomial для работы с многочленами.

Все числовые типы принимают в качестве параметра шаблона тип скаляра для арифметических операций. Этот тип должен быть согласован у всех числовых типов (однако, ошибиться случайно не получится, тк если они не будут согласованы, то код просто не пройдет компиляцию). Данное решение было введено для большой гибкости при работе со скалярными типами (см. ScalarType).

### scalar
Базовый модуль для всех числовых типов. Был введен для потенциальной возможности работы с большими числами и числами произвольной точности. Например, можно написать класс BigIntScalarType и передать его числовому типу, скажем Real, т.е. ``` Real<BigIntScalarType> ```. Однако, если точности встроенных типов достаточно, то ScalarType можно и не использовать ``` Real<double> ```.

### Real
Модуль, реализующий действительные числа. Имеется специализация шаблона для типа double. Пример работы с классом Real:

```
#include <iostream>
#include "Real.h"


int main()
{
    Real<double> var1(23.6);
    Real<double> var2(12.6);

    Real<double> var3 = var1 * var2;

    std::cout << std::to_string(var1.real()) << " * " << std::to_string(var2.real()) << " = ";
    std::cout << std::to_string(var3.real()) << std::endl;
    // output: 23.600000 * 12.600000 = 297.360000

    return 0;
}
```

### Complex
Модуль, реализующий комплексные числа. Модуль полностью повторяет функционал std::complex. Более того, на данный момент весь модуль описывается одним файлом:

```
#pragma once
#include<complex>

namespace alg
{
    namespace num
    {
        #define Complex std::complex
        
    } // namespace num
} // namespace alg
```

### NumType
Модуль, реализующий число произвольной алгебры с динамической типизацией. На данный момент поддерживаются две алгебры: комплексные и действительные числа. Реализовано автоматическое преобразование типов при выполнении алг. операций. Например при сложении действительного и комплесного числа результат будет представлен в виде комплексного числа. Приведу пример работы с модулем

```
#include <iostream>
#include "NumType.h"


int main()
{
    NumType<double> var1(Real<double>(4.5));
    NumType<double> var2(Complex<double>(5.6, 23));

    NumType<double> var3 = var1 / var2;

    std::cout << var1.getString() << " / " << "(" << var2.getString() << ")" << " = ";
    std::cout << var3.getString() << std::endl;
    // output: 4.500000 / (5.600000 + 23.000000i) = 0.044971 + (-0.184703i)

    return 0;
}
```


## calc
Данный модуль предоставляет классы для упрощения алгебраических выражений, представленных в виде строки (в будущем несложно будет добавить чтение из файла, если на то будет необходимость). Лексер и парсер независимы друг от друга и зависят только от общих токенов, представленных в модуле tok. Центральным в этом модуле явлется Calculator, инкапсулярующий всю основную логику (по сути данный подмодуль является фасадом), поэтому использовать лексер и парсер напрямую нет необходимости.

### Calculator
Модуль для упрощения алг. выражений. Интерфейс довольно интуитивный: необходимо задать ввод setupInput...() и вызвать метод calculate(). Пример:

```
#include "Calculator.h"
#include "NumType.h"

using alg::calc::Calculator;


int main()
{
    Calculator<double> calc;
    calc.setupInputString("(4+6i)/(1-2i)");
    NumType<double> res = calc.calculate();

    /*
        Doing sthg with the result
    */

    return 0;
}
```


### tok
Модуль для создания токенов для парсера и лексера

#### TokenType
Модуль, состоящий из простых структур токенов. Имеются простые структуры для определенных видов токенов (например, OperatorTokenType для токенов операторов +, -, ...). Пример создания токенов:

```
TokenType(OperatorTokenType(OperatorTokenType::OPERATOR::PLUS));
TokenType(NumTokenType(NumTokenType::NUM::REAL, "5"));
```

#### TokenGenerator
Вспомогательный модуль для создания токенов. Пример:

```
TokenGenerator::constructParam(ParamTokenType::PARAM::ROUND_OPEN);
TokenGenerator::constructTermination(TerminationTokenType::TERMINATION::END_OF_LINE);
```

### lex
Модуль предоставляющий лексер для токенизации ввода (будь то строка или поток). Данная реализация основана на gnu flex лексере. Однако модуль слабо привязан к внешним зависимостям и в случае необходимости заменить их не составит труда.

#### Lexer
Модуль, инкапсулирующий лексер (или же сканер). Для сканирования ввода необходимо его задать с помощью функции setupInput...() (на данный момент есть только ввод в виде строки setupInput...(), но добавить другой не составит труда) и вызвать функцию closeInput() после сканирования. При переключении ввода нет необходимости явно вызывать closeInput(), а просто вызвать setupInput...(). Для получения следующего токена необходимо вызвать функцию getNextToken(). Пример:

```
#include "Lexer.h"
#include "TokenType.h"

int main()
{
    Lexer lexer;
    lexer.setInputString("4.5i * tan(x)");

    do
    {
        TokenType token = getNextToken();
        /* 
            Doing smth with this token
        */
        if (token == TokenType(TerminationTokenType(TerminationTokenType::TERMINATION::END_OF_INPUT)))
            break;
    } while (true);

    lexer.closeInput();
    
    return 0;
}
```

Описание интерфейса Lexer:
* setupInputString - задание ввода в виде строки
* closeInput - функцию необходимо вызвать после работы с лексером
* getInputType - получить вид ввода (строка, поток и тд)
* getNextToken - получить следующий токен. Если токенов больше нет, то возвращается терминирующих токен TokenType(TerminationTokenType(TerminationTokenType::TERMINATION::END_OF_INPUT)) (если после него вызвать эту функцию, то будет брошено исключение std::runtime_error). Если ввод не задан, то выбрасывается исключение std::runtime_error.

### pars
Модуль для парсинга токенов. Данная реализация основана на gnu bison. В связи с этим класс парсера хоть и я является шаблонным, но ограничен лишь типом double. В будущем планируется переписать данный модуль с помощью Boost::Spirit.

#### Parser
Модуль представляющий собой непосредственно парсер. Для парсинга необходимо добавить токены с помощью pushToken() с завершающим (терминирующим токеном) и вызвать метод parse(). Пример:

```
#include "Parser.h"
#include "TokenType.h"

#define REAL_TOKEN(real_str) TokenType(NumTokenType(NumTokenType::NUM::REAL, real_str))
#define PLUS_TOKEN TokenType(OperatorTokenType(OperatorTokenType::OPERATOR::PLUS))
#define END_OF_INPUT_TOKEN TokenType(TerminationTokenType(TerminationTokenType::TERMINATION::END_OF_INPUT))

int main()
{
    Parser<double> parser;
    std::vector<TokenType> tokens({REAL_TOKEN("5"), PLUS_TOKEN, REAL_TOKEN("5"), END_OF_INPUT_TOKEN});

    for (auto token : tokens)
        parser.pushToken(token);
    NumType<double> res = parser.parse();

    return 0;
}
```

## Примечание
На данный момент не реализована обработка исключений, возможно не хватает некоторых "удобных" для пользователей функций.
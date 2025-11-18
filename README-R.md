<div align="center">

# Реализация языка программирования Super Biba-Boba language на C++
  ![C++](https://img.shields.io/badge/C++-23-blue?style=for-the-badge&logo=cplusplus)
  ![CMake](https://img.shields.io/badge/CMake-3.20+-green?style=for-the-badge&logo=cmake)
  ![Testing](https://img.shields.io/badge/Google_Test-Framework-red?style=for-the-badge&logo=google)

</div>

- Данный проект представляет реализацию языка программирования `ParaCL` из курса C++ от К.И. Владимирова.

## 📖 Введение
Разработка собственного языка программирования представляет собой фундаментальную задачу в компьютерных науках, позволяющую на практике исследовать принципы вычислений. Создание языка с C-подобным синтаксисом позволяет лучше понять архитектуру компиляторов. Этот процесс раскрывает внутреннюю логику трансляции высокоуровневых конструкций в промежуточные представления.

Ручная реализация лексического и синтаксического анализаторов сопряжена с существенными сложностями. Такой подход требует написания и отладки низкоуровневого кода, что особенно проблематично при модификации грамматики. Обработка приоритета операторов и ассоциативности становится нетривиальной задачей, делая поддержку языка чрезвычайно трудоёмкой.

Использование инструментов `Flex` и `Bison` позволяет автоматизировать создание анализаторов. `Flex` генерирует эффективный сканер на основе регулярных выражений, а `Bison` строит LALR(1)-парсер, выполняющий синтаксический анализ с опережающим просмотром в один токен. Этот подход значительно ускоряет разработку, обеспечивая надёжность и лёгкость модификации грамматики.

## 🔑 Методика
Написание фронтенда языка программирования включает в себя несколько задач:
1) составление грамматики;
2) разбиение программы на токены, лексический анализ;
3) составление `AST`, синтаксический анализ.

Для описания грамматики подойдёт формат `РБНФ` [1]. Для генерации лексического и синтаксического анализаторов можно использовать `Flex` и `Bison`.
Для выполнения программы можно написать интерпретатор, который при помощи абстракции `Visitor'a` пройдёт по `AST` и просимулирует выполнение программы. 

## 👨‍💻 Ход работы
### Описание грамматики

Составлена грамматика целевого языка программирования. Ниже приведено её описание в формате, близком к `РБНФ` [1]:

<details>
<summary>Грамматика</summary>
  
```
Program        ::= StmtList EOF

StmtList       ::= /* empty */ | StmtList Statement

Statement      ::= AssignmentStmt ';' | InputStmt ';' | IfStmt | WhileStmt | PrintStmt ';' | BlockStmt

BlockStmt      ::= '{' StmtList '}'
AssignmentStmt ::= Var '=' Expression
InputStmt      ::= Var '=' '?'
IfStmt         ::= 'if'    '(' Expression ')' Statement [ 'else' Statement ]
WhileStmt      ::= 'while' '(' Expression ')' Statement
PrintStmt      ::= 'print' Expression

Expression     ::= Equality
Equality       ::= Relational ( ( '==' | '!=' ) Relational )*
Relational     ::= AddSub ( ( '<' | '>' | '<=' | '>=' ) AddSub )*
AddSub         ::= MulDiv ( ( '+' | '-' ) MulDiv )*
MulDiv         ::= Unary  ( ( '*' | '/' ) Unary )*
Unary          ::= '-' Unary | Primary
Primary        ::= '(' Expression ')' | Var | Number

Var            ::= [A-Za-z_][A-Za-z0-9_]*
Number         ::= [0-9]+
EOF            ::= __end_of_file__
```

</details>

### Реализация лексического анализатора
На первом этапе исследования данной проблемы началась разработка классов токенов, узлов, лексера и парсера:
<details>
<summary>Показать блок кода</summary>
  
```C++
class Parser {
    std::size_t pc_ = 0;
    std::unique_ptr<Node> root_{nullptr};
  public:
    bool parse(const std::vector<std::unique_ptr<Token>> &tokens);
  private:
    /// select a statement and run its handler
    std::unique_ptr<Node> get_statement(const std::vector<std::unique_ptr<Token>> &tokens);

    // handlers for different types of operators
    std::unique_ptr<Node> get_assign(const std::vector<std::unique_ptr<Token>> &tokens);
    std::unique_ptr<Node> get_input(const std::vector<std::unique_ptr<Token>> &tokens);

    std::unique_ptr<Node> get_print(const std::vector<std::unique_ptr<Token>> &tokens);

    std::unique_ptr<Node> get_if(const std::vector<std::unique_ptr<Token>> &tokens);
    std::unique_ptr<Node> get_while(const std::vector<std::unique_ptr<Token>> &tokens);

    ...
};
```
</details>

Однако в процессе разработки оказалось, что существуют инструменты для генерации лексических и синтаксических анализаторов `Flex` и `Bison`. Решено использовать эти инструменты благодаря их значительным преимуществам:

- **Автоматизация** — исключает необходимость ручной реализации парсера
- **Надежность** — снижение количества ошибок при синтаксическом анализе и повышение устойчивости
- **Поддержка сложных грамматик** — встроенная обработка приоритета и ассоциативности операторов
- **Быстрая разработка** — изменения грамматики приводят к немедленной перегенерации парсера

Поэтому написан файл с описанием для генерации лексического анализатора [lexer.l](https://github.com/RTCupid/Super_Biba_Boba_Language/blob/main/frontend/src/lexer.l).
В нём определены следующие конструкции:

```l
WHITESPACE    [ \t\r\v]+
ID            [a-zA-Z_][a-zA-Z0-9_]*
NUMBER        [0-9]+
NUMBER1       [1-9]+
ZERO          0
LINE_COMMENT  "//".*
BLOCK_COMMENT "/*"([^*]|\*+[^*/])*\*+"/"
NEWLINE  \n
```

и правила для их обработки:
```y
{WHITESPACE}    { /* skip blanks and tabs */ }
{NEWLINE}       { ++yylineno; }
{LINE_COMMENT}  { /* skip */ }
{BLOCK_COMMENT} { /* skip */ }

"if"            { return process_if();   }
"else"          { return process_else(); }
"while"         { return process_while(); }
"print"         { return process_print(); }
"?"             { return process_input(); }
...
```

Как можно заметить в файле `lexer.l` для обработки правил вызываются некоторые функции. Эти функции определены в классе `Lexer`, который наследуется от
`yyFlexLexer` (см. файл [lexer.hpp](https://github.com/RTCupid/Super_Biba_Boba_Language/blob/main/frontend/include/lexer.hpp)).
Они сохраняют в полях класса `current_lexem` и `current_value`, чтобы в процессе прохождения лексемы можно было вывести.
Планируется, что этот класс будет использоваться в том числе для обработки ошибок. Пример функции для обработки:
```C++
int process_if() {
    current_lexem = "conditional operator";
    current_value = "if";
    return yy::parser::token::TOK_IF;
}
```

В качестве возвращаемого значения используется token из парсера, который генерирует `Bison`, это сделано для совместной работы `Bison` и `Flex`.

### Реализация синтаксического анализатора
Для генерации синтаксического анализатора при помощи `Bison` в соответствующей форме написано описание грамматики [parser.y](https://github.com/RTCupid/Super_Biba_Boba_Language/blob/main/frontend/src/parser.y). 

Функция, через которую осуществляется взаимодействие парсера с лексером:
```C++
int yylex(yy::parser::semantic_type*   yylval,
          yy::parser::location_type*   yylloc,
          language::Lexer*             scanner)
{
    auto tt = scanner->yylex();

    if (tt == yy::parser::token::TOK_NUMBER)
      yylval->build<int>() = std::stoi(scanner->YYText());

    if (tt == yy::parser::token::TOK_ID)
      yylval->build<std::string>() = scanner->YYText();

    return tt;
}
```
Для чисел и переменных сохраняется значение в `yylval`, в остальных случаях возвращается тип токена.

Во время синтаксического анализа строится `AST` (abstract-syntax-tree). 
При помощи введения новых правил для синтаксического анализа реализована иерархия порядка исполнения.

Также это дерево можно посмотреть в графическом представлении при помощи graphviz. Для компиляции изображения необходимо ввести
```bash
dot graph_dump/graph_dump.gv -Tsvg -o graph_dump/graph_dump.svg
```
и мы получим следующее представление дерева (пример)
<div align="center">
  <img src="docs/graph_dump.svg" alt="Dump Banner" width="500">
</div>


### Симулятор
Чтобы симулировать выполнение программы, реализован класс `Simulator` [simulator.hpp](https://github.com/RTCupid/Super_Biba_Boba_Language/blob/main/frontend/include/simulator.hpp), наследующийся от абстрактного класса ASTVisitor:

```C++
// Visitor pattern for AST traversal
class ASTVisitor {
  public:
    virtual ~ASTVisitor() = default;

    virtual void visit(Program &node) = 0;
    virtual void visit(Block_stmt &node) = 0;
    virtual void visit(Assignment_stmt &node) = 0;
    virtual void visit(Input_stmt &node) = 0;
    virtual void visit(If_stmt &node) = 0;
...
};
```

В классе `Simulator` выполняется переопределение виртуальных функций `ASTVisitor`, а также вводится функция для вычисления выражений, которая
использует специальный класс `ExpressionEvaluator` [expr_evaluator.hpp](https://github.com/RTCupid/Super_Biba_Boba_Language/blob/main/frontend/include/expr_evaluator.hpp):

```C++
number_t Simulator::evaluate_expression(Expression &expression) {
    ExpressionEvaluator evaluator(*this);
    expression.accept(evaluator);

    return evaluator.get_result();
}
```

`ExpressionEvaluator` специализируется только на вычислении выражений, содержит поле `result_` для сохранения результата выражения, а также `simulator_` - 
ссылку на симулятор, из которого он был вызван, чтобы иметь доступ к таблице имён.

### Пример программы
Ниже приведён простой пример корректной программы на языке - вычисление n-го `числа Фиббоначи`:

```C
fst = 0;               // тип не требуется, все типы int 
snd = 1;
iters = ?;             // считать со std::cin число и определить переменную
while (iters > 1) {
    tmp = fst;
    fst = snd;
    snd = snd + tmp;
    iters = iters - 1;
}
print snd;             // вывести значение переменной в std::cout
```
### Запуск программы
Клонирование репозитория, сборка и компиляция выполняется при помощи следующих команд:

```
git clone https://github.com/RTCupid/Super_Biba_Boba_Language.git
cd Super_Biba_Boba_Language
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

Запуск программы производится в следующем формате:
```
./build/frontend/frontend <имя файла с программой>
```

## 👥 Создатели проекта

<div align="center">

  <a href="https://github.com/RTCupid">
    <img src="https://raw.githubusercontent.com/BulgakovDmitry/3D_triangles/main/img/A.jpeg" width="160" height="160" style="border-radius: 50%;">
  </a>
  <a href="https://github.com/BulgakovDmitry">
    <img src="https://raw.githubusercontent.com/BulgakovDmitry/3D_triangles/main/img/D.jpeg" width="160" height="160" style="border-radius: 50%;">
  </a>
  <br>
  <a href="https://github.com/RTCupid"><strong>@RTCupid, </strong></a>
  <a href="https://github.com/BulgakovDmitry"><strong>@BulgakovDmitry</strong></a>
  <br>
</div>

## 📚 Литература
1. Расширенная форма Бэккуса-Науэра [Электронный ресурс]: статья. -  https://divancoder.ru/2017/06/ebnf/ (дата обращения 21 мая 2025)

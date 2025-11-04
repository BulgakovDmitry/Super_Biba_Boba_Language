<div align="center">

# Implementation of the Super Biba-Boba programming language in C++
  ![C++](https://img.shields.io/badge/C++-23-blue?style=for-the-badge&logo=cplusplus)
  ![CMake](https://img.shields.io/badge/CMake-3.20+-green?style=for-the-badge&logo=cmake)
  ![Testing](https://img.shields.io/badge/Google_Test-Framework-red?style=for-the-badge&logo=google)

</div>

- This project is our implementation of programming language ParaCL from C++ cource by K.I.Vladimirov.

## Description of the grammar

Below is a description of the grammar of the language in a format close to EBNF [2], which was updated before the addition of the new syntax of the language:

```
Program     ::= StmtList 
StmtList    ::= Statement ';' 

Statement   ::= Assignment | IfStmt  | WhileStmt |  Input   | Print

IfStmt      ::= 'if'    '(' Expression ')' '{' StmtList '}'
WhileStmt   ::= 'while' '(' Expression ')' '{' StmtList '}'

Assignment  ::= Var '=' Expression

Input       ::= Var '=' '?'
Print       ::= 'print' Expression

Expression  ::= Equality
Equality    ::= Rel ( ( '==' | '!=' ) Rel )*
Rel         ::= AddSub ( ( '<' | '>' | '<=' | '>=' ) AddSub )*
AddSub      ::= Primary ( ( '+' | '-' ) Primary )*
Primary     ::= '(' Expression ')'| Var | Number

Var         ::= ([a-z] | [A-Z])+
Num         ::= ['0'-'9']+
```

## Project Creators

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

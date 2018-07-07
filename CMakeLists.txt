cmake_minimum_required(VERSION 3.6)
project(Projeto)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c "Source Files/Exames.c" "Source Files/Exames.h" "Source Files/Menus.c" "Source Files/Menus.h" "Source Files/Tempo.c" "Source Files/Tempo.h" "Source Files/Disciplinas.c" "Source Files/Disciplinas.h" "Source Files/Estruturas.h" "Source Files/Protecoes.c" "Source Files/Protecoes.h" "Source Files/Alunos.c" "Source Files/Alunos.h" "Source Files/Ficheiros.c" "Source Files/Ficheiros.h")
add_executable(Projeto ${SOURCE_FILES})
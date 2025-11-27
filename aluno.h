#ifndef ALUNO_H
#define  ALUNO_H
#include "new_string.h"
#define NOTA_MAX 10
#define MAX_ALUNOS 100
#define NOTA_MIN 0
#define NOTAS_QUANT 2
typedef struct {
    int matricula;
    String nome;
    int idade;
    double notas[NOTAS_QUANT];
    double media;
} Aluno;



typedef Aluno Alunos[MAX_ALUNOS];
void adicionar_aluno(Aluno *alunos, int *atual_index);
void listar_alunos(Aluno *alunos, int *atual_index);
void buscar_alunos(Aluno *alunos, int *atual_index);
void estatistica_turma(Aluno *alunos, int *atual_index);

#endif
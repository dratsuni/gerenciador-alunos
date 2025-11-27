#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "../include/aluno.h"
#include "../include/input.h"
#include "../include/new_string.h"
#define MATRICULA_JA_EXISTE 1
#define NOME_DUPLICADO 2
#define ALUNO_NAO_EXISTE 0


static double media_geral = 0;
static double maior_media = 0;
static double menor_media = 0;

static void adicionar_notas(Aluno *aluno){
    double nota;
    int index = 0;

    while (index < NOTAS_QUANT) {
        printf("digite a %da nota: ", index + 1);
        persistent_number_input(&nota,  double_input);
        if (nota <= NOTA_MAX && nota >= NOTA_MIN){
            aluno->notas[index] = nota;
            index++;
        } else {
            printf("Tente novamente. Digite notas de [0-10]\n.");
        }
    }
}

static void media_notas(Aluno *aluno){
    double *notas = aluno->notas;
    double soma = 0;

    for (int i = 0; i < NOTAS_QUANT; i++){
        soma += notas[i];
    }

    aluno->media = soma / NOTAS_QUANT;
}

static int aluno_existe(Aluno *alunos, Aluno *aluno, int index_atual){

    for (int i = 0; i < index_atual; i++){
        if (alunos[i].matricula == aluno->matricula){
            return MATRICULA_JA_EXISTE;
        } if (strcmp(alunos[i].nome, aluno->nome) == 0) {
            return NOME_DUPLICADO;
        }
    }

    return ALUNO_NAO_EXISTE;
}

static void formatar_dados(Aluno *aluno){
    if (aluno != NULL){
        printf("    MATRICULA: %d\n", aluno->matricula);
        printf("    NOME: %s\n", aluno->nome);
        printf("    Notas:\n");

        for (int i = 0; i < NOTAS_QUANT; i++){
            printf("        %d nota: %.2lf\n", i, aluno->notas[i]);
        }
        
        printf("    MEDIA: %lf\n", aluno->media);
    }
}

static void adicionar_estatistica(Aluno *aluno, int index){
    if (aluno->media > maior_media){
        maior_media = aluno->media;
    } if (aluno->media  < menor_media || index == 0){
        menor_media = aluno->media;
    }

    media_geral += aluno->media;
}

static void digitar_dados_aluno(Aluno *temp_aluno){

    printf("digite o nome do aluno: ");
    str_input(temp_aluno->nome, STRING_LENGHT);
    printf("digite a matricula: ");
    persistent_number_input(&temp_aluno->matricula, int_input);
    adicionar_notas(temp_aluno);
    media_notas(temp_aluno);

}


void adicionar_aluno(Aluno *alunos, int *index_atual){
    Aluno temp_aluno;

    if (*index_atual < MAX_ALUNOS){        
        digitar_dados_aluno(&temp_aluno);

        int o_aluno_existe = aluno_existe(alunos, &temp_aluno, *index_atual);

        if (o_aluno_existe == ALUNO_NAO_EXISTE){
            printf("Aluno adicionado!\n");
            adicionar_estatistica(&temp_aluno, *index_atual);
            alunos[*index_atual] = temp_aluno;
            *index_atual += 1;

        } else if (o_aluno_existe == MATRICULA_JA_EXISTE) {
            printf("Error: Já existe um aluno com essa matricula. Tente novamente.\n");
    
        } else {
            printf("Error: Já existe um aluno com esse nome.\n");
        }
    } else {
        printf("Error: Limite de alunos excedido.\n");
    }

}

void listar_alunos(Aluno *alunos, int *atual_index){
    if (*atual_index > 0){
        printf("=============Alunos cadastrados=============\n\n");
        for (int i = 0; i < *atual_index; i++){
            printf("%do Aluno(a):\n", i + 1);
            formatar_dados(&alunos[i]);
        }
        printf("============================================\n");
    } else {
        printf("Nenhum aluno cadastrado.\n");
    }
}

void buscar_alunos(Aluno *alunos, int *atual_index){
    int index = 0;
    int aluno_encontrado = 0;
    int matricula = 0;

    printf("Digite o numero de matricula do aluno: ");
    persistent_number_input(&matricula,int_input);

    while(index < *atual_index){
        if(alunos[index].matricula == matricula){
            formatar_dados(&alunos[index]);
            aluno_encontrado = 1;
            break;
        }
        index++;
    }

    if (aluno_encontrado == 0){
        printf("Aluno nao econtrado.\n");
    }
}

void estatistica_turma(Aluno *alunos, int *atual_index){
    (void) alunos;

    double media_geral_tmp = (*atual_index > 0) ? media_geral / *atual_index : media_geral;

    printf("==============Estatistica geral da turma=================\n");
    printf("Quantidade de  alunos: %d\n", *atual_index);
    printf("Maior media: %.2lf\n", maior_media);
    printf("Menor media: %.2lf\n", menor_media);
    printf("Media geral: %.2lf\n", media_geral_tmp);
    printf("=========================================================\n");

}





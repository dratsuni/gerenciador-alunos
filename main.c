#include "new_string.h"
#include "aluno.h"
#include "input.h"
#include <stdio.h>



static Alunos alunos;
int index_atual = 0;

typedef  void (*OpcoesArray)(Aluno *aluno_struct, int *index);
static void mostrar_menu();
static int opcoes(int op);

int main (){
    int break_while = 1;
    int op = 0;
    while (break_while){
        mostrar_menu();
        persistent_number_input(&op, int_input);
        break_while = opcoes(op);
    }

    return 0;

}

static void mostrar_menu(){
        printf("==[GERENCIADOR DE ALUNOS]==\n");
        printf(" [1]Cadastrar aluno\n [2]Lista alunos\n [3]Buscar aluno\n [4]Estatisticas da turma\n [5]Sair\n");
        printf("Escolha: ");
    
}

static int opcoes(int op){

    OpcoesArray opcoes_array[] = {adicionar_aluno, listar_alunos, buscar_alunos, estatistica_turma};
    if (op < 5 && op > 0){
        opcoes_array[op - 1](alunos, &index_atual);
        return 1;
    } else if (op != 5 || op <= 0) {
        printf("Essa opcao nao existe.\n");
        return 1;
    } else {
        return 0;
    }
    
}





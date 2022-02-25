#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#define TM 50
#define TL 4

/* Criar um programa para gerenciar um sistema de reservas de mesas em um
restaurante. O restaurante possui 50 mesas. Cada mesa possui 4 lugares. O
programa deve permitir escolher a quantidade de mesas que se deseja
reservar e quais os números das mesas a serem reservadas (os números das
mesas variam de 1 a 50). Todos os lugares são demarcados. Com isso, o
programa deve armazenar o nome, telefone e e-mail de todas as pessoas
que ficarão em cada um dos lugares da mesa. Em uma mesa de 4 lugares, é
possível que no máximo 4 pessoas sentem na mesa, mas podem ser menos
de 4 pessoas. Ao abrir o programa o sistema deve carregar, de um arquivo
binário cujo nome será fornecido pelo usuário, as reservas do restaurante.
Se o arquivo informado não existir, ele deve ser criado. Em seguida, deve ser
possível:
a. Realizar reservas
b. Excluir reservas
c. Procurar por uma determinada reserva
d. Visualizar todas as reservas
e. Informar a porcentagem de ocupação do restaurante de acordo com
as reservas realizadas. A porcentagem de ocupação deve ser
informada em função do número de mesas que já possuem reservas
e também em função do número de pessoas com reserva.
Observações:
a) algoritmo deverá informar se foi possível realizar a reserva e atualizar a
reserva. Se não for possível, o algoritmo deverá emitir uma mensagem de
erro.
b) O algoritmo deve terminar quando o usuário digitar o código 0 para uma
das mesas ou quando todas as mesas já possuírem reservas.
c) Ao finalizar o programa, todas as reservas devem ser salvas em um
arquivo binário.
 */
        
typedef struct {
        char nome[50];
        double telefone;
        char email[50];
}informacoes;

typedef struct {
    informacoes cadeiras[TL];
    int numero_mesa;
    int qnt_cadeira;
} reserva;

int main(int argc, char *argv[]) {
    
    SetConsoleOutputCP(65001);

    FILE *arq;
    reserva r[TM];
    char escolha, nome[20];
    float porcentagem_mesa = 0, porcentagem_pessoa = 0;
    int mesas[TM], qnt_cadeira[TL], qtd_mesa = 0, cont_mesa = 0, m,i, j, numero_mesa1, n = 0; 
    int cont_mesa1 = 0, cont = 0, mesa_buscada = 0, mesa_removida = 0, cont_pessoa = 0, arquivo=0;

    printf("Informe o nome do arquivo de reservas: ");
	fgets(nome,20,stdin);
	nome[strlen(nome)-1]='\0';
    
    arq = fopen(nome, "rb");

    if (arq == NULL){
        printf("\n\nErro! \nImpossivel abrir o arquivo!");
        printf("\nArquivo %s sendo criado...\n\n", nome);
        for (i=0; i<TM; i++){
            mesas[i]=0;
        }
    }else {
        fread (mesas,sizeof(reserva), TM, arq);
        for (i=0; i<TM; i++){
            if(r[i].numero_mesa == 51){
                cont_mesa++;
            }
        }
        for (i=0; i<TL; i++){
             if(r[i].numero_mesa == 51){
                cont_pessoa++;
             }
        }
        fclose(arq);
    }
    
    do{
        printf("|------------------------ RESERVA DE MESAS DO RESTAURANTE ----------------------|");
        printf("\n\n|     --Selecione uma das alternativas abaixos conforme sua descrição!--        |");
        printf("\n\n|a. Realizar reservas;                                                          |");
        printf("\n\n|b. Excluir reservas;                                                           |");
        printf("\n\n|c. Procurar por uma determinada reserva;                                       |");
        printf("\n\n|d. Visualizar todas as reservas;                                               |");
        printf("\n\n|e. Informa a porcentagem de ocupação do restaurante;                           |");
        printf("\n\n|-------------------------------------------------------------------------------|");

        printf("\n\nInforme a opção escolhida: ");
        scanf(" %c", &escolha);
        
        if (escolha == 'a' || escolha == 'A'){
            if (cont_mesa == 50){
                break;
            }
            printf("\n\nInforme a quantidade de mesas que deseja reservar: ");
            scanf("%d", &qtd_mesa);
            if (qtd_mesa<=50){
                for (i=0;i<qtd_mesa; i++){
                    pergunta:
                    printf("\nInforme o número da %d° mesa ou o algarismo '0' para encerrar o sistema de reserva: ", i+1);
                    scanf("%d", &numero_mesa1);
                    if (numero_mesa1 == 0){
                        printf("\nPrograma encerrado com sucesso!");
                        goto final;
                    }
                    if (r[numero_mesa1-1].numero_mesa == 51){
                        printf("\n\nEssa mesa já está reservada!\n");
                        goto pergunta;
                    }
                    if (r[numero_mesa1-1].numero_mesa > 0 || r[numero_mesa1-1].numero_mesa <= TM){
                        printf("\nInforme a quantidade de cadeiras: ");
                        scanf("%d", &r[numero_mesa1-1].qnt_cadeira);
                        if (r[numero_mesa1-1].qnt_cadeira > 0 || r[numero_mesa1-1].qnt_cadeira <=TL ){
                            for(j=0; j<r[numero_mesa1-1].qnt_cadeira; j++){
                                printf("\n\n-----------------  Cadeira %d  -----------------", j+1);
                                printf("\nInforme o nome da pessoa que ocupará o %d° assento: ", j+1);
                                fflush(stdin);
                                fgets(r[numero_mesa1-1].cadeiras[j].nome, 50, stdin);
                                printf("\nInforme o telefone da pessoa que ocupará o %d° assento: ", j+1);
                                scanf("%lf", &r[numero_mesa1-1].cadeiras[j].telefone);
                                printf("\nInforme o email da pessoa que ocupará o %d° assento: ", j+1);
                                fflush(stdin);
                                fgets(r[numero_mesa1-1].cadeiras[j].email, 50, stdin);
                                cont_pessoa++;
                            }
                                printf("\n\nReserva feita com sucesso!\n\n");
                                r[numero_mesa1-1].numero_mesa=51;
                                cont_mesa++;
                                cont_mesa1++;
                        } 
                        else
                            printf("\n\nMesa não possui a quantidade de cadeiras informada!");
                    } 
                    else{
                        printf("\n\nNúmero de mesas inválido!");
                    }
                    cont++;
                } 
             } 
        }
        if (escolha == 'b' || escolha == 'B'){
            printf("Informe o número da mesa que deseja remover: ");
            scanf("%d", &mesa_removida);
            for(i=0; i < TM; i++){
                if (mesa_removida == i+1 && r[i].numero_mesa == 51){
                    cont_pessoa -= r[i].qnt_cadeira;
                    r[i].numero_mesa = 0;
                    cont_mesa--;
                    printf("\nReserva removida com sucesso!\n\n");
                    break;
                }
            }
        }
        if (escolha == 'c' || escolha == 'C'){
            printf("Informe o número da mesa em deseja buscar a reserva: ");
            scanf("%d", &mesa_buscada);
            for(i=0; i < TM; i++){
                if (mesa_buscada == i+1 && r[i].numero_mesa == 51){
                    printf("\n\nMesa número %d foi achada!", i+1);
                    printf("\nPossui %d cadeiras reservadas", r[i].qnt_cadeira);
                    for(j=0; j<r[i].qnt_cadeira; j++){
                        printf("\n\n---------  Dados Cadeira %d  ---------", j+1);
                        printf("\nNome: %s", r[i].cadeiras[j].nome);
                        printf("\nTelefone: %0.lf", r[i].cadeiras[j].telefone);
                        printf("\nEndereço de email: %s", r[i].cadeiras[j].email);
                        printf("\n\n");
                        break;
                    }
                } 
            }
        }
        if (escolha == 'd' || escolha == 'D'){
            printf("\n\n------------  MESAS RESERVADAS  ------------");
            for (i=0; i < TM; i++){
                if (r[i].numero_mesa == 51){
                    printf("\n\nMesa número: %d", i+1);
                    printf("\nCom %d cadeiras reservadas", r[i].qnt_cadeira);
                    printf("\n\n");
                }
            }
        }
        if (escolha == 'e' || escolha == 'E'){
            printf("\n\n------------  PORCENTAGEM DE RESERVAS  ------------");
            porcentagem_mesa =  ((float)cont_mesa / TM) * 100;
            porcentagem_pessoa =  ((float)cont_pessoa / 200) * 100;
            printf("\n\nA porcentagem de ocupação de mesas é de %.2f%%.", porcentagem_mesa);
            printf("\nA porcentagem de ocupação de pessoas é de %.2f%%", porcentagem_pessoa);
            printf("\n\n");
        }
    } while (escolha != 0);
    final:

    arq = fopen(nome, "wb");
    if(arq != NULL)
    fwrite (mesas,sizeof(reserva), TM, arq);
    fclose(arq);

    return 0;
}
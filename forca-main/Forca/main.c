#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>
#include <string.h>

int menu_principal();
void recebe_palavra(char* palavra);
void padroniza_palavra(char* palavra);
int inicia_adivinhacao();
void desenha_forca(int contador, int inicio);
int verifica_tamanho(char* palavra);
char* cria_string_vazia(char* string_vazia, int tamanho);
void verifica_tentativa(char* palavra, char* palavra_vazia, char* erros, int* contador_erros);
void padroniza_tentativa(char* chute);
int verifica_vitoria(char* palavra_vazia);
void mostra_acertos(char* palavra_vazia);
void mostra_erros(char erros[], int contador_erros);
void mostra_correta(char* palavra);
void vitoria();
void derrota();
void jogar_novamente(int* continuar_jogo, int* contador_erros);


int main(){
    system("mode 800");
    int inicio_do_jogo, contador_erros = 0, tamanho_palavra, continuar_jogo = 1;
    char palavra[100], palavra_vazia[100], erros[6] = {' '};

    setlocale(LC_ALL, "Portuguese");
    while (continuar_jogo == 1) {
        inicio_do_jogo = menu_principal();
        if (inicio_do_jogo == 1) {
            system("cls");
            recebe_palavra(palavra);
            padroniza_palavra(palavra);
            system("cls");
            if (inicia_adivinhacao() == 1) {
                system("cls");
                tamanho_palavra = verifica_tamanho(palavra);
                strcpy(palavra_vazia, cria_string_vazia(palavra_vazia, tamanho_palavra));
                do {
                    desenha_forca(contador_erros, 0);
                    verifica_tentativa(palavra, palavra_vazia, erros, &contador_erros);
                    system("cls");
                    mostra_acertos(palavra_vazia);
                    mostra_erros(erros, contador_erros);

                    if (verifica_vitoria(palavra_vazia) == 1) {
                        system("cls");
                        vitoria();
                        desenha_forca(contador_erros, 1);
                        jogar_novamente(continuar_jogo, &contador_erros);
                        break;
                    }

                    if (contador_erros >= 6) {
                        system("cls");
                        derrota();
                        mostra_correta(palavra);
                        desenha_forca(contador_erros, 1);
                        jogar_novamente(continuar_jogo, &contador_erros);
                        break;
                    }

                    if (strcmp(palavra, palavra_vazia) != 0 && contador_erros < 6) {
                        continue;
                    }

                } while (1);
            }

        } else {
            system("cls");
            menu_principal();
        }
    }


}

int menu_principal(){
    int opcao;
    printf("\n##########################################################");
    printf("\n#                                                        #");
    printf("\n#                                             ###        #");
    printf("\n#                                             # #        #");
    printf("\n#                                             ###        #");
    printf("\n#        ####  ####  ####  ####   ##           #         #");
    printf("\n#        #     #  #  #  #  #     #  #          #         #");
    printf("\n#        ##    #  #  ####  #     ####        # # #       #");
    printf("\n#        #     #  #  # #   #     #  #      #   #   #     #");
    printf("\n#        #     ####  #  #  ####  #  #          #         #");
    printf("\n#                                            #   #       #");
    printf("\n#                                          #       #     #");
    printf("\n#                                                        #");
    printf("\n#        Bem vindo ao jogo da forca!                     #");
    printf("\n#                                                        #");
    printf("\n#        O jogo deve ser jogado por 2 jogadores!         #");
    printf("\n#        O Jogador 1 escolhe a palavra a ser             #");
    printf("\n#        adivinhada e o Jogador 2 tenta adivinhá-la!     #");
    printf("\n#                                                        #");
    printf("\n#        A forca oferece 6 tentativas, você consegue     #");
    printf("\n#        sobreviver?                                     #");
    printf("\n#                                                        #");
    printf("\n#        Boa Sorte!!                                     #");
    printf("\n#                                                        #");
    printf("\n#        (Digite 1 para iniciar o jogo)                  #");
    printf("\n#                                                        #");
    printf("\n#                                                        #");
    printf("\n#                                                        #");
    printf("\n##########################################################");
    printf("\n ###");
    printf("\n ###");
    printf("\n ###");
    printf("\n#####");
    printf("\n ###");
    printf("\n  #\n");
    scanf("%d",&opcao);
    getchar();
    return opcao;
}

void recebe_palavra(char* palavra){
    printf("\n##########################################################");
    printf("\n#                                                        #");
    printf("\n#                                                        #");
    printf("\n#                                                        #");
    printf("\n#                                                        #");
    printf("\n#       #### #### ####  ##  ###  #### ####      ##       #");
    printf("\n#        ##  #  # #    #  # #  # #  # #  #     ###       #");
    printf("\n#        ##  #  # # ## #### #  # #  # ####      ##       #");
    printf("\n#      # ##  #  # #  # #  # #  # #  # # #       ##       #");
    printf("\n#      ####  #### #### #  # ###  #### #  #     ####      #");
    printf("\n#                                                        #");
    printf("\n#                                                        #");
    printf("\n#                                                        #");
    printf("\n#                                                        #");
    printf("\n#                                                        #");
    printf("\n#        Você deve escolher a palavra a ser              #");
    printf("\n#        adivinhada!                                     #");
    printf("\n#                                                        #");
    printf("\n#        Por favor, não use acentuação.                  #");
    printf("\n#                                                        #");
    printf("\n#                                                        #");
    printf("\n#        Você pode utilizar palavras compostas!          #");
    printf("\n#        Exemplo: Guarda-chuva                           #");
    printf("\n#                                                        #");
    printf("\n#        Digite abaixo a palavra escolhida!              #");
    printf("\n#                                                        #");
    printf("\n#        Boa Sorte!!                                     #");
    printf("\n#                                                        #");
    printf("\n#                                                        #");
    printf("\n#                                                        #");
    printf("\n##########################################################");
    printf("\n ###");
    printf("\n ###");
    printf("\n ###");
    printf("\n#####");
    printf("\n ###");
    printf("\n  #\n");
    fgets(palavra, 100, stdin);
}

void padroniza_palavra(char* palavra){
    for (int i = 0; palavra[i] != '\0'; i++){
        palavra[i] = tolower(palavra[i]);
    }
}

int inicia_adivinhacao(){
    int inicio;
    printf("\n##########################################################");
    printf("\n#                                                        #");
    printf("\n#                                                        #");
    printf("\n#                                                        #");
    printf("\n#                                                        #");
    printf("\n#       #### #### ####  ##  ###  #### ####     ####      #");
    printf("\n#        ##  #  # #    #  # #  # #  # #  #       ##      #");
    printf("\n#        ##  #  # # ## #### #  # #  # ####     ####      #");
    printf("\n#      # ##  #  # #  # #  # #  # #  # # #      ##        #");
    printf("\n#      ####  #### #### #  # ###  #### #  #     ####      #");
    printf("\n#                                                        #");
    printf("\n#                                                        #");
    printf("\n#                                                        #");
    printf("\n#                                                        #");
    printf("\n#        Você deve adivinhar a palavra escolhida!        #");
    printf("\n#                                                        #");
    printf("\n#                                                        #");
    printf("\n#        Você terá 6 tentativas para acertar,            #");
    printf("\n#                                                        #");
    printf("\n#        ou...                                           #");
    printf("\n#                                                        #");
    printf("\n#        Você é enforcado!                               #");
    printf("\n#                                                        #");
    printf("\n#        Boa Sorte!!                                     #");
    printf("\n#                                                        #");
    printf("\n#                                                        #");
    printf("\n#        Digite 1 para começar a adivinhar!              #");
    printf("\n#                                                        #");
    printf("\n#                                                        #");
    printf("\n#                                                        #");
    printf("\n##########################################################");
    printf("\n ###");
    printf("\n ###");
    printf("\n ###");
    printf("\n#####");
    printf("\n ###");
    printf("\n  #\n");
    scanf("%d", &inicio);
    return inicio;
}

void desenha_forca(int contador, int inicio){
    if(inicio == 0){
            switch(contador){
                case 0:
                    printf("Você tem 6 tentativas!\n");
                    printf("_____________   \n|.|         |   \n|.|        _|_\n|.|          \n|.|        \ \n|.|         \n|.| \n|.| \n|.| \n\n");
                    printf("\n");
                    break;

                case 1:
                    printf("Você tem 5 tentativas!\n");
                    printf("_____________   \n|.|         |   \n|.|        _|_\n|.|         O    \n|.|         \n|.|       \n|.| \n|.| \n|.| \n\n");
                    printf("\n");
                    break;

                case 2:
                    printf("Você tem 4 tentativas!\n");
                    printf("_____________   \n|.|         |   \n|.|        _|_\n|.|         O    \n|.|         |    \n|.|         \n|.| \n|.| \n|.| \n\n");
                    printf("\n");
                    break;

                case 3:
                    printf("Você tem 3 tentativas!\n");
                    printf("_____________   \n|.|         |   \n|.|        _|_\n|.|         O    \n|.|        /|    \n|.|         \n|.| \n|.| \n|.| \n\n");
                    printf("\n");
                    break;

                case 4:
                    printf("Você tem 2 tentativas!\n");
                    printf("_____________   \n|.|         |   \n|.|        _|_\n|.|         O    \n|.|        /|\\    \n|.|         \n|.| \n|.| \n|.| \n\n");
                    printf("\n");
                    break;

                case 5:
                    printf("Você tem apenas 1 tentativa!\n");
                    printf("_____________   \n|.|         |   \n|.|        _|_\n|.|         O    \n|.|        /|\\    \n|.|        /  \n|.|  \n|.|  \n|.| \n\n");
                    printf("\n");
                    break;

                case 6:
                    printf("FORCA!!!\n");
                    printf("_____________   \n|.|         |   \n|.|        _|_\n|.|         O    \n|.|        /|\\    \n|.|        / \\ \n|.|  \n|.|  \n|.| \n\n");
                    printf("\n");
                    break;
            }

    } else {
    puts("_____________ \n|.|         |   \n|.|        _|_\n|.|         O    \t JOGO DA FORCA \n|.|        /|\\ \n|.|        / \\           Feito por: Heloisa Moraes \n|.| \n|.| \n|.| \n|.| \n|.| \n");
    }

}

int verifica_tamanho(char* palavra){
    int tamanho = 0;
    for (int i = 0; palavra[i] != '\n' && palavra[i] != '\0'; i++){
        tamanho++;
    }
    return tamanho;
}

char* cria_string_vazia(char* string_vazia, int tamanho){
    for (int i = 0; i < tamanho; i++){
        string_vazia[i] = '_';
    }
    string_vazia[tamanho] = '\0';
    return string_vazia;
}

void verifica_tentativa(char* palavra, char* palavra_vazia, char* erros, int* contador_erros){
    char chute;
    int acerto = 0;
    printf("Digite a letra que deseja chutar:\n");
    scanf(" %c", &chute);
    getchar();
    padroniza_tentativa(&chute);
    for (int i = 0; palavra[i] != '\0'; i++) {
        if (chute == palavra[i]) {
            palavra_vazia[i] = chute;
            acerto = 1;
        }
    }

    if (!acerto && *contador_erros < 6) {
        erros[*contador_erros] = chute;
        (*contador_erros)++;
    }
}

void padroniza_tentativa(char* chute){
    *chute = tolower(*chute);
}

int verifica_vitoria(char* palavra_vazia){
    int todas_letras_adivinhadas = 1;
    for (int i = 0; palavra_vazia[i] != '\0'; i++){
        if (palavra_vazia[i] == '_'){
            todas_letras_adivinhadas = 0;
            break;
        }
    }
    return todas_letras_adivinhadas;
}

void mostra_acertos(char* palavra_vazia){
    printf("Letras acertadas: \n");
    printf("\n%s\n\n", palavra_vazia);
}

void mostra_erros(char erros[], int contador_erros){
    if (contador_erros > 0){
        printf("Letras erradas: \n");
        for (int i = 0; i < contador_erros; i++){
        printf("%c\n", erros[i]);
        }
        printf("\n");
    } else if (contador_erros == 0) {
        printf("Você não errou... ainda!\n\n");
    }
}

void mostra_correta(char* palavra){
    printf("\n\nA palavra correta era...\n");
    printf("\n%s\n\n", palavra);
}

void vitoria(){
    printf("\n##########################################################");
    printf("\n#                                                        #");
    printf("\n#                                                        #");
    printf("\n#    ##    ##  ##  ######  ######  ######  ##   ####     #");
    printf("\n#    ##    ##  ##    ##    ##  ##  ##  ##  ##  ##  ##    #");
    printf("\n#    ##    ##  ##    ##    ##  ##  ##  ##  ##  ##  ##    #");
    printf("\n#    ##    ##  ##    ##    ##  ##  ######  ##  ######    #");
    printf("\n#    ##    ##  ##    ##    ##  ##  ###     ##  ##  ##    #");
    printf("\n#    ##    ##  ##    ##    ##  ##  ## #    ##  ##  ##    #");
    printf("\n#     ##  ##   ##    ##    ##  ##  ##  #   ##  ##  ##    #");
    printf("\n#       ##     ##    ##    ######  ##   #  ##  ##  ##    #");
    printf("\n#                                                        #");
    printf("\n#                                                        #");
    printf("\n#                        *                               #");
    printf("\n#      *                                  *      *       #");
    printf("\n#             *                    *                     #");
    printf("\n#                          ###                           #");
    printf("\n#                   *      # #                 *         #");
    printf("\n#      *       *           ###         *                 #");
    printf("\n#                       #   #   #                        #");
    printf("\n#                         # # #                          #");
    printf("\n#          *                #             *              #");
    printf("\n#                           #                   *        #");
    printf("\n#                           #                            #");
    printf("\n#              *            #                            #");
    printf("\n#     *                    # #        *          *       #");
    printf("\n#                         #   #                          #");
    printf("\n#                                                        #");
    printf("\n#                                                        #");
    printf("\n#                                                        #");
    printf("\n##########################################################\n");
}

void derrota(){
    printf("\n###########################################################");
    printf("\n#                                                         #");
    printf("\n#                                                         #");
    printf("\n#  ####    ######  ######  ######  ######  ######  ####   #");
    printf("\n#  ##  ##  ##      ##  ##  ##  ##  ##  ##    ##   ##  ##  #");
    printf("\n#  ##  ##  ##      ##  ##  ##  ##  ##  ##    ##   ##  ##  #");
    printf("\n#  ##  ##  ####    ######  ######  ##  ##    ##   ######  #");
    printf("\n#  ##  ##  ##      ###     ###     ##  ##    ##   ##  ##  #");
    printf("\n#  ##  ##  ##      ## #    ## #    ##  ##    ##   ##  ##  #");
    printf("\n#  ##  ##  ##      ##  #   ##  #   ##  ##    ##   ##  ##  #");
    printf("\n#  ####    ######  ##   #  ##   #  ######    ##   ##  ##  #");
    printf("\n#                                                         #");
    printf("\n#                                                         #");
    printf("\n#                                                         #");
    printf("\n#                                                         #");
    printf("\n#                                                         #");
    printf("\n#                          ###                            #");
    printf("\n#                          # #                            #");
    printf("\n#                          ###                            #");
    printf("\n#                           #                             #");
    printf("\n#                         # # #                           #");
    printf("\n#                        #  #  #                          #");
    printf("\n#                           #                             #");
    printf("\n#                           #                             #");
    printf("\n#                           #                             #");
    printf("\n#                          # #                            #");
    printf("\n#                         #   #                           #");
    printf("\n#                                                         #");
    printf("\n#                                                         #");
    printf("\n#                                                         #");
    printf("\n###########################################################\n");
}

void jogar_novamente(int* continuar_jogo, int* contador_erros){
    printf("Deseja jogar novamente?\n");
    printf("Digite 1 para sim e 0 para não: \n");
    scanf("%d", &continuar_jogo);
    if (continuar_jogo == 1){
        *contador_erros = 0;
    } else if (continuar_jogo == 0) {
        *continuar_jogo = 0;
    }
    system("cls");
}

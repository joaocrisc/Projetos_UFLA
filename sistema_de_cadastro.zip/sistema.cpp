/* João Gabriel Carvalho Criscolo, Plinio Alves Cardoso, Bernardo Corradi Oliveira */

#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;
//registros dos dados
struct musico {
	int CPF;
    string nome;
    int idade;
    string instrumento;
    string banda;
    bool removido = false;
};
// Função para ordenar lista de músicos pelo CPF (ordem crescente)
void ordenar_CPF(musico *lista, int tam) {
    int posMenor;
    for (int i = 0; i < tam - 1; i++) {
        posMenor = i;
        for (int j = i + 1; j < tam; j++) {
            if (lista[j].CPF < lista[posMenor].CPF) {
                posMenor = j; //encontrou o menor cpf
            }
        }
        if (posMenor != i) { //troca os elementos para ordenar
            musico temp = lista[posMenor];
            lista[posMenor] = lista[i];
            lista[i] = temp;
        }
    }
}

// Ordena lista de músicos pela idade (ordem crescente)
void ordenar_idade(musico*&lista,int tam){
    int posMenor;
    for (int i = 0; i < tam-1; i++) {
        posMenor=i;
        for (int j = i + 1; j < tam; j++) {
            if (lista[posMenor].idade > lista[j].idade) {
               posMenor=j;// Encontra o músico mais jovem no intervalo
            }
        }
         musico temp = lista[posMenor];
                lista[posMenor] = lista[i];
                lista[i] = temp;
    }
}

// Ordena lista de músicos pelo nome (ordem alfabética)
void ordenar_nome(musico*&lista,int tam){
    int posMenor;
    for (int i = 0; i < tam - 1; i++) {
        posMenor = i;
        for (int j = i + 1; j < tam; j++) {
            if (lista[j].nome < lista[posMenor].nome) {
                posMenor = j; // Encontra o nome "menor"
            }
        }
        if (posMenor != i) { // Troca para ordenar alfabeticamente
            musico temp = lista[posMenor];
            lista[posMenor] = lista[i];
            lista[i] = temp;
        }
    }
}

// Busca binária por CPF em lista ordenada
int buscabinaria_cpf(musico *lista, int cpfprocurado, int inicio, int fim) {
    int meio = (inicio + fim) / 2;

    if (fim >= inicio) {
        if (lista[meio].CPF == cpfprocurado)
            return meio; // Encontrou o CPF
        else if (lista[meio].CPF < cpfprocurado)
            return buscabinaria_cpf(lista, cpfprocurado, meio + 1, fim);  // Busca à direita
        else
            return buscabinaria_cpf(lista, cpfprocurado, inicio, meio - 1); // Busca à esquerda
    } else {
        return -1; // Nao encontrado
    }
}


// Busca binária por nome em lista ordenada
int buscabinaria_nome(musico *lista, string NomeProcurado, int inicio, int fim) {
    int meio = (inicio + fim) / 2;

    if (fim >= inicio) {
        if (lista[meio].nome == NomeProcurado)
            return meio; // Encontrou o nome
        else if (lista[meio].nome < NomeProcurado)
            return buscabinaria_nome(lista,NomeProcurado, meio + 1, fim); // Busca a direita
        else
            return buscabinaria_nome(lista,NomeProcurado, inicio, meio - 1); // Busca a esquerda
    } else {
        return -1; // Nao encontrado
    }
}

// Aumenta dinamicamente a capacidade da lista de músicos
void redimensionar(musico *&lista, int &capacidade) {
    int nova_capacidade = capacidade + 5; // Incremento fixo
    musico *novo = new musico[nova_capacidade];
     // Copia os elementos existentes
    for (int i = 0; i < capacidade; i++) {
        novo[i] = lista[i];
    }
    delete[] lista; // Libera memória antiga
    lista = novo; // O antigo aponta para o novo
    capacidade = nova_capacidade; // Atualiza capacidade
}

// Inserção de novos músicos
void inserir(musico *&lista, int &tam, int capacidade) {
    int inserir;
    cout << "Deseja inserir? 1-sim 2-nao: ";
    cin >> inserir;

    while (inserir == 1) {
        if (tam >= capacidade) {
            redimensionar(lista, capacidade); // Redimensiona se necessário
        }
		
		 // Coleta dados do músico
        cout << "Insira os dados do musico: " << endl;
        cout << "Nome: ";
        cin.ignore();
        getline(cin, lista[tam].nome);
        cout << "Idade: ";
        cin >> lista[tam].idade;
        cout << "CPF: ";
        cin >> lista[tam].CPF;
        cout << "Instrumento: ";
        cin.ignore();
        getline(cin, lista[tam].instrumento);
        cout << "Banda: ";
        getline(cin, lista[tam].banda);
        tam++;

        cout << "Deseja inserir outro? 1-sim 2-nao: ";
        cin >> inserir;
    }
}
// Exclusão lógica de músico pelo CPF
void excluir(musico *&lista, int &tam) {
    int cpfexcluir;
    cout << "Digite o CPF do musico que deseja excluir: ";
    cin >> cpfexcluir;
    ordenar_CPF(lista, tam);  // Ordena antes da busca binária
    int posicao = buscabinaria_cpf(lista, cpfexcluir, 0, tam - 1);
    
    if (posicao != -1) {
        lista[posicao].removido = true;  // Marca como removido
        cout << "Musico marcado para ser excluido com sucesso!" << endl;
    } else {
        cout << "Musico com CPF " << cpfexcluir << " nao encontrado." << endl;
    }
}

// Alteração de dados de músico
void alterar(musico *&lista, int &tam) {
    int cpfalterar;
    cout << "Digite o CPF do musico que deseja alterar: ";
    cin >> cpfalterar;

    ordenar_CPF(lista, tam); // Ordena antes da busca binária
    int posicao = buscabinaria_cpf(lista, cpfalterar, 0, tam - 1);

    if (posicao != -1) {
        cout << "-------------------------" << endl;
        cout << "Insira os novos dados do musico: " << endl;
        cout << "Nome: ";
        cin.ignore();
        getline(cin, lista[posicao].nome);
        cout << "Idade: ";
        cin >> lista[posicao].idade;
        cout << "CPF: ";
        cin >> lista[posicao].CPF;
        cout << "Instrumento: ";
        cin.ignore();
        getline(cin, lista[posicao].instrumento);
        cout << "Banda: ";
        getline(cin, lista[posicao].banda);
        cout << "Musico alterado com sucesso!" << endl;
        cout << "-------------------------" << endl;
    } else {
        cout << "Musico com CPF " << cpfalterar << " nao encontrado." << endl;
    }
}

// Listagem de músicos ativos
int listarMusicos(musico *lista, int tam) {
    if (tam == 0) {
        cout << "Nenhum musico cadastrado." << endl;
        return 0;
    }

    cout << "------ LISTA DE MUSICOS ------" << endl;
    for (int i = 0; i < tam; i++) {
        if (!lista[i].removido){ // Ignora músicos marcados como removidos
            cout << "Nome: " << lista[i].nome << endl;
            cout << "Idade: " << lista[i].idade << endl;
            cout << "CPF: " << lista[i].CPF << endl;
            cout << "Instrumento: " << lista[i].instrumento << endl;
            cout << "Banda: " << lista[i].banda << endl;
            cout << "-------------------------" << endl;
        }
    }
    return 1;
}

// Função que encontra a banda com mais músicos ativos
int bandaComMaisMusicos(musico *lista, int tam) {
    if (tam == 0) {
        cout << "Nenhum musico cadastrado." << endl;
        return 0;
    }

    string* bandas = new string[tam];  // Armazena nomes de bandas únicas
    int* cont = new int[tam];  // Contador de músicos por banda

    int qtdBandas = 0;

    for (int i = 0; i < tam; i++)
        cont[i] = 0;

    
    for (int i = 0; i < tam; i++) {

        if (!lista[i].removido) { // Considera apenas músicos ativos

            bool achou = false;

            
            for (int j = 0; j < qtdBandas; j++) {
                if (lista[i].banda == bandas[j]) {
                    cont[j]++; // Incrementa contador da banda existente
                    achou = true;
                }
            }

            
            if (!achou) { // Nova banda encontrada
                bandas[qtdBandas] = lista[i].banda;
                cont[qtdBandas] = 1;
                qtdBandas++;
            }
        }
    }

    if (qtdBandas == 0) {
        cout << "Nenhum musico ativo cadastrado." << endl;
        delete[] bandas;
        delete[] cont;
        return 0;
    }
    // Determina o máximo de músicos em uma banda
    int maximo = cont[0];
    for (int i = 1; i < qtdBandas; i++) {
        if (cont[i] > maximo)
            maximo = cont[i];
    }

     // Verifica se há empate
    int numEmpate = 0;
    for (int i = 0; i < qtdBandas; i++) {
        if (cont[i] == maximo)
            numEmpate++;
    }
      // Exibe banda(s) com mais músicos
    if (numEmpate > 1) {
        cout << "Empate entre as bandas: ";
        for (int i = 0; i < qtdBandas; i++) {
            if (cont[i] == maximo)
                cout << bandas[i] << ", ";
        }
        cout << "com " << maximo << " musicos cada." << endl;

    } else {
        for (int i = 0; i < qtdBandas; i++) {
            if (cont[i] == maximo)
                cout << "Banda com mais musicos: " << bandas[i]
                     << " (" << maximo << " musicos)" << endl;
        }
    }
	
    delete[] bandas;
    delete[] cont;
    return 1;
}




// Função que exibe o menu principal e retorna a opção escolhida pelo usuário
int interface() {
    int opcao;
    cout << "----MENU PRINCIPAL----" << endl;
    cout << "1 - Inserir novo musico" << endl;
    cout << "2 - Buscar musico por CPF" << endl;
    cout << "3 - Marcar para excluir musico por CPF" << endl;
    cout << "4 - Alterar dados do musico" << endl;
    cout << "5 - Banda com mais musicos" << endl;
    cout << "6 - Listar todos os musicos" << endl;
    cout << "7 - Buscar por um intervalo" << endl;
    cout << "8 - Metodo de Ordenacao" << endl;
    cout << "9 - Informacoes do projeto" << endl;
    cout << "10 - Registrar alteracoes" << endl;
    cout << "11 - Buscar musico por nome"<<endl;
    cout << "0 - Sair" << endl;
    cout << "Escolha: ";
    cin >> opcao;
    return opcao; // Retorna a opção escolhida pelo usuário
}

// Função que exibe o menu de métodos de ordenação e retorna a opção escolhida
int interfaceOrdenacao(){
    int opcao;
    cout << "----METODO DE ORDENACAO----" << endl;
    cout << "1 - Ordenar por CPF" << endl;
    cout << "2 - Ordenar por Idade" << endl;
    cout << "3 - Ordenar por Nome" << endl;
    cout << "Escolha: ";
    cin >> opcao;
    return opcao; // Retorna a opção de ordenação escolhida
}

// Função que lê os músicos de um arquivo CSV e preenche a lista dinâmica
// Recebe a capacidade inicial, tamanho atual da lista e o ponteiro da lista
// Retorna -1 se houver erro ao abrir o arquivo, 0 caso contrário
int leitura(int &capacidade, int &tam, musico *&lista) {
    ifstream entrada("musicos.csv"); // Abre arquivo CSV
    if (!entrada.is_open()) { // Verifica se abriu corretamente
        cout << "Erro ao abrir o arquivo!" << endl;
        return -1;
    }
	
    while (!(entrada.eof() || lista[tam].nome == "")) {
        if (tam >= capacidade) { // Verifica se precisa redimensionar
            redimensionar(lista, capacidade);
        }
		
		 // Lê campos do arquivo
        getline(entrada, lista[tam].nome, ';'); // Nome do músico
     
        entrada >> lista[tam].idade;
        entrada.ignore();
        entrada >> lista[tam].CPF;
        entrada.ignore();
        getline(entrada, lista[tam].instrumento, ';');
        getline(entrada, lista[tam].banda,';');
        entrada.ignore();
        tam++; // Incrementa quantidade de músicos lidos
		
    }

    entrada.close();  // Fecha arquivo
    return 0; // Leitura concluída
}

// Função que salva as alterações feitas na lista em um arquivo CSV
// Recebe a lista de músicos e o tamanho atual
void registrar(musico *lista, int tam) {
    cout<< "--------------------------" << endl;
    cout << "Salvando alteracoes" << endl;
    cout << "Digite o nome do arquivo para registrar as mudancas:" << endl;
    string arq;
    cin>> arq; 
    ofstream saida(arq); // Cria arquivo de saída
    for (int i = 0; i < tam; i++) {
        if (!lista[i].removido){ // Salva apenas músicos ativos
            saida << lista[i].nome << ";"
                  << lista[i].idade << ";"
                  << lista[i].CPF << ";"
                  << lista[i].instrumento << ";"
                  << lista[i].banda << ";" << endl;
          }
    }
    saida.close();  // Fecha arquivo
    cout << "Dados salvos com sucesso no arquivo " << arq << endl;
    cout << "--------------------------" << endl;
}

// Função que exibe informações sobre o projeto
void informacoes_projeto()
{
    cout << "-------------------------" << endl;
    cout << "Projeto de Cadastro de Musicos - Turma 22A" << endl;
    cout << "Desenvolvido por: " << endl;
    cout << "Joao Gabriel Carvalho Criscolo" << endl;
    cout << "Plinio Cardoso Alves" << endl;
    cout << "Bernardo Corradi Oliveira" << endl;
    cout << "Linguagem utilizada: C++" << endl;
    cout << "Funcionalidades: Inserir, Buscar, Excluir, Alterar dados de musicos, " << endl;
    cout << "Dados armazenados em arquivo CSV" << endl;
    cout << "-------------------------" << endl;
}

// Função que lista os músicos em um intervalo de índices
// Recebe lista, tamanho da lista, índice inicial e final
int listarIntervalo(musico *lista, int tam, int inicio, int fim) {
    if (tam == 0) {
        cout << "Nenhum musico cadastrado." << endl;
        return 0;
    }
    else if (inicio < 0){
        inicio = 0;  // Ajusta índice inicial inválido
    }
    else if (fim >= tam){
        fim = tam - 1; // Ajusta índice final inválido
    }
   else  if (inicio > fim) {  // Intervalo inválido
        cout << "Intervalo invalido." << endl;
        return 0 ;
    }
    cout << "------ LISTA DE MUSICOS (" << inicio << " a " << fim << ") ------" << endl;
    for (int i = inicio; i <= fim; i++) {
        if (!lista[i].removido){ // Exibe apenas músicos ativos
            cout << "Indice " << i << ":" << endl;
            cout << "Nome: " << lista[i].nome << endl;
            cout << "Idade: " << lista[i].idade << endl;
            cout << "CPF: " << lista[i].CPF << endl;
            cout << "Instrumento: " << lista[i].instrumento << endl;
            cout << "Banda: " << lista[i].banda << endl;
            cout << "-------------------------" << endl;
        }
    }
    return 1;
}

int main() {
	 // Inicialização da lista com capacidade inicial
    int capacidade = 40, tam = 0;
    musico *lista = new musico[capacidade];
    // Leitura de arquivo CSV, encerra se houver erro
    if (leitura(capacidade, tam, lista) == -1)
        return -1;

    int opcao;
    do {
        opcao = interface(); // Mostra menu principal

        cout << "-------------------------" << endl << endl;

        switch (opcao) {
            case 1:
                inserir(lista, tam, capacidade); // Inserir músicos
                break;
                
            case 2: {  // Buscar músico por CPF
                ordenar_CPF(lista, tam); // Necessário para busca binária
                cout << "Digite o CPF que deseja procurar: ";
                int procurado;
                cin >> procurado;
                int pos = buscabinaria_cpf(lista, procurado, 0, tam - 1);
                
                if (pos != -1) {
                    if (!lista[pos].removido) {
                        cout << "Musico encontrado:" << endl;
                        cout << "Nome: " << lista[pos].nome << endl;
                        cout << "Idade: " << lista[pos].idade << endl;
                        cout << "CPF: " << lista[pos].CPF << endl;
                        cout << "Instrumento: " << lista[pos].instrumento << endl;
                        cout << "Banda: " << lista[pos].banda << endl;
                    } else {
                        cout << "Musico encontrado, mas esta marcado para exclusao." <<endl;
                    }
                } else {
                    cout << "Musico nao encontrado." << endl;
                }
                break;
            }
            
            case 3: // Exclusão lógica
                excluir(lista, tam);
                break;
                
            case 4: // Alteração de dados
                alterar(lista, tam);
                break;
                
            case 5: // Banda com mais músicos
                bandaComMaisMusicos(lista, tam);
                break;
                
            case 6:  // Listar todos os músicos
                listarMusicos(lista, tam);
                break;
                
            case 7: // Listagem por intervalo de índices
                int inicio, fim;
                cout << "Digite o indice inicial: ";
                cin >> inicio;
                cout << "Digite o indice final: ";
                cin >> fim;
                listarIntervalo(lista, tam, inicio, fim);
                break;  
                
            case 8: { // Menu de ordenação
                int opcOrdenacao = interfaceOrdenacao();
                switch (opcOrdenacao) {
                    case 1:
                        ordenar_CPF(lista, tam);
                        cout << "Ordenado por CPF!" << endl;
                        break;

                    case 2:
                        ordenar_idade(lista, tam);   
						cout << "Ordenado por idade!" << endl;
                        break;
                        
                    case 3:
                        ordenar_nome(lista, tam);   
						cout << "Ordenado por nome!" << endl;
                        break;

                    default:
                        cout << "Opcao invalida no menu de ordenacao." << endl;
                        break;
                }
                break;
            }
                
            case 9: // Mostrar informações do projeto
                informacoes_projeto();
                break;
			
			case 10: // Salvar alterações em arquivo
			 registrar(lista, tam);
             break;
             
             case 11:{ // Busca por nome usando busca binária
             ordenar_nome(lista,tam);  // Ordenar para busca binária
             cout << "Digite o NOME que deseja procurar: ";
             string busca;
             cin >> busca;
             cout << endl;
                int posc;
                posc = buscabinaria_nome(lista, busca, 0, tam - 1);
                
                if (posc != -1) {
                    if (!lista[posc].removido) {
                        cout << "Musico encontrado:" << endl;
                        cout << "Nome: " << lista[posc].nome << endl;
                        cout << "Idade: " << lista[posc].idade << endl;
                        cout << "CPF: " << lista[posc].CPF << endl;
                        cout << "Instrumento: " << lista[posc].instrumento << endl;
                        cout << "Banda: " << lista[posc].banda << endl;
                    } else {
                        cout << "Musico encontrado, mas esta marcado para exclusao." <<endl;
                    }
                } else {
                    cout << "Musico nao encontrado." << endl;
                }
                break;
			}
			
            case 0: // Sair do programa
                cout << "Saindo do programa..." << endl;
                registrar(lista, tam);
                break;
                
            default:
                cout << "Opcao invalida, tente novamente." << endl;
                break;
        }

    } while (opcao != 0);

    delete[] lista; // Liberar memória
	return 0;
}

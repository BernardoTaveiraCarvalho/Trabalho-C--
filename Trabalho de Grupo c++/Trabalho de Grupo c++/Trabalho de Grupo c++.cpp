#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iomanip> 
#include <time.h>
#include <string>
#define _CRT_SECURE_NO_WARNINGS
using namespace std;
bool IFSTOCK, IFCOMPRA = false;
int CCLIENTE = 0;

void cleanInputBuffer() {
    char ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}
double obterDouble(double minValor, double maxValor, string msg) { //verificar doubles
    double valor;
    cout << (msg);
    while (scanf("%lf", &valor) != 1 || valor < minValor || valor > maxValor) {
        cleanInputBuffer();
        cout << (msg);
    }
    cleanInputBuffer();
    return valor;
}
int obterInt(int minValor, int maxValor, string msg) {//verificar ints
    int valor;
    cout << (msg);
    while (scanf("%d", &valor) != 1 || valor < minValor || valor > maxValor) {
        cleanInputBuffer();
        cout << (msg);
    }
    cleanInputBuffer();
    return valor;
}
void menu(int quantidadeCliente, int quantidadeStock, int stockQuantidade[], string stockNome[], double stockPreco[], int  checkoutQuantidade[], double checkoutPreco[], string  NomeCliente[]);
void vendaProd(int quantidadeCliente, int quantidadeStock, int stockQuantidade[], string stockNome[], double stockPreco[], int  checkoutQuantidade[], double checkoutPreco[], string  NomeCliente[]);
const string currentDateTime() {//Mostrar data
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d hora:%X", &tstruct);
    return buf;
}
void VerClientes(int quantidadeCliente, int quantidadeStock, int stockQuantidade[], string stockNome[], double stockPreco[], int checkoutQuantidade[], double checkoutPreco[], string NomeCliente[]) {//Ver todos os clientes
    system("cls");
    if (CCLIENTE <= 0) {
        cout << "Não existem clientes!";
    }
    else {
        for (int i = 0; i < CCLIENTE; i++) {
            cout << "Numero Cliente: " << i + 1 << endl;
            cout << "Nome: " << NomeCliente[i + 1] << endl;
            cout << "Total de produtos comprados: " << checkoutQuantidade[i + 1] << endl;
            cout << "Total gasto: " << checkoutPreco[i + 1] << endl;
        }
    }
}
void VerCliente(int quantidadeCliente, int quantidadeStock, int stockQuantidade[], string stockNome[], double stockPreco[], int checkoutQuantidade[], double checkoutPreco[], string NomeCliente[]) {//Ver um cliente
    system("cls");
    if (CCLIENTE <= 0) {
        cout << "Não existem clientes!";
    }
    else {
        int opcao;


        opcao = obterInt(1, 2, "Vai querer filtrar por codigo(1) ou por nome(2):  ");

        if (opcao == 1) {
            int id;

            id = obterInt(1, CCLIENTE, "Escreva o id: ");

            cout << "Numero Cliente: " << CCLIENTE << endl;
            cout << "Nome: " << NomeCliente[CCLIENTE] << endl;
            cout << "Total de produtos comprados: " << checkoutQuantidade[CCLIENTE] << endl;
            cout << "Total gasto: " << checkoutPreco[CCLIENTE] << endl;
        }
        else if (opcao == 2) {
            string nome;
            cout << "Escreva o nome: ";
            cin >> nome;


            bool encontrado = false;
            for (int i = 0; i < CCLIENTE; i++) {
                if (nome.compare(NomeCliente[i + 1]) == 0) {
                    cout << "Numero Cliente: " << i + 1 << endl;
                    cout << "Nome: " << NomeCliente[i + 1] << endl;
                    cout << "Total de produtos comprados: " << checkoutQuantidade[i + 1] << endl;
                    cout << "Total gasto: " << checkoutPreco[i + 1] << endl;
                    encontrado = true;
                }
            }
            if (encontrado == false) {
                system("cls");
                cout << "Nao foi encontrado ninguem com esse nome verifique maisculas e minusculas" << endl;
            }
        }
    }
}
void Cliente(int quantidadeCliente, int quantidadeStock, int stockQuantidade[], string stockNome[], double stockPreco[], int checkoutQuantidade[], double checkoutPreco[], string NomeCliente[]) {//Menu cliente
    system("cls");
    int opcao;
    cout << "------Cliente-----" << endl;
    cout << "1 Ver Clientes" << endl;
    cout << "2 Ver Cliente" << endl;
    cout << "3 sair" << endl;


    opcao = obterInt(1, 3, "Insira :");

    switch (opcao) {
    case 1:
        VerClientes(quantidadeCliente, quantidadeStock, stockQuantidade, stockNome, stockPreco, checkoutQuantidade, checkoutPreco, NomeCliente);
        break;
    case 2:
        VerCliente(quantidadeCliente, quantidadeStock, stockQuantidade, stockNome, stockPreco, checkoutQuantidade, checkoutPreco, NomeCliente);
        break;
    case 3:
        menu(quantidadeCliente, quantidadeStock, stockQuantidade, stockNome, stockPreco, checkoutQuantidade, checkoutPreco, NomeCliente);
        break;

    }


}
void talao(int quantidadeStock, string NomeCliente, int stockQuantidadeCopia[], string stockNome[], double stockPreco[], double total, double pagamento) {//Mostrar talão

    system("cls");
    cout << "=====================TALAO====================" << endl << endl;
    cout << "ID Cliente: " << CCLIENTE << endl;
    cout << "Nome Cliente: " << NomeCliente << endl;

    cout << "---------------------------------" << endl;
    for (int i = 0; i < quantidadeStock; i++) {

        if (stockQuantidadeCopia[i] > 0) {
            cout << "Produto: " << stockNome[i] << endl;
            cout << "Quantidade: " << stockQuantidadeCopia[i] << endl;
        }
        cout << "-----------------------------" << endl;
    }
    cout << "Preco s/IVA: " << total - total * 0.23 << endl;
    cout << "IVA: " << 0.23 << endl;
    cout << "Total C/iva: " << total << endl;
    cout << "Valor entregue: " << pagamento << endl;
    double troco = pagamento - total;
    cout << "Troco: " << troco << endl;
    cout << "Data de compra : " << currentDateTime() << endl;
    system("pause");


}
void mostrarproduto(int quantidade, int stockQuantidade[], string stockNome[], double stockPreco[]) {//Mostrar produtos
    int i;

    i = obterInt(1, quantidade, "Indique o id do produto ");

    system("cls");
    if (stockNome[i] != "0") {

        cout << "========Produto====================================================================" << endl;


        cout << endl << endl << "Id: " << i << endl << "Nome: " << stockNome[i - 1] << endl << "Quantidade: " << stockQuantidade[i - 1] << endl << "Preco: " << stockPreco[i - 1] << endl << endl;

        cout << "=================================================================================" << endl;
    }

}
void mostrarStock(int n, int* quantidade, string* produto, double* preco) {//Mostrar todos os produtos

    system("cls");
 
    cout << "========Stock====================================================================" << endl;

    for (int i = 0; i < n; i++) {
        if (produto[i] != "0") {
            cout << endl << endl << "Id: " << i + 1 << endl << "Nome: " << produto[i] << endl << "Quantidade: " << quantidade[i] << endl << "Preco: " << preco[i] << endl << endl;
        }
    }
    cout << "=================================================================================" << endl;


}
void Criarstock(int quantidade, int stockQuantidade[], string stockNome[], double stockPreco[]) {  //Criação de stock
  //        0           1             2
  //  quantidade | nome do produto |preço custo
  //
  //
    system("cls");
    cout << "------Stock-----" << endl;
    for (int i = 0; i < quantidade; i++) {
        do {
            cout << "Nome: ";
            cin >> stockNome[i];
        } while (stockNome[i] == "0");
        stockQuantidade[i] = obterInt(1, INT_MAX, "Quantidade: ");
        stockPreco[i] = obterDouble(0.01, DBL_MAX, "Preco: ");


    }
    system("cls");
}
int eliminarstock(int quantidadeStock, int* stockQuantidade, string* stockNome, double* stockPreco) {//Eliminar produto
    //system("cls");
    int id = 1;
    mostrarStock(quantidadeStock, stockQuantidade, stockNome, stockPreco);
    id = obterInt(1, quantidadeStock, "Insira o id que quer eliminar: ");



    int j = 0;
    for (int i = 0; i < quantidadeStock; i++) {

        if (i == quantidadeStock - 1 || i == id - 1) {
            stockQuantidade[i] = 0;
            stockNome[i] = "0";
            stockPreco[i] = 0;

        }
        if (i >= id - 1 && i != id - 1) {
            stockQuantidade[i] = stockQuantidade[i + 1];
            stockNome[i] = stockNome[i + 1];
            stockPreco[i] = stockPreco[i + 1];
        }


    }


    quantidadeStock = quantidadeStock - 1;

    mostrarStock(quantidadeStock, stockQuantidade, stockNome, stockPreco);
    system("pause");
    //system("cls");
    return quantidadeStock;

}
void stock(int quantidadeCliente, int quantidadeStock, int stockQuantidade[], string stockNome[], double stockPreco[], int  checkoutQuantidade[], double checkoutPreco[], string  NomeCliente[]) {//Menu stock
    int opcao;
    system("cls");
    do {

        cout << "------Stock-----" << endl;
        cout << "1 Adicionar Stock" << endl;
        cout << "2 Ver todo o stock" << endl;
        cout << "3 Ver stock" << endl;
        cout << "4 Eliminar stock" << endl;
        cout << "5 sair" << endl;
        //cout << "Insira: ";
        opcao = obterInt(1, 5, "Insira: ");
        switch (opcao) {
        case 1:
            Criarstock(quantidadeStock, stockQuantidade, stockNome, stockPreco);
            IFSTOCK = true;
            break;
        case 2:
            if (IFSTOCK == true) {
                mostrarStock(quantidadeStock, stockQuantidade, stockNome, stockPreco);
            }
            else {
                system("cls");
                cout << "Insira o stock" << endl;
            }
            break;
        case 3:
            if (IFSTOCK == true) {

                mostrarproduto(quantidadeStock, stockQuantidade, stockNome, stockPreco);
            }
            else {
                system("cls");
                cout << "Insira o stock" << endl;
            }
            break;
        case 4:
            quantidadeStock = eliminarstock(quantidadeStock, stockQuantidade, stockNome, stockPreco);
            break;
        case 5:
            menu(quantidadeCliente, quantidadeStock, stockQuantidade, stockNome, stockPreco, checkoutQuantidade, checkoutPreco, NomeCliente);
        }
    } while (opcao != 4);
}
double adicionarProduto(int stockQuantidadeCopia[], int quantidadeCliente, int quantidadeStock, int stockQuantidade[], string stockNome[], double stockPreco[], int  checkoutQuantidade[], double checkoutPreco[], string  NomeCliente[]) {//Compra produtos
    mostrarStock(quantidadeStock, stockQuantidade, stockNome, stockPreco);
    int codigo;
    int quantidade = 0;
    int nomeStock;
    int opcao;
    double totalPagamento = 0;
    int n = 2;

    cout << endl;
    do {

        do {
            codigo = obterInt(-1, quantidadeStock, "Insira o codigo do produto insira -1 para terminar:  ");
            codigo = codigo - 1;
            if (codigo == -2) {
                return totalPagamento;
            }
        } while (stockQuantidade[codigo] <= 0);



        quantidade = obterInt(1, stockQuantidade[codigo], "Quantidade: ");
        cout << fixed << setprecision(2);
        cout << "Este produto vai custar: " << (stockPreco[codigo] * quantidade) + (stockPreco[codigo] * quantidade) * 0.23 << " euros com iva incluido" << endl;
        cout << std::fixed;
        opcao = obterInt(1, 2, "Tem a certeza 1 sim 2 nao: ");
        if (opcao == 1) {
            system("cls");
            stockQuantidadeCopia[codigo] = quantidade;
            checkoutQuantidade[CCLIENTE + 1] = checkoutQuantidade[CCLIENTE + 1] + quantidade;
            stockQuantidade[codigo] = stockQuantidade[codigo] - quantidade;
            totalPagamento = totalPagamento + (stockPreco[codigo] + stockPreco[codigo] * 0.23) * quantidade;
            mostrarStock(quantidadeStock, stockQuantidade, stockNome, stockPreco);
        }
    } while (codigo != -2);
    return totalPagamento;
}
void vendaProd(int quantidadeCliente, int quantidadeStock, int stockQuantidade[], string stockNome[], double stockPreco[], int  checkoutQuantidade[], double checkoutPreco[], string  NomeCliente[]) {//Venda
    int opcao;
    int* stockQuantidadeCopia = new int[quantidadeStock];
    double total;
    for (int i = 0; i < quantidadeStock; i++) {
        stockQuantidadeCopia[i] = 0;
    }
    system("cls");
    checkoutQuantidade[CCLIENTE + 1] = 0;
    total = adicionarProduto(stockQuantidadeCopia, quantidadeCliente, quantidadeStock, stockQuantidade, stockNome, stockPreco, checkoutQuantidade, checkoutPreco, NomeCliente);
    system("cls");
    double pagamento;
    if (total > 0) {
        cout << "Total a  pagar: " << total << "euros com iva incluido" << endl;
        pagamento = obterDouble(total, DBL_MAX, "Insira o pagamento:");

        cout << "Troco: " << pagamento - total << endl;
        int talaoif;
        CCLIENTE++;
        cout << "Digite o seu nome de cliente: ";
        cin >> NomeCliente[CCLIENTE];
        checkoutPreco[CCLIENTE] = total;
        talaoif = obterInt(1, 2, "Vai querer talao? 1 sim 2 nao:  ");



        if (talaoif == 1) {
            talao(quantidadeStock, NomeCliente[CCLIENTE], stockQuantidadeCopia, stockNome, stockPreco, total, pagamento);
        }
        system("cls");
    }
}
void menu(int quantidadeCliente, int quantidadeStock, int stockQuantidade[], string stockNome[], double stockPreco[], int  checkoutQuantidade[], double checkoutPreco[], string  NomeCliente[]) {//Menu principal


    int opcao;
    system("cls");
    do {

        cout << "------Menu-----" << endl;
        cout << "1 Stock" << endl;
        cout << "2 Venda" << endl;
        cout << "3 Clientes" << endl;
        cout << "4 sair" << endl;
        opcao = obterInt(1, 4, "Insira: ");
        switch (opcao) {
        case 1:
            stock(quantidadeCliente, quantidadeStock, stockQuantidade, stockNome, stockPreco, checkoutQuantidade, checkoutPreco, NomeCliente);
            break;
        case 2:
            if (IFSTOCK == true) {
                vendaProd(quantidadeCliente, quantidadeStock, stockQuantidade, stockNome, stockPreco, checkoutQuantidade, checkoutPreco, NomeCliente);

            }
            else {
                system("cls");
                cout << "Insira o stock" << endl;
            }
            break;
        case 3:
            if (CCLIENTE > 0) {
                Cliente(quantidadeCliente, quantidadeStock, stockQuantidade, stockNome, stockPreco, checkoutQuantidade, checkoutPreco, NomeCliente);
            }
            else {
                system("cls");
                cout << "Nao tem Clientes" << endl;
            }
            break;
        case 4:
            break;
        }
    } while (opcao != 4);
}
void Trabalho() {
    int linhas = 3, colunas = 2;
    string** mat = new string * [linhas];
    cout << "Trabalho realizado por: " << endl;
    cout << "========================" << endl;
    for (int i = 0; i < 3; i++) {
        mat[i] = new string[colunas];
    }
    mat[0][0] = "Antonio Barbosa";
    mat[0][1] = "T0121073";
    mat[1][0] = "Bernardo Taveira";
    mat[1][1] = "T0121075";
    mat[2][0] = "Pedro Teixeira";
    mat[2][1] = "T0121084";
    for (int i = 0; i < 3; i++) {
        cout << "Nome: " << mat[i][0] << endl << "ID: " << mat[i][1] << endl;
    }
    cout << endl << "TURMA: TPSI 10.21" << endl;
    cout << "=========================" << endl;
    system("pause");
    system("cls");
}
int main() {//Main


    int quantidadeCliente = 10;
    int quantidadeStock;
    Trabalho();
    cout << "Bem vindo ao  Vendor  app vamos iniciar..." << endl;
    quantidadeStock = obterInt(1, INT_MAX, "Insire a quantidade de linhas de produtos: ");
    int* stockQuantidade = new int[quantidadeStock];
    string* stockNome = new string[quantidadeStock];
    double* stockPreco = new double[quantidadeStock];
    int* checkoutQuantidade = new int[quantidadeCliente];
    double* checkoutPreco = new double[quantidadeCliente];
    string* NomeCliente = new string[quantidadeCliente];
    menu(quantidadeCliente, quantidadeStock, stockQuantidade, stockNome, stockPreco, checkoutQuantidade, checkoutPreco, NomeCliente);
    system("cls");
}
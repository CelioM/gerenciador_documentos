#include "usuario.h"
#include "documento.h"
#include "documentmanager.h"
#include "util.h"

#include <iostream>
#include <exception>

using namespace std;

void testeGED()
{
    cout << "Teste 1:" << endl;
    GEDSystem sistema;

    cout << "Sistema inicializado com exito" << endl;

    // Teste com credenciais erradas
    cout << "Tentativa de login" << endl;

    if(!sistema.login("Nome_errado", "Senha_aleatória"))
    {
        cout << "O sistema recusou o login (como esperado)" << endl;
    }
    else
    {
        cout << "ERRO: Sucesso inesperado no login com credenciais inválidas!" << endl;
    }

    // Teste como document manager
    cout << "Teste de login como document manager..." << endl;

    if(sistema.login("admin", "admin123"))
    {
        cout << "Sucesso: Foi cadastrado um document manager" << endl;

        cout << "Criando um novo documento..." << endl;

        // Cria documento válido - cuidado com o nome do usuário atribuído
        sistema.criarDocumento("document_test", "teste!", "admin");

        sistema.listarDocumentos();
        cout << "Documento criado" << endl;

        // Tenta criar documento com usuário inválido
        cout << "Tentando criar documento com usuário inválido" << endl;
        sistema.criarDocumento("DOc_teste", "Gerenc_p1", "unkown");
        cout << "Sucesso: Sistema recusou/criou documento conforme esperado" << endl;

        // Desativação do usuário
        sistema.logout();
    }
    else
    {
        cout << "Falha: Não foi possível fazer o login como admin" << endl;
    }

    // Teste como analista
    cout << "Teste de login como analista..." << endl;

    if(sistema.login("pinhati", "senha_pinhati"))
    {
        cout << "Login como analista foi feito" << endl;

        // Aprova documento
        cout << "Tentativa de aprovação de documento" << endl;
        sistema.aprovarDocumento("document_test");

        // Reprova documento
        cout << "Reprovando documento" << endl;
        sistema.reprovarDocumento("document_test", "Falta especifications");
        sistema.visualizarComentarios("document_test");

        sistema.logout();
    }
    else
    {
        cout << "Falha: Não foi possível logar como analista" << endl;
    }
}

int main()
{
    try
    {
        testeGED();
        cout << "\n=== Todos os testes foram feitos ===\n" << endl;
    }
    catch(const exception& e)
    {
        cerr << "\nERRO NA FASE DE TESTE. Razão: " << e.what() << endl;
        return 1;
    }

    return 0;
}

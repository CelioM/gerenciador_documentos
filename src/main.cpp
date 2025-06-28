#include "usuario.h"
#include "documento.h"
#include "documentmanager.h"
#include "util.h"

#include <iostream>
#include <exception>

using namespace std;

void testeGED()
{
	cout << " Teste 1:" <endl;
	GEDSystem sistema;

	cout << "Sistema inicializado com exito" << endl;
	
	//Teste com credenciais erradas
	cout << "Tentativa de login" << endl;

	if(!sistema.login ("Nome_errado", "Senha_aleatória")
	{
		cout << "O sistema recusou o login(como esperado)" << endl;
	}
	else
	{
		cout << "Sucesso no gerenciamento de cadastramento!" << endl;
	}

	//Teste como documentmanager

	cout << "Teste de login como document manager..." << endl;

	if(sistema.login("admin", "admin123")
	{
		cout << "Sucesso foi cadastrado um document manager" << endl;

		cout << "Criando um novo documento..." << endl;
		
		//Cria documento válido
		sistema.criarDocumento("document_test","teste!", "anonimos");
		sistema.listarDocumentos();
		cout << "Documento criado" << endl;

		//Tenta criar documento com usuário 
		cout << "Tentando criar documento com usuário inválido" << endl;
		sistema.criarDocumento("DOc_teste","Gerenc_p1","unkown") << endl;
		cout << "sucesso na criacao" << endl;
		
		//Desativação do usuário
		sistema.logout();
	}	
	else
	{
		cout << "Falha nao foi possível fazer o login como admin" << endl;
	}

	//Teste como analista
	
	cout << "Teste de login como analista..." << endl;

	if(sistema.login("pinhati","senha_pinhati"))
	{
		cout << "Login como analista foi feito" << endl;

		//aprova documento
		cout << "Tentativa de aprovação de documento" << endl;
		sistema.aprovarDocumento("DOC-001");

		//reprova
		cout<< "Reprovando documento" << endl;
		sistema.reprovarDocumento("DOC-001","Falta especifications");
		sistema.visualizarComentarios("DOC-001");

		sistema.logout();
	}
	else
	{
		cout << "Falha não foi possível logar como analista" << endl;
	}

}

int main()
{
	try
	{
		testeGED();
		cout << "\n=== Todos os teste foram feitos ===\n" << endl;	
	}
	catch(const exception& e)
	{
		cerr << "\nERRO NA FASE DE TESTE" << "razao: "  << e.what() << endl;
		return 1;
	}

	return 0;
}

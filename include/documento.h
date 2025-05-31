#ifndef DOCUMENTOS_HPP
#define DOCUMENTOS_HPP

#include <iostream>
#include <string>

class Documentos
{
private:
	string nome;
	string titulo;
	int versao;
	string status;
	string criador;

public:

	Documentos(std::string& nome, std::string& titulo, int versao, std::string& status, std::string& criador) : nome(nome), titulo(titulo), versao(0), status(status), criador(criador) {} 

	string getNome() {return nome;}
	
	string getTitulo() {return titulo;}

	string getStatus() {return status;}

	int getVersao() {return versao;}

	void atualizarStatus()
	{
		
	}

	void salvarComoArquivo()
	{

	}

};

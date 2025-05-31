#ifndef USUARIO_HPP
#define USUARIO_HPP

#include <iostream>
#include <string>

class Usuario
{
private:
	std::string nome;
	std::string status;
	std::string comentarios;
	std::string horario;
	
public:
	Usuario(const std::string& nome, const std::string& status, const std::string& comentarios, const std::string& horario) : nome(nome), status(status),comentarios(comentarios),horario(horario) {}

	//Getters

	std::string getNome() const {return nome;}
	std::string getStatus() const {return status;}
	std::string getComentarios() const {return comentarios;}
	std::string getHorario() const {return horario;}

	//Setters(definições)

	void setNome(const std::string& n) {nome = n;}
	void setStatus(const std::string& s) {status = s;}
	void setComentarios(const std::string& c) {comentarios = c;}
	void setHorario(const std::string h) {horario = h;}

	//Exibição de informações

	void exibir() const
	{
		std::cout << nome << "O status: " << status << "\n";
		std::cout << "Comentarios: " << comentarios << "\n";
		std::cout << " Horario: " << horario << std::endl;
	}
};

#endif

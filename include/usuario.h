#ifndef USUARIO_HPP
#define USUARIO_HPP

#include <iostream>
#include <string>
#include <vector>

class Usuario
{
private:
	std::string nome_;
	std::string comentarios_;
	std::string senha_;
	std::string tipo_;
	
public:
	Usuario(const std::string& nome, const std::string& comentarios, const std::string& senha,const std::string& tipo) : nome_(nome), comentarios_(comentarios),senha_(senha), tipo_(tipo) {}

	//Getters

	std::string getNome() const {return nome_;}
	std::string getComentarios() const {return comentarios_;}
	std::string getTipo() const {return tipo_;}

	//Setters(definições)

	void setNome(const std::string& n) {nome_ = n;}
	void setComentarios(const std::string& c) {comentarios_ = c;}
	void setSenha(const std::string s) {senha_ = s;}
	void setTipo(const std::string& t) {tipo_ = t;}

	void status() const;
	static bool login(const std::vector<Usuario>& usuarios, const std::string& nome,const std::string& senha);
};

struct TipoUsuario
{
	std::vector<std::string> tipos;
	Usuario usuario;
};

#endif

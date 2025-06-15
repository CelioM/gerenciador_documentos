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

	// Getters
    std::string getNome() const { return nome_; }
    std::string getComentarios() const { return comentarios_; }
    std::string getSenha() const { return senha_; }
    std::string getTipo() const { return tipo_; }

    // Setters
    void setNome(const std::string& n) { nome_ = n; }
    void setComentarios(const std::string& c) { comentarios_ = c; }
    void setSenha(const std::string& s) { senha_ = s; }
    void setTipo(const std::string& t) { tipo_ = t; }

 	 void status() const 
	 {
        std::cout << "Usuário: " << nome_ << "\n";
        std::cout << "Tipo: " << tipo_ << "\n";
        if (!comentarios_.empty()) 
		  {
            std::cout << "Comentários: " << comentarios_ << "\n";
        }
    }

    static bool login(const std::vector<Usuario>& usuarios, 
                     const std::string& nome, const std::string& senha) 
	 {
        for (const auto& usuario : usuarios) 
		  {
            if (usuario.nome_ == nome && usuario.senha_ == senha) 
				{
                return true;
            }
        }
        return false;
    };

	struct TipoUsuario 
	{
		static const std::string DOCUMENT_MANAGER;
    	static const std::string ANALISTA;
    
    	static std::vector<std::string> getTipos()
		{
        return {DOCUMENT_MANAGER, ANALISTA};
    	}
	};

	const std::string TipoUsuario::DOCUMENT_MANAGER = "DocumentManager";
	const std::string TipoUsuario::ANALISTA = "Analista";
	 

#endif

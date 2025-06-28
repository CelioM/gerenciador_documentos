#ifndef USUARIO_HPP
#define USUARIO_HPP

#include <iostream>
#include <string>
#include <vector>

// Enum global
enum TipoUsuario {
    NORMAL = 0,
    DOCUMENT_MANAGER = 1,
    ANALISTA = 2
};

class Usuario
{
private:
    std::string nome_;
    std::string senha_;
    int tipo_;
    std::string comentarios_;

public:
    Usuario() {}
    Usuario(const std::string& nome, const std::string& senha, int tipo, const std::string& comentarios)
        : nome_(nome), senha_(senha), tipo_(tipo), comentarios_(comentarios) {}

    // Getters
    std::string getNome() const { return nome_; }
    std::string getSenha() const { return senha_; }
    int getTipo() const { return tipo_; }
    std::string getComentarios() const { return comentarios_; }

    // Setters
    void setNome(const std::string& n) { nome_ = n; }
    void setSenha(const std::string& s) { senha_ = s; }
    void setTipo(int t) { tipo_ = t; }
    void setComentarios(const std::string& c) { comentarios_ = c; }

    void status() const {
        std::cout << "Usuário: " << nome_ << "\n";
        std::cout << "Tipo: " << tipo_ << "\n";
        if (!comentarios_.empty()) {
            std::cout << "Comentários: " << comentarios_ << "\n";
        }
    }
};

#endif // USUARIO_HPP

#ifndef USUARIO_H
#define USUARIO_H

#include <string>

enum class TipoUsuario { CRIADOR, ANALISTA };

class Usuario {
public:
    Usuario(const std::string& nome, const std::string& senha, TipoUsuario tipo);

    static bool login();
    static TipoUsuario getUsuarioAtualTipo();

private:
    std::string nome;
    std::string senha;
    TipoUsuario tipo;

    static bool verificarCredenciais(const std::string& nome, const std::string& senha, TipoUsuario& tipo);
};

#endif

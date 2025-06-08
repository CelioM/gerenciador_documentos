#include "../include/usuario.h"
#include <iostream>

static TipoUsuario usuarioAtual;

Usuario::Usuario(const std::string& nome, const std::string& senha, TipoUsuario tipo)
    : nome(nome), senha(senha), tipo(tipo) {}

bool Usuario::login() {
    std::string nomeInput, senhaInput;
    std::cout << "Digite seu nome de usuário: ";
    std::cin >> nomeInput;
    std::cout << "Digite sua senha: ";
    std::cin >> senhaInput;

    return verificarCredenciais(nomeInput, senhaInput, usuarioAtual);
}

TipoUsuario Usuario::getUsuarioAtualTipo() {
    return usuarioAtual;
}

bool Usuario::verificarCredenciais(const std::string& nome, const std::string& senha, TipoUsuario& tipo) {
    if (nome == "admin" && senha == "admin123") {
        tipo = TipoUsuario::CRIADOR;
        return true;
    } else if (nome == "ana" && senha == "ana123") {
        tipo = TipoUsuario::ANALISTA;
        return true;
    }
    std::cout << "Credenciais inválidas.\n";
    return false;
}
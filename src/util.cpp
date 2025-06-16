#include "../include/util.h"
#include <filesystem>
#include <chrono>
#include <ctime>

std::string Util::obterCaminhoDesktop() {
    const char* home = getenv("HOME");
    return std::string(home);// + "/Área de Trabalho"; - não funcionou no meu
}

std::string Util::obterDataHoraAtual() {
    auto agora = std::chrono::system_clock::now();
    std::time_t tempo = std::chrono::system_clock::to_time_t(agora);
    return std::string(std::ctime(&tempo));
}

bool Util::arquivoExiste(const std::string& caminho) {
    return std::filesystem::exists(caminho);
}

void Util::criarDiretorioSeNaoExistir(const std::string& caminho) {
    if (!std::filesystem::exists(caminho)) {
        std::filesystem::create_directory(caminho);
    }
}

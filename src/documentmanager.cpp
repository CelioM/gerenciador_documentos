#include "../include/documentmanager.h"
#include "../include/util.h"
#include <fstream>
#include <filesystem>
#include <iostream>

DocumentManager::DocumentManager(const std::string& diretorioBase) {
    caminhoPasta = diretorioBase + "/GED_Documentos";
    caminhoCSV = caminhoPasta + "/documentos.csv";
    criarEstrutura();
}

void DocumentManager::criarEstrutura() {
    criarPastaSeNaoExistir();
    criarCSVSeNaoExistir();
}

void DocumentManager::criarPastaSeNaoExistir() {
    Util::criarDiretorioSeNaoExistir(caminhoPasta);
}

void DocumentManager::criarCSVSeNaoExistir() {
    if (!Util::arquivoExiste(caminhoCSV)) {
        std::ofstream arquivo(caminhoCSV);
        arquivo << "Nome,Titulo,Status,Revisao,Comentario,Horario,Atribuido\n";
    }
}

void DocumentManager::criarDocumento(const std::string& nome, const std::string& titulo, const std::string& atribuido) {
    std::ofstream csv(caminhoCSV, std::ios::app);
    std::string horario = Util::obterDataHoraAtual();
    csv << nome << "," << titulo << ",00A,," << horario << "," << atribuido << "\n";
    criarArquivoSimuladoPDF(nome, titulo);
}

void DocumentManager::criarArquivoSimuladoPDF(const std::string& nome, const std::string& titulo) {
    std::ofstream arquivo(caminhoPasta + "/" + nome);
    arquivo << "TÍTULO: " << titulo << "\nDOCUMENTO CRIADO.\n";
}

void DocumentManager::excluirDocumento(const std::string& nome) {
    std::filesystem::remove(caminhoPasta + "/" + nome);
    // Regrava o CSV sem a linha correspondente (exercício opcional)
}
void DocumentManager::listarArquivos() {
    try {
        for (const auto& entry : std::filesystem::directory_iterator(caminhoPasta)) {
            if (entry.is_regular_file()) {
                std::cout << entry.path().filename().string() << std::endl;
            }
        }
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Erro ao acessar o diretório: " << e.what() << std::endl;
    }
}
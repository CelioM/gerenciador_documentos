#ifndef DOCUMENTMANAGER_H
#define DOCUMENTMANAGER_H

#include <string>

class DocumentManager {
public:
    DocumentManager(const std::string& diretorioBase);
    void criarDocumento(const std::string& nome, const std::string& titulo, const std::string& atribuido);
    void excluirDocumento(const std::string& nome);
    void criarEstrutura(); // Cria pasta e CSV automaticamente
private:
    std::string caminhoPasta;
    std::string caminhoCSV;
    void criarCSVSeNaoExistir();
    void criarPastaSeNaoExistir();
    void criarArquivoSimuladoPDF(const std::string& nome, const std::string& titulo);
};

#endif

#pragma once

#include <string>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

namespace Util {
    fs::path  obterCaminhoDesktop();
    std::string obterDataHoraAtual();
    bool arquivoExiste(const std::string& caminho);
    void criarDiretorioSeNaoExistir(const std::string& caminho);
	
	bool limparDiretorio(const fs::path& caminho);
	std::vector<std::string> limparArquivoNoDiretorio(const fs::path& caminho);

	//Funções de validação
	bool validarNomeDocumento(const std::string& nome);
	bool validarRevisaoDocumento(const std::string& revisao);

	std::string gerarNomeArquivoDocumento(const std::string& nomeDoc, const std::string& revisao);
	std::string proximaRevisao(const std::string& revisaoAtual);
}


#ifndef UTIL_H
#define UTIL_H

#include <string>

namespace Util {
    std::string obterCaminhoDesktop();
    std::string obterDataHoraAtual();
    bool arquivoExiste(const std::string& caminho);
    void criarDiretorioSeNaoExistir(const std::string& caminho);
}

#endif

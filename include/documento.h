
#ifndef DOCUMENTO_H
#define DOCUMENTO_H

#include <string>
#include <vector>

class Documento {
public:
    Documento(const std::string& nome);
    void aprovar();
    void reprovar(const std::string& comentario);
    void atenderComentario();
    void carregarDados();
    void salvarDados();

private:
    std::string nome;
    std::string titulo;
    std::string status;
    std::string revisao;
    std::string comentario;
    std::string horario;
    std::string atribuido;

    void atualizarHorario();
    std::string proximaRevisao(const std::string& atual);
};

#endif

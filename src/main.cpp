#include "../include/documentmanager.h"
#include "../include/documento.h"
#include "../include/usuario.h"
#include "../include/util.h"
#include <iostream>

int main() {
    std::string comando;
    std::cout << "Digite 'entrar' para iniciar o login: ";
    std::cin >> comando;

    if (comando != "entrar") {
        std::cout << "Comando inválido. Encerrando programa.\n";
        return 0;
    }

    Usuario usuario("","",TipoUsuario::CRIADOR);
    if (!usuario.login()) return 0;

    TipoUsuario tipo = usuario.getUsuarioAtualTipo();
    DocumentManager manager(Util::obterCaminhoDesktop());

    while (true) {
        std::string opcao;
        std::cout << "\nMenu:\n";
        if (tipo == TipoUsuario::CRIADOR) {
            std::cout << "1. Criar documento\n2. Excluir documento\n3. Listar Documentos\n0. Sair\n";
        } else {
            std::cout << "1. Aprovar documento\n2. Reprovar documento\n3. Atender comentário\n4. Listar Documentos\n0. Sair\n";
        }

        std::cout << "Escolha uma opção: ";
        std::cin >> opcao;

        if (opcao == "0") break;

        if (tipo == TipoUsuario::CRIADOR) {
            if (opcao == "1") {
                std::string nome, titulo, atribuido;
                std::cout << "Nome do documento (ex: abc-nomedoc.pdf): ";
                std::cin >> nome;
                std::cin.ignore();
                std::cout << "Título do documento: ";
                std::getline(std::cin, titulo);
                std::cout << "Atribuído a (opcional): ";
                std::getline(std::cin, atribuido);
                manager.criarDocumento(nome, titulo, atribuido);
            } else if (opcao == "2") {
                std::string nome;
                std::cout << "Nome do documento a excluir: ";
                std::cin >> nome;
                manager.excluirDocumento(nome);
            } else if (opcao == "3") {
                manager.listarArquivos();
            }
        } else if (tipo == TipoUsuario::ANALISTA) {
            

            if (opcao == "1") {
                std::string nome;
                std::cout << "Nome do documento: ";
                std::cin >> nome;
                Documento doc(nome);
                doc.aprovar();
            } else if (opcao == "2") {
                std::string nome;
                std::cout << "Nome do documento: ";
                std::cin >> nome;
                Documento doc(nome);
                std::cin.ignore();
                std::string comentario;
                std::cout << "Comentário da reprovação: ";
                std::getline(std::cin, comentario);
                doc.reprovar(comentario);
            } else if (opcao == "3") {
                std::string nome;
                std::cout << "Nome do documento: ";
                std::cin >> nome;
                Documento doc(nome);
                std::cout << std::endl;
                doc.atenderComentario();
            } else if (opcao == "4") {
                manager.listarArquivos();
            }
        }
    }
    std::cout << "Encerrando o programa.\n";
    return 0;
}
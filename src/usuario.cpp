#include "usuario.h"
#include "documento.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <ctime>
#include <iomanip>
#include <chrono>
#include <filesystem>

namespace fs = std::filesystem;
using namespace std;

// Representar o comentario do documento
struct texto_comentario {
    string autor;
    string texto;
    string dataHora;
    bool atendido;
};

// ------------------------ Classe Usuario ------------------------
class Usuario {
private:
    string nome;
    string senha;
    int tipo; // Você pode criar um enum para o tipo
    string comentarios;
public:
    Usuario() {}
    Usuario(string n, string s, int t, string c)
        : nome(n), senha(s), tipo(t), comentarios(c) {}

    string getNome() const { return nome; }
    string getSenha() const { return senha; }
    int getTipo() const { return tipo; }
    string getComentarios() const { return comentarios; }
};

// ---------------------- Classe Documento ------------------------
class Documento {
public:
    string nome;
    string titulo;
    string status;
    string revisao;
    string dataHora;
    string dataHoraRevisao;
    string atribuidoA;
    string caminho;
    string caminhoArquivo;

    Documento() {}
};

// Enum exemplo para tipos de usuário
enum TipoUsuario {
    NORMAL = 0,
    DOCUMENT_MANAGER = 1
};

// --------------------- Classe GEDSystem -------------------------

class GEDSystem {
private:
    vector<Usuario> usuarios;
    vector<Documento> documentos;
    Usuario* usuarioAtual;
    string arquivoCSV;
    string pastaDocumentos;
    string arquivoUsuarios;

    string getCurrentDateTime() {
        auto now = chrono::system_clock::now();
        time_t now_c = chrono::system_clock::to_time_t(now);
        tm local_tm;
#ifdef _WIN32
        localtime_s(&local_tm, &now_c);
#else
        localtime_r(&now_c, &local_tm);
#endif
        char buffer[80];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &local_tm);
        return string(buffer);
    }

    // Função que carrega usuários do CSV
    void carregarUsuarios() {
        usuarios.clear();
        ifstream arquivo(arquivoUsuarios);

        if (!arquivo.is_open()) {
            cerr << "Erro: Não foi possível abrir o arquivo de usuários: " << arquivoUsuarios << endl;
            return;
        }

        string linha;
        int linhaNum = 0;

        while (getline(arquivo, linha)) {
            linhaNum++;
            stringstream ss(linha);
            string campo;
            vector<string> campos;

            while (getline(ss, campo, ';')) {
                campos.push_back(campo);
            }

            if (campos.size() >= 4) {
                Usuario user(campos[0], campos[1], stoi(campos[2]), campos[3]);
                usuarios.push_back(user);
            } else {
                cout << "A linha: " << linhaNum << " ignorada. Campos insuficientes" << endl;
            }
        }
        arquivo.close();
    }

    void salvarUsuarios() {
        ofstream arquivo(arquivoUsuarios);

        if (!arquivo.is_open()) {
            cerr << "Erro: Nao foi possivel abrir arquivo para salvar usuarios" << endl;
            return;
        }

        for (const auto& user : usuarios) {
            arquivo << user.getNome() << ";" << user.getSenha() << ";" << user.getTipo() << ";" << user.getComentarios() << endl;
        }
        arquivo.close();
    }

    void carregarDocumentos() {
        documentos.clear();
        ifstream arquivo(arquivoCSV);

        if (!arquivo.is_open()) return;

        string linha;
        int linhaNum = 0;

        while (getline(arquivo, linha)) {
            linhaNum++;
            stringstream ss(linha);
            string campo;
            vector<string> campos;

            while (getline(ss, campo, ';')) {
                campos.push_back(campo);
            }

            if (campos.size() >= 6) {
                Documento doc;
                doc.nome = campos[0];
                doc.titulo = campos[1];
                doc.status = campos[2];
                doc.revisao = campos[3];
                doc.dataHora = campos[4];
                doc.atribuidoA = campos[5];
                doc.caminho = campos.size() > 6 ? campos[6] : "";
                documentos.push_back(doc);
            } else {
                cout << "Linha " << linhaNum << " ignorada: campos insuficientes." << endl;
            }
        }
        arquivo.close();
    }

    string escapeCSVField(const string& field) {
        string escaped = field;
        if (escaped.find(';') != string::npos || escaped.find('"') != string::npos) {
            size_t pos = 0;
            while ((pos = escaped.find('"', pos)) != string::npos) {
                escaped.insert(pos, "\"");
                pos += 2;
            }
            escaped = "\"" + escaped + "\"";
        }
        return escaped;
    }

    void salvarDocumentos() {
        ofstream arquivo(arquivoCSV);

        if (!arquivo.is_open()) {
            cerr << "Erro ao abrir arquivo CSV para escrita" << endl;
            return;
        }

        for (const auto& doc : documentos) {
            arquivo << escapeCSVField(doc.nome) << ";"
                << escapeCSVField(doc.titulo) << ";"
                << escapeCSVField(doc.status) << ";"
                << escapeCSVField(doc.revisao) << ";"
                << escapeCSVField(doc.dataHora) << ";"
                << escapeCSVField(doc.atribuidoA) << ";"
                << escapeCSVField(doc.caminho) << "\n";
        }
        arquivo.close();
    }

    void criarArquivoDocumento(Documento& doc) {
        fs::path caminhoCompleto = fs::path(pastaDocumentos) / (doc.nome + "_" + doc.revisao + ".txt");
        ofstream arquivo(caminhoCompleto.string());
        if (arquivo.is_open()) {
            arquivo << "Título: " << doc.titulo << "\n";
            arquivo << "Status: " << doc.status << "\n";
            arquivo << "Revisão: " << doc.revisao << "\n";
            arquivo << "Última revisão: " << doc.dataHora << "\n";
            arquivo << "Atribuído a: " << doc.atribuidoA << "\n\n";
            arquivo << "Conteúdo do documento...\n";
            arquivo.close();
            doc.caminhoArquivo = caminhoCompleto.string();
        } else {
            cerr << "Erro ao criar arquivo do documento." << endl;
        }
    }

    void avancarRevisao(Documento& doc) {
        if (doc.revisao == "00A")
            doc.revisao = "00B";
        else if (doc.revisao == "00B")
            doc.revisao = "00C";
        else if (doc.revisao == "00C")
            doc.revisao = "00";

        doc.dataHora = getCurrentDateTime();
    }

    bool isDocumentManager() const {
        return usuarioAtual && usuarioAtual->getTipo() == DOCUMENT_MANAGER;
    }

    bool usuarioExiste(const string& nomeUsuario) const {
        for (const auto& user : usuarios) {
            if (user.getNome() == nomeUsuario) {
                return true;
            }
        }
        return false;
    }

public:
    GEDSystem() {
        pastaDocumentos = string(getenv("USERPROFILE")) + "/Desktop/DocumentosGED";
        arquivoCSV = pastaDocumentos + "/documentos.csv";
        arquivoUsuarios = pastaDocumentos + "/usuarios.csv";

        if (!fs::exists(pastaDocumentos)) {
            fs::create_directories(pastaDocumentos);
        }

        carregarUsuarios();

        if (usuarios.empty()) {
            Usuario admin("admin", "admin123", DOCUMENT_MANAGER, "Administrador do sistema");
            usuarios.push_back(admin);
            salvarUsuarios();
        }

        carregarDocumentos();
        usuarioAtual = nullptr;
    }

    ~GEDSystem() {
        salvarDocumentos();
        salvarUsuarios();
    }

    bool login(const string& nome, const string& senha) {
        for (auto& user : usuarios) {
            if (user.getNome() == nome && user.getSenha() == senha) {
                usuarioAtual = &user;
                return true;
            }
        }
        return false;
    }

    void logout() {
        usuarioAtual = nullptr;
    }

    void criarDocumento(const string& nome, const string& titulo, const string& atribuidoA) {
        if (!isDocumentManager()) {
            cout << "Apenas Document Managers podem criar documentos." << endl;
            return;
        }

        if (!usuarioExiste(atribuidoA)) {
            cout << "Usuário atribuído não encontrado." << endl;
            return;
        }

        Documento novoDoc;
        novoDoc.nome = nome;
        novoDoc.titulo = titulo;
        novoDoc.status = "Em análise";
        novoDoc.revisao = "00A";
        novoDoc.dataHora = getCurrentDateTime();
        novoDoc.atribuidoA = atribuidoA;

        criarArquivoDocumento(novoDoc);
        documentos.push_back(novoDoc);
        salvarDocumentos();

        cout << "Documento criado com sucesso." << endl;
    }

    void exibirMenuPrincipal() {
        cout << "\nSistema de Gerenciamento de Documentos (GED)\n";
        cout << "1. Listar documentos\n";
        if (isDocumentManager()) {
            cout << "2. Criar documento\n";
            cout << "3. Excluir documento\n";
        }
        cout << "4. Aprovar documento\n";
        cout << "5. Reprovar documento com comentário\n";
        cout << "6. Visualizar comentários\n";
        cout << "7. Atender comentário\n";
        cout << "8. Sair\n";
        cout << "Escolha uma opção: ";
    }
};

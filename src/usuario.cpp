#include "usuario.hpp"
#include "documento.hpp"

#include <ctime>
#include <iomanip>
#include <chrono>
#include <vector>
#include <sstream>

using namespace std;

//Representar o comentario do documento
struct texto_comentario
{
	string autor;
	string texto;
	string dataHora;
	bool atendido;
};

//Classe para o sistema de gerenciamento eletrônico de dados

class Usuario
{
private:
	vector<Usuario> usuarios;
	vector<Documentos> documentos;
	Usuario* usuarioAtual;
	string arquivoCsv;
	string pastaDocumentos;
	string arquivoUsuarios;

	string CurrentData_time()
	{
		//Obtém tempo atual como um ponto de tempo
		auto now = std::chrono::system_clock::now();

		//Converte o tempo para uma estrutura tm para facilitar a formatação
		std::time_t agora = std::chrono::system_clock::to_time_t(agora);
		std::time_t agora_tm = *std::localtime(&agora c);

		//Formata data e hora usando strftime
		char buffer[80];
		std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &agora_tm);
		return string(buffer);
	}
	
	//Função que carrega usuários do CSV
	void carregarUsuarios()
	{
		usuarios.clear();
		std::ifstream arquivo(arquivoUsuarios);

		if(!arquivo.is_open())
		{
			std::cerr << "Erro: Não foi possível abrir o arquivo de usuários: "<< arquivoUsuarios << endl;
			return;
		}

		std::string linha;
		int linhaNum = 0;

		while(getline(arquivo,linha))
		{
			linhaNum++;
			std::stringstream ss(linha);
			std::string campo;
			vector<string> campos;

			while(getline(ss, campo, ';'))
			{
				campos.push_back(campo);
			}

			if(campos.size() >= 4)
			{
				//Validações dos campos
				Usuario user(campos[0], campos[1], campos[2], campos[3]);
				usuarios.push_back(user);
			}
			else
			{
				cout << "A linha: " << linhaNum << " ignorada. Campos insuficientes" << endl;
			}
		}
		arquivo.close();
	}

	void salvarUsuarios()
	{
		std::ofstream arquivo(arquivoUsuarios);
		
		if(!arquivo.is_open())
		{
			std::cerr << "Erro: Nao foi possivel abrir arquivo para salvar usuarios" << endl;
			return;
		}

		for(const auto& user: usuarios)
		{
			arquivo << user.getNome() << ";" << user.getComentarios() << ";" << user.getSenha() << ";" << user.getTipo() << endl;
		}
		arquivo.close();
	}

	//Função para carregar documentos do csv
void carregarDocumentos()
{
    documentos.clear();
    std::ifstream arquivo(arquivoCSV);

    if (!arquivo.is_open()) return;

    std::string linha;
    int linhaNum = 0;

    while (getline(arquivo, linha))
    {
        linhaNum++;
        std::stringstream ss(linha);
        std::string campo;
        std::vector<std::string> campos;

        while (getline(ss, campo, ';'))
        {
            campos.push_back(campo);
        }

        if (campos.size() >= 6)
        {
            Documento doc;

            doc.nome = campos[0];
            doc.titulo = campos[1];
            doc.status = campos[2];
            doc.revisao = campos[3];
            doc.dataHora = campos[4];         
            doc.atribuidoA = campos[5];
            doc.caminho = campos.size() > 6 ? campos[6] : "";

            documentos.push_back(doc);
        }
        else
        {
            std::cout << "Linha " << linhaNum << " ignorada: campos insuficientes." << std::endl;
        }
    }
    arquivo.close();
}

std::string escapeCSVField(const std::string& field)
{
    std::string escaped = field;
    if (escaped.find(';') != std::string::npos || escaped.find('"') != std::string::npos)
    {
        size_t pos = 0;
        while ((pos = escaped.find('"', pos)) != std::string::npos)
        {
            escaped.insert(pos, "\"");
            pos += 2;
        }
        escaped = "\"" + escaped + "\"";
    }
    return escaped;
}

void salvarDocumentos()
{
    std::ofstream arquivo(arquivoCSV);

    if (!arquivo.is_open())
    {
        std::cerr << "Erro ao abrir arquivo CSV para escrita" << std::endl;
        return;
    }

    for (const auto& doc : documentos)
    {
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
	
// Função para criar arquivo de documento simulado
void criarArquivoDocumento(Documento& doc)
{
    fs::path caminhoCompleto = pastaDocumentos / (doc.nome + "_" + doc.revisao + ".txt");
    std::ofstream arquivo(caminhoCompleto.string());
    if (arquivo.is_open()) 
    {
        arquivo << "Título: " << doc.titulo << "\n";
        arquivo << "Status: " << doc.status << "\n";
        arquivo << "Revisão: " << doc.revisao << "\n";
        arquivo << "Última revisão: " << doc.dataHoraRevisao << "\n";
        arquivo << "Atribuído a: " << doc.atribuidoA << "\n\n";
        arquivo << "Conteúdo do documento...\n";
        arquivo.close();
        doc.caminhoArquivo = caminhoCompleto.string();
    } 
    else
    {
        std::cerr << "Erro ao criar arquivo do documento." << std::endl;
    }
}

void avancarRevisao(Documento& doc)
{
    if (doc.revisao == "00A")
        doc.revisao = "00B";
    else if (doc.revisao == "00B")
        doc.revisao = "00C";
    else if (doc.revisao == "00C")
        doc.revisao = "00";

    doc.dataHora = CurrentData_time(); // Função que retorna data/hora atual em string
}

bool isDocumentManager() const
{
    return usuarioAtual && usuarioAtual->getTipo() == TipoUsuario::DOCUMENT_MANAGER;
}

bool usuarioExiste(const std::string& nomeUsuario) const
{
    for(const auto& user : usuarios)
    {
        if(user.getNome() == nomeUsuario)
        {
            return true;
        }
    }
    return false;
}

public:
	
	GEDSystem()
	{
    pastaDocumentos = fs::path(getenv("USERPROFILE")) / "Desktop" / "DocumentosGED";
    arquivoCSV = pastaDocumentos / "documentos.csv";
    arquivoUsuarios = pastaDocumentos / "usuarios.csv";

    // Cria a pasta se não existir
    if (!fs::exists(pastaDocumentos))
    {
        fs::create_directories(pastaDocumentos);
    }

    // Criar usuário admin caso não exista
    carregarUsuarios();

    if (usuarios.empty())
    {
        Usuario admin("admin", "admin123", TipoUsuario::DOCUMENT_MANAGER, "Administrador do sistema");
        usuarios.push_back(admin);
        salvarUsuarios();
    }

    carregarDocumentos();
    usuarioAtual = nullptr;
	}

	~GEDSystem()
	{
    	salvarDocumentos();
   	 salvarUsuarios();
	}

	bool login(const std::string& nome, const std::string& senha)
	{
    for (auto& user : usuarios)
    {
        if (user.getNome() == nome && user.getSenha() == senha)
        {
            usuarioAtual = &user;
            return true;
        }
    }
    	return false;
	}
	
	// Função para logout
    void logout() {
        usuarioAtual = nullptr;
    }

	 // Função para criar documento (apenas Document Manager)
    void criarDocumento(const std::string& nome, const std::string& titulo, const std::string& atribuidoA) {
        if (!isDocumentManager()) {
            std::cout << "Apenas Document Managers podem criar documentos." << std::endl;
            return;
        }

        if (!usuarioExiste(atribuidoA)) {
            std::cout << "Usuário atribuído não encontrado." << std::endl;
            return;
        }

        Documento novoDoc;
        novoDoc.nome = nome;
        novoDoc.titulo = titulo;
        novoDoc.status = "Em análise";
        novoDoc.revisao = "00A";
        novoDoc.dataHoraRevisao = getCurrentDateTime();
        novoDoc.atribuidoA = atribuidoA;

        criarArquivoDocumento(novoDoc);
        documentos.push_back(novoDoc);
        salvarDocumentos();

        std::cout << "Documento criado com sucesso." << std::endl;
    }

	 // Função para exibir o menu principal
void exibirMenuPrincipal(bool isDocumentManager) 
{
    std::cout << "\nSistema de Gerenciamento de Documentos (GED)\n";
    std::cout << "1. Listar documentos\n";
    if (isDocumentManager) {
        std::cout << "2. Criar documento\n";
        std::cout << "3. Excluir documento\n";
    }
    std::cout << "4. Aprovar documento\n";
    std::cout << "5. Reprovar documento com comentário\n";
    std::cout << "6. Visualizar comentários\n";
    std::cout << "7. Atender comentário\n";
    std::cout << "8. Sair\n";
    std::cout << "Escolha uma opção: ";
}

};

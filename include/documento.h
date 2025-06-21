#ifndef DOCUMENTOS_HPP
#define DOCUMENTOS_HPP

#include <iostream>
#include <string>
#include <ctime>

class Documentos
{
private:
	std::string nome_;
	std::string extensao_; 	// (ex: ... ".txt")
	std::string titulo_;
	int versao_;
	std::string status_;	// "rascunho", "revisao", "finalizado"
	std::string criador_;
	std::time_t dataCriacao_;
	std::time_t dataModificacao_;
	std::string caminho_; 	//caminho do arquivo no sistema
public:

	Documentos(const std::string& nome, const std::string& extensao, 
              const std::string& titulo, const std::string& criador,
              const std::string& caminho = "", const std::string& status = "rascunho")
        : nome_(nome), extensao_(extensao), titulo_(titulo), versao_(1),
          status_(status), criador_(criador), caminho_(caminho) {
        dataCriacao_ = std::time(nullptr);
        dataModificacao_ = dataCriacao_;
    }

	 //Getters
	std::string getNomeCompleto() const {return nome_ + extensao_;}
	std::string getTitulo() const {return titulo_;}
	std::string getCriador() const {return criador_;}
	std::string getCaminho() const {return caminho_;}
	std::string getStatus() const {return status_;}
	int getVersao() const {return versao_;}
	std::time_t dataCriacao() const {return dataCriacao_;}
	std::time_t dataModificao() const {return dataModificacao_;}
	
	// Setters
	void setNome(const std::string& n) {nome_ =n;}
	void setTitulo(const std::string& t) {titulo_ = t;}
	void setStatus(const std::string& s) {status_ = s;}
	int setExtensao(const std::string& e) {extensao_ = e;}
	
	void atualizarVersao()
	{
		versao_++;
		atualizarModificacao();
	}

	void atualizarStatus(const std::string& NovoStatus)
	{
		if(NovoStatus == "rascunho" || NovoStatus == "revisao" || NovoStatus == "finalizado")
		{
			status_ = NovoStatus_;
			atualizarModificacao();
		}
		else
		{
			throw std::invalid_argument("Status inválido");
		}
	}

	bool salvarComoArquivo(const std::string& NovoCaminho = "")
	{
		if(!caminho_.empty())
		{
			caminho_ = NovoCaminho;
		}

		atualizarModificacao();

		return true;
	}

private:
	void atualizarModificacao()
	{
		dataModificacao_ = std::time(nullptr);
	}
};

#endif

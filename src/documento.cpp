#include "../include/documento.h"
#include "../include/util.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <filesystem>

Documento::Documento(const std::string& nome) : nome(nome) {
    carregarDados();
}

void Documento::carregarDados() {
    std::ifstream csv(Util::obterCaminhoDesktop() + "/GED_Documentos/documentos.csv");
    std::string linha;
    while (std::getline(csv, linha)) {
        std::stringstream ss(linha);
        std::getline(ss, this->nome, ',');
        std::getline(ss, this->titulo, ',');
        std::getline(ss, this->status, ',');
        std::getline(ss, this->revisao, ',');
        std::getline(ss, this->comentario, ',');
        std::getline(ss, this->horario, ',');
        std::getline(ss, this->atribuido);
        if (this->nome == nome) break;
    }
}

void Documento::salvarDados() {
    // Este método atualiza a linha correspondente no CSV
    // (pode ser feito lendo todo arquivo e sobrescrevendo com as mudanças)
}

void Documento::aprovar() {
    if (revisao == "00C") {
        status = "Aprovado";
        revisao = "00";
    }
    atualizarHorario();
    salvarDados();
}

void Documento::reprovar(const std::string& comentario) {
    status = "Reprovado";
    this->comentario = comentario;
    atualizarHorario();
    salvarDados();
}

void Documento::atenderComentario() {
    if (status == "Reprovado") {
        status = "Atendido";
        revisao = proximaRevisao(revisao);
    }
    atualizarHorario();
    salvarDados();
}

std::string Documento::proximaRevisao(const std::string& atual) {
    if (atual == "00A") return "00B";
    if (atual == "00B") return "00C";
    if (atual == "00C") return "00";
    return atual;
}

void Documento::atualizarHorario() {
    horario = Util::obterDataHoraAtual();
}
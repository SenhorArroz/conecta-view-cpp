#include "../../include/models/ProvaGincana.hpp"
#include "../../include/exceptions/GincanaExceptions.hpp"
#include <iostream>
#include <fstream>
#include <string>

ProvaGincana::ProvaGincana(std::string id, std::string titulo, std::string equipeId, std::string descricao)
    : AtividadePontuada(id, titulo, equipeId), descricao(descricao) {
    this->pontosObtidos = 0;
    this->avaliador = "Aguardando avaliacao";
}

std::string ProvaGincana::getDescricao() const { return descricao; }

int ProvaGincana::getPontosObtidos() const { return pontosObtidos; }

std::string ProvaGincana::getAvaliador() const { return avaliador; }

void ProvaGincana::avaliarApresentacao(int nota, const std::string& nomeAvaliador) {
    if (nota < 0) {
        throw PontuacaoInvalidaException();
    }
    this->pontosObtidos = nota;
    this->avaliador = nomeAvaliador;
}

int ProvaGincana::calcularPontos() const {
    return pontosObtidos;
}

void ProvaGincana::exibirResumo() const {
    std::cout << "Prova: " << getTitulo() << "\n"
              << "Descricao: " << descricao << "\n"
              << "Nota: " << pontosObtidos << " (Avaliador: " << avaliador << ")\n";
}

void ProvaGincana::salvar(std::ofstream& arquivoSaida) const {
    arquivoSaida << "---PROVA---\n";
    arquivoSaida << getId() << "\n";
    arquivoSaida << getTitulo() << "\n";
    arquivoSaida << getEquipeId() << "\n";
    arquivoSaida << pontosObtidos << "\n";
}

void ProvaGincana::carregar(std::ifstream& arquivoEntrada) {
    (void)arquivoEntrada;
}
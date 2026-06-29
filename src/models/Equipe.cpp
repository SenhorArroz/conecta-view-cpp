#include "../../include/models/Equipe.hpp"
#include "../../include/models/abstratos/AtividadePontuada.hpp"
#include "../../include/exceptions/GincanaExceptions.hpp"
#include <fstream>
#include <string>

Equipe::Equipe(std::string id, std::string nome, Usuario* criador)
    : id(id), nome(nome), criador(criador) {
    if (id.empty() || nome.empty()) {
        throw EntradaInvalidaException("ID e nome da equipe nao podem ser vazios.");
    }
}

Equipe::~Equipe() {
    for (AtividadePontuada* atv : atividades) {
        delete atv;
    }
    atividades.clear();
}

std::string Equipe::getId() const { return id; }

std::string Equipe::getNome() const { return nome; }

Usuario* Equipe::getCriador() const { return criador; }

void Equipe::adicionarAtividade(AtividadePontuada* atividade) {
    if (atividade == nullptr) {
        throw EntradaInvalidaException("Nao eh possivel adicionar uma atividade nula.");
    }
    atividades.push_back(atividade);
}

const std::vector<AtividadePontuada*>& Equipe::getAtividades() const {
    return atividades;
}

int Equipe::calcularPontuacaoTotal() const {
    int total = 0;
    for (AtividadePontuada* atv : atividades) {
        if (atv != nullptr) {
            total += atv->calcularPontos(); 
        }
    }
    return total;
}

void Equipe::salvar(std::ofstream& arquivoSaida) const {
    arquivoSaida << "---EQUIPE---\n";
    arquivoSaida << id << "\n";
    arquivoSaida << nome << "\n";
}

void Equipe::carregar(std::ifstream& arquivoEntrada) {
    (void)arquivoEntrada;
}

std::ostream& operator<<(std::ostream& os, const Equipe& equipe) {
    os << "[" << equipe.id << "] " << equipe.nome;
    return os;
}
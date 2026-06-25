#include "../../include/models/Equipe.hpp"
#include "../../include/models/abstratos/AtividadePontuada.hpp"
#include <fstream>
#include <string>

Equipe::Equipe(std::string id, std::string nome, Usuario* criador)
    : id(id), nome(nome), criador(criador) {}

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
    if (atividade != nullptr) {
        atividades.push_back(atividade);
    }
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
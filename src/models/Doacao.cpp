#include "../../include/models/Doacao.hpp"
#include "../../include/models/ItemSendoDoado.hpp"
#include "../../include/exceptions/GincanaExceptions.hpp"
#include <iostream>
#include <fstream>
#include <string>

Doacao::Doacao(std::string id, std::string titulo, std::string equipeId, std::string nomeDoador, std::string descricao)
    : AtividadePontuada(id, titulo, equipeId), nomeDoador(nomeDoador), descricao(descricao) {
    if (nomeDoador.empty()) {
        throw EntradaInvalidaException("O nome do doador nao pode ser vazio.");
    }
    this->status = StatusDoacao::PENDENTE_AVALIACAO; 
}

Doacao::~Doacao() {
    for (ItemSendoDoado* item : itensDoados) {
        delete item;
    }
    itensDoados.clear();
}

void Doacao::aprovar() {
    if (status != StatusDoacao::PENDENTE_AVALIACAO) {
        throw TransicaoEstadoInvalidaException(); 
    }
    status = StatusDoacao::APROVADA;
}

void Doacao::rejeitar() {
    if (status != StatusDoacao::PENDENTE_AVALIACAO) {
        throw TransicaoEstadoInvalidaException();
    }
    status = StatusDoacao::REJEITADA;
}

StatusDoacao Doacao::getStatus() const { return status; }

void Doacao::adicionarItem(ItemSendoDoado* item) {
    if (item == nullptr) {
        throw EntradaInvalidaException("Nao eh possivel adicionar um item nulo a doacao.");
    }
    if (status == StatusDoacao::REJEITADA) {
        throw TransicaoEstadoInvalidaException();
    }
    itensDoados.push_back(item);
}

int Doacao::calcularPontos() const {
    if (status != StatusDoacao::APROVADA) {
        return 0;
    }

    int subtotal = 0;
    for (ItemSendoDoado* item : itensDoados) {
        if (item != nullptr) {
            subtotal += item->calcularSubtotalPontos();
        }
    }
    return subtotal;
}

void Doacao::exibirResumo() const {
    std::cout << "Doacao: " << getTitulo() << " | Doador: " << nomeDoador << "\n";
}

void Doacao::salvar(std::ofstream& arquivoSaida) const {
    arquivoSaida << "---DOACAO---\n";
    arquivoSaida << getId() << "\n" << getTitulo() << "\n" << getEquipeId() << "\n";
}

void Doacao::carregar(std::ifstream& arquivoEntrada) { 
    (void)arquivoEntrada;
}

std::ostream& operator<<(std::ostream& os, const Doacao& doacao) {
    os << "Doacao [" << doacao.getId() << "] - " << doacao.getTitulo();
    return os;
}

std::istream& operator>>(std::istream& is, Doacao& doacao) {
    (void)doacao;
    return is;
}
#include "../../include/models/Item.hpp"
#include "../../include/models/abstratos/Usuario.hpp"
#include "../../include/exceptions/GincanaExceptions.hpp"
#include <fstream>
#include <string>

Item::Item(std::string id, std::string nome, std::string descricao, int pontosBase, Usuario* criador)
    : id(id), nome(nome), descricao(descricao), pontosBase(pontosBase), criador(criador) {
    if (id.empty() || nome.empty()) {
        throw EntradaInvalidaException("ID e nome do item nao podem ser vazios.");
    }
    if (pontosBase < 0) {
        throw PontuacaoInvalidaException();
    }
}

std::string Item::getId() const { return id; }

std::string Item::getNome() const { return nome; }

std::string Item::getDescricao() const { return descricao; }

int Item::getPontosBase() const { return pontosBase; }

Usuario* Item::getCriador() const { return criador; }

void Item::salvar(std::ofstream& arquivoSaida) const {
    arquivoSaida << "---ITEM---\n";
    arquivoSaida << id << "\n";
    arquivoSaida << nome << "\n";
    arquivoSaida << pontosBase << "\n";
}

void Item::carregar(std::ifstream& arquivoEntrada) {
    (void)arquivoEntrada;
}
#include "../../include/models/ItemSendoDoado.hpp"
#include "../../include/models/Item.hpp"
#include "../../include/exceptions/GincanaExceptions.hpp"
#include <string>

ItemSendoDoado::ItemSendoDoado(std::string id, Item* itemBase, int quantidade)
    : id(id), itemBase(itemBase), quantidade(quantidade) {
    if (id.empty()) {
        throw EntradaInvalidaException("ID do item doado nao pode ser vazio.");
    }
    if (itemBase == nullptr) {
        throw EntradaInvalidaException("Item base nao pode ser nulo.");
    }
    if (quantidade <= 0) {
        throw EntradaInvalidaException("A quantidade doada deve ser maior que zero.");
    }
}

std::string ItemSendoDoado::getId() const { return id; }

int ItemSendoDoado::getQuantidade() const { return quantidade; }

Item* ItemSendoDoado::getItemBase() const { return itemBase; }

int ItemSendoDoado::calcularSubtotalPontos() const {
    if (itemBase != nullptr) {
        return quantidade * itemBase->getPontosBase();
    }
    return 0;
}
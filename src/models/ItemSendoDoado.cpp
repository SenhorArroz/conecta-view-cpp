#include "../../include/models/ItemSendoDoado.hpp"
#include "../../include/models/Item.hpp"
#include <string>

ItemSendoDoado::ItemSendoDoado(std::string id, Item* itemBase, int quantidade)
    : id(id), itemBase(itemBase), quantidade(quantidade) {}

std::string ItemSendoDoado::getId() const { return id; }

int ItemSendoDoado::getQuantidade() const { return quantidade; }

Item* ItemSendoDoado::getItemBase() const { return itemBase; }

int ItemSendoDoado::calcularSubtotalPontos() const {
    if (itemBase != nullptr) {
        return quantidade * itemBase->getPontosBase();
    }
    return 0;
}
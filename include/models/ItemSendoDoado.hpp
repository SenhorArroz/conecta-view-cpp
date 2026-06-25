#pragma once

#include <string>

class Item;

class ItemSendoDoado {
private:
    std::string id;
    
    int quantidade;
    
    Item* itemBase; 

public:
    ItemSendoDoado(std::string id, Item* itemBase, int quantidade);

    ~ItemSendoDoado() = default;

    std::string getId() const;
    int getQuantidade() const;
    Item* getItemBase() const;

    int calcularSubtotalPontos() const;
};
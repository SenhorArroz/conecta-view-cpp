#pragma once

#include <fstream> 

class IPersistente {
public:
    virtual ~IPersistente() = default;

    virtual void salvar(std::ofstream& arquivoSaida) const = 0;

    virtual void carregar(std::ifstream& arquivoEntrada) = 0;
};
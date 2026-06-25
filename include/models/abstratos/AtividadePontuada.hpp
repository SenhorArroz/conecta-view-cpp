#pragma once

#include <string>

class AtividadePontuada {
protected:
    std::string id;
    std::string titulo;   
    std::string equipeId; 

public:
    AtividadePontuada(std::string id, std::string titulo, std::string equipeId);

    virtual ~AtividadePontuada();

    std::string getId() const;
    std::string getTitulo() const;
    std::string getEquipeId() const;

    virtual int calcularPontos() const = 0;
    
    virtual void exibirResumo() const = 0;
};
#include "../../include/models/abstratos/AtividadePontuada.hpp"
#include "../../include/exceptions/GincanaExceptions.hpp"

AtividadePontuada::AtividadePontuada(std::string id, std::string titulo, std::string equipeId)
    : id(id), titulo(titulo), equipeId(equipeId) {
    if (id.empty() || titulo.empty() || equipeId.empty()) {
        throw EntradaInvalidaException("ID, titulo e ID da equipe não podem ser vazios para uma atividade pontuada.");
    }
}

AtividadePontuada::~AtividadePontuada() {}

std::string AtividadePontuada::getId() const { return id; }
std::string AtividadePontuada::getTitulo() const { return titulo; }
std::string AtividadePontuada::getEquipeId() const { return equipeId; }
#include "../../include/models/abstratos/AtividadePontuada.hpp"

AtividadePontuada::AtividadePontuada(std::string id, std::string titulo, std::string equipeId)
    : id(id), titulo(titulo), equipeId(equipeId) {}

AtividadePontuada::~AtividadePontuada() {}

std::string AtividadePontuada::getId() const { return id; }
std::string AtividadePontuada::getTitulo() const { return titulo; }
std::string AtividadePontuada::getEquipeId() const { return equipeId; }
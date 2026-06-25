#include "../../include/models/abstratos/Usuario.hpp"

Usuario::Usuario(std::string id, std::string nome, std::string email, std::string senha)
    : id(id), nome(nome), email(email), senha(senha) {}

Usuario::~Usuario() {}

std::string Usuario::getId() const { return id; }
std::string Usuario::getNome() const { return nome; }
std::string Usuario::getEmail() const { return email; }

bool Usuario::verificarSenha(const std::string& senhaDigitada) const {
    return this->senha == senhaDigitada;
}
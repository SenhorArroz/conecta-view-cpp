#include "../../include/models/abstratos/Usuario.hpp"
#include "../../include/exceptions/GincanaExceptions.hpp"

Usuario::Usuario(std::string id, std::string nome, std::string email, std::string senha)
    : id(id), nome(nome), email(email), senha(senha) {
    if (id.empty() || nome.empty() || email.empty() || senha.empty()) {
        throw EntradaInvalidaException("Nenhum dos campos do usuario (id, nome, email, senha) pode ser vazio.");
    }
}

Usuario::~Usuario() {}

std::string Usuario::getId() const { return id; }
std::string Usuario::getNome() const { return nome; }
std::string Usuario::getEmail() const { return email; }

bool Usuario::verificarSenha(const std::string& senhaDigitada) const {
    return this->senha == senhaDigitada;
}
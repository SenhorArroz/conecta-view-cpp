#pragma once

#include <string>

class Usuario {
private:
    std::string id;
    std::string nome;
    std::string email;
    std::string senha;

public:
    Usuario(std::string id, std::string nome, std::string email, std::string senha);

    virtual ~Usuario();

    std::string getId() const;
    std::string getNome() const;
    std::string getEmail() const;
    
    bool verificarSenha(const std::string& senhaDigitada) const;

    virtual void exibirMenu() const = 0;
    
    virtual std::string getTipo() const = 0;
};
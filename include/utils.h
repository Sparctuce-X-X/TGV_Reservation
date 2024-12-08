#ifndef UTILS_H
#define UTILS_H

#include <string>

// Déclaration des fonctions utilitaires
std::string validerEntreeNonVide(const std::string& message);
bool validerDate(const std::string& date);
std::string demanderDateValide(const std::string& message);
void verifierFichier(const std::string& cheminFichier);

#endif

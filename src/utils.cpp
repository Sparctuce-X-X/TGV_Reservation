#include "utils.h"
#include <iostream>
#include <regex>
#include <fstream> // Nécessaire pour std::ifstream et std::ofstream

// Valider une entrée utilisateur non vide
std::string validerEntreeNonVide(const std::string& message) {
    std::string entree;
    do {
        std::cout << message;
        std::getline(std::cin, entree);
        if (entree.empty()) {
            std::cout << "Erreur : Ce champ ne peut pas être vide. Veuillez réessayer.\n";
        }
    } while (entree.empty());
    return entree;
}

// Valider le format de la date (YYYY-MM-DD)
bool validerDate(const std::string& date) {
    std::regex formatDate("\\d{4}-\\d{2}-\\d{2}");
    return std::regex_match(date, formatDate);
}

// Demander une date valide au format YYYY-MM-DD
std::string demanderDateValide(const std::string& message) {
    std::string date;
    do {
        std::cout << message;
        std::cin >> date;
        if (!validerDate(date)) {
            std::cout << "Erreur : Format de date invalide. Utilisez le format YYYY-MM-DD.\n";
        }
    } while (!validerDate(date));
    return date;
}

// Vérifier l'existence d'un fichier et le créer s'il est manquant
void verifierFichier(const std::string& cheminFichier) {
    std::ifstream fichier(cheminFichier);
    if (!fichier) {
        std::cout << "Fichier manquant : " << cheminFichier << ". Création d'un fichier vide.\n";
        std::ofstream nouveauFichier(cheminFichier);
        if (!nouveauFichier) {
            std::cerr << "Erreur : Impossible de créer le fichier " << cheminFichier << ".\n";
        }
    }
}

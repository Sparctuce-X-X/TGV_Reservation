#include "../include/Billet.h"
#include <iostream>
#include <fstream>
#include <sstream>

// Constructeur
Billet::Billet(int numero, const std::string& classe, float prixBillet, int train, const std::string& date,
               const std::string& depart, const std::string& arrivee)
    : numeroBillet(numero), typeClasse(classe), prix(prixBillet), numeroTrain(train),
      dateVoyage(date), villeDepart(depart), villeArrivee(arrivee) {}

// Afficher les détails du billet
void Billet::afficherDetailsBillet() const {
    std::cout << "Billet #" << numeroBillet << ": " << typeClasse << " Classe"
              << "\nPrix: " << prix << " EUR"
              << "\nTrain: " << numeroTrain
              << "\nDate: " << dateVoyage
              << "\nDépart: " << villeDepart << " -> Arrivée: " << villeArrivee
              << "\n";
}

// Getters
int Billet::getNumeroBillet() const {
    return numeroBillet;
}

const std::string& Billet::getTypeClasse() const {
    return typeClasse;
}

float Billet::getPrix() const {
    return prix;
}

int Billet::getNumeroTrain() const {
    return numeroTrain;
}

const std::string& Billet::getDateVoyage() const {
    return dateVoyage;
}

const std::string& Billet::getVilleDepart() const {
    return villeDepart;
}

const std::string& Billet::getVilleArrivee() const {
    return villeArrivee;
}

// Charger les billets depuis un fichier
std::vector<Billet> Billet::chargerBillets(const std::string& fichier) {
    std::vector<Billet> billets;
    std::ifstream file(fichier);

    if (!file) {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier " << fichier << "\n";
        return billets;
    }

    std::string ligne;
    while (std::getline(file, ligne)) {
        std::stringstream ss(ligne);
        std::string numeroBillet, typeClasse, prix, numeroTrain, dateVoyage, villeDepart, villeArrivee;

        std::getline(ss, numeroBillet, '|');
        std::getline(ss, typeClasse, '|');
        std::getline(ss, prix, '|');
        std::getline(ss, numeroTrain, '|');
        std::getline(ss, dateVoyage, '|');
        std::getline(ss, villeDepart, '|');
        std::getline(ss, villeArrivee, '|');

        billets.emplace_back(std::stoi(numeroBillet), typeClasse, std::stof(prix), std::stoi(numeroTrain),
                             dateVoyage, villeDepart, villeArrivee);
    }

    file.close();
    return billets;
}

// Sauvegarder les billets dans un fichier
void Billet::sauvegarderBillets(const std::vector<Billet>& billets, const std::string& fichier) {
    std::ofstream file(fichier);

    if (!file) {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier " << fichier << " pour l'écriture.\n";
        return;
    }

    for (const auto& billet : billets) {
        file << billet.getNumeroBillet() << "|"
             << billet.getTypeClasse() << "|"
             << billet.getPrix() << "|"
             << billet.getNumeroTrain() << "|"
             << billet.getDateVoyage() << "|"
             << billet.getVilleDepart() << "|"
             << billet.getVilleArrivee() << "\n";
    }

    file.close();
}

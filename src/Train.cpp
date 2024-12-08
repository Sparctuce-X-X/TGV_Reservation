#include "../include/Train.h"
#include <fstream>
#include <sstream>
#include <iostream>

// Constructeur
Train::Train(int numero, const std::string& depart, const std::string& arrivee, const std::string& horaireDep, const std::string& horaireArr, int capaciteTotal)
    : numeroTrain(numero), villeDepart(depart), villeArrivee(arrivee), horaireDepart(horaireDep), horaireArrivee(horaireArr), capacite(capaciteTotal), placesLibres(capaciteTotal) {}

// Vérifie si des places sont disponibles
bool Train::verifierDisponibilite() const {
    return placesLibres > 0;
}

// Réserve une place
bool Train::reserverPlace() {
    if (placesLibres > 0) {
        placesLibres--;
        return true;
    }
    return false;
}

// Annule une réservation
bool Train::annulerReservation() {
    if (placesLibres < capacite) {
        placesLibres++;
        return true;
    }
    return false;
}

// Affiche les informations du train
void Train::afficherInfosTrain() const {
    std::cout << "Train #" << numeroTrain << ": " << villeDepart << " -> " << villeArrivee
              << "\nDépart: " << horaireDepart << " | Arrivée: " << horaireArrivee
              << "\nPlaces disponibles: " << placesLibres << "/" << capacite << "\n";
}

// Getters
int Train::getNumeroTrain() const {
    return numeroTrain;
}

const std::string& Train::getVilleDepart() const {
    return villeDepart;
}

const std::string& Train::getVilleArrivee() const {
    return villeArrivee;
}

const std::string& Train::getHoraireDepart() const {
    return horaireDepart;
}

const std::string& Train::getHoraireArrivee() const {
    return horaireArrivee;
}

int Train::getPlacesLibres() const {
    return placesLibres;
}

int Train::getCapacite() const {
    return capacite;
}

// Charger les trains depuis un fichier
std::vector<Train> Train::chargerTrains(const std::string& fichier) {
    std::vector<Train> trains;
    std::ifstream file(fichier);

    try {
        if (!file) {
            throw std::ios_base::failure("Erreur : Impossible d'ouvrir le fichier " + fichier);
        }

        std::string ligne;
        while (std::getline(file, ligne)) {
            std::stringstream ss(ligne);
            std::string numeroTrain, villeDepart, villeArrivee, horaireDepart, horaireArrivee, capacite;

            std::getline(ss, numeroTrain, '|');
            std::getline(ss, villeDepart, '|');
            std::getline(ss, villeArrivee, '|');
            std::getline(ss, horaireDepart, '|');
            std::getline(ss, horaireArrivee, '|');
            std::getline(ss, capacite, '|');

            trains.emplace_back(std::stoi(numeroTrain), villeDepart, villeArrivee, horaireDepart, horaireArrivee,
                                std::stoi(capacite));
        }

    } catch (const std::exception& e) {
        std::cerr << e.what() << "\n";
    }

    return trains;
}


// Sauvegarder les trains dans un fichier
void Train::sauvegarderTrains(const std::vector<Train>& trains, const std::string& fichier) {
    std::ofstream file(fichier);

    if (!file) {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier " << fichier << " pour l'écriture.\n";
        return;
    }

    for (const auto& train : trains) {
        file << train.getNumeroTrain() << "|"
             << train.getVilleDepart() << "|"
             << train.getVilleArrivee() << "|"
             << train.getHoraireDepart() << "|"
             << train.getHoraireArrivee() << "|"
             << train.getCapacite() << "|"
             << train.getPlacesLibres() << "\n";
    }

    file.close();
}

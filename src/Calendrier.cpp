#include "Calendrier.h"
#include <iostream>

// Ajouter un train à une date donnée
void Calendrier::ajouterHoraire(const std::string& date, const Train& train) {
    horaireTrain[date].push_back(train);
}

// Afficher tous les trains pour toutes les dates
void Calendrier::afficherCalendrier() const {
    if (horaireTrain.empty()) {
        std::cout << "Aucun horaire disponible.\n";
        return;
    }

    for (const auto& [date, trains] : horaireTrain) {
        std::cout << "Date : " << date << "\n";
        for (const auto& train : trains) {
            train.afficherInfosTrain();
            std::cout << "-------------------------------\n";
        }
    }
}

// Rechercher des trains pour une date et des villes spécifiques
std::vector<Train> Calendrier::rechercherTrainsParDate(const std::string& date, const std::string& villeDepart, const std::string& villeArrivee) const {
    std::vector<Train> trainsTrouves;

    auto it = horaireTrain.find(date);
    if (it == horaireTrain.end()) {
        std::cout << "Aucun train disponible pour la date : " << date << "\n";
        return trainsTrouves;
    }

    for (const auto& train : it->second) {
        if ((villeDepart.empty() || train.getVilleDepart() == villeDepart) &&
            (villeArrivee.empty() || train.getVilleArrivee() == villeArrivee)) {
            trainsTrouves.push_back(train);
        }
    }

    return trainsTrouves;
}

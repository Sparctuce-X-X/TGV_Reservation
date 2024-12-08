#ifndef CALENDRIER_H
#define CALENDRIER_H

#include <string>
#include <vector>
#include <map>
#include "Train.h"

class Calendrier {
private:
    // Map où chaque clé est une date, et la valeur est une liste des trains programmés ce jour-là
    std::map<std::string, std::vector<Train>> horaireTrain;

public:
    // Ajouter un train à une date donnée
    void ajouterHoraire(const std::string& date, const Train& train);

    // Afficher tous les trains pour toutes les dates
    void afficherCalendrier() const;

    // Rechercher des trains pour une date et des villes spécifiques
    // Retourne une liste de trains correspondant aux critères
    std::vector<Train> rechercherTrainsParDate(const std::string& date, const std::string& villeDepart = "", const std::string& villeArrivee = "") const;
};

#endif

#include "SelectionPolicy.h"
#include <algorithm>

NaiveSelection:: NaiveSelection():
    lastSelectedIndex(-1) {} //i changed the form :{}

const FacilityType& NaiveSelection:: selectFacility(const vector<FacilityType>& facilitiesOptions) {
    lastSelectedIndex = (lastSelectedIndex+1)%facilitiesOptions.size();  //mabye we should add a check if the list is empty?
        return facilitiesOptions[lastSelectedIndex];
    }

const string NaiveSelection:: toString() const {
        return "selectionPolicy: nve";
    }

NaiveSelection* NaiveSelection:: clone() const {
        NaiveSelection *copy = new NaiveSelection();
        (*copy).lastSelectedIndex = this->lastSelectedIndex;
        return copy;
    }

BalancedSelection:: BalancedSelection(int LifeQualityScore, int EconomyScore, int EnvironmentScore):
    LifeQualityScore(LifeQualityScore), EconomyScore(EconomyScore), EnvironmentScore(EnvironmentScore) {}

const FacilityType& BalancedSelection:: selectFacility(const vector<FacilityType>& facilitiesOptions) {
        int distance = __INT_MAX__;
        int minIndex = 0;
        for(std::size_t i = 0 ; i < facilitiesOptions.size() ; i++){
            int life = LifeQualityScore+ facilitiesOptions[i].getLifeQualityScore();
            int eco = EconomyScore+ facilitiesOptions[i].getEconomyScore();
            int env = EnvironmentScore+ facilitiesOptions[i].getEnvironmentScore();
            int deff = std::max({life, eco, env})- std::min({life, eco, env});
            if ( deff < distance) {
                distance = deff;
                minIndex = i;
            }
        }
        return facilitiesOptions[minIndex];
    }


const string BalancedSelection:: toString() const {
        return "selectionPolicy: bal";
    }


BalancedSelection* BalancedSelection:: clone() const  {
        BalancedSelection *copy = new BalancedSelection(this->LifeQualityScore, this->EconomyScore ,this->EnvironmentScore);
        return copy;
    }

EconomySelection:: EconomySelection(): 
        lastSelectedIndex(-1) {}

const FacilityType& EconomySelection:: selectFacility(const vector<FacilityType>& facilitiesOptions) {
        lastSelectedIndex ++;
        std::size_t counter = 0; //to prevent endless loop
        while (facilitiesOptions[lastSelectedIndex].getCategory() !=  FacilityCategory::ECONOMY && counter>=facilitiesOptions.size()){
            lastSelectedIndex = (lastSelectedIndex+1) %facilitiesOptions.size();
            counter++;
        }
        return facilitiesOptions[lastSelectedIndex];
    }
const string EconomySelection:: toString() const {
        return "selectionPolicy: eco";
    }
        
EconomySelection* EconomySelection:: clone() const {
        EconomySelection *copy = new EconomySelection();
        (*copy).lastSelectedIndex = this->lastSelectedIndex;
        return copy;
    }



SustainabilitySelection:: SustainabilitySelection():
        lastSelectedIndex(-1) {}

const FacilityType& SustainabilitySelection:: selectFacility(const vector<FacilityType>& facilitiesOptions) {
        lastSelectedIndex ++;
        std::size_t counter = 0; //to prevent endless loop
        while (facilitiesOptions[lastSelectedIndex].getCategory() !=  FacilityCategory::ENVIRONMENT && counter>=facilitiesOptions.size()){
            lastSelectedIndex = (lastSelectedIndex+1) %facilitiesOptions.size();
            counter++;
        }
        return facilitiesOptions[lastSelectedIndex];
    }

const string SustainabilitySelection:: toString() const {
        return "selectionPolicy: env";
    }
        
SustainabilitySelection* SustainabilitySelection:: clone() const {
        SustainabilitySelection *copy = new SustainabilitySelection();
        (*copy).lastSelectedIndex = this->lastSelectedIndex;
        return copy;
    }
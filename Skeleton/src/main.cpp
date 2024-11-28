//#include "Simulation.h"
#include "Settlement.h"
#include "SelectionPolicy.h"
#include <iostream>

using namespace std;

//Simulation* backup = nullptr;

int main(int argc, char** argv){
   cout << "Hi Hagar"<< endl;
    Settlement *stl = new Settlement("kFarSPL", SettlementType::VILLAGE);
    cout << stl->toString() << endl;
    Facility *facil = new Facility("kindergarden", "spl2", FacilityCategory::ECONOMY, 2, 2, 1, 1);
    cout << facil->toString() << endl;
    FacilityStatus fs(facil->step());
    if (fs == FacilityStatus::OPERATIONAL)
    {
        cout << "OPERATIONAL time left=" + std::to_string(facil->getTimeLeft()) << endl;
    }
    else
    {
        cout << "UNDER_CONSTRUCTION time left=" + std::to_string(facil->getTimeLeft()) << endl;
    }
    // Selection Policy Test
    NaiveSelection *ns = new NaiveSelection();
    FacilityType ft1("Hospital", FacilityCategory::ENVIRONMENT, 4, 2, 1, 1);
    FacilityType ft2("Bank", FacilityCategory::ECONOMY, 3, 2, 1, 1);
    FacilityType ft3("University", FacilityCategory::ECONOMY, 5, 2, 1, 1);
    FacilityType ft4("Beauty-Salon", FacilityCategory::LIFE_QUALITY, 2, 2, 1, 1);

    const vector<FacilityType> facilitiesOptions = {ft1, ft2, ft3, ft4};
    const FacilityType &chosenNaive = ns->selectFacility(facilitiesOptions);
    cout << "Naive Test:" << endl;
    cout << chosenNaive.getName() << endl;
    const FacilityType &chosenNaive1 = ns->selectFacility(facilitiesOptions);
    cout << chosenNaive1.getName() << endl;

    EconomySelection *es = new EconomySelection();
    const FacilityType &chosenEconomy = es->selectFacility(facilitiesOptions);
    cout << "Economy Test:" << endl;
    cout << chosenEconomy.getName() << endl;
    const FacilityType &chosenEconomy1 = es->selectFacility(facilitiesOptions);
    cout << chosenEconomy1.getName() << endl;
    const FacilityType &chosenEconomy2 = es->selectFacility(facilitiesOptions);
    cout << chosenEconomy2.getName() << endl;

    SustainabilitySelection *ss = new SustainabilitySelection();
    const FacilityType &chosenSustainability = ss->selectFacility(facilitiesOptions);
    cout << "Sustainability Test:" << endl;
    cout << chosenSustainability.getName() << endl;
    const FacilityType &chosenSustainability1 = ss->selectFacility(facilitiesOptions);
    cout << chosenSustainability1.getName() << endl;

    BalancedSelection *bs = new BalancedSelection(1, 2, 3);
    cout << "Balance Test:" << endl;
    const FacilityType &chosenBalanced = bs->selectFacility(facilitiesOptions);
    cout << chosenBalanced.getName() << endl;
    /*if(argc!=2){
        cout << "usage: simulation <config_path>" << endl;
        return 0;
    }
    string configurationFile = argv[1];
    Simulation simulation(configurationFile);
    simulation.start();
    if(backup!=nullptr){
    	delete backup;
    	backup = nullptr;
    }*/
    return 0;
}
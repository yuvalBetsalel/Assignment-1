#include "Plan.h"
    
    Plan:: Plan(const int planId, const Settlement &settlement, SelectionPolicy *selectionPolicy, const vector<FacilityType> &facilityOptions):
            plan_id(planId), settlement(settlement), selectionPolicy(selectionPolicy),facilities(std::vector<Facility*>()), 
            underConstruction(std::vector<Facility*>()), facilityOptions(facilityOptions), 
            status(PlanStatus::AVALIABLE), life_quality_score(0), economy_score(0), environment_score(0) {} //check if settelment is correct
    
    //copy constructor
    Plan:: Plan (const Plan& other):
        plan_id(other.plan_id), settlement(other.settlement), 
        selectionPolicy(other.selectionPolicy->clone()), 
        facilities(other.facilities), underConstruction(other.underConstruction), facilityOptions(other.facilityOptions), status(other.status), 
        life_quality_score(other.life_quality_score), economy_score(other.economy_score), environment_score(other.environment_score) 
        {}

    //copy assignment operator
    void Plan:: operator=(const Plan& other){
        if (&other != this) {
            plan_id = other.plan_id;
            settlement = other.settlement;
            delete selectionPolicy;
            selectionPolicy = other.selectionPolicy->clone();
            for (std::size_t i=0; i<facilities.size(); i++){
                delete facilities.at(i); }
            for (std::size_t i=0; i<other.facilities.size(); i++) {
                other.facilities.push_back(new Facility(other.facilities.at(i))); //check if defult copy constuctor is ok
            }
            for (std::size_t i=0; i<underConstruction.size(); i++){
                delete underConstruction.at(i); }
            for (std::size_t i=0; i<other.underConstruction.size(); i++) {
                other.underConstruction.push_back(new Facility(other.underConstruction.at(i))); //check if defult copy constuctor is ok
            }
            facilityOptions = other.facilityOptions;
            status = other.status;
            life_quality_score = other.life_quality_score;
            economy_score = other.economy_score;
            environment_score = other.environment_score;
        }
    }

    const int Plan:: getlifeQualityScore() const{
        return life_quality_score;
    }
    const int Plan:: getEconomyScore() const{
        return economy_score;
    }
    const int Plan:: getEnvironmentScore() const{
        return environment_score;
    }
    //void Plan:: setSelectionPolicy(SelectionPolicy *selectionPolicy){
        //   delete selectionPolicy;                      //should we use this? need to delete?
    //    this->selectionPolicy = selectionPolicy; }
    
    bool Plan:: checkIfAvailable(const Settlement &settlement, std::size_t size) { //check if function works
        if (settlement.getType() == SettlementType::VILLAGE)
            return (size<1);
        if (settlement.getType() == SettlementType::CITY)
            return (size<2);
        else //settlement.getType() == SettlementType::METROPOLIS
            return (size<3);
    }
    
    void Plan:: step(){
        while (status == PlanStatus::AVALIABLE){
            const FacilityType& nextFacilityType = selectionPolicy->selectFacility(facilityOptions);
            Facility* nextFacility = new Facility(nextFacilityType, settlement.getName());
            addFacility(nextFacility);
            if (!checkIfAvailable(settlement, underConstruction.size()))  
                status = PlanStatus::BUSY;
        }
        for (size_t i = 0; i < underConstruction.size() ; i++) {
            if ((*underConstruction[i]).step() == FacilityStatus::OPERATIONAL){
                life_quality_score += (*underConstruction[i]).getLifeQualityScore;
                economy_score += (*underConstruction[i]).getEconomyScore;
                environment_score += (*underConstruction[i]).getEnvironmentScore;
                addFacility(underConstruction.at(i));
                underConstruction.erase(underConstruction.at(i));}          //begin()+i
        }
        if (checkIfAvailable(settlement,underConstruction.size()))
            status = PlanStatus::AVALIABLE;
    }
    
    
    void Plan:: printStatus(){
        if (status == PlanStatus::AVALIABLE)
            cout << "planStatus: AVALIABLE" << ;
        else
            cout << "planStatus: BUSY" << ; 
    }
    
    const vector<Facility*>& Plan:: getFacilities() const{
        rerurn &facilities;
    }
    
    void Plan:: addFacility(Facility* facility){ 
        if (facility->getStatus() == FacilityStatus::UNDER_CONSTRUCTIONS)
            underConstruction.push_back(facility);
        else //status is operational
            facilities.push_back(facility);
    }
    
    const string Plan:: toString() const{
        return "planID: " + plan_id + "settlementName " + settlement.getName(); 
    }

    
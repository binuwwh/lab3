#include <iostream>
#include <string>
#include <vector>
#include <map>

// Базовый класс для описателя информационного агентства
class InformationAgencyDescriptor {
public:
    InformationAgencyDescriptor(const std::string& name, const std::string& profile,
        const std::string& licenseNumber, const std::string& location)
        : name(name), profile(profile), licenseNumber(licenseNumber), location(location) {}

    virtual ~InformationAgencyDescriptor() {}

    std::string getName() const { return name; }
    std::string getProfile() const { return profile; }
    std::string getLicenseNumber() const { return licenseNumber; }
    std::string getLocation() const { return location; }
    virtual std::string getType() const = 0;
    virtual void displayInfo() const = 0;

private:
    std::string name;
    std::string profile;
    std::string licenseNumber;
    std::string location;
};

// Класс для описателя печатного издания
class PrintMediaDescriptor : public InformationAgencyDescriptor { //периодичность и тираж.
public:
    PrintMediaDescriptor(const std::string& name, const std::string& profile,
        const std::string& licenseNumber, const std::string& location,
        const std::string& periodicity, int circulation)
        : InformationAgencyDescriptor(name, profile, licenseNumber, location),
        periodicity(periodicity), circulation(circulation) {}

    std::string getType() const override { return "Print Media"; }
    void displayInfo() const override;

    std::string getPeriodicity() const { return periodicity; }
    int getCirculation() const { return circulation; }
    void setPrintCirculation(int newCirculation) { circulation = newCirculation; }
    void setPrintPeriodicity(const std::string& newPeriodicity) { periodicity = newPeriodicity; }

private:
    std::string periodicity;
    int circulation;
};

void PrintMediaDescriptor::displayInfo() const {
    std::cout << "Print Media Agency Information:" << std::endl;
    std::cout << "Name: " << getName() << std::endl;
    std::cout << "Profile: " << getProfile() << std::endl;
    std::cout << "License Number: " << getLicenseNumber() << std::endl;
    std::cout << "Location: " << getLocation() << std::endl;
    std::cout << "Periodicity: " << periodicity << std::endl;
    std::cout << "Circulation: " << circulation << std::endl;
}

// Класс для описателя радиостанции
class RadioStationDescriptor : public InformationAgencyDescriptor { //диапазон и частота вещания.
public:
    RadioStationDescriptor(const std::string& name, const std::string& profile,
        const std::string& licenseNumber, const std::string& location,
        const std::string& frequencyRange, const std::string& frequency)
        : InformationAgencyDescriptor(name, profile, licenseNumber, location),
        frequencyRange(frequencyRange), frequency(frequency) {}

    std::string getType() const override { return "Radio Station"; }
    void displayInfo() const override;

    std::string getFrequencyRange() const { return frequencyRange; }
    std::string getFrequency() const { return frequency; }
    void setFrequencyRange(const std::string& newRange) { frequencyRange = newRange; }
    void setFrequency(const std::string& newFrequency) { frequency = newFrequency; }

private:
    std::string frequencyRange;
    std::string frequency;
};

void RadioStationDescriptor::displayInfo() const {
    std::cout << "Radio Station Agency Information:" << std::endl;
    std::cout << "Name: " << getName() << std::endl;
    std::cout << "Profile: " << getProfile() << std::endl;
    std::cout << "License Number: " << getLicenseNumber() << std::endl;
    std::cout << "Location: " << getLocation() << std::endl;
    std::cout << "Frequency Range: " << frequencyRange << std::endl;
    std::cout << "Frequency: " << frequency << std::endl;
}

// Класс для таблицы, хранящей информацию об информационных агентствах
class InformationAgencyTable {
public:
    void addAgency(InformationAgencyDescriptor* agency);
    InformationAgencyDescriptor* findAgency(const std::string& name);
    void removeAgency(const std::string& name); //удаляет агентство с заданным именем
    void displayTable() const; // выводит информацию
    int countAgenciesInRegion(const std::string& region) const; // возвращает количество агентств, находящихся в указанном регионе

    std::vector<InformationAgencyDescriptor*> getAgenciesByType(const std::string& type) const; //возвращает вектор указателей на агентства определенного типа
    void revokeLicense(const std::string& name); //аннулирует лицензию агентства с заданным именем
    void registerNewAgency(const std::string& name, const std::string& profile, //регистрирует новое агентство в таблице
        const std::string& licenseNumber, const std::string& location,
        const std::string& type, const std::string& additionalInfo);
    void updateAgencyInfo(const std::string& name, const std::string& type, const std::string& field, const std::string& value); //обновляет информацию об агентстве с заданным именем и типом. 

private:
    std::vector<InformationAgencyDescriptor*> agencies;
};

void InformationAgencyTable::addAgency(InformationAgencyDescriptor* agency) {
    agencies.push_back(agency);
}

InformationAgencyDescriptor* InformationAgencyTable::findAgency(const std::string& name) {
    for (auto agency : agencies) {
        if (agency->getName() == name) {
            return agency;
        }
    }
    return nullptr;
}

void InformationAgencyTable::removeAgency(const std::string& name) {
    for (auto it = agencies.begin(); it != agencies.end(); ++it) {
        if ((*it)->getName() == name) {
            delete* it;
            agencies.erase(it);
            break;
        }
    }
}

void InformationAgencyTable::displayTable() const {
    for (const auto& agency : agencies) {
        agency->displayInfo();
        std::cout << std::endl;
    }
}

int InformationAgencyTable::countAgenciesInRegion(const std::string& region) const {
    int count = 0;
    for (const auto& agency : agencies) {
        if (agency->getLocation() == region) {
            count++;
        }
    }
    return count;
}

std::vector<InformationAgencyDescriptor*> InformationAgencyTable::getAgenciesByType(const std::string& type) const {
    std::vector<InformationAgencyDescriptor*> result;
    for (const auto& agency : agencies) {
        if (agency->getType() == type) {
            result.push_back(agency);
        }
    }
    return result;
}

void InformationAgencyTable::revokeLicense(const std::string& name) {
    for (auto it = agencies.begin(); it != agencies.end(); ++it) {
        if ((*it)->getName() == name) {
            // Do additional actions if needed before revoking the license
            delete* it;
            agencies.erase(it);
            break;
        }
    }
}

void InformationAgencyTable::registerNewAgency(const std::string& name, const std::string& profile,
    const std::string& licenseNumber, const std::string& location,
    const std::string& type, const std::string& additionalInfo) {
    if (type == "Print Media") {
        std::string periodicity;
        int circulation;
        std::cout << "Enter periodicity for Print Media: ";
        std::cin >> periodicity;
        std::cout << "Enter circulation for Print Media: ";
        std::cin >> circulation;
        PrintMediaDescriptor* printMedia = new PrintMediaDescriptor(name, profile, licenseNumber, location, periodicity, circulation);
        addAgency(printMedia);
    }
    else if (type == "Radio Station") {
        std::string frequencyRange, frequency;
        std::cout << "Enter frequency range for Radio Station: ";
        std::cin >> frequencyRange;
        std::cout << "Enter frequency for Radio Station: ";
        std::cin >> frequency;
        RadioStationDescriptor* radioStation = new RadioStationDescriptor(name, profile, licenseNumber, location, frequencyRange, frequency);
        addAgency(radioStation);
    }
    else {
        // Добавьте обработку других типов агентств при необходимости
        std::cerr << "Unsupported agency type." << std::endl;
    }
}

void InformationAgencyTable::updateAgencyInfo(const std::string& name, const std::string& type, const std::string& field, const std::string& value) {
    InformationAgencyDescriptor* agency = findAgency(name);
    if (agency) {
        if (type == "Print Media") {
            PrintMediaDescriptor* printMedia = dynamic_cast<PrintMediaDescriptor*>(agency);
            if (field == "Circulation") {
                int newCirculation = std::stoi(value);
                printMedia->setPrintCirculation(newCirculation);
            }
            else if (field == "Periodicity") {
                printMedia->setPrintPeriodicity(value);
            }
            else {
                std::cerr << "Unsupported field for Print Media." << std::endl;
            }
        }
        else if (type == "Radio Station") {
            RadioStationDescriptor* radioStation = dynamic_cast<RadioStationDescriptor*>(agency);
            if (field == "Frequency Range") {
                radioStation->setFrequencyRange(value);
            }
            else if (field == "Frequency") {
                radioStation->setFrequency(value);
            }
            else {
                std::cerr << "Unsupported field for Radio Station." << std::endl;
            }
        }
        else {
            std::cerr << "Unsupported agency type." << std::endl;
        }
    }
    else {
        std::cerr << "Agency not found." << std::endl;
    }
}

int main() {
    InformationAgencyTable table;

    table.registerNewAgency("PrintNews", "News", "12345", "CityA", "Print Media", "AdditionalInfo1");
    table.registerNewAgency("RadioWave", "Music", "67890", "CityB", "Radio Station", "AdditionalInfo2");

    table.displayTable();

    table.updateAgencyInfo("PrintNews", "Print Media", "Circulation", "15000");
    table.updateAgencyInfo("RadioWave", "Radio Station", "Frequency Range", "AM");

    table.displayTable();

    return 0;
}

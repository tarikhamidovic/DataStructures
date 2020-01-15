// Probably one of the worst codes I wrote...
// Have fun :)

#include<iostream>
#include"station.hpp"
#include<vector>
#include<fstream>
#include<string>
#include<stdexcept>

void loadCSV(std::vector<station>& vec) {
  std::ifstream file("stations.csv");
  if (!file.is_open()) {
    throw std::logic_error("Desila se greska pri otvaranju datoteke!");
  }
  else {
    std::string id, place, latitudestr, longitudestr, elevationstr, junk;
    std::getline(file, junk, '\n');
    while (file.good()) {
      std::getline(file, id, ',');
      std::getline(file, latitudestr, ',');
      std::getline(file, longitudestr, ',');
      std::getline(file, elevationstr, ',');
      std::getline(file, place, '\n');
      double latitude = std::stod(latitudestr);
      double longitude = std::stod(longitudestr);
      int elevation = std::stoi(elevationstr);
      station mystation(id, place, latitude, longitude, elevation);
      std::string fileName;
      fileName = place + ".csv";
      std::ifstream file2(fileName);
      if (!file2.is_open()) {
        throw std::logic_error("Desila se greska pri otvaranju datoteke!");
      }
      else {
        std::string yearptr, mintemp, maxtemp, monthptr, stationid;
        std::getline(file2, junk, '\n');
        while (file2.good()) {
          std::getline(file2, stationid, ',');
          std::getline(file2, yearptr, '-');
          std::getline(file2, monthptr, ',');
          std::getline(file2, maxtemp, ',');
          std::getline(file2, mintemp, '\n');
          int year = std::stoi(yearptr);
          int month = std::stoi(monthptr);
          if (maxtemp.size() == 0) {
            maxtemp = "N/A";
          }
          if (mintemp.size() == 0) {
            mintemp = "N/A";
          }
          info results(id, year, mintemp, maxtemp, month);
          mystation.addToVec(results);
        }
      }
      if (place == "Zagreb") {
        break;
      }
      vec.push_back(mystation);
    }
  }
}

station findStation(std::vector<station>& vec, const std::string& input) {
  for (int i = 0; i < vec.size(); ++i) {
    if (vec[i].getPlace() == input) {
      return vec[i];
    }
  }
  return station();
}

std::vector<info> findYear(std::vector<info> vec, const int& input) {
  std::vector<info> newVec;
  for (int i = 0; i < vec.size(); ++i) {
    if (vec[i].getYear() == input) {
      newVec.push_back(vec[i]);
    }
  }
  return newVec;
}

info findMonth(std::vector<info> vec, int input) {
  for (int i = 0; i < vec.size(); ++i) {
    if (vec[i].getMonth() == input) {
      return vec[i];
    }
  }
  return info();
}

void replaceinfo(std::vector<info>& vec, info val) {
  for (int i = 0; i < vec.size(); ++i) {
    if (vec[i].getMonth() == val.getMonth() && vec[i].getYear() == val.getYear()) {
      vec[i] = val;
      return;
    }
  }
  vec.push_back(val);
}

void replacestation(std::vector<station>& vec, station val) {
  for (int i = 0; i < vec.size(); ++i) {
    if (vec[i].getId() == val.getId()) {
      vec[i] = val;
      return;
    }
  }
}

int main(int argc, char *argv[])
{
  bool programRunning = true;
  std::vector<station> listOfStations;
  while (programRunning) {
    loadCSV(listOfStations);
    std::cout << "************ Historical temperature information ************" << std::endl;
    std::cout << "\t 1. Get information for enitre year" << std::endl;
    std::cout << "\t 2. Get information for specific month" << std::endl;
    std::cout << "\t 3. Insert new historical temperature information" << std::endl;
    std::cout  << std::endl;
    std::cout << "\t 4. Exit" << std::endl;
    std::cout << "Your choice?: " ;
    int menu;
    std::cin >> menu;
    switch (menu) {
      case 1 :
        {
          std::cout << "Enter location where station is placed: ";
          std::string inputPlace;
          std::cin >> inputPlace;
          station mystation = findStation(listOfStations, inputPlace);
          if (mystation.getPlace() == "") {
            std::cout << "No station with that name!" << std::endl;
            std::cout << std::endl;
            break;
          }
          std::cout << "Station ID: " << mystation.getId() << std::endl;
          std::cout << "Lattitude: " << mystation.getLatitude() << std::endl;
          std::cout << "Longitude: " << mystation.getLongitude() << std::endl;
          std::cout << "Elevation: " << mystation.getElevation() << std::endl;
          std::cout  << std::endl;
          std::cout << "Enter year: " ;
          int inputYear;
          std::cin >> inputYear;
          std::cout  << std::endl;
          std::vector<info> yearVector = findYear(mystation.getVec(), inputYear);
          std::cout << "Month \t Max temp \t Min temp" << std::endl;
          info data = findMonth(yearVector, 1);
          if (data.getMonth() != 0) {
            std::cout << "Jan \t " << data.getMaxtemp() << " \t \t "<< data.getMintemp()<< std::endl;
          }
          else {
            std::cout << "Jan \t N/A \t \t N/A" << std::endl;
          }
          data = findMonth(yearVector, 2);
          if (data.getMonth() != 0) {
            std::cout << "Feb \t " << data.getMaxtemp() << " \t \t "<< data.getMintemp()<< std::endl;
          }
          else {
            std::cout << "Feb \t N/A \t \t N/A" << std::endl;
          }
          data = findMonth(yearVector, 3);
          if (data.getMonth() != 0) {
            std::cout << "Mar \t " << data.getMaxtemp() << " \t \t "<< data.getMintemp()<< std::endl;
          }
          else {
            std::cout << "Mar \t N/A \t \t N/A" << std::endl;
          }
           data = findMonth(yearVector, 4);
          if (data.getMonth() != 0) {
            std::cout << "Apr \t " << data.getMaxtemp() << " \t \t "<< data.getMintemp()<< std::endl;
          }
          else {
            std::cout << "Apr \t N/A \t \t N/A" << std::endl;
          }
           data = findMonth(yearVector, 5);
          if (data.getMonth() != 0) {
            std::cout << "May \t " << data.getMaxtemp() << " \t \t "<< data.getMintemp()<< std::endl;
          }
          else {
            std::cout << "May \t N/A \t \t N/A" << std::endl;
          }
           data = findMonth(yearVector, 6);
          if (data.getMonth() != 0) {
            std::cout << "Jun \t " << data.getMaxtemp() << " \t \t "<< data.getMintemp()<< std::endl;
          }
          else {
            std::cout << "Jun \t N/A \t \t N/A" << std::endl;
          }
           data = findMonth(yearVector, 7);
          if (data.getMonth() != 0) {
            std::cout << "Jul \t " << data.getMaxtemp() << " \t \t "<< data.getMintemp()<< std::endl;
          }
          else {
            std::cout << "Jul \t N/A \t \t N/A" << std::endl;
          }
           data = findMonth(yearVector, 8);
          if (data.getMonth() != 0) {
            std::cout << "Aug \t " << data.getMaxtemp() << " \t \t "<< data.getMintemp()<< std::endl;
          }
          else {
            std::cout << "Aug \t N/A \t \t N/A" << std::endl;
          }
           data = findMonth(yearVector, 9);
          if (data.getMonth() != 0) {
            std::cout << "Sep \t " << data.getMaxtemp() << " \t \t "<< data.getMintemp()<< std::endl;
          }
          else {
            std::cout << "Sep \t N/A \t \t N/A" << std::endl;
          }
           data = findMonth(yearVector, 10);
          if (data.getMonth() != 0) {
            std::cout << "Oct \t " << data.getMaxtemp() << " \t \t "<< data.getMintemp()<< std::endl;
          }
          else {
            std::cout << "Oct \t N/A \t \t N/A" << std::endl;
          }
           data = findMonth(yearVector, 11);
          if (data.getMonth() != 0) {
            std::cout << "Nov \t " << data.getMaxtemp() << " \t \t "<< data.getMintemp()<< std::endl;
          }
          else {
            std::cout << "Nov \t N/A \t \t N/A" << std::endl;
          }
            data = findMonth(yearVector, 12);
          if (data.getMonth() != 0) {
            std::cout << "Dec \t " << data.getMaxtemp() << " \t \t "<< data.getMintemp()<< std::endl;
          }
          else {
            std::cout << "Dec \t N/A \t \t N/A" << std::endl;
          }
          std::cout << std::endl;
        }
        break;
      case 2 :
        {
          std::cout << "Enter location where station is placed: ";
          std::string inputPlace;
          std::cin >> inputPlace;
          station mystation = findStation(listOfStations, inputPlace);
          if (mystation.getPlace() == "") {
            std::cout << "No station with that name!" << std::endl;
            std::cout << std::endl;
            break;
          }
          std::cout << "Station ID: " << mystation.getId() << std::endl;
          std::cout << "Lattitude: " << mystation.getLatitude() << std::endl;
          std::cout << "Longitude: " << mystation.getLongitude() << std::endl;
          std::cout << "Elevation: " << mystation.getElevation() << std::endl;
          std::cout  << std::endl;
          std::cout << "Enter year: " ;
          int inputYear;
          std::cin >> inputYear;
          std::cout  << std::endl;
          std::vector<info> yearVector = findYear(mystation.getVec(), inputYear);
          std::cout << "Enter month: ";
          int inputMonth;
          std::cin >> inputMonth;
          if (inputMonth > 12 || inputMonth < 1) {
            std::cout << "Month goes out of range! :)" << std::endl;
            std::cout << std::endl;
            break;
          }
          info data = findMonth(yearVector, inputMonth);
          std::cout << "Max temp \t Min temp" << std::endl;
          std::cout << data.getMaxtemp() << " \t\t " << data.getMintemp() << std::endl;
          std::cout << std::endl;
        }
        break;
      case 3 :
        {
          std::cout << "Enter location where station is placed: ";
          std::string inputPlace;
          std::cin >> inputPlace;
          station mystation = findStation(listOfStations, inputPlace);
          if (mystation.getPlace() == "") {
            std::cout << "No station with that name!" << std::endl;
            std::cout << std::endl;
            break;
          }
          std::cout << "Station ID: " << mystation.getId() << std::endl;
          std::cout << "Lattitude: " << mystation.getLatitude() << std::endl;
          std::cout << "Longitude: " << mystation.getLongitude() << std::endl;
          std::cout << "Elevation: " << mystation.getElevation() << std::endl;
          std::cout  << std::endl;
          std::cout << "Enter year: " ;
          int inputYear;
          std::cin >> inputYear;
          std::cout  << std::endl;
          std::vector<info> yearVector = findYear(mystation.getVec(), inputYear);
          std::cout << "Enter month: ";
          int inputMonth;
          std::cin >> inputMonth;
          if (inputMonth > 12 || inputMonth < 1) {
            std::cout << "Month goes out of range! :)" << std::endl;
            std::cout << std::endl;
            break;
          }
          info data = findMonth(yearVector, inputMonth);
          std::cout << "1 -> Change Max temp" << std::endl;
          std::cout << "2. -> Change Min temp" << std::endl;
          std::cout << "Your choice: ";
          int choice;
          std::cin >> choice;
          switch (choice) {
            case 1 :
              {
                if (data.getMonth() == 0) {
                  data.setMonth(inputMonth);
                  data.setYear(inputYear);
                }
                std::cout << "Enter new value: ";
                std::string newVal;
                std::cin >> newVal;
                data.setMaxtemp(newVal);
                replaceinfo(mystation.getVec(), data);
                replacestation(listOfStations, mystation);
                break;
              }
            case 2: 
              {
                if (data.getMonth() == 0) {
                  data.setMonth(inputMonth);
                  data.setYear(inputYear);
                }
                std::cout << "Enter new value: ";
                std::string newVal;
                std::cin >> newVal;
                data.setMintemp(newVal);
                replaceinfo(mystation.getVec(), data);
                replacestation(listOfStations, mystation);
                break;
              }
            default :
              std::cout << "Invalid argument!" << std::endl;
              std::cout << std::endl;
              break;
          }
        }
        std::cout << std::endl;
        break;
      case 4 :
        programRunning = false;
        break;
      default :
        std::cout << "Invalid argument!" << std::endl;
        break;
    }
  }

  return 0;
}

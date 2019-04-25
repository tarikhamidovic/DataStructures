#ifndef _STATION_HPP_
#define _STATION_HPP_

#include<iostream>
#include<string>
#include<vector>

class info {
  public:
    info() = default;
    info(std::string id, int year, std::string mintemp, std::string maxtemp, int month) : id_{id}, year_{year}, mintemp_{mintemp}, maxtemp_{maxtemp}, month_{month} {}
    ~info() {}
    std::string getId() {
      return id_;
    }
    int getYear() {
      return year_;
    }
    std::string getMintemp() {
      return mintemp_;
    }
    std::string getMaxtemp() {
      return maxtemp_;
    }
    int getMonth() {
      return month_;
    }
    void setMintemp(const std::string& newValue) {
      mintemp_ = newValue;
    }
    void setMaxtemp(const std::string& newValue) {
      maxtemp_= newValue;
    }
    void setMonth(int input) {
      month_ = input;
    }
    void setYear(int input) {
      year_ = input;
    }
  private:
    std::string id_ = "";
    int year_ = 0;
    std::string mintemp_ = "N/A";
    std::string maxtemp_ = "N/A";
    int month_ = 0;
};

class station {
  public:
    station() = default;
    station(std::string id, std::string place, double latitude, double longitude, int elevation) : id_{id}, place_{place}, latitude_{latitude}, longitude_{longitude}, elevation_{elevation} {}
    ~station() {}
    std::string getId() {
      return id_;
    }
    std::string getPlace() {
      return place_;
    }
    double getLatitude() {
      return latitude_;
    }
    double getLongitude() {
      return longitude_;
    }
    int getElevation() {
      return elevation_;
    }
    void addToVec(const info& val) {
      infoVec_.push_back(val);
    }
    std::vector<info>& getVec() {
      return infoVec_;
    }
    friend std::ostream& operator<<(std::ostream& out, const station& stat) {
      out << stat.id_ << ' ' << stat.latitude_ << ' ' << stat.longitude_ << ' ' << stat.elevation_ << ' ' << stat.place_ ;
      return out;
    }
  private:
    std::string id_ = "";
    std::string place_ = "";
    double latitude_ = 0;
    double longitude_ = 0;
    int elevation_ = 0;
    std::vector<info> infoVec_;
};

#endif

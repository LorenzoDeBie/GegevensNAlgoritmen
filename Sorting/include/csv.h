#pragma once

#include <algorithm>
#include <cassert>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>


class CsvData
{
public:
    // Scheidingsteken: teken in vlottendekommagetallen
    // Voor een Nederlandstalige excel, scheidingsteken ',' opgeven
    CsvData(const std::string& bestandsnaam, char scheidingsteken = '.', char delimiter = '\t');

    template <class T> // T kan int, unsigned int, float, ... zijn
    void voeg_data_toe(const std::vector<T>& toe_te_voegen_data);

    void voeg_data_toe(const std::vector<double>& nieuwe_data);

    std::string to_string() const;

    std::string geef_bestandsnaam() const;
    void write_to_file() const;

protected:
    std::vector<std::vector<double>> data;
    char scheidingsteken;
    char delimiter;
    std::string bestandsnaam;
    std::vector<double>::size_type max_kolom_grootte = 0;

    static constexpr int kolombreedte = 12;
    static constexpr int precisie = 6;
    static const std::string extensie;
};

template <class T> // T kan int, unsigned int, float, ... zijn
void CsvData::voeg_data_toe(const std::vector<T>& toe_te_voegen_data)
{
    std::vector<double> nieuwe_data;
    nieuwe_data.reserve(toe_te_voegen_data.size());

    for (const T& d : toe_te_voegen_data)
    {
        nieuwe_data.push_back(static_cast<double>(d));
    }

    voeg_data_toe(nieuwe_data);
}


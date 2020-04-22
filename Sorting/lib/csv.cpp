#include <csv.h>

const std::string CsvData::extensie{".csv"};

CsvData::CsvData(const std::string& bestandsnaam, char scheidingsteken, char delimiter)
: scheidingsteken{scheidingsteken}, delimiter{delimiter}, bestandsnaam{bestandsnaam}
{
    if (bestandsnaam.empty())
    {
        throw "Lege bestandsnaam";
    }

    std::string::size_type begin_extensie = bestandsnaam.rfind(extensie);

    if (begin_extensie == 0)
    {
        throw "Ongeldige bestandsnaam";
    }

    if ((begin_extensie == std::string::npos) || (begin_extensie != (bestandsnaam.size() - extensie.size())))
    {
        this->bestandsnaam.append(extensie);
    }
}

void CsvData::voeg_data_toe(const std::vector<double>& nieuwe_data)
{
    data.push_back(nieuwe_data);

    auto kolom_grootte = nieuwe_data.size();
    if (kolom_grootte > max_kolom_grootte)
    {
        max_kolom_grootte = kolom_grootte;
    }
}

std::string CsvData::to_string() const
{
    std::stringstream out;

    for (std::size_t i = 0; i < max_kolom_grootte; i++)
    {
        for (std::size_t j = 0; j < data.size(); j++)
        {
            if (i < data[j].size())
            {
                out << std::setprecision(precisie) << std::scientific << data[j][i];
            }

            if (j == (data.size() - 1))
            {
                out << '\n';
            }
            else
            {
                out << delimiter;
            }
        }
    }

    std::string content = out.str();
    std::replace(content.begin(), content.end(), '.', scheidingsteken);

    return content;
}

std::string CsvData::geef_bestandsnaam() const
{
    return bestandsnaam;
}

void CsvData::write_to_file() const
{
    std::ofstream out(bestandsnaam);
    assert(out);

    out << to_string();
}
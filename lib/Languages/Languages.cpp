#include <unordered_map>
#include <vector>
#include <string>

#include "Languages.h"

std::unordered_map<std::string, std::vector<std::string>> months = {
    {"en", {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"}},
    {"it", {"Gen", "Feb", "Mar", "Apr", "Mag", "Giu", "Lug", "Ago", "Set", "Ott", "Nov", "Dic"}},
    {"es", {"Ene", "Feb", "Mar", "Abr", "May", "Jun", "Jul", "Ago", "Sep", "Oct", "Nov", "Dic"}},
    {"fr", {"Jan", "Fev", "Mar", "Avr", "Mai", "Jun", "Jul", "Aou", "Sep", "Oct", "Nov", "Dec"}},
    {"de", {"Jan", "Feb", "Mar", "Apr", "Mai", "Jun", "Jul", "Aug", "Sep", "Okt", "Nov", "Dez"}}
};

std::unordered_map<std::string, std::vector<std::string>> days = {
    {"en", {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"}},
    {"it", {"Dom", "Lun", "Mar", "Mer", "Gio", "Ven", "Sab"}},
    {"es", {"Dom", "Lun", "Mar", "Mie", "Jue", "Vie", "Sab"}},
    {"fr", {"Dim", "Lun", "Mar", "Mer", "Jeu", "Ven", "Sam"}},
    {"de", {"Son", "Mon", "Die", "Mit", "Don", "Fre", "Sam"}}
};
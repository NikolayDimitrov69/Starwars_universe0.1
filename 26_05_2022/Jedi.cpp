#include "Jedi.h"


std::istream& operator>>(std::istream& is, Jedi& jedi)
{
    is >> jedi.planet >> jedi.name >> jedi.rank >> jedi.age >> jedi.saber_color >> jedi.strenght;
    return is;
}

std::ostream& operator<<(std::ostream& os, const Jedi& jedi)
{
    os << "Jedi " << jedi.getPlanet() << ' ' << jedi.getName() << ' ' << jedi.getRank() << ' ' << jedi.getAge() << ' ' << jedi.getSaberColor() << ' ' << jedi.getStrenght() << '\n';
    return os;
}
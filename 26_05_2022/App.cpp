#include "App.h"

void App::nextLine()
{
	const int max = 100;
	char word[max]{};
	std::cin.getline(word, max, '\n');

	char newcommand[max]{};
	char newargument[max]{};

	int i = 0;
	int j = 0;
	for (; word[i] != ' ' && word[i] != '\0'; i++)
	{
		newcommand[i] = word[i];
	}

	command = newcommand;

	do {
		if (word[i] == ' ' && word[i] != '\0')
		{
			i++;
		}
		for (; word[i] != ' ' && word[i] != '\0'; i++, j++)
		{
			newargument[j] = word[i];
		}
		if (j > 0)
		{
			arguments.push_back(newargument);
			//! Зануляване на newargument
			for (unsigned i = 0; i < j; i++)
			{
				newargument[i] = 0;
			}
		}
		j = 0;
	} while (word[i] != '\0');
}

std::string App::GetStrongestJedi(std::string planet)
{
	std::string strongestjedi = "";
	double higheststrenght = 0;
	for (unsigned i = 0; i < jedis.size(); i++)
	{	
		if (planet == jedis[i].getPlanet() && jedis[i].getStrenght() > higheststrenght)
		{
			higheststrenght = jedis[i].getStrenght();
			strongestjedi = jedis[i].getName();
		}
	}
	return strongestjedi;
}

std::string App::GetYoungestJedi(std::string planet, unsigned _rank) 
{
	std::string youngestjedi = "";
	unsigned lowestage = 9999999999999999999;
	for (unsigned i = 0; i < jedis.size(); i++)
	{
		if (planet == jedis[i].getPlanet() && _rank == jedis[i].getRank() && (jedis[i].getAge() < lowestage || jedis[i].getAge() == lowestage && jedis[i].getName() < youngestjedi))
		{
			lowestage = jedis[i].getAge();
			youngestjedi = jedis[i].getName();
		}
	}
	return youngestjedi;
}

const bool& App::PlanetsExists(std::string planet) const
{
	for (unsigned i = 0; i < planets.size() && planets.size() != 0; i++)
	{
		if (planet == planets[i])
		{
			return true;
		}
	}
	return false;
}

const bool& App::JediExists(std::string jedi) const
{
	for (unsigned i = 0; i < jedis.size() && jedis.size() != 0; i++)
	{
		if (jedi == jedis[i].getName())
		{
			return true;
		}
	}
	return false;
}

const bool& App::JediExistsOnPlanet(std::string jedi, std::string planet) const
{
	for (unsigned i = 0; i < jedis.size() && jedis.size() != 0; i++)
	{
		if (jedi == jedis[i].getName() && planet == jedis[i].getPlanet())
		{
			return true;
		}
	}
	return false;
}

const bool& App::canRankIncrease(std::string name) const
{
	for (unsigned i = 0; i < jedis.size(); i++)
	{
		if (name == jedis[i].getName() && jedis[i].getRank() < 7)
		{
			return true;
		}
	}
	return false;
}

const bool& App::canRankDecrease(std::string name) const
{
	for (unsigned i = 0; i < jedis.size(); i++)
	{
		if (name == jedis[i].getName() && jedis[i].getRank() > 0)
		{
			return true;
		}
	}
	return false;
}

const bool& App::PlanetIsInahbitet(std::string planet) const
{
	for  (unsigned i = 0;  i < jedis.size();  i++)
	{
		if (planet == jedis[i].getPlanet())
		{
			return true;
		}
	}
	return false;
}

const bool& App::planetHasAGrandMaster(std::string planet) const {
	for (unsigned i = 0; i < jedis.size(); i++)
	{
		if (planet == jedis[i].getPlanet() && jedis[i].getRank() == 7)
		{
			return true;
		}
	}
	return false;
}

void App::EraseJediNumber(std::string jedi) {
	unsigned t = 0;
	while (jedi != jedis[t].getName() && t <= jedis.size())
	{
		t++;
	}
	jedis.erase(jedis.begin() + t);
}

void App::IncreaseJediRank(std::string name, double multiplier)
{
	for (unsigned i = 0; i < jedis.size(); i++)
	{
		if (name == jedis[i].getName())
		{
			jedis[i].setRank(jedis[i].getRank() + 1);
			jedis[i].setStrenght(jedis[i].getStrenght() * (1 + multiplier));
		}
	}
}

void App::DecreaseJediRank(std::string name, double multiplier)
{
	for (unsigned i = 0; i < jedis.size(); i++)
	{
		if (name == jedis[i].getName())
		{
			jedis[i].setRank(jedis[i].getRank() - 1);
			jedis[i].setStrenght(jedis[i].getStrenght() * (1 - multiplier));
		}
	}
}

const unsigned& App::getNumberOfRank(std::string str) const{
	Jedi jedi;
	for (unsigned i = 0; i < 8; i++)
	{
		if (str == jedi.getRankName(i))
		{
			return i;
		}
	}
	return 8;
}

const unsigned& App::getNumberOfColor(std::string str) const {
	Jedi jedi;
	for (unsigned i = 0; i < 12; i++)
	{
		if (str == jedi.getSaberColorName(i))
		{
			return i;
		}
	}
	return 12;
}

std::string App::getMostUsedColor(std::string planet, unsigned rank){
	Jedi jedi;
	unsigned Arr[12]{};
	for (unsigned i = 0; i < jedis.size(); i++)
	{
		if (planet == jedis[i].getPlanet() && rank == jedis[i].getRank() && rank != -1)
		{
			Arr[jedis[i].getSaberColor()]++;
		}
		if (planet == jedis[i].getPlanet() && rank == -1 && planetHasAGrandMaster(planet))
		{
			Arr[jedis[i].getSaberColor()]++;
		}
	}
	return jedi.getSaberColorName(biggestNumInArray(Arr, 12));
}

void App::PrintInhabitants(std::string planet) 
{
	Jedi* array{ new Jedi[jedis.size()]{} };
	for (unsigned rank = 0; rank < 8; rank++)
	{
		unsigned j = 0;
		for (unsigned i = 0; i < jedis.size(); i++)
		{
			if (planet == jedis[i].getPlanet() && jedis[i].getRank() == rank)
			{
				array[j] = jedis[i];
				j++;
			}
		}
		selectionSort(array, j);
		for (unsigned i = 0; i < j; i++)
		{
			std::cout << "Name: " << array[i].getName() << '\n';
		}
	}
	delete[] array;
}

void App::PrintInhabitants2(std::string planet, std::string planet2)
{
	Jedi* array{ new Jedi[jedis.size()]{} };
	unsigned j = 0;
	for (unsigned i = 0; i < jedis.size(); i++)
	{
		if (planet == jedis[i].getPlanet() || planet2 == jedis[i].getPlanet())
		{
			array[j] = jedis[i];
			j++;
		}
	}
	selectionSort(array, j);
	for (unsigned i = 0; i < j; i++)
	{
		std::cout << "Name: " << array[i].getName() << '\n';
	}
	delete[] array;
}

void App::selectionSort(Jedi * arr, int n)
{
	int i, j, min_idx;

	for (i = 0; i < n - 1; i++)
	{

		min_idx = i;
		for (j = i + 1; j < n; j++)
			if (alpha_sort(arr[j].getName(), arr[min_idx].getName()) == arr[j].getName())
				min_idx = j;

		swap(&arr[min_idx], &arr[i]);
	}
}

void App::swap(Jedi* xp, Jedi* yp)
{
	Jedi holder = *xp;
	*xp = *yp;
	*yp = holder;
}

Jedi App::getJedi(std::string name) {
	for (unsigned i = 0; i < jedis.size(); i++)
	{
		if (name == jedis[i].getName())
		{
			Jedi jedi(jedis[i].getPlanet(), jedis[i].getName(), jedis[i].getRank(), jedis[i].getAge(), jedis[i].getSaberColor(), jedis[i].getStrenght());
			return jedi;
		}
	}
}

std::ostream& operator << (std::ostream& os, const Jedis& jedis)
{
	for (unsigned i = 0; i < jedis.size() && jedis.size() != 0; i++)
	{
		os << jedis[i];
	}
	return os;
}

std::ostream& operator << (std::ostream& os, const Planets& planets)
{
	for (unsigned i = 0; i < planets.size() && planets.size() != 0; i++)
	{
		os << "Planet " << planets[i] << '\n';
	}
	return os;
}

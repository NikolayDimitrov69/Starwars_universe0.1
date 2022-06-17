#ifndef JEDI_H
#define JEDI_H
#include <iostream>
#include <string>

class Jedi {
private:
    std::string planet;
	std::string name;
	unsigned rank;
	std::string RankName[8] = { "YOUNGLING", "INITIATE", "PADAWAN", "KNIGHT_ASPIRANT", "KNIGHT","MASTER", "BATTLE_MASTER","GRAND_MASTER" };
	unsigned age;
	unsigned saber_color;
	std::string CannonColors[12] = { "white", "yellow", "brown", "red", "black", "purple", "magenta", "cyan", "blue-green", "orange", "green", "blue"};
	double strenght;
public:
	Jedi() {
		planet = "";
		name = "";
		rank = 0;
		age = 0;
		saber_color = 0;
		strenght = 0;
	}

	Jedi(std::string _newplanet, std::string _newname, unsigned _newrank, unsigned _newage, unsigned _newsaber_color, double _newstrenght) 
		:planet(_newplanet), name(_newname), rank(_newrank), age(_newage), saber_color(_newsaber_color), strenght(_newstrenght)
	{}

	//! Селектори:
	const std::string& getPlanet() const {
		return planet;
	}

	const std::string& getName() const {
		return name;
	}

	const unsigned& getRank()const {
		return rank;
	}

	const std::string& getRankName(unsigned _rank)const {
		return RankName[_rank];
	}

	const unsigned& getAge() const {
		return age;
	}

	const unsigned& getSaberColor() const {
		return saber_color;
	}

	const std::string& getSaberColorName(unsigned _color) {
		return CannonColors[_color];
	}

	const double& getStrenght() const {
		return strenght;
	}

	//! Мутатори:
	void setPlanet(std::string _newplanet) {
		planet = _newplanet;
	}

	void setName(std::string _newname) {
		name = _newname;
	}

	void setRank(unsigned _newrank) {
		rank = _newrank;
	}

	void setAge(unsigned _newage) {
		age = _newage;
	}

	void setSaberColor(unsigned _newcolor) {
		saber_color = _newcolor;
	}

	void setStrenght(double _newstrenght) {
		strenght = _newstrenght;
	}

	friend std::istream& operator >> (std::istream&, Jedi&);
};

std::ostream& operator<<(std::ostream&, const Jedi&);

#endif
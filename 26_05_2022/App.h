#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include "Jedi.h"
#include "Functions.h"

using Planets = std::vector<std::string>;

using Jedis = std::vector<Jedi>;

using Arguments = std::vector<std::string>;

class App {
private:
	Planets planets;

	Jedis jedis;

	std::string status;

	std::string command;

	Arguments arguments;

	std::string currentFile;

public:

	App() {
		status = "closed";
		command = "";
		currentFile = "";
	}

	void nextLine();

	//! Селектори:
	const Planets& printPlanetVector() const  {
		return planets;
	}

	const Jedis& printJediVector() const {
		return jedis;
	}

	const unsigned& getPlanetSize() const {
		return planets.size();
	}

	const unsigned& getJediSize() const {
	return jedis.size();
	}

	std::string GetStrongestJedi(std::string);

	std::string GetYoungestJedi(std::string, unsigned);

	const std::string& getStatus() const{
		return status;
	}

	const std::string& getCurrentFile() const {
		return currentFile;
	}

	const std::string& getCommand() const {
		return command;
	}

	const unsigned& getNumberOfRank(std::string)const;

	const unsigned& getNumberOfColor(std::string str) const;

	const Arguments& getArgument() const {
		return arguments;
	}

	const std::string& getArgumentNumber(unsigned i) const {
		return arguments[i];
	}

	const unsigned& getArgumentSize() const {
		return arguments.size();
	}

	//! Мутатори:
	void pushbackPlanet(std::string _newplanet) {
		planets.push_back(_newplanet);
	}

	void pushbackJedi(Jedi _newjedi) {
		jedis.push_back(_newjedi);
	}

	void setStatus(std::string _newstatus) {
		status = _newstatus;
	}

	void setCurrentFile(std::string _newfile) {
		currentFile = _newfile;
	}

	void setCommand(std::string _newcommand) {
		command = _newcommand;
	}

	void pushbackArgument(std::string _newargument) {
		arguments.push_back(_newargument);
	}

	//! Изтривач на вектор	
	void PlanetsVectorErase() {
		planets.clear();
	}

	void JediVectorErase() {
		jedis.clear();
	}

	void ArgumentVectorErase() {
		arguments.clear();
	}

	void EraseJediNumber(std::string);

	//! Проверки
	const bool& PlanetsExists(std::string) const;

	const bool& JediExists(std::string) const;

	const bool& JediExistsOnPlanet(std::string, std::string) const;

	const bool& PlanetIsInahbitet(std::string) const;

	const bool& canRankIncrease(std::string) const;

	const bool& canRankDecrease(std::string) const;

	const bool& planetHasAGrandMaster(std::string) const;

	//! Функционалности
	void IncreaseJediRank(std::string, double);

	void DecreaseJediRank(std::string, double);

	std::string getMostUsedColor(std::string, unsigned);

	void PrintInhabitants(std::string);

	void PrintInhabitants2(std::string, std::string);

	void selectionSort(Jedi*, int );

	void swap(Jedi*, Jedi*);

	Jedi getJedi(std::string);
};

std::ostream& operator << (std::ostream&, const Jedis&);

std::ostream& operator << (std::ostream&, const Planets&);
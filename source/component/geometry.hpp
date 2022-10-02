#pragma once
#include "../main/global.hpp"

//-------------------------------------------------------------

struct Triangle {
	sf::Vector2f* points = new sf::Vector2f[3];
	sf::Vector2f* sideNormals = new sf::Vector2f[3];
	bool isClockwise;

	//-------------------------------------------------------------

	Triangle() {}
	Triangle(sf::Vector2f p_point_0, sf::Vector2f p_point_1, sf::Vector2f p_point_2);

	//-------------------------------------------------------------

	void calculateSideNormals();
};

//-------------------------------------------------------------

extern std::vector<Triangle> getTrianglesFromPolygon(std::vector<sf::Vector2f> p_points);
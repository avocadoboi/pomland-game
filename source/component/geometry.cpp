#include "geometry.hpp"

//-------------------------------------------------------------
//
// struct Triangle
//
//-------------------------------------------------------------

Triangle::Triangle(sf::Vector2f p_point_0, sf::Vector2f p_point_1, sf::Vector2f p_point_2) {
	points[0] = p_point_0;
	points[1] = p_point_1;
	points[2] = p_point_2;
}

void Triangle::calculateSideNormals() {
	isClockwise = (points[0].x*(points[1].y - points[2].y) + points[1].x*(points[2].y - points[0].y) + points[2].x*(points[0].y - points[1].y)) < 0;
	sideNormals[0] = getVector2Rotated90Degrees(getVector2Normalized(points[1] - points[0]), isClockwise);
	sideNormals[1] = getVector2Rotated90Degrees(getVector2Normalized(points[2] - points[1]), isClockwise);
	sideNormals[2] = getVector2Rotated90Degrees(getVector2Normalized(points[0] - points[2]), isClockwise);
}

//-------------------------------------------------------------
//
// Functions
//
//-------------------------------------------------------------

std::vector<Triangle> getTrianglesFromPolygon(std::vector<sf::Vector2f> p_points) {
	std::vector<Triangle> triangles;
	if ((int)p_points.size() > 2) {
		float area = 0;
		for (int a = 0; a < (int)p_points.size(); a++) {
			sf::Vector2f& nextPoint = a == (int)p_points.size() - 1 ? p_points[0] : p_points[a + 1];
			area += (p_points[a].x - nextPoint.x) * (p_points[a].y + nextPoint.y);
		}
		bool isClockwise = area > 0;

		while ((int)p_points.size() > 2) {
			Triangle bestTriangle;
			int bestTrianglePointIndex;
			float bestSideSquareSum = -1;

			for (int a = 0; a < (int)p_points.size(); a++) {
				int i1 = a < (int)p_points.size() - 1 ? a + 1 : 0;
				int i2 = a < (int)p_points.size() - 2 ? a + 2 : (a < (int)p_points.size() - 1 ? 0 : 1);

				sf::Vector2f& point_0 = p_points[a];
				sf::Vector2f point_1 = p_points[i1];
				sf::Vector2f point_2 = p_points[i2];

				float rotation = getVector2Rotation(point_1, point_0);
				rotateVector2(point_1, point_0, -rotation);
				rotateVector2(point_2, point_0, -rotation);

				if (isClockwise ? (point_2.y > point_0.y) : (point_2.y < point_0.y)) {
					float sideSquareSum = getVector2DistanceSquared(p_points[a], p_points[i1])
										+ getVector2DistanceSquared(p_points[i1], p_points[i2])
										+ getVector2DistanceSquared(p_points[i2], p_points[a]);
					if (bestSideSquareSum == -1 || sideSquareSum < bestSideSquareSum) {
						bestTriangle = Triangle(p_points[a], p_points[i1], p_points[i2]);
						bestTrianglePointIndex = i1;
						bestSideSquareSum = sideSquareSum;
					}
				}
			}

			bestTriangle.calculateSideNormals();
			triangles.push_back(bestTriangle);
			p_points.erase(p_points.begin()+bestTrianglePointIndex);
		}
	}
	return triangles;
}
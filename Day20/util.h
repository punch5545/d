#pragma once
struct ColorRGBA {
	unsigned short Red;
	unsigned short Green;
	unsigned short Blue;
};

struct prevShape {
	int startX;
	int startY;
	int endX;
	int endY;
	char shapeType;
	char brushType;
	char penType;
	char penSize;
	bool isBrush;
	ColorRGBA cBrush;
	ColorRGBA cPen;
};
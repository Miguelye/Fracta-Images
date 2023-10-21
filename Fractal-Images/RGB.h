#pragma once

namespace mayg

{

struct RGB
{
	double r;
	double g;
	double b;

	RGB(double r, double g, double b);
};

//overloading the - operator
RGB operator-(const RGB& first, const RGB& second);

}


#include "ZoomList.h"

namespace mayg
{

	ZoomList::ZoomList(int width, int height) : m_width(width), m_height(height) {
	
	};

	// This Fuctions calculates the center of the current image state.
	void ZoomList::add(const Zoom& zoom)
	{
		zooms.push_back(zoom);

		m_xCenter += (zoom.x - m_width / 2) * m_scale;
		m_yCenter += (zoom.y - m_height / 2) * m_scale;
		m_scale *= zoom.scale;
	}

	std::pair<double, double> ZoomList::doZoom(int x, int y)
	{
		//Scaling making the range from -1 to 1;
		double xFractal = (x - m_width / 2) * m_scale + m_xCenter;
		double yFractal = (y - m_height / 2) * m_scale + m_yCenter;

		return std::pair<double, double>(xFractal, yFractal);
	}
}
//
//  CueLaserGraphic.cpp
//
//  Created by Seb Lee-Delisle on 29/07/2018.
//

#include "CueLaserGraphic.h"



void CueLaserGraphic :: loadFromSVG(string filename, int targetzone){
	graphic.clear();

	svg.load(filename);
	if(name->size()==0) setName(filename);
	graphic.addSvg(svg, true, true); // optimise, subtract fills
	targetZone = targetzone;
	
}


void CueLaserGraphic :: update(float time, bool isPlaying){
    
    if(isActive(time)) {
		laser.setTargetZone(targetZone);
      	graphic.renderToLaser(laser);
    }


}

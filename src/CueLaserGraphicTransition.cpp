//
//  CueLaserGraphicTransition.cpp
//  BecHillLasers
//
//  Created by Seb Lee-Delisle on 13/08/2018.
//
//

#include "CueLaserGraphicTransition.h"



void CueLaserGraphicTransition :: loadFromSVG(string filename, int targetzone){
	graphic.clear();
	
	svg.load(filename);
	if(name->size()==0) setName(filename);
	graphic.addSvg(svg, false);
	targetZone = targetzone;
	
	ofSort(graphic.polylines, CueLaserGraphicTransition::sortByXPosition);

	totalLineLength = 0;
	
	for(int i = 0; i<graphic.polylines.size(); i++) {
		totalLineLength+=graphic.polylines[i]->getPerimeter();
	}
	
}

void CueLaserGraphicTransition :: update(float time, bool isPlaying){
	
	if(isActive(time)) {
		
		laser.setTargetZone(targetZone);
		
		float cueTime = time - getStart();
		
		if(cueTime<startTrans) {
			
			vector<ofPolyline*>& polys = graphic.polylines;
			vector<ofColor>& colours = graphic.colours;
			
			float progressLength = ofMap(cueTime, 0, startTrans, 0, totalLineLength);
			
			//int polyindex = ofMap(progress, 0, 1, 0, polys.size());
			tempPoly.clear();
			
			float currentLength = 0;
			for(int i = 0; i<polys.size(); i++) {
				ofPolyline & poly = *polys[i];
				float perimeter = poly.getPerimeter();
				if(currentLength+perimeter>progressLength) {
//					float polyprogress = (progressLength-currentLength)/perimeter;
					
					float maxVertex = poly.getIndexAtLength(progressLength-currentLength);
					
					for(int j = 0; j<maxVertex; j++) {
						tempPoly.addVertex(poly.getPointAtIndexInterpolated(j));
					}
					
					tempPoly.addVertex(poly.getPointAtIndexInterpolated(maxVertex));
					laser.drawPoly(tempPoly, colours[i]);
					laser.drawDot(poly.getPointAtIndexInterpolated(maxVertex), colours[i], 1, OFXLASER_PROFILE_DETAIL);
					break;
				} else {
					laser.drawPoly(poly, colours[i]);
					currentLength+=poly.getPerimeter();
				}
			}
			
		} else {
			graphic.renderToLaser(laser);
		}
		
		
	}
	
	
}

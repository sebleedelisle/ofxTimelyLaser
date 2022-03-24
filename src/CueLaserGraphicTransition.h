//
//  CueLaserGraphicTransition.h
//  BecHillLasers
//
//  Created by Seb Lee-Delisle on 13/08/2018.
//
//

#pragma once
#include "ofMain.h"
#include "CueLaserGraphic.h"

class CueLaserGraphicTransition : public CueLaserGraphic {
	
	public:
	
	CueLaserGraphicTransition() {
		
		fixedLength = true;
		params.add(startTrans.set("start transition", 0, 0,10));
		params.add(endTrans.set("end transition", 0, 0,10));
		//params.remove(duration);
	};
	
	virtual void loadFromSVG(string filename, int targetZone = 0);
	
	virtual void update(float time, bool isPlaying);
	
	ofParameter<float> startTrans = 0, endTrans = 0;
	
	float totalLineLength = 0;
	ofPolyline tempPoly; 
	
	static bool sortByXPosition(const ofPolyline* a, const ofPolyline* b) {
		
		return a->getBoundingBox().x < b->getBoundingBox().x;
	}
	protected:

	private:

};

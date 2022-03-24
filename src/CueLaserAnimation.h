//
//  CueLaserAnimation.h
//  BecHillLasers
//
//  Created by Seb Lee-Delisle on 30/07/2018.
//
//

#pragma once
#include "ofMain.h"
#include "CueTransformable.h"
#include "ofxLaserGraphic.h"
#include "ofxLaserManager.h"
//#include "ofxSvg.h"
#include "SVGLoader.h"

class CueLaserAnimation : public CueTransformable{
	
public:
	
	CueLaserAnimation() : laser(*ofxLaser::Manager::instance()) {
		
		fixedLength = true;
		params.add(targetZone.set("target Zone", 0, 0,8));
		params.add(fps.set("frame rate", 30, 1,120));
		params.add(startPadding.set("start delay", 0, 0,10));
		params.add(endPadding.set("end padding", 0, 0,10));
		//params.remove(duration);
	};
	void loadSVGSequence(string filename, int targetZone = 0);
	virtual void update(float time, bool isPlaying);
	
	virtual void drawCueBlock();
		
	void autoSetEnd(); 
	
	int getNumFrames() { return numFrames;}
	float getFPS() { return fps;}
	float getStartPadding() { return startPadding;}
	
	void setFPS(float framerate) { fps = framerate;}
	void setStartPadding(float delay) { startPadding = delay;}
	
	//int targetZone = 0;
	
	const string type = "CueLaserAnimation";
	
protected:
	
	SVGLoader svgLoader;
	
	ofxLaser::Manager& laser;
	ofParameter<float> fps = 30;
	ofParameter<float> startPadding = 0, endPadding = 0;
	ofParameter<int> targetZone = 0;
	int numFrames = 0;
	
	// TODO add looping, play count, ping pong etc
	
private:
	
};

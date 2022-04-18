//
//  CueLaserAnimation.cpp
//  BecHillLasers
//
//  Created by Seb Lee-Delisle on 30/07/2018.
//
//

#include "CueLaserAnimation.h"

void CueLaserAnimation :: loadSVGSequence(string filename, int targetzone){

	// THIS SHOULD NEVER BE CALLED MORE THAN ONCE
	
	numFrames = svgLoader.startLoad(filename);
	autoSetEnd();
	//setName(filename);
	targetZone = targetzone;
}
void CueLaserAnimation :: update(float time, bool isPlaying){
	
    if(!initialised && svgLoader.hasFinishedLoading()) {
        updateColourList();
        autoSetEnd();
        initialised = true;
    }
	
	if(isActive(time)) {

		float cueTime = time - getStart()-startPadding;
		int index = round(cueTime * fps);
		if(index<0) index = 0; 
		ofxLaser::Graphic &graphic = svgLoader.getLaserGraphic(index);
		laser.setTargetZone(targetZone);
        
        
        vector<ofPolyline*> & polylines = graphic.polylines;
        vector<ofColor> & colours = graphic.colours;
        
        for(size_t i= 0; i<polylines.size(); i++) {
            ofColor& colour = colours[i];
            int col = colour.getHex();

            if(zonesByColour.find(col)!=zonesByColour.end()) {
                int zone = zonesByColour[col];
                if(zone>=0) laser.setTargetZone(zone);
                else laser.setTargetZone(targetZone);
            } else {
                laser.setTargetZone(targetZone);
            }
            laser.drawPoly(*polylines[i],colour, OFXLASER_PROFILE_DEFAULT);
            
        }
        
		//laser.drawLaserGraphic(graphic);
		
		//ofLog(OF_LOG_NOTICE, "index : " + ofToString(index)+ " cueTime : " + ofToString(cueTime) + " duration : " + ofToString(duration)+ " numFrames : " + ofToString(numFrames)); 
	
		
	}
	
	
}

void CueLaserAnimation :: updateColourList() {
    colourList.clear();
    int numframes = svgLoader.frames.size();
    for(int i = 0; i<numframes ; i++ ) {
        ofxLaser::Graphic &graphic = svgLoader.getLaserGraphic(i);
        for(ofColor& colour : graphic.colours) {
            if(std::find(colourList.begin(), colourList.end(), colour)==colourList.end()) {
                colourList.push_back(colour);
            }
            
        }
        
    }
    cout << name << endl;
    for(ofColor& colour : colourList) {
        cout << std::hex << colour.getHex()<< endl;
    }
    
    
    
}
void CueLaserAnimation :: autoSetEnd() {
	setDuration ((float)numFrames/fps + startPadding + endPadding);
	
	
}

void CueLaserAnimation :: drawCueBlock() {
	
	ofRectangle drawRect = rect;
	drawRect.x = round(drawRect.x);
	drawRect.y = round(drawRect.y);
	drawRect.setWidth(round(drawRect.getWidth()));
	drawRect.setHeight(round(drawRect.getHeight()));
	
	
	
	
	ofPushStyle();
	ofFill();
	ofSetColor(fillColour);
	ofRectangle progressRect(drawRect);
	if(svgLoader.getLoadedCount()<getNumFrames()) {
		progressRect.setWidth(ofMap(svgLoader.getLoadedCount(), 0, getNumFrames(), 0, round(drawRect.getWidth())));
	}
	
	ofDrawRectangle(progressRect);
	ofNoFill();
	
	ofSetLineWidth(2);
	ofRectangle outlineRect(drawRect);
	
	outlineRect.width-=4;
	outlineRect.height-=4;
	outlineRect.x+=2;
	outlineRect.y+=2;
	ofDrawRectangle(outlineRect);
	
	
	if(isSelected()) {
		ofSetColor(strokeColour);
	} else {
		ofSetColor(20,30,60);// TODO - pass in track colour
	}
	

	ofSetLineWidth(1);
	drawRect.x+=0.5;
	drawRect.y+=0.5;
	drawRect.width-=1;
	drawRect.height-=1;
	
	ofDrawRectangle(drawRect);
	
	ofSetColor(strokeColour);
	string label = ofToUpper(getName());
	if(label.size()*8 > drawRect.width-10) {
		int numchars = ((drawRect.width-10)/8)-1;
		if(numchars<0) numchars = 0;
		label.resize(numchars);
		label = label+"…";
		
	}
	ofDrawBitmapString(label, drawRect.getLeft()+4, drawRect.getCenter().y+5);
	ofPopStyle();
}


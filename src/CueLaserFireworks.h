//
//  CueLaserFireworks.h
//  BecHillLasers
//
//  Created by Seb Lee-Delisle on 13/08/2018.
//
//

#pragma once
#include "ofMain.h"
#include "CueTransformable.h"
#include "ofxLaserManager.h"
//#include "Particle.h"
#include "SimpleParticleSystem.h"

class CueLaserFireworks : public CueTransformable {
	
	public:
	CueLaserFireworks() : laser(*ofxLaser::Manager::instance()) {};
	
	virtual void update(float time, bool isPlaying);
	void addParticleBurst(float x, float y, ofColor colour); 
	//void resetParticles(); 
	
	protected:
	
	int targetZone =0; 
	ofxLaser::Manager& laser;
	float lastUpdateTime =0;
	//vector<Particle> particles;
	SimpleParticleSystem particleSystem;
	
	private:

};

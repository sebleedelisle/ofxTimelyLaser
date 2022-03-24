//
//  CueLaserFireworks.cpp
//  BecHillLasers
//
//  Created by Seb Lee-Delisle on 13/08/2018.
//
//

#include "CueLaserFireworks.h"



void CueLaserFireworks :: update(float time, bool isPlaying){
//
//	if((particles.size()<20) || ((lastUpdateTime<=startTime) && (time>=startTime))) {
//		resetParticles();
//
//	}
	
	float cueTime = time - getStart();
	float deltaTime = time-lastUpdateTime;
	
	if(particleSystem.particles.size()>0) {
		laser.setTargetZone(0);
		particleSystem.update(deltaTime);
		particleSystem.renderToLaser(laser);
	}
	
	
	//float cueTime = time-startTime;
	if(isActive(time)) {
		
		float top = 0;
		float bottom = 160;
		float left = 100;
		float right = 700;
		
		int burstcount = 10;
		
		for(int i = 0; i<burstcount; i++) {
			float starttime = ofMap(i, 0, burstcount, 0,1) * duration; // Quad::easeOut(i, 0, 1, burstcount) * duration;
			if((cueTime>starttime) && (lastUpdateTime-getStart()<starttime)) {
				ofPoint beampos(ofMap(sin(i*1.9), -1, 1, left, right),ofMap(ofNoise(10000, i*10000), 0, 1, top, bottom));
				addParticleBurst(beampos.x,beampos.y, ofColor::fromHsb(i*18,255,255));
			}
			
			
		}
		
//		float deltaTime = time-lastUpdateTime;
//
//		if(deltaTime>0) {
//			for(int i = 0; i<particles.size(); i++) {
//				Particle& p = particles[i];
//				p.update(deltaTime);
//
//			}
//
//		}
//		laser.setTargetZone(targetZone);
//		for(Particle&p : particles) {
//
//			if(!p.life.isFinished())
//				laser.drawDot(p.pos, ofColor::white, p.size);
//
//		}
//
		
	}
	
	lastUpdateTime = time;
}

void CueLaserFireworks::addParticleBurst(float x, float y, ofColor colour) {
	int numparticles = 20;
	
	for(int i =0 ; i<numparticles; i++) {
		SimpleParticle& p = *particleSystem.addParticle(x, y);
		//p.reset();
		//p.pos.set(400,400);
		p.colour = colour;
		p.fade = 0.98;
		p.vel.set(100,0);
		p.vel.rotate(ofMap(i,0,numparticles, 0,360), ofVec3f(0,0,1));
		p.drag =0.99;
		p.lifeTime = 4;
		//p.life.reset();
		p.gravity.set(0,1,0);
		//p.sizeStart = 1;
		//p.sizeEnd = 0;
		p.flickerMin = 0;
		
		
	}
	
}

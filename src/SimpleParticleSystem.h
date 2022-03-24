//
// Created by Seb Lee-Delisle on 2019-02-13.
//

#pragma once
#include "ofxLaserManager.h"
#include "ofMain.h"

class SimpleParticle : public ofPoint{
	public:
	SimpleParticle(float xpos = 0, float ypos = 0) {
		x = xpos;
		y = ypos;
		brightness = 1;

	}
	void reset(float xpos, float ypos) {
		x = xpos;
		y = ypos;
		brightness = 1;
		alive = true;
		colour = ofColor(255);
		drag = 0.93;
		gravity.set(0,10);
		elapsedTime = 0;
		updateCount = 0;
		fade = 0.85;
		flickerMin = 0;
		noiseOffset = ofRandom(100);
		lifeTime = -1;
	}

	bool update(float deltaTime) {
		if(!alive) return false;
		elapsedTime+=deltaTime;
		(ofPoint&)*this+=vel*deltaTime;
		while(updateCount<elapsedTime*updateFrequency) {
			vel*=drag;
			vel+=gravity;
			brightness*=fade;
			updateCount++;

		}
		if(brightness<0.01) alive = false;
		if(elapsedTime<0) alive = false; // if we've gone back in time to before the particle exists then delete it
		if((lifeTime>-1)&&(elapsedTime>lifeTime)) alive = false; 

		return alive;

	}
	
	float getBrightness() {
		return brightness * ofMap(ofNoise((noiseOffset+elapsedTime)*100), 0.2,0.8,flickerMin, 1, true);
		//return brightness * ofMap(ofNoise(ofGetElapsedTimef()*100), 0,1,flickerMin, 1);
		
	}


	ofColor colour;
	ofPoint vel;
	ofPoint gravity;
	
	float brightness;
	float fade;
	float drag;
	float elapsedTime = 0;
	float flickerMin;
	float noiseOffset = 0;
	int updateCount;
	int updateFrequency = 60;
	float lifeTime = -1;

	bool alive;

};

class SimpleParticleSystem {

	public :

	~SimpleParticleSystem() {
		for(SimpleParticle* particle : particles) {
			delete particle;
		}
	}

	void update(float deltatime) {

		for(SimpleParticle* particle : particles) {
			if (particle->alive) {
				particle->update(deltatime);
				if (!particle->alive) {
					spareParticles.push_back(particle);
				}
			}

		}
	}
	void renderToLaser(ofxLaser::Manager& laser, string renderProfile = OFXLASER_PROFILE_DEFAULT) {
		for(SimpleParticle* particle : particles) {
			if (particle->alive) {
				if(particle->getBrightness()>0.1) { //particle->getBrightness() << endl;
					laser.drawDot(*particle, particle->colour, particle->getBrightness());
				}
			}
		}
	}
	SimpleParticle* addParticle(ofPoint& p) {
		return addParticle(p.x, p.y);
	}
	SimpleParticle* addParticle(float x, float y) {
		SimpleParticle* p;
		if(spareParticles.size()>0) {
			p = spareParticles.back();
			spareParticles.pop_back();
		} else {
			p = new SimpleParticle();
			particles.push_back(p);
		}
		p->reset(x, y);

		return p;

	}


	vector<SimpleParticle*> particles;
	vector<SimpleParticle*> spareParticles;

};

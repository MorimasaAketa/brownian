// main.cpp
#include "ofMain.h"

#define NParticle 10000

class ofApp : public ofBaseApp{
    
public:
    void setup(){
        ofBackground(0);
        // particle initialize
        for(int i =0 ; i < NParticle; i++ ){
            ofVec2f p;
            p.set(ofGetWidth()/2,ofGetHeight()/2);
            particlePos.push_back(p);
            ofVec2f v;
            v.set(ofRandom(-3, 3), ofRandom(-3, 3));
            particleVec.push_back(v);
            
            //            particleRot.push_back(ofRandom(-0.01,0.01));
            particleRot.push_back(0.01);
        }
    }
    void update(){

    }
    void draw(){
        double salt   = ofMap(ofGetMouseX(), 0,  ofGetWidth(), 0, 0.1);
        double length = ofMap(ofGetMouseX(), 0, ofGetWidth(), 0, 5);
        ofSetColor(255);
        
        for (int i=0; i< NParticle; i++) {
            ofDrawLine(particlePos[i].x, particlePos[i].y,
                       particlePos[i].x + particleVec[i].x* length*length*2,
                       particlePos[i].y + particleVec[i].y* length*length*2);
            double radius = particlePos[i].distance(ofVec2f(ofGetWidth()/2, ofGetHeight()/2));
            double salt_with_radius = salt * radius/ofGetHeight()/2;
            
            particleVec[i].rotateRad((particleRot[i] + salt_with_radius*ofSign(particleRot[i])) * PI);
            particlePos[i].x += particleVec[i].x;
            particlePos[i].y += particleVec[i].y;

        }
    }
    // Define members here.
    vector<ofVec2f> particlePos, particleVec;
    vector<double> particleRot;

};

int main( ){
    ofSetupOpenGL(1280,720,OF_WINDOW);          // <-------- setup the GL context
    
    // this kicks off the running of my app
    // can be OF_WINDOW or OF_FULLSCREEN
    // pass in width and height too:
    ofRunApp(new ofApp());
    
}
// main.cpp
#include "ofMain.h"

#define NParticle 4096
#define HistoryMax 10000
class ofApp : public ofBaseApp{
    
    
class Particle{
        
    public:
        ofVec2f pos, vec;
        double rot;
        deque<ofVec2f> pos_history;
        
        Particle() : vec(0, 0),pos(0,0),rot(0) {
            pos_history.resize(0);
        }
        
        void move(ofVec2f next){
            while(pos_history.size() > HistoryMax){
                pos_history.pop_front();
            }
            pos_history.push_back(pos);
            pos = next;
        }
        
        ~Particle(){
            pos_history.clear();
            pos_history.shrink_to_fit();
        }
        
        
    };

    
public:
    void setup(){
        ofBackground(0);
        // particle initialize
        particles.resize(NParticle);
        for(int i =0 ; i < NParticle; i++ ){
            ofVec2f p;
            p.set(ofGetWidth()/2,ofGetHeight()/2);
            ofVec2f v;
            v.set(ofRandom(-3, 3), ofRandom(-3, 3));
            particles[i].pos = p;
            particles[i].vec = v;

            //            particleRot.push_back(ofRandom(-0.01,0.01));
            particles[i].rot = 0.01;
        }
    }
    void update(){

    }
    void draw(){
        double salt   = ofMap(ofGetMouseX(), 0,  ofGetWidth(), -0.1, 0.1);
        double length = ofMap(abs(ofGetHeight()/2-ofGetMouseY()), 0, ofGetHeight()/2, 0, 100);
        ofSetColor(255);
        
        for (int i=0; i< NParticle; i++) {

                ofDrawLine(particles[i].pos.x, particles[i].pos.y,
                           particles[i].pos.x + particles[i].vec.x * length * length *2,
                           particles[i].pos.y + particles[i].vec.y * length * length *2);
            double radius = particles[i].pos.distance(ofVec2f(ofGetWidth()/2, ofGetHeight()/2));
            double salt_with_radius = salt * radius/ofGetHeight()*4;
            particles[i].vec.rotateRad((particles[i].rot + salt_with_radius*ofSign(particles[i].rot)) * PI);
            particles[i].move(particles[i].pos + particles[i].vec);
            
            /*            ofDrawLine(particlePos[i].x, particlePos[i].y,
                       particlePos[i].x + particleVec[i].x* length*length*2,
                       particlePos[i].y + particleVec[i].y* length*length*2);
            double radius = particlePos[i].distance(ofVec2f(ofGetWidth()/2, ofGetHeight()/2));
            double salt_with_radius = salt * radius/ofGetHeight()*4;
            
            particleVec[i].rotateRad((particleRot[i] + salt_with_radius*ofSign(particleRot[i])) * PI);
            particlePos[i].x += particleVec[i].x;
            particlePos[i].y += particleVec[i].y;
*/
        }
    }
    // Define members here.
    //    vector<ofVec2f> particlePos, particleVec;
    vector<Particle> particles;
    vector<double> particleRot;

};

int main( ){
    ofSetupOpenGL(1280,720,OF_WINDOW);          // <-------- setup the GL context
    
    // this kicks off the running of my app
    // can be OF_WINDOW or OF_FULLSCREEN
    // pass in width and height too:
    ofRunApp(new ofApp());
    
}
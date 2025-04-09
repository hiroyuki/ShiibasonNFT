//
//  ArtnetManager.h
//  Shiibason-LED
//
//  Created by 堀宏行 on 2025/04/08.
//
#include "ofxArtnet.h"
#include "Light.h"

class ArtnetManager {
public:
    
    ofPixels flex1Data, flex2Data, blastData;
    float rotateValue = 0;
    
    void setup(){
        sender.setup("10.0.0.10");
        datas.push_back(make_shared<ofFbo>());
        datas.push_back(make_shared<ofFbo>());
        datas[Light::FLEX].get()->allocate(200, 1, GL_RGB);
        datas[Light::BLAST].get()->allocate(4, 1, GL_RGB);
    }
    
    void clearColor(Light::LED_TYPE type, ofColor color = ofColor::black){
        datas[type].get()->begin();
        ofSetColor(color);
        ofDrawRectangle(0, 0, datas[type].get()->getWidth(), 1);
        datas[type].get()->end();
        
    }
    
    void setColor(int currentScene, int nextScene, float progress, float rotate, Light light){
        if (light.sceneID == currentScene || light.sceneID == nextScene){
            ofPushStyle();
            ofEnableBlendMode(OF_BLENDMODE_ADD);
            datas[light.type].get()->begin();
            int r = light.sceneID == currentScene ? light.color.r * (1 - progress) : light.color.r * progress;
            int g = light.sceneID == currentScene ? light.color.g * (1 - progress) : light.color.g * progress;
            int b = light.sceneID == currentScene ? light.color.b * (1 - progress) : light.color.b * progress;
            rotateValue = rotate == 0 ? 0 : rotateValue + rotate;
//            ofLog()<<r << " " << g << " " << b;
            ofSetColor(r,g,b);
            int from = int(light.from + rotateValue) % (int)datas[light.type].get()->getWidth();
            ofDrawRectangle(from, 0, light.width, 1);
            if(from + light.width > (int)datas[light.type].get()->getWidth()) {
                ofDrawRectangle(0, 0, from + light.width - (int)datas[light.type].get()->getWidth(), 1);
            }
            datas[light.type].get()->end();
            ofPopStyle();
        }
    }
    
    void draw(){
        datas[Light::FLEX].get()->draw(10,10, 600, 30);
        datas[Light::BLAST].get()->draw(10,40, 600, 30);
    }
    
    void sendColor(){
        
        
        ofFbo flex1, flex2;
        {
            flex1.allocate(100, 1, GL_RGB);
            flex1.begin();
            datas[Light::FLEX].get()->draw(0,0);
            flex1.end();
            flex1.readToPixels(flex1Data);
            ofxArtnetMessage m = flex1Data;
            m.setUniverse15(0);
            sender.sendArtnet(m);
        }
        
        {
            flex2.allocate(100, 1, GL_RGB);
            flex2.begin();
            datas[Light::FLEX].get()->draw(-100,0);
            flex2.end();
            flex2.readToPixels(flex1Data);
            ofxArtnetMessage m = flex1Data;
            m.setUniverse15(1);
            sender.sendArtnet(m);
        }
        
        {
            datas[Light::BLAST].get()->readToPixels(blastData);
            ofxArtnetMessage m = blastData;
            m.setUniverse15(2);
            sender.sendArtnet(m);
        }
    }
    
private:
    ofxArtnetSender sender;
    vector<ofPtr<ofFbo>> datas;
    
};

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
    
    ofPixels data;
    
    void setup(){
        sender.setup("10.0.0.10");
        datas.push_back(make_shared<ofFbo>());
        datas.push_back(make_shared<ofFbo>());
        datas.push_back(make_shared<ofFbo>());
        datas[Light::FLEX1].get()->allocate(100, 1, GL_RGB);
        datas[Light::FLEX2].get()->allocate(100, 1, GL_RGB);
        datas[Light::BLAST].get()->allocate(4, 1, GL_RGB);
    }
    
    void clearColor(Light::LED_TYPE type, ofColor color = ofColor::black){
        datas[type].get()->begin();
        ofSetColor(color);
        ofDrawRectangle(0, 0, datas[type].get()->getWidth(), 1);
        datas[type].get()->end();
        
    }
    
    void setColor(Light light){
        datas[light.type].get()->begin();
        ofSetColor(light.color);
        ofDrawRectangle(light.from, 0, light.to, 1);
        datas[light.type].get()->end();
    }
    
    void sendColor(){
        int univerese = 0;
        for(auto fbo : datas) {
            fbo.get()->readToPixels(data);
            ofxArtnetMessage m = data;
            m.setUniverse15(univerese);
            sender.sendArtnet(m);
            univerese++;
        }
    }
    
private:
    ofxArtnetSender sender;
    vector<ofPtr<ofFbo>> datas;
    
};

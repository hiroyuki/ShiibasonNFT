#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    preview = true;
    artnet.setup();
    ofSetFrameRate(44);
    recv.setup(9999);
    artnet.clearColor(Light::FLEX1, ofColor::black);
    artnet.clearColor(Light::FLEX2, ofColor::black);
    artnet.clearColor(Light::BLAST, ofColor::black);
    if(!xml.load("colors.xml")) {
        ofLog() << "failed to load xml";
        xml.appendChild("data");
    } else {
        ofXml data = xml.getChild("data");
        for(auto lightdata : data.getChildren("light")) {
            ofLog() << "find child";
            lights.push_back(Light(lightdata.getChild("type").getIntValue(),
                                   lightdata.getChild("from").getIntValue(),
                                   lightdata.getChild("to").getIntValue(),
                                   lightdata.getChild("colorr").getIntValue(),
                                   lightdata.getChild("colorg").getIntValue(),
                                   lightdata.getChild("colorb").getIntValue()));
            ofLog() << lights.back().toString();
            
        }
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    while(recv.hasWaitingMessages()) {
    
        ofxOscMessage m;
        recv.getNextMessage(m);
        ofLog() << m.getAddress();
        if (m.getAddress() == "/set_color") {
            tmp = Light(m.getArgAsInt32(0),
                                   m.getArgAsInt32(1),
                                   m.getArgAsInt32(2),
                                   m.getArgAsInt32(3),
                                   m.getArgAsInt32(4),
                                   m.getArgAsInt32(5)
                                   );
        }
        if ( m.getAddress() == "/add_color") {
            ofLog() << tmp.toString();
            lights.push_back(tmp);
            ofXml xmllight = xml.getChild("data").appendChild("light");
            xmllight.appendChild("type").set(tmp.type);
            xmllight.appendChild("from").set(tmp.from);
            xmllight.appendChild("to").set(tmp.to);
            xmllight.appendChild("colorr").set((int)tmp.color.r);
            xmllight.appendChild("colorg").set((int)tmp.color.g);
            xmllight.appendChild("colorb").set((int)tmp.color.b);
            xml.save("colors.xml");
            
        }
        
        if ( m.getAddress() == "/preview") {
            preview = m.getArgAsBool(0);
        }
    }
    artnet.clearColor(Light::FLEX1, ofColor::black);
    artnet.clearColor(Light::FLEX2, ofColor::black);
    artnet.clearColor(Light::BLAST, ofColor::black);
    
    if(preview) {
        artnet.setColor(tmp);
    }
    
    for (auto color : lights) {
        artnet.setColor(color);
    }
    artnet.sendColor();
}

//--------------------------------------------------------------
void ofApp::draw(){

}

//--------------------------------------------------------------
void ofApp::exit(){
    artnet.clearColor(Light::FLEX1, ofColor::black);
    artnet.clearColor(Light::FLEX2, ofColor::black);
    artnet.clearColor(Light::BLAST, ofColor::black);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == '1'){
        artnet.clearColor(Light::FLEX1, ofColor::black);
    }
    if(key == '2'){
        artnet.clearColor(Light::FLEX2, ofColor::black);
    }
    
    if(key == '3'){
        artnet.clearColor(Light::BLAST, ofColor::black);
    }
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

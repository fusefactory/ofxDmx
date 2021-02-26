#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
//    ofSetLogLevel(OF_LOG_VERBOSE);
    ofSetWindowTitle("DMX channels controller");
    
    ofxXmlSettings settings;
    settings.loadFile("dmx.xml");
    
    port = settings.getValue("port", "");
    modules = settings.getValue("modules", 1);
    channelsPerModule = settings.getValue("channelsPerModule", 10);
        
    gui.setup();
    gui.setPosition(4, 4);
    gui.setName("dmx");
    gui.add(save.set("save", false));
    gui.add(load.set("load", false));
    
    for(int m = 1; m <= modules; m++){
        for(int c = 1; c <= channelsPerModule; c++){
            int index = (m - 1) * channelsPerModule + (c - 1);
            string name = getChannelName(m, c);
            
            ofxIntSlider *slider = new ofxIntSlider();
            gui.add(slider->setup(name, 0, 0, 255));
        }
    }
    
    gui.setSize(ofGetWidth() - 20 , gui.getHeight());
    
    dmx.connect(port, modules * channelsPerModule);
    dmx.update(true); // black on startup
}

string ofApp::getChannelName(int module, int channel){
    string name = "m_" + ofToString(module) + "_c_" + ofToString(channel);
    return name;
}

void ofApp::exit() {
    dmx.clear();
    dmx.update(true); // black on shutdown
}

//--------------------------------------------------------------
void ofApp::update(){
    if(save) {
        save = false;
        gui.saveToFile("settings.xml");
    }
    if(load) {
        if(ofFile::doesFileExist(ofToDataPath("settings.xml"))) {
            gui.loadFromFile("settings.xml");
        }
        load = false;
    }
    
    for(int m = 1; m <= modules; m++){
        for(int c = 1; c <= channelsPerModule; c++){
            string name = getChannelName(m, c);
            ofxIntSlider &slider = gui.getIntSlider(name);
            int channel = (m - 1) * channelsPerModule + c;
            
            dmx.setLevel(channel, slider);
        }
    }
    
    if(dmx.isConnected()) {
        dmx.update();
    } else {
        ofSetColor(255);
        ofDrawBitmapString("Could not connect to port " + ofToString(port), 250,20);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);

    gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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

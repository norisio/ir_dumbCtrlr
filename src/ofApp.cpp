#include "ofApp.h"

const std::array<std::string, 4>
robot{
  "mrpmpi1.local",
  "mrpmpi2.local",
  "mrpmpi3.local",
  "mrpmpi4.local"
};
const int PORT_ROBOT=8000;

//--------------------------------------------------------------
void ofApp::setup(){
  ofSetFrameRate(60);
  up=down=right=left=false;
  
}

//--------------------------------------------------------------
void ofApp::update(){
  if(isSenderReady){
    ofxOscMessage m;
    m.setAddress("/operator/operation");
    m.addInt32Arg(getDrc());
    
    sndr->sendMessage(m);
    
    static const bool withPermission = true;
    if(withPermission){
      ofxOscMessage x;
      x.setAddress("/main/toRobot");
      x.addInt32Arg(0);
      x.addDoubleArg(0.f);
      x.addDoubleArg(0.f);
      x.addDoubleArg(0.f);
      for(int i=0; i<9; ++i){
        x.addBoolArg(true);
      }
      sndr->sendMessage(x);
    }
  }
}

//--------------------------------------------------------------
void ofApp::draw(){
  static int width=ofGetWidth(), height=ofGetHeight();
  
  std::string str;
  if(isSenderReady){
    ofSetColor(ofColor::black);
    str=robot[senderRobInd]+":"+ofToString(PORT_ROBOT);
  }else{
    str="Press 1-4.";
  }
  ofDrawBitmapString(str, 0, 30);
  
  ofPushMatrix();
  ofTranslate(width/2, height/2);
  ofSetColor(ofColor::red);
  if(!(up||down||left||right)){
    ofDrawCircle(0, 0, 30);
  }else{
    ofRotate(getRot());
    ofSetLineWidth(10);
    ofDrawLine(0, 0, 0, -100);
    ofDrawCircle(0, -110, 20);
  }
  ofPopMatrix();
}

int32_t ofApp::getDrc(){
  if(up){
    if(right)return 2;
    else if(left) return 8;
    else return 1;
  }else if(down){
    if(right)return 4;
    else if(left)return 6;
    else return 5;
  }else if(right){
    return 3;
  }else if(left){
    return 7;
  }
  return 0;
}
float ofApp::getRot(){
  if(up){
    if(right)return 45;
    else if(left) return -45;
    else return 0;
  }else if(down){
    if(right)return 135;
    else if(left)return -135;
    else return 180;
  }else if(right){
    return 90;
  }else if(left){
    return -90;
  }
  return 0;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
  switch(key){
    case OF_KEY_UP:
      up=true;
      break;
    case OF_KEY_DOWN:
      down=true;
      break;
    case OF_KEY_LEFT:
      left=true;
      break;
    case OF_KEY_RIGHT:
      right=true;
      break;
    case OF_KEY_BACKSPACE:
      if(isSenderReady)deleteSender();
      break;
    case '1':
    case '2':
    case '3':
    case '4':
      if(!isSenderReady)setupSender(key);
      break;
  }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
  switch(key){
    case OF_KEY_UP:
      up=false;
      break;
    case OF_KEY_DOWN:
      down=false;
      break;
    case OF_KEY_LEFT:
      left=false;
      break;
    case OF_KEY_RIGHT:
      right=false;
      break;
  }
}

void ofApp::setupSender(int key){
  if(!isSenderReady){
    sndr = new ofxOscSender;
    int i = key - '1';
    senderRobInd = i;
    sndr->setup(robot[i], PORT_ROBOT);
    isSenderReady = true;
  }
}

void ofApp::deleteSender(){
  if(isSenderReady){
    delete sndr;
    isSenderReady = false;
  }
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

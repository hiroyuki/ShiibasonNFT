//
//  Light.h
//  Shiibason-LED
//
//  Created by 堀宏行 on 2025/04/08.
//

class Light{
public:
    Light(){
        type = (LED_TYPE)0;
        from = 0;
        width = 0;
        color.r = 0;
        color.g = 0;
        color.b = 0;
    }
    Light(int _sceneID, int _type, int _from, int _width, int r, int g, int b){
        sceneID = _sceneID;
        type = (LED_TYPE)_type;
        from = _from;
        width = _width;
        color.r = r;
        color.g = g;
        color.b = b;
    }
    enum LED_TYPE{
        FLEX=0, BLAST=1
    } type;
    int from;
    int width;
    ofColor color;
    unsigned int sceneID;
    
    string toString() {
        string str  = type == 0 ? "FLEX1 " : type == 1 ? "FLEX2 " : "BLAST ";
        str += " " + ofToString(from);
        str += " " + ofToString(width);
        str += " " + ofToString((int)color.r);
        str += " " + ofToString((int)color.g);
        str += " " + ofToString((int)color.b);
        return str;
    }
//    float blightness;
//    float saturation;
};

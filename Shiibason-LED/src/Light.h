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
        to = 0;
        color.r = 0;
        color.g = 0;
        color.b = 0;
    }
    Light(int _type, int _from, int _to, int r, int g, int b){
        type = (LED_TYPE)_type;
        from = _from;
        to = _to;
        color.r = r;
        color.g = g;
        color.b = b;
    }
    enum LED_TYPE{
        FLEX1=0, FLEX2=1, BLAST=2
    } type;
    int from;
    int to;
    ofColor color;
    
    string toString() {
        string str  = type == 0 ? "FLEX1 " : type == 1 ? "FLEX2 " : "BLAST ";
        str += " " + ofToString(from);
        str += " " + ofToString(to);
        str += " " + ofToString((int)color.r);
        str += " " + ofToString((int)color.g);
        str += " " + ofToString((int)color.b);
        return str;
    }
//    float blightness;
//    float saturation;
};

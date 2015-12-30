//
//  PretzelShaders.h
//
//  Created by Charlie Whitney on 12/19/15.
//
//

#pragma once

namespace pretzel
{
    
    class PretzelShaders
    {
    public:
        std::string hueFrag, hueVert;
        
        
        PretzelShaders(){
            hueVert =  "#version 150\n"
            "uniform mat4 ciModelViewProjection;\n"
            "in vec4 	ciPosition;\n"
            "in vec2 	ciTexCoord0;\n"
            "out highp vec2 TexCoord;\n"
            "\n"
            "void main(void)\n"
            "{\n"
            "	gl_Position = ciModelViewProjection * ciPosition;\n"
            "	TexCoord = ciTexCoord0;\n"
            "}\n";
            
            hueFrag = "#version 150\n"
            "uniform vec4 uPickedCol;\n"
            "in vec2 TexCoord;\n"
            "out vec4 oColor;\n"
            "\n"
            "void main(void)\n"
            "{\n"
            "	vec4 grayUD = mix( vec4(0,0,0,1), vec4(1,1,1,1), TexCoord.t );\n"
            "	vec4 finalCol = mix( grayUD, uPickedCol, TexCoord.s);\n"
            "	oColor = min( grayUD, finalCol );\n"
            "}";
        }
        
        private:
        
        
    };
}

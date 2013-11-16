

#ifndef HelloWorld_GLProgramWithMyUnifos_h
#define HelloWorld_GLProgramWithMyUnifos_h
#include "cocos2d.h"

#include<iostream>
#include<map>
using namespace std;

#include "indexVBO.h"
using namespace cocos2d;
//if program1 and program2 have a uniform variable with the same name, the two variable's uniform ID (GLint) may be different. 
//so safe way is let each shader program hold his own uniform IDs.
class CGLProgramWithMyUnifos{
	CCGLProgram*program;
public:
	map<string,GLint> myUnifoMap;
    CGLProgramWithMyUnifos(){
		program=NULL;
	}
	virtual ~CGLProgramWithMyUnifos(){
		program->release();
	}
    void setProgram(CCGLProgram*_program){
        if(program){
            program->release();
        }
        program=_program;
        program->retain();
    }
    CCGLProgram*getProgram(){
        return program;
    }

};
  



#endif

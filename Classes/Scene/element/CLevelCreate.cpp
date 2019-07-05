#include<CLevelCreate.h>

USING_NS_CC;

CLevelCreate::~CLevelCreate(){}
CLevelCreate::CLevelCreate(b2World* _b2W, int L){
    //圖片\
    _b2World = _b2W;
    char level[9];
    char name[4];
    sprintf(level, "Level_%d", L);
    int num = rand()%2;
    sprintf(name, "%d", num);
    for(int i =0; i<6; i++){
        _DownGround[i]= CSLoader::createNode("Obstacle.csb")->getChildByName("Level_0")->getChildByName("0");
        _DownGround[i]->setPosition(210+425*i,235);
        this->addChild(_DownGround[i]);
    }
}
void CLevelCreate::dostep(){
    for(int i =0; i<6; i++){
        if(_DownGround[i]->getPosition().x < (-215.0f)){
            if(i==0)
                _DownGround[i]->setPosition(_DownGround[5]->getPosition().x+425,235);
            else
                _DownGround[i]->setPosition(_DownGround[i-1]->getPosition().x+425,235);
        }
        _DownGround[i]->setPosition(_DownGround[i]->getPosition().x-20,235);
    }
}

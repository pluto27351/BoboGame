#include "CAnsCreater.h"

CAnsCreater::CAnsCreater(int uni, int queNo, int number) {
    char name[14];
    sprintf(name,"ans/u%d_%d.csb",uni, queNo);
    auto answer = CSLoader::createNode(name);
    Input_ans(*answer, number);
    
}
void CAnsCreater::Input_ans(Node &Q, int number) {
    char Input[5];
    char fn[3];
    int inputData,data;
    
    Node *Output_f = (Node *)Q.getChildByName("F_1");
    Text *ntor = (Text *)Output_f->getChildByName("ntor");
    
    
    _answer[0] = ntor->getTag();
    _answer[1] = Output_f->getTag();
    _answer[2] = 0;
    
    if(_answer[0] != -1){
        sprintf(Input, "%d", number);
        _answer[2] = std::atoi(Numerator(ntor->getString().c_str(), Input));
    }
    else {
        _answer[0] = number / _answer[1];
        _answer[2] = number % _answer[1];
    }
    
    if(_answer[1] == 0)_answer[1] = number;
    else if(_answer[2] == 0){_answer[1] = 0;}
    
    char n[4],d[4],f[4];
    sprintf(n, "%d", _answer[2]);
    sprintf(d, "%d", _answer[1]);
    sprintf(f, "%d", _answer[0]);
    CCLOG("ans = %d,%d,%d",_answer[0],_answer[1],_answer[2]);
    
//    auto ans =Set_CAnsCreater(n,d,f);
//    ans->setPosition(Vec2(40,0));
//    Output_f->addChild(ans);
//
//    Output_f->removeChildByName("ntor");
    
}

CAnsCreater::CAnsCreater(int uni, int queNo, int number,int c,int b) {
    Node * answer;
    
    char name[14];
    sprintf(name,"ans/u%d_%d.csb",uni, queNo);
    answer = CSLoader::createNode(name);

    Node *Output_f = (Node *)answer->getChildByName("F_1");
    Text *ntor = (Text *)Output_f->getChildByName("ntor");
    char bc[5],aa[5];
    sprintf(bc,"%d",b*c);
    sprintf(aa,"%d",number);
    _answer[0] = 0;
    _answer[1] = number;
    _answer[2] = b*c;
    CCLOG("ans = %d,%d,%d",_answer[0],_answer[1],_answer[2]);
//    Output_f->addChild(Set_CAnsCreater(bc,aa,""));
//    Output_f->removeChildByName("ntor");
    
}

CAnsCreater::CAnsCreater(int number,int q){
    float xPos = CSLoader::createNode("Ani/line.csb")->getChildByName("2")->getPositionX();
    float yPos = -150;
    float move = xPos/number;
    Node *fraction;
    int up = -1;
    xPos *= -1;
    
    for(int i=0;i<(2*number);i++){
        Sprite *line;
        char n[4],d[4],f[4];
        sprintf(n, "%d", i+1);
        sprintf(d, "%d", number);
        sprintf(f, "%d", 0);
        if((i+1) % number == 0){ up =1; }
        
        if( i == q ){
            _answer[0] = 0;
            _answer[1] =number;
            _answer[2] = i+1;
//            fraction = Set_CAnsCreater(n,d,f);
//            fraction->setPosition(Vec2(xPos+move*(i+1),yPos + 100*up));
        }
        
        up*=-1;
        
    }
    CCLOG("ans = %d,%d,%d",_answer[0],_answer[1],_answer[2]);
}

void CAnsCreater::queCreater(int uni, int queNo, int number) {
    char name[14];
    sprintf(name, "Que/q%d_%d.csb", uni, queNo);
    auto queNode = CSLoader::createNode(name);
    Input_que(*queNode, number);
    
    addChild(queNode);
}


void CAnsCreater::queCreater(int uni, int queNo, int number,int c,int b) {
    char name[14];
    sprintf(name, "que/q%d_%d.csb", uni, queNo);
    auto Q = CSLoader::createNode(name);
    int inputData = Q->getChildByName("bg")->getTag();
    char Input[5];
    
    Text *Output_n = (Text *)Q->getChildByName("MN_1");
    sprintf(Input, "%d", c);
    Output_n->setString(Input);
    Output_n->setTextColor(_textColor4B);
    
    int data = inputData / 100;
    for (int i = 0; i < data; i++) {
        sprintf(Input, "C_%d", i + 1);
        Text* Output_c = (Text*)Q->getChildByName(Input);
        sprintf(Input, "%d", number);
        int k = std::atoi(Numerator(Output_c->getString().c_str(), Input));
        Output_c->setString(chiness[k - 2]);
        Output_c->setTextColor(_textColor4B);
    }
    inputData = inputData % 100;
    
    data = inputData / 10;
    for (int i = 0; i < data; i++) {
        sprintf(Input, "N_%d", i + 1);
        Text *Output_n = (Text *)Q->getChildByName(Input);
        sprintf(Input, "%d", number);
        Output_n->setString(Input);
        Output_n->setTextColor(_textColor4B);
    }
    inputData = inputData % 10;
    
    data = inputData;
    for (int i = 0; i < data; i++) {
        sprintf(Input, "F_%d", i + 1);
        Node *Output_f = (Node *)Q->getChildByName(Input);
        Text *ntor = (Text *)Output_f->getChildByName("ntor");
        if(b == -1){
            sprintf(Input, "%d", number);
            b = std::atoi(Numerator(ntor->getString().c_str(), Input));
        }
        char bb[5],aa[5];
        sprintf(bb,"%d",b);
        sprintf(aa,"%d",number);

        Output_f->addChild(Set_CAnsCreater(bb,aa,""));
        Output_f->removeChildByName("ntor");
    }
    
    addChild(Q);
}

void CAnsCreater::Input_que(Node &Q, int number) {
    char Input[5];
    char fn[3];
    int inputData,data;
    auto bg = (Node *)Q.getChildByName("bg");

    inputData = bg->getTag();
    data = inputData / 100;
    for (int i = 0; i < data; i++) {
        sprintf(Input, "C_%d", i + 1);
        Text* Output_c = (Text*)Q.getChildByName(Input);
        sprintf(Input, "%d", number);
        int k = std::atoi(Numerator(Output_c->getString().c_str(), Input));
        Output_c->setString(chiness[k - 2]);
        Output_c->setTextColor(_textColor4B);
    }
    inputData = inputData % 100;
    
    
    data = inputData / 10;
    for (int i = 0; i < data; i++) {
        sprintf(Input, "N_%d", i + 1);
        Text *Output_n = (Text *)Q.getChildByName(Input);
        sprintf(Input, "%d", number);
        Output_n->setString(Input);
        Output_n->setTextColor(_textColor4B);
    }
    inputData = inputData % 10;
    
    data = inputData;
    for (int i = 0; i < data; i++) {
        sprintf(Input, "F_%d", i + 1);
        Node *Output_f = (Node *)Q.getChildByName(Input);
        Text *ntor = (Text *)Output_f->getChildByName("ntor");
        
        int outN[3] = {ntor->getTag(),Output_f->getTag(),0};
        
        if(outN[1] == 0)outN[1] = number;
        
        if(outN[0] != -1){
            sprintf(Input, "%d", number);
            outN[2] = std::atoi(Numerator(ntor->getString().c_str(), Input));
        }
        else {
            outN[0] = number / outN[1];
            outN[2] = number % outN[1];
        }
        char n[4],d[4],f[4];
        sprintf(n, "%d", outN[2]);
        sprintf(d, "%d", outN[1]);
        sprintf(f, "%d", outN[0]);
        
        Output_f->addChild(Set_CAnsCreater(n,d,f));
        
        Output_f->removeChildByName("ntor");
    }
    
}

void CAnsCreater::queLineCreater(int number,int q){
    auto line = CSLoader::createNode("Ani/line.csb");
    float xPos = line->getChildByName("2")->getPositionX();
    float yPos = -150;
    line -> setPosition(Vec2(0,yPos));
    addChild(line);
    
    float move = xPos/number;
    xPos *= -1;
    Node *fraction;
    int up = -1;
    for(int i=0;i<(2*number);i++){
        Sprite *line;
        char n[4],d[4],f[4];
        sprintf(n, "%d", i+1);
        sprintf(d, "%d", number);
        sprintf(f, "%d", 0);
        if((i+1) % number == 0){
            up =1;
        }
        else {
            line = Sprite::createWithSpriteFrameName("length_2.png");
            line->setPosition(Vec2(xPos+move*(i+1),yPos));
            addChild(line);
        }
        if( i != q ){  //if( i != q[0] && i != q[1] && i != q[2] ){
            fraction = Set_CAnsCreater(n,d,f);
            fraction->setPosition(Vec2(xPos+move*(i+1),yPos + 100*up));
            addChild(fraction);
        }else {
            auto box = (Sprite *)Sprite::createWithSpriteFrameName("line_box.png");
            box->setPosition(Vec2(xPos+move*(i+1),yPos + 100*up));
            addChild(box);
        }
        
        up*=-1;
        
    }
}


bool CAnsCreater::CheckAnswer(Vec3 a) {
    if (a.x != _answer[0] || a.y != _answer[1] || a.z != _answer[2])return false;
    return true;
}

char * CAnsCreater::Numerator(const char *c, const char *number) {
    char *ntor = (char*)c;
    bool count = false; //判斷是否要運算(+,-,*,/)
    bool z = false;
    if (number[1] != NULL)z = true;        //判斷幾位數 2位以上
    if (c[0] == 'd') {  //如果是改變分子 把d移掉全完前
        for (int i = 0; c[i] != NULL; i++)
            ntor[i] = c[i + 1];
    }
    
    //型成字串的過程
    for (int i = 0; c[i] != NULL; i++) {
        if (c[i] == 'F') {               //F分母的數
            if (z == true) {
                ntor = new char[strlen(c) + 1];
                ntor = (char*)c;
                for (int i = strlen(ntor) - 1; i >= 0; i--) //將字串往後推
                    ntor[i + 1] = c[i];
                ntor[i] = number[0]; ntor[i + 1] = number[1];
            }
            else {
                ntor[i] = number[0];
            }
        }
        else if (c[i] == '=') { //出現'＝'進運算
            count = true;
        }
    }
    
    //加減乘除運算
    if (count == true) {
        int a = 0, b = 0;
        for (int i = 0; ntor[i] != NULL; i++)
            switch (c[i]) {
                case '+':
                    for (int x = i - 1, y = 0; x > 0; x--, y++)//x數字 y個位數或十位數
                        a += (ntor[x] - '0')*pow(10, y);
                    for (int x = strlen(c) - 1, y = 0; x > i; x--, y++)
                        b += (ntor[x] - '0')*pow(10, y);
                    sprintf(ntor, "%d", a + b);
                    break;
                case '-':
                    for (int x = i - 1, y = 0; x > 0; x--, y++)
                        a += (ntor[x] - '0')*pow(10, y);
                    for (int x = strlen(c) - 1, y = 0; x > i; x--, y++)
                        b += (ntor[x] - '0')*pow(10, y);
                    sprintf(ntor, "%d", a - b);
                    break;
                case 'x': //a * b
                    for (int x = i - 1, y = 0; x > 0; x--, y++)
                        a += (ntor[x] - '0')*pow(10, y);
                    for (int x = strlen(c) - 1, y = 0; x > i; x--, y++)
                        b += (ntor[x] - '0')*pow(10, y);
                    sprintf(ntor, "%d", a*b);
                    break;
                case '%': //a * b
                    for (int x = i - 1, y = 0; x > 0; x--, y++)
                        a += (ntor[x] - '0')*pow(10, y);
                    for (int x = strlen(c) - 1, y = 0; x > i; x--, y++)
                        b += (ntor[x] - '0')*pow(10, y);
                    sprintf(ntor, "%d", a%b);
                    break;
            }
    }
    return(ntor);
}

Node * CAnsCreater::Set_CAnsCreater(const char *numerator, const char *denominator, const char *front) {
    float scale = 0.5f;
    for (int i = 0; numerator[i] != NULL; scale += 0.5f, i++);
    auto fn = (Node *)Node::create(); //最後的回傳-分數的形狀
    Sprite *bar;
    auto Ntor = cocos2d::ui::Text::create(); //分子
    auto Dtor = cocos2d::ui::Text::create(); //分母
    
    bar = (Sprite *)Sprite::create("Img/bar.png");
    bar->setScale(6 * scale, 5);
    bar->setColor(Color3B::BLACK);
    
    Ntor->setFontSize(50);
    Ntor->setString(numerator);
    Ntor->setPosition(Point(0, 30));
    Ntor->setColor(Color3B::BLACK);
    
    Dtor->setFontSize(50);
    Dtor->setString(denominator);
    Dtor->setPosition(Point(0, -30));
    Dtor->setColor(Color3B::BLACK);
    
    fn->addChild(bar);
    fn->addChild(Ntor);
    fn->addChild(Dtor);
    
    for (int i = 0; front[i] != NULL && front[i] != '0'; i++) {
        auto Ftor = cocos2d::ui::Text::create();
        Ftor->setFontSize(50);
        Ftor->setString(front);
        Ftor->setPosition(Point(-40, 0));
        Ftor->setColor(Color3B::BLACK);
        fn->addChild(Ftor);
    }
    return(fn);
}

cocos2d::Node * CAnsCreater::CAnsCreaterOperation(int n) {
    char c_n[5];
    sprintf(c_n, "%d", n);
    auto plus = new cocos2d::ui::Text*[n - 1]; //加
    auto equal = cocos2d::ui::Text::create(); //等於
    
    auto fn = (Node *)Node::create(); //最後的回傳-運算式的形狀
    
    //分數生成
    Node ** all_f = new Node*[n + 1];
    for (int i = 0; i < n + 1; i++) {
        if (i < n)
            all_f[i] = Set_CAnsCreater("1", c_n, "0");
        else
            all_f[i] = Set_CAnsCreater(c_n, c_n, "0");
    }
    
    //排位子
    for (int i = 0; i < 2 * n + 1; i++) {
        if (i % 2) {
            if (i == 2 * n - 1) {
                equal = cocos2d::ui::Text::create();
                equal->setString("=");
                equal->setFontSize(50);
                equal->setColor(Color3B::BLACK);
                equal->setPosition(Point(50 * i, 0));
            }
            else {
                plus[(i - 1) / 2] = cocos2d::ui::Text::create();
                plus[(i - 1) / 2]->setString("+");
                plus[(i - 1) / 2]->setFontSize(50);
                plus[(i - 1) / 2]->setColor(Color3B::BLACK);
                plus[(i - 1) / 2]->setPosition(Point(50 * i, 0));
            }
        }
        else {
            all_f[i / 2]->setPosition(50 * i, 0);
        }
    }
    
    for (int i = 0; i < n + 1; i++)
        fn->addChild(all_f[i]);
    for (int i = 0; i < n - 1; i++)
        fn->addChild(plus[i]);
    fn->addChild(equal);
    
    return(fn);
}

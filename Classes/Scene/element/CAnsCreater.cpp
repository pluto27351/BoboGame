#include "CAnsCreater.h"

void CAnsCreater::queCreater(int uni, int queNo, int number) {
	Node * answer;

	char name[14];
	sprintf(name, "que/q%d_%d.csb", uni, queNo);
	auto queNode = CSLoader::createNode(name);
	Input_que(*queNode, number);
    addChild(queNode);
    
    sprintf(name,"ans/u%d_%d.csb",uni, queNo);
    answer = CSLoader::createNode(name);
    Input_ans(*answer, number);

}

void CAnsCreater::queCreater(int uni, int queNo, int number,int c,int b) {

    char name[14];
    sprintf(name, "que/q%d_%d.csb", uni, queNo);
    auto queNode = CSLoader::createNode(name);
    Input_que(*queNode, number,c,b);
    addChild(queNode);
    
    Input_ans(number,c,b);
    
}

void CAnsCreater::Input_que(Node &Q, int number) {
	char Input[5];
	char fn[3];
	int inputData, data;
	auto bg = (Node *)Q.getChildByName("bg");


	inputData = bg->getTag();
	data = inputData / 100;
	for (int i = 0; i < data; i++) {
		sprintf(Input, "C_%d", i + 1);
		Text* Output_c = (Text*)Q.getChildByName(Input);
		Output_c->setString(chiness[number - 2]);
	}
	inputData = inputData % 100;


	data = inputData / 10;
	for (int i = 0; i < data; i++) {
		sprintf(Input, "N_%d", i + 1);
		Text *Output_n = (Text *)Q.getChildByName(Input);
		sprintf(Input, "%d", number);
		Output_n->setString(Input);
	}
	inputData = inputData % 10;


	data = inputData;
	for (int i = 0; i < data; i++) {
		sprintf(Input, "F_%d", i + 1);
		Node *Output_f = (Node *)Q.getChildByName(Input);
		Text *ntor = (Text *)Output_f->getChildByName("ntor");
        
        int outNumber[3] = {ntor->getTag(),Output_f->getTag(),0};
        if(outNumber[1] == 0)outNumber[1] = number;
        
        if(outNumber[0] != -1){
            sprintf(Input, "%d", number);
            outNumber[2] = std::atoi(Numerator(ntor->getString().c_str(), Input));
        }
        else {
            outNumber[0] = number / outNumber[1];
            outNumber[2] = number % outNumber[1];
        }
        char n[4],d[4],f[4];
        sprintf(n, "%d", outNumber[2]);
        sprintf(d, "%d", outNumber[1]);
        sprintf(f, "%d", outNumber[0]);
        
        Output_f->addChild(Set_CAnsCreater(n,d,f));
        
        Output_f->removeChildByName("ntor");
	}

}


void CAnsCreater::Input_que(Node &Q, int number,int c,int b) {
    char Input[5];
    char fn[3];
    
    Text *Output_n = (Text *)Q.getChildByName("N_1");
    sprintf(Input, "%d", c);
    Output_n->setString(Input);
   // Output_n->setTextColor(_textColor4B);
    
    Node *Output_f = (Node *)Q.getChildByName("F_1");
    Text *ntor = (Text *)Output_f->getChildByName("ntor");
    char bb[5],aa[5];
    sprintf(bb,"%d",b);
    sprintf(aa,"%d",number);
    Output_f->addChild(Set_CAnsCreater(bb,aa,""));
    Output_f->removeChildByName("ntor");

}


void CAnsCreater::Input_ans(Node &Q, int number) {
    char Input[5];
    char fn[3];
    int inputData, data;
    auto bg = (Node *)Q.getChildByName("bg");

    Node *Output_f = (Node *)Q.getChildByName("F_1");
    Text *f = (Text *)Output_f->getChildByName("ntor");
    sprintf(fn, "%d", f->getTag());
    sprintf(Input, "%d", number);
    int k = Output_f->getTag();

    if(f->getTag() == -1){
        answer[0] = number / k;
        answer[2] = number % k;
    }
    else {
        answer[0] = std::atoi(fn);
        answer[2] = std::atoi(Numerator(f->getString().c_str(), Input));
    }
    if(k == 0)answer[1] = number;
    else answer[1] = k;

    CCLOG("answer = %d,%d,%d", answer[0], answer[1], answer[2]);

}

void CAnsCreater::Input_ans(int number,int c,int b) {
    answer[0] = 0;
    answer[1] = number;
    answer[2] = b*c;
    
    CCLOG("answer = %d,%d,%d", answer[0], answer[1], answer[2]);
    
}

bool CAnsCreater::CheckAnswer(Vec3 a) {
	if (a.x != answer[0] || a.y != answer[1] || a.z != answer[2])return false;
	return true;
}

char * CAnsCreater::Numerator(const char *c, const char *number) {
	char *ntor = (char*)c;
	bool count = false; //�P�_�O�_�n�B��(+,-,*,/)
	bool z = false;
	if (number[1] != NULL)z = true;        //�P�_�X��� 2��H�W
	if (c[0] == 'd') {  //�p�G�O���ܤ��l ��d���������e
		for (int i = 0; c[i] != NULL; i++)
			ntor[i] = c[i + 1];
	}
    
	//�����r�ꪺ�L�{
	for (int i = 0; c[i] != NULL; i++) {
		if (c[i] == 'F') {               //F��������
			if (z == true) {
				ntor = new char[strlen(c) + 1];
				ntor = (char*)c;
				for (int i = strlen(ntor) - 1; i >= 0; i--) //�N�r�꩹���
					ntor[i + 1] = c[i];
				ntor[i] = number[0]; ntor[i + 1] = number[1];
			}
			else {
				ntor[i] = number[0];
			}
		}
		else if (c[i] == '=') { //�X�{'��'�i�B��
			count = true;
		}
	}

	//�[����B��
	if (count == true) {
		int a = 0, b = 0;
		for (int i = 0; ntor[i] != NULL; i++)
			switch (c[i]) {
			case '+':
				for (int x = i - 1, y = 0; x > 0; x--, y++)//x�Ʀr y�Ӧ�ƩΤQ���
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
	auto fn = (Node *)Node::create(); //�̫᪺�^��-���ƪ��Ϊ�
	Sprite *bar;
	auto Ntor = cocos2d::ui::Text::create(); //���l
	auto Dtor = cocos2d::ui::Text::create(); //����

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
	auto plus = new cocos2d::ui::Text*[n - 1]; //�[
	auto equal = cocos2d::ui::Text::create(); //����

	auto fn = (Node *)Node::create(); //�̫᪺�^��-�B�⦡���Ϊ�

	//���ƥͦ�
	Node ** all_f = new Node*[n + 1];
	for (int i = 0; i < n + 1; i++) {
		if (i < n)
			all_f[i] = Set_CAnsCreater("1", c_n, "0");
		else
			all_f[i] = Set_CAnsCreater(c_n, c_n, "0");
	}

	//�Ʀ�l
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

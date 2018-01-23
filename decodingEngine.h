#include "decodingModuleHeaders.h"
#include <bits/stdc++.h>
#define MAX 100
#define ascii 129
using namespace std;

class decodingModule{
  ifstream inFile;
  node *root;
  vector <int> inOrder;
  vector <int> preOrder;
  int preIndex;
  clock_t begin, end;
public:
  decodingModule();
  void setRoot(node *temp);
  node *getRoot();
  node *getNode(int data);
  void generateInOrderAndPreOrder();
  int sizeOfArray();
  int search(int start, int end, int data);
  node* generateTreeUtil(int start, int end);
  int isLeaf(node* temp);
  void decodingUtil(node *temp);
  ~decodingModule();
};

decodingModule::decodingModule(){
  begin = clock();
  root = NULL;
  preIndex = 0;
}

void decodingModule::setRoot(node *temp){
  this->root = temp;
}

node *decodingModule::getRoot(){
  return this->root;
}

node *decodingModule::getNode(int data){
  node *temp = new node;
  temp->setData(data);
  temp->setLchild(NULL);
  temp->setRchild(NULL);
	return temp;
}

void decodingModule::generateInOrderAndPreOrder(){
  inFile.open("ModuleCodes.bin");
  if (!inFile.is_open())  {
    cout << "Path to file \"ModuleCodes.bin\" not found." << endl;
    exit(0);
  }
  else
    cout << "File is being Decoded ...\nPlease Wait ..." << endl;
  char c;
  int flag = 0, signFlag = 0;
  std::string s = "";
  while(inFile.get(c)){
    if(c == '-')
      signFlag = 1;
    else if(c == '~')
      flag = 1;
    else if(c == ','){
      int no  = atoi(s.c_str());
      if(signFlag == 1) {no = -no;}
      if(flag == 0) inOrder.push_back(no);
      else preOrder.push_back(no);
      signFlag = 0;
      s = "";
    }
    else
      s += c;
  }
  inFile.close();
}

int decodingModule::sizeOfArray(){
  return (inOrder.size() - 1);
}

int decodingModule::search(int start, int end, int data){
  for(int i = start; i <= end; i++){
    if(inOrder[i] == data)
      return i;
  }
  return -1;
}

node *decodingModule::generateTreeUtil(int start, int end){
  if(start > end) return NULL;
  node *newNode = getNode(preOrder[preIndex++]);
  if(start == end)  return newNode;
  int inIndex = search(start, end, newNode->getData());
  newNode->setLchild(generateTreeUtil(start, inIndex - 1));
  newNode->setRchild(generateTreeUtil(inIndex + 1, end));
  return newNode;
}

int decodingModule::isLeaf(node* temp){
	 return (temp->getLchild() == NULL && temp->getRchild() == NULL ? 1 : 0);
}

void decodingModule::decodingUtil(node *temp){
  ifstream decodedFile;
  decodedFile.open("Output.bin");
  FILE *ModuleDecodedFile = fopen("Decoded.txt", "wb");
  char c;
  int flag = 0;
  decodedFile.get(c);
  while (1){
    while (!(isLeaf(temp))){
      if (c == '0') {
        temp = temp->getLchild();
        if(!decodedFile.get(c)) {flag = 1;break;}
      }
      else if (c == '1') {
        temp = temp->getRchild();
        if(!decodedFile.get(c)) {flag = 1;break;}
      }
      else {
        cout << "Error encounted... Aborting!!!" << endl;
        exit(0);
        return;
      }
      if(flag == 1) break;
    }
    fprintf(ModuleDecodedFile, "%c", (char)temp->getData());
    if(flag == 1) break;
    temp = getRoot();
  }
  fclose(ModuleDecodedFile);
  decodedFile.close();
}

decodingModule::~decodingModule(){
  cout << "File Successfully Decoded." << endl;
  end = clock();
  double timeTakenToDecode = (double)(end - begin) / CLOCKS_PER_SEC;
  cout << "Time Taken for Decoding is \"" << timeTakenToDecode << "\" Sec."<< endl;
}

#include <bits/stdc++.h>
#include "encodingModuleHeaders.h"
#define MAX 100
#define ascii 129
using namespace std;

class encodingModule{
  ifstream inFile;
  char filePath[MAX];
  node *root;
  int freq[129];
  char encodeValue[ascii][MAX];
  clock_t begin, end;
public:
  encodingModule();
  void setRoot(node *temp);
  node *getRoot();
  node *getNode(int data, int freq);
  minHeap *createHeap(int capacity);
  void swap(node **a, node **b);
  void heapify(minHeap *heapNode, int index);
  void buildHeap(minHeap *heapNode);
  node *getMinNode(minHeap *heapNode);
  void insert(minHeap *heapNode, node *node);
  node *generateTreeUtil();
  void generateCodesUtil(node *temp);
  void generateCodes(node *temp, int codes[], int k);
  void encodingUtil();
  void ModuleCodes(node *temp);
  void inOrder(node *temp, FILE *);
  void preOrder(node *temp, FILE *);
  ~encodingModule();
};

encodingModule::encodingModule(){
  cout << "Enter the Path of File to be Encoded ::" << endl;
  cin >> filePath;
  begin = clock();
  inFile.open(filePath);
  if (!inFile.is_open())  {
    cout << "Path to file \"" << filePath << "\" not found." << endl;
    exit(0);
  }
  root = NULL;
  char c;
  cout << "File Found and being Encoded ...\nPlease Wait ..." << endl;
  while (inFile.get(c))
    ++freq[(int)c];
}

void encodingModule::setRoot(node *temp){
  this->root = temp;
}

node *encodingModule::getRoot(){
  return this->root;
}

node *encodingModule::getNode(int data,int freq){
  node *temp = new node;
  temp->setData(data);
  temp->setFreq(freq);
  temp->setLchild(NULL);
  temp->setRchild(NULL);
	return temp;
}

minHeap *encodingModule::createHeap(int capacity){
  minHeap *temp = new minHeap;
	temp->setSize(capacity);
	temp->setCapacity(capacity);
  temp->setArray(capacity);
	return temp;
}

void encodingModule::swap(node **a, node **b){
	node *temp = *a;
	*a = *b;
	*b = temp;
}

void encodingModule::heapify(minHeap *heapNode, int index){
  int smallest = index;
	int left = 2 * index + 1;
	int right = 2 * index + 2;
	if(left < heapNode->getSize() && heapNode->getArray(left)->getFreq() < heapNode->getArray(smallest)->getFreq())
		smallest = left;
	if(right < heapNode->getSize() && heapNode->getArray(right)->getFreq() < heapNode->getArray(smallest)->getFreq())
		smallest = right;
	if(smallest != index){
		swap(&heapNode->getArray(smallest), &heapNode->getArray(index));
		heapify(heapNode, smallest);
	}
}

void encodingModule::buildHeap(minHeap *heapNode){
  int n = heapNode->getSize() - 1;
	for(int i = (ascii - 1)/2;i >= 0;--i)
		heapify(heapNode, i);
}

node *encodingModule::getMinNode(minHeap *heapNode){
	node *temp = heapNode->getArray(0);
  heapNode->setArrayElement(heapNode->getArray(heapNode->getSize() - 1), 0);
	heapNode->setSize(heapNode->getSize() - 1);
	heapify(heapNode,0);
	return temp;
}

void encodingModule::insert(minHeap *heapNode, node *node){
  heapNode->setSize(heapNode->getSize() + 1);
	int i = heapNode->getSize() - 1;
	while(i && node->getFreq() < heapNode->getArray((i - 1)/2)->getFreq()){
		heapNode->setArrayElement(heapNode->getArray((i - 1)/2), i);
		i = (i - 1)/2;
	}
  heapNode->setArrayElement(node, i);
}

node *encodingModule::generateTreeUtil(){
  int rootValue = -1;
	node *lNode,*rNode,*newNode;
	minHeap *heapNode = createHeap(ascii);
	for(int i = 1;i < ascii;i++)
    heapNode->setArrayElement(getNode(i,freq[i]), i);
	buildHeap(heapNode);
	while(heapNode->getSize() != 1){
		lNode = getMinNode(heapNode);
		rNode = getMinNode(heapNode);
		int freq = lNode->getFreq() + rNode->getFreq();
		newNode = getNode(rootValue--,freq);
		newNode->setLchild(lNode);
		newNode->setRchild(rNode);
		insert(heapNode,newNode);
	}
	return getMinNode(heapNode);
}

void encodingModule::generateCodesUtil(node *temp){
  int codes[MAX];
  generateCodes(temp, codes, 0);
}

void encodingModule::generateCodes(node *temp, int codes[], int k){
	int no = 0;
	if(temp->getLchild()){
		codes[k] = 0;
		generateCodes(temp->getLchild(), codes, k + 1);
	}
	if(temp->getRchild()){
		codes[k] = 1;
		generateCodes(temp->getRchild(), codes, k + 1);
	}
	if(temp->getLchild() == NULL && temp->getRchild() == NULL){
		int x = 0;
		for(int i = 0;i < k;i++){
			encodeValue[temp->getData()][x] = codes[i] + 48;
			x++;
		}
		encodeValue[temp->getData()][x] = '\0';
	}
}

void encodingModule::encodingUtil(){
  FILE *ModuleOutputFile = fopen("Output.bin", "wb");
  char c;
  inFile.clear();
  inFile.seekg(0, ios::beg);
	while (inFile.get(c)){
    if(encodeValue[(int)c] != 0)
      for(int i = 0;encodeValue[(int)c][i] != '\0';i++)
        fprintf(ModuleOutputFile, "%c", encodeValue[(int)c][i]);
    else{
			cout << "Error in input Sequence" << endl;
      exit(0);
		}
	}
  fclose(ModuleOutputFile);
}

void encodingModule::ModuleCodes(node *temp){
  FILE *ModuleCodesFile = fopen ("ModuleCodes.bin", "wb");
  inOrder(temp, ModuleCodesFile);
  fputs("~", ModuleCodesFile);
  preOrder(temp, ModuleCodesFile);
  fclose(ModuleCodesFile);
}

void encodingModule::inOrder(node *temp, FILE *ModuleCodesFile){
  if(temp){
    inOrder(temp->getLchild(), ModuleCodesFile);
    fprintf(ModuleCodesFile, "%d,", temp->getData());
    inOrder(temp->getRchild(), ModuleCodesFile);
  }
}

void encodingModule::preOrder(node *temp, FILE *ModuleCodesFile){
  if(temp){
    fprintf(ModuleCodesFile, "%d,", temp->getData());
    preOrder(temp->getLchild(), ModuleCodesFile);
    preOrder(temp->getRchild(), ModuleCodesFile);
  }
}

encodingModule::~encodingModule(){
  inFile.close();
  cout << "Encoding of File is Finished Successfully" << endl;
  end = clock();
  double timeTakenToEncode = (double)(end - begin) / CLOCKS_PER_SEC;
  cout << "Time Taken for Encoding is \"" << timeTakenToEncode << "\" Sec."<< endl;
}

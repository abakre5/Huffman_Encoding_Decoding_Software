class node{
	int data;
	int freq;
	node *lChild;
	node *rChild;
public:
  void setData(int data);
  void setFreq(int freq);
  void setLchild(node *temp);
  void setRchild(node *temp);
  int getData();
  int getFreq();
  node *getLchild();
  node *getRchild();
};

void node::setData(int data){
  this->data = data;
}

void node::setFreq(int freq){
  this->freq = freq;
}

void node::setLchild(node *temp){
  this->lChild = temp;
}

void node::setRchild(node *temp){
  this->rChild = temp;
}

int node::getData(){
  return this->data;
}

int node::getFreq(){
  return this->freq;
}

node *node::getLchild(){
  return this->lChild;
}

node *node::getRchild(){
  return this->rChild;
}

class minHeap{
	int size;
	int capacity;
public:
node **array;
  void setSize(int size);
  void setCapacity(int capacity);
  void setArray(int capacity);
  int getSize();
  int getCapacity();
  node *&getArray(int);
  void setArrayElement(node *, int i);
};

void minHeap::setSize(int size){
  this->size = size;
}

void minHeap::setCapacity(int capacity){
  this->capacity = capacity;
}

int minHeap::getSize(){
  return this->size;
}

int minHeap::getCapacity(){
  return this->capacity;
}

void minHeap::setArray(int capacity){
  this->array = new node*[capacity];
  for(int i = 0; i < capacity; ++i)
    array[i] = new node[capacity];
}

node *&minHeap::getArray(int i){
  return this->array[i];
}


void minHeap::setArrayElement(node *temp, int i){
  this->array[i] = temp;
}

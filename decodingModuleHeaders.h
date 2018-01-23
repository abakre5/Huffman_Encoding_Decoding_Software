class node{
	int data;
	node *lChild;
	node *rChild;
public:
  void setData(int data);
  void setLchild(node *temp);
  void setRchild(node *temp);
  int getData();
  node *getLchild();
  node *getRchild();
};

void node::setData(int data){
  this->data = data;
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

node *node::getLchild(){
  return this->lChild;
}

node *node::getRchild(){
  return this->rChild;
}

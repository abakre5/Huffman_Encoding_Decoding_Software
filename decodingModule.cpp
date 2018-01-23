#include "decodingEngine.h"

int main(){
  decodingModule *decodingModuleObj = new decodingModule;
  decodingModuleObj->generateInOrderAndPreOrder();
  decodingModuleObj->setRoot(decodingModuleObj->generateTreeUtil(0, decodingModuleObj->sizeOfArray()));
  decodingModuleObj->decodingUtil(decodingModuleObj->getRoot());
  decodingModuleObj->~decodingModule();
  return 0;
}

#include "encodingEngine.h"

int main(){
  encodingModule *encodingModuleObj = new encodingModule;
  encodingModuleObj->setRoot(encodingModuleObj->generateTreeUtil());
  encodingModuleObj->generateCodesUtil(encodingModuleObj->getRoot());
  encodingModuleObj->ModuleCodes(encodingModuleObj->getRoot());
  encodingModuleObj->encodingUtil();
  encodingModuleObj->~encodingModule();
  return 0;
}

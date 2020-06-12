int stringToInt(String x){
  int i=0;
  int val=0;
  while(x[i]!='\0'){
    val*=10;
    int temp = x[i]-48;
    val+=temp;
    i++;
  }
  return val;
}

char* stringToCharPtr(String x){
  char *ptr=new char [x.length()+1];
  int i;
  for(i=0;i<x.length();i++){
    ptr[i]=x[i];
  }
  ptr[i]='\0';
  return ptr;
}

#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
using namespace std;

struct Pitch{
    int num;
    std::string type;
    std::string tie;
    std::string dot;
    int finger;
    int duration;
};

using namespace std;

int main(){

  Pitch pitch[10000];
  Pitch pitch2[10000];
  int tag=0;

  std::ifstream myfile("/home/franklin/Desktop/xml2vec-master/test.txt");

  char c;
  int line=0;
  while (myfile.get(c)) {
      if (c == '\n')
          line++;
  }
  //std::cout<<line<<std::endl;

  std::ifstream myfile2("/home/franklin/Desktop/xml2vec-master/test.txt");
  int m=4;     //
  std::string **swp;      //动态申请二维数组 line行 m列
  swp=new std::string*[line];
  for(int i=0;i<line;i++)
  swp[i]=new std::string[m];

  for(int i=0;i<line;i++){
      for(int j=0;j<4;j++){
          myfile2 >> swp[i][j];
      }
  }


  for (int i=0; i<line; i++){
      pitch[i].num  = stoi(swp[i][0]);
      pitch[i].type = swp[i][1];
      pitch[i].tie  = swp[i][2];
      pitch[i].dot  = swp[i][3];

      //std::cout << pitch[i].num <<"\t"<< pitch[i].type<<"\t"<<pitch[i].tie<<"\t"<<pitch[i].dot<<std::endl;
  }

  myfile2.close();
  //**************************************************************************************






  //***********************根据音符类型、有无附点以及空音符来计算duration值**********************
  for (int i=0; i<line; i++){
      if(pitch[i].dot == "False")
      {
          if(pitch[i].type == "half")
              pitch[i].duration = 1000;
          else if(pitch[i].type == "quarter")
              pitch[i].duration = 500;
          else if(pitch[i].type == "eighth")
              pitch[i].duration = 250;
          else if(pitch[i].type == "16th")
              pitch[i].duration = 125;
          else if(pitch[i].type == "whole")
              pitch[i].duration = 2000;
          else
              pitch[i].duration = 125;

      }
      else
      {
          if(pitch[i].type == "half")
              pitch[i].duration = 1500;
          else if(pitch[i].type == "quarter")
              pitch[i].duration = 750;
          else if(pitch[i].type == "eighth")
              pitch[i].duration = 375;
          else if(pitch[i].type == "16th")
              pitch[i].duration = 187;
          else if(pitch[i].type == "whole")
              pitch[i].duration = 3000;
          else
              pitch[i].duration = 125;
      }
  }
  //找到乐谱中所有的空音符，然后将其duration添加到前面最近的非空音符上。
  for (int i=0; i<line; i++){
      if(pitch[i].num == 999){
          int notation = 0;
          int j=i;
          while(pitch[j].num == 999)
          {
              j--;
              if(j<0)
              {notation = 1;break;}
          }
          if(notation == 1)
              continue;
          else
              pitch[j].duration = pitch[j].duration + pitch[i].duration;
      }
  }
  //**************************************************************************************










//***********************************分配手指，生成pitch.finger成员变量值*************
//找出所有的空音符并计数count，将所有的非空音符提取复制到另一个对象pitch2中，
//然后对pitch2对象进行处理,计算出finger值
  int count=0;
  for (int i=0,j=0; i<line; i++){
      if(pitch[i].num!=999){
           pitch2[j] = pitch[i];
           j++;
      }
      else {
          count++;
      }
  }
  while(pitch2[tag].num){
//特殊情况,如果当前音符为最后一个或者倒数第二个，需要特殊处理
//其他音符通过while循环处理
      if(tag == (line-count-1) ){
          pitch2[tag].finger = 1;
          break;
      }
      else if(tag == (line-count-2) ){

          if( (pitch2[tag+1].num - pitch2[tag].num) == 10 ){
              pitch2[tag].finger = 1;
              pitch2[tag+1].finger = 2;
          }
          else if( (pitch2[tag+1].num - pitch2[tag].num) == 20 ){
              pitch2[tag].finger = 1;
              pitch2[tag+1].finger = 3;
          }
          else if( (pitch2[tag+1].num - pitch2[tag].num) == 30 ){
              pitch2[tag].finger = 1;
              pitch2[tag+1].finger = 4;
          }
          else if( (pitch2[tag].num - pitch2[tag+1].num) == 10 ){
              pitch2[tag].finger = 4;
              pitch2[tag+1].finger = 3;
          }
          else if( (pitch2[tag].num - pitch2[tag+1].num) == 20 ){
              pitch2[tag].finger = 4;
              pitch2[tag+1].finger = 2;
          }
          else if( (pitch2[tag].num - pitch2[tag+1].num) == 30 ){
              pitch2[tag].finger = 4;
              pitch2[tag+1].finger = 1;
          }
          else{
              pitch2[tag].finger = 1;
              pitch2[tag+1].finger = 1;
          }

          break;
      }
      else{
          int min = 0;
          int max = 0;
          int minimum = 0;
          int flag = 0;
          int flag2 = 0;
          if (pitch2[tag].num > pitch2[tag+1].num){
              min = pitch2[tag+1].num;
              max = pitch2[tag].num;
          }
          else {
              min = pitch2[tag].num;
              max = pitch2[tag+1].num;
          }
          for (int i=tag+2; i<line-count; i++){

              if(pitch2[i].num > max)
              {
                  max = pitch2[i].num;
                  minimum = min;
              }
              else if(pitch2[i].num < min)
              {
                  minimum = min;
                  min = pitch2[i].num;
              }
              else
                  minimum = min;


              if ( (max - min)>30){
                  for(int j=tag; j<=i-1; j++){
                      if(pitch2[j].num == minimum)
                          pitch2[j].finger = 1;
                      else if((pitch2[j].num - minimum) == 10)
                          pitch2[j].finger = 2;
                      else if((pitch2[j].num - minimum) == 20)
                          pitch2[j].finger = 3;
                      else if((pitch2[j].num - minimum) == 30)
                          pitch2[j].finger = 4;
                      else
                          pitch2[j].finger = 1;
                  }
                  tag = i;
                  flag = 1;
                  break;
              }
            }
          if (flag == 0){
              for(int j=tag; j<line-count; j++){
                  if(pitch2[j].num == min)
                      pitch2[j].finger = 1;
                  else if((pitch2[j].num - min) == 10)
                      pitch2[j].finger = 2;
                  else if((pitch2[j].num - min) == 20)
                      pitch2[j].finger = 3;
                  else if((pitch2[j].num - min) == 30)
                      pitch2[j].finger = 4;
                  else
                      pitch2[j].finger = 1;
              }
              flag2 = 1;
          }

          if(flag2 == 1)
              break;
      }
  }
//*******************************************************************************







//**********************************还要考虑机械臂移动所花费的时间，本项目统一为300ms.****************
//下面是遍历pitch2对象数组且找出机械臂发生移动的音符，令该音符前一个音符的时值减去机械臂移动时间。************
  for(int i=0; i<line-count-1; i++){
      if(    ((pitch2[i+1].num > pitch2[i].num) and(pitch2[i+1].finger < pitch2[i].finger) )  or  ((pitch2[i+1].num<pitch2[i].num) and (pitch2[i+1].finger>pitch2[i].finger))   or   (abs(pitch2[i+1].num-pitch2[i].num) != abs(pitch2[i+1].finger-pitch2[i].finger) *10)     )
      //if(   (abs(pitch2[i+1].num-pitch2[i].num) != abs(pitch2[i+1].finger-pitch2[i].finger) *10)     )
        pitch2[i].duration = pitch2[i].duration - 300;
      if(pitch2[i].duration < 0)
          pitch2[i].duration = 0;

    }







//***************最终生成了规划结果，保存在txt文档格式*********************************
  std::ofstream plan_file("/home/franklin/Desktop/xml2vec-master/planning_result.txt",std::ios::out);
  for (int i=0; i<line-count; i++) {
      plan_file << pitch2[i].num <<"\t"<<pitch2[i].finger<<"\t"<<pitch2[i].duration<<std::endl;
  }
  plan_file.close();



  return 0;
}




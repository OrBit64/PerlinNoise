#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <random>
#include <algorithm>


/*
int main(){
    vector<int>nums={1,2,3,4,5,6};
    for(int i =0;i<6;i++){
        cout<<nums[i]<<endl;
    }

}
*/

double dotXY(double X,double Y);//функция для обнаружения координат сетки


int main(){


}
//я не доделал эту функцию
double dotXY(double X,double Y){

    int LeftLowX=std::floor(X);
    int LeftLowY=std::floor(Y);
    double dotX=X-LeftLowX;//расположение точки X пример: х=2.2  2.2-2=0.2 
    double dotY=Y-LeftLowY;
    int RightLowX=LeftLowX+1;// координата правой нижней части
    int LeftHightY=LeftLowY+1;
    int RightHightX=LeftLowX+1;
    //std::vector<int>LL{LeftLowX,LeftLowY};//LL- left low
    //std::vector<int>RL{RightHightX,LeftLowY};//R-right (first letter-side/ second-height)
    //std::vector<int>LH{LeftLowX,LeftHightY};
    //std::vector<int>RH{RightHightX,LeftHightY};
    return 0.0;
}
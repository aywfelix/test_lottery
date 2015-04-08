#include "util.h"

//测试程序获取1-12数出现的概率
int main(int argc, char *argv[])
{

	int a[12] = {0};
    const int Gen_max = 10000000;
    srand(unsigned(time(0)));
	srand((unsigned)time(NULL));
	int t = 0;
  
	for(int icnt = 0; icnt != Gen_max; ++icnt)
        switch(int(random(1,12)))
        {
        case 1: a[0]++; break;
        case 2: a[1]++; break;
        case 3: a[2]++; break;
        case 4: a[3]++; break;
        case 5: a[4]++; break;
        case 6: a[5]++; break;
        case 7: a[6]++; break;
        case 8: a[7]++; break;
        case 9: a[8]++; break;
        case 10: a[9]++; break;
		case 11: a[10]++; break;
		case 12: a[11]++; break;
        default: cerr << "Error!" << endl; exit(-1);
        }
    
    for(int icnt = 0; icnt != 12; ++icnt)
        cout << icnt <<"\t"<< double(a[icnt])/Gen_max*100 << "%" << endl;
    
	cout <<endl;
    return 0;
}

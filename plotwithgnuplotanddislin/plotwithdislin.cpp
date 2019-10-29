#include <iostream>
#include <cmath>
#include "discpp.h"
#include <vector>
#include <fstream>

using namespace std;
//将文本文件中得数据读入vector中，并返回一个vector。
vector<double> InputData_To_Vector()
{
  vector<double> p;
  ifstream infile("./curvetmp.txt");
  double number;
  while (!infile.eof())
  {
    infile >> number;
    p.push_back(number);
  }
  p.pop_back(); //此处要将最后一个数字弹出，是因为上述循环将最后一个数字读取了两次
  return p;
}

int main()
{
  int n = 100, totaln, i, ic;
  double fpi = 3.1415926 / 180.0, step, x;
  double xray[100], y1ray[100], y2ray[100];
  Dislin g;
  vector<double> result;

  FILE *pPipe;

  /* Run DIR so that it writes its output to a pipe. Open this
         * pipe with read text attribute so that we can read it
         * like a text file.
         */

  char *pipecmd = "awholefile.exe 0.3 0.7 0.18 0.2 0.1 2.3 0.2 1e4 4.5e6 2e4 0.52 >curvetmp.txt";
  if ((pPipe = _popen(pipecmd, "r")) == NULL)
    exit(1);
  _pclose(pPipe);

  result = InputData_To_Vector();
  totaln = result.size();
  n = totaln / 3;
  step = 360. / (n - 1);

  for (i = 0; i < n; i++)
  {
    xray[i] = i * step;
    x = xray[i] * fpi;
    y1ray[i] = sin(x);
    y2ray[i] = cos(x);
    xray[i] = result[3 * i];
    y1ray[i] = result[3 * i + 2];
  }
  // g.qplot(xray, y1ray, n);
  g.metafl("xwin");
  // g.scrmod ("revers");
  g.setpag("da4l");
  g.disini();
  g.pagera();
  g.complx();
  g.axspos(450, 1800);
  g.axslen(2200, 1200);

  g.name("Length", "x");
  g.name("Curvanture", "y");

  g.labdig(-1, "x");
  g.ticks(9, "x");
  g.ticks(10, "y");

  // g.titlin("Demonstration of CURVE", 1);
  g.titlin("Curvanture of Bend Stiffner", 1);

  ic = g.intrgb(0.95, 0.95, 0.95);
  g.axsbgd(ic);

  // g.graf(0.0, 360.0, 0.0, 90.0, -1.0, 1.0, -1.0, 0.5);
  g.graf(0.0, 5.0, 0.0, 1.0, 0.0, 0.25, 0.0, 0.05);
  g.setrgb(0.7, 0.7, 0.7);
  g.grid(1, 1);

  g.color("fore");
  g.height(50);
  g.title();

  g.color("red");
  g.curve(xray, y1ray, n);
  // g.color("green");
  // g.curve(xray, y2ray, n);
  g.disfin();
  return 0;
}
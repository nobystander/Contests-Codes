//计算几何二维模板测试
//根据题意求交点即可。
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;
const double eps = 1e-10;
const double PI = acos(-1.0);

int dcmp(double x)
{
    if(fabs(x) < eps) return 0;
    else return x > 0? 1:-1;
}

//////////////////////////////点和直线部分//////////////////////////////////////
struct Point
{
    double x,y;
    Point(double x = 0,double y = 0):x(x),y(y) {}
};

typedef Point Vector;
Point operator + (Vector A,Vector B) { return Vector(A.x+B.x,A.y+B.y); }
Point operator - (Point A,Point B) { return Vector(A.x-B.x,A.y-B.y); }
Point operator * (Vector A,double p) { return Vector(A.x*p,A.y*p); }
Point operator / (Vector A,double p) { return Vector(A.x/p,A.y/p); }
bool operator == (const Point& A,const Point& B) { return dcmp(A.x-B.x) == 0 && dcmp(A.y-B.y) == 0; }
bool operator < (const Point& A,const Point& B) { return A.x < B.x || (A.x == B.x && A.y < B.y); }

double Dist(Point A,Point B)
{
    return sqrt((A.x-B.x)*(A.x-B.x) + (A.y-B.y)*(A.y-B.y));
}

double Dot(Vector A,Vector B) { return A.x*B.x + A.y*B.y; }
double Cross(Vector A,Vector B) { return A.x*B.y - A.y*B.x; }
double Length(Vector A) { return sqrt(Dot(A,A)); }
double Angle(Vector A,Vector B) { return acos(Dot(A,B) / Length(A) / Length(B)); } //A,B所成角
double Angle(Vector A) { return atan2(A.y,A.x); } //向量与x轴正方向所成角
double Area2(Point A,Point C,Point B)  { return Cross(B-A,C-A); } //求AB,AC向量所成平行四边形面积
Vector Normal(Vector A) //求A向量单位法相量　向左侧
{
    double L = Length(A);
    return Vector(-A.y/L,A.x/L);
}
Vector Rotate(Vector A,double rad)
{
    return Vector(A.x*cos(rad)-A.y*sin(rad),A.x*sin(rad)+A.y*cos(rad));
}
Point TwoLinePoint(Point P,Vector v,Point Q,Vector w) //求P+tv和Q+tw的交点
{
    Vector u = P-Q;
    double t = Cross(w,u)/Cross(v,w);
    return P+v*t;
}
double PointToLine(Point P,Point A,Point B) //点P到AB直线距离
{
    Vector v1 = B-A,v2 = P-A;
    return fabs(Cross(v1,v2))/Length(v1);
}
double PointToSegment(Point P,Point A,Point B) //点P到线段AB距离
{
    if(A == B) return Length(P-A);
    Vector v = B-A,v1 = P-A,v2 = P-B;
    if(dcmp(Dot(v,v1)) < 0) return Length(v1);
    else if(dcmp(Dot(v,v2)) > 0) return Length(v2);
    else   return fabs(Cross(v,v1)) / Length(v);
}
Point LineProjection(Point P,Point A,Point B) //点P在直线AB上的投影点
{
    Vector v = B-A;
    return A+v*(Dot(v,P-A) / Dot(v,v));
}
bool IsSegmentProperIntersection(Point a1,Point a2,Point b1,Point b2) //判断２线段是否相交（规范相交：只有１个交点且交点不在线段端点）
{
    double c1 = Cross(a2-a1,b1-a1),c2 = Cross(a2-a1,b2-a1),
        c3 = Cross(b2-b1,a1-b1),c4 = Cross(b2-b1,a2-b1);
    return dcmp(c1)*dcmp(c2) < 0 && dcmp(c3)*dcmp(c4) < 0;
}
bool IsPointOnSegment(Point P,Point A,Point B) //判断点是否在直线上，
{
    return dcmp(Cross(A-P,B-P)) == 0 && dcmp(Dot(A-P,B-P)) < 0;
}

bool IsSegmentInproperIntersection(Point a1,Point a2,Point b1,Point b2) //判断２线段是否相交(非规范）
{
     if(IsPointOnSegment(a1,b1,b2) || IsPointOnSegment(a2,b1,b2) ||
        IsPointOnSegment(b1,a1,a2) || IsPointOnSegment(b2,a1,a2))
            return true;
    return IsSegmentProperIntersection(a1,a2,b1,b2);
}

double PolygonArea(const vector<Point>& P)//求多边形面积
{
    int n = P.size();
    double area = 0;
    for(int i = 1;i < n-1;++i)
        area += Area2(P[0],P[i],P[i+1]);
    return area/2;
}


///////////////////////////////////直线和圆///////////////////////////////////////////

struct Line
{
    Point p;
    Vector v;
    Line(Point p,Vector v): p(p),v(v) {}
    Point getPoint(double t) { return p+v*t; } //获得直线上一点
    Line move(double d) { return Line(p+Normal(v)*d,v); } //直线沿法相量平移d
};
struct Circle
{
    Point c;
    double r;
    Circle(Point c,double r):c(c),r(r) {}
    Point getPoint(double rad) //获得圆上一点(rad为逆时针角)
    {
        return Point(c.x+cos(rad)*r,c.y*sin(rad)*r);
    }
};
int LineCirclePoint(Line L,Circle C,vector<Point>& res) //求直线与圆的交点，返回交点数
{
    double a = L.v.x,b = L.p.x-C.c.x,c = L.v.y,d = L.p.y-C.c.y;
    double e = a*a+c*c,f = 2*(a*b + c*d),g = b*b+d*d-C.r*C.r;
    double delta = f*f-4*e*g;
    double t1,t2;
    if(dcmp(delta) < 0) return 0;
    if(dcmp(delta) == 0)
    {
        t1 = t2 = -f / (2*e);
        res.push_back(L.getPoint(t1));
        return 1;
    }
    t1 = (-f - sqrt(delta)) / (2*e);
    res.push_back(L.getPoint(t1));
    t2 = (-f + sqrt(delta)) / (2*e);
    res.push_back(L.getPoint(t2));
    return 2;
}
int TwoCirclePoint(Circle C1,Circle C2,vector<Point>& res) //求２圆交点，返回交点数（特别的－１表示２圆重合，无穷个交点)
{
    double d = Length(C1.c-C2.c);
    if(dcmp(d) == 0)
    {
        if(dcmp(C1.r-C2.r) == 0) return -1;
        return 0;
    }
    if(dcmp(C1.r + C2.r - d) < 0) return 0;
    if(dcmp(fabs(C1.r-C2.r) - d) > 0) return 0;

    double a = Angle(C2.c-C1.c);
    double da = acos((C1.r*C1.r+d*d-C2.r*C2.r) / (2*C1.r*d));
    Point p1 = C1.getPoint(a-da),p2 = C1.getPoint(a+da);

    res.push_back(p1);
    if(p1 == p2) return 1;
    res.push_back(p2);
    return 2;
}
int PointCircleTangents(Point p,Circle C,vector<Line>& res) //过顶点球圆的切线，返回切线条数
{
    Vector u = C.c - p;
    double dist = Length(u);
    if(dist < C.r) return 0;
    else if(dcmp(dist - C.r) == 0)
    {
        res.push_back(Line(p,Rotate(u,PI/2)));
        return 1;
    }
    else
    {
        double ang = asin(C.r/dist);
        res.push_back(Line(p,Rotate(u,-ang)));
        res.push_back(Line(p,Rotate(u,+ang)));
        return 2;
    }
}

int TwoCircleTangents(Circle A,Circle B,vector<Point>& a,vector<Point>& b)
{
    int cnt = 0;
    if(A.r < B.r) { swap(A,B); swap(a,b); }
    int d2 = (A.c.x-B.c.x)*(A.c.x-B.c.x) + (A.c.y-B.c.y)*(A.c.y-B.c.y);
    int rdiff = A.r-B.r;
    int rsum = A.r+B.r;
    if(d2 < rdiff*rdiff) return 0;

    double base = atan2(B.c.y-A.c.y,B.c.x-A.c.x);
    if(d2 == 0 && A.r == B.r) return -1;
    if(d2 == rdiff*rdiff)
    {
        a.push_back(A.getPoint(base)) ; b.push_back(B.getPoint(base)); cnt++;
        return 1;
    }
    double ang = acos((A.r-B.r) / sqrt(d2));
    a.push_back(A.getPoint(base+ang)); b.push_back(B.getPoint(base+ang)); cnt++;
    a.push_back(A.getPoint(base-ang)); b.push_back(B.getPoint(base-ang)); cnt++;
    if(d2 == rsum*rsum)
    {
        a.push_back(A.getPoint(base)); b.push_back(B.getPoint(PI+base)); cnt++;
    }
    else if(d2 > rsum*rsum)
    {
        double ang = acos((A.r+B.r) / sqrt(d2));
        a.push_back(A.getPoint(base+ang)); b.push_back(B.getPoint(PI+base+ang)); cnt++;
        a.push_back(A.getPoint(base-ang)); b.push_back(B.getPoint(PI+base-ang)); cnt++;
    }
    return cnt;
}

/////////////////////////点和多边形///////////////////////////////////

int IsPointInPolygon(Point p,vector<Point>& poly) //判断点p是否在多边形内　-1表示在边界上，1在内部，０在外部
{
    int wn = 0;
    int n=poly.size();
    for(int i = 0; i < n; i++)
    {
        if(IsPointOnSegment(p, poly[i], poly[(i+1)%n])) return -1;
        int k = dcmp(Cross(poly[(i+1)%n]-poly[i], p-poly[i]));
        int d1 = dcmp(poly[i].y-p.y);
        int d2 = dcmp(poly[(i+1)%n].y-p.y);
        if(k > 0 && d1 <= 0 && d2 > 0) wn++;
        if(k < 0 && d2 <= 0 && d1 > 0) wn--;
    }
    if (wn != 0) return 1;
    return 0;
}


/////////////////////点群///////////////////////////

//计算凸包
//输入点顺序不会被破坏
//如果不希望在凸包的边上有点，把２个<=改成<
//精度较高时候使用dcmp比较
int ConvexHull(vector<Point> p,vector<Point>& res)
{
    res.erase(unique(p.begin(),p.end()));
    sort(p.begin(),p.end());
    int n = p.size();
    int m = 0;
    for(int i = 0; i < n; i++)
    {
        while(m > 1 && Cross(res[m-1]-res[m-2], p[i]-res[m-2]) <= 0) m--;
        res.push_back(p[i]);m++;
    }
    int k=m;
    for(int i = n-2; i >= 0; i--)
    {
        while(m > k && Cross(res[m-1]-res[m-2], p[i]-res[m-2]) <= 0) m--;
        res.push_back(p[i]);m++;
    }
    if(n > 1) m--;
    return m;
}



//旋转卡壳求最大２点距离
double RotatingCalipers(vector<Point>& points) {
  vector<Point> p;
  ConvexHull(points,p);
  int n = p.size();
  if(n == 1) return 0;
  if(n == 2) return Dist(p[0], p[1]);
  p.push_back(p[0]); // 免得取模
  double ans = 0;
  for(int u = 0, v = 1; u < n; u++) {
    // 一条直线贴住边p[u]-p[u+1]
    for(;;) {
      // 当Area(p[u], p[u+1], p[v+1]) <= Area(p[u], p[u+1], p[v])时停止旋转
      // 即Cross(p[u+1]-p[u], p[v+1]-p[u]) - Cross(p[u+1]-p[u], p[v]-p[u]) <= 0
      // 根据Cross(A,B) - Cross(A,C) = Cross(A,B-C)
      // 化简得Cross(p[u+1]-p[u], p[v+1]-p[v]) <= 0
      int diff = Cross(p[u+1]-p[u], p[v+1]-p[v]);
      if(diff <= 0) {
        ans = max(ans, Dist(p[u], p[v])); // u和v是对踵点
        if(diff == 0) ans = max(ans, Dist(p[u], p[v+1])); // diff == 0时u和v+1也是对踵点
        break;
      }
      v = (v + 1) % n;
    }
  }
  return ans;
}

// 半平面交主过程


Point getPoint(Point A,Point B,Point C)
{
	Vector v1=C-B;
	double a1=Angle(A-B,v1);	
	v1=Rotate(v1,a1/3);

	Vector v2=B-C;
	double a2=Angle(A-C,v2);	
	v2=Rotate(v2,-a2/3);

	return TwoLinePoint(B,v1,C,v2);
}

int main()
{
	//freopen("test","r",stdin);
	Point A,B,C,D,E,F;
	int T;
	scanf("%d",&T);
	while(T--){
		scanf("%lf %lf",&A.x,&A.y);
		scanf("%lf %lf",&B.x,&B.y);
		scanf("%lf %lf",&C.x,&C.y);
		D=getPoint(A,B,C);
		E=getPoint(B,C,A);
		F=getPoint(C,A,B);
		printf("%.6lf %.6lf %.6lf %.6lf %.6lf %.6lf\n",D.x,D.y,E.x,E.y,F.x,F.y);
	}
	return 0;
}



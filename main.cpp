#include <bits/stdc++.h>

using namespace std;

ifstream in("dateConvex.in");

class Punct
{
    public:
     double x, y;
     Punct(double abscisa, double ordonata):x(abscisa), y(ordonata){}
     Punct(){}
     friend ostream& operator << (ostream& os, const Punct& point);

     bool operator == (const Punct& p)
     {
         return (x == p.x) && (y == p.y);
     }

     bool operator != (const Punct& p)
     {
         return (x != p.x) || (y != p.y);
     }
};

ostream& operator << (ostream& os, const Punct& point)
{
    os<<'('<<point.x<<','<<point.y<<')'<<" ";
    return os;
}

class Sorter
{
public:
    static Punct st;
    static bool cmp(const Punct &A, const Punct&B)
    {
        return (A.y-st.y)*(B.x-st.x) < (B.y-st.y)*(A.x-st.x);
    }
    static void Sort(vector<Punct>&P, int start)
    {
        st = P[start];
        Punct t = P[0];
        P[0] = P[start];
        P[start]=t;
        sort(P.begin()+1, P.end(), Sorter::cmp);
    }
};

Punct Sorter :: st = Punct();

void citire(vector<Punct>& points)
{
     double x, y;
     while(in>>x>>y)
         points.push_back(Punct(x,y));
}

void afisare(int n, vector<Punct>& points)
{
    for(int i = 0; i < n; i++)
        cout<<points[i];
}

int produs_vectorial(const Punct &A, const Punct &B, const Punct &C)
{
    int produs_vectori=(B.y-A.y)*(C.x-A.x)-(C.y-A.y)*(B.x-A.x);
    if(produs_vectori <= 0)
        return 0;
    else return 1;

}

vector<Punct> convex_hull_Jarvis(vector<Punct>& points)
{
     vector<Punct> CH;
     int start = 0;
     for(int i = 1 ; i < points.size(); i++)
     {
         if(points[i].x < points[start].x)
            start=i;
         if(points[i].x == points[start].x and points[i].y > points[start].y)
            start=i;
     }

     CH.push_back(points[start]);

     for(int i = 0 ; i < CH.size(); i++)
     {
         Punct nextPoint = (CH[i]==points[0])? points[1]: points[0];
         for(int j = 0; j < points.size(); j++)
             if(produs_vectorial(CH[i], points[j], nextPoint) > 0)
                nextPoint = points[j];

         if (nextPoint != CH[0])
            CH.push_back(nextPoint);
     }

     return CH;
}

vector<Punct> convex_hull_Graham(vector<Punct> &P)
{
     int start = 0;
     for(int i = 1; i < P.size(); i++)
        if(P[i].y < P[start].y || (P[i].y == P[start].y && P[i].x < P[start].x))
            start=i;

     Sorter::Sort(P, start);
     P.insert(P.begin(), P[P.size()-1]);

     int nrH=2; // P[0], P[start];

     for(int i = 3; i < P.size(); i++)
     {
         while(nrH > 1 && produs_vectorial(P[nrH-1], P[nrH], P[i]) > 0)
            nrH--;

         nrH++;
         swap(P[nrH], P[i]);
     }

     return vector<Punct>(P.begin(), P.begin()+nrH);

}

main()
{
    vector<Punct>points;
    vector<Punct>rez;
    int comanda;

    printf("%s", "Convex hull alghoritm using Jarvis March or Graham Scan");
    printf("%s", "\nReading the points from dateConvex.in");
    citire(points);
    printf("%s", "\nPick one of the two alghorithms:\n1.Jarvis March\n2.Graham Scan\n");

    cin>>comanda;

    if(comanda == 1)
       rez = convex_hull_Jarvis(points);
    else rez = convex_hull_Graham(points);

    afisare(rez.size(), rez);
}

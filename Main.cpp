#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

/**
 * Metode per convertir un numero en binari, es guarda la seva representacio en el vector
 * @brief convert
 * @param x
 * @param a
 * @return
 */
long long convert(long long x, vector<long long>& a)
{
    long long remainder, digits = 0, dividend = x;
    while(dividend != 0) {
        dividend = dividend / 2;
        digits++;
    }
    a = vector<long long>(digits);
    dividend = x;
    for(int i = digits - 1; i >= 0; i--) {
        remainder = dividend % 2;
        a[i] = remainder;
        dividend = dividend / 2;
    }
}

/**
 * Metode per calcular el maxim comu divisor de dos nombres a i b
 * @brief gcd
 * @param a
 * @param b
 * @return
 */
long long gcd(long long a, long long b)
{
    if(b == 0) return a;
    else return gcd(b, a % b);

}

/**
 * Metode per calcular l'inversor en aritmetica modular, tenint com a precondicio que existeix l'invers,
 * es a dir, que mcd(a,n) = 1
 * @brief extended_gcd
 * @param a
 * @param n
 * @return
 */
long long extended_gcd(long long a,long long n)
{
    long long tmp;
    long long q = 0;
    long long x0 = 1; long long x1 = 0;
    long long y0 = 0; long long y1 = 1;
    long long r0 = n; long long r1 = a;
    while(r1 != 1) {
        q = int(r0/r1);
        tmp = r1;
        r1 = r0 - (q*r1);
        r0 = tmp;
        tmp = x1;
        x1 = x0 - (q*x1);
        x0 = tmp;
        tmp = y1;
        y1 = y0 - (q*y1);
        y0 = tmp;
    }
    return y1;
}

/**
 * Metode per calcular l'exponenciació ràpida a^z mod n
 * @brief expo_rapida
 * @param a
 * @param z
 * @param n
 * @return
 */
long long expo_rapida(long long a, long long z, long long n)
{
    long long x = 1;
    vector<long long> tr;
    convert(z,tr);
    for(int i = 0; i < tr.size(); ++i) {
        x = (x*x)%(n);
        if(tr[i] == 1){
            x = (x*a)%n;
        }
    }
    return x;
}

/**
 * Metode per saber si un numero es primer o no
 * @brief isPrime
 * @param x
 * @return
 */
int isPrime(long long x)
{
    for(long long  i = 2; i <= x/2; i++) {
        if(x%i == 0) return 0;
    }
    return 1;
 }

/**
 * Metode per factoritzar un nombre n, deixa els factors de n en el vector
 * @brief factorizta
 * @param n
 * @param v
 * @return
 */
void factoritza(long long n, vector<long long>& v)
{
    for(long long x = 2; x <= n; x++)
        if(n%x==0 && isPrime(x)) v.push_back(x);
}

/**
 * Metode per calcular el totien d'euclides
 * @brief totien
 * @param p
 * @param q
 * @return
 */
long long totien(long long p, long long q)
{
    return (p-1)*(q-1);
}

/**
 * Metode per passar d'una variable long long a string
 * @brief NumberToString
 * @param Number
 * @return
 */
string NumberToString(long long Number)
{
     ostringstream ss;
     ss << Number;
     return ss.str();
}

int main()
{
    long long n = 297045209;
    long long e = 31273;

    vector<long long> v;
    // trobem els factors de n
    factoritza(n,v);

    cout << "p = " << v[0] << endl;
    cout << "q = " << v[1] << endl;

    // calculem el totien d'euclides
    long long totEuc = totien(v[0],v[1]);

    // trobem la clau privada
    long long d = extended_gcd(e,totEuc);

    cout << "k = " << d << endl;

    string m = "200666210013190540063819167261614542049809460199890445116717160241121464042499593051857884267983799137962994008940442141432992141352380276156126211645697064871407200666210051579330151477860132365869182961368127198214225533994053579647144984612245696933273547644008802873201260264090027782081863804000942130162886679294587920109896540264319216029171407054691479037854213251028951074326959150327472247090457210337132278807762158890901227966908248073711064871407003435238017323126026960027020241784242747266228565601238705475025053173255247164096123584008141160090837481119374905144840117043831873253848444132415482196125203095493910100256021002211169256211300058028495284790158059618256289412666007369665108774719193676463081290341105600659219129688101113155169719642150195533169440992270886187261675559052295135169145625083851481113109131250987500212017148262928788119374905163451235138609015119028139162724513203886557236094882023072142060993078060937473095541526114454060087817311124026348255528452156378232182192551109584331115554773006830772007010422026576760022586512078061033109896540264319216209950616017085294100346158181881429147557158100528495271366459287197486200605722208666017108320490135742354027000553182409188007098326156346036093619614006816440255528452265381055010487868073044409150211436194235369151477860291050968200605722231264565108320490243134102142644652096123584267284364026275213188037444153965068208278816081057196";

    cout << " - Missatge encriptat C = " << m << endl;

    vector<string> v2;
    // Dividim en Ci parts
    string a = "";
    int j = 0;
    for(int i = 0; i < m.length(); ++i) {
        a = a + m[i];
        ++j;
        if(j%9 == 0) {
            v2.push_back(a);
            a = "";
        }
    }

    vector<long long> final(v2.size());
    // Decodifico Ci
    for(int i = 0; i < v2.size(); ++i) {
        final[i] = atol((v2[i].c_str()));
        final[i] = expo_rapida(final[i],d,n);
    }

    // afegeixo 0 necesaris
    vector<string> last(final.size());
    string t;
    for(int i = 0; i < final.size(); ++i) {
        t = NumberToString(final[i]);
        while(t.length() < 8) {
            t = "0" + t;
        }
        last[i] = t;
    }

    // concatena
    string done;
    for(int i = 0; i < last.size(); ++i) {
        done += last[i];
    }

    // agrupa de 3 en 3
    vector<string> vs(done.length()/3);
    int k = 0;
    string sp;
    for(int i = 0; i < done.length(); ++i) {
        sp += done[i];
        ++k;
        if(k%3 == 0) {
            vs.push_back(sp);
            sp = "";
        }
    }

    // mostrar missatge
    cout << endl;
    cout << " - Missatge desencriptat P = ";
    for(int i = 0; i < vs.size(); ++i) {
        int fl = atoi(vs[i].c_str());
        char c = fl;
        cout << c;
    }
    cout << endl;
}

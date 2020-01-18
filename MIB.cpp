#include <bits/stdc++.h>
using namespace std;

int contadorDfs;          // contador para saber la iteración de la busqueda en profundidad
bool flag;                // Flag para saber si un grafo no tiene puente.


/* Funcion DFS
   realiza un recorrido en profundidad a partir del nodo v, identifica la mínima iteración necesaria para llegar a cada nodo,
   el número de iteración en la que se visitó al nodo, e imprime por terminal los arcos que al ser eliminados generan otra 
   componente conexa (puente).
   ---------------------------------
   recibe un entero u que identifica al  nodo, un map grafo que representa al grafo y sus listas de adyacencia, un map min_iteracion
   en la que se guarda el valor de la mínima iteración necesaria para cada nodo, un map iteracion para almacenar la iteracion en que es
   visitado cada nodo y un map padre que almacena el nodo padre de cada nodo.
*/
void DFS(int u, map<int,vector<int> > & grafo,map <int,int> & min_iteracion,map <int,int> & iteracion,map <int,int> & padre){
    min_iteracion[u] = contadorDfs; // se actualiza los valores según el contador global antes definido
    iteracion[u] = contadorDfs;
    contadorDfs++; // se aumenta el contador por cada iteración de dfs

    for (int i = 0; i < (int)grafo[u].size(); i++){  // se recorren los vecinos del nodo u
        int v = grafo[u][i];
        if (iteracion[v] == -1){   // si el nodo no ha sido visitado
            padre[v] = u;
            DFS(v,grafo,min_iteracion,iteracion,padre);  // se realiza DFS a cada nodo vecino
            if (min_iteracion[v] > iteracion[u]){   // si los nodos forman un puente
                flag = true;
                cout << u << " " << v << '\n';   // imprime el puente
            }
            min_iteracion[u] = min(min_iteracion[u], min_iteracion[v]); // se actualiza la mínima iteración
        }
        else if (v != padre[u]){  // si el nodo no es el padre
            min_iteracion[u] = min(min_iteracion[u], iteracion[v]);
        } 
    }
}

int main(){
    int n;
    while(cin >> n){
        int a,v;
        string line;

        map<int, vector<int> > grafo;            // Inicialización de grafo.
        map<int, int> min_iteracion;                   // Vector de iteraciones minimas de Dfs que necesita el nodo respectivo para ser visitado.
        map<int, int> iteracion;                   // Vector de iteraciones en que fue visitado el nodo respectivo.
        map<int, int> padre;                // Vector de vertices que corresponden al padre del nodo respectivo (para un dfs dado).

        getline(cin,line);
        istringstream is(line);
        
        for (int i = 0; i < n; i++){
            vector < int > vecinos;             

            getline(cin,line);
            istringstream is(line);
            is >> a;                 //toma el primer valor de la linea (el nodo).

            while(is >> v){    // recorre los valores de la linea (los vecinos).
                vecinos.push_back(v);
            }
            grafo.insert(make_pair(a, vecinos));
            min_iteracion.insert(make_pair(a,0));
            iteracion.insert(make_pair(a,-1));
            padre.insert(make_pair(a,-1));
        }
        flag = false;
        for (auto itr = grafo.begin(); itr != grafo.end(); itr++){      // Se hace DFS por cada componente conexa del grafo.
            contadorDfs = 0;
            DFS(itr->first,grafo,min_iteracion,iteracion,padre);
        }
        if (!flag){
            cout << "No Existe Corte.\n";
        }
        cout << '\n';
        
    }
    return 0;
}
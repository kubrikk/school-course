#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


struct DisjointSet {

    vector< int > parents;  // `предок` в понятии организации дерева множества
    vector< int > sizes;    // массив для хранения мощности множества,
                            // актуальный размер хранится в `корне` множества

    // конструируем СНМ для хранения информации об n объектах по их индексам
    DisjointSet(int size) {
        // резервируем память
        parents.resize(size);
        sizes.resize(size);
        for (int i = 0; i < size; i++) {
            parents[i] = i;     // изначально каждый элемент образует отдельное
                                // множество (каждый элемент является `корнем`)
            sizes[i] = 1;   // размер каждого мноежства в таком случае -- 1
        }
    }

    // метод, возвращающий `корень` множества
    int get_id_set(int node) {
        // если вершина `node` является своим предком
        if (parents[node] == node) {
            return node;    // то она и есть `корень` множества
        }
        // иначе перестроим дерево, сделав предком для всех вершин в порядке
        // рекурсинвого обхода `корень` древесного множества
        parents[node] = get_id_set(parents[node]);
        // вернём `корень`
        return parents[node];
    }

    // метод для объединения двух множнств по экземплярам
    void merge(int fir_node, int sec_node) {

        // узнаём `корни` двух множеств 
        int fir_root = get_id_set(fir_node);
        int sec_root = get_id_set(sec_node);
        
        // если это разные множества
        if (fir_root != sec_root) {
            // присоединяем меньшее множество к большему
            if (sizes[fir_root] > sizes[sec_root]) {
                // `корень` меньшего множества становится потомком `большего`
                parents[sec_root] = fir_root;
                sizes[fir_root] += sizes[sec_root]; // переопредеяем размер
            }
            else {
                parents[fir_root] = sec_root;
                sizes[sec_root] += sizes[fir_root];
            }
        }

        return;
    }
};


int main() {

    int n, m;
    cin >> n >> m;

    DisjointSet djs(n);

    // первое значение тройки -- вес ребра, второе и третье -- вершины
    vector< pair< int, pair< int, int > > > edges(n);
    // ввод рёбер
    for (int i = 0; i < m; i++) {
        // вводятся номера вершин, образующих ребро, и их вес
        cin >> edges[i].second.first >> edges[i].second.second
            >> edges[i].first;
    }

    // сортируем лексикографически тройки (для нас важна сортировка по весу)
    sort(edges.begin(), edges.end());
    vector< pair< int, pair< int, int > > > result; // массив для хранения 
                                                    // остовного дерева
    // последовательно перебираем рёбра (отсортированные по весу)
    for (int i = 0; i < m; i++) {
        int first_vertex = edges[i].second.first;
        int second_vertex = edges[i].second.second;

        // если ребро связывает две компоненты связности
        if (djs.get_id_set[first_vertex] != djs.get_id_set[second_vertex]) {
            // используем его
            result.push_back(edges[i]);
            djs.merge(first_vertex, second_vertex);
        }
    }
    
    // вывод информации о рёбрах минимального остова
    for (int i = 0; i < result.size(); i++) {
        cout << result[i].second.first << ' ' << result[i].second.second << ' '
             << result[i].first << endl;
    }

    return 0;
}
#include <iostream>
#include <vector>

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

    // количество элементов множества, и количество команд объединения
    int n, m;
    cin >> n >> m;

    DisjointSet djs(n);
    for (int i = 0; i < m; i++) {
        // элементы `fir_node` и `sec_node` в одном множестве
        int fir_node, sec_node;
        cin >> fir_node >> sec_node;
        djs.merge(fir_node, sec_node);
    }

    // вывод информации о каждом элементе 
    // {номер элемента, номер `корня`, размер множества}
    for (int i = 0; i < n; i++) {
        cout << i << ": " << djs.get_id_set(i) << ": " << 
            djs.sizes[djs.get_id_set(i)] << endl;
    }

    return 0;
}